#ifndef __GENIEUTILS_H__
#define __GENIEUTILS_H__

namespace GENIEUtils
{

class GraphSpline
{
 public:
  GraphSpline(TGraph* g)
    {
      spline=new TSpline3( (std::string("graphspline") + g->GetName()).c_str(),g);
    }

  ~GraphSpline() { delete spline; };

  double operator()(double* x, double*)
  {
    return spline->Eval(x[0]);
  }

 private:
  TSpline3* spline;
};

TF1* GENIEgetCCSpline(const int nuPDG, const int targetA);

double CHspline(double *x, double *p)
{
  TF1 * spC = GENIEgetCCSpline((int)(p[0]), 12);
  TF1 * spH = GENIEgetCCSpline((int)(p[0]), 1);
  return spC->Eval(x[0])+spH->Eval(x[0]);
}

TF1* GENIEgetCCSpline(const int nuPDG, const int targetA)
{
  if(targetA==13){
    TF1 * fCH = new TF1("CCsp13",CHspline, 0, 120, 1);
    fCH->SetParameter(0,nuPDG);
    return fCH;
  }
  else{
    const TString objname=Form("CCsp%d",targetA);
    TF1 * sp = (TF1*) gDirectory->FindObject(objname);
    if(!sp){
      printf("initiating spline for nuPDG %d targetA %d\n", nuPDG, targetA);

      const TString myGENIE = gSystem->Getenv("myGENIE");
      if(myGENIE==""){
        printf("no myGENIE!\n"); exit(1);
      }
      const TString splineFileName = myGENIE+"/spline/xsec_graphs.root";
      TFile splineFile(splineFileName);
      if(splineFile.IsZombie()){
        cerr << "Can't find GENIE spline file at:" << endl;
        cerr << splineFileName << endl;
        cerr << "Exiting" << endl;
        exit(1);
      }
      
      TString splineName = "nu_";
      switch(abs(nuPDG)){
      case 14:
        splineName+="mu";
        break;
      case 12:
        splineName+="e";
        break;
      default:
        cerr << "XSecLooper::getCCSpline(): nu PDG is set to " << nuPDG
             << ", which we don't have splines for. Bailing" << endl;
        exit(1);
      }
      if(nuPDG<0) splineName+="_bar";
      
      if(targetA==12){
        splineName+="_C12/tot_cc";
      }
      else if(targetA==1){
        splineName+="_H1/tot_cc";
      }
      else{
        printf("wrong targetA %d\n", targetA); exit(1);
      }
      
      printf("check splineFileName %s\nsplineName %s\n", splineFileName.Data(), splineName.Data());
      TGraph* gr=(TGraph*)splineFile.Get(splineName);
      if(!gr){
        cerr << "Can't find spline " << splineName << " in file " << splineFileName << ". Bailing." << endl;
        exit(1);
      }

      GraphSpline * gsp=new GraphSpline(gr);
      sp = new TF1(objname, gsp, 0, 120, 0, "GraphSpline" );
    }
    return sp;
  }
}

double GENIEgetFluxIntegral(const TH1F * h_rate,  const int nuPDG, const int targetA)
{
  TF1 * spline = GENIEgetCCSpline(nuPDG, targetA);
  
  double fluxInt = 0;
  for(int ii=1; ii<=h_rate->GetNbinsX(); ii++){

    //only do it within Enu cut!
    if(h_rate->GetBinContent(ii)<1){
      continue;
    }

    const double binLowEdge = h_rate->GetBinLowEdge(ii);
    const double binWidth   = h_rate->GetBinWidth(ii);

    //dimension: cross section
    const double xsec = spline->Integral(binLowEdge, binLowEdge+binWidth)/binWidth;

    if( xsec < 1E-6 ){
      std::cout << " Warning, xsec is 0 for bin from " << binLowEdge << " - " <<  binLowEdge+binWidth << endl;
    }
    else{
      //has bin width in it
      fluxInt += h_rate->GetBinContent(ii)/xsec;
      //printf("binLowEdge %f binWidth %f xsec %f rate %f flux %f\n", binLowEdge, binWidth, xsec, h_rate->GetBinContent(ii), fluxInt);
    }
  }

  return fluxInt;
}

//end of namespace
}
#endif
