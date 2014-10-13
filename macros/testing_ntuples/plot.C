void plot(){


    TCanvas *c = new TCanvas("c","c",600,700);
    TFile *f = new TFile("total_nuTuple.root","READ");
    f->MakeProject("test","*","recreate++");    
    ntupleProducer->cd();
    TH1F *h_met[9];
    TString str_i[9] = {"corrMET","jerUpMET","jerDownMET","phoUpMET","phoDownMET","jetupMET","jetdownMET","uncUpMET","uncDownMET"};

    //c->cd();

    for(int i==0; i<9; i++){
        h_met[i] = new TH1F("h_met_"+str_i[i],"h_met_"+str_i[i],20,0,200);
        eventTree->Draw(str_i[i]+".Mod()>>h_met_"+str_i[i],"","goff");   
        c->cd();
        c->SetLogy();
        if(i == 0) h_met[i]->Draw();
        else {
            h_met[i]->SetLineColor(i);
            h_met[i]->Draw("sames");
        }
    }

}
