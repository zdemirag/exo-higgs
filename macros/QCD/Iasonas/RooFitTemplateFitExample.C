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
  TFile *fdata = TFile::Open("dataTemplates_newMED.root");
  //file containing real MC templates
  TFile *freal = TFile::Open("mcAllTemplates_newMED.root");

  //background template histo
  TH1F *h1 = (TH1F*)fdata->Get("h_fake_NUMBER");
  h1->Print();
  //Real MC photon template histo
  TH1F *h2 = (TH1F*)freal->Get("H_real_NUMBER");
  h2->Print();
  //Data histo
  TH1F *hData = (TH1F*)fdata->Get("h_num_NUMBER");
  hData->Print();
  //denominator histo
  TH1F *hnum = (TH1F*)fdata->Get("h_denom_NUMBER");
  hnum->Print();


  //avoiding 0 entries in the histograms
  //fake and real mc histos are the most critical
  for(int bincount = 1; bincount <= h1->GetNbinsX();bincount++){
    if(h1->GetBinContent(bincount) == 0.) h1->SetBinContent(bincount,1.e-6);
  }
  for(int bincount = 1; bincount <= h2->GetNbinsX();bincount++){
    if(h2->GetBinContent(bincount) == 0.) h2->SetBinContent(bincount,1.e-6);
  }

  int ndataentries = hData->GetEntries();

  float sininmin = 0.;
  float sininmax = 0.03;

  //set variable
  RooRealVar sinin("sinin","#sigma_{i#etai#eta}",sininmin,sininmax);
  sinin.setRange("sigrange",0.005,0.011);

  //set histograms pdfs
  RooDataHist faketemplate("faketemplate","fake template",sinin,h1);
  RooHistPdf fakepdf("fakepdf","test hist fake pdf",sinin,faketemplate);

  RooDataHist realtemplate("realtemplate","real template",sinin,h2);
  RooHistPdf realpdf("realpdf","test hist real pdf",sinin,realtemplate);

  //set data distribution to be fitted to
  RooDataHist data("data","data to be fitted to",sinin,hData);

  //variables that will contain real and fake estimates
  RooRealVar signum("signum","signum",0,ndataentries);
  RooRealVar fakenum("fakenum","fakenum",0,ndataentries);

  //set extended pdfs
  RooExtendPdf extpdfsig("Signal","extpdfsig",realpdf,signum,"sigrange");
  RooExtendPdf extpdffake("Background","extpdffake",fakepdf,fakenum,"sigrange");

  //composite model pdf
  RooAddPdf model("model","sig + background",RooArgList(extpdfsig,extpdffake));

  //make fit
  model.fitTo(data,RooFit::Minos());

  //plot
  RooPlot *xframe = sinin.frame();
  xframe->SetTitle("");

  //gStyle->SetOptStat(0);
  //gStyle->SetOptFit(0);

/*
  data.plotOn(xframe);
  model.plotOn(xframe,LineWidth(4),LineColor(38));
  model.plotOn(xframe,Components(extpdfsig),LineColor(2),LineStyle(2));
  model.plotOn(xframe,Components(extpdffake),LineColor(8),LineStyle(2));
*/

  data.plotOn(xframe);
  model.plotOn(xframe,LineWidth(4),LineColor(38));
  model.plotOn(xframe,Components(extpdffake),DrawOption("F"),LineColor(8),FillColor(8),FillStyle(3001),MoveToBack());
  model.plotOn(xframe,Components(extpdfsig),LineWidth(2),LineColor(2));
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
   leg1->AddEntry(xframe->findObject("model_Norm[sinin]_Comp[Background]"), "fake", "f");
   leg1->Draw("same");





  //get estimates and their errors
  float fakevalue = fakenum.getValV();
  float fakeerrorhi = fakenum.getErrorHi();
  float fakeerrorlo = fakenum.getErrorLo();
  float fakeerrormax = max(fabs(fakeerrorhi),fabs(fakeerrorlo));
  TString fakeresults = TString::Format("Fake results %f +%f %f",fakevalue,fakeerrorhi,fakeerrorlo);

  float sigvalue = signum.getValV();
  float sigerrorhi = signum.getErrorHi();
  float sigerrorlo = signum.getErrorLo();
  float sigerrormax = max(fabs(sigerrorhi),fabs(sigerrorlo));
  TString sigresults = TString::Format("Signal results %f +%f %f",sigvalue,sigerrorhi,sigerrorlo);

  cout<<"sigvalue "<<sigvalue<<" sigerrormax "<<sigerrormax<<" sigerrormax/sigvalue "<<sigerrormax/sigvalue<<endl;
  cout<<"fakevalue "<<fakevalue<<" fakeerrormax "<<fakeerrormax<<" fakeerrormax/fakevalue "<<fakeerrormax/fakevalue<<endl;

  cout<<fakeresults.Data()<<endl;
  cout<<sigresults.Data()<<endl;

  //find the bin corresponding to 0.011
  int binnr = 22;
  float numerator = hData->Integral(0,binnr);
  float denominator = hnum->Integral();
  float contamination = sigvalue;

  cout<<numerator<<" "<<denominator<<" "<<contamination<<endl;
  float fakerate = (numerator-contamination)/denominator;
  float fakerateerror = fakerate * sqrt( (1./numerator) + (1./denominator) + ((sigerrormax/sigvalue)*(sigerrormax/sigvalue)) );
  cout<<"Fake rate results "<<fakerate<<" "<<fakerateerror<<endl;

  //stuff to be used from useRoofit.sh script
  cout<<"\n\n FAKE_RATE "<<fakerate<<"\n\n"<<endl;
  //canvas->SaveAs("template_NUMBER.pdf");
  canvas->SaveAs("template_NUMBER.png");


  cout<<"exiting Roofit..."<<endl;

}











