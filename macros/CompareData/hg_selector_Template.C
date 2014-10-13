#define hg_selector_cxx

#include "hg_selector.h"
#include <TH2.h>
#include <TStyle.h>

#include "PhysicsTools/Utilities/interface/LumiReweightingStandAlone.h"
using namespace std;

string  selection       = "nunuGamma_GGF";
string  period          = "2012";
string  suffix          = "SUFFIX";

bool    verbose         = false;
bool    mc              = false;
bool    qcd             = false;
bool    efake           = false;
bool    pjets           = false;

//float mu_pt[10];

reweight::LumiReWeighting LumiWeightsD_;
reweight::LumiReWeighting LumiWeightsD_sys_;

TF1* fjetreso = new TF1("jetReso","TMath::Sqrt(((sign([0])*(([0]/x)^2))+(([1]^2)*(x^([2]-1.))))+([3]^2))",0,15000);
TF1* fmex     = new TF1("Mex Sigma", "[0]*TMath::Sqrt(x) + [1]",0,5000);
TF1* fmey     = new TF1("Mey Sigma", "[0]*TMath::Sqrt(x) + [1]",0,5000);
TF1* fphoton  = new TF1("Photon_Sigma","[0]*pow(x,[1])",0,10000);
TF1* fmuon    = new TF1("ptsigma_barrel", "pol3", 0, 10000);

int n_vertex_count = 0;
int n_photon_count = 0;
int n_hltmatched_count = 0;
int pass_filter = 0;
int n_jet_cut = 0;
int n_pvalue = 0;

int n_total = 0;
int n_neutrino = 0;
int n_met = 0;
int n_pt = 0;
int n_eta = 0;
int n_id = 0;
int n_iso = 0;

void hg_selector::Begin(TTree *tree)
{

   TString option = GetOption();

   //PU Reweighting:

   Float_t DataDist_2012D[60] = {1768.77, 3651.68, 7356.92, 14793.3, 51246.8, 489173, 2.63921e+06, 6.82361e+06, 1.88317e+07, 5.19794e+07, 1.08899e+08, 1.88257e+08, 2.57316e+08, 3.01258e+08, 3.27492e+08, 3.44354e+08, 3.59374e+08, 3.74823e+08, 3.90058e+08, 4.0217e+08, 4.08643e+08, 4.11422e+08, 4.11151e+08, 4.05573e+08, 3.92856e+08, 3.72226e+08, 3.44284e+08, 3.10504e+08, 2.7226e+08, 2.30759e+08, 1.8777e+08, 1.45857e+08, 1.07763e+08, 7.56393e+07, 5.0551e+07, 3.23928e+07, 2.0178e+07, 1.25011e+07, 7.95461e+06, 5.38133e+06, 3.95572e+06, 3.15182e+06, 2.66553e+06, 2.33493e+06, 2.08e+06, 1.86352e+06, 1.669e+06, 1.48952e+06, 1.32229e+06, 1.16642e+06, 1.02175e+06, 888282, 766092, 655189, 555473, 466702, 388487, 320302, 261506, 211367};

   Float_t DataDist_2012D_sys[60] = {1632.3, 3240.95, 6296.46, 12068, 30517.4, 227305, 1.49497e+06, 4.52239e+06, 1.0476e+07, 2.96274e+07, 6.82538e+07, 1.28218e+08, 2.00114e+08, 2.55292e+08, 2.90327e+08, 3.11739e+08, 3.26279e+08, 3.39668e+08, 3.53444e+08, 3.67108e+08, 3.78444e+08, 3.85013e+08, 3.88036e+08, 3.88742e+08, 3.85622e+08, 3.76942e+08, 3.61739e+08, 3.39978e+08, 3.12601e+08, 2.80828e+08, 2.45645e+08, 2.08081e+08, 1.69728e+08, 1.32723e+08, 9.92184e+07, 7.08564e+07, 4.84379e+07, 3.18819e+07, 2.04316e+07, 1.29836e+07, 8.39661e+06, 5.69316e+06, 4.14131e+06, 3.24848e+06, 2.71199e+06, 2.35979e+06, 2.10068e+06, 1.88918e+06, 1.70364e+06, 1.53423e+06, 1.37666e+06, 1.22917e+06, 1.0912e+06, 962650, 843537, 733913, 633795, 543116, 461705, 389280};
  
   Float_t MCDist_Summer2012_S10[60] = {2.560E-06,5.239E-06,1.420E-05,5.005E-05,1.001E-04,2.705E-04,1.999E-03,6.097E-03,1.046E-02,1.383E-02,1.685E-02,2.055E-02,2.572E-02,3.262E-02,4.121E-02,4.977E-02,5.539E-02,5.725E-02,5.607E-02,5.312E-02,5.008E-02,4.763E-02,4.558E-02,4.363E-02,4.159E-02,3.933E-02,3.681E-02,3.406E-02,3.116E-02,2.818E-02,2.519E-02,2.226E-02,1.946E-02,1.682E-02,1.437E-02,1.215E-02,1.016E-02,8.400E-03,6.873E-03,5.564E-03,4.457E-03,3.533E-03,2.772E-03,2.154E-03,1.656E-03,1.261E-03,9.513E-04,7.107E-04,5.259E-04,3.856E-04,2.801E-04,2.017E-04,1.439E-04,1.017E-04,7.126E-05,4.948E-05,3.405E-05,2.322E-05,1.570E-05,5.005E-06};

   std::vector<float> DataDistD;
   std::vector<float> DataDistD_sys;
   std::vector<float> MCDist;
  
   for( int i=0; i<60; ++i) {
     DataDistD.push_back(DataDist_2012D[i]);
     DataDistD_sys.push_back(DataDist_2012D_sys[i]);
     MCDist.push_back(MCDist_Summer2012_S10[i]);
   }

   LumiWeightsD_ = reweight::LumiReWeighting(MCDist, DataDistD);
   LumiWeightsD_sys_ = reweight::LumiReWeighting(MCDist, DataDistD_sys);

   // Get trigger names from jobTree                                                                                                                                                
   vector<string>* triggerNames = 0;
   TFile   *inFile         = tree->GetCurrentFile();
   TTree   *jobTree        = (TTree*)inFile->Get("ntupleProducer/jobTree");

   jobTree->SetBranchAddress("triggerNames", &triggerNames);
   jobTree->GetEntry();
   triggerSelector = new TriggerSelector(selection, period, *triggerNames);

   //histoFile = new TFile("/uscms_data/d3/zdemirag/HZg_Ntuples/analyzer/CMSSW_5_3_8_patch1/src/Analyzer_v2/higgsHistograms_SUFFIX.root","RECREATE");

   histoFile = new TFile("higgsHistograms_SUFFIX.root","RECREATE");
   histoFile->cd();
  
   //Setting up new tree
   histoFile->mkdir("Analyzer", "Analyzer");
   AnDir = (TDirectory*)histoFile->GetDirectory("Analyzer");


   //OutTree2 = new TTree("Zeynep_Test","Zeynep_Test");
   //b_mu_pt = OutTree2->Branch("mu_pt",&mu_pt,"mu_pt[10]");

   tm = new TreeManager("AnalyzerTree", "H to MonoPhoton Analyzer Tree" /*, histoFile*/);

   tm->AddVar("run","int");
   tm->AddVar("lumi","int");
   tm->AddVar("event","int");

   tm->AddVar("isZnn","int");

   tm->AddVar("jet_pt","float");
   tm->AddVar("jet_size","int");
   tm->AddVar("ntrack","int");

   tm->AddVar("minDR","float");
   tm->AddVar("Pho_Pt", "float");
   tm->AddVar("Pho_Px", "float");
   tm->AddVar("Pho_Py", "float");
   tm->AddVar("Pho_Eta", "float");
   tm->AddVar("Pho_Phi","float");
   tm->AddVar("Pho_R9","float");
   tm->AddVar("Photon_tight","int");
   tm->AddVar("Photon_medium","int");
   tm->AddVar("pixelVeto","int");
   tm->AddVar("conversionVeto","int");
   tm->AddVar("HoE","float");
   tm->AddVar("numGoodPhotons","int");
   tm->AddVar("n_jets_mva_loose", "int");
   tm->AddVar("jet_eta","float");

   tm->AddVar("dphi_jet_met","float");
   tm->AddVar("dR_jet_met","float");
   tm->AddVar("dphi_jet_pho","float");
   tm->AddVar("dphi_pho_met","float");
   tm->AddVar("dR_pho_met","float");

   tm->AddVar("MET_old", "float");
   tm->AddVar("MEx_old","float");
   tm->AddVar("MEy_old","float");
   tm->AddVar("MPhi_old","float");
   tm->AddVar("MET", "float");
   tm->AddVar("MEx","float");
   tm->AddVar("MEy","float");
   tm->AddVar("MPhi","float");

   tm->AddVar("MetSig","float");
   if(mc) {
     tm->AddVar("sum_genPt","float");
     tm->AddVar("gen_pt_22","float");
     tm->AddVar("gen_eta_22","float");
     tm->AddVar("gen_status_22","float");
     tm->AddVar("gen_pt_23","float");
     tm->AddVar("gen_pt_l","float");
     tm->AddVar("gen_pt_n","float");
     tm->AddVar("gen_pdg","int");
   }   
   tm->AddVar("minMET","float");
   tm->AddVar("pvalue","float");

   tm->AddVar("MT_old","float");
   tm->AddVar("MT","float");
   tm->AddVar("MinMT","float");

   tm->AddVar("NVtx","int");

   tm->AddVar("Photon", "TLorentzVector");
   tm->AddVar("hltmatched","bool");
   tm->AddVar("hltmatched_Pho","bool");
   tm->AddVar("hltmatched_Phoid","bool");
   tm->AddVar("LICTD","float");

   tm->AddVar("foundisoel","int");
   tm->AddVar("foundlooseEl","int");

   tm->AddVar("foundvetoEl_0","int");
   tm->AddVar("foundvetoEl_5","int");
   tm->AddVar("foundvetoEl_10","int");

   tm->AddVar("foundisomu","int");
   tm->AddVar("loose_mu_0","int");
   tm->AddVar("loose_mu_5","int");
   tm->AddVar("loose_mu_10","int");

   tm->AddVar("el_pt_leading","float");
   tm->AddVar("el_phi_leading","float");
   tm->AddVar("el_eta_leading","float");
   tm->AddVar("mu_pt_leading","float");
   tm->AddVar("mu_phi_leading","float");
   tm->AddVar("mu_eta_leading","float");


   //Ecal Variables
   tm->AddVar("sigmaIEtaIEta","float");
   tm->AddVar("sigmaIEtaIPhi","float");
   tm->AddVar("sigmaIPhiIPhi","float");
   tm->AddVar("scEtaWidth","float");
   tm->AddVar("scPhiWidth","float");
   tm->AddVar("preShowerOverRaw","float");
   tm->AddVar("e1x3","float");
   tm->AddVar("e1x5","float");
   tm->AddVar("e2x2","float");
   tm->AddVar("e2x5","float");
   tm->AddVar("e2x5Max","float");
   tm->AddVar("e5x5","float");
   tm->AddVar("e2OverE5","float");
   tm->AddVar("scRawEnergy","float");
   tm->AddVar("scPSEnergy","float");
   tm->AddVar("scEnergy","float");
   tm->AddVar("roundness","float");
   tm->AddVar("angle","float");
   tm->AddVar("sMin","float");
   tm->AddVar("sMaj","float");
   tm->AddVar("seedCrystalEnergy","float");
   tm->AddVar("seedCrystalTime","float");

   if(!mc){
     tm->AddVar("hltpho","bool");
     tm->AddVar("hltphoid","bool");
     tm->AddVar("hltphoidmet","bool");
   }

   //PuVariables
   if(mc){
     tm->AddVar("npT","int");
     tm->AddVar("npIT","int");
     tm->AddVar("MyWeightData","float");
     tm->AddVar("MyWeightData_sys","float");
   }

   tm->AddVar("mu_count","int");

   tm->InitVars();


 // ch      nh       ph
  float EAPhoTemp[7][3] = {
    {0.012,  0.030,   0.148}, //         eta < 1.0  
    {0.010,  0.057,   0.130}, // 1.0   < eta < 1.479   
    {0.014,  0.039,   0.112}, // 1.479 < eta < 2.0  
    {0.012,  0.015,   0.216}, // 2.0   < eta < 2.2 
    {0.016,  0.024,   0.262}, // 2.2   < eta < 2.3  
    {0.020,  0.039,   0.260}, // 2.3   < eta < 2.4 
    {0.012,  0.072,   0.266}  // 2.4   < eta       
  };

  for (unsigned int i =0; i<7; i++){
    for (unsigned int j =0; j<3; j++){
      EAPho[i][j] = EAPhoTemp[i][j];
    }
  }


}

