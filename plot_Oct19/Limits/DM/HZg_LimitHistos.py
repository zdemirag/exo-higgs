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

def makeHistos(channel,var, bin, xlow, finalcuts,varname):
    
    List = [ 'DiPhotonJets','DiphotonBox_Pt_25to250','DiphotonBox_Pt_250toInf','WtoLNuMu','WtoLNuTau','WGamma','ZGToLLG','ZGamma_Inclusive','efake_dd','qcd_dd','GJets_HT_40To100','GJets_HT_100To200','GJets_HT_200To400','GJets_HT_400', 'SinglePhotonParked','DM','SUFFIX'] 
    
    Variables = {}
    
    efficiency ={}
    
    totalbkg = 0
    bkg = 0
    totalWeight = 0
    data = 0
    diphoton = 0.
    gamma_jet = 0.

    for Type in List:

        SF_photon = "( (0.99 * 0.97 * (Pho_Pt>40 && Pho_Pt<50)) +  (0.99 * 1.01 * (Pho_Pt>=50) ) )"
            
        cut_GGFTrig = " && (hltmatched==1)"
        pu_weight  = "MyWeightData_new"

        trig_phoid = "((0.5*0.89*(1+TMath::Erf( (Pho_Pt  - 19.44) / (7.15*sqrt(2))))) * (Pho_Pt  >30.) )"
        trig_met   = "((0.5*0.977*(1+TMath::Erf( (MET - 28.23) / (25.0*sqrt(2))))) * (MET>40.) )"        

        if (Type.startswith('GJets')):
            other_weight = "(1.7 * (n_jets_mva_loose == 0) + 1.1 * (n_jets_mva_loose > 0))"
            dphi_weight = "(0.378403 - 0.159585*TMath::Abs(dphi_pho_met) + 1.35184*pow(TMath::Abs(dphi_pho_met),2) - 0.423989*pow(TMath::Abs(dphi_pho_met),3)- 0.19808*pow(TMath::Abs(dphi_pho_met),4) + 0.108294*pow(TMath::Abs(dphi_pho_met),5) - 0.0130729*pow(TMath::Abs(dphi_pho_met),6))"

 
        else:
            dphi_weight = "(1.0)"
            other_weight = "(1.0)"

        cut_standard= "(Pho_Pt > 45 && Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.442 && sigmaIEtaIEta > 0.001  && sqrt(sigmaIPhiIPhi) > 0.001  && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 &&  Pho_R9<1.0  && MET>40. && MetSig > 20 && loose_mu_10==0 && foundvetoEl_10 == 0 && MT > 100. && minMET>45. && TMath::Abs(TMath::Log10(pvalue)) > 2 && (TMath::Abs(dphi_jet_pho) <2.5 || dphi_jet_pho == -99) && HT < 100 && angle > 1.2)"

        #weight = "(1.0)"
        weight  =  "(" + pu_weight + "*"+ other_weight + "*" + dphi_weight + "*" + trig_phoid + "*" +trig_met + "*" +SF_photon+")"
        
        histName = Type+varname+channel
        Variables[Type] = TH1F(histName, histName, bin,  array('d',xlow))
        totalWeight += xsec[Type]/Nevents[Type]
        
        if Type.startswith("DiPhoton") or Type.startswith("DiphotonBox"):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard + ") *1*"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            
        if Type.startswith("WtoLNuMu"):
            Trees[Type].Draw(var + " >> " + histName ,  "(" + cut_standard +  ")*1*" +weight,"goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])

        if Type.startswith("WtoLNuTau"):
            Trees[Type].Draw(var + " >> " + histName ,  "(" + cut_standard +  " && ( TMath::Abs(gen_pdg) < 15 ) )* 1 *" +weight,"goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])                        

        if Type.startswith("WGamma"):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard  + ") *1.05*"+weight , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])

        if Type.startswith('ZGamma_Inclusive'):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard  + " && isZnn==1 ) * 1.2 * "+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])

        if Type.startswith('ZGToLLG'):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard  + ")*"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            
        if Type.startswith("qcd"):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard  +cut_GGFTrig + "&& (HoE < 0.05 && sigmaIEtaIEta < 0.015 ))* (1.503 + 981./pow(Pho_Pt,1.75))"   , "goff")
            
        if Type.startswith("efake_dd"):
            Trees[Type].Draw(var + " >> " + histName ,  "(" + cut_standard  + ") * (0.0238) ","goff")

        if Type.startswith("GJets_"):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") *1.0*"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])

        if Type.startswith('SUFFIX'):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") *"+weight   , "goff")
            #Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            
        if Type.startswith("SinglePhotonParked"):
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  cut_GGFTrig +")"  , "goff")

        if Type.startswith("GJets_HT_"):
            gamma_jet += round(Variables[Type].Integral(0,bin+1),2)
        if Type.startswith("Di"):
            diphoton += round(Variables[Type].Integral(0,bin+1),2)

        if Variables[Type].Integral(0,bin+1) != 0:
            if not (Type.startswith("SUFFIX") or Type.startswith("SinglePhoton")):
                bkg += Variables[Type].Integral(0,bin+1)
                totalbkg+= Variables[Type].Integral(0,bin+1)



    ### Combine backgrounds with same systematics and write to the output root file ###
    Variables['SinglePhotonParked'].SetName("data_obs")
    Variables['SinglePhotonParked'].SetTitle("data_obs")
    Variables['SinglePhotonParked'].Write()

    Variables['DiPhotonJets'].Add(Variables['DiphotonBox_Pt_250toInf'])
    Variables['DiPhotonJets'].Add(Variables['DiphotonBox_Pt_25to250'])
    Variables['DiPhotonJets'].SetName("DiPhoton")
    Variables['DiPhotonJets'].SetTitle("DiPhoton")
    Variables['DiPhotonJets'].Write()

    Variables['WtoLNuTau'].Add(Variables['WtoLNuMu'])
    Variables['WtoLNuTau'].SetName('WtoLNu')
    Variables['WtoLNuTau'].SetTitle('WtoLNu')
    Variables['WtoLNuTau'].Write()

    Variables['WGamma'].SetName('WGamma')
    Variables['WGamma'].SetTitle('WGamma')
    Variables['WGamma'].Write()

    Variables['ZGamma_Inclusive'].Add(Variables['ZGToLLG'])
    Variables['ZGamma_Inclusive'].SetName('ZGamma')
    Variables['ZGamma_Inclusive'].SetTitle('ZGamma')
    Variables['ZGamma_Inclusive'].Write()

    Variables['qcd_dd'].SetName('QCD')
    Variables['qcd_dd'].SetTitle('QCD')
    Variables['qcd_dd'].Write()

    Variables['efake_dd'].SetName('EFake')
    Variables['efake_dd'].SetTitle('EFake')
    Variables['efake_dd'].Write()

    Variables['GJets_HT_40To100'].Add(Variables['GJets_HT_100To200'])
    Variables['GJets_HT_40To100'].Add(Variables['GJets_HT_200To400'])
    Variables['GJets_HT_40To100'].Add(Variables['GJets_HT_400'])
    Variables['GJets_HT_40To100'].SetName('PJets')
    Variables['GJets_HT_40To100'].SetTitle('PJets')
    Variables['GJets_HT_40To100'].Write()

    Variables['SUFFIX'].SetName('SUFFIX')
    Variables['SUFFIX'].SetTitle('SUFFIX')
    Variables['SUFFIX'].Write()

    binname = 'SUFFIX'
    datacard = open('datacard_'+binname+'.txt', 'w')
    datacard.write( "#  datacard for SUFFIX signal \n")
    datacard.write( 'imax 1 number of channels \n') 
    datacard.write( 'jmax 7 number of backgrounds \n')
    datacard.write( 'kmax 10 number of nuisance parameters \n')
    datacard.write( '--------------- \n')
    #datacard.write( 'shapes * * '+str(f.GetName())+' $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC \n' )
    datacard.write( '--------------- \n')
    datacard.write( 'bin        '+binname+' \n')
    datacard.write( 'observation '+str(round(Variables['SinglePhotonParked'].Integral(),5))+' \n')
    datacard.write( '--------------- \n')
    datacard.write( 'bin     '+binname+' '+binname+' '+binname+' '+binname+' '+binname+' '+binname+' '+binname+' '+binname+' \n')
    datacard.write( 'process '+binname+' DiPhoton WtoLNu  WGamma  ZGamma  QCD     EFake   PJets \n')
    datacard.write( 'process 0       1        2       3       4       5       6       7 \n')
    datacard.write( 'rate    '+str(round(Variables['SUFFIX'].Integral(),3))+'   '+str(round(Variables['DiPhotonJets'].Integral(),3))+'     '+str(round(Variables['WtoLNuTau'].Integral(),3))+' '+str(round(Variables['WGamma'].Integral(),3))+' '+str(round(Variables['ZGamma_Inclusive'].Integral(),3))+' '+str(round(Variables['qcd_dd'].Integral(),3))+' '+str(round(Variables['efake_dd'].Integral(),3))+' '+str(round(Variables['GJets_HT_40To100'].Integral(),3))+' \n')
    datacard.write( '--------------- \n')
    datacard.write( 'lumi    lnN 1.026 1.026 1.026 1.026 1.026 1.0   1.0   1.026 \n')
    datacard.write( 'qcd     lnN -      -      -     -    -    1.35   -     -    \n')
    datacard.write( 'efake   lnN -      -      -     -    -     -    1.06   -    \n') 
    datacard.write( 'phoEn   lnN 1.04  1.04  1.04  1.04  1.04  -   -     1.04    \n')
    datacard.write( 'metsys  lnN 1.04  1.04  1.04  1.04  1.04  -   -     1.04    \n')
    datacard.write( 'kfacorP lnN -     -     -  -  -      -     -    1.16  \n')
    datacard.write( 'kfacorW lnN -     -     1.05  -  -      -     -    -  \n')
    datacard.write( 'kfacorZ lnN -     -     -  1.05  -      -     -    -  \n')
    datacard.write( 'pusys   lnN 1.01   1.01   1.01  1.01  1.01      -     -    1.01  \n')
    datacard.write( 'pdfsig  lnN 1.1  -     -     -     -      -      -     -  \n')
    #datacard.write( 'jes shape 1 1 1 \n')
    #datacard.write( 'jer shape 1 1 1 \n')
    datacard.close()
    
    ### Print some useful information ###
    print "*******************************************************"
    print "bkg scaled to ",lumi,"/pb: " ,round(totalbkg,2) #, " scaled to 18/fb: " ,  round(totalbkg* 18000,2) ,  " scaled to 7.6/fb: " ,  round(totalbkg* 7600,2)
    #print "total # of entries for bkg is:  " , bkg
    
    print "Data: ", Variables['SinglePhotonParked'].Integral(0,bin+1)

    print "SUFFIX scaled to:  ", lumi,"/pb: " ,round(Variables['SUFFIX'].Integral(0,bin+1),2), "Significance: ", round(Variables['SUFFIX'].Integral(0,bin+1)/sqrt(totalbkg),2)
    
    print "Gamma + Jet: " , gamma_jet, round(gamma_jet/round(totalbkg,2),2) * 100
    print "Diphoton: ", diphoton, round(diphoton/round(totalbkg,2),2) * 100
    print "E fake: ",  round(Variables['efake_dd'].Integral(0,bin+1),2), round(round(Variables['efake_dd'].Integral(0,bin+1),2)/round(totalbkg,2),2) * 100
    print "Jet fake: ", round(Variables['qcd_dd'].Integral(0,bin+1),2), round(round(Variables['qcd_dd'].Integral(0,bin+1),2)/round(totalbkg,2),2) * 100
    print "Wgamma : ", round(Variables['WGamma'].Integral(0,bin+1),2), round(round(Variables['WGamma'].Integral(0,bin+1),2)/round(totalbkg,2),2) * 100
    print "Znunu Gamma : ", round(Variables['ZGamma_Inclusive'].Integral(0,bin+1),2), round( round(Variables['ZGamma_Inclusive'].Integral(0,bin+1),2)/round(totalbkg,2),2) * 100
    #print "WtoLNuMu : ", round(Variables['WtoLNuMu'].Integral(0,bin+1),2), round(round(Variables['WtoLNuMu'].Integral(0,bin+1),2)/round(totalbkg,2),2) * 100
    print "WtoLNu : ", round(Variables['WtoLNuTau'].Integral(0,bin+1),2), round(round(Variables['WtoLNuTau'].Integral(0,bin+1),2)/round(totalbkg,2),2) * 100
    
    print "*******************************************************"
    
    #print totalWeight
    

    del Variables


xlow = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200]

bin = len(xlow)-1

var3 = 'MT'
varname3 = 'MT'

var2 = 'Pho_Pt'
varname2 = 'Pho_Pt'

var = 'MET';
varname = 'MET';

finalcuts = False; channel = "MChi70"
f = TFile(channel+"_Histos.root","RECREATE")
f.cd('..')
f.mkdir('mchi70')
f.cd('mchi70') 

#makeHistos(channel,var, bin, xlow, finalcuts,varname)
makeHistos(channel,var2, bin, xlow, finalcuts,varname2)
#makeHistos(channel,var3, bin, xlow, finalcuts,varname3)


