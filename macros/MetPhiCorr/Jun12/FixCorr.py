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

def makeHistos(channel,var, bin, xlow,varname,testcut):


    MEx_corr = 'MEx_old - (0.231012 - 0.0368553*NVtx)'
    MEy_corr = 'MEy_old - (0.164057 - 0.119796*NVtx)'

    Met_corr = 'sqrt(('+MEx_corr+')**2+('+MEy_corr+')**2)'


    List = ['DiPhotonJets', 'DiphotonBox_Pt_25to250','DiphotonBox_Pt_250toInf','WtoLNuMu','WtoLNuTau','WGamma','ZGamma_Inclusive','efake_dd','qcd_dd','GJets_HT_40To100','GJets_HT_100To200','GJets_HT_200To400','GJets_HT_400','ZGToLLG','SinglePhotonParked','MChi_120','MChi_70', 'MChi_80','MChi_90','MChi_100'] 
    
    cut_GGFTrig = " && (hltmatched==1)"

    #NoMETCut
    cut_standard = "(Pho_Pt > 45 && Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.442 && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001 && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 &&  Pho_R9<1.0 &&" +testcut+ ") "

    pu_weight  = "MyWeightData"
    trig_phoid = "((0.5*0.892*(1+TMath::Erf( (Pho_Pt  + 36.8) / (43.8*sqrt(2))))) * (Pho_Pt  >30.) )"
    trig_met   = "((0.5*0.986*(1+TMath::Erf( (MET - 28.0) / (26.0*sqrt(2))))) * (MET>0.) )"
    
    weight  =  "(" + pu_weight + "*" + trig_phoid + "*" +trig_met +")"
    Variables = {}
    efficiency ={}

    print Met_corr, " " , testcut

    for Type in List:

        histName = Type+varname+channel
        #Variables[Type].Sumw2()
        Variables[Type] = TH1F(histName, histName, bin,  array('d',xlow))

        if Type.startswith("DiPhoton") or Type.startswith("DiphotonBox"):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard + ") *1*"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            
        if Type.startswith("WtoLNu"):
            Trees[Type].Draw(var + " >> " + histName ,  "(" + cut_standard +  ")*" +weight,"goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])

        if Type.startswith("WGamma"):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard  + ") *1.05*"+weight , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])

        if Type.startswith('ZGamma_Inclusive'):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard  + " && isZnn==1)*1.2*"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])

        if Type.startswith('ZGToLLG'):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard  + ")*"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            
        if Type.startswith("GJets_"):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") *1.25*"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])

     
    ### Combine backgrounds with same systematics and write to the output root file ###
    Variables['DiPhotonJets'].Add(Variables['DiphotonBox_Pt_250toInf'])
    Variables['DiPhotonJets'].Add(Variables['DiphotonBox_Pt_25to250'])
    Variables['DiPhotonJets'].SetName("DiPhoton")
    Variables['DiPhotonJets'].SetTitle("DiPhoton")
    #Variables['DiPhotonJets'].Write()

    Variables['WtoLNuTau'].Add(Variables['WtoLNuMu'])
    Variables['WtoLNuTau'].SetName('WtoLNu')
    Variables['WtoLNuTau'].SetTitle('WtoLNu')
    #Variables['WtoLNuTau'].Write()

    Variables['WGamma'].SetName('WGamma')
    Variables['WGamma'].SetTitle('WGamma')
    #Variables['WGamma'].Write()

    Variables['ZGamma_Inclusive'].SetName('ZGamma')
    Variables['ZGamma_Inclusive'].SetTitle('ZGamma')
    #Variables['ZGamma_Inclusive'].Write()

    Variables['ZGToLLG'].SetName('ZGToLLG')
    Variables['ZGToLLG'].SetTitle('ZGToLLG')
    #Variables['ZGToLLG'].Write()

    Variables['GJets_HT_40To100'].Add(Variables['GJets_HT_40To100'])
    Variables['GJets_HT_100To200'].Add(Variables['GJets_HT_100To200'])
    Variables['GJets_HT_200To400'].Add(Variables['GJets_HT_200To400'])
    Variables['GJets_HT_400'].Add(Variables['GJets_HT_400'])
    Variables['GJets_HT_40To100'].SetName('GJets')
    Variables['GJets_HT_40To100'].SetTitle('GJets')
    #Variables['GJets_HT_40To100'].Write()

    print Variables['GJets_HT_40To100'].Integral()


    Variables['GJets_HT_40To100'].Add(Variables['ZGToLLG'])
    Variables['GJets_HT_40To100'].Add(Variables['ZGamma_Inclusive'])
    Variables['GJets_HT_40To100'].Add(Variables['WGamma'])
    Variables['GJets_HT_40To100'].Add(Variables['WtoLNuTau'])
    Variables['GJets_HT_40To100'].Add(Variables['DiPhotonJets'])
    Variables['GJets_HT_40To100'].SetName('AllBkg_'+varname+channel)
    Variables['GJets_HT_40To100'].SetTitle('AllBkg_'+varname+channel)
    Variables['GJets_HT_40To100'].Write()

    print Variables['GJets_HT_40To100'].Integral()
    
    del Variables

      