void hg_selector::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t hg_selector::Process(Long64_t entry)
{

  GetEntry(entry);

  if( entry % 1000 == 0 ) cout << "Processing event number: " << entry << endl;
  if(verbose) cout << "Processing event number: " << entry << endl;
  n_total++;

  TLorentzVector Photon;
  TVector3 Photon3;

  if(mc)   fmex->SetParameters(0.53,3.08);
  else fmex->SetParameters(0.61,0.37);
  
  if(mc)   fmey->SetParameters(0.53,3.4); 
  else fmey->SetParameters(0.62,0.17);
 
  fphoton->SetParameters(0.1138,-0.449);
  fmuon->SetParameters(0.006821,0.0001047,-1.213e-08,1.874e-12);


  int NumGoodPhotons = 0; 
  int found_isolatedMuon = 0;
  int found_isolatedElectron = 0;
  int found_looseMuon_0 = 0;
  int found_looseMuon_5 = 0;
  int found_looseMuon_10 = 0;

  bool fired_HLTPho = false;
  bool fired_HLTPhoId = false;
  bool fired_HLTPhoIdMet = false;  


  tm->SetValue("run",runNumber);  
  tm->SetValue("lumi",lumiSection);
  tm->SetValue("event",eventNumber);


  int has_neutrino = 0;
  //std::cout << "has_neutrino set " << has_neutrino << std::endl;
  if(mc){
    for (int g = 0; g <  genParticles->GetSize(); ++g) {
      TCGenParticle* thisgen = (TCGenParticle*) genParticles->At(g);
      if(thisgen->Mother()!=0){
	//std::cout << "thisgen->Mother()->GetPDGId(): "<<thisgen->Mother()->GetPDGId() <<std::endl;
	//std::cout << "status 1 and 3? " << thisgen->GetStatus() << std::endl;
	if( (thisgen->GetStatus() == 1 || thisgen->GetStatus() == 3) && abs(thisgen->Mother()->GetPDGId()) == 23){
	  if(abs(thisgen->GetPDGId()) == 12 || abs(thisgen->GetPDGId()) == 14 || abs(thisgen->GetPDGId()) == 16){    
	    has_neutrino = 1;
	  }
	}
      }
    }
  }

  if(has_neutrino == 1 ) n_neutrino++;  
  tm->SetValue("isZnn",has_neutrino);
  

  //std::cout << "has_neutrino? " << has_neutrino << std::endl;

  
  if(!mc){
    //Trigger Status
    for (int i = 0; i <  triggerObjects->GetSize(); ++i) {
      TCTriggerObject* thisTrigObj = (TCTriggerObject*) triggerObjects->At(i);
      if(thisTrigObj->GetHLTName().find("HLT_Photon30_v")!=std::string::npos) fired_HLTPho = true;
      if(thisTrigObj->GetHLTName().find("HLT_Photon30_R9Id90_CaloId_HE10_Iso40_EBOnly_v")!=std::string::npos) fired_HLTPhoId = true; 
      if(thisTrigObj->GetHLTName().find("HLT_Photon30_R9Id90_CaloId_HE10_Iso40_EBOnly_Met25_HBHENoiseCleaned_v")!=std::string::npos) fired_HLTPhoIdMet = true;
    }    
    
    if (NoiseFilters_isScraping) { if(verbose) cout << "NoiseFilters_isScraping: " << NoiseFilters_isScraping << endl; return kTRUE;}
    if (NoiseFilters_isNoiseHcalHBHE) {if(verbose) cout << "NoiseFilters_isNoiseHcalHBHE: " << NoiseFilters_isNoiseHcalHBHE <<endl; return kTRUE;}
    if (NoiseFilters_isNoiseHcalLaser) {if(verbose) cout << "NoiseFilters_isNoiseHcalLaser: " <<NoiseFilters_isNoiseHcalLaser <<endl; return kTRUE;}
    if (NoiseFilters_isNoiseEcalTP) {if(verbose) cout << "NoiseFilters_isNoiseEcalTP: " << NoiseFilters_isNoiseEcalTP<< endl; return kTRUE;}
    if (NoiseFilters_isNoiseEcalBE) {if(verbose) cout<< "NoiseFilters_isNoiseEcalBE: " << NoiseFilters_isNoiseEcalBE << endl; return kTRUE;}
    if (NoiseFilters_isCSCTightHalo) {if(verbose) cout<< "NoiseFilters_isCSCTightHalo: " << NoiseFilters_isCSCTightHalo <<endl; return kTRUE;}
    if (NoiseFilters_isNoiseEEBadSc) {if(verbose) cout << "NoiseFilters_isNoiseEEBadSc: " << NoiseFilters_isNoiseEEBadSc <<endl; return kTRUE;}
    if (!NoiseFilters_isNoisetrkPOG1){if(verbose) cout << "!NoiseFilters_isNoisetrkPOG1: " << !NoiseFilters_isNoisetrkPOG1 << endl; return kTRUE;}
    if (!NoiseFilters_isNoisetrkPOG2){if(verbose) cout << "!NoiseFilters_isNoisetrkPOG2: " << !NoiseFilters_isNoisetrkPOG2 << endl; return kTRUE;}
    if (!NoiseFilters_isNoisetrkPOG3) {if(verbose) cout << "!NoiseFilters_isNoisetrkPOG3: " << !NoiseFilters_isNoisetrkPOG3 << endl;return kTRUE;}
    pass_filter++;
    
  }
  if(!mc){
    tm->SetValue("hltpho",fired_HLTPho);
    tm->SetValue("hltphoid",fired_HLTPhoId);
    tm->SetValue("hltphoidmet",fired_HLTPhoIdMet);
  }

  //if( ! (fired_HLTPho || fired_HLTPhoId || fired_HLTPhoIdMet)  ) return kTRUE; 
  
  ////////////////////////////
  //Check the event vertices//  
  //////////////////////////// 
  if(verbose) cout << "Checking for good vertices..." << endl; 

  vector<TVector3> goodVertices;
  vector<TCPrimaryVtx> pvVect;
  for (int i = 0; i < primaryVtx->GetSize(); ++i) {
    TCPrimaryVtx* pVtx = (TCPrimaryVtx*) primaryVtx->At(i);
    if (!pVtx->IsFake() && pVtx->NDof() > 4. && fabs(pVtx->z()) <= 24. && fabs(pVtx->Perp()) <= 2.) {
      goodVertices.push_back(*pVtx);
      if (i == 0) { //std::cout << "NTrack: " << pVtx->Ntracks() << std::endl; 
	tm->SetValue("ntrack",pVtx->Ntracks());}
    }    
  }

  if (goodVertices.size() < 1) return kTRUE; 

  int nvtx = goodVertices.size();

  tm->SetValue("NVtx",goodVertices.size());
  pvPosition = new TVector3();
  *pvPosition = goodVertices[0];
 
  n_vertex_count++;
 

  ///////////// 
  // photons //                                                                              
  /////////////                                                                                                                                                                
  if(verbose) cout << "Checking for good photons..." << endl; 
 
  vector<TCPhoton> photonsIDIso;

  for (Int_t i = 0; i < recoPhotons->GetSize(); ++i) {
    TCPhoton* thisPhoton = (TCPhoton*) recoPhotons->At(i);
    
    if(!qcd) {
      if (!PassPhotonID(thisPhoton, mediumPhID)) continue; n_id++;
      if (!PassPhotonIso(thisPhoton, mediumPhIso)) continue; n_iso++;
    }
    if(qcd) {
      if (!PassNewQCDID(thisPhoton)) continue;
    }
    
    if (!(thisPhoton->Pt()>40.)) continue; n_pt++;
    if (!(fabs(thisPhoton->SCEta())<1.4442)) continue;  n_eta++;
    
    float newR9 = -99;
    if(mc)
      newR9 = 0.0010 + thisPhoton->R9() * 1.0045;
    else  newR9 = thisPhoton->R9();
   
    if (!(newR9>0.9)) continue;

    // Pixel Seed Veto Reversed for Efake
    if(efake){
      if ( !(thisPhoton->TrackVeto() == 1) ) continue;
    }
    if (!efake) {
      if ( !(thisPhoton->TrackVeto() == 0) ) continue;
    }
   
    
    photonsIDIso.push_back(*thisPhoton);
    NumGoodPhotons++; 
    
    if(NumGoodPhotons == 1 ) {      
      Photon = TLorentzVector(photonsIDIso[0].Px(), photonsIDIso[0].Py(), photonsIDIso[0].Pz(), photonsIDIso[0].Energy());
      Photon3 = TVector3(photonsIDIso[0].Px(), photonsIDIso[0].Py(), photonsIDIso[0].Pz());
      ( (TLorentzVector *)tm->ReturnObj("Photon") )->SetPxPyPzE( Photon.Px(), Photon.Py(), Photon.Pz(), Photon.E());
    
      vector<TCPhoton::CrystalInfo> savedCrystals = thisPhoton->GetCrystalVect();
      tm->SetValue("seedCrystalEnergy",savedCrystals[0].energy);
      tm->SetValue("seedCrystalTime",savedCrystals[0].time);
      savedCrystals.clear();
      
      float LICDT = computeLICDT(thisPhoton);
      tm->SetValue("LICTD",LICDT);

      int phIsTight = 0;
      int phIsMedium = 0;

      if(PassPhotonID(thisPhoton,tightPhID) && PassPhotonIso(thisPhoton, tightPhIso)) phIsTight = 1;
      if(PassPhotonID(thisPhoton,mediumPhID) && PassPhotonIso(thisPhoton, mediumPhIso)) phIsMedium = 1;

      tm->SetValue("Photon_tight",phIsTight);
      tm->SetValue("Photon_medium",phIsMedium);
      tm->SetValue("Pho_Pt",thisPhoton->Pt());
      tm->SetValue("Pho_Px",thisPhoton->Px());
      tm->SetValue("Pho_Py",thisPhoton->Py());
      tm->SetValue("Pho_Eta",thisPhoton->SCEta());
      tm->SetValue("Pho_Phi",thisPhoton->Phi());
      tm->SetValue("Pho_R9",newR9);
      tm->SetValue("pixelVeto",thisPhoton->TrackVeto());
      tm->SetValue("conversionVeto",thisPhoton->ConversionVeto());
      tm->SetValue("HoE",thisPhoton->HadOverEm());
      tm->SetValue("sigmaIEtaIEta",thisPhoton->SigmaIEtaIEta());
      tm->SetValue("sigmaIEtaIPhi",thisPhoton->SigmaIEtaIPhi());
      tm->SetValue("sigmaIPhiIPhi",thisPhoton->SigmaIPhiIPhi());
      tm->SetValue("scEtaWidth",thisPhoton->SCEtaWidth());
      tm->SetValue("scPhiWidth",thisPhoton->SCPhiWidth());
      tm->SetValue("preShowerOverRaw",thisPhoton->PreShowerOverRaw());
      tm->SetValue("e1x3",thisPhoton->E1x3());
      tm->SetValue("e1x5",thisPhoton->E1x5());
      tm->SetValue("e2x2",thisPhoton->E2x2());
      tm->SetValue("e2x5",thisPhoton->E2x5());
      tm->SetValue("e2x5Max",thisPhoton->E2x5Max());
      tm->SetValue("e5x5",thisPhoton->E5x5());
      tm->SetValue("e2OverE5",thisPhoton->E2OverE5());
      tm->SetValue("scRawEnergy",thisPhoton->SCRawEnergy());
      tm->SetValue("scPSEnergy",thisPhoton->SCPSEnergy());
      tm->SetValue("scEnergy",thisPhoton->SCEnergy());
      tm->SetValue("roundness",thisPhoton->Roundness());
      tm->SetValue("angle",thisPhoton->Angle());
      tm->SetValue("sMin",thisPhoton->SMin());
      tm->SetValue("sMaj",thisPhoton->SMaj());
    }
    else break;



  }
  
  if(NumGoodPhotons < 1) return kTRUE; //Skip events with no photons
  n_photon_count++;
  
  tm->SetValue("numGoodPhotons",NumGoodPhotons);


  //////////////////
  // HLT MATCHING //
  //////////////////
    
  bool hltmatched_formaintrig = false; 
  bool hltmatched_pho = false;
  bool hltmatched_phoId = false;
  
  if(!mc){
    for (int i = 0; i <  triggerObjects->GetSize(); ++i) {
      TCTriggerObject* thisTrigObj = (TCTriggerObject*) triggerObjects->At(i);
      if(thisTrigObj->GetModuleName() == "hltPhoton30HEFilter"){
	if (Photon.DeltaR(*thisTrigObj) < 0.3 && fired_HLTPho) {hltmatched_pho = true;}                                                                                       
      }
    }
    
    for (int i = 0; i <  triggerObjects->GetSize(); ++i) {                                                                                                                  
      TCTriggerObject* thisTrigObj = (TCTriggerObject*) triggerObjects->At(i);                                                                                      
      if( thisTrigObj->GetModuleName() == "hltPhoton30R9Id90CaloIdHE10Iso40EBOnlyTrackIsoLastFilter"){
	if (Photon.DeltaR(*thisTrigObj) < 0.3 && fired_HLTPhoIdMet) {hltmatched_formaintrig = true;}
	if (Photon.DeltaR(*thisTrigObj) < 0.3 && fired_HLTPhoId) {hltmatched_phoId = true;}
      }
    } 
    if(!hltmatched_formaintrig) return kTRUE;
    n_hltmatched_count++;
  } 

  tm->SetValue("hltmatched", hltmatched_formaintrig);
  tm->SetValue("hltmatched_Pho", hltmatched_pho);
  tm->SetValue("hltmatched_Phoid", hltmatched_phoId);

  ///////////////
  // MET Stuff //
  ///////////////
  
  float MEx_corr;
  float MEy_corr;


  //std::cout << "which correction are you applying? " << std::endl;
  if(!mc){
    //data
    MEx_corr = corrMET->Px() - (-0.199274+0.319277*nvtx-0.00139148*nvtx*nvtx);
    MEy_corr = corrMET->Py() - (-0.845096-0.00599484*nvtx-0.00237262*nvtx*nvtx);
    //std::cout << "this one: corrMET->Px() - (-0.199274+0.319277*nvtx-0.00139148*nvtx*nvtx)" << std::endl;
  }
  else{
    //mc
    MEx_corr = corrMET->Px() - (0.027699-0.00586364*nvtx-0.000996412*nvtx*nvtx);
    MEy_corr = corrMET->Py() - (-0.0312551-0.0901471*nvtx-0.000950153*nvtx*nvtx);
    //std::cout << "this one: corrMET->Px() - (0.027699-0.00586364*nvtx-0.000996412*nvtx*nvtx)" << std::endl;
  }

  
  float Met_corr = sqrt(MEx_corr*MEx_corr + MEy_corr*MEy_corr);
  float MET_phi_corr = TMath::ATan2(MEy_corr,MEx_corr);
  
  TLorentzVector MET_corr;
  MET_corr.SetPxPyPzE(MEx_corr,MEy_corr,0,Met_corr);
  
  tm->SetValue("dphi_pho_met", MET_corr.DeltaPhi(Photon));
  tm->SetValue("dR_pho_met", MET_corr.DeltaR(Photon));
  
  tm->SetValue("MET_old", corrMET->Mod());
  tm->SetValue("MEx_old",corrMET->Px());
  tm->SetValue("MEy_old",corrMET->Py());
  tm->SetValue("MPhi_old",corrMET->Phi());
  
  tm->SetValue("MET", Met_corr);
  tm->SetValue("MEx",MEx_corr);
  tm->SetValue("MEy",MEy_corr);
  tm->SetValue("MPhi",MET_phi_corr);
  
  tm->SetValue("MetSig",corrMET->Significance());
  tm->SetValue("MT",TransverseMass(Photon.Pt(), Photon.Px(), Photon.Py(), Met_corr, MEx_corr,MEy_corr));
  

  if(!(Met_corr > 40.)) return kTRUE; n_met++;

  float sum_genPt = 0;
  
  TLorentzVector sum_gen(0,0,0,0);
  
  if(mc){
    
    for (int g = 0; g <  genParticles->GetSize(); ++g) {
      TCGenParticle* thisgen = (TCGenParticle*) genParticles->At(g);
      
      if(thisgen->GetStatus() == 3 || thisgen->GetStatus() == 1){
	//std::cout << "gen id: " << thisgen->GetPDGId() << " pt: " << thisgen->Pt() << std::endl;

	tm->SetValue("gen_pdg",thisgen->GetPDGId());
	if(thisgen->GetPDGId() == 22) {tm->SetValue("gen_pt_22",thisgen->Pt()); tm->SetValue("gen_eta_22",thisgen->Eta()); tm->SetValue("gen_status_22",thisgen->GetStatus()); }
        if(thisgen->GetPDGId() == 23) tm->SetValue("gen_pt_23",thisgen->Pt());
        if(abs(thisgen->GetPDGId()) == 11 || abs(thisgen->GetPDGId()) == 13 || abs(thisgen->GetPDGId()) == 15) tm->SetValue("gen_pt_l",thisgen->Pt());
        //if(abs(thisgen->GetPDGId()) == 12 || abs(thisgen->GetPDGId()) == 14 || abs(thisgen->GetPDGId()) == 16) tm->SetValue("gen_pt_n",thisgen->Pt());
	if(abs(thisgen->GetPDGId()) == 1000039) tm->SetValue("gen_pt_n",thisgen->Pt());

      }

      if(abs(thisgen->GetPDGId()) == 1000039 ){
      //if(abs(thisgen->GetPDGId()) == 12 || abs(thisgen->GetPDGId()) == 14 || abs(thisgen->GetPDGId()) == 16){
	if(thisgen->GetStatus() != 3) continue;
     
	TLorentzVector* gen = (TLorentzVector*) thisgen;
	
	sum_gen += *gen;
	//cout << "thisgen->Et(): " << thisgen->Et() << " thisgen->GetPDGId(): " << thisgen->GetPDGId()  << " thisgen->GetStatus(): " << thisgen->GetStatus() <<std::endl;      
      }
      
      if(abs(thisgen->GetPDGId()) == 11 || abs(thisgen->GetPDGId()) == 13 ){
	if(thisgen->GetStatus() != 3) continue;
	if(verbose) std::cout << "Found a gen lepton: " << thisgen->GetPDGId() << " : " << thisgen->Pt() << std::endl;
      }  
    }
    
    sum_genPt = sum_gen.Pt();
    //std::cout << " sum_genPt: " << sum_genPt << std::endl;
    
    tm->SetValue("sum_genPt",sum_genPt);
  }

  if(verbose) std::cout << "starting jet veto" << std::endl;
  
  ///////////////
  // Jet Veto  //
  ///////////////
  
  int count_jets_mva_loose = 0; 
  
  float dphi_jm = -99;
  float dR_jm = -99;
  float dphi_jp = -99;
  for(int jet = 0; jet < patJets->GetSize(); jet++){
    TCJet* Jet = (TCJet*) patJets->At(jet);

    //Veto on Central Jets
    if( Jet->DeltaR(Photon) > 0.5 && Jet->Pt() > 20. && TMath::Abs(Jet->Eta())<2.4){
    //if( Jet->DeltaR(Photon) > 0.5 && TMath::Abs(Jet->Eta())<2.4){
      if(Jet->PuJetIdFlag_mva_loose()==1) {
	count_jets_mva_loose++;
	
	if(count_jets_mva_loose == 1) { 
	  //std::cout << "leading dphi_jet_met: " <<  Jet->DeltaPhi(MET_corr) << " , dR: "  << Jet->DeltaR(MET_corr) <<std::endl; }	  
	  tm->SetValue("jet_pt",Jet->Pt());
	  tm->SetValue("jet_eta",Jet->Eta());   
	  dphi_jm = Jet->DeltaPhi(MET_corr);
	  dphi_jp = Jet->DeltaPhi(Photon);
	  dR_jm = Jet->DeltaR(MET_corr);
	}
      }	
    }
  }
  tm->SetValue("n_jets_mva_loose", count_jets_mva_loose);
  
  tm->SetValue("jet_size",patJets->GetSize());
  tm->SetValue("dphi_jet_met",dphi_jm);
  tm->SetValue("dR_jet_met",dR_jm);
  tm->SetValue("dphi_jet_pho",dphi_jp);

  if(count_jets_mva_loose < 2) n_jet_cut++;

  //////////////////////
  // MHT Minimization //
  //////////////////////
  
  float STPrime = corrMET->SumEt();

  reco_pt.push_back(Photon.Pt());
  reco_phi.push_back(Photon.Phi());
  sigma_ms.push_back(fphoton->Eval(Photon.Pt())*Photon.Pt());
  STPrime -= Photon.Pt();
  
  found_isolatedElectron = 0;
  int found_vetoEl_0 = 0;
  int found_vetoEl_5 = 0;
  int found_vetoEl_10 = 0;
  int found_looseEl = 0;
  
  //const int size_jet = patJets->GetSize();
  const int size_elec = recoElectrons->GetSize();
  const int size_muon = recoMuons->GetSize();
  
  bool electronIsJet[size_elec];
  bool muonIsJet[size_muon];

  float mindR = 100;
  //Looking at electrons.
  
  vector<TCElectron> electronIDIso;

  for (int i = 0; i <  recoElectrons->GetSize(); ++i) {
    TCElectron* thisElec = (TCElectron*) recoElectrons->At(i);   
    if(verbose) std::cout << "Electron Pt: " << thisElec->Pt() << std::endl;

    if (thisElec->TrackPosition().DeltaR(Photon3) < mindR) mindR = thisElec->TrackPosition().DeltaR(Photon3);

    if (thisElec->Pt() > 10  && thisElec->DeltaR(Photon) > 0.3 && PassElectronID(thisElec, looseElID) && PassElectronIso(thisElec, looseElIso)) { found_looseEl = 1;}
    if (thisElec->DeltaR(Photon) > 0.3 && PassElectronID(thisElec,vetoElID)&& PassElectronIso(thisElec, looseElIso)) {found_vetoEl_0 =1;}    
    if (thisElec->Pt() > 5  && thisElec->DeltaR(Photon) > 0.3 && PassElectronID(thisElec,vetoElID)&& PassElectronIso(thisElec, looseElIso)) {found_vetoEl_5 =1;}    
    if (thisElec->Pt() > 10  && thisElec->DeltaR(Photon) > 0.3 && PassElectronID(thisElec,vetoElID)&& PassElectronIso(thisElec, looseElIso)) {found_vetoEl_10 =1;}    
    if (thisElec->DeltaR(Photon) > 0.3 && PassElectronID(thisElec, mediumElID) && PassElectronIso(thisElec, mediumElIso)) {
      electronIsJet[i] = 0;
      electronIDIso.push_back(*thisElec);
      found_isolatedElectron = 1; 
      
      //overlap check
      for(int jet = 0; jet < patJets->GetSize(); jet++){
	TCJet* Jet = (TCJet*) patJets->At(jet);     
	if(verbose) std::cout << "El Overlap: " << Jet->DeltaR(*thisElec) << " El Jet Pt: " << Jet->Pt() << " El Pile Up Id: "<< Jet->PuJetIdFlag_mva_loose() << std::endl;
	if(Jet->DeltaR(*thisElec) < 0.5 && Jet->Pt() > 20. && Jet->PuJetIdFlag_mva_loose()==1){
	  electronIsJet[i] = 1;
	} //overlap check
      }
      
      if (electronIsJet[i] == 0 && thisElec->Pt()>10.){ 
	reco_pt.push_back(thisElec->Pt());
	reco_phi.push_back(thisElec->Phi());
	sigma_ms.push_back(fphoton->Eval(thisElec->Pt())* thisElec->Pt());
	STPrime -= thisElec->Pt();
      }
    }
  }

  if(verbose) std::cout <<"Exiting the electron loop with "<<electronIDIso.size() <<" electrons.."<< std::endl;

  tm->SetValue("minDR",mindR);
  
  tm->SetValue("el_pt_leading", electronIDIso.size() < 1 ? -99 : electronIDIso[0].Pt());
  tm->SetValue("el_phi_leading",electronIDIso.size() < 1 ? -99 : electronIDIso[0].Phi());
  tm->SetValue("el_eta_leading",electronIDIso.size() < 1 ? -99 : electronIDIso[0].Eta());

  // Looking at muons:
  found_isolatedMuon = 0;
  found_looseMuon_0 = 0;
  found_looseMuon_5 = 0;
  found_looseMuon_10 = 0;

  vector<TCMuon> muonIDIso;
  vector<float> muon_pt;  

  tm->SetValue("mu_count",recoMuons->GetSize());

  //for(int m = 0; m<10; m++){mu_pt[m] = -1;}

  for (int i = 0; i < recoMuons->GetSize(); ++ i)  {
    
    TCMuon* thisMuon = (TCMuon*) recoMuons->At(i);    
    if(verbose) std::cout << "I see this muon in the loop: " << thisMuon->Pt() << std::endl;
    muonIsJet[i] = 0;
    
    if ( thisMuon->DeltaR(Photon) > 0.3 && thisMuon->IsPF() == 1 && (thisMuon->IsGLB() == 1  || thisMuon->IsTRK() == 1 ) && PassMuonIso(thisMuon, looseMuIso)){ found_looseMuon_0 = 1; 
    
      //mu_pt[i]= thisMuon->Pt();
}

    if (thisMuon->Pt() > 10 && thisMuon->DeltaR(Photon) > 0.3 && thisMuon->IsPF() == 1 && (thisMuon->IsGLB() == 1  || thisMuon->IsTRK() == 1 ) && PassMuonIso(thisMuon, looseMuIso)){ found_looseMuon_10 = 1; }

    if (thisMuon->Pt() > 5 && thisMuon->DeltaR(Photon) > 0.3 && thisMuon->IsPF() == 1 && (thisMuon->IsGLB() == 1  || thisMuon->IsTRK() == 1 ) && PassMuonIso(thisMuon, looseMuIso)){ found_looseMuon_5 = 1; }
    
    if (thisMuon->DeltaR(Photon) > 0.3 && PassMuonID(thisMuon, tightMuID) && PassMuonIso(thisMuon, tightMuIso)){  
      found_isolatedMuon = 1;
      muonIDIso.push_back(*thisMuon);

      if(verbose) std::cout << "Muon Passed the tight id" << std::endl;
      
      //overlap check
      for(int jet = 0; jet < patJets->GetSize(); jet++){
	TCJet* Jet = (TCJet*) patJets->At(jet);     
	
	if(verbose) std::cout << "Mu Overlap: " << Jet->DeltaR(*thisMuon) << " Mu Jet Pt: " << Jet->Pt() << " Mu Pile Up Id: "<< Jet->PuJetIdFlag_mva_loose() << std::endl;
	
	if(Jet->DeltaR(*thisMuon) < 0.5 && Jet->Pt() > 20. && Jet->PuJetIdFlag_mva_loose()==1) muonIsJet[i] = 1; 
      } //overlap check
       
      if(verbose) std::cout << "Muon is a Jet Check: " << muonIsJet[i] << std::endl;
      
      if(muonIsJet[i] == 0 && thisMuon->Pt() > 10.){
	reco_pt.push_back(thisMuon->Pt());
	reco_phi.push_back(thisMuon->Phi());
	sigma_ms.push_back(fmuon->Eval(thisMuon->Pt())* thisMuon->Pt());
	STPrime -= thisMuon->Pt();  
      }
    }
  }

  tm->SetValue("mu_pt_leading", muonIDIso.size() < 1 ? -99 : muonIDIso[0].Pt());
  tm->SetValue("mu_phi_leading",muonIDIso.size() < 1 ? -99 : muonIDIso[0].Phi());
  tm->SetValue("mu_eta_leading",muonIDIso.size() < 1 ? -99 : muonIDIso[0].Eta());

  for(int jet = 0; jet < patJets->GetSize(); jet++){
    TCJet* Jet = (TCJet*) patJets->At(jet);     
    if( Jet->DeltaR(Photon) > 0.5 && Jet->Pt() > 20. && Jet->PuJetIdFlag_mva_loose()==1){
      reco_pt.push_back(Jet->Pt());
      reco_phi.push_back(Jet->Phi());
      sigma_ms.push_back(jetreso(fjetreso,Jet->Pt(), Jet->Eta()));
      STPrime -= Jet->Pt(); 
    }
  }
  
  sigma_mex = fmex->Eval(TMath::Abs(STPrime));
  sigma_mey = fmey->Eval(TMath::Abs(STPrime));
  
  Ndim = reco_pt.size();
  
  ROOT::Math::Minimizer* min =  ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");
  min->SetMaxFunctionCalls(1000000);
  min->SetMaxIterations(10000);
  min->SetTolerance(0.0001);
  
  ROOT::Math::Functor f(this,&hg_selector::func, Ndim); 
  min->SetFunction(f);
  
  for (int i=0; i<Ndim; i++){
    TString name = "pt";
    name += i;
    double lower = TMath::Max(0.,reco_pt[i] - 5*sigma_ms[i]);
    double upper = reco_pt[i] + (5*sigma_ms[i]);
    min->SetLimitedVariable(i,name.Data(),reco_pt[i],0.1,lower,upper);
  }   
  
  min->Minimize();         
  const double *xs = min->X(); 
  min->Clear();
  
  float p_value = TMath::Prob(func(xs),2);
  
  // Finding Parametrized MET:
  double ParPx = 0; double ParPy = 0;  double RecoPx= 0;  double RecoPy = 0.;
  
  for(int j=0; j<Ndim; j++){

    if(verbose) std::cout << "N: " << j << " reco_pt: " << reco_pt[j] << " min pt: "<< xs[j] << " reso: "  << sigma_ms[j] <<std::endl;

    ParPx += xs[j]*cos(reco_phi[j]);
    ParPy += xs[j]*sin(reco_phi[j]);
    RecoPx += reco_pt[j]*cos(reco_phi[j]);
    RecoPy += reco_pt[j]*sin(reco_phi[j]);
  }
  
  float MinMET = sqrt((ParPx*ParPx)+(ParPy*ParPy));
  float RecoMET = sqrt(RecoPx*RecoPx+RecoPy*RecoPy);

  tm->SetValue("MinMT",TransverseMass(Photon.Pt(), Photon.Px(), Photon.Py(), MinMET, -ParPx, -ParPy));

  if (mc) {if(verbose){std::cout << "PF MET: " << corrMET->Mod() << " Minimized MET: " << MinMET << " Reco MET: " << RecoMET << " sum_genPt: " <<sum_genPt << std::endl;}}
  else {if(verbose){std::cout << "PF MET: " << corrMET->Mod() << " Minimized MET: " << MinMET << " Reco MET: " << RecoMET << std::endl;}}

  delete min;
  reco_pt.clear();
  reco_phi.clear();
  sigma_ms.clear();

  tm->SetValue("foundisomu",found_isolatedMuon);
  tm->SetValue("loose_mu_0",found_looseMuon_0);
  tm->SetValue("loose_mu_5",found_looseMuon_5);
  tm->SetValue("loose_mu_10",found_looseMuon_10);

  tm->SetValue("foundisoel",found_isolatedElectron);
  tm->SetValue("foundlooseEl",found_looseEl);

  tm->SetValue("foundvetoEl_0",found_vetoEl_0);
  tm->SetValue("foundvetoEl_5",found_vetoEl_5);
  tm->SetValue("foundvetoEl_10",found_vetoEl_10);

  tm->SetValue("minMET",MinMET);
  tm->SetValue("pvalue",p_value);

  if( TMath::Abs(log10(p_value)) >2  ) n_pvalue++;


  if(mc){
    tm->SetValue("npT",nPUVerticesTrue);
    tm->SetValue("npIT",nPUVertices);
    tm->SetValue("MyWeightData",LumiWeightsD_.weight(nPUVerticesTrue));
    tm->SetValue("MyWeightData_sys",LumiWeightsD_sys_.weight(nPUVerticesTrue));
  }


  tm->TreeFill();
  //OutTree2->Fill();

  return kTRUE;
}

