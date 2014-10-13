from ROOT import *
from array import array
import math
from math import *

from tdrStyle import *
setTDRStyle()

lumiPlot = 7.3

def PlotLimits():

    mass = array('d', [70,80,90,100])
    masserr = array('d', [0,0])

    mass_str = ['70','80','90','100']
    
    exp   =array('d',[0 for i in range(len(mass))])
    experr=array('d',[0 for i in range(len(mass))])
    obs   =array('d',[0 for i in range(len(mass))])
    obserr=array('d',[0 for i in range(len(mass))]) 
    exp68H=array('d',[0 for i in range(len(mass))])
    exp68L=array('d',[0 for i in range(len(mass))])
    exp95H=array('d',[0 for i in range(len(mass))])
    exp95L=array('d',[0 for i in range(len(mass))])

    #xsec = [1.090253,0.820263,0.544212,0.303971]
    

    for i in range(len(mass)):
        RootFile = TFile('higgsCombineTest.Asymptotic.m_MChi_'+mass_str[i]+'.root')
        MyTree = RootFile.Get('limit')
        Nevents = MyTree.GetEntriesFast()
        for entry in xrange(Nevents):
            MyTree.GetEntry(entry)
            if MyTree.quantileExpected == -1:
                obs[i]= MyTree.limit # * xsec[i]
                obserr[i]= 0
            if MyTree.quantileExpected >0.49 and MyTree.quantileExpected <0.51:
                exp[i]= MyTree.limit #* xsec[i]
                experr[i]=0
            if MyTree.quantileExpected >0.15 and MyTree.quantileExpected <0.17:
                exp68L[i]=MyTree.limit #  * xsec[i]
            if MyTree.quantileExpected >0.83 and MyTree.quantileExpected <0.85:
                exp68H[i]=MyTree.limit # * xsec[i]
            if MyTree.quantileExpected >0.024 and MyTree.quantileExpected <0.026:
                exp95L[i]=MyTree.limit # * xsec[i]
            if MyTree.quantileExpected >0.974 and MyTree.quantileExpected <0.976:
                exp95H[i]=MyTree.limit # * xsec[i]

    print exp, obs

    massv = TVectorD(len(mass),mass)
    expv = TVectorD(len(mass),exp)
    exp68Hv = TVectorD(len(mass),exp68H)
    exp68Lv = TVectorD(len(mass),exp68L)
    exp95Hv = TVectorD(len(mass),exp95H)
    exp95Lv = TVectorD(len(mass),exp95L)
    #exp95Lv = TVectorD(len(mass),exp68L)

    obsv = TVectorD(len(mass),obs)
    masserrv = TVectorD(len(mass),masserr)
    obserrv = TVectorD(len(mass),obserr)
    experrv = TVectorD(len(mass),experr)       


    observed = TGraphAsymmErrors(massv,obsv,masserrv,masserrv,obserrv,obserrv)
    observed.SetLineColor(ROOT.kBlack)
    observed.SetLineWidth(2)
    observed.SetMarkerStyle(20)
    expected = TGraphAsymmErrors(massv,expv,masserrv,masserrv,experrv,experrv)
    expected.SetLineColor(ROOT.kBlack)
    expected.SetLineWidth(2)
    expected.SetLineStyle(2)
    ## I'm confused, somehow this is the way that works
    expected68 = TGraphAsymmErrors(massv,expv,masserrv,masserrv,exp95Lv,exp68Hv)
    #expected68 = TGraphAsymmErrors(massv,expv,masserrv,masserrv,exp68Lv,exp68Hv)
    expected68.SetFillColor(ROOT.kGreen)
    expected95 = TGraphAsymmErrors(massv,expv,masserrv,masserrv,exp68Lv,exp95Hv)
    #expected95 = TGraphAsymmErrors(massv,expv,masserrv,masserrv,exp95Lv,exp95Hv)
    expected95.SetFillColor(ROOT.kYellow)

    c4 = TCanvas("c4","Limits", 1000, 800)

    c4.SetBottomMargin(0.15)
    c4.SetRightMargin(0.06)

    expected95.Draw("a3")
    #expected95.GetYaxis().SetRangeUser(0,50)
    expected95.GetXaxis().SetTitle("M_{#chi} [GeV]")
    expected95.GetYaxis().SetTitle("Signal Strength")
    expected68.Draw("3same")
    expected.Draw("csame")
    #observed.Draw("cpsame")
    #theory.Draw("csame")

    latex = TLatex()
    latex.SetNDC()
    latex.SetTextSize(0.04)
    latex.SetTextAlign(31) # align right
    latex.DrawLatex(0.45, 0.95, "CMS Preliminary");
    
    latex2 = TLatex()
    latex2.SetNDC()
    latex2.SetTextSize(0.04)
    latex2.SetTextAlign(31) # align right
    latex2.DrawLatex(0.87, 0.95, str(lumiPlot) + " fb^{-1} at #sqrt{s} = 8 TeV")

    latex4 = TLatex()
    latex4.SetNDC()
    latex4.SetTextSize(0.04)
    latex4.SetTextAlign(31) # align right
    #latex4.DrawLatex(0.80, 0.87, "e+jets N_{b tags} #geq 1 ");

    legend = TLegend(.2,.6,.5,.9)
    legend . AddEntry(observed , '95% CL observed', "lp")
    legend . AddEntry(expected , '95% CL expected', "l")
    legend . AddEntry(expected68 , '#pm 1#sigma expected', "f")
    legend . AddEntry(expected95 , '#pm 2#sigma expected', "f")

    legend.SetShadowColor(0);
    legend.SetFillColor(0);
    legend.SetLineColor(0);
    legend.Draw()

    c4.SaveAs('LimitPlot.root')
    c4.SaveAs('LimitPlot.pdf')
    c4.SaveAs('LimitPlot.png')

PlotLimits()
