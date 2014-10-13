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
    
    cut_GGFTrig = " && (hltmatched==1)"


    cut_standard ="(Pho_Pt > 45 && Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.442 && sigmaIEtaIEta > 0.001  && sqrt(sigmaIPhiIPhi) > 0.001  &&  Pho_R9<1.0  && MET>40. && loose_mu_10 == 0 && foundvetoEl_10 == 0   && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 )"#&& HT<100 && ( TMath::Abs(dphi_jet_pho) <2.5 || dphi_jet_pho == -99 ))"

    pu_weight  = "MyWeightData"
    trig_phoid = "((0.5*0.892*(1+TMath::Erf( (Pho_Pt  + 36.8) / (43.8*sqrt(2))))) * (Pho_Pt  >30.) )"
    trig_met   = "((0.5*0.986*(1+TMath::Erf( (MET - 28.0) / (26.0*sqrt(2))))) * (MET>0.) )"
    
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
            print Type, ' ' ,lumi / Nevents[Type] * xsec[Type]
            
            
    print Variables['GJets_HT_40To100'].Integral()
    print Variables['GJets_HT_100To200'].Integral()
    print Variables['GJets_HT_200To400'].Integral()
    print Variables['GJets_HT_400'].Integral()
    
    Variables['GJets_HT_40To100'].Add(Variables['GJets_HT_100To200'])
    Variables['GJets_HT_40To100'].Add(Variables['GJets_HT_200To400'])
    Variables['GJets_HT_40To100'].Add(Variables['GJets_HT_400'])
    
    Variables['GJets_HT_40To100'].SetName('GJets'+varname)
    Variables['GJets_HT_40To100'].SetTitle('GJets'+varname)
    Variables['GJets_HT_40To100'].Write()
    

    del Variables

xlow=[0,1,2,3,4,5,6,7,8,9,10]
bin = len(xlow)-1

var = 'n_jets_mva_loose'
varname = 'n_jets_mva_loose'

finalcuts = False; channel = "madgraph"
f = TFile(channel+"_Histos.root","RECREATE")
f.cd('..')
f.mkdir('susyHiggs')
f.cd('susyHiggs') 
makeHistos(channel,var, bin, xlow, finalcuts,varname)