void hg_selector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void hg_selector::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

//  histoFile->cd();
//  AnDir->cd();

  std::cout << "n_total: " << n_total << std::endl;
  std::cout << "n_neutrino: " << n_neutrino << std::endl;
  std::cout << "n_id: "<< n_id << std::endl;
  std::cout << "n_iso: "<< n_iso << std::endl;
  std::cout << "n_pt: "<< n_pt << std::endl;
  std::cout << "n_eta: "<< n_eta << std::endl;
  std::cout << "n_photon: " << n_photon_count<< std::endl;
  std::cout << "n_met: " << n_met << std::endl;
  std::cout << "n_jet_cut: " << n_jet_cut << std::endl;
  std::cout << "n_pvalue: " << n_pvalue << std::endl;

  histoFile->cd();
  AnDir->cd();
  tm->TreeWrite();
  //  OutTree2->Write();
//  histoFile->cd();
//  histoFile->Close();
}


bool hg_selector::PassQCDID(TCPhoton *ph){

  //Iso:
  float chEA,nhEA,phEA,chIsoCor,nhIsoCor,phIsoCor,tmpEta;
  
  tmpEta = ph->SCEta();

  if (fabs(tmpEta) < 1.0){
    chEA = EAPho[0][0];
    nhEA = EAPho[0][1];
    phEA = EAPho[0][2];
  }else if (fabs(tmpEta) < 1.479){
    chEA = EAPho[1][0];
    nhEA = EAPho[1][1];
    phEA = EAPho[1][2];
  }else if (fabs(tmpEta) < 2.0){
    chEA = EAPho[2][0];
    nhEA = EAPho[2][1];
    phEA = EAPho[2][2];
  }else if (fabs(tmpEta) < 2.2){
    chEA = EAPho[3][0];
    nhEA = EAPho[3][1];
    phEA = EAPho[3][2];
  }else if (fabs(tmpEta) < 2.3){
    chEA = EAPho[4][0];
    nhEA = EAPho[4][1];
    phEA = EAPho[4][2];
  }else if (fabs(tmpEta) < 2.4){
    chEA = EAPho[5][0];
    nhEA = EAPho[5][1];
    phEA = EAPho[5][2];
  }else{
    chEA = EAPho[6][0];
    nhEA = EAPho[6][1];
    phEA = EAPho[6][2];
  }

  chIsoCor = ph->IsoMap("chIso03")-rhoFactor*chEA;
  nhIsoCor = ph->IsoMap("nhIso03")-rhoFactor*nhEA;
  phIsoCor = ph->IsoMap("phIso03")-rhoFactor*phEA;

  //Id

  bool denoID=false;
              
  bool upperBound=false;
  bool lowerBound =false;

  double  maxPFCharged= TMath::Min(5.0*(2.6) , 0.20*ph->Pt());
  double  maxPFPhoton = TMath::Min(5.0*(1.3+0.005*ph->Pt()) , 0.20*ph->Pt());
  double  maxPFNeutral= TMath::Min(5.0*(3.5+0.04*ph->Pt()) , 0.20*ph->Pt());


  upperBound= (max((double)chIsoCor,0.) < maxPFCharged
	       && max((double)nhIsoCor,0.) < maxPFNeutral
	       && max((double)phIsoCor,0.) < maxPFPhoton
	       && ph->HadOverEm() < 0.05
	       && ph->SigmaIEtaIEta() < 0.015
	       && ph->ConversionVeto() == 1);
  lowerBound= (max((double)chIsoCor,0.) > 2.6
	       || max((double)nhIsoCor,0.) > 3.5+0.04 *ph->Pt()
	       || max((double)phIsoCor,0.) > 1.3+0.005*ph->Pt());
  
  if( (upperBound) && (lowerBound) )denoID = true;

  return denoID; 

}


