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


    List = ['efake_dd','qcd_dd','SinglePhotonParked']
    
    cut_GGFTrig = " && (hltmatched==1)"

    #No MET CUT
    cut_standard = "(Pho_Pt > 45 && Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.442 && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001 && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 &&  Pho_R9<1.0 )"
  
    weight = "1"
    Variables = {}
    efficiency ={}

    totScale = 0;

    for Type in List:

        histName = Type+var+channel
        Variables[Type] =  TH2D(histName, histName+";NVtx;<MEx,y>",50,0,50,200,-100,100 )
        Variables[Type].Sumw2()

        if Type.startswith("qcd"):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard  + ")* (1.54 + 1114/pow(Pho_Pt,1.799))  "   , "goff")

        if Type.startswith("efake_dd"):
            Trees[Type].Draw(var + " >> " + histName ,  "(" + cut_standard  + ") * (0.0252) ","goff")

        if Type.startswith("SinglePhotonParked"):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  cut_GGFTrig +")"  , "goff")

       
    print totScale 
    ### Combine backgrounds with same systematics and write to the output root file ###

    Variables['qcd_dd'].SetName("qcd"+channel)
    Variables['qcd_dd'].SetTitle("qcd"+channel)
    Variables['qcd_dd'].Write()

    Variables['efake_dd'].SetName('efake'+channel)
    Variables['efake_dd'].SetTitle('efake'+channel)
    Variables['efake_dd'].Write()

    Variables['SinglePhotonParked'].SetName('data'+channel)
    Variables['SinglePhotonParked'].SetTitle('data'+channel)
    Variables['SinglePhotonParked'].Write()

    print Variables['SinglePhotonParked'].Integral()

    Variables['SinglePhotonParked'].Add(Variables['qcd_dd'])
    Variables['SinglePhotonParked'].Add(Variables['efake_dd'])
    Variables['SinglePhotonParked'].SetName('AllBkg'+channel)
    Variables['SinglePhotonParked'].SetTitle('AllBkg'+channel)
    Variables['SinglePhotonParked'].Write()

    

    del Variables

      
varx = 'MEx_old:NVtx'; channelx = "PhiCorrX"
vary = 'MEy_old:NVtx'; channely = "PhiCorrY"
f = TFile("PhiCorr_Histos_Data.root","RECREATE")
f.cd('..')
f.mkdir('phiCorr')
f.cd('phiCorr') 
makeHistos(channelx,varx)
makeHistos(channely,vary)
