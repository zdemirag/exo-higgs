import ROOT, sys, os, string, re
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

    # Choose 1, ratio or pull
    drawPull = False
    drawRatio = True

    
    #No Tau
    List = [ 'DiPhotonJets','DiphotonBox_Pt_25to250','DiphotonBox_Pt_250toInf','WtoLNuMu','WtoLNuTau','WGamma','ZGToLLG','ZGamma_Inclusive','efake_dd','qcd_dd','GJets_HT_40To100','GJets_HT_100To200','GJets_HT_200To400','GJets_HT_400','MChi_120','MChi_70', 'MChi_80','MChi_90','MChi_100', 'SinglePhotonParked','DM'] 
    
    #List = [ 'DiPhotonJets',  'SinglePhotonParked'] 
    

    SF_photon = "0.99"    
    cut_GGFTrig = " && (hltmatched==1)"

    stack = THStack('a', 'a')
    added = TH1D('a', 'a',bin,low,high)
    added.Sumw2()

    Variables = {}    
    efficiency ={}
    totalbkg = 0
    diphoton = 0.
    gamma_jet = 0.

    print ' '
    print var

    for Type in List:

        if var == 'Phi_old':
            var = 'TMath::ATan2(MEy_old,MEx_old)'

        if var == 'MT_old':
            #var = 'sqrt( (Pho_Pt+MET_old)* (Pho_Pt+MET_old) - (Pho_Px+MEx_old)*(Pho_Px+MEx_old) - (Pho_Py+MEy_old)*(Pho_Py+MEy_old) )'
            var = 'sqrt((2*Pho_Pt*'+MET_old+')*(1-TMath::Cos(Pho_Phi-'+Phi_old +')))'

        if( Type == 'SinglePhotonParked' or  Type == 'efake_dd'  or  Type == 'qcd_dd'):

            MEx_corr = '(MEx_old-(-0.199274+0.319277*NVtx-0.00139148*NVtx*NVtx))'
            MEy_corr = '(MEy_old-(-0.845096-0.00599484*NVtx-0.00237262*NVtx*NVtx))'
            Phi_corr = 'TMath::ATan2('+MEy_corr+','+MEx_corr+')'
            Met_corr = '(sqrt('+MEx_corr+'**2+'+MEy_corr+'**2))'

            #MT_new = 'sqrt( (Pho_Pt+'+Met_corr+')* (Pho_Pt+'+Met_corr+') - (Pho_Px+'+MEx_corr+')*(Pho_Px+'+MEx_corr+') - (Pho_Py+'+MEy_corr+')*(Pho_Py+'+MEy_corr+') )'

            MT_new = 'sqrt((2*Pho_Pt*'+Met_corr+')*(1-TMath::Cos(Pho_Phi-'+Phi_corr +')))'

            if var=='Met_corr' or var =='(sqrt((MEx_old-(0.027699-0.00586364*NVtx-0.000996412*NVtx*NVtx))**2+(MEy_old-(-0.0312551-0.0901471*NVtx-0.000950153*NVtx*NVtx))**2))':
                var = Met_corr
            if var=='Phi_corr' or var =='TMath::ATan2((MEy_old-(-0.0312551-0.0901471*NVtx-0.000950153*NVtx*NVtx)),(MEx_old-(0.027699-0.00586364*NVtx-0.000996412*NVtx*NVtx)))':
                var = Phi_corr
            if var =='MT_new' or var == 'sqrt((2*Pho_Pt*(sqrt((MEx_old-(0.027699-0.00586364*NVtx-0.000996412*NVtx*NVtx))**2+(MEy_old-(-0.0312551-0.0901471*NVtx-0.000950153*NVtx*NVtx))**2)))*(1-TMath::Cos(Pho_Phi-TMath::ATan2((MEy_old-(-0.0312551-0.0901471*NVtx-0.000950153*NVtx*NVtx)),(MEx_old-(0.027699-0.00586364*NVtx-0.000996412*NVtx*NVtx))))))':
                var = MT_new
        else :
            MEx_corr = '(MEx_old-(0.027699-0.00586364*NVtx-0.000996412*NVtx*NVtx))'
            MEy_corr = '(MEy_old-(-0.0312551-0.0901471*NVtx-0.000950153*NVtx*NVtx))'
            Phi_corr = 'TMath::ATan2('+MEy_corr+','+MEx_corr+')'
            Met_corr = '(sqrt('+MEx_corr+'**2+'+MEy_corr+'**2))'
            #MT_new = 'sqrt( (Pho_Pt+'+Met_corr+')* (Pho_Pt+'+Met_corr+') - (Pho_Px+'+MEx_corr+')*(Pho_Px+'+MEx_corr+') - (Pho_Py+'+MEy_corr+')*(Pho_Py+'+MEy_corr+') )
            MT_new = 'sqrt((2*Pho_Pt*'+Met_corr+')*(1-TMath::Cos(Pho_Phi-'+Phi_corr +')))'

            if var=='Met_corr' or var=='(sqrt((MEx_old-(-0.199274+0.319277*NVtx-0.00139148*NVtx*NVtx))**2+(MEy_old-(-0.845096-0.00599484*NVtx-0.00237262*NVtx*NVtx))**2))':
                var = Met_corr
            if var=='Phi_corr' or var == 'TMath::ATan2((MEy_old-(-0.845096-0.00599484*NVtx-0.00237262*NVtx*NVtx)),(MEx_old-(-0.199274+0.319277*NVtx-0.00139148*NVtx*NVtx)))':
                var = Phi_corr
            if var =='MT_new' or var =='sqrt((2*Pho_Pt*(sqrt((MEx_old-(-0.199274+0.319277*NVtx-0.00139148*NVtx*NVtx))**2+(MEy_old-(-0.845096-0.00599484*NVtx-0.00237262*NVtx*NVtx))**2)))*(1-TMath::Cos(Pho_Phi-TMath::ATan2((MEy_old-(-0.845096-0.00599484*NVtx-0.00237262*NVtx*NVtx)),(MEx_old-(-0.199274+0.319277*NVtx-0.00139148*NVtx*NVtx))))))':
                var = MT_new
     
        #print Type
        #print '   Phi_corr: ', Phi_corr
        #print '   Met_corr: ', Met_corr
        #print '     MT_new: ', MT_new
        #print '        var: ', var
        #print ' '

        if var =='dP(phomet)':
            var ='Pho_Phi-'+Phi_corr

            
        #cut_standard = "(Pho_Pt > 45 && Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.442 && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001 && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 &&  Pho_R9<1.0  && "+ Met_corr+">40.)"#&& loose_mu==0 && foundvetoEl ==0 )"

        # No R9
        cut_standard = "(Pho_Pt > 45 &&TMath::Abs(Pho_Eta)<1.4442 && sqrt(sigmaIPhiIPhi) > 0.001 && "+ Met_corr+">40.)"#&& loose_mu==0 && foundvetoEl ==0 )"
        
        
        #cut_standard = "(Pho_Pt > 45 && Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.442 && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001 && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 &&  Pho_R9<1.0  &&  TMath::Abs(log10(pvalue)) > 2 && MetSig > 15  && "+ Met_corr+">40. && loose_mu==0 && foundvetoEl ==0) "

        #cut_standard = "(Pho_Pt > 45 && Pho_R9>0.9 &&TMath::Abs(Pho_Eta)<1.442 && sigmaIEtaIEta > 0.001 && sqrt(sigmaIPhiIPhi) > 0.001 && seedCrystalEnergy/(e1x3+e1x5-seedCrystalEnergy) < 0.9 &&  Pho_R9<1.0  && "+ Met_corr+">40.)"#&& " +MT_new +">100.)"


        pu_weight  = "MyWeightData"
        trig_phoid = "((0.5*0.892*(1+TMath::Erf( (Pho_Pt  + 36.8) / (43.8*sqrt(2))))) * (Pho_Pt  >30.) )"
        trig_met   = "((0.5*0.986*(1+TMath::Erf( ( ("+Met_corr+") - 28.0) / (26.0*sqrt(2))))) * ("+ Met_corr+">40.) )"
        
        weight  =  "(" + pu_weight + "*" + trig_phoid + "*" +trig_met + "*" +SF_photon+")"
        #weight = '1'

        Variables[Type] = TH1F(Type+save+channel, Type+save+channel, bin, low, high)
        Variables[Type].Sumw2()
        histName = Type+save+channel
        
        if Type.startswith("DiPhoton") or Type.startswith("DiphotonBox"):
            Variables[Type].SetFillColor(ROOT.kOrange-3)
            Variables[Type].SetLineColor(ROOT.kOrange-3)
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard + " ) * 1 *"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            stack.Add(Variables[Type],"hist")
            added.Add(Variables[Type])
            
        if Type.startswith("WtoLNu"):
            Variables[Type].SetFillColor(ROOT.kMagenta-2)
            Variables[Type].SetLineColor(ROOT.kMagenta-2)
            Trees[Type].Draw(var + " >> " + histName ,  "(" + cut_standard +  ")* 1 *" +weight,"goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            stack.Add(Variables[Type],"hist")
            added.Add(Variables[Type])

        if Type.startswith("WGamma"):
            Variables[Type].SetFillColor(ROOT.kGreen-3)
            Variables[Type].SetLineColor(ROOT.kGreen-3)
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard  + ") * 1.05 *"+weight , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            stack.Add(Variables[Type],"hist")
            added.Add(Variables[Type])


        if Type.startswith('ZGamma_Inclusive'):
            Variables[Type].SetFillColor(ROOT.kYellow-4)
            Variables[Type].SetLineColor(ROOT.kYellow-4)
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard  + " && isZnn==1 ) * 1.2 * "+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            stack.Add(Variables[Type],"hist")
            added.Add(Variables[Type])

        if Type.startswith('ZGToLLG'):
            Variables[Type].SetFillColor(ROOT.kYellow-4)
            Variables[Type].SetLineColor(ROOT.kYellow-4)
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard  + ")*"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            stack.Add(Variables[Type],"hist")
            added.Add(Variables[Type])
            

        if Type.startswith("qcd"):
            Variables[Type].SetFillColor(9)
            Variables[Type].SetLineColor(9)
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard  + ")* (1.54 + 1114/pow(Pho_Pt,1.799))  "   , "goff")
            stack.Add(Variables[Type],"hist")
            added.Add(Variables[Type])

