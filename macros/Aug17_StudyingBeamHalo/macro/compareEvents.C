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

void compareEvents(){

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
  tdrStyle->SetPadTopMargin(0.07);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.13);
  tdrStyle->SetPadRightMargin(0.05);

  // For the Global title:
  //tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(35);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.045);
  // tdrStyle->SetTitleH(0); // Set the height of the title box
  // tdrStyle->SetTitleW(0); // Set the width of the title box
  tdrStyle->SetTitleX(0.15); // Set the position of the title box
  // tdrStyle->SetTitleY(0.985); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  tdrStyle->SetTitleBorderSize(0);

  // For the axis titles:
  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.04, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.5);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

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

  gROOT -> ForceStyle();

  tdrStyle->cd();

  vector<TString> cut;

  //Ratio
  // halo like
  cut.push_back("Pho_Pt > 45 && Pho_SigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.006 && sqrt(sigmaIPhiIPhi) < 0.0087 && passedDen==1 ");
  // good events
  cut.push_back("Pho_Pt > 45 && Pho_SigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.009 && passedDen==1 ");
  
  //QCD MC
  cut.push_back("Pho_Pt > 45 && Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.4442 && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001 && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 &&  Pho_R9<1.0 && MET > 40.");
  //ZG MC
  cut.push_back("Pho_Pt > 45 && Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.4442 && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001 && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 &&  Pho_R9<1.0 && MET > 40.");



//Yields
//halo like
// cut.push_back("Pho_Pt > 45 && Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.4442 && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.006 && sqrt(sigmaIPhiIPhi) < 0.0087 && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 &&  Pho_R9<1.0 && MET >40.");
  // good events
//  cut.push_back("Pho_Pt > 45 && Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.4442 && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.009 && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 &&  Pho_R9<1.0 && MET > 40.");



  float binsize = 100;
  float binup = 0.02;
  float binlow = 0;
  //TString var = "sqrt(sigmaIPhiIPhi)";
  TString var = "sigmaIEtaIEta";

  const int n = 4;
  TString location = "../root_file/";
  TString filename[n] = {"QCD_ratio_withMIP","QCD_ratio_withMIP","QCD_MC","ZGMC"};
  TString naming[n] = {"0.006 < #sigma_{i#phii#phi} < 0.0087","#sigma_{i#phii#phi} > 0.09", "QCD MC", "Z#nu#nu#gamma MC"};

  TFile *f[n];
  TH1F *h[n]; 

  gStyle->SetOptStat(kFALSE);

  for(int file = 0; file<n; file++){
  
      f[file] = new TFile(location+"higgsHistograms_"+filename[file]+".root","READ");
      f[file]->cd("Analyzer");
  
      h[file]  = new TH1F("h_"+naming[file],"h_"+naming[file] ,binsize ,binlow ,binup);
      if(file < 2){
          AnalyzerTree->Draw("Pho_SigmaIEtaIEta>>h_"+naming[file],cut[file],"");
      }
      else
          AnalyzerTree->Draw(var+">>h_"+naming[file],cut[file],"");
      std::cout << "File: "<< naming[file] <<" NEvents: " << h[file]->Integral() << std::endl;
      h[file]->Scale(1./h[file]->Integral());

      std::cout << "\n" << std::endl;
      

  }
  
  TLegend *leg = new TLegend(0.5879195,0.7482517,0.9496644,0.9300699,NULL,"brNDC");       
  TCanvas *c = new TCanvas("c","c",600,700);

  c->SetLogy();
  c->cd();
  for (int k = 0; k<n; k++){


      h[k]->GetYaxis()->SetTitle("Events");
      h[k]->GetXaxis()->SetTitle(var);

      h[k]->SetMarkerColor(k);
      if(k==0) h[k]->SetLineColor(4);
      else h[k]->SetLineColor(k);
      h[k]->SetLineWidth(2);

      h[k]->SetTitle("For Ratio Den Selection");
      
      if(k==0) h[k] -> Draw("");
      else h[k]->Draw("same");
  
      leg->AddEntry(h[k],naming[k],"l");
      leg->SetFillColor(0);
      leg->SetShadowColor(0);

  }

  leg->Draw();
      
  c->SaveAs("sieie_ratio_den.pdf");
      
}
