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

    cut_standard ="(Pho_Pt > 45 && Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.442 && sigmaIEtaIEta > 0.001  && sqrt(sigmaIPhiIPhi) > 0.001  &&  Pho_R9<1.0  && MET>40. && loose_mu_10 == 0 && foundvetoEl_10 == 0   && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 )"

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

xlow = [0,1,2,3,4,5,6,7,8,9,10]
bin = len(xlow)-1

var = 'n_jets_mva_loose'
varname = 'n_jets_mva_loose'

finalcuts = False; channel = "pythia"
f = TFile(channel+"_Histos.root","RECREATE")
f.cd('..')
f.mkdir('susyHiggs')
f.cd('susyHiggs') 
makeHistos(channel,var, bin, xlow, finalcuts,varname)

