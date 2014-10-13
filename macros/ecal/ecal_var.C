#include <TFile.h>
#include <TH1F.h>
#include <THStack.h>
#include <iostream>
#include <TInterpreter.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TLegend.h>
#include <iomanip>
#include <string>
#include <vector>
#include <TColor.h>
#include <TStyle.h>

void ecal_var(){

  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

  // For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);

  // For the Pad:
  tdrStyle->SetPadBorderMode(0);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(true);
  tdrStyle->SetPadGridY(true);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

  // For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);

  // For the histo:
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  tdrStyle->SetEndErrorSize(2);
  tdrStyle->SetErrorX(0.);

  tdrStyle->SetMarkerStyle(20);

  //For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

  //For the date:
  tdrStyle->SetOptDate(0);

  // For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat("emr"); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);
  // tdrStyle->SetStatStyle(Style_t style = 1001);
  // tdrStyle->SetStatX(Float_t x = 0);
  // tdrStyle->SetStatY(Float_t y = 0);

  // Margins:
  tdrStyle->SetPadTopMargin(0.07);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.13);
  tdrStyle->SetPadRightMargin(0.05);

  // For the Global title:
  tdrStyle->SetTitleFont(35);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.045);
  tdrStyle->SetTitleX(0.15); // Set the position of the title box
  tdrStyle->SetTitleBorderSize(0);

  // For the axis titles:
  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.04, "XYZ");
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.05);

  // For the axis labels:
  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.03, "XYZ");

  // For the axis:
  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

  // Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

  const Int_t NRGBs = 5;
  const Int_t NCont = 255;

  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  tdrStyle->SetNumberContours(NCont);

  gROOT -> ForceStyle();

  tdrStyle->cd();

  std::vector<TString> name;
  std::vector<float> nbins;
  std::vector<float> low;
  std::vector<float> high;

  name.push_back("Pho_Pt");
  nbins.push_back(100); low.push_back(0); high.push_back(200);

  name.push_back("sigmaIEtaIEta");
  nbins.push_back(100); low.push_back(0); high.push_back(0.02);

  name.push_back("sigmaIEtaIPhi");
  nbins.push_back(100); low.push_back(-0.002); high.push_back(0.002);

  name.push_back("sigmaIPhiIPhi");
  nbins.push_back(100); low.push_back(0); high.push_back(0.001);

  name.push_back("scEtaWidth");
  nbins.push_back(100); low.push_back(0); high.push_back(0.02);

  name.push_back("scPhiWidth");
  nbins.push_back(10); low.push_back(0); high.push_back(0.2);

  name.push_back("e1x3");
  nbins.push_back(250); low.push_back(0); high.push_back(250);

  name.push_back("e1x5");
  nbins.push_back(250); low.push_back(0); high.push_back(250);

  name.push_back("e2x2");
  nbins.push_back(250); low.push_back(0); high.push_back(250);

  name.push_back("e2x5");
  nbins.push_back(250); low.push_back(0); high.push_back(250);

  name.push_back("e2x5Max");
  nbins.push_back(250); low.push_back(0); high.push_back(250);

  name.push_back("e5x5");
  nbins.push_back(250); low.push_back(0); high.push_back(250);

  name.push_back("e1x3/e5x5");
  nbins.push_back(100); low.push_back(0); high.push_back(1);

  name.push_back("e1x5/e5x5");
  nbins.push_back(100);low.push_back(0); high.push_back(1);

  name.push_back("e2x2/e5x5");
  nbins.push_back(100);low.push_back(0); high.push_back(1);

  name.push_back("e2OverE5");
  nbins.push_back(100); low.push_back(0.5); high.push_back(1.5);

  name.push_back("scRawEnergy");
  nbins.push_back(300); low.push_back(0); high.push_back(300);

  name.push_back("scPSEnergy");
  nbins.push_back(100); low.push_back(0); high.push_back(0.03);

  name.push_back("scEnergy");
  nbins.push_back(300); low.push_back(0); high.push_back(300);

  name.push_back("mipChi2");
  nbins.push_back(300); low.push_back(0); high.push_back(30);

  name.push_back("mipTotEn");
  nbins.push_back(300); low.push_back(0); high.push_back(30);

  name.push_back("mipSlope");
  nbins.push_back(100); low.push_back(-0.25); high.push_back(0.25);

  name.push_back("mipIntercept");
  nbins.push_back(120); low.push_back(-30); high.push_back(30);

  name.push_back("mipNHitCone");
  nbins.push_back(200); low.push_back(0); high.push_back(100);

  name.push_back("mipIsHalo");
  nbins.push_back(2); low.push_back(0); high.push_back(1);

  name.push_back("roundness");
  nbins.push_back(100); low.push_back(0); high.push_back(1);

  name.push_back("angle");
  nbins.push_back(200); low.push_back(0); high.push_back(2);

  name.push_back("sMin");
  nbins.push_back(100); low.push_back(0); high.push_back(1);

  name.push_back("sMaj");
  nbins.push_back(1000); low.push_back(0); high.push_back(10);

  name.push_back("LICTD");
  nbins.push_back(100); low.push_back(-50); high.push_back(50);

  name.push_back("seedCrystalEnergy");
  nbins.push_back(300); low.push_back(0); high.push_back(300);

  name.push_back("seedCrystalTime");
  nbins.push_back(200); low.push_back(-2); high.push_back(2);

  name.push_back("minDR");
  nbins.push_back(500); low.push_back(0); high.push_back(5);

  const int cutno = 0;
  std::vector<TString> cut;
  cut.push_back("numGoodPhotons==1");    
  const int size = name.size();

  TCanvas* c[size];
  
  for(int i = 0; i<size; i++){

    c[i]  = new TCanvas(name[i],name[i],600,600);
    
    gStyle->SetOptStat(kFALSE);


    //TFile *f_data = new TFile("higgsHistograms_partOfData.root","READ");
    TFile *f_data = new TFile("../../rootFiles/higgsHistograms_SinglePhotonParked.root","READ");
    f_data->cd("Analyzer");
    TH1F *h_data =  new TH1F("h_data","h_data",nbins[i],low[i],high[i]);
    h_data->Sumw2();
    AnalyzerTree->Draw(name[i]+">>h_data",cut[cutno],"");
    h_data->Scale(1./h_data->Integral());
    h_data->SetTitle(name[i]);
  
    TFile *f_sig = new TFile("../../rootFiles/higgsHistograms_susyHiggs.root","READ");
    f_sig->cd("Analyzer");  
    TH1F *h_sig  = new TH1F("h_sig","h_sig",nbins[i],low[i],high[i]); 
    h_sig->Sumw2();
    AnalyzerTree->Draw(name[i]+">>h_sig",cut[cutno],"");
    h_sig->Scale(1./h_sig->Integral());

    h_sig->SetMarkerColor(2);
    h_sig->SetMarkerSize(0.2);
    h_sig->SetLineColor(2);
    h_sig->SetLineWidth(2);
    h_sig->SetLineStyle(1);

    TFile *f_efake = new TFile("../../rootFiles/higgsHistograms_efake_dd.root","READ");
    f_efake->cd("Analyzer");
    TH1F *h_efake  = new TH1F("h_efake","h_efake",nbins[i],low[i],high[i]);
    h_efake->Sumw2();
    AnalyzerTree->Draw(name[i]+">>h_efake",cut[cutno],"");
    h_efake->Scale(1./h_efake->Integral());
   
    h_efake->SetMarkerColor(4);
    h_efake->SetMarkerSize(0.2);
    h_efake->SetLineColor(4);
    h_efake->SetLineWidth(2);
    h_efake->SetLineStyle(1);


    TFile *f_jfake = new TFile("../../rootFiles/higgsHistograms_qcd_dd.root","READ");
    f_jfake->cd("Analyzer");
    TH1F *h_jfake  = new TH1F("h_jfake","h_jfake",nbins[i],low[i],high[i]);
    h_jfake->Sumw2();
    AnalyzerTree->Draw(name[i]+">>h_jfake",cut[cutno],"");
    h_jfake->Scale(1./h_jfake->Integral());
   
    h_jfake->SetMarkerColor(8);
    h_jfake->SetMarkerSize(0.2);
    h_jfake->SetLineColor(8);
    h_jfake->SetLineWidth(2);
    h_jfake->SetLineStyle(1);
    
    h_data->Draw("pex0");
    h_sig->Draw("SAMEHIST");
    h_efake->Draw("SAMEHIST");
    h_jfake->Draw("SAMEHIST");


    TLegend *leg = new TLegend(0.6879195,0.7482517,0.9496644,0.9300699,NULL,"brNDC");

    leg->AddEntry(h_data,"Single Photon Data","p"); 
    leg->AddEntry(h_sig,"H Susy Signal","l");//"DM_M10_V x 10000","l");
    leg->AddEntry(h_efake,"E Fake Bkg","l");
    leg->AddEntry(h_jfake,"J Fake Bkg","l");
    leg->SetFillColor(0);
    leg->SetShadowColor(0);
    leg->Draw();


    c[i]->SetLogy();
    c[i]->SaveAs("plots/"+ name[i]+".pdf");
  

  }
}