bool hg_selector::PassNewQCDID(TCPhoton *ph){

  //Iso:                                                                                                                                                                        
  float chEA,nhEA,phEA,chIsoCor,nhIsoCor,phIsoCor,tmpEta;
  tmpEta = ph->SCEta();
  if (fabs(tmpEta) < 1.0){
    chEA = EAPho[0][0];
    nhEA = EAPho[0][1];
    phEA = EAPho[0][2];
  }else if (fabs(tmpEta) < 1.479){
    chEA = EAPho[1][0];
    nhEA = EAPho[1][1];
    phEA = EAPho[1][2];
  }else if (fabs(tmpEta) < 2.0){
    chEA = EAPho[2][0];
    nhEA = EAPho[2][1];
    phEA = EAPho[2][2];
  }else if (fabs(tmpEta) < 2.2){
    chEA = EAPho[3][0];
    nhEA = EAPho[3][1];
    phEA = EAPho[3][2];
  }else if (fabs(tmpEta) < 2.3){
    chEA = EAPho[4][0];
    nhEA = EAPho[4][1];
    phEA = EAPho[4][2];
  }else if (fabs(tmpEta) < 2.4){
    chEA = EAPho[5][0];
    nhEA = EAPho[5][1];
    phEA = EAPho[5][2];
  }else{
    chEA = EAPho[6][0];
    nhEA = EAPho[6][1];
    phEA = EAPho[6][2];
  }

  chIsoCor = ph->IsoMap("chIso03")-rhoFactor*chEA;
  nhIsoCor = ph->IsoMap("nhIso03")-rhoFactor*nhEA;
  phIsoCor = ph->IsoMap("phIso03")-rhoFactor*phEA;

  //Id                                   
   
  bool denoID_new =false;
  bool upperBound =false;
  bool lowerBound =false;

  double  maxPFCharged= TMath::Min(5.*4.0, 0.2*ph->Pt());
  double  maxPFPhoton = TMath::Min(5.*(4.5 + 0.005*ph->Pt()), 0.2*ph->Pt());
  double  maxPFNeutral= TMath::Min(5.*(4.5 + 0.04*ph->Pt()), 0.2*ph->Pt());
  
  upperBound= (max((double)chIsoCor,0.) < maxPFCharged
               && max((double)nhIsoCor,0.) < maxPFNeutral
               && max((double)phIsoCor,0.) < maxPFPhoton
               && ph->HadOverEm() < 0.05             
	       && ph->SigmaIEtaIEta() > 0.001
	       && sqrt(ph->SigmaIPhiIPhi()) > 0.001
	       );

  lowerBound= (max((double)chIsoCor,0.) > 4.0
               || max((double)nhIsoCor,0.) > 4.5+0.04 *ph->Pt()
               || max((double)phIsoCor,0.) > 4.5+0.005*ph->Pt()
	       || ph->SigmaIEtaIEta() > 0.012);

  if( (upperBound) && (lowerBound) )denoID_new = true;
  
  return denoID_new;
}


