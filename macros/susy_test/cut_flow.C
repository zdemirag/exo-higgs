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

void cut_flow(){

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
  tdrStyle->SetTitleYOffset(1.05);
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

  //TH1::AddDirectory(kFALSE);



  const int cutno = 0;
  std::vector<TString> cut;

  //cut.push_back("mu_pt_leading>0. && mu_pt_trailing>0. && (hltpho || hltphoid)");
  cut.push_back("mu_pt_leading>0. && mu_pt_trailing>0");

  //cut.push_back("el_pt_leading>0. && el_pt_trailing>0. && (hltpho || hltphoid)");
  //cut.push_back("el_pt_leading>0. && el_pt_trailing>0");

  
  vector<TString> name;
  // name.push_back("Pho_Pt");
  //name.push_back( "MET");
  
  //name.push_back( "el_pt_leading");
  //name.push_back( "el_pt_trailing");
  //name.push_back( "m_ee");
 
  //name.push_back( "mu_pt_leading");
  //name.push_back( "mu_pt_trailing");
  name.push_back( "m_mm"); 

  float scaleup =5000;
  TString location = "";

  //const int nbins = 19;
  //float bins[nbins+1] = {30.,35.,40.,45.,50., 55., 60., 65., 70., 75., 80., 85., 90., 95., 100., 125., 150., 200., 250., 300.};

  const int size = name.size();
  TCanvas *c[size];
  gStyle->SetOptStat(kFALSE);

  for(int i = 0; i<name.size();i++){
    c[i] = new TCanvas("c"+name[i],"c"+name[i],680,600);


    TFile *f_data = new TFile(location+"higgsHistograms_SinglePhotonParked_susy.root","READ");
    f_data->cd("Analyzer");
    
    TH1F *h_data  = new TH1F("h_data","h_data" ,100 ,2.4,4);
    //TH1F *h_data  = new TH1F("h_data","h_data" ,100 ,10,210);
    //TH1F *h_data  = new TH1F("h_data","h_data" ,10 ,7.9, 10.9);

    h_data->Sumw2();
    AnalyzerTree->Draw(name[i]+">>h_data",cut[cutno],"");
    std::cout << "Data: " << h_data->Integral() << std::endl;
    c[i]->cd();
    //c[i]->SetLogy();
    h_data->GetYaxis()->SetTitle("Events");
    h_data->GetXaxis()->SetTitle(name[i]+" [GeV]");
    h_data->SetTitle("");
    h_data->Draw();
  }

}


//cut.push_back("Pho_Pt > 30. && conversionVeto==1 && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && sigmaIEtaIEta < 0.011 && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001 ");
  //cut.push_back("Pho_Pt > 30. && conversionVeto==1 && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && el_pt_leading>0. && mu_pt_leading>0. ");
  //cut.push_back("Pho_Pt > 30. && conversionVeto==1 && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && mu_pt_leading>0. && mu_pt_trailing>0.");
  //cut.push_back("mu_pt_leading>0. && mu_pt_trailing>0.");
  //cut.push_back("Pho_Pt > 30. && conversionVeto==1 && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && el_pt_leading>0. && el_pt_trailing>0.");
  //TString e_m = "TMath::Sqrt(2*mu_pt_leading*el_pt_leading * (TMath::CosH(mu_eta_leading - el_eta_leading) - TMath::Cos(mu_phi_leading - el_phi_leading) ) )";
  //TString e_m = "TMath::Sqrt(2*mu_pt_leading*mu_pt_trailing * (TMath::CosH(mu_eta_leading - mu_eta_trailing) - TMath::Cos(mu_phi_leading-mu_phi_trailing) ))";
  //TString e_m = "TMath::Sqrt(2*el_pt_leading*el_pt_trailing * (TMath::CosH(el_eta_leading - el_eta_trailing) - TMath::Cos(el_phi_leading-el_phi_trailing) ))";
  //TString e_m = "(TLorentzVector::SetPtEtaPhiM(mu_pt_leading,mu_eta_leading,mu_phi_leading, 0.1057) + TLorentzVector::SetPtEtaPhiM(el_pt_leading,el_eta_leading,el_phi_leading,0.000510)).M()";
