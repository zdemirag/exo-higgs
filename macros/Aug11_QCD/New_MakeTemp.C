#define New_MakeTemp_cxx

#include "New_MakeTemp.h"
#include <TH2.h>
#include <TStyle.h>
#include <TProfile.h>
#include <TVector3.h>
#include <iostream>
#include <fstream>

TH1F *h_num_1;
TH1F *h_1;
TH1F *h_denom_1;
TH1F *h_fake_1;

TH1F *h_num_2;
TH1F *h_2;
TH1F *h_denom_2;
TH1F *h_fake_2;

TH1F *h_num_3;
TH1F *h_3;
TH1F *h_denom_3;
TH1F *h_fake_3;

TH1F *h_num_4;
TH1F *h_4;
TH1F *h_denom_4;
TH1F *h_fake_4;

TH1F *h_num_5;
TH1F *h_5;
TH1F *h_denom_5;
TH1F *h_fake_5;

TH1F *h_num_6;
TH1F *h_6;
TH1F *h_denom_6;
TH1F *h_fake_6;

TH1F *h_num_7;
TH1F *h_7;
TH1F *h_denom_7;
TH1F *h_fake_7;

TFile fout("dataTemplates_Zeynep.root","RECREATE");



void New_MakeTemp::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   h_1   = new TH1F("h_1","sinin",60,0.,0.03);
   h_num_1   = new TH1F("h_num_1","sinin",60,0.,0.03);
   h_denom_1 = new TH1F("h_denom_1","sinin",60,0.,0.03);
   h_fake_1  = new TH1F("h_fake_1","sinin",60,0.,0.03);
   
   h_2   = new TH1F("h_2","sinin",60,0.,0.03); 
   h_num_2   = new TH1F("h_num_2","sinin",60,0.,0.03);
   h_denom_2 = new TH1F("h_denom_2","sinin",60,0.,0.03);
   h_fake_2  = new TH1F("h_fake_2","sinin",60,0.,0.03);
   
   h_3   = new TH1F("h_3","sinin",60,0.,0.03);
   h_num_3   = new TH1F("h_num_3","sinin",60,0.,0.03);
   h_denom_3 = new TH1F("h_denom_3","sinin",60,0.,0.03);
   h_fake_3  = new TH1F("h_fake_3","sinin",60,0.,0.03);
   
   h_4   = new TH1F("h_4","sinin",60,0.,0.03);   
   h_num_4   = new TH1F("h_num_4","sinin",60,0.,0.03);
   h_denom_4 = new TH1F("h_denom_4","sinin",60,0.,0.03);
   h_fake_4  = new TH1F("h_fake_4","sinin",60,0.,0.03);
   
 
   h_5   = new TH1F("h_5","sinin",60,0.,0.03);
   h_num_5   = new TH1F("h_num_5","sinin",60,0.,0.03);
   h_denom_5 = new TH1F("h_denom_5","sinin",60,0.,0.03);
   h_fake_5  = new TH1F("h_fake_5","sinin",60,0.,0.03);
   
   
   h_6   = new TH1F("h_6","sinin",60,0.,0.03);
   h_num_6   = new TH1F("h_num_6","sinin",60,0.,0.03);
   h_denom_6 = new TH1F("h_denom_6","sinin",60,0.,0.03);
   h_fake_6  = new TH1F("h_fake_6","sinin",60,0.,0.03);
   
   
   h_7   = new TH1F("h_7","sinin",60,0.,0.03);
   h_num_7   = new TH1F("h_num_7","sinin",60,0.,0.03);
   h_denom_7 = new TH1F("h_denom_7","sinin",60,0.,0.03);
   h_fake_7  = new TH1F("h_fake_7","sinin",60,0.,0.03);
   


}

void New_MakeTemp::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t New_MakeTemp::Process(Long64_t entry)
{

    GetAllEntries(entry);

    //if( !(njet > 0 )) return kTRUE;
    if( !(MET < 40)) return kTRUE;

    if( !(Pho_SigmaIEtaIEta>0.001) ) return kTRUE;

    //std::cout << "I am about to check stuff" << std::endl;

    if(passedNum==1){
        if(Pho_Pt>30. && Pho_Pt<40.)   h_1->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>40. && Pho_Pt<50.)   h_2->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>50. && Pho_Pt<60.)   h_3->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>60. && Pho_Pt<70.)   h_4->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>70. && Pho_Pt<80.)   h_5->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>80. && Pho_Pt<100.)  h_6->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>100.&& Pho_Pt<130.)  h_7->Fill(Pho_SigmaIEtaIEta);
    }

    if(passedNum==1 && Pho_SigmaIEtaIEta < 0.011){
        //std::cout <<"Is Num like photon" << std::endl;
        if(Pho_Pt>30. && Pho_Pt<40.)   h_num_1->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>40. && Pho_Pt<50.)   h_num_2->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>50. && Pho_Pt<60.)   h_num_3->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>60. && Pho_Pt<70.)   h_num_4->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>70. && Pho_Pt<80.)   h_num_5->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>80. && Pho_Pt<100.)  h_num_6->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>100.&& Pho_Pt<130.)  h_num_7->Fill(Pho_SigmaIEtaIEta);
    }

    if(passedDen==1){
        //std::cout <<"Is Den like photon" << std::endl;
        
        if(Pho_Pt>30.&&Pho_Pt<40.)   h_denom_1->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>40.&&Pho_Pt<50.)   h_denom_2->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>50.&&Pho_Pt<60.)   h_denom_3->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>60.&&Pho_Pt<70.)   h_denom_4->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>70.&&Pho_Pt<80.)   h_denom_5->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>80.&&Pho_Pt<100.)  h_denom_6->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>100.&&Pho_Pt<130.) h_denom_7->Fill(Pho_SigmaIEtaIEta);
    }


 if(passedFake==1){
        if(Pho_Pt>30.&&Pho_Pt<40.)   h_fake_1->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>40.&&Pho_Pt<50.)   h_fake_2->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>50.&&Pho_Pt<60.)   h_fake_3->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>60.&&Pho_Pt<70.)   h_fake_4->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>70.&&Pho_Pt<80.)   h_fake_5->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>80.&&Pho_Pt<100.)  h_fake_6->Fill(Pho_SigmaIEtaIEta);
        if(Pho_Pt>100.&&Pho_Pt<130.) h_fake_7->Fill(Pho_SigmaIEtaIEta);
    }

 //std::cout << "end" << std::endl;

   return kTRUE;
}

void New_MakeTemp::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void New_MakeTemp::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
    std::cout<<"terminating, creating dataTemplates_met0.root"<<std::endl;
 fout.cd();
 fout.Write();
 fout.Close();


}


void New_MakeTemp::GetAllEntries(Long64_t entry)
{
   // List of branches
   b_Pho_Pt->GetEntry(entry);
   b_Pho_SigmaIEtaIEta->GetEntry(entry);
   b_passedNum->GetEntry(entry);
   b_passedDen->GetEntry(entry);
   b_passedFake->GetEntry(entry);
   b_njet->GetEntry(entry);

}
