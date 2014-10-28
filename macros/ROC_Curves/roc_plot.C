#include "TH1.h"
#include "TH1F.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TPostScript.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TPaveText.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;


void roc_plot(){

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
  tdrStyle->SetPadTopMargin(0.05);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.13);
  tdrStyle->SetPadRightMargin(0.05);

  // For the Global title:
  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);

  // For the axis titles:
  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.05);

  // For the axis labels:
  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.05, "XYZ");

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
  
  gROOT -> ForceStyle();
  
  tdrStyle->cd();
  
  gStyle->SetOptStat(0111);
  gStyle->SetOptFit(1111);
  

  int bkg = 787623.93;
  int sig = 9313.;
  
  const int n = 5;
  
  //minmet
  //Double_t cut[n] = {10,15,20,25,30,35,40,45,50,55} ;
  
  //pvalue
  //Double_t cut[n] = {0,0.5,1,1.5,2,2.5,3,3.5,4.0};

  //metsig
  Double_t cut[n] = {5,10,15,20,25};

  //minmet
  //Double_t sensitivity_bkg_n[n]={660142.26/bkg,551026.78/bkg,444547.21/bkg,354649.92/bkg,283093.63/bkg ,227934.73/bkg ,187564.23/bkg,158191.46/bkg,103089.49/bkg,68423.49/bkg};
  //Double_t sensitivity_sig_n[n]={9274./sig ,9233./sig,9172./sig,9089./sig,8995./sig,8870./sig,8718./sig,8539./sig,7398./sig,6497./sig};

  //pvalue
  //Double_t sensitivity_bkg_n[n]={787623.93/bkg,290416.84/bkg, 166165.65/bkg, 87792.43/bkg, 49447.43/bkg, 30536.76/bkg, 19869.09/bkg, 13705.00/bkg, 10075.21/bkg};
  //Double_t sensitivity_sig_n[n]={9313./sig,9005./sig, 8499./sig,7547./sig,6508./sig,5579./sig,4832./sig,4213./sig,3649./sig};

  //metsig
  Double_t sensitivity_bkg_n[n]={579088.98/bkg,94310.14/bkg, 13034.68/bkg,2503.93./bkg,756.13./bkg};
  Double_t sensitivity_sig_n[n]={9045./sig,7492./sig,5899./sig,4654./sig,3726./sig};

  sensitivity_bkg = new TGraph(n,cut,sensitivity_bkg_n);
  sensitivity_sig = new TGraph(n,cut,sensitivity_sig_n);
  
  //Double_t xdummy[2] = {10,55};
  //Double_t xdummy[2] = {-0.1,3};
  Double_t xdummy[2] = {0,25};
  Double_t ydummy[2] = {0.0,1.0};
  
  dummy = new TGraph(2,xdummy,ydummy);
  dummy->SetLineColor(0);
  dummy->SetLineWidth(0);
  dummy->SetMarkerColor(0);
  dummy->SetMarkerSize(0);
  dummy->Draw("AP*");
  dummy->GetYaxis()->SetTitle("Efficiency");
  //dummy->GetXaxis()->SetTitle("Minimized #slash{E}_{T} Cut [GeV]");
  //dummy->GetXaxis()->SetTitle("|Log10(P_{#Chi^{2}})|");
  dummy->GetXaxis()->SetTitle("Met Significance");
  dummy->GetYaxis()->SetLabelSize(0.04);
  dummy->GetXaxis()->SetLabelSize(0.04);
  
  sensitivity_bkg->SetLineColor(2);
  sensitivity_bkg->SetMarkerColor(2);
  
  sensitivity_sig->SetLineColor(4);
  sensitivity_sig->SetMarkerColor(4);
  
  sensitivity_bkg->Draw("LPSame");
  sensitivity_sig->Draw("LPSame");

  //legend = new TLegend(.70,.70,.90,.90,"Final Selection e/#mu+jets");
  legend = new TLegend(0.1845638,0.2027972,0.3674497,0.3024476,NULL,"brNDC");

  legend->AddEntry(sensitivity_bkg, "#gamma + Jets", "lp");
  legend->AddEntry(sensitivity_sig, "Z (#nu#nu) #gamma" , "lp");
  
  legend->SetShadowColor(0);
  legend->SetFillColor(0);
  legend->SetLineColor(0);
  legend->Draw("Same");
  
  latex2 = new TLatex();
  latex2->SetNDC();
  latex2->SetTextSize(0.04);
  latex2->SetTextAlign(31); 
  latex2->DrawLatex(0.87, 0.96, "CMS Preliminary, #sqrt{s} = 8 TeV");

  
}
