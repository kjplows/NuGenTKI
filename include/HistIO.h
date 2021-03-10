#ifndef __HISTIO_H__
#define __HISTIO_H__

#include "TreeIO.h"

#define CC0piNpID 1
#define CC1piNpID 2
#define CCMpiNpID 4
#define CCEXCL3H1 5
#define CCEXCL3H4 6
#define LOWRECOIL 8
#define LOWRECOIL0piNp 9
#define NUBAR1PI 16
#define MMECCQE 32

using namespace std;

namespace HistIO
{
  //============================================ variables and histograms ===================================== 
  double perweight, enu;
  int targetZ, evtMode, npar;

  TH1D * henu  = 0x0;

#if __OPENCALC__ 
  double muonmomentum, muontheta;
  double Wtrue, Wrest, xBj, xrest, Q2;
  double protonmomentum, protontheta, pionmomentum, piontheta, pionEk, baryonmomentum, baryontheta, baryonmass;
  double dpt, dphit, dalphat,  neutronmomentum,  dpTT;
  double omegamup, modelf, Tmax, chi;
#endif
  TH1D * hmuonmomentum = 0x0, * hmuontheta = 0x0;
  TH1D * hWtrue = 0x0, * hWrest = 0x0, * hxBj = 0x0, * hxrest = 0x0, * hQ2 = 0x0;
  TH1D * hprotonmomentum = 0x0,* hprotontheta = 0x0, * hpionmomentum = 0x0, * hpiontheta = 0x0, * hpionEk =0x0, * hbaryonmomentum=0x0, * hbaryontheta=0x0, * hbaryonmass=0x0;
  TH1D * hdpt = 0x0, * hdphit = 0x0, * hdalphat = 0x0, * hneutronmomentum = 0x0, * hdpTT = 0x0;
  TH1D * homegamup = 0x0, * hpionTmax = 0x0, * hchi = 0x0;

  //correlation plots: muon proton and pion theta vs momentum
  //raw histos here
  TH2D * hmuonmomentumVStheta = 0x0;
  TH2D * hprotonmomentumVStheta = 0x0;
  TH2D * hpionmomentumVStheta = 0x0;
  TH2D * hpionEkVStheta = 0x0;
  // from here on 1st var Y axis 2nd var X axis
  TH2D * hpionTmaxVStheta = 0x0; //technically Tmax vs (1 - costheta)
  TH2D * hpionEkVSomegamup = 0x0;
  TH2D * homegamupVStheta = 0x0;
  TH2D * hchiVSdalphat = 0x0;
  //normalised histos here

