#ifndef _ANAUTILS_
#define _ANAUTILS_

#include "ProcessUtils.h"

using namespace std;
using namespace ProcessUtils;

class AnaUtils
{
 public:
  static void DoFill(TTree *tt);
  static void Ini();

  static TChain * InputROOTFiles(const TString file, const TString tr);
  static void MainProceed();

 private:
  //DoFill
  static bool IsGood();
  static void Calc();

  //need to Ini-->
  static TLorentzVector * baryonfullp;
  //<--
};

TLorentzVector * AnaUtils::baryonfullp = new TLorentzVector;

TChain * AnaUtils::InputROOTFiles(const TString file, const TString tr)
{
  TChain *ch=0x0;

  if(file.Contains(".root")){
    ch = new TChain(tr);
    ch->Add(file);
  }
  else{
    ifstream fin(file);
    if(!fin){
      printf("AnaUtils::InputROOTFiles file not found \n%s\n\n",file.Data()); exit(1);
    }

    TString buff;
    while(fin.good()){
      fin>>buff;
      if(buff!=""){
        if(!buff.Contains(".root")){
          return 0x0;
        }
        else{
          if(!ch){
            ch = new TChain(tr);
          }
          ch->Add(buff);
        }
      }
    }
  }

  //const Int_t ent = ch->GetEntries(); //takes infinity time!!
  printf("\t%d trees!\n",ch->GetNtrees());

  return ch;
}

//=======================================================================================================
//Generator independent procedures
//=======================================================================================================

void AnaUtils::MainProceed()
{
  if(expmode==kMINERvA || expmode==kNONE){
    if(anamode == GFS){
      ProceedMINERvAGFS();
    }
    else if(anamode == LOWRECOIL){
      ProceedMINERvALOWRECOIL();
    }
    else if(anamode == NUBAR1PI){
      ProceedMINERvANUBAR1PI();
    }
    else if(anamode == MMECCQE){
      ProceedMINERvAMECCQE();
    }
    else if(anamode == CLR){
      ProceedCLR();
    }
    else if(anamode == RESPS){
      ProceedRESPS();
    }
    else if(anamode == NUGAS){
      ProceedNUGAS();
    }
    else if(anamode == GFSPIZERO){
      ProceedMINERvAGFSPIZERO();
    }
    else if(anamode == GFS0PI){
      ProceedMINERvAGFS0PI();
    }
  }
  else if(expmode==kT2K){
    if(anamode == GFS){
      ProceedT2KGFS();
    }
    else if(anamode == GFSEXP){
      ProceedT2KGFSEXP();
    }
  }
  else if(expmode==kDUNE){
    if(anamode == EXCL3){
      ProceedDUNEEXCL3();
    }
  }
}



void AnaUtils::DoFill(TTree *tt)
{
  if(IsGood()){
    Calc();
    tt->Fill();
    static int count = 0;
    count++;
    if(count%10000==0){
      cout<<"Fill Count "<<count<<endl;
    }
  }

  //need to do it also before first event
  //do it outside
  //Ini();
}

void AnaUtils::Ini()
{
  IniTreeIO();

  IniGeneratorIO();

  IniProcessUtils();

  baryonfullp->SetXYZT(0,0,0,0);
}

