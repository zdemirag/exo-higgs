{
  gSystem->Load("libRooFit");
  using namespace RooFit;
  #include "TROOT.h"
  #include "TSystem.h"
  #include "TH1F.h"
  #include "TF1.h"
  #include "TFile.h"
  #include "TLegend.h"
  #include "TText.h"
  #include "TGraphErrors.h"
  #include "TGraphAsymmErrors.h"
  #include "TMultiGraph.h"
  #include "TCanvas.h"
  #include "TStyle.h"
  
  #include <vector>
  #include <algorithm>

  cout<<"Executing RooFit stuff..."<<endl;

  TCanvas *canvas = new TCanvas("canvas","canvas",900,100,600,500);

  //file containing data-driven templates
  TFile *fdata = TFile::Open("dataTemplates_Zeynep.root");
  //file containing real MC templates
  TFile *freal = TFile::Open("mcAllTemplates_newMED.root");

  //background template histo
  TH1F *hfake = (TH1F*)fdata->Get("h_fake_NUMBER");
  hfake->Print(); //Formerly h1

  //Real MC photon template histo
  TH1F *hreal = (TH1F*)freal->Get("H_real_NUMBER");
  //TH1F *hreal = (TH1F*)fdata->Get("h_num_NUMBER");
  hreal->Print(); //Formerly h2

  //Data histo
  TH1F *hData = (TH1F*)fdata->Get("h_NUMBER");
  hData->Print();

  //denominator histo
  TH1F *hnum = (TH1F*)fdata->Get("h_num_NUMBER");
  hnum->Print();

  //denominator histo
  TH1F *hden = (TH1F*)fdata->Get("h_denom_NUMBER");
  hden->Print();


  float numerator = hnum->Integral();
  float denominator = hden->Integral();

  //avoiding 0 entries in the histograms
  //fake and real mc histos are the most critical
  for(int bincount = 1; bincount <= hfake->GetNbinsX();bincount++){
    if(hfake->GetBinContent(bincount) == 0.) hfake->SetBinContent(bincount,1.e-6);
  }
  for(int bincount = 1; bincount <= hreal->GetNbinsX();bincount++){
    if(hreal->GetBinContent(bincount) == 0.) hreal->SetBinContent(bincount,1.e-6);
  }

  int ndataentries = hData->GetEntries();

  float sininmin = 0.;
  float sininmax = 0.03;

  //set variable
  //RooRealVar sinin("sinin","#sigma_{i#etai#eta}",sininmin,sininmax);
  RooRealVar sinin("sinin","#sigma_{i#etai#eta}",0,ndataentries);
  //sinin.setRange("sigrange",0,0.011);

  //set histograms pdfs
  RooDataHist faketemplate("faketemplate","fake template",sinin,hfake);
  RooHistPdf fakepdf("fakepdf","test hist fake pdf",sinin,faketemplate);

  RooDataHist realtemplate("realtemplate","real template",sinin,hreal);
  RooHistPdf realpdf("realpdf","test hist real pdf",sinin,realtemplate);

  //set data distribution to be fitted to
  RooDataHist data("data","data to be fitted to",sinin,hData);

  //variables that will contain real and fake estimates
  RooRealVar signum("signum","signum",0,ndataentries);
  RooRealVar fakenum("fakenum","fakenum",0,ndataentries);

  //set extended pdfs
  //RooExtendPdf extpdfsig("Signal","extpdfsig",realpdf,signum,"sigrange");
  //RooExtendPdf extpdffake("Background","extpdffake",fakepdf,fakenum,"sigrange");

  RooExtendPdf extpdfsig("Signal","extpdfsig",realpdf,signum);
  RooExtendPdf extpdffake("Background","extpdffake",fakepdf,fakenum);

  //composite model pdf
  RooAddPdf model("model","sig + background",RooArgList(extpdfsig,extpdffake));

  //make fit
  //model.fitTo(data,RooFit::Minos(),Range(0.008,0.03));
  model.fitTo(data,RooFit::Minos());

  //plot
  RooPlot *xframe = sinin.frame();
  xframe->SetTitle("");

  //gStyle->SetOptStat(0);
  //gStyle->SetOptFit(0);


  data.plotOn(xframe);
  model.plotOn(xframe,LineWidth(4),LineColor(38));
  model.plotOn(xframe,Components(extpdfsig),LineColor(2),LineStyle(2));
  model.plotOn(xframe,Components(extpdffake),LineColor(8),LineStyle(8));

/*
  data.plotOn(xframe);
  model.plotOn(xframe,LineWidth(4),LineColor(38));
  model.plotOn(xframe,Components(extpdffake),DrawOption("F"),LineColor(8),FillColor(8),FillStyle(3001),MoveToBack());
  model.plotOn(xframe,Components(extpdfsig),LineWidth(2),LineColor(2));
*/
  data.plotOn(xframe);

  xframe->Print();


  canvas->cd();
  xframe->Draw();
  gPad->SetLogy();
  gPad->SetTickx();
  gPad->SetTicky();
  TLegend *leg1 = new TLegend(0.600806,0.701271,0.885081,0.885593 );
   leg1->SetFillColor(kWhite);
   leg1->SetTextSize(0.03);
   leg1->SetHeader("templates LOWER<p_{T}<UPPER");
   leg1->AddEntry(xframe.findObject("h_data"), "data", "P");
   leg1->AddEntry(xframe->findObject("model_Norm[sinin]"), "real+fake fit to data", "L");
   leg1->AddEntry(xframe->findObject("model_Norm[sinin]_Comp[Signal]"), "real", "L");
   leg1->AddEntry(xframe->findObject("model_Norm[sinin]_Comp[Background]"), "fake", "L");
   leg1->Draw("same");



  //get estimates and their errors
  float fakevalue = fakenum.getValV();
  float fakeerrorhi = fakenum.getErrorHi();
  float fakeerrorlo = fakenum.getErrorLo();
  float fakeerrormax = max(fabs(fakeerrorhi),fabs(fakeerrorlo));
  float fakeerrormax_rel = fakeerrormax/fakevalue;
  TString fakeresults = TString::Format("Fake results %f +%f %f",fakevalue,fakeerrorhi,fakeerrorlo);

  float sigvalue = signum.getValV();
  float sigerrorhi = signum.getErrorHi();
  float sigerrorlo = signum.getErrorLo();
  float sigerrormax = max(fabs(sigerrorhi),fabs(sigerrorlo));
  TString sigresults = TString::Format("Signal results %f +%f %f",sigvalue,sigerrorhi,sigerrorlo);

  sinin.setRange("signal",0,0.011) ;
  RooAbsReal* igx_sig = extpdfsig.createIntegral(sinin,NormSet(sinin),Range("signal")) ;
  RooAbsReal* igx_fake = extpdffake.createIntegral(sinin,NormSet(sinin),Range("signal")) ;

  cout<<"sigvalue "<<sigvalue<<" sigerrormax "<<sigerrormax<<" sigerrormax/sigvalue "<<sigerrormax/sigvalue<<endl;
  cout<<"fakevalue "<<fakevalue<<" fakeerrormax "<<fakeerrormax<<" fakeerrormax/fakevalue "<<fakeerrormax/fakevalue<<endl;

  cout<<fakeresults.Data()<<endl;
  cout<<sigresults.Data()<<endl;

  float contamination = sigvalue;

  cout<<numerator<<" "<<denominator<<" "<<contamination<<endl;

  float fakerate = (numerator-contamination)/denominator; 
  float fakerate = (fakenum.getValV()*igx_fake.getValV())/denominator;

  float fakerateerror = fakerate * sqrt( (1./numerator) + (1./denominator) + ((sigerrormax/sigvalue)*(sigerrormax/sigvalue)) );
  float fakerateerrornew = (1./denominator)*sqrt(numerator+contamination+denominator*fakerate**2);

  
  float fake_temp_region = (fakenum.getValV()*igx_fake.getValV());
  float fake_temp_err = fakeerrormax_rel * fake_temp_region;

  float fake_ratio_err = fakerate * sqrt(  (fake_temp_err / fake_temp_region)**2 + (1./denominator) );

   cout<<"Fake rate results "<<fakerate<<" old err.: "<<fakerateerror<<" new err. "<<fakerateerrornew<< " fake_ratio_err: " << fake_ratio_err << std::endl;



  //stuff to be used from useRoofit.sh script
  cout<<"\n\n FAKE_RATE "<<fakerate<<" "<<fake_ratio_err<<"\n\n"<<endl;
  //canvas->SaveAs("template_NUMBER.pdf"); 
  canvas->SaveAs("template_NUMBER.pdf"); 
  canvas->SaveAs("template_NUMBER.root"); 


  cout<<"exiting Roofit..."<<endl; 

} 











