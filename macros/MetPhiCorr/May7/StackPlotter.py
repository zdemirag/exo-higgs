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

    List = ['GJets_HT_40To100','GJets_HT_100To200','GJets_HT_200To400','GJets_HT_400']
    
    #List = ['PJets_15to30','PJets_30to50','PJets_50to80','PJets_80to120','PJets_120to170','PJets_170to300', 'PJets_300to470', 'PJets_470to800', 'PJets_800to1400', 'PJets_1400to1800','PJets_1800']
    
    cut_GGFTrig = " && (hltmatched==1)"


    cut_standard = "(Pho_Pt > 45.&&  Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.442 && MET > 40.&& pixelVeto==0 )"
    cut_standard_efake = "(Pho_Pt > 45.&&  Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.442 && MET > 40.&& pixelVeto==1 )"
    
    #Preliminary
    #cut_standard = "(Pho_Pt > 45.&&  Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.442 && MET > 40.&& pixelVeto==0  && TMath::Abs(dphi_pho_met)<1 )"
    #cut_standard_efake = "(Pho_Pt > 45.  && Pho_R9>0.9 && TMath::Abs(Pho_Eta)<1.442 && MET > 40.&& pixelVeto==1  && TMath::Abs(dphi_pho_met)<1 )"
    
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
        Variables[Type] . SetTitle(varname)
        Variables[Type] . GetXaxis() . SetTitle(varname)

        totalWeight += xsec[Type]/Nevents[Type]

        if Type.startswith("GJets_"):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") *1*"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            
            
    ### Combine backgrounds with same systematics and write to the output root file ###

    Variables['GJets_HT_40To100'].Add(Variables['GJets_HT_40To100'])
    Variables['GJets_HT_100To200'].Add(Variables['GJets_HT_100To200'])
    Variables['GJets_HT_200To400'].Add(Variables['GJets_HT_200To400'])
    Variables['GJets_HT_400'].Add(Variables['GJets_HT_400'])

    
    Variables['GJets_HT_40To100'].SetName('GJets')
    Variables['GJets_HT_40To100'].SetTitle('GJets')
    Variables['GJets_HT_40To100'].Write()


    

    del Variables

xlow = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200]

#xlow = [0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,130,132,134,136,138,140,142,144,146,148,150,152,154,156,158,160,162,164,166,168,170,172,174,176,178,180,182,184,186,188,190,192,194,196,198,200]      
#xlow = [0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200]
xlow2 = [0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,3.0,3.1,3.2,3.3,3.4,3.5]
xlow2 = [-3.4,-3.3,-3.2,-3.1,-3.0,-2.9,-2.8,-2.7,-2.6,-2.5,-2.4,-2.3,-2.2,-2.1,-2.0,-1.9,-1.8,-1.7,-1.6,-1.5,-1.4,-1.3,-1.2,-1.1,-1.0,-0.9,-0.8,-0.7,-0.6,-0.5,-0.4,-0.3,-0.2,-0.1,0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,3.0,3.1,3.2,3.3,3.4,3.5]

bin = len(xlow)-1
bin2 = len(xlow2)-1


#var = 'MT';
var3 = 'TMath::Abs(dphi_pho_met)'
varname3 = 'dphi'

var4 = 'MPhi'
varname4 ='MPhi'

#var = 'jet_pt/Pho_Pt'
#varname = 'jetptRatio'

var = 'Pho_Pt'
varname = 'PhotonPt'

#var = 'jet_pt'
#varname = 'jet_pt'

var2 = 'MET'
varname2 = 'MET'

finalcuts = False; channel = "susy"
f = TFile(channel+"_"+varname+"__Histos.root","RECREATE")
f.cd('..')
f.mkdir('susyHiggs')
f.cd('susyHiggs') 
makeHistos(channel,var, bin, xlow, finalcuts,varname)
makeHistos(channel,var2,bin, xlow,finalcuts,varname2)
makeHistos(channel,var3,bin2, xlow2,finalcuts,varname3)
makeHistos(channel,var4,bin2, xlow2,finalcuts,varname4)

