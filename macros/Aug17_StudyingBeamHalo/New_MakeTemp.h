//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Aug  8 20:03:16 2014 by ROOT version 5.32/00
// from TTree AnalyzerTree/H to MonoPhoton Analyzer Tree
// found on file: n_jetTest.root
//////////////////////////////////////////////////////////

#ifndef New_MakeTemp_h
#define New_MakeTemp_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.
#include <TLorentzVector.h>
#include <TObject.h>
#include <TVector3.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class New_MakeTemp : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           run;
   Int_t           lumi;
   Int_t           event;
   Float_t         Pho_Pt;
   Float_t         Pho_SigmaIEtaIEta;
   Float_t         sigmaIPhiIPhi;
   Bool_t          passedNum;
   Bool_t          passedDen;
   Bool_t          passedFake;
   Int_t           numGoodPhotons;
   Float_t         MET;
 //TLorentzVector  *Photon;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   UInt_t          fP_fUniqueID;
   UInt_t          fP_fBits;
   Double_t        fP_fX;
   Double_t        fP_fY;
   Double_t        fP_fZ;
   Double_t        fE;
   Bool_t          elVeto0;
   Bool_t          muVeto0;
   Bool_t          elVeto5;
   Bool_t          muVeto5;
   Bool_t          elVeto10;
   Bool_t          muVeto10;
   Int_t           njet;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_event;   //!
   TBranch        *b_Pho_Pt;   //!
   TBranch        *b_Pho_SigmaIEtaIEta;   //!
   TBranch        *b_sigmaIPhiIPhi;   //!
   TBranch        *b_passedNum;   //!
   TBranch        *b_passedDen;   //!
   TBranch        *b_passedFake;   //!
   TBranch        *b_numGoodPhotons;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_Photon_fUniqueID;   //!
   TBranch        *b_Photon_fBits;   //!
   TBranch        *b_Photon_fP_fUniqueID;   //!
   TBranch        *b_Photon_fP_fBits;   //!
   TBranch        *b_Photon_fP_fX;   //!
   TBranch        *b_Photon_fP_fY;   //!
   TBranch        *b_Photon_fP_fZ;   //!
   TBranch        *b_Photon_fE;   //!
   TBranch        *b_elVeto0;   //!
   TBranch        *b_muVeto0;   //!
   TBranch        *b_elVeto5;   //!
   TBranch        *b_muVeto5;   //!
   TBranch        *b_elVeto10;   //!
   TBranch        *b_muVeto10;   //!
   TBranch        *b_njet;   //!

   New_MakeTemp(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~New_MakeTemp() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   virtual void    GetAllEntries(Long64_t entry);


   ClassDef(New_MakeTemp,0);
};

#endif

#ifdef New_MakeTemp_cxx
void New_MakeTemp::Init(TTree *tree)
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
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("Pho_Pt", &Pho_Pt, &b_Pho_Pt);
   fChain->SetBranchAddress("Pho_SigmaIEtaIEta", &Pho_SigmaIEtaIEta, &b_Pho_SigmaIEtaIEta);
   fChain->SetBranchAddress("sigmaIPhiIPhi", &sigmaIPhiIPhi, &b_sigmaIPhiIPhi);
   fChain->SetBranchAddress("passedNum", &passedNum, &b_passedNum);
   fChain->SetBranchAddress("passedDen", &passedDen, &b_passedDen);
   fChain->SetBranchAddress("passedFake", &passedFake, &b_passedFake);
   fChain->SetBranchAddress("numGoodPhotons", &numGoodPhotons, &b_numGoodPhotons);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_Photon_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_Photon_fBits);
   fChain->SetBranchAddress("fP.fUniqueID", &fP_fUniqueID, &b_Photon_fP_fUniqueID);
   fChain->SetBranchAddress("fP.fBits", &fP_fBits, &b_Photon_fP_fBits);
   fChain->SetBranchAddress("fP.fX", &fP_fX, &b_Photon_fP_fX);
   fChain->SetBranchAddress("fP.fY", &fP_fY, &b_Photon_fP_fY);
   fChain->SetBranchAddress("fP.fZ", &fP_fZ, &b_Photon_fP_fZ);
   fChain->SetBranchAddress("fE", &fE, &b_Photon_fE);
   fChain->SetBranchAddress("elVeto0", &elVeto0, &b_elVeto0);
   fChain->SetBranchAddress("muVeto0", &muVeto0, &b_muVeto0);
   fChain->SetBranchAddress("elVeto5", &elVeto5, &b_elVeto5);
   fChain->SetBranchAddress("muVeto5", &muVeto5, &b_muVeto5);
   fChain->SetBranchAddress("elVeto10", &elVeto10, &b_elVeto10);
   fChain->SetBranchAddress("muVeto10", &muVeto10, &b_muVeto10);
   fChain->SetBranchAddress("njet", &njet, &b_njet);
}

Bool_t New_MakeTemp::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef New_MakeTemp_cxx
