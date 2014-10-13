import ROOT, sys, os, string, re
from ROOT import *

from array import array

import math
from math import *

from tdrStyle import *
setTDRStyle()

from LoadData import *

lumi = 7369.
lumi_str = '7.3'

#7.396
def makeHistos(channel,var, bin, xlow, finalcuts,varname):
    
    List = ['PJets_15to30','PJets_30to50','PJets_50to80','PJets_80to120','PJets_120to170','PJets_170to300', 'PJets_300to470', 'PJets_470to800', 'PJets_800to1400', 'PJets_1400to1800','PJets_1800']
    
    cut_GGFTrig = " && (hltmatched==1)"

    
    #Preliminary
    cut_standard = "(Pho_Pt > 45.&&  Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.442 && MET > 40.&& pixelVeto==0  && TMath::Abs(dphi_pho_met)<1 )"
    cut_standard_efake = "(Pho_Pt > 45.  && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40.&& pixelVeto==1  && TMath::Abs(dphi_pho_met)<1 )"
    
    #cut_standard = "(Pho_Pt > 45. && Pho_Pt < 60. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89 && loose_mu==0 && foundvetoEl==0 &&  TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5) && TMath::Abs(log10(pvalue)) > 2 && pixelVeto==0"

    #cut_standard_efake = "(Pho_Pt > 45. && Pho_Pt < 60. && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40. && minMET > 40.  &&  MetSig > 15.&& n_jets_mva_loose < 2  && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001  && Pho_R9 < 1 && TMath::Abs(LICTD) < 4. && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.89  && TMath::Abs(dphi_jet_met)> 1.5 && TMath::Abs(dphi_pho_met)> 2.5)  && TMath::Abs(log10(pvalue)) > 2  && loose_mu==0 && foundvetoEl==0 && pixelVeto==1"

            
    pu_weight  = "MyWeightData"
    trig_phoid = "((0.5*0.892*(1+TMath::Erf( (Pho_Pt  + 36.8) / (43.8*sqrt(2))))) * (Pho_Pt  >30.) )"
    trig_met   = "((0.5*0.986*(1+TMath::Erf( (MET - 28.0) / (26.0*sqrt(2))))) * (MET>40.) )"
    
    #weight ="1"
    weight  =  "(" + pu_weight + "*" + trig_phoid + "*" +trig_met +")"

    Variables = {}
    
    efficiency ={}
    
    totalbkg = 0
    bkg = 0
    totalWeight = 0
    data = 0
    diphoton = 0.
    gamma_jet = 0.

    for Type in List:

        histName = Type+varname+channel
        Variables[Type] = TH1F(histName, histName, bin,  array('d',xlow))
        totalWeight += xsec[Type]/Nevents[Type]

        if Type.startswith("PJets_"):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") *1*"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            
            
    ### Combine backgrounds with same systematics and write to the output root file ###

    Variables['PJets_15to30'].Add(Variables['PJets_30to50'])
    Variables['PJets_15to30'].Add(Variables['PJets_50to80'])
    Variables['PJets_15to30'].Add(Variables['PJets_80to120'])
    Variables['PJets_15to30'].Add(Variables['PJets_120to170'])
    Variables['PJets_15to30'].Add(Variables['PJets_170to300'])
    Variables['PJets_15to30'].Add(Variables['PJets_300to470'])
    Variables['PJets_15to30'].Add(Variables['PJets_470to800'])
    Variables['PJets_15to30'].Add(Variables['PJets_800to1400'])
    Variables['PJets_15to30'].Add(Variables['PJets_1400to1800'])
    Variables['PJets_15to30'].Add(Variables['PJets_1800'])
    Variables['PJets_15to30'].SetName('PJets')
    Variables['PJets_15to30'].SetTitle('PJets')
    Variables['PJets_15to30'].Write()


    

    del Variables

      
#xlow = [0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200]
xlow = [0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,3.0,3.1,3.2,3.3,3.4,3.5]
bin = len(xlow)-1

#var = 'MT';
#var = 'TMath::Abs(dphi_pho_met)'
#varname = 'dphi'

var = 'MPhi_old'
varname = 'oldphi'

#var = 'jet_pt/Pho_Pt'
#varname = 'jetptRatio'

finalcuts = False; channel = "susy"
f = TFile(channel+"_"+varname+"__Histos.root","RECREATE")
f.cd('..')
f.mkdir('susyHiggs')
f.cd('susyHiggs') 
makeHistos(channel,var, bin, xlow, finalcuts,varname)

