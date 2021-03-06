#include "TMath.h"

void trigeff(){

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


  //TFile *f = new TFile("higgsHistograms_trigger_all.root","READ");
  TFile *f = new TFile("~/lnwork/lowEt_monophoton/CMSSW_5_3_4/src/RootFiles/data.root","READ");

  //Float_t bins[] = { 40, 45, 60, 80, 120, 500};
  //TH1F *den_data_id_vspt = new TH1F("den_data_id_vspt","den_data_id_vspt",5,bins);
  //TH1F *num_data_id_vspt = new TH1F("num_data_id_vspt","num_data_id_vspt",5,bins);
  TH1F *den_data_id_vspt = new TH1F("den_data_id_vspt","den_data_id_vspt",100,0,500);
  TH1F *num_data_id_vspt = new TH1F("num_data_id_vspt","num_data_id_vspt",100,0,500);
  eff_data_id_vspt= new TGraphAsymmErrors;
  den_data_id_vspt->Sumw2();
  num_data_id_vspt->Sumw2();
    
  //TH1F *den_data_met = new TH1F("den_data_met","den_data_met",5,bins);
  //TH1F *num_data_met = new TH1F("num_data_met","num_data_met",5,bins);
  TH1F *den_data_met = new TH1F("den_data_met","den_data_met",250,0,500);
  TH1F *num_data_met = new TH1F("num_data_met","num_data_met",250,0,500);
  eff_data_met= new TGraphAsymmErrors;
  den_data_met->Sumw2();
  num_data_met->Sumw2();

  TString jet = " && Pho_Pt>35";
  //TString jet = " && Pho_Pt>35 && n_jets_mva_loose==0";
  //TString jet = " && Pho_Pt>35 && n_jets_mva_loose>0";
  
 
  AnalyzerTree->Draw("Pho_Pt>>den_data_id_vspt","hltmatched_Pho==1 && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001 && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 &&  Pho_R9<1.0 " + jet,"");  
  AnalyzerTree->Draw("Pho_Pt>>num_data_id_vspt","hltmatched_Pho==1 && hltmatched_Phoid==1 && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001 && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 &&  Pho_R9<1.0 "+ jet,"");

  AnalyzerTree->Draw("MET>>den_data_met","hltmatched_Phoid==1 && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001 && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 &&  Pho_R9<1.0 " + jet,"");
  AnalyzerTree->Draw("MET>>num_data_met"," hltmatched_Phoid==1 && hltmatched==1 && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001 && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 &&  Pho_R9<1.0" + jet,"");

  TPaveText *name = new TPaveText(60,1.07,160,1.17);
  name->AddText("HLT_Photon30_R9Id90_CaloId_HE10_Iso40_EBOnly_Met25_HBHENoiseCleaned");
  name->SetFillColor(0);
  name->SetFillStyle(0);
  name->SetLineColor(0);
  name->SetTextSize(0.028);

  TF1 *f1 = new TF1("f1","1",0,500);
  f1->SetLineColor(4);
  f1->SetLineStyle(2);
  f1->SetLineWidth(2);

  gSystem->Load("libMathCore");
  //gStyle->SetOptFit(0);

  TF1 *erf1 = new TF1("erf1", "0.5*[2]*(1+TMath::Erf( (x-[0]) / ([1]*sqrt(2)) ) )",0.0,500.0);
  erf1->SetParameter(0,30);
  erf1->SetParameter(1,30);
  erf1->SetParameter(2,0.9);
  erf1->SetParLimits(2,0.0,1.0);
  erf1->SetLineColor(2);
  erf1->SetLineWidth(2);

  TF1 *erf2 = new TF1("erf2","0.5*[2]*(1+TMath::Erf( (x-[0]) / ([1]*sqrt(2)) ) )",0.0,500.0);
  erf2->SetParameter(0,10);
  erf2->SetParameter(1,10);
  erf2->SetParameter(2,0.9);
  erf2->SetParLimits(2,0.0,1.0);
  erf2->SetLineColor(2);
  erf2->SetLineWidth(2);

  TCanvas* c1 =  new TCanvas("c1","c1",700,600);
  c1->cd();
  eff_data_id_vspt->BayesDivide(num_data_id_vspt,den_data_id_vspt,"");
  eff_data_id_vspt->Draw("ap");
  eff_data_id_vspt->SetTitle("HLT Photon Id Efficiency");
  eff_data_id_vspt->GetYaxis()->SetTitle("Efficiency");
  eff_data_id_vspt->GetXaxis()->SetTitle("Offline Photon Pt [GeV]");
  eff_data_id_vspt->GetYaxis()->SetRangeUser(0.0,1.19);
  //eff_data_id_vspt->Fit("erf1","RMBI");
  eff_data_id_vspt->Fit("erf1");
  //name->Draw("same");
  f1->Draw("same");
  c1->SaveAs("old_root/eff_id_vspt.pdf");
  c1->SaveAs("old_root/eff_id_vspt.png");

  //for(int i = 0; i< 5 ; i++) { 
  //std::cout << "value: " << eff_data_id_vspt->GetY()[i] << std::endl; }

  TCanvas* c2 =  new TCanvas("c2","c2",700,600);
  c2->cd();
  eff_data_met->BayesDivide(num_data_met,den_data_met,"");
  eff_data_met->Draw("ap");
  eff_data_met->SetTitle("HLT MET Efficiency");
  eff_data_met->GetYaxis()->SetTitle("Efficiency");
  eff_data_met->GetXaxis()->SetTitle("Offline PF MET [GeV]");
  eff_data_met->GetYaxis()->SetRangeUser(0.0,1.19);
  eff_data_met->Fit("erf2","RMBI");
  //name->Draw("same");
  f1->Draw("same");
  c2->SaveAs("old_root/eff_met.pdf");
  c2->SaveAs("old_root/eff_met.png");
  //for(int i = 0; i< 5 ; i++) { 
  //std::cout << "value: " << eff_data_met->GetY()[i] << std::endl; }

  
}

