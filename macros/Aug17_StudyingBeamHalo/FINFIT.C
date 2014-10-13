void FINFIT(){
 
 gROOT->SetStyle("Plain");
 gStyle->SetOptTitle(0);
 gStyle->SetOptStat(0);

 //Read input from txt
 ifstream FROut("FROutput.txt");
 std::string FR;

 int j=0;

 double qsafe = 100.;

 double y_j, ey_j;

 const int n = 7;
 
 Double_t y[n];
 Double_t ey[n];

 while(!FROut.eof()) {
     FROut >> FR >> y_j >> ey_j;
     if (qsafe != y_j){
         y[j]=y_j;
         ey[j]=ey_j;
         qsafe = y_j;
         j++;
     }
 }

 Double_t x[n];
 Double_t ex[n];

 TFile *f = new TFile("dataTemplates_Zeynep_pt.root","READ");
 for(int i = 1; i < 8; i++){
     string Result;          // string which will contain the result  
     ostringstream convert;   // stream used for the conversion 
     convert << i;      // insert the textual representation of 'Number' in the characters in the stream
     Result = convert.str(); // set 'Result' to the contents of the stream
     TString name = "h_denom_"+Result;
     TH1F *h = (TH1F*)f->Get(name);
     std::cout << "bin "<<i-1<<" "<<h->GetMean() <<" +/- " << h->GetRMS() << std::endl;
     x[i-1] = h->GetMean();
     ex[i-1] = h->GetRMS();
 }



 gr0 = new TGraphErrors(n,x,y,ex,ey);
 gr0->SetMarkerStyle(20);
 gr0->GetXaxis()->SetRangeUser(30,130);
 gr0->GetXaxis()->SetTitle("p_{T} (GeV)");
 //gr0->GetXaxis()->SetRangeUser(30,130);
 gr0->GetYaxis()->SetTitle("Fake Ratio");
 TF1 ffit0("ffit0","[0]+[1]/x^[2]",30,130);
 ffit0.SetLineColor(40);
 ffit0.SetLineWidth(3);
 ffit0.SetParameter(0,1.54);
 ffit0.SetParameter(1,1114);
 ffit0.SetParameter(2,1.799);
 GR0 =  (TGraphErrors*)gr0->Clone();
 
 ////////////////////////////////////////////////
 TCanvas *cc = new TCanvas("Fake Rate","Fake Rate",900,600);
 gPad->SetTickx();
 gPad->SetTicky();
 gStyle->SetOptFit(1111);
 gStyle->SetStatX(0.88);
 gStyle->SetStatY(0.75);
 gStyle->SetStatW(0.14);
 gStyle->SetStatH(0.1);
 gStyle->SetStatBorderSize(0);
 GR0->Fit(&ffit0);
 GR0->Draw("APSAME");

 TLegend *leg1 = new TLegend(0.64, 0.76, 0.87, 0.83);
  leg1->SetFillColor(kWhite);
  leg1->SetTextSize(0.03);
  leg1->SetHeader("#splitline{#gamma fake rate for QCD}{fit function: p0+p1/x^p2}");
  //leg1->AddEntry(GR0, "no MET cut", "P");
  leg1->Draw("same");
 
 cc->SaveAs("fitResult.root");
 
}




