import ROOT, sys, os, string, re
from ROOT import *
from ROOT import TCanvas, TFile, TProfile, TNtuple, TH1F, TH1D, TH2D, TH2F, TF1, TPad, TPaveLabel, TPaveText, TLegend, TLatex, THStack, TGraph, TGraphErrors, TColor, TMath
from ROOT import gROOT, gBenchmark, gRandom, gSystem, Double, gPad

from array import array

import math
from math import *

from tdrStyle import *
setTDRStyle()

from LoadData import *

print "Starting Plotting Be Patient!"

scale_up = 1000.
lumi = 7369.
lumi_str = '7.3'

#7.396
def plot_nice1D(channel, var, bin, low, high, ylabel, xlabel, save, setLog = False, finalcuts = False):

    result = true

    # Choose 1, ratio or pull
    drawPull = False
    drawRatio = True
    
    #folder = 'Preliminary'
    #folder = 'Lepton_CR'
    #folder = 'ModelIndep'
    #folder = 'SusyHiggs'

    folder = 'newReso'
    
    #No Tau

    List = [ 'DiPhotonJets','DiphotonBox_Pt_25to250','DiphotonBox_Pt_250toInf','WtoLNuMu','WtoLNuTau','WGamma','ZGToLLG','ZGamma_Inclusive','efake_dd','qcd_dd','GJets_HT_40To100','GJets_HT_100To200','GJets_HT_200To400','GJets_HT_400','SinglePhotonParked','DM','MChi_70'] 

    SF_photon = "( (0.99 * 0.97 * (Pho_Pt>40 && Pho_Pt<50)) +  (0.99 * 1.01 * (Pho_Pt>=50) ) )"
    
    cut_GGFTrig = " && (hltmatched==1)"

    stack = THStack('a', 'a')

    added = TH1D('a', 'a',bin,low,high)
    added.Sumw2()

    added_mconly = TH1D('added_mconly', 'added_mconly',bin,low,high)
    added_mconly.Sumw2()

    added_nogjets = TH1D('added_nogets', 'added_nogjets',bin,low,high)
    added_nogjets.Sumw2()
       
    justGJets = TH1D('justGJets', 'justGJets',bin,low,high)
    justGJets.Sumw2()

    Variables = {}    
    efficiency ={}
    totalbkg = 0
    diphoton = 0.
    gamma_jet = 0.
 
    print ' '
    print var

    for Type in List:

        pu_weight  = "MyWeightData_new"
        #pu_weight  = "MyWeightData_new_sys" 

        

        trig_phoid = "((0.5*0.892*(1+TMath::Erf( (Pho_Pt  + 36.8) / (43.8*sqrt(2))))) * (Pho_Pt  >30.) )"
        trig_met   = "((0.5*0.986*(1+TMath::Erf( (MET - 28.0) / (26.0*sqrt(2))))) * (MET>40.) )"

        #trig_met   = "((0.5*1.0*(1+TMath::Erf( (MET - 30.0) / (45.5*sqrt(2))))) * (MET>40.) )"

        #trig_met = "(1.0)"
        
        puweight = "(1.0)"
        
        if (Type.startswith('GJets')):
            other_weight = "(1.7 * (n_jets_mva_loose == 0) + 1.1 * (n_jets_mva_loose > 0))"
            dphi_weight = "(0.378403 - 0.159585*TMath::Abs(dphi_pho_met) + 1.35184*pow(TMath::Abs(dphi_pho_met),2) - 0.423989*pow(TMath::Abs(dphi_pho_met),3)- 0.19808*pow(TMath::Abs(dphi_pho_met),4) + 0.108294*pow(TMath::Abs(dphi_pho_met),5) - 0.0130729*pow(TMath::Abs(dphi_pho_met),6))"

 
        else:
            dphi_weight = "(1.0)"
            other_weight = "(1.0)"

        #PRELIMINARY
        cut_standard ="(Pho_Pt > 45 && Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.442 && sigmaIEtaIEta > 0.001  && sqrt(sigmaIPhiIPhi) > 0.001  &&  Pho_R9<1.0    && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 && MET>40. && loose_mu_10==0 && foundvetoEl_10==0 )"

        #LEPTON_CR
        #cut_standard= "(Pho_Pt > 45 && Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.442 && sigmaIEtaIEta > 0.001  && sqrt(sigmaIPhiIPhi) > 0.001  && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 &&  Pho_R9<1.0  && MET>40. && (loose_mu_10==1 || foundvetoEl_10 == 1) )"

        #MODELINDEP
        #cut_standard ="(Pho_Pt > 45 && Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.442 && sigmaIEtaIEta > 0.001  && sqrt(sigmaIPhiIPhi) > 0.001  &&  Pho_R9<1.0    && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 && MET>40. && loose_mu_10==0 && foundvetoEl_10==0 && n_jets_mva_loose < 2 && (TMath::Abs(dphi_jet_pho) <2.5 || dphi_jet_pho == -99) )"

        #SUSYHIGGS
        #cut_standard= "(Pho_Pt > 45 && Pho_Pt<60.  && Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.442 && sigmaIEtaIEta > 0.001  && sqrt(sigmaIPhiIPhi) > 0.001  && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 &&  Pho_R9<1.0  && MET>40. && MetSig > 20 && loose_mu_10==0 && foundvetoEl_10 == 0 && MT > 100. && minMET>45.)" 
        

        weight  =  "(" + pu_weight + "*"+ other_weight + "*" + dphi_weight + "*" + trig_phoid + "*" +trig_met + "*" +SF_photon+")"

        Variables[Type] = TH1F(Type+save+channel, Type+save+channel, bin, low, high)
        Variables[Type].Sumw2()
        histName = Type+save+channel
        
        if Type.startswith("DiPhoton") or Type.startswith("DiphotonBox"):
            #Variables[Type].SetFillColor(ROOT.kOrange-3)
            #Variables[Type].SetLineColor(ROOT.kOrange-3)
            Variables[Type].SetFillColor(ROOT.kMagenta-2)
            Variables[Type].SetLineColor(ROOT.kMagenta-2)
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard + " ) * 1 *"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            stack.Add(Variables[Type],"hist")
            added.Add(Variables[Type])
            added_mconly.Add(Variables[Type])
            added_nogjets.Add(Variables[Type])
                        
        if Type.startswith("WtoLNuMu"):
            Variables[Type].SetFillColor(ROOT.kMagenta-2)
            Variables[Type].SetLineColor(ROOT.kMagenta-2)
            Trees[Type].Draw(var + " >> " + histName ,  "(" + cut_standard +  " )* 1 *" +weight,"goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            stack.Add(Variables[Type],"hist")
            added.Add(Variables[Type])
            added_mconly.Add(Variables[Type])
            added_nogjets.Add(Variables[Type])


        if Type.startswith("WtoLNuTau"):
            Variables[Type].SetFillColor(ROOT.kMagenta-2)
            Variables[Type].SetLineColor(ROOT.kMagenta-2)
            Trees[Type].Draw(var + " >> " + histName ,  "(" + cut_standard +  " && ( TMath::Abs(gen_pdg) < 15 ) )* 1 *" +weight,"goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            stack.Add(Variables[Type],"hist")
            added.Add(Variables[Type])
            added_mconly.Add(Variables[Type])
            added_nogjets.Add(Variables[Type])
                
        if Type.startswith("WGamma"):
            Variables[Type].SetFillColor(ROOT.kGreen-3)
            Variables[Type].SetLineColor(ROOT.kGreen-3)
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard  + ") * 1.05 *"+weight , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            stack.Add(Variables[Type],"hist")
            added.Add(Variables[Type])
            added_mconly.Add(Variables[Type])
            added_nogjets.Add(Variables[Type])
            
        if Type.startswith('ZGamma_Inclusive'):
            Variables[Type].SetFillColor(ROOT.kYellow-4)
            Variables[Type].SetLineColor(ROOT.kYellow-4)
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard  + " && isZnn==1 ) * 1.2 * "+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            stack.Add(Variables[Type],"hist")
            added.Add(Variables[Type])
            added_mconly.Add(Variables[Type])
            added_nogjets.Add(Variables[Type])
            
        if Type.startswith('ZGToLLG'):
            Variables[Type].SetFillColor(ROOT.kYellow-4)
            Variables[Type].SetLineColor(ROOT.kYellow-4)
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard  + ")*"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            stack.Add(Variables[Type],"hist")
            added.Add(Variables[Type])
            added_mconly.Add(Variables[Type])
            added_nogjets.Add(Variables[Type])            

        if Type.startswith("qcd"):
            Variables[Type].SetFillColor(9)
            Variables[Type].SetLineColor(9)
            Trees[Type].Draw(var + " >> " + histName,"(" +cut_standard +cut_GGFTrig + "&& (HoE < 0.05 && sigmaIEtaIEta < 0.015 ))* (1.503 + 981./pow(Pho_Pt,1.75))"   , "goff")

            stack.Add(Variables[Type],"hist")
            added.Add(Variables[Type])
            added_nogjets.Add(Variables[Type])                        

#        if Type.startswith("PJets_"):
        if Type.startswith("GJets_"):
            Variables[Type].SetFillColor(ROOT.kRed-7)
            Variables[Type].SetLineColor(ROOT.kRed-7)
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") * 1.0 * "+weight   , "goff")
            #Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") * 1.25 * "+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            stack.Add(Variables[Type],"hist")
            added.Add(Variables[Type])
            added_mconly.Add(Variables[Type])            
            justGJets.Add(Variables[Type])

        if Type.startswith("efake_dd"):
            Variables[Type].SetFillColor(7)
            Variables[Type].SetLineColor(7)
            #Trees[Type].Draw(var + " >> " + histName ,  "(" + cut_standard  + ") * (0.0252) ","goff")
            Trees[Type].Draw(var + " >> " + histName ,  "(" + cut_standard  + ") * (0.0238) ","goff")
            stack.Add(Variables[Type],"hist")
            added.Add(Variables[Type])
            added_nogjets.Add(Variables[Type])
                        
##         if Type.startswith("MChi_120"):
##             Variables[Type].SetLineColor(1)
##             Variables[Type].SetLineWidth(3)
##             Variables[Type].SetLineStyle(5)
##             Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") *"+weight   , "goff")
##             Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])

        if Type.startswith("MChi_70"):
            Variables[Type].SetLineColor(1)
            Variables[Type].SetLineWidth(3)
            Variables[Type].SetLineStyle(8)
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") *"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])

