from ROOT import *
from array import *

from tdrStyle import *
setTDRStyle()
ROOT.gStyle.SetOptFit(0)

for axis in ['ex','ey']:
    for pm in ['final']:
        for width in ['sigma','rms']:

            xbins = []
            sigma = []
            dsigma = []

            xbins_data = []
            sigma_data = []
            dsigma_data = []

            f = open('mc_log_'+axis+'_'+pm,'r')
            lines = f.readlines()
            afterfirstline = False 
            for line in range(len(lines)-1):
                if (not ('  to  ' in lines[line])): continue
                bins =  lines[line].split('  ')
                if (float(bins[0])<10.0): continue
                if (float(lines[line+1].split('  ')[2].rstrip('\n'))/float(lines[line+1].split('  ')[0])>0.5): break
                if (float(bins[2].rstrip('\n'))>1801.0): break
                if (not afterfirstline): 
                    xbins.append(float(bins[0]))
                    xbins.append(float(bins[2].rstrip('\n')))
                else: xbins.append(float(bins[2].rstrip('\n')))
                afterfirstline = True
                if (width=='sigma'):
                    sigma.append(float(lines[line+1].split('  ')[0]))
                    dsigma.append(float(lines[line+1].split('  ')[2].rstrip('\n')))
                if (width=='rms'):
                    sigma.append(float(lines[line+2].rstrip('\n')))
                    dsigma.append(float(lines[line+1].split('  ')[2].rstrip('\n')))
            f.close()
            
            f = open('data_log_'+axis+'_'+pm,'r')  
            lines = f.readlines()
            afterfirstline = False 
            for line in range(len(lines)-1):
                if (not ('  to  ' in lines[line])): continue
                bins =  lines[line].split('  ')
                if (float(bins[0])<10.0): continue
                if (float(lines[line+1].split('  ')[2].rstrip('\n'))/float(lines[line+1].split('  ')[0])>0.5): break
                if (float(bins[2].rstrip('\n'))>1801.0): break
                if (not afterfirstline): 
                    xbins_data.append(float(bins[0]))
                    xbins_data.append(float(bins[2].rstrip('\n')))
                else: xbins_data.append(float(bins[2].rstrip('\n')))
                afterfirstline = True
                if (width=='sigma'):
                    sigma_data.append(float(lines[line+1].split('  ')[0]))
                    dsigma_data.append(float(lines[line+1].split('  ')[2].rstrip('\n')))
                if (width=='rms'):
                    sigma_data.append(float(lines[line+2].rstrip('\n')))
                    dsigma_data.append(float(lines[line+1].split('  ')[2].rstrip('\n')))
                    
            f.close()

            h_width_mc = TH1D("h_width_mc","h_width_mc",len(xbins)-1,array('d',xbins))
            for i in range(1,len(xbins)-1):
                h_width_mc.SetBinContent(i,sigma[i-1])
                h_width_mc.SetBinError(i,dsigma[i-1])
                
            h_width_data = TH1D("h_width_data","h_width_data",len(xbins_data)-1,array('d',xbins_data))
            for i in range(1,len(xbins_data)-1):
                h_width_data.SetBinContent(i,sigma_data[i-1])
                h_width_data.SetBinError(i,dsigma_data[i-1])
                
            fmc = TF1("fmc","[0]*sqrt(x)+[1]",xbins[0],xbins[len(xbins)-1]) 
            fdata = TF1("fdata","[0]*sqrt(x)+[1]",xbins_data[0],xbins[len(xbins_data)-1]) 

            c = TCanvas("c","c",1000,800)
            c.SetRightMargin(0.08)
            h_width_mc.GetXaxis().SetLabelSize(0.04)
            h_width_mc.GetXaxis().SetTitle('#SigmaE_{T}-#Sigmap_{T}^{vis.} [GeV]')
            if (axis=='ex'): h_width_mc.GetYaxis().SetTitle("#sigma(ME_{x}) [GeV]")
            if (axis=='ey'): h_width_mc.GetYaxis().SetTitle("#sigma(ME_{y}) [GeV]")
            h_width_mc.SetLineColor(4)
            h_width_mc.SetMarkerColor(4)
            fmc.SetLineColor(4)
            h_width_mc.SetMaximum(55)
            #h_width_mc.SetMaximum(1.5*max(sigma))
            h_width_mc.Draw("pe")
            h_width_mc.Fit(fmc,"N")
            fmc.Draw("same")
            latex2 = TLatex()
            latex2.SetNDC()
            latex2.SetTextFont(42)
            latex2.SetTextAlign(11)
            latex2.SetTextSize(0.5*c.GetTopMargin())
            if (axis=='ex'): latex2.DrawLatex(0.45,0.32,"#sigma(ME_{x})_{MC} = "+str(round(fmc.GetParameter(0),3))+" #sqrt{#SigmaE_{T}-#Sigmap_{T}^{vis}}+ ("+str(round(fmc.GetParameter(1),3))+")")
            if (axis=='ey'): latex2.DrawLatex(0.45,0.32,"#sigma(ME_{y})_{MC} = "+str(round(fmc.GetParameter(0),3))+" #sqrt{#SigmaE_{T}-#Sigmap_{T}^{vis}}+ ("+str(round(fmc.GetParameter(1),3))+")")
            fdata.SetLineColor(1)
            h_width_data.Draw("epsame")
            h_width_data.Fit(fdata,"N+")
            fdata.Draw("same")
            if (axis=='ex'): latex2.DrawLatex(0.45,0.24,"#sigma(ME_{x})_{Data} = "+str(round(fdata.GetParameter(0),3))+" #sqrt{#SigmaE_{T}-#Sigmap_{T}^{vis}}+ ("+str(round(fdata.GetParameter(1),3))+")")
            if (axis=='ey'): latex2.DrawLatex(0.45,0.24,"#sigma(ME_{y})_{Data} = "+str(round(fdata.GetParameter(0),3))+" #sqrt{#SigmaE_{T}-#Sigmap_{T}^{vis}}+ ("+str(round(fdata.GetParameter(1),3))+")")
            latex2.SetTextSize(0.5*c.GetTopMargin())
            latex2.SetTextFont(42)
            latex2.SetTextAlign(31) # align right                                       
            latex2.DrawLatex(0.87, 0.95,"0.37 fb^{-1} at #sqrt{s} = 8 TeV")
            latex2.SetTextSize(0.9*c.GetTopMargin())
            latex2.SetTextFont(62)
            latex2.SetTextAlign(11) # align right                                       
            latex2.DrawLatex(0.25, 0.85, "CMS")
            latex2.SetTextSize(0.7*c.GetTopMargin())
            latex2.SetTextFont(52)
            latex2.SetTextAlign(11)
            latex2.DrawLatex(0.23, 0.8, "Preliminary")
            legend = TLegend(0.23,.60,0.45,.70)
            legend.AddEntry(h_width_data, "Data", "l")
            legend.AddEntry(h_width_mc, "MC","l")
            legend.SetShadowColor(0);
            legend.SetFillColor(0);
            legend.SetLineColor(0);
            legend.Draw()
            c.SaveAs(axis+'_'+pm+'_'+width+'.pdf')
            
            