xlow1 = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,368,369,370,371,372,373,374,375,376,377,378,379,380,381,382,383,384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,399,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,424,425,426,427,428,429,430,431,432,433,434,435,436,437,438,439,440,441,442,443,444,445,446,447,448,449,450,451,452,453,454,455,456,457,458,459,460,461,462,463,464,465,466,467,468,469,470,471,472,473,474,475,476,477,478,479,480,481,482,483,484,485,486,487,488,489,490,491,492,493,494,495,496,497,498,499,500]
xbin1 = len(xlow1)-1

xlow = [-3.5,-3.4,-3.3,-3.2,-3.1,-3.0,-2.9,-2.8,-2.7,-2.6,-2.5,-2.4,-2.3,-2.2,-2.1,-2.0,-1.9,-1.8,-1.7,-1.6,-1.5,-1.4,-1.3,-1.2,-1.1,-1.0,-0.9,-0.8,-0.7,-0.6,-0.5,-0.4,-0.3,-0.2,-0.1,1.97064586871e-15,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3.0,3.1,3.2,3.3,3.4,3.5]
xbin = len(xlow)-1




MEx_corr = '(MEx_old - (0.231012 - 0.0368553*NVtx))'
MEy_corr = '(MEy_old - (0.164057 - 0.119796*NVtx))'

Met_corr = 'sqrt('+MEx_corr+'**2+'+MEy_corr+'**2)'
Phi_corr = 'TMath::ATan2('+MEy_corr+','+MEx_corr+')'
Phi_old  = 'TMath::ATan2(MEy_old,MEx_old)'

var1 = Met_corr
varname1 = 'CorrMET'

var2 = Phi_corr
varname2 = 'CorrPhi'

var3 = '( TMath::ATan2(MEy_old,MEx_old)  )';
varname3 = 'OldPhi'

channel1 = "FixedResults_NoCut"
channel = "FixedResults_MetCut"

testcut1 = '1'
testcut = Met_corr+' > 40.'

print Met_corr


f = TFile(channel+"_Histos.root","RECREATE")
f.cd('..')
f.mkdir('phiCorr')
f.cd('phiCorr')

makeHistos(channel1,var1, xbin1, xlow1,varname1,testcut1)
makeHistos(channel1,var2, xbin,  xlow, varname2,testcut1)
makeHistos(channel1,var3, xbin,  xlow, varname3,testcut1)

makeHistos(channel,var1, xbin1, xlow1,varname1,testcut)
makeHistos(channel,var2, xbin,  xlow, varname2,testcut)
makeHistos(channel,var3, xbin,  xlow, varname3,testcut)

