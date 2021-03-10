#include "stdlib.h"

#include <iostream>
#include <fstream>

#include "TString.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TTree.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH2D.h"
#include "TChain.h"
#include "AnaUtils.h"
#include "ReadGENIE.h"

using namespace std;
using namespace ReadGENIE;

void GENIEReadChain(TChain * ch, TTree * tout, TH1F * &hCCrate, const int nEntryToStop = -999)
{
  ReadGENIE::SetChain(ch);

  int ientry = 0;
  while(ch->GetEntry(ientry)){
    if(ientry%100000==0){
      printf("myEntries %d\n", ientry);
    }

    if(nEntryToStop>0){
      if(ientry>=nEntryToStop){
        printf("\n\n\n************************  GENIE Breaking after %d entries ***********************************************\n\n", nEntryToStop);
        break;
      }
    }

    //do it before the loop continues for any reason
    ientry++;

    //===========================================================================

    const TString ecode=gEvtCode->GetString();
    if(ecode.Contains("Weak[NC]")){//skip NC
      continue;
    }
    else if(!ecode.Contains("Weak[CC]")){
      printf("not cc!!! %s\n", ecode.Data()); exit(1);
    }

    if(!hCCrate){
      hCCrate = new TH1F("hCCrate","", 100000, 0, 100);//1MeV per bin
    }

    const double tmpenu = StdHepP4[0][3];
    hCCrate->Fill(tmpenu);

    const int tmpevent = EvtNum;
    const int tmpprod= -999;//not needing G2NeutEvtCode anymore, no need to modify GENIE code; abs(G2NeutEvtCode);
    const double tmppw = 1;//to-do EvtXSec;

    const int tmpnp = StdHepN;

    //printf("\ntest ientry %d tmpevent %d tmpprod %d tmpenu %f tmppw %f tmpnp %d\n", ientry, tmpevent, tmpprod, tmpenu, tmppw, tmpnp);
    
    AnaUtils::Ini();

    const bool isHydrogen = ecode.Contains("1000010010");//special case

    int idxIni = -999;
    int idxRESnucleon = -999;
    int idxRESpi = -999;
    int idxDelta = -999;

    //initialise leading pion stats for each entry
    Int_t pionID = 0; Int_t leadingpionID = 0; 
    double Etemp = -999.; 

    //loop over all particles, pick pi-p, get leading FS pi-p
    
    for(int ii=1; ii<tmpnp; ii++){//loop to pick out leading pion
      const int tmpid = StdHepPdg[ii]; //pip = 211
      const double tmptote = StdHepP4[ii][3];
      const GeneratorIO::dtype IniOrFinaltype = ReadGENIE::GetIniOrFinalType(ii, isHydrogen, tmpevent, tmpid);
      //check to see if leading. Make sure it's kFINAL!
      if(tmpid == 211 && tmptote > Etemp && IniOrFinaltype==kFINAL){//update
	Etemp = tmptote;
	leadingpionID = pionID;
      }
      if(tmpid == 211){pionID++;} //have to update for all FS pi-p}
    }//first loop over particles

    if(ientry%100000==0){printf("we have %d pi-p\n", pionID); printf("Leading FS pion ID %d\n", leadingpionID); printf("Leading FS pion E %f\n", Etemp);}

    pionID = 0; //reset counter
    //loop over all particles and calc, interfering with FS pi-p only 
    bool isLeadingPion = false;

    if(ientry%100000==0){printf("DEBUG: ONTO SECOND LOOP\n");}
    
    for(int ii=1; ii<tmpnp; ii++){//2nd loop, for all particles
      const int tmpid = StdHepPdg[ii]; //pip = 211

      if( ( abs(tmpid) == 12 || abs(tmpid) == 14 || abs(tmpid) == 16 ) && StdHepFm[ii]!=0 ){//charm decay to neutrino
        continue;
      }

      if( abs(tmpid)==13 && StdHepFm[ii]!=0 ){//skip non CC muon
        continue;

      }

      if(tmpid>1000000000){//skip nucleus
        continue;
      }

      //leading pion is tagged in ID so will only calc pion if it's the same
      if(tmpid==211){
	if(pionID==leadingpionID){
	  if(ientry%100000==0){printf("Found leading pion. ID %d, Energy %f\n", pionID, StdHepP4[ii][3]);}
	  isLeadingPion=true;
	}
	else{
	  if(ientry%100000==0){printf("Subleading pion. ID %d, Energy %f\n", pionID, StdHepP4[ii][3]);}
	  isLeadingPion=false;
	} //reset to false after leading pion found
	pionID++;
      }

      const GeneratorIO::dtype IniOrFinaltype = ReadGENIE::GetIniOrFinalType(ii, isHydrogen, tmpevent, tmpid);
      const GeneratorIO::dtype RESdtype = ReadGENIE::GetRESType(ii, ecode, IniOrFinaltype, idxIni, idxDelta, idxRESnucleon, idxRESpi);
      const double tmpKNsrc = ReadGENIE::GetKNsource(ii, IniOrFinaltype, idxDelta); //proton 1; pion -1      
      const bool isOK = (IniOrFinaltype!=GeneratorIO::kNULL || RESdtype!=GeneratorIO::kNULL);

      if(ientry%100000==0 && tmpid == 211){printf("Is pion OK?");}
      if(isOK){ //continue if this is non-leading pi-plus
	if(ientry%100000==0 && tmpid == 211){printf(" YES.\n");}

	if(tmpid==211 && isLeadingPion==false){
	  if(ientry%100000==0){printf("Throwing subleading pion\n");};
	}
	else{
	  if(tmpid==211 && ientry%100000==0){printf("\n Leading pion processing...\n");}

	  const double tmpmom1 = StdHepP4[ii][0];
	  const double tmpmom2 = StdHepP4[ii][1];
	  const double tmpmom3 = StdHepP4[ii][2];
	  const double tmptote = StdHepP4[ii][3];
	
        //test
        //const TVector3 tmpvec(tmpmom1, tmpmom2, tmpmom3); printf("test particle %d %f %f %f %f %d mom %f theta %f\n", ii, tmpmom1, tmpmom2, tmpmom3, tmptote, tmpid, tmpvec.Mag(), tmpvec.Theta()*TMath::RadToDeg());

        //if(ecode.Contains("QES")){ cout<<"test event "<<tmpevent<<" ii "<<ii<<" IniOrFinaltype "<<IniOrFinaltype<<" idxIni "<<idxIni<<" ecode "<<ecode<<" status "<<StdHepStatus[ii]<<" pdg "<<StdHepPdg[ii]<<" scat "<<StdHepRescat[ii]<<" StdHepFd "<<StdHepFd[ii]<<" StdHepLd "<<StdHepLd[ii]<<" RESdtype "<<RESdtype<<" "<<endl;}
          
	  if(tmpid == 211 && ientry%100000==0){printf("GENIE pion Proceed?\n"); if(IniOrFinaltype==kFINAL){printf("kFINAL\n");}else{printf("NOT kFINAL!!!\n");}}
	  if(GeneratorIO::GENIEProceed(IniOrFinaltype, RESdtype, ecode, tmpevent, tmpprod, tmpenu, tmppw, tmpmom1, tmpmom2, tmpmom3, tmptote, tmpid, tmpKNsrc)){

          //if(ecode.Contains("QES")){printf("test now do Main IniOrFinaltype %d\n", IniOrFinaltype); ch->Show(ientry);}
	    if(tmpid == 211 && ientry%100000==0){printf("GENIE pion Proceeded\n");}
	    AnaUtils::MainProceed();
	  }
	  else if(tmpid == 211 && ientry%100000==0){printf("GENIE pion NOT Proceeded\n");}
	}//is not subleading pion
      }//isOK
      else{
	if(ientry%100000==0 && tmpid == 211){printf(" NO.\n");}
      }

    }//loop over particle

    AnaUtils::DoFill(tout);
  }//loop over event

  cout<<"All entries "<<ientry<<endl;
}