bool AnaUtils::IsGood()
{
    if(anamode==GFSEXP || anamode==CLR){
    //if(anamode==GFS || anamode==GFSEXP || anamode==CLR){
    cout<<"need to think more! stop for the moment"<<endl; exit(1);
  }

    if(anamode==GFSPIZERO || anamode==GFS0PI || anamode==GFS){
      if(anamode==GFS && ProcessUtils::nuEcutflag){ //fix GiBUU flux? Hopefully
	return false;
      }
      //if(anamode==GFSPIZERO || anamode==GFS0PI){
      if(IsBKG()){
	return false;
      }
      
      //1mu
      if(GetNMuons()!=1){
	return false;
      }
      
      //Np at least one proton needed for baryon kinematic calculation
      //if(GetNProtons()==0){
      if(GetNProtons()!=1){ //more rigorous test for GiBUU
	return false;
      }
      
      if(anamode==GFSPIZERO || anamode == GFS){
	//if(anamode==GFSPIZERO){
	//1 or more pion
	//if(GetNPions()==0){
	//1 pion only
	if(GetNPions()!=1){
	  return false;
	}
      }
      else{
	//require 0 pi 
	if(GetNPions()){
	  return false;
	}
      }
      
      return true;
      
      /*
      //1mu
      //0pi at least 1 p
      //1pi any p
      return (npar >= 101 && npar < 120);
      */
    }
    else if(anamode==RESPS){
      //1mu
      if(GetNMuons()!=1){
	return false;
      }
      
      //0 or 1pi
      if(GetNPions()>1){
	return false;
      }
      
      if(IsBKG()){
	return false;
      }
      
      //only care about RES
      if(evtMode!=2){
	return false;
      }
      
      return true;
    }
  else if(anamode==MMECCQE){
    if(GetNMuons()!=1){
      return false;
    }

    if(IsBKG()){
      return false;
    }

    return true;
  }
  else if(anamode==LOWRECOIL){
    return (GetNMuons()==1);
  }
  else if(anamode==NUBAR1PI){
    if(GetNMuons()!=1)
      return false;

    if(GetNPions()!=1)
      return false;

    if(IsBKG()){
      return false;
    }

    return true;
  }
  else if(anamode==NUGAS){
    if(GetNMuons()!=1)
      return false;
    
    if(targetZ!=1)
      return false;

    if(IsBKG())
      return false;

    return true;
    /*
    if(IsBKG()){
      return false;
    }

    if(GetNNeutrons()==1 && GetNProtons()==0 && GetNPions()==0)//antinu QE
      return true;

    if(GetNNeutrons()==0 && GetNProtons()==1 && GetNPions()==1)//RES
      return true;

    return false;
    */
  }
  else if(anamode==EXCL3){
    if(IsBKG()){
      return false;
    }

    //1mu
    if(GetNMuons()!=1){
      return false;
    }

    //1p
    if(GetNProtons()!=1){
      return false;
    }

    //1pi
    if(GetNPions()!=1){
      return false;
    }

    return true;
  }
  else{
    printf("unknown anamode %d\n", anamode); exit(1);
  }
}

