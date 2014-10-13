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

void FakeRate() {


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
  tdrStyle->SetTitleYOffset(1.5);

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

  // Postscript options:
  tdrStyle->SetPaperSize(20.,20.);
  tdrStyle->SetPalette(1);
  
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
  
  int binsize = 10;
  int binlow = 30;
  int binup = 130;

  TString cut_Iasonas_n = "pfmet_pt < 40. && ph_N_Pt   > 0. && ph_N_sinin < 0.011";
  TString cut_Iasonas_d = "pfmet_pt < 40. && ph_DLU_Pt > 0. ";

  TString cut_Zeynep_n_new = "passedNum && Pho_Pt > 0. && Pho_SigmaIEtaIEta < 0.011 && MET>40";
  TString cut_Zeynep_d_new = "passedDen && Pho_Pt > 0. && MET>40";

  TFile *f_Iasonas = new TFile("Iasonas_Data.root","READ");
  f_Iasonas->cd("Analyzer");
  TH1F *h_num_I  = new TH1F("h_num_I","h_num_I" ,binsize ,binlow ,binup);
  TH1F *h_den_I  = new TH1F("h_den_I","h_den_I" ,binsize ,binlow ,binup);

  AnalyzerTree->Draw("ph_N_Pt>>h_num_I",cut_Iasonas_n,"goff");
  AnalyzerTree->Draw("ph_DLU_Pt>>h_den_I",cut_Iasonas_d,"goff");
  
  TH1F *h_raw_I = (TH1F*)h_num_I->Clone("h_raw_I");
  h_raw_I->Divide(h_den_I);

  //TFile *f_Zeynep = new TFile("higgsHistograms_trigger_QCD.root","READ");
  TFile *f_Zeynep = new TFile("higgsHistograms_Free_MET.root","READ");

  f_Zeynep->cd("Analyzer");
  TH1F *h_num_Z  = new TH1F("h_num_Z","h_num_Z" ,binsize ,binlow ,binup);
  TH1F *h_den_Z  = new TH1F("h_den_Z","h_den_Z" ,binsize ,binlow ,binup);
  
  AnalyzerTree->Draw("Pho_Pt>>h_num_Z",cut_Zeynep_n_new,"goff");
  AnalyzerTree->Draw("Pho_Pt>>h_den_Z",cut_Zeynep_d_new,"goff");
 
  TH1F *h_raw_Z = (TH1F*)h_num_Z->Clone("h_raw_Z");
  h_raw_Z->Divide(h_den_Z);

  //lepton veto
  TH1F *h_num_Z_l  = new TH1F("h_num_Z_l","h_num_Z_l" ,binsize ,binlow ,binup);
  TH1F *h_den_Z_l  = new TH1F("h_den_Z_l","h_den_Z_l" ,binsize ,binlow ,binup);
  AnalyzerTree->Draw("Pho_Pt>>h_num_Z_l",cut_Zeynep_n_new+" && elVeto0==0 && muVeto0==0","goff");
  AnalyzerTree->Draw("Pho_Pt>>h_den_Z_l",cut_Zeynep_d_new+" && elVeto0==0 && muVeto0==0" ,"goff");
 
  TH1F *h_raw_Z_l = (TH1F*)h_num_Z_l->Clone("h_raw_Z_l");
  h_raw_Z_l->Divide(h_den_Z_l);

  //jet count
  TH1F *h_num_Z_j  = new TH1F("h_num_Z_j","h_num_Z_j" ,binsize ,binlow ,binup);
  TH1F *h_den_Z_j  = new TH1F("h_den_Z_j","h_den_Z_j" ,binsize ,binlow ,binup);
  AnalyzerTree->Draw("Pho_Pt>>h_num_Z_j",cut_Zeynep_n_new+" && njet>0","goff");
  AnalyzerTree->Draw("Pho_Pt>>h_den_Z_j",cut_Zeynep_d_new+" && njet>0","goff");
 
  TH1F *h_raw_Z_j = (TH1F*)h_num_Z_j->Clone("h_raw_Z_j");
  h_raw_Z_j->Divide(h_den_Z_j);

  TCanvas* c1 =  new TCanvas("c1","c1",700,600);
  c1->cd();

  h_raw_I->SetTitle("Raw Fake Rate");
  h_raw_I->GetYaxis()->SetTitle("Raw Fake Rate");
  h_raw_I->GetXaxis()->SetTitle("Offline Photon Pt [GeV]");
  h_raw_I->Draw();
  h_raw_I->GetYaxis()->SetRangeUser(0.0,15);

  h_raw_Z->SetLineColor(2);
  h_raw_Z->Draw("same");

  h_raw_Z_l->SetLineColor(4);
  h_raw_Z_l->Draw("same");

  h_raw_Z_j->SetLineColor(6);
  h_raw_Z_j->Draw("same");


  gStyle->SetOptStat(kFALSE);
  
  TLegend *leg = new TLegend(0.6879195,0.7482517,0.9496644,0.9300699,NULL,"brNDC");
  leg->AddEntry(h_raw_I, "Iasonas Raw Fake Rate" ,"l");
  leg->AddEntry(h_raw_Z, "Zeynep Raw Fake Rate" ,"l");
  leg->AddEntry(h_raw_Z_l, "Zeynep Raw Fake Rate + no leptons" ,"l");
  leg->AddEntry(h_raw_Z_j, "Zeynep Raw Fake Rate + jet > 1" ,"l");

  leg->SetFillColor(0);
  leg->SetShadowColor(0);
  leg->Draw();
  
  

}
