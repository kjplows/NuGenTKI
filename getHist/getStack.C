void getStack2(const TString fin, const TString anaid, const TString tag, const TString var)
{
  const TString dir= ("outStack/"+anaid);
  gSystem->Exec("mkdir -p "+dir);

  cout<<" fin "<<fin<<" anaid "<<anaid<<" tag "<<tag<<" var "<<var<<endl;
  TFile::Open(fin);

  TList *lout=new TList;

  if(var.Contains("VS")){
    TH2D * hall=(TH2D*) gDirectory->Get(var+"_all"); 
    TH2D * hqe=(TH2D*) gDirectory->Get(var+"_qe"); 
    TH2D * hres=(TH2D*) gDirectory->Get(var+"_res");
    TH2D * hdis=(TH2D*) gDirectory->Get(var+"_dis");
    TH2D * h2p2h=(TH2D*) gDirectory->Get(var+"_2p2h");
    TH2D * hother=(TH2D*) gDirectory->Get(var+"_other");

    TH2D *hh[]={hall, hqe, hres, hdis, h2p2h}; 
    const int nh=5;
    for(int ii=0; ii<nh; ii++){
      hh[ii]->Scale(1./13.); printf("Scaling to per nucleon in CH,  C and H should have been full nucleus and combined !!\n");
      lout->Add(hh[ii]);
    }
    if(var.Contains("proton")){hall->SetTitle("Proton theta vs momentum");}
    else if(var.Contains("muon")){hall->SetTitle("Muon theta vs momentum");;}
    else{hall->SetTitle("Pion theta vs momentum");}
    //hall->SetTitle(strin+"theta vs momentum");
    hall->SetName("hcorr");
    hall->SetXTitle("p (GeV/c)");
    hall->SetYTitle("#theta");
    hall->SetZTitle("#frac{d#sigma}{dpd#theta}");
    TCanvas *cc=new TCanvas;
    hall->Draw("COLZ");
    gPad->Update();
    TPaveStats *st = (TPaveStats*) hall->FindObject("stats");
    st->SetX1NDC(0.5); st->SetX2NDC(0.8);
    cc->Print(Form("outStack/%s/%s_%s.eps", anaid.Data(), var.Data(), tag.Data()));
    cc->Print(Form("outStack/%s/%s_%s.png", anaid.Data(), var.Data(), tag.Data()));
    cc->Clear(); 
    hall->ProfileX()->SetYTitle("#bar{#theta}");
    hall->ProfileX()->Draw();
    gPad->Update();
    cc->Print(Form("outStack/%s/%s_%s_momProf.eps", anaid.Data(), var.Data(), tag.Data()));
    cc->Print(Form("outStack/%s/%s_%s_momProf.png", anaid.Data(), var.Data(), tag.Data()));
    cc->Clear();
    hall->ProfileY()->SetYTitle("#bar{p}");
    hall->ProfileY()->Draw();
    gPad->Update();
    cc->Print(Form("outStack/%s/%s_%s_thetaProf.eps", anaid.Data(), var.Data(), tag.Data()));
    cc->Print(Form("outStack/%s/%s_%s_thetaProf.png", anaid.Data(), var.Data(), tag.Data()));
    cc->Clear();
    hall->ProjectionX()->SetYTitle("Integrated xsec per #theta bin");
    hall->ProjectionX()->Draw();
    gPad->Update();
    cc->Print(Form("outStack/%s/%s_%s_momProj.eps", anaid.Data(), var.Data(), tag.Data()));
    cc->Print(Form("outStack/%s/%s_%s_momProj.png", anaid.Data(), var.Data(), tag.Data()));
    cc->Clear();
    hall->ProjectionY()->SetYTitle("Integrated xsec per p bin");
    hall->ProjectionY()->Draw();
    gPad->Update();
    cc->Print(Form("outStack/%s/%s_%s_thetaProj.eps", anaid.Data(), var.Data(), tag.Data()));
    cc->Print(Form("outStack/%s/%s_%s_thetaProj.png", anaid.Data(), var.Data(), tag.Data()));
    cc->Clear();

    // now to do the normalisation:
    // First get for each X-bin (Y-bin) the TH1D behind //do that with ProjectionX(firstbin = lowedge, lastbin = highedge)
    // Then SetMaximum of that TH1D to 1 //note Scale() works the way I wanted SetMaximum to.
    // create new TH2D with that normalisation
    // ==> 2 new TH2Ds for each TH1D
    
    const Int_t XBINLOW = 1; const Int_t YBINLOW = 1;
    Int_t XBINHIGH = 1; Int_t YBINHIGH = 1;
    Double_t maxp = 0.; Double_t maxtheta = 0.;
 
    //get number of bins
    if(var.Contains("proton"))
    {
      //continue;
    }
    else if(var.Contains("muon")){
      XBINHIGH = ((TH1D*)gDirectory->Get("muonmomentum_all"))->GetNbinsX();
      maxp = ((TH1D*)gDirectory->Get("muonmomentum_all"))->GetXaxis()->GetBinLowEdge(XBINHIGH) + ((TH1D*)gDirectory->Get("muonmomentum_all"))->GetXaxis()->GetBinWidth(XBINHIGH);
      YBINHIGH = ((TH1D*)gDirectory->Get("muontheta_all"))->GetNbinsX();
      maxtheta = ((TH1D*)gDirectory->Get("muontheta_all"))->GetXaxis()->GetBinLowEdge(YBINHIGH) + ((TH1D*)gDirectory->Get("muontheta_all"))->GetXaxis()->GetBinWidth(YBINHIGH);
    }
    else{
      XBINHIGH = ((TH1D*)gDirectory->Get("pionmomentum_all"))->GetNbinsX();
      maxp = ((TH1D*)gDirectory->Get("pionmomentum_all"))->GetXaxis()->GetBinLowEdge(XBINHIGH) + ((TH1D*)gDirectory->Get("pionmomentum_all"))->GetXaxis()->GetBinWidth(XBINHIGH);
      YBINHIGH = ((TH1D*)gDirectory->Get("piontheta_all"))->GetNbinsX();
      maxtheta = ((TH1D*)gDirectory->Get("piontheta_all"))->GetXaxis()->GetBinLowEdge(YBINHIGH) + ((TH1D*)gDirectory->Get("piontheta_all"))->GetXaxis()->GetBinWidth(YBINHIGH);
    }
    
    //declare TH2D * to be filled
    TH2D * hallxnorm = new TH2D("hallxnorm","hallxnorm",XBINHIGH,0.,maxp,YBINHIGH,0.,maxtheta);
    TH2D * hallynorm = new TH2D("hallynorm","hallynorm",XBINHIGH,0.,maxp,YBINHIGH,0.,maxtheta);
    TH2D * hallxmaxima = new TH2D("hallxmaxima","hallxmaxima",XBINHIGH,0.,maxp,YBINHIGH,0.,maxtheta);
    TH2D * hallymaxima = new TH2D("hallymaxima","hallymaxima",XBINHIGH,0.,maxp,YBINHIGH,0.,maxtheta);

    /*strategy for the contour normalisation: 
      first, get the p-slice as for hallxnorm and scale
      repeat that for all theta-bins, and DO NOT GIVE A BLIN about the theta pdf.
      (it's just where the maxima are we're interested in)
      after that, put each slice back.
      Repeat, but do it for theta maxima.
      That is all. Breckenridge.
     */

    TH1D* htemp = 0x0;
    //X(p)-normalisation
    //loop over Y-bins
    for(Int_t i = YBINLOW; i < YBINHIGH; i++){
      //project the slice and set maximum
      htemp = hall->ProjectionX("htemp", i, i+i);
      Double_t maxval = htemp->GetMaximum();
      long double scalefactor = 1/maxval;
      htemp->Scale(scalefactor);
      //cout << htemp->GetMean() << endl;
      Int_t tbin = 0;
      bool guardX = true;
      for(Int_t j = XBINLOW; j < XBINHIGH; j++){
	tbin = hallxnorm->GetBin(j,i);
	double yrod = htemp->GetBinContent(j);
	if(yrod > 0.1){guardX = false;}
	double blyat = htemp->GetBinContent(j) * hall->GetBinContent(j,i);
	hallxmaxima->SetBinContent(tbin,yrod);
	hallxnorm->SetBinContent(tbin,blyat); //this must ABSOLUTELY be SetBinContent(); AddBinContent and Fill both fail.
	hallxnorm->GetXaxis()->SetRangeUser(0.,2.);
	gStyle->SetOptStat(111111);
      }
      if(guardX){
	for(Int_t j = XBINLOW; j < XBINHIGH; j++)
	  {
	    tbin = hall->GetBin(j,i);
	    hallxmaxima->SetBinContent(tbin,0);
	    hallxnorm->SetBinContent(tbin,0);
	  }
      }
    }
    //scan X-bins of ready histo for abnormalities
    for(Int_t i = XBINLOW; i < XBINHIGH; i++){
      bool guardY = true;
      for(Int_t j = YBINLOW; j < YBINHIGH; j++){
	htemp = hall->ProjectionY("htemp",i,i+1);
	Double_t maxval = htemp->GetMaximum();
	htemp->Scale(1/maxval);
	if(htemp->GetMaximum() > 0.1){guardY=false;}
      }
      if(guardY){
	Int_t tbin = 0;
	for(Int_t j = YBINLOW; j < YBINHIGH; j++){
	  tbin = hallxnorm->GetBin(i,j);
	  hallxmaxima->SetBinContent(tbin,0.);
	  hallxnorm->SetBinContent(tbin,0.);
	}
      }
    }

    //Y(theta)-normalisation
    for(Int_t i = XBINLOW; i < XBINHIGH; i++){
      htemp = hall->ProjectionY("htemp", i, i+1);
      Double_t maxval = htemp->GetMaximum();
      long double scalefactor = 1/maxval;
      htemp->Scale(scalefactor);
      Int_t tbin = 0;
      //guard against dead X-bins, which have no max because they are dead
      bool guardY = true;
      for(Int_t j = YBINLOW; j < YBINHIGH; j++){
	tbin = hallynorm->GetBin(i,j);
	double yrod = htemp->GetBinContent(j);
	//deactivate guard on seeing something like a max
	if(yrod > 0.1){guardY = false;}
	double blyat = htemp->GetBinContent(j) * hall->GetBinContent(i,j);
	hallymaxima->SetBinContent(tbin,yrod);
        hallynorm->SetBinContent(tbin,blyat);
	hallynorm->GetXaxis()->SetRangeUser(0.,2.); //post that it is very strange
	gStyle->SetOptStat(111111);
      } 
      if(guardY){
	for(Int_t j = YBINLOW; j < YBINHIGH; j++){
	  tbin = hallynorm->GetBin(i,j);
	  hallymaxima->SetBinContent(tbin,0.);
	  hallynorm->SetBinContent(tbin,0.);
	}
      }
    }

    //scan Y-bins of ready histo for abnormalities
    for(Int_t i = YBINLOW; i < YBINHIGH; i++){
      bool guardX = true;
      for(Int_t j = XBINLOW; j < XBINHIGH; j++){
	htemp = hall->ProjectionX("htemp",i,i+1);
	Double_t maxval = htemp->GetMaximum();
	htemp->Scale(1/maxval);
	if(htemp->GetMaximum() > 0.1){guardX=false;}
      }
      if(guardX){
	Int_t tbin = 0;
	for(Int_t j = XBINLOW; j < XBINHIGH; j++){
	  tbin = hallxnorm->GetBin(j,i);
	  hallxmaxima->SetBinContent(tbin,0.);
	  hallxnorm->SetBinContent(tbin,0.);
	}
      }
    }


    htemp->Reset();

    //we actually didn't need these, we wanted contours of maxima so both bins normalised

    //print the new histograms
    hallxnorm->SetTitle("Normalised-on-p correlations");
    hallxnorm->SetXTitle("p_{norm}");
    hallxnorm->SetYTitle("#theta");
    hallxnorm->Draw("COLZ");
    gPad->Update();
    st = (TPaveStats*)hallxnorm->FindObject("stats");
    st->SetX1NDC(0.7); st->SetX2NDC(0.8);
    cc->Print(Form("outStack/%s/%s_%s_momNorm.eps", anaid.Data(), var.Data(), tag.Data()));
    cc->Print(Form("outStack/%s/%s_%s_momNorm.png", anaid.Data(), var.Data(), tag.Data()));
    cc->Clear();

    hallxmaxima->SetTitle("Maxima map: p-normalisation");
    hallxmaxima->SetXTitle("p_{norm}");
    hallxmaxima->SetYTitle("#theta_{norm}");
    hallxmaxima->Draw("COLZ");
    gPad->Update();
    st = (TPaveStats*)hallxmaxima->FindObject("stats");
    st->SetX1NDC(0.7); st->SetX2NDC(0.8);
    cc->Print(Form("outStack/%s/%s_%s_momMax.eps", anaid.Data(), var.Data(), tag.Data()));
    cc->Print(Form("outStack/%s/%s_%s_momMax.png", anaid.Data(), var.Data(), tag.Data()));
    cc->Clear();

    hallynorm->SetTitle("Normalised-on-#theta correlations");
    hallynorm->SetXTitle("p");
    hallynorm->SetYTitle("#theta_{norm}");
    hallynorm->Draw("COLZ");
    gPad->Update();
    st = (TPaveStats*)hallynorm->FindObject("stats");
    st->SetX1NDC(0.7); st->SetX2NDC(0.8);
    cc->Print(Form("outStack/%s/%s_%s_thetaNorm.eps", anaid.Data(), var.Data(), tag.Data()));
    cc->Print(Form("outStack/%s/%s_%s_thetaNorm.png", anaid.Data(), var.Data(), tag.Data()));
    cc->Clear();

    hallymaxima->SetTitle("Maxima map: #theta-normalisation");
    hallymaxima->SetXTitle("p_{norm}");
    hallymaxima->SetYTitle("#theta_{norm}");
    hallymaxima->Draw("COLZ");
    gPad->Update();
    st = (TPaveStats*)hallymaxima->FindObject("stats");
    st->SetX1NDC(0.7); st->SetX2NDC(0.8);
    cc->Print(Form("outStack/%s/%s_%s_thetaMax.eps", anaid.Data(), var.Data(), tag.Data()));
    cc->Print(Form("outStack/%s/%s_%s_thetaMax.png", anaid.Data(), var.Data(), tag.Data()));
    cc->Clear();

    //add these histograms to the list, I want to see them in 3D
    lout->Add(hallxnorm);
    lout->Add(hallxmaxima);
    lout->Add(hallynorm);
    lout->Add(hallymaxima);

  }
  else{
    TH1D * hall=(TH1D*) gDirectory->Get(var+"_all");   
    TH1D * hqe=(TH1D*) gDirectory->Get(var+"_qe");     
    TH1D * hres=(TH1D*) gDirectory->Get(var+"_res");   
    TH1D * hdis=(TH1D*) gDirectory->Get(var+"_dis");   
    TH1D * h2p2h=(TH1D*) gDirectory->Get(var+"_2p2h"); 
    TH1D * hother=(TH1D*) gDirectory->Get(var+"_other"); 
    if(hother){
      if(hother->GetEntries()){
        printf("\n\n\n\n\n%s has entry! Is it COH?? \n\n\n\n\n\n", hother->GetName()); exit(1);
      }
      else{
        cout<<hother->GetName()<<" good "<<hother->GetEntries()<<endl;
      }
    }

    TH1D * hqe_0pi=(TH1D*) gDirectory->Get(var+"_qe_0pi");
    TH1D * hqe_1pi=(TH1D*) gDirectory->Get(var+"_qe_1pi");
    TH1D * hqe_Mpi=(TH1D*) gDirectory->Get(var+"_qe_Mpi");
    TH1D * hres_0pi=(TH1D*) gDirectory->Get(var+"_res_0pi");
    TH1D * hres_1pi=(TH1D*) gDirectory->Get(var+"_res_1pi");
    TH1D * hres_Mpi=(TH1D*) gDirectory->Get(var+"_res_Mpi");
    TH1D * hdis_0pi=(TH1D*) gDirectory->Get(var+"_dis_0pi");
    TH1D * hdis_1pi=(TH1D*) gDirectory->Get(var+"_dis_1pi");
    TH1D * hdis_Mpi=(TH1D*) gDirectory->Get(var+"_dis_Mpi");
    TH1D * h2p2h_0pi=(TH1D*) gDirectory->Get(var+"_2p2h_0pi");
    TH1D * h2p2h_1pi=(TH1D*) gDirectory->Get(var+"_2p2h_1pi");
    TH1D * h2p2h_Mpi=(TH1D*) gDirectory->Get(var+"_2p2h_Mpi");

    /*
    TH1D *hh[]={hall, hqe, hres, hdis, h2p2h};
    TString tit[]={"all", "QE","RES", "DIS", "2p2h"};
    const Int_t cols[]={kBlack, kRed-3,  kGray, kMagenta, kOrange};
    */

    TH1D *hh[]={   hall,  hqe_0pi,  hqe_1pi,  hqe_Mpi,  hres_0pi,  hres_1pi,  hres_Mpi,  hdis_0pi,  hdis_1pi,  hdis_Mpi,  h2p2h_0pi,  h2p2h_1pi,  h2p2h_Mpi};
    TString tit[]={"all", "QE", "QE 1#pi^{+}", "QE multi-#pi^{+}", "RES", "RES 1#pi^{+}", "RES multi-#pi^{+}", "DIS", "DIS 1#pi^{+}", "DIS multi-#pi^{+}", "2p2h", "2p2h 1#pi^{+}", "2p2h multi-#pi^{+}"};
    const Int_t cols[]={kBlack, kRed-3,  kGray, kMagenta, kOrange, kBlue, kGreen+3, kRed+3,  kGray+2, kViolet+3, kOrange+7, kAzure-6, kGreen+1};

    THStack * stk = new THStack(var,tag); lout->Add(stk);
 
    TLegend *lg=new TLegend(0.75, 0.5, 0.9,0.9); lg->SetName("lg"); lout->Add(lg);
    lg->SetFillStyle(0);
    
    const int nh = sizeof(hh)/sizeof(TH1D*);
    for(int ii=0; ii<nh; ii++){
      
      //scale for CH target!
      //hh[ii]->Scale(1./12.); printf("Scaling to per nucleon in C,  C should have been full nucleus and combined !!\n");
      hh[ii]->Scale(1./13.); printf("Scaling to per nucleon in CH,  C and H should have been full nucleus and combined !!\n");
      
      lout->Add(hh[ii]);
      //hh[ii]->SetLineWidth(0.5);
      hh[ii]->SetLineStyle(kSolid);
      hh[ii]->SetLineColor(cols[ii]);
      hh[ii]->SetFillColor(cols[ii]);
      hh[ii]->SetFillStyle(1001);
      hh[ii]->SetTitle(Form("%s %s",tit[ii].Data(), hh[ii]->GetTitle()));
      hh[ii]->SetName(Form("%s%s",var.Data(), tit[ii].Data()));
      if(ii){
        stk->Add(hh[ii]);
      }
      lg->AddEntry(hh[ii], tit[ii], "fl");
    }

    TCanvas *cc=new TCanvas;
    //stk->Draw("hist C");
    stk->Draw("hist");
    stk->GetXaxis()->SetTitle(var);
    stk->SetTitle(hall->GetTitle());
    gStyle->SetTitleX(0.5);
    //stk->Draw("hist C");
    stk->Draw("hist");
    hall->SetLineWidth(3);
    hall->SetLineColor(kBlack);
    hall->SetFillStyle(0);
    hall->SetMinimum(0);
    hall->Draw("same");
    printf("total integrated xsec %s %s %e\n", anaid.Data(), var.Data(), hall->Integral(0,10000,"width"));
    lg->Draw();
    cc->Print(Form("outStack/%s/%s_%s.eps", anaid.Data(), var.Data(), tag.Data()));
    cc->Print(Form("outStack/%s/%s_%s.png", anaid.Data(), var.Data(), tag.Data()));
  }

  TFile *fout=new TFile(Form("%s/%s_%s.root", dir.Data(), var.Data(), tag.Data()),"recreate");
  TDirectory *ld=gDirectory->mkdir(tag);
  ld->cd();
  lout->Write();
  fout->Save();
  fout->Close();    
}
