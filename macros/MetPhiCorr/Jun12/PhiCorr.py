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

#def makeHistos(channel,var, bin, xlow, finalcuts):
def  makeHistos(channel,var):


    List = ['DiPhotonJets', 'DiphotonBox_Pt_25to250','DiphotonBox_Pt_250toInf','WtoLNuMu','WtoLNuTau','WGamma','ZGamma_Inclusive','efake_dd','qcd_dd','GJets_HT_40To100','GJets_HT_100To200','GJets_HT_200To400','GJets_HT_400','ZGToLLG','SinglePhotonParked','MChi_120','MChi_70', 'MChi_80','MChi_90','MChi_100'] 
    
    cut_GGFTrig = " && (hltmatched==1)"

    #No MET CUT
    cut_standard = "(Pho_Pt > 45 && Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.442 && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001 && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 &&  Pho_R9<1.0)"

    pu_weight  = "MyWeightData"
    trig_phoid = "((0.5*0.892*(1+TMath::Erf( (Pho_Pt  + 36.8) / (43.8*sqrt(2))))) * (Pho_Pt  >30.) )"
    trig_met   = "((0.5*0.986*(1+TMath::Erf( (MET_old - 28.0) / (26.0*sqrt(2))))) * (MET_old>0.) )"

    weight = "1"
    #weight  =  "(" + pu_weight + "*" + trig_phoid + "*" +trig_met +")"
    Variables = {}
    efficiency ={}

    totScale = 0;

    for Type in List:

        histName = Type+var+channel
        #Variables[Type] = TH1F(histName, histName, bin,  array('d',xlow))
        Variables[Type] =  TH2D(histName, histName+";NVtx;<MEx,y>",50,0,50,200,-100,100 )
        #Variables[Type] =  TH2D(histName, histName+";p_value; MetSig",20,0,20,200,0,100 )
        Variables[Type].Sumw2()
        #Variables[Type] =  TH2D(histName, histName+";NVtx;<MEx,y>",xbin,array('d',xlow),ybin,array('d',ylow) )

        if Type.startswith("DiPhoton") or Type.startswith("DiphotonBox"):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard + ") *1*"+weight, "goff")
            totScale += lumi / Nevents[Type] * xsec[Type]
            #print Type,Variables[Type].Integral(), lumi / Nevents[Type] * xsec[Type]
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            
        if Type.startswith("WtoLNu"):
            Trees[Type].Draw(var + " >> " + histName ,  "(" + cut_standard +  ")*1*" +weight,"goff")
            totScale += lumi / Nevents[Type] * xsec[Type]
            #print Type, lumi / Nevents[Type] * xsec[Type]
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])

        if Type.startswith("WGamma"):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard  + ") *1.05*"+weight , "goff")
            totScale += lumi / Nevents[Type] * xsec[Type]
            #print Type,Variables[Type].Integral(), lumi / Nevents[Type] * xsec[Type]
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])

        if Type.startswith('ZGamma_Inclusive'):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard  + " && isZnn==1)*1.2*"+weight   , "goff")
            totScale += lumi / Nevents[Type] * xsec[Type]
            #print Type,Variables[Type].Integral(), lumi / Nevents[Type] * xsec[Type]
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])

        if Type.startswith('ZGToLLG'):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard  + ")*"+weight   , "goff")
            totScale += lumi / Nevents[Type] * xsec[Type]
            #print Type,Variables[Type].Integral(), lumi / Nevents[Type] * xsec[Type]
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            
        if Type.startswith("GJets_"):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") *1.25*"+weight   , "goff")
            totScale += lumi / Nevents[Type] * xsec[Type]
            #print Type,Variables[Type].Integral(), lumi / Nevents[Type] * xsec[Type]
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])

        if Type.startswith("MChi_90"):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") *"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])


    print totScale 
    ### Combine backgrounds with same systematics and write to the output root file ###
    Variables['DiPhotonJets'].Add(Variables['DiphotonBox_Pt_250toInf'])
    Variables['DiPhotonJets'].Add(Variables['DiphotonBox_Pt_25to250'])
    Variables['DiPhotonJets'].SetName("DiPhoton"+channel)
    Variables['DiPhotonJets'].SetTitle("DiPhoton"+channel)
    Variables['DiPhotonJets'].Write()

    Variables['WtoLNuMu'].Add(Variables['WtoLNuMu'])
    Variables['WtoLNuTau'].SetName('WtoLNu'+channel)
    Variables['WtoLNuTau'].SetTitle('WtoLNu'+channel)
    Variables['WtoLNuTau'].Write()

    Variables['WGamma'].SetName('WGamma'+channel)
    Variables['WGamma'].SetTitle('WGamma'+channel)
    Variables['WGamma'].Write()

    Variables['ZGamma_Inclusive'].SetName('ZGamma'+channel)
    Variables['ZGamma_Inclusive'].SetTitle('ZGamma'+channel)
    Variables['ZGamma_Inclusive'].Write()

    Variables['ZGToLLG'].SetName('ZGToLLG'+channel)
    Variables['ZGToLLG'].SetTitle('ZGToLLG'+channel)
    Variables['ZGToLLG'].Write()

    Variables['GJets_HT_40To100'].Add(Variables['GJets_HT_40To100'])
    Variables['GJets_HT_100To200'].Add(Variables['GJets_HT_100To200'])
    Variables['GJets_HT_200To400'].Add(Variables['GJets_HT_200To400'])
    Variables['GJets_HT_400'].Add(Variables['GJets_HT_400'])
    Variables['GJets_HT_40To100'].SetName('GJets'+channel)
    Variables['GJets_HT_40To100'].SetTitle('GJets'+channel)
    Variables['GJets_HT_40To100'].Write()

    print Variables['GJets_HT_40To100'].Integral()

    Variables['GJets_HT_40To100'].Add(Variables['ZGToLLG'])
    Variables['GJets_HT_40To100'].Add(Variables['ZGamma_Inclusive'])
    Variables['GJets_HT_40To100'].Add(Variables['WGamma'])
    Variables['GJets_HT_40To100'].Add(Variables['WtoLNuTau'])
    Variables['GJets_HT_40To100'].Add(Variables['DiPhotonJets'])
    Variables['GJets_HT_40To100'].SetName('AllBkg'+channel)
    Variables['GJets_HT_40To100'].SetTitle('AllBkg'+channel)
    Variables['GJets_HT_40To100'].Write()

    Variables['MChi_90'].SetName('Signal')
    Variables['MChi_90'].SetTitle('Signal')
    Variables['MChi_90'].Write()
    

    print Variables['GJets_HT_40To100'].Integral()

    del Variables

      
varx = 'MEx_old:NVtx'; channelx = "PhiCorrX"
vary = 'MEy_old:NVtx'; channely = "PhiCorrY"

varM = "MetSig:-log10(pvalue)"; channelM = "FakeMET"

f = TFile("PhiCorr_Histos.root","RECREATE")
f.cd('..')
f.mkdir('phiCorr')
f.cd('phiCorr') 
makeHistos(channelx,varx)
makeHistos(channely,vary)
#makeHistos(channelM,varM)