##         if Type.startswith("MChi_90"):
##             Variables[Type].SetLineColor(1)
##             Variables[Type].SetLineWidth(3)
##             Variables[Type].SetLineStyle(8)
##             Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") *"+weight   , "goff")
##             Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])

##         if Type.startswith("MChi_80"):
##             Variables[Type].SetLineColor(1)
##             Variables[Type].SetLineWidth(3)
##             Variables[Type].SetLineStyle(8)
##             Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") *"+weight   , "goff")
##             Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])

##         if Type.startswith("MChi_100"):
##             Variables[Type].SetLineColor(1)
##             Variables[Type].SetLineWidth(3)
##             Variables[Type].SetLineStyle(8)
##             Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") *"+weight   , "goff")
##             Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])


        if Type.startswith("DM"):
            Variables[Type].SetLineColor(2)
            Variables[Type].SetLineWidth(3)
            Variables[Type].SetLineStyle(8)
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") *"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type] * 1000)

            
        if Type.startswith("SinglePhotonParked"):
            Variables[Type].SetMarkerStyle(20)
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  cut_GGFTrig +")"  , "goff")


#        if Type.startswith("PJets_"):
        if Type.startswith("GJets_"):
            gamma_jet += round(Variables[Type].Integral(0,bin+1),2)
            
        if Type.startswith("Di"):
            diphoton += round(Variables[Type].Integral(0,bin+1),2)

        if Variables[Type].Integral(0,bin+1) != 0:
            if not (Type.startswith("MChi") or Type.startswith("DM")  or Type.startswith("SinglePhoton")):
                totalbkg+= Variables[Type].Integral(0,bin+1)

        efficiency[Type] = Variables[Type].Integral()/Nevents[Type]

    
    lumi_error = 0.026
    qcd_error = 0.35 
    efake_error = 0.1 
    other_error = 0.05
    pjets_error = 0.20

    ratiosys  = TH1D('Ratio2', 'Ratio2', bin, low, high)
    ratiosys = Variables['SinglePhotonParked'].Clone()

    uncert_list = []
    uncertband = added.Clone();
     
    List_1 = ['DiPhotonJets', 'DiphotonBox_Pt_25to250','DiphotonBox_Pt_250toInf', 'WtoLNuMu','WtoLNuTau' ,'GJets_HT_40To100','GJets_HT_100To200','GJets_HT_200To400','GJets_HT_400','WGamma','ZGamma_Inclusive','qcd_dd','efake_dd','ZGToLLG']

    #List_1 = ['DiPhotonJets', 'DiphotonBox_Pt_25to250','DiphotonBox_Pt_250toInf', 'WtoLNuMu','GJets_HT_40To100','GJets_HT_100To200','GJets_HT_200To400','GJets_HT_400','WGamma','ZGamma_Inclusive','qcd_dd','efake_dd','ZGToLLG']

    for hbin in range(0,uncertband.GetNbinsX()+1): 

        uncert_lumi = 0.026
        uncert_qcd = 0.35
        uncert_efake = 0.1
        uncert_other = 0.05
        uncert_stat = 0.
        uncert_pjets = 0.2
        totalbin = 0.

        for i in List_1:

            if (i.startswith('qcd')): 
                uncert_qcd += (Variables[i].GetBinContent(hbin+1)*qcd_error)
                uncert_stat += Variables[i].GetBinError(hbin+1)**2
                            
                test = sqrt(  ((Variables[i].GetBinContent(hbin+1)*qcd_error))**2  + (Variables[i].GetBinError(hbin+1))**2 )

            elif (i.startswith('efake')): 
                uncert_efake += (Variables[i].GetBinContent(hbin+1)*efake_error)
                uncert_stat += Variables[i].GetBinError(hbin+1)**2
                
                test = sqrt(  (Variables[i].GetBinContent(hbin+1)*efake_error)**2 + (Variables[i].GetBinError(hbin+1))**2 )
                
            elif (i in xsec.keys()):

                if(i.startswith('GJet')):
                    uncert_pjets +=(Variables[i].GetBinContent(hbin+1)*pjets_error)
                uncert_lumi += (efficiency[i]*xsec[i])
                uncert_other += (Variables[i].GetBinContent(hbin+1)*other_error)
                uncert_stat += Variables[i].GetBinError(hbin+1)**2

                test = sqrt( (lumi_error*((efficiency[i]*xsec[i])))**2 + ((Variables[i].GetBinContent(hbin+1)*other_error))**2 + (Variables[i].GetBinError(hbin+1))**2 )

            #print "bin number: " ,hbin+1, " sample: " ,i," number of events: " , Variables[i].GetBinContent(hbin+1) , " uncert_efake: ", uncert_efake," uncert_qcd: ",uncert_qcd," uncert_other: ",uncert_other," uncert_stat: ", uncert_stat," uncert_lumi: ",uncert_lumi


            #print i, " bin content: ",round( Variables[i].GetBinContent(hbin+1),2), " error: " , round(test,2), " %: " , round(test/(Variables[i].GetBinContent(hbin+1) +1),2) * 100
            totalbin += round( Variables[i].GetBinContent(hbin+1),2)

        uncert = sqrt( (lumi_error*uncert_lumi)**2 + uncert_qcd**2 + uncert_efake**2 + uncert_other**2 + uncert_stat + uncert_pjets**2)

        #print ' ' 
        #print 'Bin Content Bkg : ', totalbin, ' ', uncert, ' % ' , round(uncert/totalbin,2)*100
        #print 'Bin Content Data: ', round(Variables['SinglePhotonParked'].GetBinContent(hbin+1),2), ' ',round(Variables['SinglePhotonParked'].GetBinError(hbin+1),2) , ' % ' , round(Variables['SinglePhotonParked'].GetBinError(hbin+1)/Variables['SinglePhotonParked'].GetBinContent(hbin+1),2)*100
        #print ' ' 



        #print "bin number: " ,hbin+1," total bkg. ",added.GetBinContent(hbin+1)," +/- ",uncert
        sys = sqrt( (lumi_error**2)*uncert_lumi + uncert_qcd**2 + uncert_efake**2 + uncert_other**2 )
        ratiosys.SetBinContent(hbin+1,0.0)
        
        if (added.GetBinContent(hbin+1)>0):
            #ratiosys.SetBinError(hbin+1,sys/added.GetBinContent(hbin+1))
            ratiosys.SetBinError(hbin+1,uncert/added.GetBinContent(hbin+1))
        else:
            ratiosys.SetBinError(hbin+1,0)

        if uncertband.GetBinContent(hbin+1) != 0:
            dummy = 1.0
            #print uncertband.GetBinContenthbin+1),'+/-',uncert,'(',100*uncert/uncertband.GetBinContent(hbin+1),'%)'
        uncertband.SetBinError(hbin+1,uncert);
        added.SetBinError(hbin+1,uncert);
        uncert_list.append(uncert)
    
        
    Pull  = TH1D('Pull', 'Pull', bin, low, high)
    Pull.Sumw2()
    Pull = Variables['SinglePhotonParked'].Clone()
    Pull.Add(added,-1)
    
    Ratio  = TH1D('Ratio', 'Ratio', bin, low, high)
    Ratio.Sumw2()
    Ratio = Variables['SinglePhotonParked'].Clone()
    Ratio.Add(added,-1)
    Ratio.Divide(added)

    if (var == 'n_jets_mva_loose'):
        njets_data  = TH1D('njets_data', 'njets_data', bin, low, high)
        njets_data.Sumw2()
        njets_data = Variables['SinglePhotonParked'].Clone()
        njets_data.Add(added_nogjets,-1)
        njets_data.Divide(justGJets)
        for jetbin in range(0,njets_data.GetNbinsX()+1):
            print njets_data.GetBinContent(jetbin)

    if (var == 'TMath::Log10(Pho_Pt/(HT+Pho_Pt))'):
        ReweightG_data  = TH1D('ReweightG_data', 'ReweightG_data', bin, low, high)
        ReweightG_data.Sumw2()
        ReweightG_data = Variables['SinglePhotonParked'].Clone()
        ReweightG_data.Add(added_nogjets,-1)
        ReweightG_data.Divide(justGJets)
        b = TF1("b",'pol6')
        ReweightG_data.Fit(b)
        b.Print()
        ReweightG_data.SaveAs(folder+'/Reweight_'+save+'.root')
        for jetbin in range(0,ReweightG_data.GetNbinsX()+1):
            print ReweightG_data.GetBinContent(jetbin)

            
    if (var == 'NVtx'):
        ReweightNVtx_data  = TH1D('ReweightNVtx_data', 'ReweightNVtx_data', bin, low, high)
        ReweightNVtx_data.Sumw2()
        ReweightNVtx_data = Variables['SinglePhotonParked'].Clone()
        ReweightNVtx_data.Add(Variables['qcd_dd'],-1)
        ReweightNVtx_data.Add(Variables['efake_dd'],-1)
        ReweightNVtx_data.Scale(1./ReweightNVtx_data.Integral()) # don't let NVtx reweighting change normalization
        ReweightNVtx_mc  = TH1D('ReweightNVtx_mc', 'ReweightNVtx_mc', bin, low, high)
        ReweightNVtx_mc.Sumw2()
        ReweightNVtx_mc = added_mconly.Clone()
        ReweightNVtx_mc.Scale(1./ReweightNVtx_mc.Integral())
        ReweightNVtx_data.Divide(ReweightNVtx_mc)
        b = TF1("b",'pol6') 
        ReweightNVtx_data.Fit(b)
        b.Print()
        ReweightNVtx_data.SaveAs(folder+'/Reweight_'+save+'.root')

    if (var == 'TMath::Abs(dphi_pho_met)'):
    #if (var == 'TMath::Abs(dphi_jet_pho)'):
        ReweightDphiMetG_data  = TH1D('ReweightDphiMetG_data', 'ReweightDphiMetG_data', bin, low, high)
        ReweightDphiMetG_data.Sumw2()
        ReweightDphiMetG_data = Variables['SinglePhotonParked'].Clone()
        ReweightDphiMetG_data.Add(added_nogjets,-1)
        ReweightDphiMetG_data.Divide(justGJets)
        b = TF1("b",'pol6')
        ReweightDphiMetG_data.Fit(b)
        b.Print()
        ReweightDphiMetG_data.SaveAs(folder+'/Reweight_'+save+'.root')
        
        
    #ratiosys = Ratio.Clone()

    #for hbin in range(0,uncertband.GetNbinsX()+1): 
        #print "data  : ", Variables['SinglePhotonParked'].GetBinContent(hbin), " ", Variables['SinglePhotonParked'].GetBinError(hbin)
        #print "added : ", added.GetBinContent(hbin), " ", added.GetBinError(hbin)
        #if Pull.GetBinContent(hbin) != 0:
            #print "Pull  : ",round(Pull.GetBinContent(hbin),2), " " , round(Pull.GetBinError(hbin),2),  " Sigma: ", round(Pull.GetBinContent(hbin) /  Pull.GetBinError(hbin),2)
        #if Ratio.GetBinContent(hbin) != 0 :
            #print "Ratio : " ,round(Ratio.GetBinContent(hbin),2), " ",round(Ratio.GetBinError(hbin),2),  " Sigma: ", round(Ratio.GetBinContent(hbin)/Ratio.GetBinError(hbin),2)
            #print "Sys for Ratio: ", round(ratiosys.GetBinError(hbin),2)

            #                uncert/added.GetBinContent(hbin),2)

    
    uncertband.SetFillStyle(3244);
    uncertband.SetFillColor(33);
    gStyle.SetHatchesLineWidth(1) 

    legend = TLegend(.60,.60,.92,.92)
    legend. AddEntry(Variables['GJets_HT_40To100'],"#gamma + Jets" , "f")
    legend . AddEntry( Variables['qcd_dd'], "Jet Faking Photon" , "f")
    #    legend . AddEntry( Variables['PJets_50to80'], "#gamma + Jets" , "f")
    legend . AddEntry( Variables['efake_dd'], "Electron Faking Photon" , "f")
    #legend . AddEntry( Variables['W2lnuEl'], "W #rightarrow l #nu" , "f")
    legend . AddEntry( Variables['ZGamma_Inclusive'],"Z #gamma","f")  
    legend . AddEntry( Variables['WGamma'], "W #gamma #rightarrow l #nu #gamma" , "f")
    #legend . AddEntry( Variables['DiPhotonJets'], "#gamma #gamma" , "f")
    legend . AddEntry( Variables['WtoLNuMu'], "W #rightarrow #mu(#tau) #nu & #gamma #gamma " , "f")
    #legend . AddEntry( Variables['WtoLNuTau'], "W #rightarrow #tau #nu" , "f")
    #legend . AddEntry( Variables['ZGToLLG'],"Z #rightarrow l l #gamma","f")
    #legend . AddEntry( Variables['DoubleMu'], "Data Driven Z #rightarrow #nu #nu #gamma","f")    
    #legend . AddEntry( Variables['Signal_GluGlu'], "GGF Signal X 1K", "l")
