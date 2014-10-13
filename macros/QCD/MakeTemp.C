#define MakeTemp_cxx

//
// Root > T->Process("MakeTemp.C")
// Root > T->Process("MakeTemp.C","some options")
// Root > T->Process("MakeTemp.C+")
//

#include "MakeTemp.h"
#include <TH2.h>
#include <TStyle.h>
#include <TProfile.h>
#include <TVector3.h>
#include <iostream>
#include <fstream>


TH1F *h_num_1;
TH1F *h_denom_1;
TH1F *h_fake_1;

TH1F *h_num_2;
TH1F *h_denom_2;
TH1F *h_fake_2;

TH1F *h_num_3;
TH1F *h_denom_3;
TH1F *h_fake_3;

TH1F *h_num_4;
TH1F *h_denom_4;
TH1F *h_fake_4;

TH1F *h_num_5;
TH1F *h_denom_5;
TH1F *h_fake_5;

TH1F *h_num_6;
TH1F *h_denom_6;
TH1F *h_fake_6;

TH1F *h_num_7;
TH1F *h_denom_7;
TH1F *h_fake_7;


TFile fout("dataTemplates_Zeynep.root","RECREATE");



void MakeTemp::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();


 h_num_1   = new TH1F("h_num_1","sinin",60,0.,0.03);
 h_denom_1 = new TH1F("h_denom_1","sinin",60,0.,0.03);
 h_fake_1  = new TH1F("h_fake_1","sinin",60,0.,0.03);

 
 h_num_2   = new TH1F("h_num_2","sinin",60,0.,0.03);
 h_denom_2 = new TH1F("h_denom_2","sinin",60,0.,0.03);
 h_fake_2  = new TH1F("h_fake_2","sinin",60,0.,0.03);

 
 h_num_3   = new TH1F("h_num_3","sinin",60,0.,0.03);
 h_denom_3 = new TH1F("h_denom_3","sinin",60,0.,0.03);
 h_fake_3  = new TH1F("h_fake_3","sinin",60,0.,0.03);

 
 h_num_4   = new TH1F("h_num_4","sinin",60,0.,0.03);
 h_denom_4 = new TH1F("h_denom_4","sinin",60,0.,0.03);
 h_fake_4  = new TH1F("h_fake_4","sinin",60,0.,0.03);

 
 h_num_5   = new TH1F("h_num_5","sinin",60,0.,0.03);
 h_denom_5 = new TH1F("h_denom_5","sinin",60,0.,0.03);
 h_fake_5  = new TH1F("h_fake_5","sinin",60,0.,0.03);

 
 h_num_6   = new TH1F("h_num_6","sinin",60,0.,0.03);
 h_denom_6 = new TH1F("h_denom_6","sinin",60,0.,0.03);
 h_fake_6  = new TH1F("h_fake_6","sinin",60,0.,0.03);

 
 h_num_7   = new TH1F("h_num_7","sinin",60,0.,0.03);
 h_denom_7 = new TH1F("h_denom_7","sinin",60,0.,0.03);
 h_fake_7  = new TH1F("h_fake_7","sinin",60,0.,0.03);


}