bool hg_selector::PassPhotonID(TCPhoton *ph, phIDCuts cutLevel){
  float tmpEta;
  bool phoPass = false;
  tmpEta = ph->SCEta();
  if (fabs(tmpEta) > 2.5) return phoPass;
  if (fabs(tmpEta) > 1.4442 && fabs(tmpEta) < 1.566) return phoPass;
  if(
     (fabs(tmpEta)  < 1.4442
      //&& ph->ConversionVeto()       == 0
      //&& ph->TrackVeto() == 1
      //&& ph->ConversionVeto()       == cutLevel.PassedEleSafeVeto[0]
      && ph->HadOverEm()               < cutLevel.HadOverEm[0]
      && ph->SigmaIEtaIEta()           < cutLevel.sigmaIetaIeta[0]
      ) ||
     (fabs(tmpEta)  > 1.566
      //&& ph->ConversionVeto()       == 0
      //&& ph->TrackVeto() == 1
      //&& ph->ConversionVeto()       == cutLevel.PassedEleSafeVeto[1]
      && ph->HadOverEm()               < cutLevel.HadOverEm[1]
      && ph->SigmaIEtaIEta()           < cutLevel.sigmaIetaIeta[1]
      )
     ) phoPass = true;
  return phoPass;
}


bool hg_selector::PassPhotonIso(TCPhoton *ph, phIsoCuts cutLevel){
  float chEA,nhEA,phEA,chIsoCor,nhIsoCor,phIsoCor,tmpEta;
  bool isoPass = false;
  tmpEta = ph->SCEta();

  if(fabs(tmpEta) > 2.5) return isoPass;

  if (fabs(tmpEta) < 1.0){
    chEA = EAPho[0][0];
    nhEA = EAPho[0][1];
    phEA = EAPho[0][2];
  }else if (fabs(tmpEta) < 1.479){
    chEA = EAPho[1][0];
    nhEA = EAPho[1][1];
    phEA = EAPho[1][2];
  }else if (fabs(tmpEta) < 2.0){
    chEA = EAPho[2][0];
    nhEA = EAPho[2][1];
    phEA = EAPho[2][2];
  }else if (fabs(tmpEta) < 2.2){
    chEA = EAPho[3][0];
    nhEA = EAPho[3][1];
    phEA = EAPho[3][2];
  }else if (fabs(tmpEta) < 2.3){
    chEA = EAPho[4][0];
    nhEA = EAPho[4][1];
    phEA = EAPho[4][2];
  }else if (fabs(tmpEta) < 2.4){
    chEA = EAPho[5][0];
    nhEA = EAPho[5][1];
    phEA = EAPho[5][2];
  }else{
    chEA = EAPho[6][0];
    nhEA = EAPho[6][1];
    phEA = EAPho[6][2];
  }

  chIsoCor = ph->IsoMap("chIso03")-rhoFactor*chEA;
  nhIsoCor = ph->IsoMap("nhIso03")-rhoFactor*nhEA;
  phIsoCor = ph->IsoMap("phIso03")-rhoFactor*phEA;

  if (cutLevel.cutName == "loosePhIso"){
    if (
        (fabs(tmpEta) < 1.4442
	 //(fabs(ph->Eta())  < 1.566                                                                                                                                                
         && max((double)chIsoCor,0.)          < cutLevel.chIso03[0]
         && max((double)nhIsoCor,0.)          < cutLevel.nhIso03[0] + 0.04*ph->Pt()
         && max((double)phIsoCor,0.)          < cutLevel.phIso03[0] + 0.005*ph->Pt()
	 ) ||
	(fabs(tmpEta) > 1.566
	 //(fabs(ph->Eta())  > 1.566                                                                                                                                                
         && max((double)chIsoCor,0.)          < cutLevel.chIso03[1]
         && max((double)nhIsoCor,0.)          < cutLevel.nhIso03[1] + 0.04*ph->Pt()
         //&& phoCut["phIso03"]/ph->Pt() < nuthin                                                                                                                                  
	 )
	) isoPass = true;
  } else {
    if (
	//(fabs(ph->Eta())  < 1.566                                                                                                                                                
        (fabs(tmpEta) < 1.4442
         && max((double)chIsoCor,0.)          < cutLevel.chIso03[0]
         && max((double)nhIsoCor,0.)          < cutLevel.nhIso03[0] + 0.04*ph->Pt()
         && max((double)phIsoCor,0.)          < cutLevel.phIso03[0] + 0.005*ph->Pt()
	 ) ||
        //(fabs(ph->Eta())  > 1.566                                                                                                                                                
        (fabs(tmpEta) > 1.566
         && max((double)chIsoCor,0.)          < cutLevel.chIso03[1]
         && max((double)nhIsoCor,0.)          < cutLevel.nhIso03[1] + 0.04*ph->Pt()
         && max((double)phIsoCor,0.)          < cutLevel.phIso03[1] + 0.005*ph->Pt()
	 )
	) isoPass = true;
  }
  return isoPass;
}