#    legend . AddEntry( Variables['MChi_120'], "M_{#Chi} = 120", "l")
    legend . AddEntry( Variables['DM'], "Dark Matter", "l")
    legend . AddEntry( Variables['MChi_70'], "M_{#Chi} = 70","l")
    legend . AddEntry( Variables['SinglePhotonParked'], "Data", "p")

    c4 = TCanvas("c4","c4", 900, 1000)
    c4.SetBottomMargin(0.3)
    c4.SetRightMargin(0.06)
  #  stack.SetMaximum( stack.GetMaximum()  +  10*stack.GetMaximum() )
    #stack.SetMaximum( 0.01*stack.GetMaximum())

    #stack.SetMaximum(Variables['SinglePhotonParked'].GetMaximum()*10 )

    if save.startswith('ratio') or save.startswith('dphi_pfmetg'):
        stack.SetMaximum(Variables['SinglePhotonParked'].GetMaximum()*100 )

    stack.SetMinimum(0.1)


    if setLog:
        c4.SetLogy()
        stack.SetMaximum( stack.GetMaximum()  +  100*stack.GetMaximum() )
    
    stack.Draw()
    #stack.GetYaxis().CenterTitle()
    stack.GetYaxis().SetTitle(ylabel)
    stack.GetYaxis().CenterTitle()
    stack.GetXaxis().SetTitle(xlabel)
    if(result):
        stack.GetXaxis().SetLabelSize(0)
        stack.GetXaxis().SetTitle('')

    uncertband.Draw("samee2")
    
    if(result):
        Variables['SinglePhotonParked'].Draw("Esame")
    #Variables['MChi_120'].Draw("same")
    Variables['MChi_70'].Draw("same")
    Variables['DM'].Draw("same")

    #print "looking at stack first bin: "
    #print added.GetBinContent(6), added.GetBinContent(7),added.GetBinContent(8),added.GetBinContent(9),added.GetBinContent(10)
    #print Variables['SinglePhotonParked'].GetBinContent(6), Variables['SinglePhotonParked'].GetBinContent(7),Variables['SinglePhotonParked'].GetBinContent(8),Variables['SinglePhotonParked'].GetBinContent(9),Variables['SinglePhotonParked'].GetBinContent(10)
    
    legend.SetShadowColor(0);
    legend.SetFillColor(0);
    legend.SetLineColor(0);

    legend.Draw("same")
    #if save.startswith('MT') or save.startswith('MET') or save.startswith('njets') or save.startswith('Pho_Pt'):
        #legend.Draw("same")
    
    latex2 = TLatex()
    latex2.SetNDC()
    latex2.SetTextSize(0.035)
    latex2.SetTextAlign(31) # align right
    latex2.DrawLatex(0.87, 0.95, lumi_str+" fb^{-1} (8 TeV)");

    latex3 = TLatex()
    latex3.SetNDC()
    latex3.SetTextSize(0.75*c4.GetTopMargin())
    latex3.SetTextFont(62)
    latex3.SetTextAlign(11) # align right
    latex3.DrawLatex(0.22, 0.85, "CMS");
    latex3.SetTextSize(0.5*c4.GetTopMargin())
    latex3.SetTextFont(52)
    latex3.SetTextAlign(11)
    latex3.DrawLatex(0.20, 0.8, "Preliminary");

    toterr = 0

    for i in range(bin):
        i += 1
        toterr += added.GetBinError(i)
        #print i,' ',added.GetBinContent(i),' +/- ',added.GetBinError(i), ' Data is: ', Variables['SinglePhotonParked'].GetBinContent(i)
        if Variables['SinglePhotonParked'].GetBinContent(i) != 0 :
        #if Pull.GetBinContent(i) != 0:
            Pull.SetBinContent(i,Pull.GetBinContent(i)/Pull.GetBinError(i))
        else: Pull.SetBinContent(i,0)

    pad = TPad("pad", "pad", 0.0, 0.0, 1.0, 1.0)
    pad.SetTopMargin(0.7)
    pad.SetFillColor(0)
    pad.SetGridy(1)
    pad.SetFillStyle(0)
    pad.Draw()
    pad.cd(0)
    pad.SetRightMargin(0.06)

    if (drawPull):
        Pull.SetMarkerStyle(20)
        Pull.SetMaximum(5.0 )
        Pull.SetMinimum(-5.0)
        Pull.SetFillColor(2)
        Pull.GetXaxis().SetTitle(xlabel)
        Pull.GetYaxis().SetTitleSize(0.04)
        Pull.GetYaxis().SetTitle('#sigma(Data-MC)')
        Pull.SetMarkerSize(0.7)
        Pull.GetYaxis().SetNdivisions(6)
        Pull.Draw("HIST")
    
    if (drawRatio):
        ratiosys.SetFillColor(33) #SetFillColor(ROOT.kYellow)
        ratiosys.SetLineColor(33) #SetLineColor(1)
        ratiosys.SetLineWidth(1)
        ratiosys.SetMaximum(2)
        ratiosys.SetMinimum(-2)
        ratiosys.GetXaxis().SetTitle(xlabel)
        ratiosys.GetYaxis().SetTitleSize(0.04)
        ratiosys.GetYaxis().SetTitle('Data-Bkg/Bkg.')
        ratiosys.GetYaxis().SetNdivisions(5)
        ratiosys.SetMarkerSize(0)
        if(result):
            ratiosys.Draw("e2")
        Ratio.SetMarkerStyle(20)
        Ratio.SetMarkerColor(1)
        Ratio.SetLineColor(1)
        Ratio.SetMarkerSize(0.8)
        if(result):
            Ratio.Draw("esame")

    if (drawRatio):
        c4.SaveAs(folder+'/StackedHisto_' + save + '.pdf')
    if (drawPull):
        c4.SaveAs(folder+'/StackedHisto_' + save + '.pdf')

    if save.startswith('Pho_Pt'):
        print "*******************************************************"
        print "bkg scaled to ",lumi,"/pb: " ,round(totalbkg,2) , " +/- ", sqrt(toterr**2)

        print "Data: ", Variables['SinglePhotonParked'].Integral(0,bin+1)