void MakeTemp::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t MakeTemp::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either MakeTemp::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.



 GetAllEntries(entry);
 //for(int j=0;j<7;j++){
     if(Num_Pho_Pt>0. && Num_Pho_SigmaIEtaIEta>0.001){//numerator
     if(Num_Pho_Pt>30.&&Num_Pho_Pt<40.)   h_num_1->Fill(Num_Pho_SigmaIEtaIEta);
     if(Num_Pho_Pt>40.&&Num_Pho_Pt<50.)   h_num_2->Fill(Num_Pho_SigmaIEtaIEta);
     if(Num_Pho_Pt>50.&&Num_Pho_Pt<60.)   h_num_3->Fill(Num_Pho_SigmaIEtaIEta);
     if(Num_Pho_Pt>60.&&Num_Pho_Pt<70.)   h_num_4->Fill(Num_Pho_SigmaIEtaIEta);
     if(Num_Pho_Pt>70.&&Num_Pho_Pt<80.)   h_num_5->Fill(Num_Pho_SigmaIEtaIEta);
     if(Num_Pho_Pt>80.&&Num_Pho_Pt<100.)  h_num_6->Fill(Num_Pho_SigmaIEtaIEta);
     if(Num_Pho_Pt>100.&&Num_Pho_Pt<130.) h_num_7->Fill(Num_Pho_SigmaIEtaIEta);
   }
   if(Den_Pho_Pt>0. && Den_Pho_SigmaIEtaIEta>0.001){//denominator
     if(Den_Pho_Pt>30.&&Den_Pho_Pt<40.)   h_denom_1->Fill(Den_Pho_SigmaIEtaIEta);
     if(Den_Pho_Pt>40.&&Den_Pho_Pt<50.)   h_denom_2->Fill(Den_Pho_SigmaIEtaIEta);
     if(Den_Pho_Pt>50.&&Den_Pho_Pt<60.)   h_denom_3->Fill(Den_Pho_SigmaIEtaIEta);
     if(Den_Pho_Pt>60.&&Den_Pho_Pt<70.)   h_denom_4->Fill(Den_Pho_SigmaIEtaIEta);
     if(Den_Pho_Pt>70.&&Den_Pho_Pt<80.)   h_denom_5->Fill(Den_Pho_SigmaIEtaIEta);
     if(Den_Pho_Pt>80.&&Den_Pho_Pt<100.)  h_denom_6->Fill(Den_Pho_SigmaIEtaIEta);
     if(Den_Pho_Pt>100.&&Den_Pho_Pt<130.) h_denom_7->Fill(Den_Pho_SigmaIEtaIEta);
   }
   if(Fake62_Pho_Pt>0. && Fake62_Pho_SigmaIEtaIEta>0.001){//fake
     if(Fake62_Pho_Pt>30.&&Fake62_Pho_Pt<40.)   h_fake_1->Fill(Fake62_Pho_SigmaIEtaIEta);
     if(Fake62_Pho_Pt>40.&&Fake62_Pho_Pt<50.)   h_fake_2->Fill(Fake62_Pho_SigmaIEtaIEta);
     if(Fake62_Pho_Pt>50.&&Fake62_Pho_Pt<60.)   h_fake_3->Fill(Fake62_Pho_SigmaIEtaIEta);
     if(Fake62_Pho_Pt>60.&&Fake62_Pho_Pt<70.)   h_fake_4->Fill(Fake62_Pho_SigmaIEtaIEta);
     if(Fake62_Pho_Pt>70.&&Fake62_Pho_Pt<80.)   h_fake_5->Fill(Fake62_Pho_SigmaIEtaIEta);
     if(Fake62_Pho_Pt>80.&&Fake62_Pho_Pt<100.)  h_fake_6->Fill(Fake62_Pho_SigmaIEtaIEta);
     if(Fake62_Pho_Pt>100.&&Fake62_Pho_Pt<130.) h_fake_7->Fill(Fake62_Pho_SigmaIEtaIEta);
   }


   return kTRUE;
}

void MakeTemp::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void MakeTemp::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

 cout<<"terminating, creating dataTemplates_met0.root"<<endl;
 fout.cd();
 fout.Write();
 fout.Close();


}


void MakeTemp::GetAllEntries(Long64_t entry)
{
   // List of branches
   b_Num_Pho_Pt->GetEntry(entry);
   b_Num_Pho_SigmaIEtaIEta->GetEntry(entry);
   b_Fake62_Pho_Pt->GetEntry(entry);
   b_Fake62_Pho_SigmaIEtaIEta->GetEntry(entry);
   b_Den_Pho_Pt->GetEntry(entry);
   b_Den_Pho_SigmaIEtaIEta->GetEntry(entry);
}