int GiBUUReadFile(const TString filelist, TTree * tout, const int nFileToStop)
{
  TString tmpfl4target(filelist);
  tmpfl4target.ToUpper();
  int tmptargetZ = 6;
  if(tmpfl4target.Contains("HYDROGEN")){
    tmptargetZ = 1;
  }

  ifstream fl;
  fl.open(filelist);
  if(!fl.is_open()){
    printf("filelist %s not opened!\n", filelist.Data()); exit(1);
  }

  int filecount=0;
  int totlinecount=0;
  int totnrun = 0;

  string singlefile;
  while(getline(fl,singlefile)){
    if(filecount%10==0){
      cout<<"File count "<<filecount<<" total line count "<<totlinecount<<" total nrun "<<totnrun<<endl;
    }

    if(nFileToStop>0){
      if(filecount>=nFileToStop){
        printf("\n\n\n************************  GiBUU Breaking after %d files ***********************************************\n\n", nFileToStop);
        break;
      }
    }

    filecount++;
  //====================================== core loop ======================================
  ifstream elf;
  elf.open(singlefile.c_str());
  if(!elf.is_open()){
    printf("singlefile %s not opened!\n", singlefile.c_str()); exit(1);
  }

  string fline;
  AnaUtils::Ini();
  getline(elf, fline);//after reading even the last line it is still not eof
  while(!elf.eof()){
    TString tmpline(fline);
    totlinecount++;
    if(tmpline.Contains("Event")){//simply ignore it
      getline(elf, fline);
      continue;
    }
    
    double tmppw;
    double tmpmom1, tmpmom2, tmpmom3, tmptote;                                                                                                     
    double tmppos1, tmppos2, tmppos3;//position
    int tmprun, tmpevent, tmpid, tmpcharge, tmpprod;
    double tmpenu;
    
    sscanf(tmpline.Data(),"%d %d %d %d %lf %lf %lf %lf %lf %lf %lf %lf %*d %d %lf", &tmprun, &tmpevent, &tmpid, &tmpcharge, &tmppw, &tmppos1, &tmppos2, &tmppos3, &tmptote, &tmpmom1, &tmpmom2, &tmpmom3, /*&history,*/ &tmpprod, &tmpenu);
    
    if(GeneratorIO::GiBUUProceed(filecount, tmprun, tmpevent, tmpcharge, tmpprod, tmpenu, tmppw, tmpmom1, tmpmom2, tmpmom3, tmptote, tmpid, tmptargetZ)){
      AnaUtils::MainProceed();
    }

    getline(elf, fline);

    bool kChangeEvent = false;
    bool kChangeRun = false;
    if(elf.eof()){
      kChangeEvent = true;
      kChangeRun = true;
    }
    else{
    //only read in new event to check for event switching
      int nextRun, nextEvent;
      sscanf(fline.c_str(),"%d %d", &nextRun,  &nextEvent);
      if(nextEvent!=tmpevent){
        kChangeEvent = true;
      }
      if(nextRun!=tmprun){
        kChangeRun = true;
      }
    }

    if(kChangeEvent){
      AnaUtils::DoFill(tout);
      AnaUtils::Ini();
    }

    if(kChangeRun){
      totnrun++;
    }

  }
  elf.close();
  //============================================= end core ==============================================
  }

  cout<<"Final file count "<<filecount<<" total line count "<<totlinecount<<" total nrun "<<totnrun<<endl;
  return totnrun;
}