#        if Type.startswith("PJets_"):
        if Type.startswith("GJets_"):
            Variables[Type].SetFillColor(ROOT.kRed-7)
            Variables[Type].SetLineColor(ROOT.kRed-7)
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") * 1.25 * "+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])
            stack.Add(Variables[Type],"hist")
            added.Add(Variables[Type])

        if Type.startswith("efake_dd"):
            Variables[Type].SetFillColor(7)
            Variables[Type].SetLineColor(7)
            #Trees[Type].Draw(var + " >> " + histName ,  "(" + cut_standard  + ") * (0.009994 + 0.00077*NVtx) ","goff")
            #Trees[Type].Draw(var + " >> " + histName ,  "(" + cut_standard  + ") * (0.02062 + 4.669/pow(ntrack,2.252) ) ","goff")
            Trees[Type].Draw(var + " >> " + histName ,  "(" + cut_standard  + ") * (0.0252) ","goff")
            stack.Add(Variables[Type],"hist")
            added.Add(Variables[Type])       

        if Type.startswith("MChi_120"):
            Variables[Type].SetLineColor(1)
            Variables[Type].SetLineWidth(3)
            Variables[Type].SetLineStyle(5)
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") *"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])

        if Type.startswith("MChi_70"):
            Variables[Type].SetLineColor(1)
            Variables[Type].SetLineWidth(3)
            Variables[Type].SetLineStyle(8)
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") *"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])

        if Type.startswith("MChi_90"):
            Variables[Type].SetLineColor(1)
            Variables[Type].SetLineWidth(3)
            Variables[Type].SetLineStyle(8)
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") *"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])

        if Type.startswith("MChi_80"):
            Variables[Type].SetLineColor(1)
            Variables[Type].SetLineWidth(3)
            Variables[Type].SetLineStyle(8)
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") *"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])

        if Type.startswith("MChi_100"):
            Variables[Type].SetLineColor(1)
            Variables[Type].SetLineWidth(3)
            Variables[Type].SetLineStyle(8)
            Trees[Type].Draw(var + " >> " + histName,  "(" + cut_standard +  ") *"+weight   , "goff")
            Variables[Type].Scale(lumi / Nevents[Type] * xsec[Type])


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
    qcd_error = 0.3 
    efake_error = 0.1 
    other_error = 0.05

    ratiosys  = TH1D('Ratio2', 'Ratio2', bin, low, high)
    ratiosys = Variables['SinglePhotonParked'].Clone()

    uncert_list = []
    uncertband = added.Clone();
     
    List_1 = ['DiPhotonJets', 'DiphotonBox_Pt_25to250','DiphotonBox_Pt_250toInf', 'WtoLNuMu','WtoLNuTau' ,'GJets_HT_40To100','GJets_HT_100To200','GJets_HT_200To400','GJets_HT_400','WGamma','ZGamma_Inclusive','qcd_dd','efake_dd','ZGToLLG']

    for hbin in range(0,uncertband.GetNbinsX()+1): 

        uncert_lumi = 0.026
        uncert_qcd = 0.3
        uncert_efake = 0.1
        uncert_other = 0.05
        uncert_stat = 0.

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
                uncert_lumi += (efficiency[i]*xsec[i])
                uncert_other += (Variables[i].GetBinContent(hbin+1)*other_error)
                uncert_stat += Variables[i].GetBinError(hbin+1)**2

                test = sqrt( (lumi_error*((efficiency[i]*xsec[i])))**2 + ((Variables[i].GetBinContent(hbin+1)*other_error))**2 + (Variables[i].GetBinError(hbin+1))**2 )

            #print "bin number: " ,hbin+1, " sample: " ,i," number of events: " , Variables[i].GetBinContent(hbin+1) , " uncert_efake: ", uncert_efake," uncert_qcd: ",uncert_qcd," uncert_other: ",uncert_other," uncert_stat: ", uncert_stat," uncert_lumi: ",uncert_lumi


            #print i, " bin content: ",round( Variables[i].GetBinContent(hbin+1),2), " error: " , round(test,2), " %: " , round(test/(Variables[i].GetBinContent(hbin+1) +1),2) * 100
            totalbin += round( Variables[i].GetBinContent(hbin+1),2)

        uncert = sqrt( (lumi_error*uncert_lumi)**2 + uncert_qcd**2 + uncert_efake**2 + uncert_other**2 + uncert_stat )

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

    #ratiosys = Ratio.Clone()
    


    for hbin in range(0,uncertband.GetNbinsX()+1): 
        #print "data  : ", Variables['SinglePhotonParked'].GetBinContent(hbin), " ", Variables['SinglePhotonParked'].GetBinError(hbin)
        #print "added : ", added.GetBinContent(hbin), " ", added.GetBinError(hbin)
        if Pull.GetBinContent(hbin) != 0:
            print "Pull  : ",round(Pull.GetBinContent(hbin),2), " " , round(Pull.GetBinError(hbin),2),  " Sigma: ", round(Pull.GetBinContent(hbin) /  Pull.GetBinError(hbin),2)
        if Ratio.GetBinContent(hbin) != 0 :
            print "Ratio : " ,round(Ratio.GetBinContent(hbin),2), " ",round(Ratio.GetBinError(hbin),2),  " Sigma: ", round(Ratio.GetBinContent(hbin)/Ratio.GetBinError(hbin),2)
            print "Sys for Ratio: ", round(ratiosys.GetBinError(hbin),2)

            #                uncert/added.GetBinContent(hbin),2)

    
    uncertband.SetFillStyle(3244);
    uncertband.SetFillColor(33);
    gStyle.SetHatchesLineWidth(1) 

    legend = TLegend(.60,.60,.92,.92)
    legend . AddEntry( Variables['qcd_dd'], "Jet Faking Photon" , "f")
    #    legend . AddEntry( Variables['PJets_50to80'], "#gamma + Jets" , "f")
    legend. AddEntry(Variables['GJets_HT_40To100'],"#gamma + Jets" , "f")
    legend . AddEntry( Variables['efake_dd'], "Electron Faking Photon" , "f")
    #legend . AddEntry( Variables['W2lnuEl'], "W #rightarrow l #nu" , "f")
    legend . AddEntry( Variables['WGamma'], "W #gamma #rightarrow l #nu #gamma" , "f")
    legend . AddEntry( Variables['DiPhotonJets'], "#gamma #gamma" , "f")
    legend . AddEntry( Variables['WtoLNuMu'], "W #rightarrow #mu(#tau) #nu" , "f")
    #legend . AddEntry( Variables['WtoLNuTau'], "W #rightarrow #tau #nu" , "f")
    legend . AddEntry( Variables['ZGamma_Inclusive'],"Z #gamma","f")  
    #legend . AddEntry( Variables['ZGToLLG'],"Z #rightarrow l l #gamma","f")
    #legend . AddEntry( Variables['DoubleMu'], "Data Driven Z #rightarrow #nu #nu #gamma","f")    
    #legend . AddEntry( Variables['Signal_GluGlu'], "GGF Signal X 1K", "l")
    legend . AddEntry( Variables['MChi_120'], "M_{#Chi} = 120", "l")
    legend . AddEntry( Variables['DM'], "Dark Matter Signal", "l")
    #legend . AddEntry( Variables['MChi_70'], "M_{#Chi} = 70","l")
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
    #stack.GetXaxis().SetTitle(xlabel)
    stack.GetYaxis().CenterTitle()
    stack.GetXaxis().SetLabelSize(0)

    uncertband.Draw("samee2")
    
    Variables['SinglePhotonParked'].Draw("Esame")
    Variables['MChi_120'].Draw("same")
    # Variables['MChi_70'].Draw("same")
    Variables['DM'].Draw("same")

    #print "looking at stack first bin: "
    #print added.GetBinContent(6), added.GetBinContent(7),added.GetBinContent(8),added.GetBinContent(9),added.GetBinContent(10)
    #print Variables['SinglePhotonParked'].GetBinContent(6), Variables['SinglePhotonParked'].GetBinContent(7),Variables['SinglePhotonParked'].GetBinContent(8),Variables['SinglePhotonParked'].GetBinContent(9),Variables['SinglePhotonParked'].GetBinContent(10)
    
    legend.SetShadowColor(0);
    legend.SetFillColor(0);
    legend.SetLineColor(0);

    #legend.Draw("same")
    #if save.startswith('MT') or save.startswith('MET') or save.startswith('njets'):
    #    legend.Draw("same")
    
    latex2 = TLatex()
    latex2.SetNDC()
    latex2.SetTextSize(0.035)
    latex2.SetTextAlign(31) # align right
    latex2.DrawLatex(0.87, 0.95, "CMS Preliminary, "+lumi_str+" fb^{-1} at #sqrt{s} = 8 TeV");

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
        ratiosys.SetMaximum(1)
        ratiosys.SetMinimum(-1)
        ratiosys.GetXaxis().SetTitle(xlabel)
        ratiosys.GetYaxis().SetTitleSize(0.04)
        ratiosys.GetYaxis().SetTitle('Data-Bkg/Bkg.')
        ratiosys.GetYaxis().SetNdivisions(5)
        ratiosys.SetMarkerSize(0)
        ratiosys.Draw("e2")
        Ratio.SetMarkerStyle(20)
        Ratio.SetMarkerColor(1)
        Ratio.SetLineColor(1)
        Ratio.SetMarkerSize(0.8)
        Ratio.Draw("esame")

    if (drawRatio):
        c4.SaveAs('Tests_Ratio/StackedHisto_' + save + '.pdf')
    if (drawPull):
        c4.SaveAs('Nvtx_Tests_Pull/StackedHisto_' + save + '.pdf')

    if save.startswith('Pho_Pt'):
        print "*******************************************************"
        print "bkg scaled to ",lumi,"/pb: " ,round(totalbkg,2) , " +/- ", sqrt(toterr**2)

        print "Data: ", Variables['SinglePhotonParked'].Integral(0,bin+1)
        print "Mchi 120: ", lumi,"/pb: ",round(Variables['MChi_120'].Integral(0,bin+1),2),"Significance: ",round(Variables['MChi_120'].Integral(0,bin+1)/sqrt(totalbkg),2)
        print "Mchi 70:  ", lumi,"/pb: " ,round(Variables['MChi_70'].Integral(0,bin+1),2), "Significance: ", round(Variables['MChi_70'].Integral(0,bin+1)/sqrt(totalbkg),2)
        print "Mchi 80:  ", lumi,"/pb: " ,round(Variables['MChi_80'].Integral(0,bin+1),2), "Significance: ", round(Variables['MChi_80'].Integral(0,bin+1)/sqrt(totalbkg),2)
        print "Mchi 90:  ", lumi,"/pb: " ,round(Variables['MChi_90'].Integral(0,bin+1),2), "Significance: ", round(Variables['MChi_90'].Integral(0,bin+1)/sqrt(totalbkg),2)
        print "Mchi 100:  ", lumi,"/pb: " ,round(Variables['MChi_100'].Integral(0,bin+1),2), "Significance: ", round(Variables['MChi_100'].Integral(0,bin+1)/sqrt(totalbkg),2)


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


