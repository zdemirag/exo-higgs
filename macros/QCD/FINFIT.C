void FINFIT(){
 
 gROOT->SetStyle("Plain");
 gStyle->SetOptTitle(0);
 gStyle->SetOptStat(0);
 
 //Read input from txt
 ifstream FROut("FROutput.txt");
 std::string FR;
 double res = -1;
 double y0_[] = {-1.,-1.,-1.,-1.,-1.,-1.,-1.};
 int j=0;
 double qsafe = 100.;
 
 while(!FROut.eof()) {
   FROut >> FR >> res;
   if (qsafe != res){
    y0_[j]=res;
    qsafe = res;
    j++;
   }
 }
 
 Int_t n = 7;
 Double_t x[]  = {35., 45., 55., 65., 75., 90., 115.};
 Double_t y0[]  = {y0_[0], y0_[1], y0_[2], y0_[3], y0_[4], y0_[5], y0_[6]};
 Double_t ex[] = {5.,5.,5.,5.,5.,10.,15.};
 Double_t ey[] = {0.06,0.06,0.06,0.06,0.06,0.06,0.06};
 
 gr0 = new TGraphErrors(n,x,y0,ex,ey);
 gr0->SetMarkerStyle(20);
 gr0->GetXaxis()->SetRangeUser(30,130);
 gr0->GetXaxis()->SetTitle("p_{T} (GeV)");
 //gr0->GetXaxis()->SetRangeUser(30,130);
 gr0->GetYaxis()->SetTitle("Fake Rate");
 TF1 ffit0("ffit0","[0]+[1]/x^[2]",30,130);
 ffit0.SetLineColor(40);
 ffit0.SetLineWidth(3);
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
 
 cc->SaveAs("fitResult.png");
 
}




