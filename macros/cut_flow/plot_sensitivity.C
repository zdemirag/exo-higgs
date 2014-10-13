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


void plot_sensitivity() {
      
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
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
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
  // tdrStyle->SetHistFillColor(1);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
  // tdrStyle->SetNumberContours(Int_t number = 20);

  tdrStyle->SetEndErrorSize(2);
  //  tdrStyle->SetErrorMarker(20);
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
  // tdrStyle->SetDateX(Float_t x = 0.01);
  // tdrStyle->SetDateY(Float_t y = 0.01);

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
  // tdrStyle->SetTitleH(0); // Set the height of the title box
  // tdrStyle->SetTitleW(0); // Set the width of the title box
  // tdrStyle->SetTitleX(0); // Set the position of the title box
  // tdrStyle->SetTitleY(0.985); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  // tdrStyle->SetTitleBorderSize(2);

  // For the axis titles:
  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.05);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

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
  // tdrStyle->SetLineScalePS(Float_t scale = 3);
  // tdrStyle->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle->SetHeaderPS(const char* header);
  // tdrStyle->SetTitlePS(const char* pstitle);

   //tdrStyle->SetBarOffset(Float_t baroff = 0.5);
   //tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
   //tdrStyle->SetPaintTextFormat(const char* format = "g");
   tdrStyle->SetPalette(1);
   //tdrStyle->SetTimeOffset(Double_t toffset);
   //tdrStyle->SetHistMinimumZero(kTRUE);


   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   tdrStyle->SetNumberContours(NCont);


   //TLatex *lab = new TLatex(0.70,0.85, "CMS 2008");
   //lab->SetNDC();
   //lab->SetTextFont(42);
   //lab->SetTextSize(0.05);
   //lab->Draw("same");

   gROOT -> ForceStyle();

   tdrStyle->cd();

   gStyle->SetOptStat(0111);
   gStyle->SetOptFit(1111);


   Double_t mtcut[5] = {80,90,100,110,120};

   Double_t sensitivity_phopt45[5] = {0.051,0.053,0.055,0.053,0.042 };
   Double_t sensitivity_phopt50[5] = {0.054,0.055,0.056,0.053,0.041 };
   Double_t sensitivity_phopt55[5] = {0.047,0.048,0.049,0.047,0.037 };

   Double_t sensitivity_phopt45_p[5] = {0.0621531,0.0640222,0.0657086,0.0636271,0.0500836};
   Double_t sensitivity_phopt50_p[5] = {0.0630204,0.0644059,0.0653491,0.0621014,0.048605};
   Double_t sensitivity_phopt55_p[5] = {0.0544277,0.0554049,0.0563004,0.0538488,0.0429858};

   Double_t sensitivity_phopt45_t[5] = {0.0477583,0.0480759,0.0507336,0.0496435,0.0393602};
   Double_t sensitivity_phopt50_t[5] = {0.0503171,0.0515073,0.0524819,0.0498969,0.0386348};
   Double_t sensitivity_phopt55_t[5] = {0.0438532,0.0447883,0.0455329,0.043715,0.0344345};


   sensitivity_phopt45_vs_mt = new TGraph(5,mtcut,sensitivity_phopt45);
   sensitivity_phopt50_vs_mt = new TGraph(5,mtcut,sensitivity_phopt50);
   sensitivity_phopt55_vs_mt = new TGraph(5,mtcut,sensitivity_phopt55);


   sensitivity_phopt45_vs_mt_p = new TGraph(5,mtcut,sensitivity_phopt45_p);
   sensitivity_phopt50_vs_mt_p = new TGraph(5,mtcut,sensitivity_phopt50_p);
   sensitivity_phopt55_vs_mt_p = new TGraph(5,mtcut,sensitivity_phopt55_p);

   
   sensitivity_phopt45_vs_mt_t = new TGraph(5,mtcut,sensitivity_phopt45_t);
   sensitivity_phopt50_vs_mt_t = new TGraph(5,mtcut,sensitivity_phopt50_t);
   sensitivity_phopt55_vs_mt_t = new TGraph(5,mtcut,sensitivity_phopt55_t);


   Double_t xdummy[2] = {70,130};
   Double_t ydummy[2] = {0.01,0.3};

   dummy = new TGraph(2,xdummy,ydummy);
   dummy->SetLineColor(0);
   dummy->SetLineWidth(0);
   dummy->SetMarkerColor(0);
   dummy->SetMarkerSize(0);
   dummy->Draw("AP*");
   dummy->GetYaxis()->SetTitle("S/sqrt(S+B)");
   dummy->GetXaxis()->SetTitle("M_{T} Cut [GeV]");
   dummy->GetYaxis()->SetLabelSize(0.04);
   dummy->GetXaxis()->SetLabelSize(0.04);

   sensitivity_phopt45_vs_mt->SetLineColor(6);
   sensitivity_phopt45_vs_mt->SetMarkerColor(6);

   sensitivity_phopt45_vs_mt_t->SetLineColor(6);
   sensitivity_phopt45_vs_mt_t->SetMarkerColor(6);
   sensitivity_phopt45_vs_mt_t->SetLineStyle(2);

   sensitivity_phopt45_vs_mt_p->SetLineColor(6);
   sensitivity_phopt45_vs_mt_p->SetMarkerColor(6);
   sensitivity_phopt45_vs_mt_p->SetLineStyle(3);
   
   sensitivity_phopt50_vs_mt->SetLineColor(8);
   sensitivity_phopt50_vs_mt->SetMarkerColor(8);

   sensitivity_phopt50_vs_mt_t->SetLineColor(8);
   sensitivity_phopt50_vs_mt_t->SetMarkerColor(8);
   sensitivity_phopt50_vs_mt_t->SetLineStyle(2);


   sensitivity_phopt50_vs_mt_p->SetLineColor(8);
   sensitivity_phopt50_vs_mt_p->SetMarkerColor(8);
   sensitivity_phopt50_vs_mt_p->SetLineStyle(3);

   sensitivity_phopt55_vs_mt->SetLineColor(2);
   sensitivity_phopt55_vs_mt->SetMarkerColor(2);

   sensitivity_phopt55_vs_mt_t->SetLineColor(2);
   sensitivity_phopt55_vs_mt_t->SetMarkerColor(2);
   sensitivity_phopt55_vs_mt_t->SetLineStyle(2);

   sensitivity_phopt55_vs_mt_p->SetLineColor(2);
   sensitivity_phopt55_vs_mt_p->SetMarkerColor(2);
   sensitivity_phopt55_vs_mt_p->SetLineStyle(3);

   sensitivity_phopt45_vs_mt->Draw("LPSame");
   sensitivity_phopt55_vs_mt->Draw("LPSame");
   sensitivity_phopt50_vs_mt->Draw("LPSame");

   sensitivity_phopt45_vs_mt_t->Draw("LPSame");
   sensitivity_phopt55_vs_mt_t->Draw("LPSame");
   sensitivity_phopt50_vs_mt_t->Draw("LPSame");

   sensitivity_phopt45_vs_mt_p->Draw("LPSame");
   sensitivity_phopt55_vs_mt_p->Draw("LPSame");
   sensitivity_phopt50_vs_mt_p->Draw("LPSame");

   //legend = new TLegend(.70,.70,.90,.90,"Final Selection e/#mu+jets");
   legend = new TLegend(.60,.60,.90,.90);
   legend->AddEntry(sensitivity_phopt45_vs_mt, "Medium Id photon p_{T} > 45 GeV, CSV", "lp");
   legend->AddEntry(sensitivity_phopt50_vs_mt, "Medium Id photon p_{T} > 50 GeV, CSV" , "lp");
   legend->AddEntry(sensitivity_phopt55_vs_mt, "Medium Id photon p_{T} > 55 GeV, CSV", "lp");
   legend->AddEntry(sensitivity_phopt45_vs_mt_t, "Tight Id photon p_{T} > 45 GeV, CSV", "lp");
   legend->AddEntry(sensitivity_phopt50_vs_mt_t, "Tight Id photon p_{T} > 50 GeV, CSV" , "lp");
   legend->AddEntry(sensitivity_phopt55_vs_mt_t, "Tight Id photon p_{T} > 55 GeV, CSV", "lp");
   legend->AddEntry(sensitivity_phopt45_vs_mt_p, "Medium Id photon p_{T} > 45 GeV, +Pixel", "lp");
   legend->AddEntry(sensitivity_phopt50_vs_mt_p, "Medium Id photon p_{T} > 50 GeV, +Pixel" , "lp");
   legend->AddEntry(sensitivity_phopt55_vs_mt_p, "Medium Id photon p_{T} > 55 GeV, +Pixel", "lp");

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