bool hg_selector::PassElectronIso(TCElectron *el, elIsoCuts cutLevel){
  float thisEA = 0;
  if (fabs(el->Eta())     <  1.0) thisEA = EAEle[0];
  else if (fabs(el->Eta())     <  1.5) thisEA = EAEle[1];
  else if (fabs(el->Eta())     <  2.0) thisEA = EAEle[2];
  else if (fabs(el->Eta())     <  2.2) thisEA = EAEle[3];
  else if (fabs(el->Eta())     <  2.3) thisEA = EAEle[4];
  else if (fabs(el->Eta())     <  2.4) thisEA = EAEle[5];
  else if (fabs(el->Eta())     >  2.4) thisEA = EAEle[6];

  float combIso = (el->IsoMap("pfChIso_R04")
    + max(0.,(double)el->IsoMap("pfNeuIso_R04") + el->IsoMap("pfPhoIso_R04") - rhoFactor*thisEA));
  bool isoPass = false;
  if (combIso/el->Pt() < cutLevel.relCombIso04) isoPass = true;
  return isoPass;
}


bool hg_selector::PassMuonID(TCMuon *mu, muIDCuts cutLevel){

  bool muPass = false;
  if (
    fabs(mu->Eta()) < 2.4
      && mu->IsPF()                          == cutLevel.IsPF
      && mu->IsGLB()                         == cutLevel.IsGLB
      && mu->NormalizedChi2()                < cutLevel.NormalizedChi2
      && mu->NumberOfValidMuonHits()         > cutLevel.NumberOfValidMuonHits
      && mu->NumberOfMatchedStations()       > cutLevel.NumberOfMatchedStations
      && mu->NumberOfValidPixelHits()        > cutLevel.NumberOfValidPixelHits
      && mu->TrackLayersWithMeasurement()    > cutLevel.TrackLayersWithMeasurement
      && fabs(mu->Dxy(pvPosition))           < cutLevel.dxy
      && fabs(mu->Dz(pvPosition))            < cutLevel.dz
    ) muPass = true;
  return muPass;

}

