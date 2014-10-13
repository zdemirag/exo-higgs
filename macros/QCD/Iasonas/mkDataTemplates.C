#define mkDataTemplates_cxx
#include "mkDataTemplates.h"
#include <TH2.h>
#include <TStyle.h>
#include <TProfile.h>
#include <TVector3.h>
#include <iostream>
#include <fstream>

TH1F *h_num_1;
TH1F *h_denom_1;
TH1F *h_fake_1;
TH1F *h_fake48_1;
TH1F *h_fake155_1;
TH1F *h_fake510_1;

TH1F *h_num_2;
TH1F *h_denom_2;
TH1F *h_fake_2;
TH1F *h_fake48_2;
TH1F *h_fake155_2;
TH1F *h_fake510_2;

TH1F *h_num_3;
TH1F *h_denom_3;
TH1F *h_fake_3;
TH1F *h_fake48_3;
TH1F *h_fake155_3;
TH1F *h_fake510_3;

TH1F *h_num_4;
TH1F *h_denom_4;
TH1F *h_fake_4;
TH1F *h_fake48_4;
TH1F *h_fake155_4;
TH1F *h_fake510_4;

TH1F *h_num_5;
TH1F *h_denom_5;
TH1F *h_fake_5;
TH1F *h_fake48_5;
TH1F *h_fake155_5;
TH1F *h_fake510_5;

TH1F *h_num_6;
TH1F *h_denom_6;
TH1F *h_fake_6;
TH1F *h_fake48_6;
TH1F *h_fake155_6;
TH1F *h_fake510_6;

TH1F *h_num_7;
TH1F *h_denom_7;
TH1F *h_fake_7;
TH1F *h_fake48_7;
TH1F *h_fake155_7;
TH1F *h_fake510_7;

TFile fout("./dataTemplates_met0.root","RECREATE");

void mkDataTemplates::Begin(TTree * /*tree*/)
{
 TString option = GetOption();
 
 h_num_1   = new TH1F("h_num_1","sinin",60,0.,0.03);
 h_denom_1 = new TH1F("h_denom_1","sinin",60,0.,0.03);
 h_fake_1  = new TH1F("h_fake_1","sinin",60,0.,0.03);
 h_fake48_1  = new TH1F("h_fake48_1","sinin",60,0.,0.03);
 h_fake155_1  = new TH1F("h_fake155_1","sinin",60,0.,0.03);
 h_fake510_1  = new TH1F("h_fake510_1","sinin",60,0.,0.03);
 
 h_num_2   = new TH1F("h_num_2","sinin",60,0.,0.03);
 h_denom_2 = new TH1F("h_denom_2","sinin",60,0.,0.03);
 h_fake_2  = new TH1F("h_fake_2","sinin",60,0.,0.03);
 h_fake48_2  = new TH1F("h_fake48_2","sinin",60,0.,0.03);
 h_fake155_2  = new TH1F("h_fake155_2","sinin",60,0.,0.03);
 h_fake510_2  = new TH1F("h_fake510_2","sinin",60,0.,0.03);
 
 h_num_3   = new TH1F("h_num_3","sinin",60,0.,0.03);
 h_denom_3 = new TH1F("h_denom_3","sinin",60,0.,0.03);
 h_fake_3  = new TH1F("h_fake_3","sinin",60,0.,0.03);
 h_fake48_3  = new TH1F("h_fake48_3","sinin",60,0.,0.03);
 h_fake155_3  = new TH1F("h_fake155_3","sinin",60,0.,0.03);
 h_fake510_3  = new TH1F("h_fake510_3","sinin",60,0.,0.03);
 
 h_num_4   = new TH1F("h_num_4","sinin",60,0.,0.03);
 h_denom_4 = new TH1F("h_denom_4","sinin",60,0.,0.03);
 h_fake_4  = new TH1F("h_fake_4","sinin",60,0.,0.03);
 h_fake48_4  = new TH1F("h_fake48_4","sinin",60,0.,0.03);
 h_fake155_4  = new TH1F("h_fake155_4","sinin",60,0.,0.03);
 h_fake510_4  = new TH1F("h_fake510_4","sinin",60,0.,0.03);
 
 h_num_5   = new TH1F("h_num_5","sinin",60,0.,0.03);
 h_denom_5 = new TH1F("h_denom_5","sinin",60,0.,0.03);
 h_fake_5  = new TH1F("h_fake_5","sinin",60,0.,0.03);
 h_fake48_5  = new TH1F("h_fake48_5","sinin",60,0.,0.03);
 h_fake155_5  = new TH1F("h_fake155_5","sinin",60,0.,0.03);
 h_fake510_5  = new TH1F("h_fake510_5","sinin",60,0.,0.03);
 
 h_num_6   = new TH1F("h_num_6","sinin",60,0.,0.03);
 h_denom_6 = new TH1F("h_denom_6","sinin",60,0.,0.03);
 h_fake_6  = new TH1F("h_fake_6","sinin",60,0.,0.03);
 h_fake48_6  = new TH1F("h_fake48_6","sinin",60,0.,0.03);
 h_fake155_6  = new TH1F("h_fake155_6","sinin",60,0.,0.03);
 h_fake510_6  = new TH1F("h_fake510_6","sinin",60,0.,0.03);
 
 h_num_7   = new TH1F("h_num_7","sinin",60,0.,0.03);
 h_denom_7 = new TH1F("h_denom_7","sinin",60,0.,0.03);
 h_fake_7  = new TH1F("h_fake_7","sinin",60,0.,0.03);
 h_fake48_7  = new TH1F("h_fake48_7","sinin",60,0.,0.03);
 h_fake155_7  = new TH1F("h_fake155_7","sinin",60,0.,0.03);
 h_fake510_7  = new TH1F("h_fake510_7","sinin",60,0.,0.03);
 
}