#        print "Mchi 120: ", lumi,"/pb: ",round(Variables['MChi_120'].Integral(0,bin+1),2),"Significance: ",round(Variables['MChi_120'].Integral(0,bin+1)/sqrt(totalbkg),2)
        print "Mchi 70:  ", lumi,"/pb: " ,round(Variables['MChi_70'].Integral(0,bin+1),2), "Significance: ", round(Variables['MChi_70'].Integral(0,bin+1)/sqrt(totalbkg),2)
#        print "Mchi 80:  ", lumi,"/pb: " ,round(Variables['MChi_80'].Integral(0,bin+1),2), "Significance: ", round(Variables['MChi_80'].Integral(0,bin+1)/sqrt(totalbkg),2)
#        print "Mchi 90:  ", lumi,"/pb: " ,round(Variables['MChi_90'].Integral(0,bin+1),2), "Significance: ", round(Variables['MChi_90'].Integral(0,bin+1)/sqrt(totalbkg),2)
#        print "Mchi 100:  ", lumi,"/pb: " ,round(Variables['MChi_100'].Integral(0,bin+1),2), "Significance: ", round(Variables['MChi_100'].Integral(0,bin+1)/sqrt(totalbkg),2)


        print "Gamma + Jet: " , gamma_jet, " $\pm$ " ,round(gamma_jet/round(totalbkg,2),2) * 100
        print "Diphoton: ", diphoton, " $\pm$ " ,round(diphoton/round(totalbkg,2),2) * 100
        print "E fake: ",  round(Variables['efake_dd'].Integral(0,bin+1),2)," $\pm$ " , round(round(Variables['efake_dd'].Integral(0,bin+1),2)/round(totalbkg,2),2) * 100
        print "Jet fake: ", round(Variables['qcd_dd'].Integral(0,bin+1),2)," $\pm$ " , round(round(Variables['qcd_dd'].Integral(0,bin+1),2)/round(totalbkg,2),2) * 100
        print "Wgamma : ", round(Variables['WGamma'].Integral(0,bin+1),2), " $\pm$ " ,round(round(Variables['WGamma'].Integral(0,bin+1),2)/round(totalbkg,2),2) * 100
        print "ZGamma : ", round(Variables['ZGamma_Inclusive'].Integral(0,bin+1),2)," $\pm$ " , round( round(Variables['ZGamma_Inclusive'].Integral(0,bin+1),2)/round(totalbkg,2),2) * 100
        print "WtoLNuMu : ", round(Variables['WtoLNuMu'].Integral(0,bin+1),2)," $\pm$ " , round(round(Variables['WtoLNuMu'].Integral(0,bin+1),2)/round(totalbkg,2),2) * 100
        print "WtoLNuTau : ", round(Variables['WtoLNuTau'].Integral(0,bin+1),2)," $\pm$ " , round(round(Variables['WtoLNuTau'].Integral(0,bin+1),2)/round(totalbkg,2),2) * 100
        print "ZGToLLG: ", round(Variables['ZGToLLG'].Integral(0,bin+1),2)," $\pm$ " , round(round(Variables['ZGToLLG'].Integral(0,bin+1),2)/round(totalbkg,2),2) * 100
        
    
    del c4
    del stack
    del Variables
    del var


