//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon May  5 12:49:19 2014 by ROOT version 5.32/00
// from TTree AnalyzerTree/H to MonoPhoton Analyzer Tree
// found on file: higgsHistograms_GJets_HT_200To400_aa.root
//////////////////////////////////////////////////////////

#ifndef phiCorr_h
#define phiCorr_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TLorentzVector.h>
#include <TObject.h>
#include <TVector3.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class phiCorr {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           run;
   Int_t           lumi;
   Int_t           event;
   Int_t           isZnn;
   Bool_t          cscTightHalo;
   Float_t         jet_pt;
   Int_t           jet_size;
   Int_t           ntrack;
   Float_t         minDR;
   Float_t         Pho_Pt;
   Float_t         Pho_Eta;
   Float_t         Pho_Phi;
   Float_t         Pho_Eta_Old;
   Float_t         Pho_R9;
   Int_t           Photon_tight;
   Int_t           pixelVeto;
   Int_t           conversionVeto;
   Float_t         HoE;
   Int_t           numGoodPhotons;
   Int_t           Preselection;
   Int_t           n_jets_mva_loose;
   Int_t           n_jets_mva_medium;
   Int_t           n_jets_mva_tight;
   Int_t           n_jets_cut_loose;
   Int_t           n_jets_cut_medium;
   Int_t           n_jets_cut_tight;
   Float_t         jet_eta;
   Float_t         dphi_jet_met;
   Float_t         dR_jet_met;
   Float_t         dphi_jet_pho;
   Float_t         dphi_pho_met;
   Float_t         dR_pho_met;
   Float_t         MET_old;
   Float_t         MEx_old;
   Float_t         MEy_old;
   Float_t         MPhi_old;
   Float_t         MET;
   Float_t         MEx;
   Float_t         MEy;
   Float_t         MPhi;
   Float_t         z_mass;
   Float_t         z_phi;
   Float_t         z_eta;
   Float_t         z_pt;
   Float_t         dphizmet;
   Float_t         MetSig;
   Float_t         sum_genPt;
   Float_t         gen_pt_22;
   Float_t         gen_eta_22;
   Float_t         gen_pt_23;
   Float_t         gen_pt_l;
   Float_t         gen_pt_n;
   Int_t           gen_pdg;
   Float_t         minMET;
   Float_t         pvalue;
   Float_t         MT_old;
   Float_t         MT;
   Float_t         MinMT;
   Int_t           NVtx;
 //TLorentzVector  *Photon;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   UInt_t          fP_fUniqueID;
   UInt_t          fP_fBits;
   Double_t        fP_fX;
   Double_t        fP_fY;
   Double_t        fP_fZ;
   Double_t        fE;
   Bool_t          hltmatched;
   Float_t         LICTD;
   Int_t           foundisoel;
   Int_t           foundlooseEl;
   Int_t           foundvetoEl;
   Int_t           foundisomu;
   Int_t           loose_mu;
   Float_t         el_pt_leading;
   Float_t         el_phi_leading;
   Float_t         el_eta_leading;
   Float_t         el_pt_trailing;
   Float_t         el_phi_trailing;
   Float_t         el_eta_trailing;
   Float_t         mu_pt_leading;
   Float_t         mu_phi_leading;
   Float_t         mu_eta_leading;
   Float_t         mu_pt_trailing;
   Float_t         mu_phi_trailing;
   Float_t         mu_eta_trailing;
   Float_t         m_mm;
   Float_t         m_ee;
   Float_t         m_em;
   Float_t         sigmaIEtaIEta;
   Float_t         sigmaIEtaIPhi;
   Float_t         sigmaIPhiIPhi;
   Float_t         scEtaWidth;
   Float_t         scPhiWidth;
   Float_t         preShowerOverRaw;
   Float_t         e1x3;
   Float_t         e1x5;
   Float_t         e2x2;
   Float_t         e2x5;
   Float_t         e2x5Max;
   Float_t         e5x5;
   Float_t         e2OverE5;
   Float_t         scRawEnergy;
   Float_t         scPSEnergy;
   Float_t         scEnergy;
   Float_t         roundness;
   Float_t         angle;
   Float_t         sMin;
   Float_t         sMaj;
   Float_t         seedCrystalEnergy;
   Float_t         seedCrystalTime;
   Int_t           npT;
   Int_t           npIT;
   Float_t         MyWeightData;
   Float_t         MyWeightData_sys;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_event;   //!
   TBranch        *b_isZnn;   //!
   TBranch        *b_cscTightHalo;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_size;   //!
   TBranch        *b_ntrack;   //!
   TBranch        *b_minDR;   //!
   TBranch        *b_Pho_Pt;   //!
   TBranch        *b_Pho_Eta;   //!
   TBranch        *b_Pho_Phi;   //!
   TBranch        *b_Pho_Eta_Old;   //!
   TBranch        *b_Pho_R9;   //!
   TBranch        *b_Photon_tight;   //!
   TBranch        *b_pixelVeto;   //!
   TBranch        *b_conversionVeto;   //!
   TBranch        *b_HoE;   //!
   TBranch        *b_numGoodPhotons;   //!
   TBranch        *b_Preselection;   //!
   TBranch        *b_n_jets_mva_loose;   //!
   TBranch        *b_n_jets_mva_medium;   //!
   TBranch        *b_n_jets_mva_tight;   //!
   TBranch        *b_n_jets_cut_loose;   //!
   TBranch        *b_n_jets_cut_medium;   //!
   TBranch        *b_n_jets_cut_tight;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_dphi_jet_met;   //!
   TBranch        *b_dR_jet_met;   //!
   TBranch        *b_dphi_jet_pho;   //!
   TBranch        *b_dphi_pho_met;   //!
   TBranch        *b_dR_pho_met;   //!
   TBranch        *b_MET_old;   //!
   TBranch        *b_MEx_old;   //!
   TBranch        *b_MEy_old;   //!
   TBranch        *b_MPhi_old;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_MEx;   //!
   TBranch        *b_MEy;   //!
   TBranch        *b_MPhi;   //!
   TBranch        *b_z_mass;   //!
   TBranch        *b_z_phi;   //!
   TBranch        *b_z_eta;   //!
   TBranch        *b_z_pt;   //!
   TBranch        *b_dphizmet;   //!
   TBranch        *b_MetSig;   //!
   TBranch        *b_sum_genPt;   //!
   TBranch        *b_gen_pt_22;   //!
   TBranch        *b_gen_eta_22;   //!
   TBranch        *b_gen_pt_23;   //!
   TBranch        *b_gen_pt_l;   //!
   TBranch        *b_gen_pt_n;   //!
   TBranch        *b_gen_pdg;   //!
   TBranch        *b_minMET;   //!
   TBranch        *b_pvalue;   //!
   TBranch        *b_MT_old;   //!
   TBranch        *b_MT;   //!
   TBranch        *b_MinMT;   //!
   TBranch        *b_NVtx;   //!
   TBranch        *b_Photon_fUniqueID;   //!
   TBranch        *b_Photon_fBits;   //!
   TBranch        *b_Photon_fP_fUniqueID;   //!
   TBranch        *b_Photon_fP_fBits;   //!
   TBranch        *b_Photon_fP_fX;   //!
   TBranch        *b_Photon_fP_fY;   //!
   TBranch        *b_Photon_fP_fZ;   //!
   TBranch        *b_Photon_fE;   //!
   TBranch        *b_hltmatched;   //!
   TBranch        *b_LICTD;   //!
   TBranch        *b_foundisoel;   //!
   TBranch        *b_foundlooseEl;   //!
   TBranch        *b_foundvetoEl;   //!
   TBranch        *b_foundisomu;   //!
   TBranch        *b_loose_mu;   //!
   TBranch        *b_el_pt_leading;   //!
   TBranch        *b_el_phi_leading;   //!
   TBranch        *b_el_eta_leading;   //!
   TBranch        *b_el_pt_trailing;   //!
   TBranch        *b_el_phi_trailing;   //!
   TBranch        *b_el_eta_trailing;   //!
   TBranch        *b_mu_pt_leading;   //!
   TBranch        *b_mu_phi_leading;   //!
   TBranch        *b_mu_eta_leading;   //!
   TBranch        *b_mu_pt_trailing;   //!
   TBranch        *b_mu_phi_trailing;   //!
   TBranch        *b_mu_eta_trailing;   //!
   TBranch        *b_m_mm;   //!
   TBranch        *b_m_ee;   //!
   TBranch        *b_m_em;   //!
   TBranch        *b_sigmaIEtaIEta;   //!
   TBranch        *b_sigmaIEtaIPhi;   //!
   TBranch        *b_sigmaIPhiIPhi;   //!
   TBranch        *b_scEtaWidth;   //!
   TBranch        *b_scPhiWidth;   //!
   TBranch        *b_preShowerOverRaw;   //!
   TBranch        *b_e1x3;   //!
   TBranch        *b_e1x5;   //!
   TBranch        *b_e2x2;   //!
   TBranch        *b_e2x5;   //!
   TBranch        *b_e2x5Max;   //!
   TBranch        *b_e5x5;   //!
   TBranch        *b_e2OverE5;   //!
   TBranch        *b_scRawEnergy;   //!
   TBranch        *b_scPSEnergy;   //!
   TBranch        *b_scEnergy;   //!
   TBranch        *b_roundness;   //!
   TBranch        *b_angle;   //!
   TBranch        *b_sMin;   //!
   TBranch        *b_sMaj;   //!
   TBranch        *b_seedCrystalEnergy;   //!
   TBranch        *b_seedCrystalTime;   //!
   TBranch        *b_npT;   //!
   TBranch        *b_npIT;   //!
   TBranch        *b_MyWeightData;   //!
   TBranch        *b_MyWeightData_sys;   //!

   phiCorr(TTree *tree=0);
   virtual ~phiCorr();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef phiCorr_cxx