var = 'Pho_Pt'; bin = 20; low = 45; high = 545; xaxis = "Photon P_{T} [GeV]"; yaxis = 'Events / 25 GeV'; save = 'Pho_Pt'; setLog = True; finalcuts = False;channel = "VBF";
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'Met_corr'; bin = 20; low = 45; high = 545;xaxis= "PF ME_{T} Corrected [GeV]"; yaxis = 'Events / 20 GeV'; save = 'MET'; setLog = True; finalcuts = False;channel = "VBF"
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'Phi_corr';  bin = 80; low = -4; high = 4; xaxis = "MET Phi"; yaxis = 'Events / 5 GeV'; save = 'MPhi'; setLog = False; finalcuts = False;channel = "VBF";
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)


var='MT_new';bin = 50; low =0; high = 250; xaxis = "Transverse Mass Corrected [GeV]"; yaxis = 'Events / 10 GeV'; save = 'MT'; setLog = True; finalcuts = False;channel = "VBF"
#var='MT_new';bin = 100; low =0; high = 500; xaxis = "Transverse Mass Corrected [GeV]"; yaxis = 'Events / 10 GeV'; save = 'MT'; setLog = True; finalcuts = False;channel = "VBF"
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

#var = 'NVtx'; bin = 25; low = 0; high = 50; xaxis= "NVtx";  yaxis = 'Events'; save ='NVtx'; setLog= True; finalcuts = False; channel = "VBF";
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