#var = "TMath::Log10(Pho_Pt/(HT+Pho_Pt))"; bin = 8; low = -1.5; high = 0.5; xaxis = "Log10(Photon Pt / ST)"; yaxis = 'Events'; save = 'Pho_Pt_ST_log'; setLog = True; finalcuts = False;channel = "VBF";
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

#var = "(HT+Pho_Pt)"; bin = 50; low = 0; high = 500; xaxis = "ST"; yaxis = 'Events'; save = 'ST'; setLog = True; finalcuts = False;channel = "VBF";
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

#var = 'Pho_Pt'; bin = 45; low = 45; high = 60; xaxis = "Photon P_{T} [GeV]"; yaxis = 'Events / 0.33 GeV'; save = 'Pho_Pt'; setLog = True; finalcuts = False;channel = "VBF";
#var = 'Pho_Pt'; bin = 15; low = 40; high = 45; xaxis = "Photon P_{T} [GeV]"; yaxis = 'Events / 25 GeV'; save = 'Pho_Pt'; setLog = True; finalcuts = False;channel = "VBF";
var = 'Pho_Pt'; bin = 20; low = 45; high = 545; xaxis = "Photon P_{T} [GeV]"; yaxis = 'Events / 25 GeV'; save = 'Pho_Pt'; setLog = True; finalcuts = False;channel = "VBF";
plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var='TMath::Abs(dphi_pho_met)'; bin=50; low=0; high=3.14; xaxis = "#Delta#Phi(ME_{T},#gamma)"; yaxis = 'Events'; save ='dphimetgamma'; setLog = True; finalcuts = False; channel = "VBF";
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'n_jets_mva_loose'; bin = 10; low =0; high = 10; xaxis = "# of Jets"; yaxis = 'Events'; save ='njets'; setLog = True; finalcuts = False; channel = "VBF";
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