void AnaUtils::Calc()
{
  const TLorentzVector dummyNu(0,0,lineenu, lineenu);
  const TLorentzVector lvq= dummyNu - (*muonfullp);

#if __OPENCALC__
  //---muon: 2
  muonmomentum = muonfullp->P();
  muontheta = muonfullp->Theta()*TMath::RadToDeg();

  //---W: 5
  //not used q3 = lvq.P();
  Q2 = -lvq.M2();
  TLorentzVector dummyP, dummyW;
  //assum proton target
  dummyP.SetXYZM(0,0,0,ProtonMass());
  dummyW = lvq+dummyP;
  Wrest = dummyW.M();
  xrest = Q2/2/(dummyP.Dot(lvq));

  dummyW = lvq+(*iniNfullp);
  Wtrue = dummyW.M();
  xBj = Q2/2/(iniNfullp->Dot(lvq));

  //---hadron: 8; baryonfullp is intermediate locally
  protonmomentum = protonfullp->P();
  protontheta = protonfullp->Theta()*TMath::RadToDeg();
  pionmomentum = pionfullp->P();
  piontheta = pionfullp->Theta()*TMath::RadToDeg();
  //pionEk = pionfullp->E()-PionMass();
  pionEk = Ekin(pionfullp, PionMass()); //only use experimental momentum

  omegamup = muonfullp->Angle(protonfullp->Vect())*TMath::RadToDeg();
  //modelf = muonfullp->E() * protonfullp->E() / lineenu * (1.-TMath::Cos(omegamup*TMath::DegToRad()));
  const double gee = 0.876;
  modelf = (muonfullp->E() * protonfullp->P() - gee) / lineenu * TMath::Cos(omegamup*TMath::DegToRad());
  //TVector3 n1 = ((dummyNu.Vect()).Unit()).Cross((muonfullp->Vect()).Unit());
  TVector3 n1 = ((dummyNu.Vect()).Cross(muonfullp->Vect())).Unit();
  //TVector3 n2 = ((protonfullp->Vect()).Unit()).Cross((pionfullp->Vect()).Unit());
  TVector3 n2 = ((protonfullp->Vect()).Cross(pionfullp->Vect())).Unit();
  double n1dotn2 = n1.Dot(n2); //if(n1dotn2 < 0.){n1dotn2 *= -1;}
  chi = TMath::ACos(n1dotn2) * TMath::RadToDeg();
        
  //(*baryonfullp) = (*protonfullp) + (*pionfullp);
  baryonfullp->SetXYZT(protonfullp->X()+pionfullp->X(), protonfullp->Y()+pionfullp->Y(), protonfullp->Z()+pionfullp->Z(), Energy(protonfullp, ProtonMass())+Energy(pionfullp, pionfullp->P()>1E-10? PionMass():0));//need to use experimental momentum only
  baryonmomentum = baryonfullp->P();
  baryontheta = baryonfullp->Theta()*TMath::RadToDeg();
  baryonmass = baryonfullp->M();

  //---TKI: 4+1
  /*//allow heavier nuclei
  if(targetZ!=6 && targetZ!=1){
    printf("AnaUtils::Calc targetZ not 1 nor 6! %d\n", targetZ); exit(1);
  }
  */

  //pretend hydrogen is carbon, same as experiment
  const int localZ = (targetZ==1 ? 6 : targetZ);

  const int localA = AnaFunctions::getTargetA(localZ);
  const TLorentzVector neutrinofullp(0,0,1,1);
  double dummymu, dummybaryon;
  double dummyomega, dummymodelf, dummychi;
  //void getCommonTKI(const int targetA, const int targetZ, const TLorentzVector *neutrinofullp, const TLorentzVector *muonfullp, const TLorentzVector *baryonfullp, double & dalphat, double & dphit, double & dpt, double & neutronmomentum, double & dpTT, double & muontheta, double & baryontheta)

  //AnaFunctions::getCommonTKI(dummyA, targetZ, &neutrinofullp, muonfullp, baryonfullp, dalphat, dphit, dpt, neutronmomentum, dpTT, dummymu, dummybaryon);
  AnaFunctions::getCommonTKI(dummyA, targetZ, &neutrinofullp, muonfullp, baryonfullp, pionfullp, dalphat, dphit, dpt, neutronmomentum, dpTT, dummymu, dummybaryon, dummyomega, dummymodelf, dummychi);
  
  /*
    protonTT = protonfullp->Vect().Dot(ztt);
    pionTT = pionfullp->Vect().Dot(ztt);
  */

  //dpTy = dpt * cos(dalphat*TMath::DegToRad());
#endif

#if __OPENCLR__
  const TVector3 ztt = (dummyNu.Vect().Cross(muonfullp->Vect())).Unit();    

  const double ares = -0.3; //0.2

  lrsign = 0;
  if(protonfullp->E()>1E-10){
    //right is -1, left is +1
    lrsign = protonfullp->Vect().Dot(ztt) > 0 ? -1 : 1;

    //just use the unweighted lrsign (original one)
    pseudosign = lrsign;
  }

  RESmass = -999;
  adlerPhi = -999;
  pseudoPhi = -999;
  w2 = 1;
  wpseudo2 = 1;
  if(RESpifullp->E()>1E-10 && RESnucleonfullp->E()>1E-10){
    const TLorentzVector ressum = (*RESpifullp) + (*RESnucleonfullp);
    RESmass = ressum.M();
    
    //double GetAdlerPhi(TLorentzVector nufull, TLorentzVector muonfull, TLorentzVector pifull, TLorentzVector nucleonfull, TLorentzVector iniNfull)
    adlerPhi = GetOneBoostAdlerPhi(dummyNu, *muonfullp, *RESpifullp, *RESnucleonfullp, *iniNfullp);

    /*
    //->test
    const double tbadler = GetTwoBoostAdlerPhi(dummyNu, *muonfullp, *RESpifullp, *RESnucleonfullp, *iniNfullp);
    if(fabs(adlerPhi-tbadler)>1e-10){
      printf("one-boost and two-boost not consistent!\n");
      exit(1);
    }
    exit(1);
    //<--
    */

    //by weighting the event with lrsign, the adlerPhi weight is not needed
    w2 = GetW2(adlerPhi, ares);
    lrsign *= w2;

    //============= repeat incorrect calculation in CLR paper first version =====>
    pseudoPhi = GetPseudoPhi(dummyNu, *muonfullp, *RESpifullp, *RESnucleonfullp);
    wpseudo2 = GetW2(pseudoPhi, ares);
    pseudosign *= wpseudo2;
  }

  cosNuIniNAngle = ((dummyNu.Vect()).Unit()).Dot((iniNfullp->Vect()).Unit());
  cosQIniNAngle = ((lvq.Vect()).Unit()).Dot((iniNfullp->Vect()).Unit());
#endif

#if __OPENNEUTRONFS__
  neutronFSmomentum = neutronFSfullp->P();
  neutronFStheta = neutronFSfullp->Theta()*TMath::RadToDeg();
#endif

#if __OPENDPTT__
  //add 20 MeV Cauchy smearing
  dpTT20s = dpTT+SmeardpTT(20);
  dpTT10s = dpTT+SmeardpTT(10);
  dpTT5s  = dpTT+SmeardpTT(5);
  dpTT2s  = dpTT+SmeardpTT(2);
#endif

#if __OPENMMECCQE__
  //muoncostheta = TMath::Cos( muonfullp->Theta()  );
  muonpt = muonfullp->Pt();
  mupz = muonfullp->Pz();
  q2qe = GetTrueCCQEQ2(muonmomentum, muonfullp->Theta());
#endif 


}


#endif
