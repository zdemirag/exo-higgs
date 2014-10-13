void makeHisto(){

  TFile fnew("Histograms.root","RECREATE");  

  TFile *f = new TFile("../../root_March3/higgsHistograms_DM.root","READ");
  TH1F *h_dm   = new TH1F("h_dm","h_dm",100,0,500);
  Analyzer->cd();
  AnalyzerTree->Draw("Pho_Pt>>h_dm","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");


  TFile *f = new TFile("../../root_March3/higgsHistograms_DiPhoton.root","READ");
  Analyzer->cd();
  TH1F *h_dip   = new TH1F("h_dip","h_dip",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_dip","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");


  TFile *f = new TFile("../../root_March3/higgsHistograms_DiphotonBox_Pt_250toInf.root","READ");
  Analyzer->cd();
  TH1F *h_DiphotonBox_Pt_250toInf   = new TH1F("h_DiphotonBox_Pt_250toInf","h_DiphotonBox_Pt_250toInf",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_DiphotonBox_Pt_250toInf","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");

  TFile *f = new TFile("../../root_March3/higgsHistograms_DiphotonBox_Pt_25to250.root","READ");
  Analyzer->cd();
  TH1F *h_DiphotonBox_Pt_25to250   = new TH1F("h_DiphotonBox_Pt_25to250","h_DiphotonBox_Pt_25to250",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_DiphotonBox_Pt_25to250","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");
  
  TFile *f = new TFile("../../root_March3/higgsHistograms_PJets_120to170.root","READ");
  Analyzer->cd();
  TH1F *h_PJets_120to170   = new TH1F("h_PJets_120to170","h_PJets_120to170",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_PJets_120to170","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");

  TFile *f = new TFile("../../root_March3/higgsHistograms_PJets_1400to1800.root","READ");
  Analyzer->cd();
  TH1F *h_PJets_1400to1800   = new TH1F("h_PJets_1400to1800","h_PJets_1400to1800",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_PJets_1400to1800","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");

  TFile *f = new TFile("../../root_March3/higgsHistograms_PJets_15to30.root","READ");
  Analyzer->cd();
  TH1F *h_PJets_15to30   = new TH1F("h_PJets_15to30","h_PJets_15to30",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_PJets_15to30","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");

  TFile *f = new TFile("../../root_March3/higgsHistograms_PJets_170to300.root","READ");
  Analyzer->cd();
  TH1F *h_PJets_170to300   = new TH1F("h_PJets_170to300","h_PJets_170to300",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_PJets_170to300","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");

  TFile *f = new TFile("../../root_March3/higgsHistograms_PJets_1800.root","READ");
  Analyzer->cd();
  TH1F *h_PJets_1800   = new TH1F("h_PJets_1800","h_PJets_1800",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_PJets_1800","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");

  TFile *f = new TFile("../../root_March3/higgsHistograms_PJets_300to470.root","READ");
  Analyzer->cd();
  TH1F *h_PJets_300to470   = new TH1F("h_PJets_300to470","h_PJets_300to470",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_PJets_300to470","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");

  TFile *f = new TFile("../../root_March3/higgsHistograms_PJets_30to50.root","READ");
  Analyzer->cd();
  TH1F *h_PJets_30to50   = new TH1F("h_PJets_30to50","h_PJets_30to50",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_PJets_30to50","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");

  TFile *f = new TFile("../../root_March3/higgsHistograms_PJets_470to800.root","READ");
  Analyzer->cd();
  TH1F *h_PJets_470to800   = new TH1F("h_PJets_470to800","h_PJets_470to800",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_PJets_470to800","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");

  TFile *f = new TFile("../../root_March3/higgsHistograms_PJets_50to80.root","READ");
  Analyzer->cd();
  TH1F *h_PJets_50to80   = new TH1F("h_PJets_50to80","h_PJets_50to80",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_PJets_50to80","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");

  TFile *f = new TFile("../../root_March3/higgsHistograms_PJets_800to1400.root","READ");
  Analyzer->cd();
  TH1F *h_PJets_800to1400   = new TH1F("h_PJets_800to1400","h_PJets_800to1400",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_PJets_800to1400","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");

  TFile *f = new TFile("../../root_March3/higgsHistograms_PJets_80to120.root","READ");
  Analyzer->cd();
  TH1F *h_PJets_80to120   = new TH1F("h_PJets_80to120","h_PJets_80to120",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_PJets_80to120","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");

  TFile *f = new TFile("../../root_March3/higgsHistograms_SinglePhotonParked.root","READ");
  Analyzer->cd();
  TH1F *h_SinglePhotonParked   = new TH1F("h_SinglePhotonParked","h_SinglePhotonParked",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_SinglePhotonParked","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");

  TFile *f = new TFile("../../root_March3/higgsHistograms_WGamma.root","READ");
  Analyzer->cd();
  TH1F *h_WGamma   = new TH1F("h_WGamma","h_WGamma",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_WGamma","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");

  TFile *f = new TFile("../../root_March3/higgsHistograms_WtoLNuMu.root","READ");
  Analyzer->cd();
  TH1F *h_WtoLNuMu   = new TH1F("h_WtoLNuMu","h_WtoLNuMu",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_WtoLNuMu","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");

  TFile *f = new TFile("../../root_March3/higgsHistograms_WtoLNuTau.root","READ");
  Analyzer->cd();
  TH1F *h_WtoLNuTau   = new TH1F("h_WtoLNuTau","h_WtoLNuTau",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_WtoLNuTau","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");

  TFile *f = new TFile("../../root_March3/higgsHistograms_ZGamma_Inclusive.root","READ");
  Analyzer->cd(); 
  TH1F *h_ZGamma_Inclusive   = new TH1F("h_ZGamma_Inclusive","h_ZGamma_Inclusive",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_ZGamma_Inclusive","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");
  
  TFile *f = new TFile("../../root_March3/higgsHistograms_efake_dd.root","READ");
  Analyzer->cd(); 
  TH1F *h_efake_dd   = new TH1F("h_efake_dd","h_efake_dd",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_efake_dd","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==1 )","");
  
  TFile *f = new TFile("../../root_March3/higgsHistograms_qcd_dd.root","READ");
  Analyzer->cd();
  TH1F *h_qcd_dd   = new TH1F("h_qcd_dd","h_qcd_dd",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_qcd_dd","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");

  TFile *f = new TFile("../../root_March3/higgsHistograms_susyHiggs.root","READ");
  Analyzer->cd();
  TH1F *h_susyHiggs   = new TH1F("h_susyHiggs","h_susyHiggs",100,0,500);
  AnalyzerTree->Draw("Pho_Pt>>h_susyHiggs","(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5 && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0 )","");




  fnew.cd(); 
  h_dm->Write();
  h_dip->Write();
  h_DiphotonBox_Pt_250toInf->Write();
  h_DiphotonBox_Pt_25to250->Write();

  h_PJets_15to30->Write();
  h_PJets_30to50->Write();
  h_PJets_50to80->Write();
  h_PJets_80to120->Write(); 
  h_PJets_120to170->Write();
  h_PJets_170to300->Write();
  h_PJets_300to470->Write();
  h_PJets_470to800->Write();
  h_PJets_800to1400->Write(); 
  h_PJets_1400to1800->Write();
  h_PJets_1800->Write();

  h_SinglePhotonParked->Write(); 
  h_WGamma->Write(); 
  h_WtoLNuMu->Write(); 
  h_WtoLNuTau->Write(); 
  h_ZGamma_Inclusive->Write(); 
  h_efake_dd->Write(); 
  h_qcd_dd->Write(); 
  h_susyHiggs->Write(); 

}