#var = 'MET'; bin = 20; low = 45; high = 545;xaxis= "PF ME_{T} Corrected [GeV]"; yaxis = 'Events / 20 GeV'; save = 'MET'; setLog = True; finalcuts = False;channel = "VBF"
var = 'MET'; bin = 20; low = 40; high = 540;xaxis= "PF ME_{T}[GeV]"; yaxis = 'Events / 25 GeV'; save = 'MET'; setLog = True; finalcuts = False;channel = "VBF"
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var='MT';bin = 30; low =0; high = 300; xaxis = "Transverse Mass[GeV]"; yaxis = 'Events / 10 GeV'; save = 'MT'; setLog = True; finalcuts = False;channel = "VBF"
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'NVtx'; bin = 25; low = 0; high = 50; xaxis= "NVtx";  yaxis = 'Events'; save ='NVtx'; setLog= True; finalcuts = False; channel = "VBF";
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = "pvalue"; bin = 100; low =0; high = 1; xaxis = "P(#Chi^2)"; yaxis = 'Events'; save = 'nolog_pvalue';setLog = True; finalcuts = False;channel = "VBF"
plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)


var = 'minMET'; bin = 50; low = 0; high = 500; xaxis = "Min ME_{T} [GeV]"; yaxis = 'Events / 50 GeV'; save = 'minMET'; setLog = True; finalcuts = False;channel = "VBF"
plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'TMath::Abs(log10(pvalue))'; bin = 20; low = 0; high = 10; xaxis = "Log10(Prob(#Chi^{2}))"; yaxis = 'Events'; save = 'pvalue'; setLog = True; finalcuts = False; channel = "VBF"
plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)