phiCorr::phiCorr(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("higgsHistograms_GJets_HT_200To400_aa.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("higgsHistograms_GJets_HT_200To400_aa.root");
      }
      f->GetObject("AnalyzerTree",tree);

   }
   Init(tree);
}

phiCorr::~phiCorr()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t phiCorr::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t phiCorr::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void phiCorr::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("isZnn", &isZnn, &b_isZnn);
   fChain->SetBranchAddress("cscTightHalo", &cscTightHalo, &b_cscTightHalo);
   fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_size", &jet_size, &b_jet_size);
   fChain->SetBranchAddress("ntrack", &ntrack, &b_ntrack);
   fChain->SetBranchAddress("minDR", &minDR, &b_minDR);
   fChain->SetBranchAddress("Pho_Pt", &Pho_Pt, &b_Pho_Pt);
   fChain->SetBranchAddress("Pho_Eta", &Pho_Eta, &b_Pho_Eta);
   fChain->SetBranchAddress("Pho_Phi", &Pho_Phi, &b_Pho_Phi);
   fChain->SetBranchAddress("Pho_Eta_Old", &Pho_Eta_Old, &b_Pho_Eta_Old);
   fChain->SetBranchAddress("Pho_R9", &Pho_R9, &b_Pho_R9);
   fChain->SetBranchAddress("Photon_tight", &Photon_tight, &b_Photon_tight);
   fChain->SetBranchAddress("pixelVeto", &pixelVeto, &b_pixelVeto);
   fChain->SetBranchAddress("conversionVeto", &conversionVeto, &b_conversionVeto);
   fChain->SetBranchAddress("HoE", &HoE, &b_HoE);
   fChain->SetBranchAddress("numGoodPhotons", &numGoodPhotons, &b_numGoodPhotons);
   fChain->SetBranchAddress("Preselection", &Preselection, &b_Preselection);
   fChain->SetBranchAddress("n_jets_mva_loose", &n_jets_mva_loose, &b_n_jets_mva_loose);
   fChain->SetBranchAddress("n_jets_mva_medium", &n_jets_mva_medium, &b_n_jets_mva_medium);
   fChain->SetBranchAddress("n_jets_mva_tight", &n_jets_mva_tight, &b_n_jets_mva_tight);
   fChain->SetBranchAddress("n_jets_cut_loose", &n_jets_cut_loose, &b_n_jets_cut_loose);
   fChain->SetBranchAddress("n_jets_cut_medium", &n_jets_cut_medium, &b_n_jets_cut_medium);
   fChain->SetBranchAddress("n_jets_cut_tight", &n_jets_cut_tight, &b_n_jets_cut_tight);
   fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("dphi_jet_met", &dphi_jet_met, &b_dphi_jet_met);
   fChain->SetBranchAddress("dR_jet_met", &dR_jet_met, &b_dR_jet_met);
   fChain->SetBranchAddress("dphi_jet_pho", &dphi_jet_pho, &b_dphi_jet_pho);
   fChain->SetBranchAddress("dphi_pho_met", &dphi_pho_met, &b_dphi_pho_met);
   fChain->SetBranchAddress("dR_pho_met", &dR_pho_met, &b_dR_pho_met);
   fChain->SetBranchAddress("MET_old", &MET_old, &b_MET_old);
   fChain->SetBranchAddress("MEx_old", &MEx_old, &b_MEx_old);
   fChain->SetBranchAddress("MEy_old", &MEy_old, &b_MEy_old);
   fChain->SetBranchAddress("MPhi_old", &MPhi_old, &b_MPhi_old);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("MEx", &MEx, &b_MEx);
   fChain->SetBranchAddress("MEy", &MEy, &b_MEy);
   fChain->SetBranchAddress("MPhi", &MPhi, &b_MPhi);
   fChain->SetBranchAddress("z_mass", &z_mass, &b_z_mass);
   fChain->SetBranchAddress("z_phi", &z_phi, &b_z_phi);
   fChain->SetBranchAddress("z_eta", &z_eta, &b_z_eta);
   fChain->SetBranchAddress("z_pt", &z_pt, &b_z_pt);
   fChain->SetBranchAddress("dphizmet", &dphizmet, &b_dphizmet);
   fChain->SetBranchAddress("MetSig", &MetSig, &b_MetSig);
   fChain->SetBranchAddress("sum_genPt", &sum_genPt, &b_sum_genPt);
   fChain->SetBranchAddress("gen_pt_22", &gen_pt_22, &b_gen_pt_22);
   fChain->SetBranchAddress("gen_eta_22", &gen_eta_22, &b_gen_eta_22);
   fChain->SetBranchAddress("gen_pt_23", &gen_pt_23, &b_gen_pt_23);
   fChain->SetBranchAddress("gen_pt_l", &gen_pt_l, &b_gen_pt_l);
   fChain->SetBranchAddress("gen_pt_n", &gen_pt_n, &b_gen_pt_n);
   fChain->SetBranchAddress("gen_pdg", &gen_pdg, &b_gen_pdg);
   fChain->SetBranchAddress("minMET", &minMET, &b_minMET);
   fChain->SetBranchAddress("pvalue", &pvalue, &b_pvalue);
   fChain->SetBranchAddress("MT_old", &MT_old, &b_MT_old);
   fChain->SetBranchAddress("MT", &MT, &b_MT);
   fChain->SetBranchAddress("MinMT", &MinMT, &b_MinMT);
   fChain->SetBranchAddress("NVtx", &NVtx, &b_NVtx);
   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_Photon_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_Photon_fBits);
   fChain->SetBranchAddress("fP.fUniqueID", &fP_fUniqueID, &b_Photon_fP_fUniqueID);
   fChain->SetBranchAddress("fP.fBits", &fP_fBits, &b_Photon_fP_fBits);
   fChain->SetBranchAddress("fP.fX", &fP_fX, &b_Photon_fP_fX);
   fChain->SetBranchAddress("fP.fY", &fP_fY, &b_Photon_fP_fY);
   fChain->SetBranchAddress("fP.fZ", &fP_fZ, &b_Photon_fP_fZ);
   fChain->SetBranchAddress("fE", &fE, &b_Photon_fE);
   fChain->SetBranchAddress("hltmatched", &hltmatched, &b_hltmatched);
   fChain->SetBranchAddress("LICTD", &LICTD, &b_LICTD);
   fChain->SetBranchAddress("foundisoel", &foundisoel, &b_foundisoel);
   fChain->SetBranchAddress("foundlooseEl", &foundlooseEl, &b_foundlooseEl);
   fChain->SetBranchAddress("foundvetoEl", &foundvetoEl, &b_foundvetoEl);
   fChain->SetBranchAddress("foundisomu", &foundisomu, &b_foundisomu);
   fChain->SetBranchAddress("loose_mu", &loose_mu, &b_loose_mu);
   fChain->SetBranchAddress("el_pt_leading", &el_pt_leading, &b_el_pt_leading);
   fChain->SetBranchAddress("el_phi_leading", &el_phi_leading, &b_el_phi_leading);
   fChain->SetBranchAddress("el_eta_leading", &el_eta_leading, &b_el_eta_leading);
   fChain->SetBranchAddress("el_pt_trailing", &el_pt_trailing, &b_el_pt_trailing);
   fChain->SetBranchAddress("el_phi_trailing", &el_phi_trailing, &b_el_phi_trailing);
   fChain->SetBranchAddress("el_eta_trailing", &el_eta_trailing, &b_el_eta_trailing);
   fChain->SetBranchAddress("mu_pt_leading", &mu_pt_leading, &b_mu_pt_leading);
   fChain->SetBranchAddress("mu_phi_leading", &mu_phi_leading, &b_mu_phi_leading);
   fChain->SetBranchAddress("mu_eta_leading", &mu_eta_leading, &b_mu_eta_leading);
   fChain->SetBranchAddress("mu_pt_trailing", &mu_pt_trailing, &b_mu_pt_trailing);
   fChain->SetBranchAddress("mu_phi_trailing", &mu_phi_trailing, &b_mu_phi_trailing);
   fChain->SetBranchAddress("mu_eta_trailing", &mu_eta_trailing, &b_mu_eta_trailing);
   fChain->SetBranchAddress("m_mm", &m_mm, &b_m_mm);
   fChain->SetBranchAddress("m_ee", &m_ee, &b_m_ee);
   fChain->SetBranchAddress("m_em", &m_em, &b_m_em);
   fChain->SetBranchAddress("sigmaIEtaIEta", &sigmaIEtaIEta, &b_sigmaIEtaIEta);
   fChain->SetBranchAddress("sigmaIEtaIPhi", &sigmaIEtaIPhi, &b_sigmaIEtaIPhi);
   fChain->SetBranchAddress("sigmaIPhiIPhi", &sigmaIPhiIPhi, &b_sigmaIPhiIPhi);
   fChain->SetBranchAddress("scEtaWidth", &scEtaWidth, &b_scEtaWidth);
   fChain->SetBranchAddress("scPhiWidth", &scPhiWidth, &b_scPhiWidth);
   fChain->SetBranchAddress("preShowerOverRaw", &preShowerOverRaw, &b_preShowerOverRaw);
   fChain->SetBranchAddress("e1x3", &e1x3, &b_e1x3);
   fChain->SetBranchAddress("e1x5", &e1x5, &b_e1x5);
   fChain->SetBranchAddress("e2x2", &e2x2, &b_e2x2);
   fChain->SetBranchAddress("e2x5", &e2x5, &b_e2x5);
   fChain->SetBranchAddress("e2x5Max", &e2x5Max, &b_e2x5Max);
   fChain->SetBranchAddress("e5x5", &e5x5, &b_e5x5);
   fChain->SetBranchAddress("e2OverE5", &e2OverE5, &b_e2OverE5);
   fChain->SetBranchAddress("scRawEnergy", &scRawEnergy, &b_scRawEnergy);
   fChain->SetBranchAddress("scPSEnergy", &scPSEnergy, &b_scPSEnergy);
   fChain->SetBranchAddress("scEnergy", &scEnergy, &b_scEnergy);
   fChain->SetBranchAddress("roundness", &roundness, &b_roundness);
   fChain->SetBranchAddress("angle", &angle, &b_angle);
   fChain->SetBranchAddress("sMin", &sMin, &b_sMin);
   fChain->SetBranchAddress("sMaj", &sMaj, &b_sMaj);
   fChain->SetBranchAddress("seedCrystalEnergy", &seedCrystalEnergy, &b_seedCrystalEnergy);
   fChain->SetBranchAddress("seedCrystalTime", &seedCrystalTime, &b_seedCrystalTime);
   fChain->SetBranchAddress("npT", &npT, &b_npT);
   fChain->SetBranchAddress("npIT", &npIT, &b_npIT);
   fChain->SetBranchAddress("MyWeightData", &MyWeightData, &b_MyWeightData);
   fChain->SetBranchAddress("MyWeightData_sys", &MyWeightData_sys, &b_MyWeightData_sys);
   Notify();
}

Bool_t phiCorr::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void phiCorr::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t phiCorr::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef phiCorr_cxx