bool hg_selector::PassMuonIso(TCMuon *mu, muIsoCuts cutLevel){

  float combIso;

  combIso = (mu->IsoMap("pfChargedHadronPt_R04")
    + max(0.,(double)mu->IsoMap("pfNeutralHadronEt_R04") + mu->IsoMap("pfPhotonEt_R04") - 0.5*mu->IsoMap("pfPUPt_R04")));

  bool isoPass = false;
  if (combIso/mu->Pt() < cutLevel.relCombIso04) isoPass = true;
  //std::cout << "muon iso: "<< combIso/mu->Pt() << " decision: "  << isoPass << std::endl;
  return isoPass;
}



bool hg_selector::PassElectronID(TCElectron *el, elIDCuts cutLevel)
{
  bool elPass = false;
  if (fabs(el->SCEta()) > 2.5) return elPass;
  if (fabs(el->SCEta()) > 1.4442 && fabs(el->SCEta()) < 1.566) return elPass;
  if (
      (fabs(el->Eta()) < 1.566
       && fabs(el->SCDeltaEta())    < cutLevel.dEtaIn[0]
       && fabs(el->SCDeltaPhi())    < cutLevel.dPhiIn[0]
       && el->SigmaIEtaIEta()             < cutLevel.sigmaIetaIeta[0]
       && el->HadOverEm()                 < cutLevel.HadOverEm[0]
       && fabs(el->Dxy(pvPosition))       < cutLevel.dxy[0]
       && fabs(el->Dz(pvPosition))        < cutLevel.dz[0]
       && el->IdMap("fabsEPDiff")         < cutLevel.fabsEPDiff[0]
       && el->ConversionMissHits()        <= cutLevel.ConversionMissHits[0]
       && el->PassConversionVeto()        == cutLevel.PassedConversionProb[0]
       ) ||
    (fabs(el->Eta()) > 1.566  
      && fabs(el->SCDeltaEta())    < cutLevel.dEtaIn[1]
      && fabs(el->SCDeltaPhi())    < cutLevel.dPhiIn[1]
      && el->SigmaIEtaIEta()             < cutLevel.sigmaIetaIeta[1]
      && el->HadOverEm()                 < cutLevel.HadOverEm[1]
      && fabs(el->Dxy(pvPosition))       < cutLevel.dxy[1]
      && fabs(el->Dz(pvPosition))        < cutLevel.dz[1]
      && el->IdMap("fabsEPDiff")         < cutLevel.fabsEPDiff[1]
      && el->ConversionMissHits()        <= cutLevel.ConversionMissHits[1]
     && el->PassConversionVeto()         == cutLevel.PassedConversionProb[1]
      )
    ) elPass = true; 
  for (int j = 0; j < recoMuons->GetSize(); ++ j)
       {
         TCMuon* thisMuon = (TCMuon*) recoMuons->At(j);    
         if (thisMuon->DeltaR(*el) < 0.05){
           elPass = false;
           break;
         }
       }
       return elPass;
}