  //correlation plots: muon proton and pion theta vs momentum
  //raw histos here
  TH2D * hmuonmomentumVStheta = 0x0;
  TH2D * hprotonmomentumVStheta = 0x0;
  TH2D * hpionmomentumVStheta = 0x0;
  //normalised histos here

#if __OPENCLR__
  double RESmass, adlerPhi, lrsign, w2;
  double pseudoPhi, pseudosign, wpseudo2;
  double CLR_KNsrc;
#endif
  TH1D * hRESmass = 0x0, * hadlerPhi = 0x0, * hlrsign = 0x0, * hw2 = 0x0;
  TH1D * hoobphi = 0x0;
  //TH1D * hpseudoPhi = 0x0, * hpseudosign = 0x0, * hwpseudo2 = 0x0;
  TH1D * hCLR_KNsrc = 0x0;

#if __OPENDPTT__ 
  double dpTT2s, dpTT5s,dpTT10s,dpTT20s;
#endif
  TH1D * hdpTT20s = 0x0, * hdpTT10s = 0x0, * hdpTT5s = 0x0, * hdpTT2s = 0x0;
  TH1D * hprotonTT = 0x0, * hpionTT = 0x0, * hdpTy = 0x0, * hlrdpt = 0x0, * hlrdpTT = 0x0, * hKNdpt = 0x0, * hsumdpt = 0x0;
  //* hpseudodpt = 0x0, 

#if __OPENMMECCQE__
#endif
  TH1D * hq3 = 0x0, * hq2qe = 0x0, * hmuonpt=0x0, * hmupz=0x0;
  TH2D * hq3VSEav = 0x0, * hq3VSneutronmomentum = 0x0, *hmuonptVSmupz=0x0, *hmupzVSmuonpt=0x0;
  TH3D * hErecoilTIMES1E3VSmupzVSmuonpt = 0x0;

//=============================================================================================================================
//                                                          Functions
//=============================================================================================================================

void SetTree(TTree * tree, const int anaid)
{
  tree->SetBranchAddress("perweight", &perweight); 
  tree->SetBranchAddress("targetZ", &targetZ);
  tree->SetBranchAddress("enu", &enu);    
  tree->SetBranchAddress("evtMode", &evtMode);
  tree->SetBranchAddress("npar", &npar);

#if __OPENCALC__ 
  tree->SetBranchAddress("muonmomentum", &muonmomentum);
  tree->SetBranchAddress("muontheta", &muontheta);
  
  tree->SetBranchAddress("Wtrue", &Wtrue);
  tree->SetBranchAddress("Wrest", &Wrest);
  tree->SetBranchAddress("xBj", &xBj);
  tree->SetBranchAddress("xrest", &xrest);
  tree->SetBranchAddress("Q2", &Q2);

  tree->SetBranchAddress("protonmomentum", &protonmomentum);
  tree->SetBranchAddress("protontheta", &protontheta);
  tree->SetBranchAddress("pionmomentum", &pionmomentum);
  tree->SetBranchAddress("piontheta", &piontheta);
  tree->SetBranchAddress("pionEk", &pionEk);
  tree->SetBranchAddress("baryonmomentum", &baryonmomentum);
  tree->SetBranchAddress("baryontheta", &baryontheta);
  tree->SetBranchAddress("baryonmass", &baryonmass);

  tree->SetBranchAddress("dpt", &dpt);
  tree->SetBranchAddress("dphit", &dphit);
  tree->SetBranchAddress("dalphat", &dalphat);
  tree->SetBranchAddress("neutronmomentum", &neutronmomentum);
  tree->SetBranchAddress("dpTT", &dpTT);

  tree->SetBranchAddress("omegamup",&omegamup);
  tree->SetBranchAddress("modelf",&modelf);
  tree->SetBranchAddress("chi",&chi);
#endif

#if __OPENCLR__   
  tree->SetBranchAddress("RESmass", &RESmass);
  tree->SetBranchAddress("adlerPhi", &adlerPhi);
  tree->SetBranchAddress("lrsign", &lrsign);
  tree->SetBranchAddress("w2", &w2);
  
  tree->SetBranchAddress("pseudoPhi", &pseudoPhi);
  tree->SetBranchAddress("pseudosign", &pseudosign);
  tree->SetBranchAddress("wpseudo2", &wpseudo2);

  tree->SetBranchAddress("CLR_KNsrc", &CLR_KNsrc);  
#endif
  
#if __OPENDPTT__  
  tree->SetBranchAddress("dpTT20s", &dpTT20s);
  tree->SetBranchAddress("dpTT10s", &dpTT10s);
  tree->SetBranchAddress("dpTT5s", &dpTT5s);
  tree->SetBranchAddress("dpTT2s", &dpTT2s);
#endif

}

void FillTopoTaskHist()
{

#if __OPENCALC__ 
  hmuonmomentum->Fill(muonmomentum,perweight);
  hmuontheta->Fill(muontheta,perweight);
  hmuonmomentumVStheta->Fill(muonmomentum,muontheta,perweight);

  hQ2->Fill(Q2,perweight);
  hxBj->Fill(xBj,perweight);
  hxrest->Fill(xrest,perweight);
  
  hprotonmomentum->Fill(protonmomentum,perweight);
  hprotontheta->Fill(protontheta,perweight);  
  hprotonmomentumVStheta->Fill(protonmomentum,protontheta,perweight);
  hpionmomentum->Fill(pionmomentum,perweight);
  hpiontheta->Fill(piontheta,perweight);
  hpionmomentumVStheta->Fill(pionmomentum,piontheta,perweight);
  hpionEk->Fill(pionEk,perweight);
  hpionEkVStheta->Fill(pionEk,piontheta,perweight);
  hbaryonmomentum->Fill(baryonmomentum,perweight);
  hbaryontheta->Fill(baryontheta,perweight);
  hbaryonmass->Fill(baryonmass,perweight);
  
  hdpt->Fill(dpt,perweight);
  hdphit->Fill(dphit,perweight);
  hdalphat->Fill(dalphat,perweight);
  hneutronmomentum->Fill(neutronmomentum,perweight);
  hdpTT->Fill(dpTT,perweight);

  Tmax = modelf / (1 - TMath::Cos(piontheta*TMath::DegToRad())) - 0.139; //charged pion mass
  homegamup->Fill(omegamup,perweight);
  hpionTmax->Fill(Tmax,perweight);
  hpionTmaxVStheta->Fill(piontheta,Tmax,perweight); 
  hchi->Fill(chi,perweight);

  hpionEkVSomegamup->Fill(omegamup,pionEk,perweight);
  homegamupVStheta->Fill(piontheta,omegamup,perweight);
  hchiVSdalphat->Fill(dalphat,chi,perweight);

#endif

#if __OPENCLR__
  if( fabs(lrsign)<1E-6 ){
    printf("\n\n\nstrange lrsign! %f\n\n\n", lrsign);exit(1);
  }

  hRESmass->Fill(RESmass,perweight);
  hadlerPhi->Fill(adlerPhi,w2*perweight);
  //hoobphi->Fill(adlerPhi, perweight);
  hlrsign->Fill(lrsign,perweight);
  hCLR_KNsrc->Fill(CLR_KNsrc,perweight);
  //hpseudoPhi->Fill(pseudoPhi, wpseudo2*perweight);
  //hpseudosign->Fill(pseudosign,perweight);
    
  //hlrdpt->Fill(dpt, lrsign * perweight);
  //hlrdpTT->Fill(dpTT, w2 * perweight);
  //hKNdpt->Fill(dpt, CLR_KNsrc * perweight);
  //hsumdpt->Fill(dpt, perweight);//sampe as dpt but with different binning
  //hpseudodpt->Fill(dpt, pseudosign * perweight);
#endif

#if __OPENDPTT__ 
  hdpTT20s->Fill(dpTT20s,perweight);
  hdpTT10s->Fill(dpTT10s,perweight);
  hdpTT5s->Fill(dpTT5s,perweight);
  hdpTT2s->Fill(dpTT2s,perweight);
#endif
  
}

void FillHist(const bool passwr, const bool isTopoTask)
{
#if __OPENCALC__
  //no cut on W for W
  hWtrue->Fill(Wtrue,perweight);
  hWrest->Fill(Wrest,perweight);
#endif
  
  if(passwr){
    henu->Fill(enu,perweight);

    //only fill if this is a topo task
    if(isTopoTask){        
      FillTopoTaskHist();
    }
  }
}

vector<TString> SetHist(const TString tag, const TString nuExp, const int anaid, TList * lout)
{
  //leave it like this

  vector<TString> hhs;

  hQ2  = new TH1D("Q2"+tag,"", 30, 0, 2); lout->Add(hQ2);
  hxBj = new TH1D("xBj"+tag,"", 30, 0, 2); lout->Add(hxBj);
  hxrest = new TH1D("xrest"+tag,"", 30, 0, 2); lout->Add(hxrest);
  hWtrue = new TH1D("Wtrue"+tag,"", 60, 0, 3); lout->Add(hWtrue);
  hWrest = new TH1D("Wrest"+tag,"", 60, 0, 3); lout->Add(hWrest);
  //henergyCCH  = new TH1D("energyCCH"+tag,"", 60, 0, 20); lout->Add(henergyCCH);
  //hxCCH = new TH1D("xCCH"+tag,"", 30, 0, 2); lout->Add(hxCCH);

  //at NUBAR1PI all these will have specific binning, therefore not needed here
  if(anaid!=NUBAR1PI){
    
    if(anaid==CCEXCL3H1||anaid==CCEXCL3H4){
      const double Cbin[]={0.025000, 0.028183, 0.031770, 0.035815, 0.040374, 0.045514, 0.051308, 0.057840, 0.065203, 0.073504, 0.082861, 0.093410, 0.105301, 0.118707, 0.133819, 0.150854, 0.170059, 0.191708, 0.216113, 0.243626, 0.274640, 0.309603, 0.349017, 0.393448, 0.443536, 0.500000, 0.563652, 0.635408, 0.716298, 0.807486, 0.910282, 1.026165, 1.156800, 1.304066, 1.470079, 1.657227, 1.868199, 2.106029, 2.374136, 2.676374, 3.017088, 3.401177, 3.834161, 4.322267, 4.872511, 5.492803, 6.192061, 6.980337, 7.868965, 8.870719, 10.000000};
      hmuonmomentum = new TH1D("muonmomentum"+tag,"", sizeof(Cbin)/sizeof(double)-1, Cbin); lout->Add(hmuonmomentum);
      hmuontheta = new TH1D("muontheta"+tag,"", 360, 0, 180); lout->Add(hmuontheta);
      hmuonmomentumVStheta = new TH2D("muonmomentumVStheta"+tag,"", sizeof(Cbin)/sizeof(double)-1, Cbin, 360, 0, 180); lout->Add(hmuonmomentumVStheta);
    }
    //no cuts mode is OFF for now
    else if(anaid==CC0piNpID || anaid==CC1piNpID || anaid==CCMpiNpID){
      //muon momentum cuts between 1.5 and 10 GeV
      const double Abin[]={0, 0.25, 0.5, 0.75, 1, 1.25, 1.500000, 2.250000, 2.500000, 2.750000, 3.000000, 3.250000, 3.500000, 3.750000, 4.000000, 4.250000, 4.500000, 4.750000, 5.000000, 5.250000, 5.500000, 5.750000, 6.000000, 6.250000, 6.500000, 6.750000, 7.000000, 7.250000, 7.500000, 7.750000, 8.000000, 8.250000, 8.500000, 8.750000, 9.000000, 9.250000, 9.500000, 9.750000, 10.000000}; 
      hmuonmomentum = new TH1D("muonmomentum"+tag,"", sizeof(Abin)/sizeof(double)-1, Abin); lout->Add(hmuonmomentum);

      // muon theta cuts to 25 degs (20 for 0pi and pi-plus)
      const double Bbin[]={0.000000, 0.5, 1., 1.5, 2.000000, 2.5, 3.000000, 3.5, 4.000000, 4.5, 5.000000, 5.5, 6.000000, 6.5, 7.000000, 7.5, 8.000000, 8.5, 9.000000, 9.5, 10.000000, 10.5, 11.000000, 11.5, 12.000000, 12.5, 13.000000, 13.5, 14.000000, 14.5, 15.000000, 15.5, 16.000000, 16.5, 17.000000, 17.5, 18.000000, 18.5, 19.000000, 19.5, 20.000000, 20.5, 21., 21.5, 22, 22.5, 23., 23.5, 24., 24.5, 25., 25.5, 26.};
    
      hmuontheta = new TH1D("muontheta"+tag,"", sizeof(Bbin)/sizeof(double)-1, Bbin); lout->Add(hmuontheta);

      hmuonmomentumVStheta = new TH2D("muonmomentumVStheta"+tag,"", sizeof(Abin)/sizeof(double)-1, Abin, sizeof(Bbin)/sizeof(double)-1, Bbin); lout->Add(hmuonmomentumVStheta);
    }
    
    else{
      const double Abin[]={0, 0.25, 0.5, 0.75, 1, 1.25, 1.500000, 2.250000, 2.500000, 2.750000, 3.000000, 3.250000, 3.500000, 3.750000, 4.000000, 4.250000, 4.500000, 4.750000, 5.000000, 5.250000, 5.500000, 5.750000, 6.000000, 6.250000, 6.500000, 6.750000, 7.000000, 7.250000, 7.500000, 7.750000, 8.000000, 8.250000, 8.500000, 8.750000, 9.000000, 9.250000, 9.500000, 9.750000, 10.000000}; 
      hmuonmomentum = new TH1D("muonmomentum"+tag,"", sizeof(Abin)/sizeof(double)-1, Abin); lout->Add(hmuonmomentum); 
      //hmuonmomentum = new TH1D("muonmomentum"+tag,"", 200, 0, 20.); lout->Add(hmuonmomentum);
      
      const double Bbin[]={0.000000, 2.000000, 3.000000, 4.000000, 5.000000, 6.000000, 7.000000, 8.000000, 9.000000, 10.000000, 11.000000, 12.000000, 13.000000, 14.000000, 15.000000, 16.000000, 17.000000, 18.000000, 19.000000, 20.000000, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 128, 130};
      hmuontheta = new TH1D("muontheta"+tag,"", sizeof(Bbin)/sizeof(double)-1, Bbin); lout->Add(hmuontheta);
      //hmuontheta = new TH1D("muontheta"+tag,"", 360, 0, 180); lout->Add(hmuontheta);

      hmuonmomentumVStheta = new TH2D("muonmomentumVStheta"+tag,"", sizeof(Abin)/sizeof(double)-1, Abin, sizeof(Bbin)/sizeof(double)-1, Bbin); lout->Add(hmuonmomentumVStheta);
    }
    henu  = new TH1D("enu"+tag,"", 60, 0, 20); lout->Add(henu);
    homegamup = new TH1D("omegamup"+tag,"", 180, 0, 90); lout->Add(homegamup);
    hchi = new TH1D("chi"+tag,"",360, 0, 180); lout->Add(hchi);
    //experimental binning here
    //hchi = new TH1D("chi"+tag,"",180, 0, 180); lout->Add(hchi);
  }
  
  hRESmass = new TH1D("RESmass"+tag,"", 60, 0, 3); lout->Add(hRESmass);
  hadlerPhi = new TH1D("adlerPhi"+tag,"", 60, 0, 360); lout->Add(hadlerPhi);
  hoobphi = new TH1D("oobphi"+tag,"", 60, 0, 360); lout->Add(hoobphi);
  hlrsign = new TH1D("lrsign"+tag,"", 3, -1.5, 1.5); lout->Add(hlrsign);
  hw2 = new TH1D("w2"+tag,"", 3, -1.5, 1.5); lout->Add(hw2); 
  hCLR_KNsrc = new TH1D("CLR_KNsrc"+tag,"", 3, -1.5, 1.5); lout->Add(hCLR_KNsrc);
  
  /*
    hpseudoPhi = new TH1D("pseudoPhi"+tag,"", 60, 0, 360); lout->Add(hpseudoPhi);
    hpseudosign = new TH1D("pseudosign"+tag,"", 3, -1.5, 1.5); lout->Add(hpseudosign);
    hwpseudo2 = new TH1D("wpseudo2"+tag,"", 3, -1.5, 1.5); lout->Add(hwpseudo2); 
  */

  if(anaid==CC0piNpID || anaid == CC1piNpID || anaid == CCMpiNpID || anaid == CCEXCL3H1 || anaid == CCEXCL3H4 ){
    if(anaid==CCEXCL3H1||anaid==CCEXCL3H4){
      const double Cbin[]={0.025000, 0.028183, 0.031770, 0.035815, 0.040374, 0.045514, 0.051308, 0.057840, 0.065203, 0.073504, 0.082861, 0.093410, 0.105301, 0.118707, 0.133819, 0.150854, 0.170059, 0.191708, 0.216113, 0.243626, 0.274640, 0.309603, 0.349017, 0.393448, 0.443536, 0.500000, 0.563652, 0.635408, 0.716298, 0.807486, 0.910282, 1.026165, 1.156800, 1.304066, 1.470079, 1.657227, 1.868199, 2.106029, 2.374136, 2.676374, 3.017088, 3.401177, 3.834161, 4.322267, 4.872511, 5.492803, 6.192061, 6.980337, 7.868965, 8.870719, 10.000000};
      hprotonmomentum = new TH1D("protonmomentum"+tag,"", sizeof(Cbin)/sizeof(double)-1, Cbin); lout->Add(hprotonmomentum);
    }
    else{
      //const double Cbin[]={0.3, 0.35, 0.4, 0.450000, 0.600000, 0.625000, 0.650000, 0.675000, 0.700000, 0.725000, 0.750000, 0.775000, 0.800000, 0.825000, 0.850000, 0.875000, 0.900000, 0.925000, 0.950000, 0.975000, 1.000000, 1.025000, 1.050000, 1.075000, 1.100000, 1.125000, 1.150000, 1.175000, 1.200000}; 
      //hprotonmomentum = new TH1D("protonmomentum"+tag,"", sizeof(Cbin)/sizeof(double)-1, Cbin); lout->Add(hprotonmomentum);
      hprotonmomentum = new TH1D("protonmomentum"+tag,"",60, 0, 3.);
    }

    if(anaid==CCEXCL3H1||anaid==CCEXCL3H4){
      const double Cbin[]={0.025000, 0.028183, 0.031770, 0.035815, 0.040374, 0.045514, 0.051308, 0.057840, 0.065203, 0.073504, 0.082861, 0.093410, 0.105301, 0.118707, 0.133819, 0.150854, 0.170059, 0.191708, 0.216113, 0.243626, 0.274640, 0.309603, 0.349017, 0.393448, 0.443536, 0.500000, 0.563652, 0.635408, 0.716298, 0.807486, 0.910282, 1.026165, 1.156800, 1.304066, 1.470079, 1.657227, 1.868199, 2.106029, 2.374136, 2.676374, 3.017088, 3.401177, 3.834161, 4.322267, 4.872511, 5.492803, 6.192061, 6.980337, 7.868965, 8.870719, 10.000000};

      hprotontheta = new TH1D("protontheta"+tag,"", 360, 0, 180); lout->Add(hprotontheta);
      hprotonmomentumVStheta = new TH2D("protonmomentumVStheta"+tag,"", sizeof(Cbin)/sizeof(double)-1, Cbin, 360, 0, 180); lout->Add(hprotonmomentumVStheta);
    }
    else{
      const double Dbin[]={0.000000, 7.500000, 10.000000, 12.500000, 15.000000, 17.500000, 20.000000, 22.500000, 25.000000, 27.500000, 30.000000, 32.500000, 35.000000, 37.500000, 40.000000, 42.500000, 45.000000, 47.500000, 50.000000, 52.500000, 55.000000, 57.500000, 60.000000, 62.500000, 65.000000, 67.500000, 70.000000}; 
      hprotontheta = new TH1D("protontheta"+tag,"", sizeof(Dbin)/sizeof(double)-1, Dbin); lout->Add(hprotontheta);
      hprotonmomentumVStheta = new TH2D("protonmomentumVStheta"+tag,"", 60, 0, 3., sizeof(Dbin)/sizeof(double)-1, Dbin); lout->Add(hprotonmomentumVStheta);
      //hprotontheta = new TH1D("protontheta"+tag,"", 360, 0, 180); lout->Add(hprotontheta);
    }

    if(anaid==CCEXCL3H1||anaid==CCEXCL3H4){
      const double Cbin[]={0.025000, 0.028183, 0.031770, 0.035815, 0.040374, 0.045514, 0.051308, 0.057840, 0.065203, 0.073504, 0.082861, 0.093410, 0.105301, 0.118707, 0.133819, 0.150854, 0.170059, 0.191708, 0.216113, 0.243626, 0.274640, 0.309603, 0.349017, 0.393448, 0.443536, 0.500000, 0.563652, 0.635408, 0.716298, 0.807486, 0.910282, 1.026165, 1.156800, 1.304066, 1.470079, 1.657227, 1.868199, 2.106029, 2.374136, 2.676374, 3.017088, 3.401177, 3.834161, 4.322267, 4.872511, 5.492803, 6.192061, 6.980337, 7.868965, 8.870719, 10.000000};
      hpionmomentum = new TH1D("pionmomentum"+tag,"", sizeof(Cbin)/sizeof(double)-1, Cbin); lout->Add(hpionmomentum);
    }
    else{
      //hpionmomentum = new TH1D("pionmomentum"+tag,"", 40, 0, 1); lout->Add(hpionmomentum);
      hpionmomentum = new TH1D("pionmomentum"+tag,"", 240, 0., 6.); lout->Add(hpionmomentum); //changed max momentum to 6 GeV/c.
      // good for pizero and 0pi, too broad for pi-plus (below)
      //hpionmomentum = new TH1D("pionmomentum"+tag,"", 40, 0.1, 0.55); lout->Add(hpionmomentum);
      //nocuts mode is ON so go with the 25 MeV/c bins!
    }

    //hpionEk = new TH1D("pionEk"+tag,"", 40, 0, 0.5); lout->Add(hpionEk); //binwidth = 12.5 MeV/bin
    //pion at 2 GeV/c has ~ 1.87 GeV KE ==> ~150 bins
    //hpionEk = new TH1D("pionEk"+tag,"",470,0,5.86); lout->Add(hpionEk);
    //focus on the problem region, 0 <= T <= 0.5 GeV. Binwidths are 0.005 GeV there. Then 220 bins of width 0.025 GeV.
    Double_t Tbin[321]; //Tbin[531];
    for(Int_t i = 0; i < 100; i++){Tbin[i] = 0.005*((Double_t)i);}
    for(Int_t i = 100; i < 321; i++){Tbin[i] = 0.5 + 0.025*(Double_t)(i-100);}
    hpionEk = new TH1D("pionEk"+tag,"",320,Tbin); lout->Add(hpionEk);

    //pi-plus below, cut 75 MeV <= Ek <= 400 MeV //NOT YET JOHN
    //hpionEk = new TH1D("pionEk"+tag,"", 40, 0.075, 0.4); lout->Add(hpionEk);

    if(anaid==CCEXCL3H1||anaid==CCEXCL3H4){
      const double Cbin[]={0.025000, 0.028183, 0.031770, 0.035815, 0.040374, 0.045514, 0.051308, 0.057840, 0.065203, 0.073504, 0.082861, 0.093410, 0.105301, 0.118707, 0.133819, 0.150854, 0.170059, 0.191708, 0.216113, 0.243626, 0.274640, 0.309603, 0.349017, 0.393448, 0.443536, 0.500000, 0.563652, 0.635408, 0.716298, 0.807486, 0.910282, 1.026165, 1.156800, 1.304066, 1.470079, 1.657227, 1.868199, 2.106029, 2.374136, 2.676374, 3.017088, 3.401177, 3.834161, 4.322267, 4.872511, 5.492803, 6.192061, 6.980337, 7.868965, 8.870719, 10.000000};

      hpiontheta = new TH1D("piontheta"+tag,"", 360, 0, 180); lout->Add(hpiontheta);
      hpionmomentumVStheta = new TH2D("pionmomentumVStheta"+tag,"", sizeof(Cbin)/sizeof(double)-1, Cbin, 360, 0, 180); lout->Add(hpionmomentumVStheta);
      hpionEkVStheta = new TH2D("pionEkVStheta"+tag,"",sizeof(Cbin)/sizeof(double)-1, Cbin, 360, 0, 180); lout->Add(hpionEkVStheta);
      hpionEkVSomegamup = new TH2D("pionEkVSomegamup"+tag,"",180,0,90,sizeof(Cbin)/sizeof(double)-1,Cbin); lout->Add(hpionEkVSomegamup);
      homegamupVStheta = new TH2D("omegamupVStheta"+tag,"",360,0,180,180,0,90); lout->Add(homegamupVStheta);
      hpionTmax = new TH1D("pionTmax"+tag,"",sizeof(Cbin)/sizeof(double)-1, Cbin); lout->Add(hpionTmax);
      hpionTmaxVStheta = new TH2D("pionTmaxVStheta"+tag,"",sizeof(Cbin)/sizeof(double)-1, Cbin, 360, 0, 180); lout->Add(hpionTmaxVStheta);
    }
    else{
      //hpiontheta = new TH1D("piontheta"+tag,"", 35, 0, 70); lout->Add(hpiontheta);
      //focus on C/6H and get dip plots0.5 deg binwidths
      //hpiontheta = new TH1D("piontheta"+tag,"",36,0,180); lout->Add(hpiontheta);
      hpiontheta = new TH1D("piontheta"+tag,"",360,0,180); lout->Add(hpiontheta);

      hpionmomentumVStheta = new TH2D("pionmomentumVStheta"+tag,"", 240, 0, 6., 36, 0, 180); lout->Add(hpionmomentumVStheta);
      
      Double_t Tbin[321]; //Tbin[531];
      for(Int_t i = 0; i < 100; i++){Tbin[i] = 0.005*((Double_t)i);}
      for(Int_t i = 100; i < 321; i++){Tbin[i] = 0.5 + 0.025*((Double_t)(i-100));}
      //hpionEkVStheta = new TH2D("pionEkVStheta"+tag,"", 240, 0, 6., 36, 0, 180); lout->Add(hpionEkVStheta);
      hpionEkVStheta = new TH2D("pionEkVStheta"+tag,"", 320, Tbin, 360, 0, 180); lout->Add(hpionEkVStheta);
      hpionEkVSomegamup = new TH2D("pionEkVSomegamup"+tag,"",180,0,90,320,Tbin); lout->Add(hpionEkVSomegamup);
      homegamupVStheta = new TH2D("omegamupVStheta"+tag,"",360,0,180,180,0,90); lout->Add(homegamupVStheta);
      hpionTmax = new TH1D("pionTmax"+tag,"", 320, Tbin); lout->Add(hpionTmax);
      hpionTmaxVStheta = new TH2D("pionTmaxVStheta"+tag,"", 360, 0, 180, 320, Tbin); lout->Add(hpionTmaxVStheta);
    }
    
    hbaryonmomentum = new TH1D("baryonmomentum"+tag,"", 30, 0.2, 6); lout->Add(hbaryonmomentum);
    hbaryontheta = new TH1D("baryontheta"+tag,"", 35, 0, 70); lout->Add(hbaryontheta);
    //hbaryontheta  =new TH1D("baryontheta"+tag,"", 360, 0, 180); lout->Add(hbaryontheta);
    hbaryonmass = new TH1D("baryonmass"+tag,"", 60, 0, 3); lout->Add(hbaryonmass);

    if(nuExp=="MINERvA" || nuExp=="NONE" || nuExp=="DUNE"){
      if(anaid==CCEXCL3H1 || anaid==CCEXCL3H4){
        hdpTT = new TH1D("dpTT"+tag,"", 400, -0.4, 0.4);
        hdpTT20s = new TH1D("dpTT20s"+tag,"", 400, -0.4, 0.4);
        hdpTT10s = new TH1D("dpTT10s"+tag,"", 800, -0.4, 0.4);
        hdpTT5s = new TH1D("dpTT5s"+tag,"", 1600, -0.4, 0.4);
        hdpTT2s = new TH1D("dpTT2s"+tag,"", 4000, -0.4, 0.4);
      }
      else{
        const double Jbin[]={-2, -0.800000, -0.700000, -0.650000, -0.600000, -0.550000, -0.500000, -0.450000, -0.4,-0.274,-0.189,-0.147,-0.105,-0.063,-0.021,0.021,0.063,0.105,0.147,0.189,0.274,0.4, 0.450000, 0.500000, 0.550000, 0.600000, 0.650000, 0.700000, 0.800000, 2};
        hdpTT = new TH1D("dpTT"+tag,"", sizeof(Jbin)/sizeof(double)-1, Jbin);
        
        if(anaid==CC0piNpID){
          const double Ebin0p[]= {0.000000, 20.000000, 40.000000, 60.000000, 80.000000, 100.000000, 120.000000, 130.000000, 140.000000, 150.000000, 160.000000, 170.000000, 180.000000};
          hdalphat = new TH1D("dalphat"+tag,"", sizeof(Ebin0p)/sizeof(double)-1, Ebin0p); 
        }
	/* else if(anaid==CC1piNpID) || anaid == CCMpiNpID){
          const double Ebin1p[]= {0.0000,20.0000,40.0000,60.0000,80.0000,100.0000,120.0000,140.0000,160.0000,180.0000};//pi0TKI binning
          hdalphat = new TH1D("dalphat"+tag,"", sizeof(Ebin1p)/sizeof(double)-1, Ebin1p); 
	  } */ //rebinning dalphat for now
	else if(anaid==CC1piNpID || anaid==CCMpiNpID){
	  hdalphat = new TH1D("dalphat"+tag,"", 36, 0., 180.);
	  hchiVSdalphat = new TH2D("chiVSdalphat"+tag,"", 36, 0., 180., 36, 0., 180.); lout->Add(hchiVSdalphat);
	}
        
        const double Fbin[]={0.000000, 2.500000, 5.000000, 7.500000, 10.000000, 12.500000, 15.000000, 17.500000, 20.000000, 22.500000, 25.000000, 27.500000, 30.000000, 35.000000, 40.000000, 45.000000, 50.000000, 55.000000, 60.000000, 70.000000, 85.000000, 105.000000, 130.000000, 180.000000};
        hdphit = new TH1D("dphit"+tag,"", sizeof(Fbin)/sizeof(double)-1, Fbin);
        
        const double Gbin[]={0.000000, 0.025000, 0.050000, 0.075000, 0.100000, 0.125000, 0.150000, 0.175000, 0.200000, 0.225000, 0.250000, 0.275000, 0.300000, 0.350000, 0.400000, 0.450000, 0.500000, 0.550000, 0.600000, 0.650000, 0.700000, 0.800000, 1.000000, 1.200000, 2.000000};
        hdpt = new TH1D("dpt"+tag,"", sizeof(Gbin)/sizeof(double)-1, Gbin);
        
        if(anaid==CC0piNpID){
          const double Hbin0p[]={0.000000, 0.025000, 0.050000, 0.075000, 0.100000, 0.125000, 0.150000, 0.175000, 0.200000, 0.225000, 0.250000, 0.275000, 0.300000, 0.350000, 0.400000, 0.450000, 0.500000, 0.550000, 0.600000, 0.650000, 0.700000, 0.800000, 1.000000, 1.200000, 2.000000};
          hneutronmomentum = new TH1D("neutronmomentum"+tag,"", sizeof(Hbin0p)/sizeof(double)-1, Hbin0p); lout->Add(hneutronmomentum);
        }
        else if(anaid==CC1piNpID || anaid == CCMpiNpID){
          //const double Hbin1p[]={0,0.055,0.11,0.165,0.22,0.275,0.33,0.385,0.44,0.495,0.56,0.655,0.81};
          //hneutronmomentum = new TH1D("neutronmomentum"+tag,"", sizeof(Hbin1p)/sizeof(double)-1, Hbin1p); lout->Add(hneutronmomentum);
	  hneutronmomentum = new TH1D("neutronmomentum"+tag,"", 100, 0, 1.); lout->Add(hneutronmomentum);
        }
        
        hprotonTT = new TH1D("protonTT"+tag,"", sizeof(Jbin)/sizeof(double)-1, Jbin);
        hpionTT = new TH1D("pionTT"+tag,"", sizeof(Jbin)/sizeof(double)-1, Jbin);
        
        const double Kbin[]={-2.000000, -1.200000, -1.000000, -0.800000, -0.700000, -0.650000, -0.600000, -0.550000, -0.500000, -0.450000, -0.400000, -0.350000, -0.300000, -0.250000, -0.200000, -0.150000, -0.100000, -0.050000, 0.000000, 0.050000, 0.100000, 0.150000, 0.200000, 0.250000, 0.300000, 0.350000, 0.400000, 0.450000, 0.500000, 0.550000, 0.600000, 0.650000, 0.700000, 2,};
        hdpTy = new TH1D("dpTy"+tag,"", sizeof(Kbin)/sizeof(double)-1, Kbin);
      }
    }
    else if(nuExp=="T2K"){
      if(anaid==CC0piNpID){//defined by T2K analysis
        const double Ebin[] = {0.00000, 26.929016, 58.441695, 88.235500, 113.445643, 134.072124, 151.260858, 165.584803, 180.000};
        hdalphat = new TH1D("dalphat"+tag,"", sizeof(Ebin)/sizeof(double)-1, Ebin);
	hchiVSdalphat = new TH2D("chiVSdalphat"+tag,"", sizeof(Ebin)/sizeof(double) -1, Ebin, sizeof(Ebin)/sizeof(double) -1, Ebin); lout->Add(hchiVSdalphat);
      }
      else{
        const double Ebin[]= {0.000000, 20.000000, 40.000000, 60.000000, 80.000000, 100.000000, 120.000000, 130.000000, 140.000000, 150.000000, 160.000000, 170.000000, 180.000000};
        hdalphat = new TH1D("dalphat"+tag,"", sizeof(Ebin)/sizeof(double)-1, Ebin);
	hchiVSdalphat = new TH2D("chiVSdalphat"+tag,"", sizeof(Ebin)/sizeof(double) -1, Ebin, sizeof(Ebin)/sizeof(double) -1, Ebin); lout->Add(hchiVSdalphat);
      }
      
      const double Fbin[]={0.00000, 3.838817, 8.021409, 12.891550, 19.480565, 29.793805, 48.701413, 85.943669, 180.00};
      hdphit = new TH1D("dphit"+tag,"", sizeof(Fbin)/sizeof(double)-1, Fbin);
      
      const double Gbin[]={0.000000, 0.080000, 0.120000, 0.155000, 0.200000, 0.260000, 0.360000, 0.510000, 1.10000};
      hdpt = new TH1D("dpt"+tag,"", sizeof(Gbin)/sizeof(double)-1, Gbin);
      
      const double Hbin[]={0.000000, 0.030000, 0.060000, 0.090000, 0.120000, 0.150000, 0.180000, 0.210000, 0.240000, 0.270000, 0.300000, 0.350000, 0.400000, 0.450000, 0.500000, 0.550000, 0.600000, 0.650000, 0.700000, 0.800000, 1.000000, 1.200000, 1.5, 2.000000};
      hneutronmomentum = new TH1D("neutronmomentum"+tag,"", sizeof(Hbin)/sizeof(double)-1, Hbin); lout->Add(hneutronmomentum);
      
      const double Jbin[]={-2, -0.800000, -0.700000, -0.650000, -0.600000, -0.550000, -0.500000, -0.450000, -0.400000, -0.350000, -0.300000, -0.250000, -0.200000, -0.150000, -0.100000, -0.050000, 0.000000, 0.050000, 0.100000, 0.150000, 0.200000, 0.250000, 0.300000, 0.350000, 0.400000, 0.450000, 0.500000, 0.550000, 0.600000, 0.650000, 0.700000, 0.800000, 2};
      hdpTT = new TH1D("dpTT"+tag,"", sizeof(Jbin)/sizeof(double)-1, Jbin);
      hprotonTT = new TH1D("protonTT"+tag,"", sizeof(Jbin)/sizeof(double)-1, Jbin);
      hpionTT = new TH1D("pionTT"+tag,"", sizeof(Jbin)/sizeof(double)-1, Jbin);
      
      const double Kbin[]={-2.000000, -1.200000, -1.000000, -0.800000, -0.700000, -0.650000, -0.600000, -0.550000, -0.500000, -0.450000, -0.400000, -0.350000, -0.300000, -0.250000, -0.200000, -0.150000, -0.100000, -0.050000, 0.000000, 0.050000, 0.100000, 0.150000, 0.200000, 0.250000, 0.300000, 0.350000, 0.400000, 0.450000, 0.500000, 0.550000, 0.600000, 0.650000, 0.700000, 2,};
      hdpTy = new TH1D("dpTy"+tag,"", sizeof(Kbin)/sizeof(double)-1, Kbin);
    }
    
    hlrdpt = new TH1D("lrdpt"+tag,"", 20, 0, 2);
    hlrdpTT = new TH1D("lrdpTT"+tag,"", 40, -2, 2);
    hKNdpt = new TH1D("KNdpt"+tag,"", 20, 0, 2);
    hsumdpt = new TH1D("sumdpt"+tag,"", 20, 0, 2);
    //hpseudodpt = new TH1D("pseudodpt"+tag,"", 20, 0, 2);
    

    TH1D * hstmp[]={hdalphat, hdphit, hdpt, hprotonTT, hpionTT, hdpTT, hdpTT20s, hdpTT10s, hdpTT5s, hdpTT2s, hdpTy, hlrdpt, hlrdpTT, hKNdpt, hsumdpt};
    //hpseudodpt, 
    for(int itmp=0; itmp<(int) (sizeof(hstmp)/sizeof(TH1D*)); itmp++){
      if(hstmp[itmp]) lout->Add(hstmp[itmp]);
    }
  }
  else if(anaid==LOWRECOIL || anaid==LOWRECOIL0piNp){
    double bq3[]={0, 0.2 ,  0.3 ,  0.4 ,  0.5 ,  0.6 ,  0.8 };
    hq3=new TH1D("q3"+tag,"", sizeof(bq3)/sizeof(double)-1, bq3); lout->Add(hq3); hhs.push_back("q3");
    
    const double bEav[]={0, 0.0166667, 0.0333333, 0.05, 0.0666667, 0.0833333, 0.1, 0.116667, 0.133333, 0.15, 0.166667, 0.183333, 0.2, 0.216667, 0.233333, 0.25, 0.266667, 0.283333, 0.3, 0.316667, 0.333333, 0.35, 0.366667, 0.383333, 0.4, 0.416667, 0.433333, 0.45, 0.466667, 0.483333, 0.5};
    hq3VSEav = new TH2D("q3VSEav"+tag,"", sizeof(bEav)/sizeof(double)-1, bEav, sizeof(bq3)/sizeof(double)-1, bq3); lout->Add(hq3VSEav); hhs.push_back("q3VSEav");
    
    if(anaid==LOWRECOIL0piNp){
      const double bneutronmomentum[]={0, 0.0333333, 0.0666667, 0.1, 0.133333, 0.166667, 0.2, 0.233333, 0.266667, 0.3, 0.333333, 0.366667, 0.4, 0.433333, 0.466667, 0.5, 0.533333, 0.566667, 0.6, 0.633333, 0.666667, 0.7, 0.733333, 0.766667, 0.8, 0.833333, 0.866667, 0.9, 0.933333, 0.966667, 1, 1.03333, 1.06667, 1.1, 1.13333, 1.16667, 1.2, 1.23333, 1.26667, 1.3, 1.33333, 1.36667, 1.4, 1.43333, 1.46667, 1.5, 1.53333, 1.56667, 1.6, 1.63333, 1.66667, 1.7, 1.73333, 1.76667, 1.8, 1.83333, 1.86667, 1.9, 1.93333, 1.96667, 2};
      hq3VSneutronmomentum = new TH2D("q3VSneutronmomentum"+tag,"", sizeof(bneutronmomentum)/sizeof(double)-1, bneutronmomentum, sizeof(bq3)/sizeof(double)-1, bq3);lout->Add(hq3VSneutronmomentum); hhs.push_back("q3VSneutronmomentum");
    }
  }
  else if(anaid==MMECCQE){
    const double q2qebins[]={0 , 0.00625 , 0.0125 , 0.025 , 0.0375 , 0.05 , 0.1 , 0.15 , 0.2 , 0.3 , 0.4 , 0.6 , 0.8 , 1.0 , 1.2 , 2.0 , 4.0 , 6.0 , 8.0 , 10.0};
    hq2qe = new TH1D("q2qe"+tag,"", sizeof(q2qebins)/sizeof(double)-1, q2qebins); lout->Add(hq2qe); hhs.push_back("q2qe");
    
    double muonptbins[]={0 , 0.07 , 0.15 , 0.25 , 0.33 , 0.4 , 0.47 , 0.55 ,0.7 , 0.85 , 1.00 , 1.25 , 1.5 , 2.5};
    hmuonpt = new TH1D("muonpt"+tag,"", sizeof(muonptbins)/sizeof(double)-1, muonptbins); lout->Add(hmuonpt); hhs.push_back("muonpt");
    
    double mupzbins[]={1.5 , 2.0 , 2.5 , 3.0 , 3.5 , 4.0 , 4.5 , 5.0 , 5.5 , 6.0 , 7.0 , 8.0 , 9.0 , 10.0 , 15.0 , 20.0};
    hmupz = new TH1D("mupz"+tag,"", sizeof(mupzbins)/sizeof(double)-1, mupzbins); lout->Add(hmupz); hhs.push_back("mupz");
    
    hmuonptVSmupz = new TH2D("muonptVSmupz"+tag,"", sizeof(mupzbins)/sizeof(double)-1, mupzbins, sizeof(muonptbins)/sizeof(double)-1, muonptbins); lout->Add(hmuonptVSmupz); hhs.push_back("muonptVSmupz");
    hmupzVSmuonpt = new TH2D("mupzVSmuonpt"+tag,"", sizeof(muonptbins)/sizeof(double)-1, muonptbins, sizeof(mupzbins)/sizeof(double)-1, mupzbins); lout->Add(hmupzVSmuonpt); hhs.push_back("mupzVSmuonpt");
    
    /*
      pt00.150.250.40.712.5
      pz1.53.5820
      recoil040801201602002402803203604006008001000
    */
    const double muonpt3dbins[]={0, 0.15, 0.25, 0.4, 0.7, 1, 2.5};
    const double mupz3dbins[]={1.5, 3.5, 8, 20};
    const double Erecoil3dbins[]={0, 40, 80, 120, 160, 200, 240, 280, 320, 360, 400, 600, 800, 1000};
    hErecoilTIMES1E3VSmupzVSmuonpt = new TH3D("ErecoilTIMES1E3VSmupzVSmuonpt"+tag, "", sizeof(muonpt3dbins)/sizeof(double)-1, muonpt3dbins, sizeof(mupz3dbins)/sizeof(double)-1, mupz3dbins, sizeof(Erecoil3dbins)/sizeof(double)-1, Erecoil3dbins); lout->Add(hErecoilTIMES1E3VSmupzVSmuonpt);; hhs.push_back("ErecoilTIMES1E3VSmupzVSmuonpt");
  }
  else if(anaid==NUBAR1PI){
    const double enubins[]={0, 1.5, 2.0,3.0,3.50,4.0,5.0,6.0,8.0,10.0, 12.0};
    henu = new TH1D("enu"+tag,"", 10, enubins); lout->Add(henu); hhs.push_back("enu");
    
    hmuonmomentum = new TH1D("muonmomentum"+tag,"", 30, 0, 10); lout->Add(hmuonmomentum); hhs.push_back("muonmomentum");
    hmuontheta = new TH1D("muontheta"+tag,"", 25, 0, 25); lout->Add(hmuontheta); hhs.push_back("muontheta");
    hmuonmomentumVStheta = new TH2D("muonmomentumVStheta"+tag,"", 30, 0, 10, 25, 0, 25); lout->Add(hmuonmomentumVStheta); hhs.push_back("muonmomentumVStheta");
    
    hpionmomentum = new TH1D("pionmomentum"+tag,"", 40, 0, 1); lout->Add(hpionmomentum); hhs.push_back("pionmomentum");
    hpionEk = new TH1D("pionEk"+tag,"", 40, 0, 0.5); lout->Add(hpionEk); hhs.push_back("pionEk");
    hpiontheta = new TH1D("piontheta"+tag,"", 35, 0, 180); lout->Add(hpiontheta); hhs.push_back("piontheta");
    hpionmomentumVStheta = new TH2D("pionmomentumVStheta"+tag,"", 40, 0, 1, 35, 0, 180); lout->Add(hpionmomentumVStheta); hhs.push_back("pionmomentumVStheta");
    hpionEkVStheta = new TH2D("pionEkVStheta"+tag,"",40,0,0.87,35,0,180); lout->Add(hpionEkVStheta); hhs.push_back("pionEkVStheta");
    hpionEkVSomegamup = new TH2D("pionEkVSomegamup"+tag,"",35,0,90,40,0,0.87); lout->Add(hpionEkVSomegamup); hhs.push_back("pionEkVSomegamup");
    homegamupVStheta = new TH2D("omegamupVStheta"+tag,"",360,0,180,180,0,90); lout->Add(homegamupVStheta);
  }
  else{
    printf("\n\nunknown anaid!! %d\n\n", anaid); exit(1);
  }

  return hhs;
}

//end of namespace
}

#endif
