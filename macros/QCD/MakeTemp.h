//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Aug  7 11:55:40 2014 by ROOT version 5.32/00
// from TTree AnalyzerTree/H to MonoPhoton Analyzer Tree
// found on file: higgsHistograms_QCD.root
//////////////////////////////////////////////////////////

#ifndef MakeTemp_h
#define MakeTemp_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.
#include <TLorentzVector.h>
#include <TObject.h>
#include <TVector3.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class MakeTemp : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           run;
   Int_t           lumi;
   Int_t           event;
   Float_t         Num_Pho_Pt;
   Float_t         Num_Pho_SigmaIEtaIEta;
   Float_t         Den_Pho_Pt;
   Float_t         Den_Pho_SigmaIEtaIEta;
   Float_t         Fake62_Pho_Pt;
   Float_t         Fake62_Pho_SigmaIEtaIEta;
   Float_t         Fake49_Pho_Pt;
   Float_t         Fake49_Pho_SigmaIEtaIEta;
   Float_t         Fake155_Pho_Pt;
   Float_t         Fake155_Pho_SigmaIEtaIEta;
   Float_t         Fake510_Pho_Pt;
   Float_t         Fake510_Pho_SigmaIEtaIEta;
   Int_t           numGoodPhotons;
   Float_t         MET;
 //TLorentzVector  *dummy_empty;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   UInt_t          fP_fUniqueID;
   UInt_t          fP_fBits;
   Double_t        fP_fX;
   Double_t        fP_fY;
   Double_t        fP_fZ;
   Double_t        fE;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_event;   //!
   TBranch        *b_Num_Pho_Pt;   //!
   TBranch        *b_Num_Pho_SigmaIEtaIEta;   //!
   TBranch        *b_Den_Pho_Pt;   //!
   TBranch        *b_Den_Pho_SigmaIEtaIEta;   //!
   TBranch        *b_Fake62_Pho_Pt;   //!
   TBranch        *b_Fake62_Pho_SigmaIEtaIEta;   //!
   TBranch        *b_Fake49_Pho_Pt;   //!
   TBranch        *b_Fake49_Pho_SigmaIEtaIEta;   //!
   TBranch        *b_Fake155_Pho_Pt;   //!
   TBranch        *b_Fake155_Pho_SigmaIEtaIEta;   //!
   TBranch        *b_Fake510_Pho_Pt;   //!
   TBranch        *b_Fake510_Pho_SigmaIEtaIEta;   //!
   TBranch        *b_numGoodPhotons;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_dummy_empty_fUniqueID;   //!
   TBranch        *b_dummy_empty_fBits;   //!
   TBranch        *b_dummy_empty_fP_fUniqueID;   //!
   TBranch        *b_dummy_empty_fP_fBits;   //!
   TBranch        *b_dummy_empty_fP_fX;   //!
   TBranch        *b_dummy_empty_fP_fY;   //!
   TBranch        *b_dummy_empty_fP_fZ;   //!
   TBranch        *b_dummy_empty_fE;   //!

   MakeTemp(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~MakeTemp() { }
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

   ClassDef(MakeTemp,0);
};

#endif

#ifdef MakeTemp_cxx
void MakeTemp::Init(TTree *tree)
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
   fChain->SetBranchAddress("Num_Pho_Pt", &Num_Pho_Pt, &b_Num_Pho_Pt);
   fChain->SetBranchAddress("Num_Pho_SigmaIEtaIEta", &Num_Pho_SigmaIEtaIEta, &b_Num_Pho_SigmaIEtaIEta);
   fChain->SetBranchAddress("Den_Pho_Pt", &Den_Pho_Pt, &b_Den_Pho_Pt);
   fChain->SetBranchAddress("Den_Pho_SigmaIEtaIEta", &Den_Pho_SigmaIEtaIEta, &b_Den_Pho_SigmaIEtaIEta);
   fChain->SetBranchAddress("Fake62_Pho_Pt", &Fake62_Pho_Pt, &b_Fake62_Pho_Pt);
   fChain->SetBranchAddress("Fake62_Pho_SigmaIEtaIEta", &Fake62_Pho_SigmaIEtaIEta, &b_Fake62_Pho_SigmaIEtaIEta);
   fChain->SetBranchAddress("Fake49_Pho_Pt", &Fake49_Pho_Pt, &b_Fake49_Pho_Pt);
   fChain->SetBranchAddress("Fake49_Pho_SigmaIEtaIEta", &Fake49_Pho_SigmaIEtaIEta, &b_Fake49_Pho_SigmaIEtaIEta);
   fChain->SetBranchAddress("Fake155_Pho_Pt", &Fake155_Pho_Pt, &b_Fake155_Pho_Pt);
   fChain->SetBranchAddress("Fake155_Pho_SigmaIEtaIEta", &Fake155_Pho_SigmaIEtaIEta, &b_Fake155_Pho_SigmaIEtaIEta);
   fChain->SetBranchAddress("Fake510_Pho_Pt", &Fake510_Pho_Pt, &b_Fake510_Pho_Pt);
   fChain->SetBranchAddress("Fake510_Pho_SigmaIEtaIEta", &Fake510_Pho_SigmaIEtaIEta, &b_Fake510_Pho_SigmaIEtaIEta);
   fChain->SetBranchAddress("numGoodPhotons", &numGoodPhotons, &b_numGoodPhotons);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_dummy_empty_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_dummy_empty_fBits);
   fChain->SetBranchAddress("fP.fUniqueID", &fP_fUniqueID, &b_dummy_empty_fP_fUniqueID);
   fChain->SetBranchAddress("fP.fBits", &fP_fBits, &b_dummy_empty_fP_fBits);
   fChain->SetBranchAddress("fP.fX", &fP_fX, &b_dummy_empty_fP_fX);
   fChain->SetBranchAddress("fP.fY", &fP_fY, &b_dummy_empty_fP_fY);
   fChain->SetBranchAddress("fP.fZ", &fP_fZ, &b_dummy_empty_fP_fZ);
   fChain->SetBranchAddress("fE", &fE, &b_dummy_empty_fE);
}

Bool_t MakeTemp::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef MakeTemp_cxx
