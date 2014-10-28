from ROOT import *
from array import array
import math
from math import *

from tdrStyle import *
setTDRStyle()

import os

lumiPlot = 7.3

def PlotLimits(rootdir,metmin,metmax,mtmin,mtmax):

    #mass = array('d', [70,80,90,100,120])
    #masserr = array('d', [0,0])
    
    #mass_str = ['70','80','90','100','120']
    
    #exp   =array('d',[0 for i in range(len(mass))])
    #experr=array('d',[0 for i in range(len(mass))])
    #obs   =array('d',[0 for i in range(len(mass))])
    #obserr=array('d',[0 for i in range(len(mass))]) 
    #exp68H=array('d',[0 for i in range(len(mass))])
    #exp68L=array('d',[0 for i in range(len(mass))])
    #exp95H=array('d',[0 for i in range(len(mass))])
    #exp95L=array('d',[0 for i in range(len(mass))])

    exp   = [] 
    experr= []
    obs   = []
    obserr= []
    exp68H= []
    exp68L= []
    exp95H= []
    exp95L= []
    met = []
    mt = []

    files = [f for f in os.listdir(rootdir) if os.path.isfile(rootdir+'/'+f)]
    for f in files:

        #print f
        RootFile = TFile(rootdir+'/'+f)
        MyTree = RootFile.Get('limit') 
        Nevents = MyTree.GetEntriesFast() 

        name = f.split('.')
        metcut = str(name[2]).replace('MET_','')
        mtcut = str(name[3]).replace('MT_','')

        if (int(metcut)<metmin or int(metcut)>metmax or int(mtcut)<mtmin or int(mtcut)>mtmax): continue
        
        #print int(metcut),int(mtcut)
        met.append(int(metcut))
        mt.append(int(mtcut))

        for entry in xrange(Nevents):
            MyTree.GetEntry(entry)
            if MyTree.quantileExpected == -1:
                obs.append(MyTree.limit) # * xsec[i]
                obserr.append(0)
            if MyTree.quantileExpected >0.49 and MyTree.quantileExpected <0.51:
                exp.append(MyTree.limit) #* xsec[i]
                experr.append(0)
            if MyTree.quantileExpected >0.15 and MyTree.quantileExpected <0.17:
                exp68L.append(MyTree.limit) #  * xsec[i]
            if MyTree.quantileExpected >0.83 and MyTree.quantileExpected <0.85:
                exp68H.append(MyTree.limit) # * xsec[i]
            if MyTree.quantileExpected >0.024 and MyTree.quantileExpected <0.026:
                exp95L.append(MyTree.limit) # * xsec[i]
            if MyTree.quantileExpected >0.974 and MyTree.quantileExpected <0.976:
                exp95H.append(MyTree.limit) # * xsec[i]

    #print exp, obs
    #print met
    #print mt    

    metbinwidth = 1000
    for i in range(len(met)):
        for j in range (len(met)):
            if (abs(met[i]-met[j])<metbinwidth and abs(met[i]-met[j])>0): metbinwidth=abs(met[i]-met[j])

    mtbinwidth = 1000
    for i in range(len(mt)):
        for j in range (len(mt)):
           if (abs(mt[i]-mt[j])<mtbinwidth and abs(mt[i]-mt[j])>0): mtbinwidth=abs(mt[i]-mt[j])

    

    
    nbins_met = (max(met)-min(met))/metbinwidth
    nbins_mt = (max(mt)-min(mt))/mtbinwidth

    fixmt=min(mt)
    while (fixmt<=max(mt)):

        metcut_fixmt = [0,1000]
        exp_fixmt    = [0,1000]
        exp68L_fixmt = [0,1000]
        exp68H_fixmt = [0,1000]
        exp95L_fixmt = [0,1000]
        exp95H_fixmt = [0,1000]
        obs_fixmt    = [0,1000]
        
        for i in range(len(mt)):

            if (mt[i]!=fixmt): continue

            for j in range(len(metcut_fixmt)):
                if (met[i]>metcut_fixmt[j] and met[i]<metcut_fixmt[j+1]):
                    metcut_fixmt.insert(j+1,met[i])
                    exp_fixmt.insert(j+1,exp[i])
                    exp68L_fixmt.insert(j+1,abs(exp68L[i]-exp[i]))
                    exp68H_fixmt.insert(j+1,abs(exp68H[i]-exp[i]))
                    exp95L_fixmt.insert(j+1,abs(exp95L[i]-exp[i]))
                    exp95H_fixmt.insert(j+1,abs(exp95H[i]-exp[i]))
                    obs_fixmt.insert(j+1,obs[i])
                    
        metcut_fixmt.pop(0)
        exp_fixmt.pop(0)
        exp68L_fixmt.pop(0)
        exp68H_fixmt.pop(0)
        exp95L_fixmt.pop(0)
        exp95H_fixmt.pop(0)
        obs_fixmt.pop(0)
        
        metcut_fixmt.pop()
        exp_fixmt.pop()
        exp68L_fixmt.pop()
        exp68H_fixmt.pop()
        exp95L_fixmt.pop()
        exp95H_fixmt.pop()
        obs_fixmt.pop()

        #print 'mt >',str(fixmt)
        #print 'met cut values: ',metcut_fixmt
        #print 'obs',obs_fixmt
        #print 'exp95L',exp95L_fixmt,'exp68L',exp68L_fixmt,'exp_fixmt',exp_fixmt,'exp68H',exp68H_fixmt,'exp95H',exp95H_fixmt

        a_metcut_fixmt    = array('d',[i+0.5 for i in range(len(metcut_fixmt))])  
        a_metcuterr_fixmt = array('d',[0.5 for i in range(len(metcut_fixmt))])        
        a_exp_fixmt       = array('d',[exp_fixmt[i] for i in range(len(exp_fixmt))])
        a_experr_fixmt    = array('d',[0 for i in range(len(exp_fixmt))])
        a_obs_fixmt       = array('d',[obs_fixmt[i] for i in range(len(obs_fixmt))])
        a_obserr_fixmt    = array('d',[0 for i in range(len(obs_fixmt))])
        a_exp68H_fixmt    = array('d',[exp68H_fixmt[i] for i in range(len(exp68H_fixmt))])
        a_exp68L_fixmt    = array('d',[exp68L_fixmt[i] for i in range(len(exp68L_fixmt))])
        a_exp95H_fixmt    = array('d',[exp95H_fixmt[i] for i in range(len(exp95H_fixmt))])
        a_exp95L_fixmt    = array('d',[exp95L_fixmt[i] for i in range(len(exp95L_fixmt))])    
        
        v_metcut_fixmt    = TVectorD(len(a_metcut_fixmt),a_metcut_fixmt)
        v_metcuterr_fixmt = TVectorD(len(a_metcuterr_fixmt),a_metcuterr_fixmt)
        v_exp_fixmt       = TVectorD(len(a_exp_fixmt),a_exp_fixmt)
        v_experr_fixmt    = TVectorD(len(a_experr_fixmt),a_experr_fixmt)
        v_exp68H_fixmt    = TVectorD(len(a_exp68H_fixmt),a_exp68H_fixmt)
        v_exp68L_fixmt    = TVectorD(len(a_exp68L_fixmt),a_exp68L_fixmt)
        v_exp95H_fixmt    = TVectorD(len(a_exp95H_fixmt),a_exp95H_fixmt)
        v_exp95L_fixmt    = TVectorD(len(a_exp95L_fixmt),a_exp95L_fixmt)
        v_obs_fixmt       = TVectorD(len(a_obs_fixmt),a_obs_fixmt)
        v_obserr_fixmt    = TVectorD(len(a_obserr_fixmt),a_obserr_fixmt)
        
        observed = TGraphAsymmErrors(v_metcut_fixmt,v_obs_fixmt,v_metcuterr_fixmt,v_metcuterr_fixmt,v_obserr_fixmt,v_obserr_fixmt)
        observed.SetLineColor(ROOT.kBlack)
        observed.SetLineWidth(2)
        observed.SetMarkerSize(0)
        expected = TGraphAsymmErrors(v_metcut_fixmt,v_exp_fixmt,v_metcuterr_fixmt,v_metcuterr_fixmt,v_experr_fixmt,v_experr_fixmt)
        expected.SetLineColor(ROOT.kBlack)
        expected.SetLineWidth(2)
        expected.SetLineStyle(2)
        expected68 = TGraphAsymmErrors(v_metcut_fixmt,v_exp_fixmt,v_metcuterr_fixmt,v_metcuterr_fixmt,v_exp68L_fixmt,v_exp68H_fixmt)
        expected68.SetFillColor(ROOT.kGreen)
        expected95 = TGraphAsymmErrors(v_metcut_fixmt,v_exp_fixmt,v_metcuterr_fixmt,v_metcuterr_fixmt,v_exp95L_fixmt,v_exp95H_fixmt)
        expected95.SetFillColor(ROOT.kYellow)        

        string_metcuts = TH1D("s","",len(v_metcut_fixmt),0,len(v_metcut_fixmt))
        for i in range(len(v_metcut_fixmt)):
            string_metcuts.SetBinContent(i+1,1.5*min(a_obs_fixmt))
            string_metcuts.GetXaxis().SetBinLabel(i+1,str(metcut_fixmt[i]))
        string_metcuts.SetLineColor(0) 
        string_metcuts.SetMarkerColor(0)
        string_metcuts.GetYaxis().SetTitle("Limit [fb]")
        string_metcuts.GetXaxis().SetTitle("Minimum MET")
        #string_metcuts.SetMinimum(0.8*min(exp68L_fixmt))
        #string_metcuts.SetMaximum(1.2*max(exp95H_fixmt))

        c = TCanvas("c","Limits", 1000, 800)        
        c.SetLogy()
        c.SetBottomMargin(0.15)
        c.SetRightMargin(0.06)

        string_metcuts.Draw("hist")
        string_metcuts.SetMaximum(10*max(exp))
        #string_metcuts.GetYaxis().SetRangeUser(0.8*min(exp95L_fixmt),1.2*max(exp95H_fixmt))
        expected95.Draw("2same")
        expected68.Draw("2same")
        expected.Draw("psame")
        #observed.Draw("psame")
        string_metcuts.Draw("axissame")
        
        #latex = TLatex()
        #latex.SetNDC()
        #latex.SetTextSize(0.04)
        #latex.SetTextAlign(31) # align right
        #latex.DrawLatex(0.45, 0.95, "CMS Preliminary");

        latex = TLatex()
        latex.SetNDC()
        latex.SetTextSize(0.75*c.GetTopMargin())
        latex.SetTextFont(62)
        latex.SetTextAlign(11) # align right
        latex.DrawLatex(0.22, 0.85, "CMS");
        latex.SetTextSize(0.5*c.GetTopMargin())
        latex.SetTextFont(52)
        latex.SetTextAlign(11)
        latex.DrawLatex(0.20, 0.8, "Preliminary");
        
                                         
        latex2 = TLatex()
        latex2.SetNDC()
        latex2.SetTextSize(0.04)
        latex2.SetTextAlign(31) # align right
        latex2.DrawLatex(0.87, 0.95, str(lumiPlot) + " fb^{-1} (8 TeV)");
    
        legend = TLegend(.7,.7,.9,.9,'MT>'+str(fixmt))
        legend . AddEntry(observed , '95% CL observed', "lp")
        legend . AddEntry(expected , '95% CL expected', "l")
        legend . AddEntry(expected68 , '#pm 1#sigma expected', "f")
        legend . AddEntry(expected95 , '#pm 2#sigma expected', "f")
        
        legend.SetShadowColor(0);
        legend.SetFillColor(0);
        legend.SetLineColor(0);
        legend.Draw()
        
        c.SaveAs('LimitPlotVsMET_MT'+str(fixmt)+'.root')
        c.SaveAs('LimitPlotVsMET_MT'+str(fixmt)+'.pdf')
        c.SaveAs('LimitPlotVsMET_MT'+str(fixmt)+'.png')
  
        del c
        del string_metcuts
        
        fixmt=fixmt+mtbinwidth 


    #copy the above section and replace the MET with MT (fixmt with fixmet)




        
    print "MET ",nbins_met," bins, ",min(met)-(metbinwidth/2),"-",max(met)+(metbinwidth/2)
    print "MT  ",nbins_mt," bins, ",min(mt)-(mtbinwidth/2),"-",max(mt)+(mtbinwidth/2)
    
    expected2D = TH2F("expected2D","MET vs MT", nbins_met,min(met)-(metbinwidth/2),max(met)+(metbinwidth/2),nbins_mt,min(mt)-(mtbinwidth/2), max(mt)+(mtbinwidth/2))
    for i in range(len(exp)):
        #print 'met:',met[i],'mt:',mt[i],'metbin:',expected2D.FindBin(met[i]),'mtbin:',expected2D.FindBin(mt[i])
        expected2D.SetBinContent(expected2D.FindBin(met[i],mt[i]),exp[i])

    observed2D = TH2F("observed2D","MET vs MT", nbins_met,min(met)-(metbinwidth/2),max(met)+(metbinwidth/2),nbins_mt,min(mt)-(mtbinwidth/2), max(mt)+(mtbinwidth/2))
    for i in range(len(obs)):
        #print 'met:',met[i],'mt:',mt[i],'metbin:',observed2D.FindBin(met[i]),'mtbin:',observed2D.FindBin(mt[i])
        observed2D.SetBinContent(observed2D.FindBin(met[i],mt[i]),obs[i])

    #contour_expected2D = expected2D.Clone("contour_expected2D")
    #contour_array = array('d',[25,20,15,10])
    #contour_expected2D.SetContour(len(contour_array), contour_array)

    c_exp = TCanvas("c_exp","2D Limits", 1000, 800)  
  
    c_exp.SetBottomMargin(0.15) 
    c_exp.SetRightMargin(0.2)  

    expected2D.Draw("colz")
    #contour_expected2D.Draw("cont3 list same")
    expected2D.GetXaxis().SetTitle("MET cut [GeV]") 
    expected2D.GetYaxis().SetTitle("MT cut [GeV]") 
    expected2D.GetZaxis().SetTitle("Expected Limit [fb]")  
    
    latex = TLatex()
    latex.SetNDC()
    latex.SetTextSize(0.75*c_exp.GetTopMargin())
    latex.SetTextFont(62)
    latex.SetTextAlign(11) # align right
    latex.DrawLatex(0.22, 0.85, "CMS");
    latex.SetTextSize(0.5*c_exp.GetTopMargin())
    latex.SetTextFont(52)
    latex.SetTextAlign(11)
    latex.DrawLatex(0.20, 0.8, "Preliminary");
    
    latex2 = TLatex() 
    latex2.SetNDC() 
    latex2.SetTextSize(0.04) 
    latex2.SetTextAlign(31) # align right 
    latex2.DrawLatex(0.87, 0.95, str(lumiPlot) + " fb^{-1} (8 TeV)") 

    c_exp.SaveAs('2DLimitPlot_expected_met'+str(metmin)+'to'+str(metmax)+'_mt'+str(mtmin)+'to'+str(mtmax)+'.root') 
    c_exp.SaveAs('2DLimitPlot_expected_met'+str(metmin)+'to'+str(metmax)+'_mt'+str(mtmin)+'to'+str(mtmax)+'.pdf')
    c_exp.SaveAs('2DLimitPlot_expected_met'+str(metmin)+'to'+str(metmax)+'_mt'+str(mtmin)+'to'+str(mtmax)+'.png')


    c_obs = TCanvas("c_obs","2D Limits", 1000, 800)    
    c_obs.SetBottomMargin(0.15)
    c_obs.SetRightMargin(0.2)
    
    observed2D.Draw("colz")
    #contour_observed2D.Draw("cont3 list same")
    observed2D.GetXaxis().SetTitle("MET cut [GeV]")
    observed2D.GetYaxis().SetTitle("MT cut [GeV]")
    observed2D.GetZaxis().SetTitle("Observed Limit [fb]")
    
    latex = TLatex()
    latex.SetNDC()
    latex.SetTextSize(0.04 )
    latex.SetTextAlign(31) # align right
    latex.DrawLatex(0.45, 0.95, "CMS Preliminary");
    
    latex2 = TLatex()
    latex2.SetNDC()
    latex2.SetTextSize(0.04)
    latex2.SetTextAlign(31) # align right
    latex2.DrawLatex(0.87, 0.95, str(lumiPlot) + " fb^{-1} at #sqrt{s} = 8 TeV")
    
    c_obs.SaveAs('2DLimitPlot_observed_met'+str(metmin)+'to'+str(metmax)+'_mt'+str(mtmin)+'to'+str(mtmax)+'.root')
    c_obs.SaveAs('2DLimitPlot_observed_met'+str(metmin)+'to'+str(metmax)+'_mt'+str(mtmin)+'to'+str(mtmax)+'.pdf')
    c_obs.SaveAs('2DLimitPlot_observed_met'+str(metmin)+'to'+str(metmax)+'_mt'+str(mtmin)+'to'+str(mtmax)+'.png')

    del c_exp
    del c_obs
    
PlotLimits('test_2d_script',65,1000,0,1000)
#PlotLimits('test_2d_script',100,1000,0,1000)
#PlotLimits('test_2d_script',99,101,99,101) 
#PlotLimits('test_2d_script',100,1000,100,1000) 

