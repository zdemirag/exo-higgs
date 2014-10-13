import ROOT, sys, os, string, re
from ROOT import *
from array import array
import math
from math import *
import ast

from tdrStyle import *
setTDRStyle()

from LoadData import *

def plot(List,channel,switch):

    ROOT.gSystem.AddIncludePath("-I$CMSSW_BASE/src/ ");
    ROOT.gSystem.AddIncludePath("-I$ROOFITSYS/include");

    ROOT.gSystem.Load("libRooFit.so")
    ROOT.gSystem.Load("libRooFitCore.so")
    ROOT.gROOT.SetStyle("Plain")
    ROOT.gROOT.ProcessLineSync(".x RooDoubleSidedCB.cxx+")

    var = 'ST_after'               

    print ''
    print '=========================================='


    lumi2012 = 7369.0/20


    MEx = RooRealVar("MEx", "MEx", -10000.0, 10000.0)
    MEy = RooRealVar("MEy", "MEy", -10000.0, 10000.0)
    Pho_Pt = RooRealVar("Pho_Pt", "Pho_Pt", -10000.0, 10000.0)
    Pho_Px = RooRealVar("Pho_Px", "Pho_Px", -10000.0, 10000.0)
    Pho_Py = RooRealVar("Pho_Py", "Pho_Py", -10000.0, 10000.0)
    HX = RooRealVar("HX", "HX", -10000.0, 10000.0)
    HY = RooRealVar("HY", "HY", -10000.0, 10000.0)
    ST_after = RooRealVar("ST_after", "ST_after", -10000.0, 10000.0)

    if switch == 'x':
        my_variable = RooFormulaVar("my_variable","(MEx)",RooArgList(MEx))

    else:
        my_variable = RooFormulaVar("my_variable","(MEy)",RooArgList(MEy))

    #my_variable = RooFormulaVar("my_variable","-(MEx + Pho_Px + HX)",RooArgList(MEx,Pho_Px,HX))
    #my_variable = RooFormulaVar("my_variable","-(MEy + Pho_Py + HY)",RooArgList(MEy,Pho_Py,HY))

    
    puWeight = RooRealVar("MyWeightData_new", "MyWeightData_new", 0.0, 10.0)

    sf_photon = "((0.99 * 0.97 * (Pho_Pt>40 && Pho_Pt<50)) +  (0.99 * 1.01 * (Pho_Pt>=50) ) )"
    trig_pho  = "((0.5*0.892*(1+TMath::Erf( (Pho_Pt  + 36.8) / (43.8*sqrt(2))))) * (Pho_Pt  >30.) )"
	

    dataset_all = RooDataSet()


    i_sample = -1
    for Sample in List:
        i_sample+=1

        recoweight = "( MyWeightData_new * "+sf_photon+"*"+trig_pho+")"

        print 'Defining RooDataSet for ',Sample        
        print "Trees Passed Entries: ",Trees[Sample].GetEntriesFast()

        dataset  = RooDataSet("dataset","dataset", Trees[Sample], RooArgSet(ST_after,Pho_Pt,puWeight,MEx,MEy,Pho_Px,Pho_Py,HX,HY))
        

        print "*******",Sample, " ", Nevents[Sample], " ", xsec[Sample]

        sampleweight = "("+str(lumi2012)+"/"+ str(Nevents[Sample]) +"*"+ str(xsec[Sample])+")"
        wFunc = RooFormulaVar("w","event weight","("+recoweight+"*"+str(sampleweight)+")",RooArgList(Pho_Pt,puWeight))
        #wFunc = RooFormulaVar("w","event weight","(1.0)",RooArgList(Pho_Pt,puWeight))
        w = dataset.addColumn(wFunc)
        

        if (i_sample == 0):
            dataset_all = RooDataSet("dataset_all","datset_all",dataset,dataset.get(),"",w.GetName())
            print 'Combined dataset',dataset_all.Print()
        else: 
            wdataset = RooDataSet(dataset.GetName(),dataset.GetTitle(),dataset,dataset.get(),"",w.GetName())
            print 'wdataset',wdataset.Print()
            dataset_all.append(wdataset)
            del wdataset

        print 'Combined Dataset',dataset_all.Print()
        del dataset
        
    VAR = dataset_all.addColumn(my_variable)
    #UX = dataset_all.addColumn(Ux)
    #UY = dataset_all.addColumn(Uy)

    print "Combined RooDataSet: ",dataset_all.Print()
    

    bins=[0,100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,3000]
    value={}
    error={}
    rms={}

    for i in range(len(bins)-1):

        save = 'STPrime_'+str(bins[i])+'to'+str(bins[i+1])
        cutST_after = "(ST_after>"+str(bins[i])+" && ST_after<"+str(bins[i+1])+")"

        # Parameters
        mass  = RooRealVar("mass","mass",0,-100,100) 
        sigma = RooRealVar("sigma","sigma",10,0,100) 
        width = RooRealVar("width","width",20,0,50)
        #width = RooRealVar("width","width",28,26,30) 


        print cutST_after
        reduced = dataset_all.reduce(cutST_after)

        c = TCanvas("c","c",700,700)
        
        signal = ROOT.RooVoigtian("v","v",VAR,mass,width,sigma);
        xframe = VAR.frame(-150,150)
        signal.fitTo(reduced,RooFit.Save(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Range(-2*reduced.sigma(VAR),2*reduced.sigma(VAR)),RooFit.PrintLevel(-1) )
        
        reduced.plotOn(xframe);
        signal.plotOn(xframe);

        result = signal.fitTo(reduced,RooFit.Save(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Range(-2*reduced.sigma(VAR),2*reduced.sigma(VAR)) ,RooFit.PrintLevel(-1) )
        
        Vsg = result.correlation(sigma,width)
        Vgs = result.correlation(width,sigma)
        Vss = result.correlation(sigma,sigma)
        Vgg = result.correlation(width,width)

        f_g = 2*sigma.getVal()*sqrt(2*log(2))
        f_l = 2*width.getVal()

        value[i] = 0.5346*f_l+sqrt(0.2166*f_l*f_l + f_g*f_g)

        ef_g = 2*sigma.getError()*sqrt(2*log(2))
        ef_l = 2*width.getError()
        p1 = ef_l*ef_l*Vgg
        p2 = ef_g*ef_l*Vsg
        p3 = ef_g*ef_l*Vgs;
        p4 = ef_g*ef_g*Vss;

        error[i]  = sqrt(p1+p2+p3+p4)
        ###
        
        argset_fit = ROOT.RooArgSet(mass,sigma,width)
        signal.paramOn(xframe,RooFit.Parameters(argset_fit),RooFit.Format("NE",RooFit.AutoPrecision(1)),RooFit.Layout(0.57,0.90,0.90))

        reduced.statOn(xframe,RooFit.Format("NE",RooFit.AutoPrecision(1)),RooFit.Layout(0.1,0.45,0.90)) ;

        chi2_text = TPaveText(0.1273408,0.5485893,0.3277154,0.6489028,"BRNDC")
        chi2_text.AddText("#chi^{2} fit = %s" %round(xframe.chiSquare(6),2))
        chi2_text.SetTextSize(0.04)
        chi2_text.SetTextColor(2)
        chi2_text.SetShadowColor(0)
        chi2_text.SetFillColor(0)
        chi2_text.SetLineColor(0)
        xframe.addObject(chi2_text)
        
        xframe.GetYaxis().SetTitleOffset(1.20) ;        
        xframe.GetXaxis().SetTitle("ME_{"+switch+"}")
        xframe.SetTitle(cutST_after)
        #xframe.SetTitle("")
        xframe.Draw();

        rms[i] = reduced.sigma(VAR)
        
        c.SaveAs(channel+"_Fits_E"+switch+"/Fits_"+save+".root")
        c.SaveAs(channel+"_Fits_E"+switch+"/Fits_"+save+".pdf")
        c.SaveAs(channel+"_Fits_E"+switch+"/Fits_"+save+".C")


    print "Sigma"
    for j in range(len(bins)-1):
        print bins[j], " to " , bins[j+1]
        print value[j]/2.3548, " +/- ", error[j]/2.3548
        print rms[j]
        print " "

#ListMC = ['WGamma']

ListMC = [ 'DiPhotonJets','DiphotonBox_Pt_25to250','DiphotonBox_Pt_250toInf','WtoLNuMu','WtoLNuTau','WGamma','ZGToLLG','ZGamma_Inclusive','GJets_HT_40To100','GJets_HT_100To200','GJets_HT_200To400','GJets_HT_400']

ListData = ['SinglePhotonParked']

#plot(ListData,'Data','x')
#plot(ListData,'Data','y')

#plot(ListMC,'MC','x')
plot(ListMC,'MC','y')

