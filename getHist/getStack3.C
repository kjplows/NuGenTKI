//this is a naive way of combining C and H //there's no reason to scale C and H histos, just make sure it's per nucleon!

void getStack3(TString finC, TString finH, TString anaidC, TString anaidH, const TString tag, const TString var)
{
  const TString anaid = anaidC.Remove(anaidC.Length() - 6, 6)+"CH";
  //const TString exten = ".root"; const TString Cfile = finC.Append(exten); const TString Hfile = finH.Append(exten);
  const TString Cfile = finC; const TString Hfile = finH;
  cout << "Cfile " << Cfile << " Hfile "<< Hfile << endl;
  const TString dir= ("outStack/"+anaid);
  gSystem->Exec("mkdir -p "+dir);

  Double_t scaleNucleus = 1.;

  cout<<" finC "<<finC << " finH "<<finH<<endl;
  cout<<" anaid "<<anaid<<" tag "<<tag<<" var "<<var<<endl;

  TList *lout = new TList;

  if(var.Contains("VS")){
    //for logistical reasons, have to set {X,Y}BIN{HIGH,LOW} and {max,min}{X,Y} here
    Int_t XBINHIGH = 100; Int_t YBINHIGH = 100;
    Int_t XBINLOW = 1; Int_t YBINLOW = 1;
    Double_t maxX = 1.; Double_t maxY = 1.;
    Double_t minX = 0.; Double_t minY = 0.;

    TFile *ffinC = TFile::Open(Cfile); TDirectory *gDirC = (TDirectory*) gDirectory;
    if(finC.Contains("GENIE")){scaleNucleus = 1.;} //Don't do scaling now, will be done later
    else if(finC.Contains("GiBUU")){scaleNucleus = 12.;} //take GiBUU to per nucleus in C
    else{cout << "unknown fin " << finC << " ; is the nucleus spelled correctly?" << endl; exit(1);}

    //scaling done at this stage to combine results.
    //initialise the carbon histos
    TH2D * hall_C=(TH2D*) gDirC->Get(var+"_all");      hall_C->Scale(scaleNucleus);
    TH2D * hqe_C=(TH2D*) gDirC->Get(var+"_qe");        hqe_C->Scale(scaleNucleus);
    TH2D * hres_C=(TH2D*) gDirC->Get(var+"_res");      hres_C->Scale(scaleNucleus);
    TH2D * hdis_C=(TH2D*) gDirC->Get(var+"_dis");      hdis_C->Scale(scaleNucleus);
    TH2D * h2p2h_C=(TH2D*) gDirC->Get(var+"_2p2h");    h2p2h_C->Scale(scaleNucleus);
    TH2D * hother_C=(TH2D*) gDirC->Get(var+"_other");  hother_C->Scale(scaleNucleus);

    TH2D * hqe_0pi_C = (TH2D*) gDirC->Get(var+"_qe_0pi");       hqe_0pi_C->Scale(scaleNucleus);       
    TH2D * hqe_1pi_C = (TH2D*) gDirC->Get(var+"_qe_1pi");       hqe_1pi_C->Scale(scaleNucleus);
    TH2D * hqe_Mpi_C = (TH2D*) gDirC->Get(var+"_qe_Mpi");       hqe_Mpi_C->Scale(scaleNucleus);

    TH2D * hres_0pi_C = (TH2D*) gDirC->Get(var+"_res_0pi");     hres_0pi_C->Scale(scaleNucleus);
    TH2D * hres_1pi_C = (TH2D*) gDirC->Get(var+"_res_1pi");     hres_1pi_C->Scale(scaleNucleus);
    TH2D * hres_Mpi_C = (TH2D*) gDirC->Get(var+"_res_Mpi");     hres_Mpi_C->Scale(scaleNucleus);

    TH2D * hdis_0pi_C = (TH2D*) gDirC->Get(var+"_dis_0pi");     hdis_0pi_C->Scale(scaleNucleus);
    TH2D * hdis_1pi_C = (TH2D*) gDirC->Get(var+"_dis_1pi");     hdis_1pi_C->Scale(scaleNucleus);
    TH2D * hdis_Mpi_C = (TH2D*) gDirC->Get(var+"_dis_Mpi");     hdis_Mpi_C->Scale(scaleNucleus);

    TH2D * h2p2h_0pi_C = (TH2D*) gDirC->Get(var+"_2p2h_0pi");   h2p2h_0pi_C->Scale(scaleNucleus);
    TH2D * h2p2h_1pi_C = (TH2D*) gDirC->Get(var+"_2p2h_1pi");   h2p2h_1pi_C->Scale(scaleNucleus);
    TH2D * h2p2h_Mpi_C = (TH2D*) gDirC->Get(var+"_2p2h_Mpi");   h2p2h_Mpi_C->Scale(scaleNucleus);

    Int_t XBINLOW_C = 1; Int_t YBINLOW_C = 1;
    Int_t XBINHIGH_C = 100; Int_t YBINHIGH_C = 100;
    Double_t maxX_C = 0.; Double_t maxY_C = 0.;
    Double_t minX_C = 0.; Double_t minY_C = 0.;
 
    //get number of bins

    XBINHIGH_C = ((TH1D*)gDirC->Get(var+"_all"))->GetNbinsX(); cout << "XBINHIGH_C = " << XBINHIGH_C;
    YBINHIGH_C = ((TH1D*)gDirC->Get(var+"_all"))->GetNbinsY(); cout << "; YBINHIGH_C = " << YBINHIGH_C << endl;
    maxX_C = ((TH1D*)gDirC->Get(var+"_all"))->GetXaxis()->GetBinLowEdge(XBINHIGH_C) + ((TH1D*)gDirC->Get(var+"_all"))->GetXaxis()->GetBinWidth(XBINHIGH_C);
    minX_C = ((TH1D*)gDirC->Get(var+"_all"))->GetXaxis()->GetBinLowEdge(XBINLOW_C);
    maxY_C = ((TH1D*)gDirC->Get(var+"_all"))->GetYaxis()->GetBinLowEdge(YBINHIGH_C) + ((TH1D*)gDirC->Get(var+"_all"))->GetYaxis()->GetBinWidth(YBINHIGH_C);
    minY_C = ((TH1D*)gDirC->Get(var+"_all"))->GetYaxis()->GetBinLowEdge(XBINLOW_C);
    
    //cout << "\n\n\n" << finC << " STUFF DONE \n\n\n";
    // now open finH hydrogen file and do the same
    TFile *ffinH = TFile::Open(Hfile); TDirectory *gDirH = (TDirectory*) gDirectory;

    if(finH.Contains("Hydrogen")){scaleNucleus = 1.;} // this is H so no problem
    else{cout << "unknown fin " << finH << " ; is the nucleus spelled correctly?" << endl; exit(1);}

    //scaling done at this stage to combine results
    TH2D * hall_H=(TH2D*) gDirH->Get(var+"_all");      hall_H->Scale(scaleNucleus);
    TH2D * hqe_H=(TH2D*) gDirH->Get(var+"_qe");        hqe_H->Scale(scaleNucleus);
    TH2D * hres_H=(TH2D*) gDirH->Get(var+"_res");      hres_H->Scale(scaleNucleus);
    TH2D * hdis_H=(TH2D*) gDirH->Get(var+"_dis");      hdis_H->Scale(scaleNucleus);
    TH2D * h2p2h_H=(TH2D*) gDirH->Get(var+"_2p2h");    h2p2h_H->Scale(scaleNucleus);
    TH2D * hother_H=(TH2D*) gDirH->Get(var+"_other");  hother_H->Scale(scaleNucleus);

    TH2D * hqe_0pi_H = (TH2D*) gDirH->Get(var+"_qe_0pi");       
    TH2D * hqe_1pi_H = (TH2D*) gDirH->Get(var+"_qe_1pi");       
    TH2D * hqe_Mpi_H = (TH2D*) gDirH->Get(var+"_qe_Mpi");       

    TH2D * hres_0pi_H = (TH2D*) gDirH->Get(var+"_res_0pi");     
    TH2D * hres_1pi_H = (TH2D*) gDirH->Get(var+"_res_1pi");     
    TH2D * hres_Mpi_H = (TH2D*) gDirH->Get(var+"_res_Mpi");     

    TH2D * hdis_0pi_H = (TH2D*) gDirH->Get(var+"_dis_0pi");     
    TH2D * hdis_1pi_H = (TH2D*) gDirH->Get(var+"_dis_1pi");     
    TH2D * hdis_Mpi_H = (TH2D*) gDirH->Get(var+"_dis_Mpi");     

    TH2D * h2p2h_0pi_H = (TH2D*) gDirH->Get(var+"_2p2h_0pi");   
    TH2D * h2p2h_1pi_H = (TH2D*) gDirH->Get(var+"_2p2h_1pi");   
    TH2D * h2p2h_Mpi_H = (TH2D*) gDirH->Get(var+"_2p2h_Mpi");   

    Int_t XBINHIGH_H = 1; Int_t YBINHIGH_H = 1;
    Int_t XBINLOW_H = 1; Int_t YBINLOW_H = 1;
    Double_t maxX_H = 0.; Double_t maxY_H = 0.;
    Double_t minX_H = 0.; Double_t minY_H = 0.;
 
    //get number of bins

    XBINHIGH_H = ((TH1D*)gDirH->Get(var+"_all"))->GetNbinsX(); cout << "XBINHIGH_H = " << XBINHIGH_H;
    YBINHIGH_H = ((TH1D*)gDirH->Get(var+"_all"))->GetNbinsY(); cout << "; YBINHIGH_H ' " << YBINHIGH_H << endl;
    maxX_H = ((TH1D*)gDirH->Get(var+"_all"))->GetXaxis()->GetBinLowEdge(XBINHIGH_H) + ((TH1D*)gDirH->Get(var+"_all"))->GetXaxis()->GetBinWidth(XBINHIGH_H);
    minX_H = ((TH1D*)gDirH->Get(var+"_all"))->GetXaxis()->GetBinLowEdge(XBINLOW_H);
    maxY_H = ((TH1D*)gDirH->Get(var+"_all"))->GetYaxis()->GetBinLowEdge(YBINHIGH_H) + ((TH1D*)gDirH->Get(var+"_all"))->GetYaxis()->GetBinWidth(YBINHIGH_H);
    minY_H = ((TH1D*)gDirH->Get(var+"_all"))->GetYaxis()->GetBinLowEdge(XBINLOW_H);

    //ffinH->Close(); //DO NOT CLOSE MAKES SEGMENTATION VIOLATION
    //cout << "\n\n\n" << finH << " STUFF DONE \n\n\n";

    // space for the combined stuff

    //get the limits
    if(XBINHIGH_C && XBINHIGH_H){XBINHIGH = TMath::Max(XBINHIGH_C,XBINHIGH_H); YBINHIGH = TMath::Max(YBINHIGH_C,YBINHIGH_H);}
    if(maxX_C && maxX_H && maxY_C && maxY_H){maxX = TMath::Max(maxX_C,maxX_H); maxY = TMath::Max(maxY_C,maxY_H);}
    if(minX_C && minX_H && minY_C && minY_H){minX = TMath::Min(minX_C,minX_H); minY = TMath::Min(minY_C,minY_H);}

    //cout << "\n\n\n Limits OK \n\n\n";

    //initialise combined histos now (must be non-null!)
    //initialise 2D histos for the combined sample
    TH2D * hall = hall_C; hall->SetName("hall"); hall->SetTitle("hall"); hall->Add(hall_H);
    
    TH2D * hqe = hqe_C; hqe->SetName("hqe"); hqe->SetTitle("hqe"); hqe->Add(hqe_H);
    TH2D * hqe_0pi = hqe_0pi_C; hqe_0pi->SetName("hqe_0pi"); hqe_0pi->SetTitle("hqe_0pi"); hqe_0pi->Add(hqe_0pi_H);
    TH2D * hqe_1pi = hqe_1pi_C; hqe_1pi->SetName("hqe_1pi"); hqe_1pi->SetTitle("hqe_1pi"); hqe_1pi->Add(hqe_1pi_H);
    TH2D * hqe_Mpi = hqe_Mpi_C; hqe_Mpi->SetName("hqe_Mpi"); hqe_Mpi->SetTitle("hqe_Mpi"); hqe_Mpi->Add(hqe_Mpi_H);

    TH2D * hres = hres_C; hres->SetName("hres"); hres->SetTitle("hres"); hres->Add(hres_H);
    TH2D * hres_0pi = hres_0pi_C; hres_0pi->SetName("hres_0pi"); hres_0pi->SetTitle("hres_0pi"); hres_0pi->Add(hres_0pi_H);
    TH2D * hres_1pi = hres_1pi_C; hres_1pi->SetName("hres_1pi"); hres_1pi->SetTitle("hres_1pi"); hres_1pi->Add(hres_1pi_H);
    TH2D * hres_Mpi = hres_Mpi_C; hres_Mpi->SetName("hres_Mpi"); hres_Mpi->SetTitle("hres_Mpi"); hres_Mpi->Add(hres_Mpi_H);

    TH2D * hdis = hdis_C; hdis->SetName("hdis"); hdis->SetTitle("hdis"); hdis->Add(hdis_H);
    TH2D * hdis_0pi = hdis_0pi_C; hdis_0pi->SetName("hdis_0pi"); hdis_0pi->SetTitle("hdis_0pi"); hdis_0pi->Add(hdis_0pi_H);
    TH2D * hdis_1pi = hdis_1pi_C; hdis_1pi->SetName("hdis_1pi"); hdis_1pi->SetTitle("hdis_1pi"); hdis_1pi->Add(hdis_1pi_H);
    TH2D * hdis_Mpi = hdis_Mpi_C; hdis_Mpi->SetName("hdis_Mpi"); hdis_Mpi->SetTitle("hdis_Mpi"); hdis_Mpi->Add(hdis_Mpi_H);

    TH2D * h2p2h = h2p2h_C; h2p2h->SetName("h2p2h"); h2p2h->SetTitle("h2p2h"); h2p2h->Add(h2p2h_H);
    TH2D * h2p2h_0pi = h2p2h_0pi_C; h2p2h_0pi->SetName("h2p2h_0pi"); h2p2h_0pi->SetTitle("h2p2h_0pi"); h2p2h_0pi->Add(h2p2h_0pi_H);
    TH2D * h2p2h_1pi = h2p2h_1pi_C; h2p2h_1pi->SetName("h2p2h_1pi"); h2p2h_1pi->SetTitle("h2p2h_1pi"); h2p2h_1pi->Add(h2p2h_1pi_H);
    TH2D * h2p2h_Mpi = h2p2h_Mpi_C; h2p2h_Mpi->SetName("h2p2h_Mpi"); h2p2h_Mpi->SetTitle("h2p2h_Mpi"); h2p2h_Mpi->Add(h2p2h_Mpi_H);

    //cout << "\n\n\n INTIALISATION OF TH2DS OK \n\n\n";

    // added scaled *per nucleus* histo
  
    TH1D * hall_slice = hall->ProjectionX("_px",2,3);

    //cout << "\n\n\n TH2D NONTOPO ADDED \n\n\n";

    //and topologies
    TH1D * hqe_0pi_slice = hqe_0pi->ProjectionX("_px",2,3);
    TH1D * hqe_1pi_slice = hqe_1pi->ProjectionX("_px",2,3);
    TH1D * hqe_Mpi_slice = hqe_Mpi->ProjectionX("_px",2,3);

    TH1D * hres_0pi_slice = hres_0pi->ProjectionX("_px",2,3);
    TH1D * hres_1pi_slice = hres_1pi->ProjectionX("_px",2,3);
    TH1D * hres_Mpi_slice = hres_Mpi->ProjectionX("_px",2,3);

    TH1D * hdis_0pi_slice = hdis_0pi->ProjectionX("_px",2,3);
    TH1D * hdis_1pi_slice = hdis_1pi->ProjectionX("_px",2,3);
    TH1D * hdis_Mpi_slice = hdis_Mpi->ProjectionX("_px",2,3);

    TH1D * h2p2h_0pi_slice = h2p2h_0pi->ProjectionX("_px",2,3);
    TH1D * h2p2h_1pi_slice = h2p2h_1pi->ProjectionX("_px",2,3);
    TH1D * h2p2h_Mpi_slice = h2p2h_Mpi->ProjectionX("_px",2,3);

    cout << "hall_slice has " << hall_slice->Integral(0,100000,"width") << " xsec per nucleus" << endl;
    cout << "hqe_0pi_slice has " << hqe_0pi_slice->Integral(0,100000,"width") << " xsec per nucleus" << endl; 
    cout << "hqe_1pi_slice has " << hqe_1pi_slice->Integral(0,100000,"width") << " xsec per nucleus" << endl;
    cout << "hqe_Mpi_slice has " << hqe_Mpi_slice->Integral(0,100000,"width") << " xsec per nucleus" << endl;
    cout << "hres_0pi_slice has " << hres_0pi_slice->Integral(0,100000,"width") << " xsec per nucleus" << endl;
    cout << "hres_1pi_slice has " << hres_1pi_slice->Integral(0,100000,"width") << " xsec per nucleus" << endl;
    cout << "hres_Mpi_slice has " << hres_Mpi_slice->Integral(0,100000,"width") << " xsec per nucleus" << endl;
    cout << "hdis_0pi_slice has " << hdis_0pi_slice->Integral(0,100000,"width") << " xsec per nucleus" << endl;
    cout << "hdis_1pi_slice has " << hdis_1pi_slice->Integral(0,100000,"width") << " xsec per nucleus" << endl;
    cout << "hdis_Mpi_slice has " << hdis_Mpi_slice->Integral(0,100000,"width") << " xsec per nucleus" << endl;
    cout << "h2p2h_0pi_slice has " << h2p2h_0pi_slice->Integral(0,100000,"width") << " xsec per nucleus" << endl;
    cout << "h2p2h_1pi_slice has " << h2p2h_1pi_slice->Integral(0,100000,"width") << " xsec per nucleus" << endl;
    cout << "h2p2h_Mpi_slice has " << h2p2h_Mpi_slice->Integral(0,100000,"width") << " xsec per nucleus" << endl;
    sleep(5);
    
    THStack * stwpa = new THStack(var, tag); //interaction mode decomp, no normalisation
    TString titwpa[]={"all","QE", "RES", "DIS", "2p2h"};
    const Int_t colswpa[]={kBlack, kRed-3, kOrange, kBlue, kViolet};

    TLegend *lg=new TLegend(0.75, 0.5, 0.9,0.9); lg->SetName("lg"); lout->Add(lg);
    lg->SetFillStyle(0);
 
    TH2D *hh[]={hall, hqe, hres, hdis, h2p2h}; 
    int nh=5;
    printf("Scaling to per nucleon in CH,  C and H should have been full nucleus and combined !!\n");
    for(int ii=0; ii<nh; ii++){
      hh[ii]->Scale(1./13.);
      
      lout->Add(hh[ii]);
      hh[ii]->SetLineStyle(kSolid);
      hh[ii]->SetFillColor(colswpa[ii]);
      if(ii!=0){hh[ii]->SetFillStyle(3001);}else{hh[ii]->SetFillStyle(1001);}
      hh[ii]->SetTitle(Form("%s %s",titwpa[ii].Data(), hh[ii]->GetTitle()));
      hh[ii]->SetName(Form("%s%s",var.Data(), titwpa[ii].Data()));
      stwpa->Add(hh[ii]);
      lg->AddEntry(hh[ii], titwpa[ii], "fl");
    }
    lout->Add(stwpa);

    TH1D *hhslice[]={   hall_slice,  hqe_0pi_slice,  hqe_1pi_slice,  hqe_Mpi_slice,  hres_0pi_slice,  hres_1pi_slice,  hres_Mpi_slice,  hdis_0pi_slice,  hdis_1pi_slice,  hdis_Mpi_slice,  h2p2h_0pi_slice,  h2p2h_1pi_slice,  h2p2h_Mpi_slice};
    TString titslice[]={"all", "QE", "QE 1#pi^{+}", "QE multi-#pi^{+}", "RES", "RES 1#pi^{+}", "RES multi-#pi^{+}", "DIS", "DIS 1#pi^{+}", "DIS multi-#pi^{+}", "2p2h", "2p2h 1#pi^{+}", "2p2h multi-#pi^{+}"};
    const Int_t colsslice[]={kBlack, kRed-3,  kGray, kMagenta, kOrange, kBlue, kGreen+3, kRed+3,  kGray+2, kViolet+3, kOrange+7, kAzure-6, kGreen+1};

    THStack * stkslice = new THStack(var,tag+"_slice"); lout->Add(stkslice);
 
    TLegend *lgslice=new TLegend(0.75, 0.5, 0.9,0.9); lgslice->SetName("lgslice"); lout->Add(lgslice);
    lgslice->SetFillStyle(0);

    const int nhslice=sizeof(hhslice)/sizeof(TH1D*);
    for(int ii=0; ii<nhslice; ii++){
      hhslice[ii]->Scale(1./13.);
      lout->Add(hhslice[ii]);
      hhslice[ii]->SetLineStyle(kSolid);
      hhslice[ii]->SetLineColor(colsslice[ii]);
      //if(ii!=0)hhslice[ii]->SetFillColor(colsslice[ii]);
      hhslice[ii]->SetFillColor(colsslice[ii]);
      //if(ii!=0){hhslice[ii]->SetFillStyle(1001);}else{hhslice[ii]->SetFillStyle(0);}
      hhslice[ii]->SetFillStyle(1001);
      hhslice[ii]->SetTitle(Form("%s %s",titslice[ii].Data(), hhslice[ii]->GetTitle()));
      hhslice[ii]->SetName(Form("%s%s",var.Data(), titslice[ii].Data()));
      if(ii!=0)stkslice->Add(hhslice[ii]);
      lgslice->AddEntry(hhslice[ii], titslice[ii], "fl");
    }
    stkslice->SetName("Stack slice");
    lout->Add(stkslice);

    TCanvas *ccslice=new TCanvas;
    //stk->Draw("hist C");
    stkslice->Draw("hist");
    if(var.Contains("Ek")){stkslice->GetXaxis()->SetTitle("T");}else{stkslice->GetXaxis()->SetTitle("p");}
    if(var.Contains("pion")){stkslice->GetXaxis()->SetRangeUser(0.,1.);}
    stkslice->SetTitle(hall_slice->GetTitle());
    gStyle->SetTitleX(0.5);
    //stk->Draw("hist C");
    stkslice->Draw("hist");
    hall_slice->SetLineWidth(3);
    hall_slice->SetLineColor(kBlack);
    hall_slice->SetFillStyle(0);
    hall_slice->SetMinimum(0);
    hall_slice->GetXaxis()->SetRangeUser(0.,1.);
    hall_slice->Draw("same"); 
    printf("slice integrated xsec %s %s %e\n", anaid.Data(), var.Data(), hall_slice->Integral(0,100000,"width"));
    lgslice->Draw();
    TString subvar("outStack/"+anaid+"/"+var(0,6)+"slices");
    gSystem->Exec("mkdir -p "+subvar); //to store these
    ccslice->Print(Form("%s/%s_%s.eps", subvar.Data(), var.Data(), tag.Data()));
    ccslice->Print(Form("%s/%s_%s.png", subvar.Data(), var.Data(), tag.Data()));
    
    if(var.Contains("proton")){hall->SetTitle("Proton theta vs momentum");}
    else if(var.Contains("muon")){hall->SetTitle("Muon theta vs momentum");;}
    else{hall->SetTitle("Pion theta vs momentum");}
    //hall->SetTitle(strin+"theta vs momentum");
    hall->GetXaxis()->SetRangeUser(0.,6.);
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

    //these THStacks will only store the complete TH2Ds. They will NOT get the projections
    //(there exists no compact way of projecting THStacks, as per ROOT forums...)
    THStack * stwpaxnorm = new THStack(var, tag+"p-norm"); 
    THStack * stwpaynorm = new THStack(var, tag+"theta-norm"); 
    THStack * stwpaxmax = new THStack(var, tag+"p-max"); 
    THStack * stwpaymax = new THStack(var, tag+"theta-max"); 

    // now to do the normalisation:
    // First get for each X-bin (Y-bin) the TH1D behind //do that with ProjectionX(firstbin = lowedge, lastbin = highedge)
    // Then SetMaximum of that TH1D to 1 //note Scale() works the way I wanted SetMaximum to.
    // create new TH2D with that normalisation
    // ==> 2 new TH2Ds for each TH1D

    //now to show the interaction mode decomposition as well
    
    //declare TH2D * to be filled
    TH2D * hallxnorm = new TH2D("hallxnorm","hallxnorm",XBINHIGH,0.,maxX,YBINHIGH,0.,maxY);
    TH2D * hallynorm = new TH2D("hallynorm","hallynorm",XBINHIGH,0.,maxX,YBINHIGH,0.,maxY);
    TH2D * hallxmax = new TH2D("hallxmax","hallxmax",XBINHIGH,0.,maxX,YBINHIGH,0.,maxY);
    TH2D * hallymax = new TH2D("hallymax","hallymax",XBINHIGH,0.,maxX,YBINHIGH,0.,maxY);

    TH2D * hqexnorm = new TH2D("hqexnorm","hqexnorm",XBINHIGH,0.,maxX,YBINHIGH,0.,maxY);
    TH2D * hqeynorm = new TH2D("hqeynorm","hqeynorm",XBINHIGH,0.,maxX,YBINHIGH,0.,maxY);
    TH2D * hqexmax = new TH2D("hqexmax","hqqxmax",XBINHIGH,0.,maxX,YBINHIGH,0.,maxY);
    TH2D * hqeymax = new TH2D("hqeymax","hqeymax",XBINHIGH,0.,maxX,YBINHIGH,0.,maxY);

    TH2D * hresxnorm = new TH2D("hresxnorm","hresxnorm",XBINHIGH,0.,maxX,YBINHIGH,0.,maxY);
    TH2D * hresynorm = new TH2D("hresynorm","hresynorm",XBINHIGH,0.,maxX,YBINHIGH,0.,maxY);
    TH2D * hresxmax = new TH2D("hresxmax","hresxmax",XBINHIGH,0.,maxX,YBINHIGH,0.,maxY);
    TH2D * hresymax = new TH2D("hresymax","hresymax",XBINHIGH,0.,maxX,YBINHIGH,0.,maxY);

    TH2D * hdisxnorm = new TH2D("hdisxnorm","hdisxnorm",XBINHIGH,0.,maxX,YBINHIGH,0.,maxY);
    TH2D * hdisynorm = new TH2D("hdisynorm","hdisynorm",XBINHIGH,0.,maxX,YBINHIGH,0.,maxY);
    TH2D * hdisxmax = new TH2D("hdisxmax","hdisxmax",XBINHIGH,0.,maxX,YBINHIGH,0.,maxY);
    TH2D * hdisymax = new TH2D("hdisymax","hdisymax",XBINHIGH,0.,maxX,YBINHIGH,0.,maxY);

    TH2D * h2p2hxnorm = new TH2D("h2p2hxnorm","h2p2hxnorm",XBINHIGH,0.,maxX,YBINHIGH,0.,maxY);
    TH2D * h2p2hynorm = new TH2D("h2p2hynorm","h2p2hynorm",XBINHIGH,0.,maxX,YBINHIGH,0.,maxY);
    TH2D * h2p2hxmax = new TH2D("h2p2hxmax","h2p2hxmax",XBINHIGH,0.,maxX,YBINHIGH,0.,maxY);
    TH2D * h2p2hymax = new TH2D("h2p2hymax","h2p2hymax",XBINHIGH,0.,maxX,YBINHIGH,0.,maxY);

    TH2D *hhxnorm[]={hallxnorm, hqexnorm, hresxnorm, hdisxnorm, h2p2hxnorm};
    TH2D *hhynorm[]={hallynorm, hqeynorm, hresynorm, hdisynorm, h2p2hynorm};
    TH2D *hhxmax[]={hallxmax, hqexmax, hresxmax, hdisxmax, h2p2hxmax};
    TH2D *hhymax[]={hallymax, hqeymax, hresymax, hdisymax, h2p2hymax};

    TH1D* htemp = 0x0;
    //X(p)-normalisation
    //loop over Y-bins
    for(Int_t hindex = 0; hindex < 5; hindex++){
      for(Int_t i = YBINLOW; i < YBINHIGH; i++){
	//project the slice and set maximum
	htemp = hh[hindex]->ProjectionX("htemp", i, i+i);
	Double_t maxval = htemp->GetMaximum();
	long double scalefactor = 1/maxval;
	htemp->Scale(scalefactor);
	//cout << htemp->GetMean() << endl;
	Int_t tbin = 0;
	bool guardX = true;
	for(Int_t j = XBINLOW; j < XBINHIGH; j++){
	  tbin = hhxnorm[hindex]->GetBin(j,i);
	  double yrod = htemp->GetBinContent(j);
	  if(yrod > 0.1){guardX = false;}
	  double blyat = htemp->GetBinContent(j) * hh[hindex]->GetBinContent(j,i);
	  hhxmax[hindex]->SetBinContent(tbin,yrod);
	  hhxnorm[hindex]->SetBinContent(tbin,blyat); //this must ABSOLUTELY be SetBinContent(); AddBinContent and Fill both fail.
	  hhxnorm[hindex]->GetXaxis()->SetRangeUser(0.,2.);
	  gStyle->SetOptStat(111111);
	}
	if(guardX){
	  for(Int_t j = XBINLOW; j < XBINHIGH; j++)
	    {
	      tbin = hh[hindex]->GetBin(j,i);
	      hhxmax[hindex]->SetBinContent(tbin,0);
	      hhxnorm[hindex]->SetBinContent(tbin,0);
	    }
	}
      }
      //scan X-bins of ready histo for abnormalities
      for(Int_t i = XBINLOW; i < XBINHIGH; i++){
	bool guardY = true;
	for(Int_t j = YBINLOW; j < YBINHIGH; j++){
	  htemp = hh[hindex]->ProjectionY("htemp",i,i+1);
	  Double_t maxval = htemp->GetMaximum();
	  htemp->Scale(1/maxval);
	  if(htemp->GetMaximum() > 0.1){guardY=false;}
	}
	if(guardY){
	  Int_t tbin = 0;
	  for(Int_t j = YBINLOW; j < YBINHIGH; j++){
	    tbin = hhxnorm[hindex]->GetBin(i,j);
	    hhxmax[hindex]->SetBinContent(tbin,0.);
	    hhxnorm[hindex]->SetBinContent(tbin,0.);
	  }
	}
      }

      //Y(theta)-normalisation
      for(Int_t i = XBINLOW; i < XBINHIGH; i++){
	htemp = hh[hindex]->ProjectionY("htemp", i, i+1);
	Double_t maxval = htemp->GetMaximum();
	long double scalefactor = 1/maxval;
	htemp->Scale(scalefactor);
	Int_t tbin = 0;
	//guard against dead X-bins, which have no max because they are dead
	bool guardY = true;
	for(Int_t j = YBINLOW; j < YBINHIGH; j++){
	  tbin = hhynorm[hindex]->GetBin(i,j);
	  double yrod = htemp->GetBinContent(j);
	  //deactivate guard on seeing something like a max
	  if(yrod > 0.1){guardY = false;}
	  double blyat = htemp->GetBinContent(j) * hh[hindex]->GetBinContent(i,j);
	  hhymax[hindex]->SetBinContent(tbin,yrod);
	  hhynorm[hindex]->SetBinContent(tbin,blyat);
	  hhynorm[hindex]->GetXaxis()->SetRangeUser(0.,2.); //post that it is very strange
	  gStyle->SetOptStat(111111);
	} 
	if(guardY){
	  for(Int_t j = YBINLOW; j < YBINHIGH; j++){
	    tbin = hhynorm[hindex]->GetBin(i,j);
	    hhymax[hindex]->SetBinContent(tbin,0.);
	    hhynorm[hindex]->SetBinContent(tbin,0.);
	  }
	}
      }

      //scan Y-bins of ready histo for abnormalities
      for(Int_t i = YBINLOW; i < YBINHIGH; i++){
	bool guardX = true;
	for(Int_t j = XBINLOW; j < XBINHIGH; j++){
	  htemp = hh[hindex]->ProjectionX("htemp",i,i+1);
	  Double_t maxval = htemp->GetMaximum();
	  htemp->Scale(1/maxval);
	  if(htemp->GetMaximum() > 0.1){guardX=false;}
	}
	if(guardX){
	  Int_t tbin = 0;
	  for(Int_t j = XBINLOW; j < XBINHIGH; j++){
	    tbin = hhxnorm[hindex]->GetBin(j,i);
	    hhxmax[hindex]->SetBinContent(tbin,0.);
	    hhxnorm[hindex]->SetBinContent(tbin,0.);
	  }
	}
      }
      
      htemp->Reset();
      
      //finalising names/legends
      hhxnorm[hindex]->SetTitle(titwpa[hindex]+"_norm");
      hhxnorm[hindex]->SetFillColor(colswpa[hindex]);
      hhxnorm[hindex]->SetFillStyle(1001);
      hhynorm[hindex]->SetTitle(titwpa[hindex]+"_norm");
      hhynorm[hindex]->SetFillColor(colswpa[hindex]);
      hhynorm[hindex]->SetFillStyle(1001);
      hhxmax[hindex]->SetTitle(titwpa[hindex]+"_max");
      hhxmax[hindex]->SetFillColor(colswpa[hindex]);
      hhxmax[hindex]->SetFillStyle(1001);
      hhymax[hindex]->SetTitle(titwpa[hindex]+"_max");
      hhymax[hindex]->SetFillColor(colswpa[hindex]);
      hhymax[hindex]->SetFillStyle(1001);

      stwpaxnorm->Add(hhxnorm[hindex]); 
      stwpaynorm->Add(hhynorm[hindex]);
      stwpaxmax->Add(hhxmax[hindex]);
      stwpaymax->Add(hhymax[hindex]);
    }//loop over interaction mode

    stwpaxnorm->SetName("stackXNORM"); stwpaxnorm->SetTitle("X-single-normalised stack"); lout->Add(stwpaxnorm);
    stwpaynorm->SetName("stackYNORM"); stwpaynorm->SetTitle("Y-single-normalised stack"); lout->Add(stwpaynorm);
    stwpaxmax->SetName("stackXMax"); stwpaxmax->SetTitle("X-double-normalised stack"); lout->Add(stwpaxmax);
    stwpaymax->SetName("stackYMax"); stwpaymax->SetTitle("Y-double-normalised stack"); lout->Add(stwpaymax);

    //we actually didn't need these, we wanted contours of maxima so both bins normalised

    //print the new histograms and save the stacks
    hallxnorm->SetTitle("Normalised-on-X correlations");
    hallxnorm->SetXTitle("X_{norm}");
    hallxnorm->SetYTitle("Y");
    hallxnorm->Draw("COLZ");
    gPad->Update();
    st = (TPaveStats*)hallxnorm->FindObject("stats");
    st->SetX1NDC(0.7); st->SetX2NDC(0.8);
    cc->Print(Form("outStack/%s/%s_%s_XNorm.eps", anaid.Data(), var.Data(), tag.Data()));
    cc->Print(Form("outStack/%s/%s_%s_XNorm.png", anaid.Data(), var.Data(), tag.Data()));
    cc->Clear();

    hallxmax->SetTitle("Maxima map: X-normalisation");
    hallxmax->SetXTitle("X_{norm}");
    hallxmax->SetYTitle("#Y_{norm}");
    hallxmax->Draw("COLZ");
    gPad->Update();
    st = (TPaveStats*)hallxmax->FindObject("stats");
    st->SetX1NDC(0.7); st->SetX2NDC(0.8);
    cc->Print(Form("outStack/%s/%s_%s_XMax.eps", anaid.Data(), var.Data(), tag.Data()));
    cc->Print(Form("outStack/%s/%s_%s_XMax.png", anaid.Data(), var.Data(), tag.Data()));
    cc->Clear();

    hallynorm->SetTitle("Normalised-on-Y correlations");
    hallynorm->SetXTitle("X");
    hallynorm->SetYTitle("#Y_{norm}");
    hallynorm->Draw("COLZ");
    gPad->Update();
    st = (TPaveStats*)hallynorm->FindObject("stats");
    st->SetX1NDC(0.7); st->SetX2NDC(0.8);
    cc->Print(Form("outStack/%s/%s_%s_YNorm.eps", anaid.Data(), var.Data(), tag.Data()));
    cc->Print(Form("outStack/%s/%s_%s_YNorm.png", anaid.Data(), var.Data(), tag.Data()));
    cc->Clear();

    hallymax->SetTitle("Maxima map: Y-normalisation");
    hallymax->SetXTitle("X_{norm}");
    hallymax->SetYTitle("Y_{norm}");
    hallymax->Draw("COLZ");
    gPad->Update();
    st = (TPaveStats*)hallymax->FindObject("stats");
    st->SetX1NDC(0.7); st->SetX2NDC(0.8);
    cc->Print(Form("outStack/%s/%s_%s_YMax.eps", anaid.Data(), var.Data(), tag.Data()));
    cc->Print(Form("outStack/%s/%s_%s_YMax.png", anaid.Data(), var.Data(), tag.Data()));
    cc->Clear();

    //add these histograms to the list, I want to see them in 3D
    lout->Add(hallxnorm);
    lout->Add(hallxmax);
    lout->Add(hallynorm);
    lout->Add(hallymax);
   
  }
  else{
    TFile *ffinC = TFile::Open(Cfile); TDirectory *gDirC = (TDirectory*) gDirectory;

    if(finC.Contains("GENIE")){scaleNucleus = 1.;}
    else if(finC.Contains("GiBUU")){scaleNucleus = 12.;} //scale to per nucleus in GiBUU now
    else{cout << "unknown fin " << finC << " ; is the nucleus spelled correctly?" << endl; exit(1);}

    TH1D * hall_C=(TH1D*) gDirC->Get(var+"_all");      hall_C->Scale(scaleNucleus);   
    TH1D * hqe_C=(TH1D*) gDirC->Get(var+"_qe");        hqe_C->Scale(scaleNucleus);
    TH1D * hres_C=(TH1D*) gDirC->Get(var+"_res");      hres_C->Scale(scaleNucleus);
    TH1D * hdis_C=(TH1D*) gDirC->Get(var+"_dis");      hdis_C->Scale(scaleNucleus);
    TH1D * h2p2h_C=(TH1D*) gDirC->Get(var+"_2p2h");    h2p2h_C->Scale(scaleNucleus);
    TH1D * hother_C=(TH1D*) gDirC->Get(var+"_other");  hother_C->Scale(scaleNucleus);
    if(hother_C){
      if(hother_C->GetEntries()){
        printf("\n\n\n\n\n%s has entry! Is it COH?? \n\n\n\n\n\n", hother_C->GetName()); exit(1);
      }
      else{
        cout<<hother_C->GetName()<<" good "<<hother_C->GetEntries()<<endl;
      }
    }

    TH1D * hqe_0pi_C=(TH1D*) gDirC->Get(var+"_qe_0pi");     hqe_0pi_C->Scale(scaleNucleus);
    TH1D * hqe_1pi_C=(TH1D*) gDirC->Get(var+"_qe_1pi");     hqe_1pi_C->Scale(scaleNucleus);
    TH1D * hqe_Mpi_C=(TH1D*) gDirC->Get(var+"_qe_Mpi");     hqe_Mpi_C->Scale(scaleNucleus);
    TH1D * hres_0pi_C=(TH1D*) gDirC->Get(var+"_res_0pi");   hres_0pi_C->Scale(scaleNucleus);
    TH1D * hres_1pi_C=(TH1D*) gDirC->Get(var+"_res_1pi");   hres_1pi_C->Scale(scaleNucleus);
    TH1D * hres_Mpi_C=(TH1D*) gDirC->Get(var+"_res_Mpi");   hres_Mpi_C->Scale(scaleNucleus);
    TH1D * hdis_0pi_C=(TH1D*) gDirC->Get(var+"_dis_0pi");   hdis_0pi_C->Scale(scaleNucleus);
    TH1D * hdis_1pi_C=(TH1D*) gDirC->Get(var+"_dis_1pi");   hdis_1pi_C->Scale(scaleNucleus);
    TH1D * hdis_Mpi_C=(TH1D*) gDirC->Get(var+"_dis_Mpi");   hdis_Mpi_C->Scale(scaleNucleus);
    TH1D * h2p2h_0pi_C=(TH1D*) gDirC->Get(var+"_2p2h_0pi"); h2p2h_0pi_C->Scale(scaleNucleus);
    TH1D * h2p2h_1pi_C=(TH1D*) gDirC->Get(var+"_2p2h_1pi"); h2p2h_1pi_C->Scale(scaleNucleus);
    TH1D * h2p2h_Mpi_C=(TH1D*) gDirC->Get(var+"_2p2h_Mpi"); h2p2h_Mpi_C->Scale(scaleNucleus);

    Int_t XBINLOW_C = 1;
    Int_t XBINHIGH_C = 1;
    Double_t maxX_C = 0.;
    Double_t minX_C = 0.;
 
    XBINHIGH_C = ((TH1D*)gDirC->Get(var+"_all"))->GetNbinsX(); cout << "XBINHIGH_C = " << XBINHIGH_C << endl;
    maxX_C = ((TH1D*)gDirC->Get(var+"_all"))->GetXaxis()->GetBinLowEdge(XBINHIGH_C) + ((TH1D*)gDirC->Get(var+"_all"))->GetXaxis()->GetBinWidth(XBINHIGH_C);
    minX_C = ((TH1D*)gDirC->Get(var+"_all"))->GetXaxis()->GetBinLowEdge(XBINLOW_C);

    //ffinC->Close(); //NONONONONON
    //cout << "\n\n\n" << finC << " STUFF DONE \n\n\n"; sleep(1);
    
    //now the H histos
    TFile *ffinH = TFile::Open(Hfile); TDirectory *gDirH = (TDirectory*) gDirectory;

    if(finH.Contains("Hydrogen")){scaleNucleus = 1.;}
    else{cout << "unknown fin " << finH << " ; is the nucleus spelled correctly?" << endl; exit(1);}

    TH1D * hall_H=(TH1D*) gDirH->Get(var+"_all");      hall_H->Scale(scaleNucleus);   
    TH1D * hqe_H=(TH1D*) gDirH->Get(var+"_qe");        hqe_H->Scale(scaleNucleus);
    TH1D * hres_H=(TH1D*) gDirH->Get(var+"_res");      hres_H->Scale(scaleNucleus);
    TH1D * hdis_H=(TH1D*) gDirH->Get(var+"_dis");      hdis_H->Scale(scaleNucleus);
    TH1D * h2p2h_H=(TH1D*) gDirH->Get(var+"_2p2h");    h2p2h_H->Scale(scaleNucleus);
    TH1D * hother_H=(TH1D*) gDirH->Get(var+"_other");  hother_H->Scale(scaleNucleus);
    if(hother_H){
      if(hother_H->GetEntries()){
        printf("\n\n\n\n\n%s has entry! Is it COH?? \n\n\n\n\n\n", hother_H->GetName()); exit(1);
      }
      else{
        cout<<hother_H->GetName()<<" good "<<hother_H->GetEntries()<<endl;
      }
    }

    TH1D * hqe_0pi_H=(TH1D*) gDirH->Get(var+"_qe_0pi");     hqe_0pi_H->Scale(scaleNucleus);
    TH1D * hqe_1pi_H=(TH1D*) gDirH->Get(var+"_qe_1pi");     hqe_1pi_H->Scale(scaleNucleus);
    TH1D * hqe_Mpi_H=(TH1D*) gDirH->Get(var+"_qe_Mpi");     hqe_Mpi_H->Scale(scaleNucleus);
    TH1D * hres_0pi_H=(TH1D*) gDirH->Get(var+"_res_0pi");   hres_0pi_H->Scale(scaleNucleus);
    TH1D * hres_1pi_H=(TH1D*) gDirH->Get(var+"_res_1pi");   hres_1pi_H->Scale(scaleNucleus);
    TH1D * hres_Mpi_H=(TH1D*) gDirH->Get(var+"_res_Mpi");   hres_Mpi_H->Scale(scaleNucleus);
    TH1D * hdis_0pi_H=(TH1D*) gDirH->Get(var+"_dis_0pi");   hdis_0pi_H->Scale(scaleNucleus);
    TH1D * hdis_1pi_H=(TH1D*) gDirH->Get(var+"_dis_1pi");   hdis_1pi_H->Scale(scaleNucleus);
    TH1D * hdis_Mpi_H=(TH1D*) gDirH->Get(var+"_dis_Mpi");   hdis_Mpi_H->Scale(scaleNucleus);
    TH1D * h2p2h_0pi_H=(TH1D*) gDirH->Get(var+"_2p2h_0pi"); h2p2h_0pi_H->Scale(scaleNucleus);
    TH1D * h2p2h_1pi_H=(TH1D*) gDirH->Get(var+"_2p2h_1pi"); h2p2h_1pi_H->Scale(scaleNucleus);
    TH1D * h2p2h_Mpi_H=(TH1D*) gDirH->Get(var+"_2p2h_Mpi"); h2p2h_Mpi_H->Scale(scaleNucleus);

    Int_t XBINLOW_H = 1;
    Int_t XBINHIGH_H = 1;
    Double_t maxX_H = 0.;
    Double_t minX_H = 0.;
 
    XBINHIGH_H = ((TH1D*)gDirH->Get(var+"_all"))->GetNbinsX(); cout << "XBINHIGH_H = " << XBINHIGH_H << endl;
    maxX_H = ((TH1D*)gDirH->Get(var+"_all"))->GetXaxis()->GetBinLowEdge(XBINHIGH_H) + ((TH1D*)gDirH->Get(var+"_all"))->GetXaxis()->GetBinWidth(XBINHIGH_H);
    minX_H = ((TH1D*)gDirH->Get(var+"_all"))->GetXaxis()->GetBinLowEdge(XBINLOW_H);

    //ffinH->Close(); //DO NOT DO THIS
    //cout << "\n\n\n" << finH << " STUFF DONE \n\n\n"; sleep(1);

    Int_t XBINHIGH = 100;
    Double_t maxX = 1.;
    Double_t minX = 0.;
   
    if(XBINHIGH_C && XBINHIGH_H){XBINHIGH = TMath::Max(XBINHIGH_C,XBINHIGH_H);}
    if(maxX_C && maxX_H){maxX = TMath::Max(maxX_C,maxX_H);}
    if(minX_C && minX_H){minX = TMath::Min(minX_C,minX_H);}

    //cout << "\n\n\n LIMITS SET \n\n\n";

    //combined histo declaration
    TH1D * hall= hall_C; hall->SetName("hall"); hall->SetTitle("hall"); hall->Add(hall_H);

    TH1D * hqe= hqe_C; hqe->SetName("hqe"); hqe->SetTitle("hqe"); hqe->Add(hqe_H);
    TH1D * hqe_0pi= hqe_0pi_C; hqe_0pi->SetName("hqe_0pi"); hqe_0pi->SetTitle("hqe_0pi"); hqe_0pi->Add(hqe_0pi_H);
    TH1D * hqe_1pi= hqe_1pi_C; hqe_1pi->SetName("hqe_1pi"); hqe_1pi->SetTitle("hqe_1pi"); hqe_1pi->Add(hqe_1pi_H);
    TH1D * hqe_Mpi= hqe_Mpi_C; hqe_Mpi->SetName("hqe_Mpi"); hqe_Mpi->SetTitle("hqe_Mpi"); hqe_Mpi->Add(hqe_Mpi_H);

    TH1D * hres= hres_C; hres->SetName("hres"); hres->SetTitle("hres"); hres->Add(hres_H);
    TH1D * hres_0pi= hres_0pi_C; hres_0pi->SetName("hres_0pi"); hres_0pi->SetTitle("hres_0pi"); hres_0pi->Add(hres_0pi_H);
    TH1D * hres_1pi= hres_1pi_C; hres_1pi->SetName("hres_1pi"); hres_1pi->SetTitle("hres_1pi"); hres_1pi->Add(hres_1pi_H);
    TH1D * hres_Mpi= hres_Mpi_C; hres_Mpi->SetName("hres_Mpi"); hres_Mpi->SetTitle("hres_Mpi"); hres_Mpi->Add(hres_Mpi_H);

    TH1D * hdis= hdis_C; hdis->SetName("hdis"); hdis->SetTitle("hdis"); hdis->Add(hdis_H);
    TH1D * hdis_0pi= hdis_0pi_C; hdis_0pi->SetName("hdis_0pi"); hdis_0pi->SetTitle("hdis_0pi"); hdis_0pi->Add(hdis_0pi_H);
    TH1D * hdis_1pi= hdis_1pi_C; hdis_1pi->SetName("hdis_1pi"); hdis_1pi->SetTitle("hdis_1pi"); hdis_1pi->Add(hdis_1pi_H);
    TH1D * hdis_Mpi= hdis_Mpi_C; hdis_Mpi->SetName("hdis_Mpi"); hdis_Mpi->SetTitle("hdis_Mpi"); hdis_Mpi->Add(hdis_Mpi_H);

    TH1D * h2p2h= h2p2h_C; h2p2h->SetName("h2p2h"); h2p2h->SetTitle("h2p2h"); h2p2h->Add(h2p2h_H);
    TH1D * h2p2h_0pi= h2p2h_0pi_C; h2p2h_0pi->SetName("h2p2h_0pi"); h2p2h_0pi->SetTitle("h2p2h_0pi"); h2p2h_0pi->Add(h2p2h_0pi_H);
    TH1D * h2p2h_1pi= h2p2h_1pi_C; h2p2h_1pi->SetName("h2p2h_1pi"); h2p2h_1pi->SetTitle("h2p2h_1pi"); h2p2h_1pi->Add(h2p2h_1pi_H);
    TH1D * h2p2h_Mpi= h2p2h_Mpi_C; h2p2h_Mpi->SetName("h2p2h_Mpi"); h2p2h_Mpi->SetTitle("h2p2h_Mpi"); h2p2h_Mpi->Add(h2p2h_Mpi_H);

    //cout << "\n\n\n HISTOS INITIALISED \n\n\n";

    //cout << "\n\n\n TH1Ds ADDED SUCCESFULLY \n\n\n"; sleep(1);

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
    printf("Scaling to per nucleon in CH,  C and H should have been full nucleus and combined !!\n");
    for(int ii=0; ii<nh; ii++){
      
      //scale for CH target!
      //hh[ii]->Scale(1./12.); printf("Scaling to per nucleon in C,  C should have been full nucleus and combined !!\n");
      hh[ii]->Scale(1./13.);
      
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
    printf("total integrated xsec %s %s %e\n", anaid.Data(), var.Data(), hall->Integral(0,10000,"width")); //sleep(2);
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

  cout<<" finC "<<finC << " finH "<<finH<<endl;
  cout<<" anaid "<<anaid<<" tag "<<tag<<" var "<<var<<endl;
}