#var = 'n_jets_mva_loose'; bin = 10; low =0; high = 10; xaxis = "# of Jets"; yaxis = 'Events'; save ='njets'; setLog = True; finalcuts = False; channel = "VBF";
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'minMET'; bin = 10; low = 0; high = 500; xaxis = "Min ME_{T} [GeV]"; yaxis = 'Events / 50 GeV'; save = 'minMET'; setLog = True; finalcuts = False;channel = "VBF"
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'TMath::Abs(log10(pvalue))'; bin = 20; low = 0; high = 10; xaxis = "p_{value}"; yaxis = 'Events'; save = 'pvalue'; setLog = True; finalcuts = False; channel = "VBF"
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'MetSig'; bin = 20; low = 0; high = 100; xaxis = "PF ME_{T} Significance"; yaxis='Events'; save = 'pfmet_significance'; setLog = True; finalcuts = False;channel = "VBF"
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'dphi_jet_pho'; bin = 50; low =0; high = 3.5; xaxis = "dPhi(Pho,Jet)"; yaxis = 'Events'; save ='dphiphojet'; setLog = True; finalcuts = False; channel = "VBF";
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'jet_pt'; bin = 20; low = 45; high = 545; xaxis = "Jet P_{T} [GeV]"; yaxis = 'Events / 20 GeV'; save = 'Jet_Pt'; setLog = True; finalcuts = False;channel = "VBF";
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'dP(phomet)'; bin = 50; low =0; high = 3.5; xaxis = "dPhi(Met,Gamma)"; yaxis = 'Events'; save ='dphimetgamma'; setLog = True; finalcuts = False; channel = "VBF";
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'Pho_Phi';  bin = 80; low = -4; high = 4; xaxis = "Photon Phi"; yaxis = 'Events / .1 '; save = 'Pho_Phi'; setLog = False; finalcuts = False;channel = "VBF";
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)


var = 'Phi_old';  bin = 80; low = -4; high = 4; xaxis = "MET Phi_old"; yaxis = 'Events / 5 GeV'; save = 'MPhi_old'; setLog = False; finalcuts = False;channel = "VBF";
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'MET_old'; bin = 100; low = 40; high = 540; xaxis = "PF ME_{T} Old [GeV]"; yaxis = 'Events / 20 GeV'; save = 'MET_old'; setLog = True; finalcuts = False;channel = "VBF"
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'MT_old'; bin = 100; low =0; high = 500; xaxis = "Transverse Mass [GeV]"; yaxis = 'Events / 10 GeV'; save = 'MT_old'; setLog = True; finalcuts = False;channel = "VBF"
#plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)

var = 'TMath::Sqrt(sigmaIPhiIPhi)'; bin = 200; low=0.006; high = 0.01; xaxis="sigmaiphiiphi"; yaxis = 'Events'; save = "iphi"; setLog = True; finalcuts = False;channel = "VBF";
plot_nice1D(channel,var, bin, low, high, yaxis, xaxis , save, setLog, finalcuts)


#########################################################################################################################################################################

