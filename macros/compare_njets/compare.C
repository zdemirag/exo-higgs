void compare(){

    TFile *f_madgraph = new TFile("madgraph_Histos.root","READ");
    TH1F *h_madgraph = f_madgraph->Get("susyHiggs/GJetsn_jets_mva_loose");

    std::cout << h_madgraph->Integral(0,2) <<std::endl;
    std::cout << h_madgraph->Integral() <<std::endl;
    std::cout << "eff: " << h_madgraph->Integral(0,2)/h_madgraph->Integral() << std::endl;
    h_madgraph->Scale(1./h_madgraph->Integral());
    h_madgraph->SetLineColor(4);
    h_madgraph->Draw();

    TFile *f_pythia = new TFile("pythia_Histos.root","READ");
    TH1F *h_pythia = f_pythia->Get("susyHiggs/PJets");

    std::cout << h_pythia->Integral(0,2) <<std::endl;
    std::cout << h_pythia->Integral() <<std::endl;
    std::cout << "eff: " << h_pythia->Integral(0,2)/h_pythia->Integral() << std::endl;
    h_pythia->Scale(1./h_pythia->Integral());
    h_pythia->SetLineColor(3);
    h_pythia->Draw("same");



}