void mkDataTemplates::SlaveBegin(TTree * /*tree*/)
{ TString option = GetOption(); }

Bool_t mkDataTemplates::Process(Long64_t entry)
{
 GetAllEntries(entry);
 //for(int j=0;j<7;j++){
 if(pfmet_pt<40.){
     if(ph_N_Pt>0. && ph_N_sinin>0.001){//numerator
     if(ph_N_Pt>30.&&ph_N_Pt<40.)   h_num_1->Fill(ph_N_sinin);
     if(ph_N_Pt>40.&&ph_N_Pt<50.)   h_num_2->Fill(ph_N_sinin);
     if(ph_N_Pt>50.&&ph_N_Pt<60.)   h_num_3->Fill(ph_N_sinin);
     if(ph_N_Pt>60.&&ph_N_Pt<70.)   h_num_4->Fill(ph_N_sinin);
     if(ph_N_Pt>70.&&ph_N_Pt<80.)   h_num_5->Fill(ph_N_sinin);
     if(ph_N_Pt>80.&&ph_N_Pt<100.)  h_num_6->Fill(ph_N_sinin);
     if(ph_N_Pt>100.&&ph_N_Pt<130.) h_num_7->Fill(ph_N_sinin);
   }
   if(ph_DLU_Pt>0. && ph_DLU_sinin>0.001){//denominator
     if(ph_DLU_Pt>30.&&ph_DLU_Pt<40.)   h_denom_1->Fill(ph_DLU_sinin);
     if(ph_DLU_Pt>40.&&ph_DLU_Pt<50.)   h_denom_2->Fill(ph_DLU_sinin);
     if(ph_DLU_Pt>50.&&ph_DLU_Pt<60.)   h_denom_3->Fill(ph_DLU_sinin);
     if(ph_DLU_Pt>60.&&ph_DLU_Pt<70.)   h_denom_4->Fill(ph_DLU_sinin);
     if(ph_DLU_Pt>70.&&ph_DLU_Pt<80.)   h_denom_5->Fill(ph_DLU_sinin);
     if(ph_DLU_Pt>80.&&ph_DLU_Pt<100.)  h_denom_6->Fill(ph_DLU_sinin);
     if(ph_DLU_Pt>100.&&ph_DLU_Pt<130.) h_denom_7->Fill(ph_DLU_sinin);
   }
   if(ph_F26_Pt>0. && ph_F26_sinin>0.001){//fake
     if(ph_F26_Pt>30.&&ph_F26_Pt<40.)   h_fake_1->Fill(ph_F26_sinin);
     if(ph_F26_Pt>40.&&ph_F26_Pt<50.)   h_fake_2->Fill(ph_F26_sinin);
     if(ph_F26_Pt>50.&&ph_F26_Pt<60.)   h_fake_3->Fill(ph_F26_sinin);
     if(ph_F26_Pt>60.&&ph_F26_Pt<70.)   h_fake_4->Fill(ph_F26_sinin);
     if(ph_F26_Pt>70.&&ph_F26_Pt<80.)   h_fake_5->Fill(ph_F26_sinin);
     if(ph_F26_Pt>80.&&ph_F26_Pt<100.)  h_fake_6->Fill(ph_F26_sinin);
     if(ph_F26_Pt>100.&&ph_F26_Pt<130.) h_fake_7->Fill(ph_F26_sinin);
   }
   ///////////////////////////////////////////////////////////////////////////
   if(ph_F48_Pt>0. && ph_F48_sinin>0.001){//fake
     if(ph_F48_Pt>30.&&ph_F48_Pt<40.)   h_fake48_1->Fill(ph_F48_sinin);
     if(ph_F48_Pt>40.&&ph_F48_Pt<50.)   h_fake48_2->Fill(ph_F48_sinin);
     if(ph_F48_Pt>50.&&ph_F48_Pt<60.)   h_fake48_3->Fill(ph_F48_sinin);
     if(ph_F48_Pt>60.&&ph_F48_Pt<70.)   h_fake48_4->Fill(ph_F48_sinin);
     if(ph_F48_Pt>70.&&ph_F48_Pt<80.)   h_fake48_5->Fill(ph_F48_sinin);
     if(ph_F48_Pt>80.&&ph_F48_Pt<100.)  h_fake48_6->Fill(ph_F48_sinin);
     if(ph_F48_Pt>100.&&ph_F48_Pt<130.) h_fake48_7->Fill(ph_F48_sinin);
   }
   if(ph_F155_Pt>0. && ph_F155_sinin>0.001){//fake
     if(ph_F155_Pt>30.&&ph_F155_Pt<40.)   h_fake155_1->Fill(ph_F155_sinin);
     if(ph_F155_Pt>40.&&ph_F155_Pt<50.)   h_fake155_2->Fill(ph_F155_sinin);
     if(ph_F155_Pt>50.&&ph_F155_Pt<60.)   h_fake155_3->Fill(ph_F155_sinin);
     if(ph_F155_Pt>60.&&ph_F155_Pt<70.)   h_fake155_4->Fill(ph_F155_sinin);
     if(ph_F155_Pt>70.&&ph_F155_Pt<80.)   h_fake155_5->Fill(ph_F155_sinin);
     if(ph_F155_Pt>80.&&ph_F155_Pt<100.)  h_fake155_6->Fill(ph_F155_sinin);
     if(ph_F155_Pt>100.&&ph_F155_Pt<130.) h_fake155_7->Fill(ph_F155_sinin);
   }
   if(ph_F510_Pt>0. && ph_F510_sinin>0.001){//fake
     if(ph_F510_Pt>30.&&ph_F510_Pt<40.)   h_fake510_1->Fill(ph_F510_sinin);
     if(ph_F510_Pt>40.&&ph_F510_Pt<50.)   h_fake510_2->Fill(ph_F510_sinin);
     if(ph_F510_Pt>50.&&ph_F510_Pt<60.)   h_fake510_3->Fill(ph_F510_sinin);
     if(ph_F510_Pt>60.&&ph_F510_Pt<70.)   h_fake510_4->Fill(ph_F510_sinin);
     if(ph_F510_Pt>70.&&ph_F510_Pt<80.)   h_fake510_5->Fill(ph_F510_sinin);
     if(ph_F510_Pt>80.&&ph_F510_Pt<100.)  h_fake510_6->Fill(ph_F510_sinin);
     if(ph_F510_Pt>100.&&ph_F510_Pt<130.) h_fake510_7->Fill(ph_F510_sinin);
   }
 }  
 //}
 return kTRUE;
}

void mkDataTemplates::SlaveTerminate(){}

void mkDataTemplates::Terminate()
{
 cout<<"terminating, creating dataTemplates_met0.root"<<endl;
 fout.cd();
 fout.Write();
 fout.Close();
}

//////////////////////////////////////////////////////////////
void mkDataTemplates::GetAllEntries(Long64_t entry)
{
   // List of branches
   b_ph_N_Pt->GetEntry(entry);
   b_ph_N_sinin->GetEntry(entry);
   b_ph_F26_Pt->GetEntry(entry);
   b_ph_F26_sinin->GetEntry(entry);
   b_ph_F48_Pt->GetEntry(entry);
   b_ph_F48_sinin->GetEntry(entry);
   b_ph_F155_Pt->GetEntry(entry);
   b_ph_F155_sinin->GetEntry(entry);
   b_ph_F510_Pt->GetEntry(entry);
   b_ph_F510_sinin->GetEntry(entry);
   b_ph_DLU_Pt->GetEntry(entry);
   b_ph_DLU_sinin->GetEntry(entry);
   b_pfmet_pt->GetEntry(entry);
}








