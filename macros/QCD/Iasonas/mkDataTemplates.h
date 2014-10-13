//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jan 14 14:31:49 2014 by ROOT version 5.34/03
// from TTree AnalyzerTree/HZ(nunu)Gamma Analyzer Tree
// found on file: dataAll.root
//////////////////////////////////////////////////////////

#ifndef mkDataTemplates_h
#define mkDataTemplates_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.
#include <TVector2.h>
#include <TObject.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class mkDataTemplates : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Float_t         ph_N_Pt;
   Float_t         ph_N_sinin;
   Float_t         ph_F26_Pt;
   Float_t         ph_F26_sinin;
   Float_t         ph_F48_Pt;
   Float_t         ph_F48_sinin;
   Float_t         ph_F155_Pt;
   Float_t         ph_F155_sinin;
   Float_t         ph_F510_Pt;
   Float_t         ph_F510_sinin;
   Float_t         ph_DLU_Pt;
   Float_t         ph_DLU_sinin;
   Float_t         pfmet_pt;

   // List of branches
   TBranch        *b_ph_N_Pt;   //!
   TBranch        *b_ph_N_sinin;   //!
   TBranch        *b_ph_F26_Pt;   //!
   TBranch        *b_ph_F26_sinin;   //!
   TBranch        *b_ph_F48_Pt;   //!
   TBranch        *b_ph_F48_sinin;   //!
   TBranch        *b_ph_F155_Pt;   //!
   TBranch        *b_ph_F155_sinin;   //!
   TBranch        *b_ph_F510_Pt;   //!
   TBranch        *b_ph_F510_sinin;   //!
   TBranch        *b_ph_DLU_Pt;   //!
   TBranch        *b_ph_DLU_sinin;   //!
   TBranch        *b_pfmet_pt;   //!

   mkDataTemplates(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~mkDataTemplates() { }
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

   ClassDef(mkDataTemplates,0);
};

#endif

#ifdef mkDataTemplates_cxx
void mkDataTemplates::Init(TTree *tree)
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

   fChain->SetBranchAddress("ph_N_Pt", &ph_N_Pt, &b_ph_N_Pt);
   fChain->SetBranchAddress("ph_N_sinin", &ph_N_sinin, &b_ph_N_sinin);
   fChain->SetBranchAddress("ph_F26_Pt", &ph_F26_Pt, &b_ph_F26_Pt);
   fChain->SetBranchAddress("ph_F26_sinin", &ph_F26_sinin, &b_ph_F26_sinin);
   fChain->SetBranchAddress("ph_F48_Pt", &ph_F48_Pt, &b_ph_F48_Pt);
   fChain->SetBranchAddress("ph_F48_sinin", &ph_F48_sinin, &b_ph_F48_sinin);
   fChain->SetBranchAddress("ph_F155_Pt", &ph_F155_Pt, &b_ph_F155_Pt);
   fChain->SetBranchAddress("ph_F155_sinin", &ph_F155_sinin, &b_ph_F155_sinin);
   fChain->SetBranchAddress("ph_F510_Pt", &ph_F510_Pt, &b_ph_F510_Pt);
   fChain->SetBranchAddress("ph_F510_sinin", &ph_F510_sinin, &b_ph_F510_sinin);
   fChain->SetBranchAddress("ph_DLU_Pt", &ph_DLU_Pt, &b_ph_DLU_Pt);
   fChain->SetBranchAddress("ph_DLU_sinin", &ph_DLU_sinin, &b_ph_DLU_sinin);
   fChain->SetBranchAddress("pfmet_pt", &pfmet_pt, &b_pfmet_pt);
}

Bool_t mkDataTemplates::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef mkDataTemplates_cxx
