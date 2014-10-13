#define phiCorr_cxx
#include "phiCorr.h"
//#include "tesingPhi.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <THStack.h>
#include <iostream>
#include <TInterpreter.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TLegend.h>
#include <iomanip>
#include <string>
#include <vector>
#include <TColor.h>
#include <TStyle.h>
#include <TProfile.h>

void phiCorr::Loop()
{

  gStyle->SetOptStat(kFALSE);

  //TFile *outputFile = new TFile("PhiCorr_data.root","RECREATE");
  //TFile *outputFile = new TFile("PhiCorr_zg.root","RECREATE");
  //TFile *outputFile = new TFile("PhiCorr_pj.root","RECREATE");
  TFile *outputFile = new TFile("PhiCorr_MadGraphpj.root","RECREATE");

  TH1F *h_phi       = new TH1F("h_phi","Old #Phi;#Phi;Events",100,-5,5);
  TH1F *h_phi_new   = new TH1F("h_phi_new","New #Phi;#Phi;Events",100,-5,5);
  TH1F *h_phi_new_a   = new TH1F("h_phi_new_a","New #Phi;#Phi;Events",100,-5,5);

  TH2D *h_mex = new TH2D("h_mex","<MEx> vs NVtx;  NVtx; <MEx>",50,0,50,100,-50,50);
  TH2D *h_mey = new TH2D("h_mey","<MEy> vs NVtx;  NVtx; <MEy>",50,0,50,100,-50,50);

  TH1F *h_met       = new TH1F("h_met","Old MET;MET [GeV];Events",200,0,200);
  TH1F *h_met_new   = new TH1F("h_met_new","New MET;MET [GeV];Events",200,0,200);
  TH1F *h_met_new_a   = new TH1F("h_met_new_a","New MET;MET [GeV];Events",200,0,200);

  TH1F *h_mex_       = new TH1F("h_mex_","MEx;MET [GeV];Events",200,-200,200);
  TH1F *h_mex_a       = new TH1F("h_mex_a","MEx_a;MET [GeV];Events",200,-200,200);
  TH1F *h_mey_       = new TH1F("h_mey_","MEy;MET [GeV];Events",200,-200,200);
  TH1F *h_mey_a       = new TH1F("h_mey_a","MEy_a;MET [GeV];Events",200,-200,200);


  TProfile *h_met_phi = new TProfile("h_met_phi","<MET> vs Phi;  NVtx; MET",100,0,500,0,5);
  TProfile *h_met_phi_a = new TProfile("h_met_phi_a","<MET> vs Phi;  NVtx; MET",100,0,500,0,5);



  //TProfile *h_mex = new TProfile("h_mex","<MEx> vs NVtx;  NVtx; <MEx>",50,0,50,0,50);
  //TProfile *h_mey = new TProfile("h_mey","<MEy> vs NVtx;  NVtx; <MEy>",50,0,50,0,50);

  if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   std::cout << nentries << std::endl;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      TLorentzVector MET_L;
      TLorentzVector MET_corr;
      MET_L.SetPxPyPzE(MEx_old,MEy_old,0,MET_old);
    
      if(Pho_Pt>30. && TMath::Abs(Pho_Eta)<1.442 && Pho_R9 > 0.9){
          h_mex->Fill(NVtx,MEx_old);
          h_mey->Fill(NVtx,MEy_old);
          h_met->Fill(MET_old);
          h_phi->Fill(TMath::ATan2(MEy_old,MEx_old));
      }

      //data
      //float MEx_corr = MEx - (0.639521 + 0.229545*(NVtx));
      //float MEy_corr = MEy - (-0.479465 - 0.0647124*(NVtx));
      
      //znunuG
      //float MEx_corr = MEx - (0.0626902 - 0.0141362*NVtx);
      //float MEy_corr = MEy - (-0.146358 - 0.0830809*NVtx);
  
      //pjets
      //float MEx_corr = MEx - (0.186578 - 0.0323318*NVtx);
      //float MEy_corr = MEy - (-0.277675 - 0.0873093*NVtx);
      

      //MADGRAPH GJETS
      float MEx_corr = MEx_old - (0.443271 - 0.0347408*NVtx);//(0.414879  - 0.0224688 *NVtx);
      float MEy_corr = MEy_old - (-0.169244 - 0.0931838*NVtx);//(0.0688546 - 0.0298695 *NVtx);

      //float MEx_corr = MEx - (0.502649 - 0.0613027*NVtx + 0.00357629*NVtx*NVtx -8.54522e-05*NVtx*NVtx*NVtx);
      //float MEy_corr = MEy - (0.341819 - 0.105503*NVtx + 0.00564646*NVtx*NVtx - 0.000119433*NVtx*NVtx*NVtx);

      float Met_corr = sqrt(MEx_corr**2+MEy_corr**2);
      MET_corr.SetPxPyPzE(MEx_corr,MEy_corr,0,Met_corr);     

      if(Pho_Pt>30. && TMath::Abs(Pho_Eta)<1.442 &&  Pho_R9 > 0.9){
          h_phi_new->Fill(TMath::ATan2(MEy_corr,MEx_corr));
          h_met_new->Fill(Met_corr);
          h_met_phi->Fill(TMath::ATan2(MEy_corr,MEx_corr),Met_corr);
          h_mex_->Fill(MEx_corr);
          h_mey_->Fill(MEy_corr);
          
      }
      if(Pho_Pt>30. && TMath::Abs(Pho_Eta)<1.442 &&  Pho_R9 > 0.9 && Met_corr>40.){
          h_phi_new_a->Fill(TMath::ATan2(MEy_corr,MEx_corr));
          h_met_new_a->Fill(Met_corr);
          h_met_phi_a->Fill(TMath::ATan2(MEy_corr,MEx_corr),Met_corr);
          h_mex_a->Fill(MEx_corr);
          h_mey_a->Fill(MEy_corr);
      }
      

   }

   TH1D* projection_x;
   TH1D* projection_y;

   int bin_x = h_mex->GetNbinsX();
   int bin_y = h_mey->GetNbinsX();

   TH1D* xVsN = new TH1D("x","x",50,0,50);
   TH1D* yVsN = new TH1D("y","y",50,0,50);




   for(int k=1; k <= bin_x; k++){
     
     projection_x = h_mex->ProjectionY("projection",k,k+1);
     mean_x = projection_x->GetMean(1);
     error_x = projection_x->GetMean(11);

     projection_y = h_mey->ProjectionY("projection",k,k+1);
     mean_y = projection_y->GetMean(1);
     error_y = projection_y->GetMean(11);
     
     xVsN -> SetBinContent(k,mean_x);
     xVsN -> SetBinError(k,error_x);
     
     yVsN -> SetBinContent(k,mean_y);
     yVsN -> SetBinError(k,error_y);



   }
   
   //std::cout << "Fitting x: " << std::endl;
   xVsN->Fit("pol3");
   yVsN->Fit("pol3");

   std::cout << "# of Events in the old: " << h_phi->Integral() << std::endl;
   std::cout << "# of Events in the new: " << h_phi_new->Integral() << std::endl;


   std::cout<<std::endl;
   std::cout<<"check for zombies"<<std::endl;
   if( outputFile->IsZombie() ){
     std::cout << "Error opening "<<"output file !" << std::endl;
     exit(1);
   }else{
     std::cout<<"about to write histos"<<std::endl;
     outputFile->Write();
     outputFile->Close();
   }


}