var = 'MetSig'; bin = 20; low = 0; high = 100; xaxis = "PF ME_{T} Significance"; yaxis='Events'; save = 'pfmet_significance'; setLog = True; finalcuts = False;channel = "VBF"
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var='TMath::Abs(dphi_jet_pho)'; bin = 50; low =0; high = 3.5; xaxis = "#Delta#Phi(#gamma,Jet)"; yaxis = 'Events'; save ='dphiphojet'; setLog = True; finalcuts = False; channel = "VBF";
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var='TMath::Abs(dphi_jet_met)';bin = 50; low =0; high = 3.5; xaxis = "#Delta#Phi(ME_{T},Jet)"; yaxis = 'Events'; save ='dphimetjet'; setLog = True; finalcuts = False; channel = "VBF";
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = "TMath::Log10(Pho_Pt/jet_pt)"; bin = 60;low=-1.5; high=3; xaxis="Log10(Photon Pt / Jet Pt)"; yaxis = 'Events'; save = 'Pho_Pt_Jet_Pt'; setLog = True; finalcuts = False;channel = "VBF";
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = "TMath::Log10(Pho_Pt/MET)"; bin = 60; low = -1.5; high = 3; xaxis = "Log10(Photon Pt / ME_{T})"; yaxis = 'Events'; save = 'Pho_Pt_Met_log'; setLog = True; finalcuts = False;channel = "VBF";
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = "TMath::Log10(Pho_Pt/HT)"; bin = 60; low = -1.5; high = 3; xaxis = "Log10(Photon Pt / HT)"; yaxis = 'Events'; save = 'Pho_Pt_HT_log'; setLog = True; finalcuts = False;channel = "VBF";
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