double  hg_selector::func(const double* par){
  Ndim = reco_pt.size();
  double px = 0, py =0, arg = 0;  
  for(int i=0; i<Ndim; i++){
    px += par[i]*cos(reco_phi[i]);
    py += par[i]*sin(reco_phi[i]);
    arg += pow((reco_pt[i]-par[i])/(sigma_ms[i]),2);
  }
  return arg + ((px*px)/(sigma_mex*sigma_mex) + (py*py)/(sigma_mey*sigma_mey));
}

double  hg_selector::jetreso(TF1 *fjetreso_T, double pt, double eta_or){
  double reso = 0;
  //TF1 *fjetreso = new TF1 ("jetReso","TMath::Sqrt(((sign([0])*(([0]/x)^2))+(([1]^2)*(x^([2]-1.))))+([3]^2))",0,15000);
  double scale = 0;

  double eta = TMath::Abs(eta_or);

  if (eta <= 0.3)              {fjetreso_T->SetParameters(2.866,0.3118,0.4075,0.01823); scale = 1.052;}
  if (eta > 0.3 && eta <= 0.5) {fjetreso_T->SetParameters(2.91,0.2793,0.4629,0.001049); scale = 1.052;}
  if (eta > 0.5 && eta <= 0.8) {fjetreso_T->SetParameters(2.768,0.3797,0.3144,0.02803); scale = 1.057;}
  if (eta > 0.8 && eta <= 1.1) {fjetreso_T->SetParameters(2.934,0.3251,0.4401,0.0079); scale = 1.057;}
  if (eta > 1.1 && eta <= 1.4) {fjetreso_T->SetParameters(2.617,0.736,0.0899,-0.04179); scale = 1.096;}
  if (eta > 1.4 && eta <= 1.7) {fjetreso_T->SetParameters(0.1406,1.477,-0.2062,-0.03656); scale = 1.096;}
  if (eta > 1.7 && eta <= 2.0) {fjetreso_T->SetParameters(1.959,1.099,-0.1357,-0.02382); scale = 1.134;}
  if (eta > 2.0 && eta <= 2.3) {fjetreso_T->SetParameters(4.113,0.4146,0.1918,0.02413); scale = 1.134;}
  if (eta > 2.3 && eta <= 2.8) {fjetreso_T->SetParameters(5.817,0.1547,0.5529,0.001136); scale = 1.288;}
  if (eta > 2.8 && eta <= 3.2) {fjetreso_T->SetParameters(4.894,0.3666,0.4251,-0.00215); scale = 1.288;}
  if (eta > 3.2 && eta <= 4.1) {fjetreso_T->SetParameters(3.624,0.2542,0.6046,0.02232); scale = 1.288;}
  if (eta > 4.1)               {fjetreso_T->SetParameters(2.727,1.035,-0.1662,0); scale = 1.288;}


  if(mc)   reso = pt * fjetreso_T->Eval(pt);
  else reso = pt * scale * fjetreso_T->Eval(pt);
  return reso;

}


float hg_selector::computeLICDT(TCPhoton *ph){
  
  vector<TCPhoton::CrystalInfo> savedCrystals = ph->GetCrystalVect();

  int seed = -1;
  float seedE = -999999, LICTD = 0;
  
  for(int k=0;k<ph->GetNCrystals() && k < 100; ++k){
    if(savedCrystals[k].energy > seedE){seed = k; seedE = savedCrystals[seed].energy;}
    if(seed<0) LICTD = -99;
    if(seed==k) continue;
    if (savedCrystals[k].energy > 1.) {
      if(TMath::Abs(savedCrystals[seed].time - savedCrystals[k].time) > TMath::Abs(LICTD)) LICTD = savedCrystals[seed].time - savedCrystals[k].time;
    }
  }
  return LICTD;
  savedCrystals.clear();
}