void anaGenerator(const TString tag, const TString filelist, const int tmpana, const int nToStop=-999)
{
  cout<<"please check "<<tag<<" "<<filelist<<" "<<tmpana<<endl;

  TreeIO::experiment kExp = TreeIO::kNONE;
  if(filelist.Contains("MINERvA")){
    kExp = TreeIO::kMINERvA;
  }
  else if(filelist.Contains("T2K")){
    kExp = TreeIO::kT2K;
  }
  else if(filelist.Contains("DUNE")){
    kExp = TreeIO::kDUNE;
  }
  else{
    cout<<"\n\nnon-experimental filelist "<<filelist<<endl<<endl;
  }

  TFile *fout=new TFile(Form("outplot/outAna%d_%s.root", tmpana, tag.Data()),"recreate");
  TTree * tout = TreeIO::GetTree((analysis)tmpana, kExp);

  //_________________________________________________________________________________________________
  //_________________________________________________________________________________________________
  TChain * genieinput = AnaUtils::InputROOTFiles(filelist, "gRooTracker");
  TH1F * hCCrate = 0x0; 
  int nrun = -999;
  if(genieinput){
    GENIEReadChain(genieinput, tout, hCCrate, nToStop);
  }
  else{
    nrun = GiBUUReadFile(filelist, tout, nToStop);
  }

  //_________________________________________________________________________________________________
  //_________________________________________________________________________________________________

  fout->cd();

  if(hCCrate){
    hCCrate->Write();
  }

  TTree *theader = new TTree("header","header");
  theader->Branch("nrun",&nrun);
  theader->Fill();
  theader->Write();

  tout->Write();

  fout->Save();
  fout->Close();

  return;
}

int main(int argc, char* argv[])
{
  //void anaGenerator(const TString tag, const TString filelist, const int tmpana, const int nToStop)
  if(argc==4){
    anaGenerator(argv[1], argv[2], atoi(argv[3]));
  }
  else if(argc==5){
    anaGenerator(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]));
  }
  else{
    printf("wrong argc %d\n", argc); return 1;
  }
  return 0;
}
