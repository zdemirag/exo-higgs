#define dumpEvent_cxx
#include "dumpEvent.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void dumpEvent::Loop()
{

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      
      if(Pho_Pt > 45. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 30. && minMET < 80. && pvalue < 0.05 &&  MetSig > 15.&& n_jets_mva_loose < 2  && Pho_Pt< 80. && MET < 100. && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && sigmaIEtaIEta < 0.007){
       std::cout << run << ":" << lumi << ":"<< event <<std::endl;
     }
   }

}