#########################################################################################################################################################################


var = 'TMath::ATan2(MEy_old,MEx_old)';  bin = 80; low = -4; high = 4; xaxis = "Old MET Phi"; yaxis = 'Events / 5 GeV'; save = 'Old_MPhi'; setLog = False; finalcuts = False;channel = "VBF";
plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'MPhi';  bin = 80; low = -4; high = 4; xaxis = "MET Phi"; yaxis = 'Events / 5 GeV'; save = 'MPhi'; setLog = False; finalcuts = False;channel = "VBF";
plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = "Pho_Pt/HT"; bin = 100; low = 0; high = 10; xaxis = "PhoPt_HT"; yaxis = 'Events'; save = 'Pho_Pt_HT'; setLog = True; finalcuts = False;channel = "VBF";
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = "Pho_Pt/MET"; bin = 100; low = 0; high = 10; xaxis = "PhoPt_MET"; yaxis = 'Events'; save = 'Pho_Pt_MET'; setLog = True; finalcuts = False;channel = "VBF";
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)


var = 'HT'; bin = 25; low = 25; high = 525;xaxis= "HT [GeV]"; yaxis = 'Events / 20 GeV'; save = 'HT'; setLog = True; finalcuts = False;channel = "VBF"
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)


var = 'n_jets'; bin = 10; low =0; high = 10; xaxis = "# of Jets"; yaxis = 'Events'; save ='njets_nopuid'; setLog = True; finalcuts = False; channel = "VBF";
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'TMath::Abs(dphi_jet_pho)'; bin = 1; low =98; high = 100; xaxis = "dPhi(Pho,Jet)"; yaxis = 'Events'; save ='dphiphojet2'; setLog = True; finalcuts = False; channel = "VBF";
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'dR_jet_met'; bin = 10; low =0; high = 5; xaxis = "dR(Met,Jet)"; yaxis = 'Events'; save ='dRmetjet'; setLog = True; finalcuts = False; channel = "VBF";
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'dR_pho_met'; bin = 10; low =0; high = 5; xaxis = "dR(Met,Pho)"; yaxis = 'Events'; save ='dRmetpho'; setLog = True; finalcuts = False; channel = "VBF";
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'jet_pt'; bin = 20; low = 45; high = 545; xaxis = "Jet P_{T} [GeV]"; yaxis = 'Events / 20 GeV'; save = 'Jet_Pt'; setLog = True; finalcuts = False;channel = "VBF";
###plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'ntrack'; bin = 75; low = 0; high = 150; xaxis = "N Tracks"; yaxis = 'Events'; save = 'ntrack'; setLog = True; finalcuts = False;channel = "VBF";
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'minDR'; bin = 25; low = 0; high = 5; xaxis = "minDR"; yaxis = 'Events'; save = 'mindR'; setLog = True; finalcuts = False;channel = "VBF";
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'roundness'; bin = 50; low = 0; high = 1; xaxis = "roundness"; yaxis = 'Events'; save = 'roundness'; setLog = True; finalcuts = False;channel = "VBF";
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'angle'; bin = 80; low = 0; high = 1.6; xaxis = "angle"; yaxis = 'Events'; save = 'angle'; setLog = True; finalcuts = False;channel = "VBF";
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)


var = 'LICTD'; bin = 20; low =-10; high = 10; xaxis = "LICTD"; yaxis = 'Events'; save ='LICTD'; setLog = True; finalcuts = False; channel = "VBF";
###plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)


var = 'scEtaWidth'; bin = 50; low =0; high = 0.02; xaxis = "scEtaWidth"; yaxis = 'Events'; save ='scEtaWidth'; setLog = True; finalcuts = False; channel = "VBF";
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'scPhiWidth'; bin = 100; low =0; high = 0.1; xaxis = "scPhiWidth"; yaxis = 'Events'; save ='scPhiWidth'; setLog = True; finalcuts = False; channel = "VBF";
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts) 

var = 'sMin'; bin = 25; low =0; high = 0.5; xaxis = "sMin"; yaxis = 'Events'; save ='sMin'; setLog = True; finalcuts = False; channel = "VBF";
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'sMaj'; bin = 50; low =0; high = 1.5; xaxis = "sMaj"; yaxis = 'Events'; save ='sMaj'; setLog = True; finalcuts = False; channel = "VBF";
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy)'; bin = 50; low=0.1; high = 1; xaxis="Swiss Cross Like"; yaxis = 'Events'; save = "swiss_like"; setLog = True; finalcuts = False;channel = "VBF";
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'TMath::Sqrt(sigmaIPhiIPhi)'; bin = 50; low=0.0; high = 0.02; xaxis="sigmaiphiiphi"; yaxis = 'Events'; save = "iphi"; setLog = True; finalcuts = False;channel = "VBF";
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'sigmaIEtaIEta'; bin = 50; low=0.0; high = 0.02; xaxis="sigmaietaieta"; yaxis = 'Events'; save = "ieta"; setLog = True; finalcuts = False;channel = "VBF";
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'HoE'; bin = 100; low=0.0; high = 0.1; xaxis="HoverE"; yaxis = 'Events'; save = "hoe"; setLog = True; finalcuts = False;channel = "VBF";
###plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'Pho_R9'; bin = 50; low=0.9; high = 1; xaxis="R9"; yaxis = 'Events'; save = "R9"; setLog = True; finalcuts = False;channel = "VBF";
##plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)
#
