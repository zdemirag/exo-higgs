from ROOT import *
import os, sys, re

lumi = 1.0

######################################################

RootFiles = {}
Trees = {}
RootFilesSlim = {}
TreesSlim = {}

vars = ['ST_after','Pho_Pt','MyWeightData_new','MEx','MEy','Pho_Px','Pho_Py','HX','HY']
for var in vars:
        gROOT.ProcessLine(
                "struct "+var+"Struct {\
                Float_t   f"+var+";\
                };" );
        
from ROOT import ST_afterStruct
from ROOT import Pho_PtStruct
from ROOT import MyWeightData_newStruct
from ROOT import MExStruct
from ROOT import MEyStruct
from ROOT import Pho_PxStruct
from ROOT import Pho_PyStruct
from ROOT import HXStruct
from ROOT import HYStruct

outdir = "/data1/zdemirag/Exo_Higgs_Analyzer/CMSSW_5_3_9/src/macros/ResolutionStudies/NewReso_Unclustered/"

#higgsHistograms_SinglePhotonParked
Samples = ['higgsHistograms_WGamma','higgsHistograms_DiPhotonJets', 'higgsHistograms_DiphotonBox_Pt_250toInf', 'higgsHistograms_DiphotonBox_Pt_25to250', 'higgsHistograms_WtoLNuTau' , 'higgsHistograms_WtoLNuMu', 'higgsHistograms_ZGamma_Inclusive','higgsHistograms_GJets_HT_40To100','higgsHistograms_GJets_HT_100To200','higgsHistograms_GJets_HT_200To400','higgsHistograms_GJets_HT_400','higgsHistograms_ZGToLLG']

for bg in Samples:

        RootFiles[bg] = TFile(outdir+bg+".root")
        print bg

        Trees[bg]     = RootFiles[bg].Get("Analyzer/AnalyzerTree")
        ST_afterstruct = ST_afterStruct()
        Pho_Ptstruct = Pho_PtStruct()
        MyWeightData_newstruct = MyWeightData_newStruct()
        MExstruct = MExStruct()
        MEystruct = MEyStruct()
        Pho_Pxstruct = Pho_PxStruct()
        Pho_Pystruct = Pho_PyStruct()
        HXstruct = HXStruct()
        HYstruct = HYStruct()
        
        makeslimfile = True
        slimfileexists = False
        
        #if (os.path.isfile(outdir+'/slim/'+bg+'.root')):
        #        slimfileexists = True
        #        RootFilesSlim[bg] = TFile(outdir+'/slim/'+bg+'.root',"READ")
        #        TreesSlim[bg] = RootFilesSlim[bg].Get("treeslim");

        #elif (makeslimfile):
        if (makeslimfile):
                print "Making slim"
                RootFilesSlim[bg] = TFile(outdir+'/slim/'+bg+'.root',"RECREATE")
                TreesSlim[bg] = TTree("treeslim","treeslim");
	
                TreesSlim[bg].Branch( 'ST_after', ST_afterstruct, 'ST_after/F' )
                TreesSlim[bg].Branch( 'Pho_Pt', Pho_Ptstruct, 'Pho_Pt/F' )
                TreesSlim[bg].Branch( 'MyWeightData_new', MyWeightData_newstruct, 'MyWeightData_new/F' )
                TreesSlim[bg].Branch( 'MEx', MExstruct, 'MEx/F' )
                TreesSlim[bg].Branch( 'MEy', MEystruct, 'MEy/F' )
                TreesSlim[bg].Branch( 'Pho_Px', Pho_Pxstruct, 'Pho_Px/F' )
                TreesSlim[bg].Branch( 'Pho_Py', Pho_Pystruct, 'Pho_Py/F' )
                TreesSlim[bg].Branch( 'HX', HXstruct, 'HX/F' )
                TreesSlim[bg].Branch( 'HY', HYstruct, 'HY/F' )


        #nevents = Trees[bg].GetEntriesFast()
        #print nevents

        for entry in xrange(Trees[bg].GetEntriesFast()):
                Trees[bg].GetEntry(entry)
                ST_afterstruct.fST_after = Trees[bg].ST_after
                Pho_Ptstruct.fPho_Pt = Trees[bg].Pho_Pt
                MyWeightData_newstruct.fMyWeightData_new = Trees[bg].MyWeightData_new
                MExstruct.fMEx = Trees[bg].MEx
                MEystruct.fMEy = Trees[bg].MEy
                Pho_Pxstruct.fPho_Px = Trees[bg].Pho_Px
                Pho_Pystruct.fPho_Py = Trees[bg].Pho_Py
                HXstruct.fHX = Trees[bg].HX
                HYstruct.fHY = Trees[bg].HY
                
                TreesSlim[bg].Fill()
                
        RootFilesSlim[bg].Write()

######################################################

Nevents = {}

Nevents['DM'] = 84000#100000.

Nevents['MChi_70'] = 199079

Nevents['MChi_80'] = 191194
Nevents['MChi_90'] = 191633
Nevents['MChi_100'] = 198266

Nevents['GJets_HT_40To100'] = 19844808 #19857930
Nevents['GJets_HT_100To200'] = 9588849 #9612703
Nevents['GJets_HT_200To400'] = 58627147 #3020693
#Nevents['GJets_HT_200To400'] = 4262287 #3020693
Nevents['GJets_HT_400'] = 9539562#9453426 #1414007


#Nevents['GJets_HT_40To100'] = 19824979  #19844808 #19857930
#Nevents['GJets_HT_100To200'] = 9588849 #9588849 #9612703
#Nevents['GJets_HT_200To400'] = 58272731   #4262287 #3020693
#Nevents['GJets_HT_400'] = 9453426  #9453426 #1414007

Nevents['ZGamma_Inclusive']  = 3169111.0  #6.32155e+05#12076.
#Nevents['ZGamma_Inclusive']  = 1466144
#sushil's sample
#Nevents['ZGamma_Inclusive']  = 43401

Nevents['ZGToLLG'] = 6583032 #6588161

Nevents['MChi_120'] = 184388.

Nevents['Data_VBF_2012C']      = 1.0
Nevents['SinglePhotonParked']            = 1.0
Nevents['qcd_dd']         = 1.0
Nevents['efake_dd']         = 1.0

#Nevents['Signal_VBF']      = 98000.0
#Nevents['Signal_GluGlu']   = 98000.0

Nevents['WGamma']          = 5000000.0

Nevents['DiphotonBox_Pt_250toInf']     = 500352.0
Nevents['DiphotonBox_Pt_25to250'] = 500050.0


Nevents['PJets_15to30']     = 1970745.0
Nevents['PJets_30to50']     = 1993325.0
Nevents['PJets_50to80']     = 1995062.0
Nevents['PJets_80to120']    = 1992627.0
Nevents['PJets_120to170']   = 2000043.0
Nevents['PJets_170to300']   = 2000069.0
Nevents['PJets_300to470']   = 2000130.0
Nevents['PJets_470to800']   = 1975231.0
Nevents['PJets_800to1400']  = 1973504.0
Nevents['PJets_1400to1800'] = 1984890.0
Nevents['PJets_1800']       = 1939122.0


Nevents['DiPhotonJets']     = 1156284.0
Nevents['W2lnuEl']      = 4883504.0
Nevents['WtoLNuTau']     = 5000722.0
Nevents['WtoLNuMu']      = 4769214.0
Nevents['QCD_20to30']   = 35040638.0
Nevents['QCD_30to80']   = 33088822.0

#forgot to run on a file
Nevents['QCD_80to170']  = 22639900#34542672.0

# a file is missing fix the # of events
Nevents['QCD_170to250'] = 31646986.0

Nevents['QCD_250to350'] = 42292370.
Nevents['QCD_350'] = 34080630.


######################################################
xsec = {}

xsec['GJets_HT_40To100'] = 20930.0
xsec['GJets_HT_100To200'] = 5212.0
xsec['GJets_HT_200To400'] = 960.5
xsec['GJets_HT_400'] = 107.5


xsec['DM'] = 1.63721e-06

xsec['ZGamma_Inclusive'] = 123.9
#xsec['ZGamma_Inclusive'] = 93
#xsec['ZGamma_Inclusive'] = 34.316
xsec['ZGToLLG'] = 132.6

xsec['MChi_120'] = 0.017900
xsec['MChi_70'] = 1.090253
xsec['MChi_80'] = 0.820263
xsec['MChi_90'] = 0.544212
xsec['MChi_100'] = 0.303971

xsec['Data_VBF_2012C']            = 1.0
xsec['SinglePhotonParked']            = 1.0

xsec['qcd_dd']         = 1.0
xsec['efake_dd']         = 1.0

#Glu : 19.27 pb * BR (1.55 E-03) * nunu (~%20)
#xsec['Signal_GluGlu']   = 5.9737E-03
#VBF : 1.578 pb  * BR (1.55 E-03) * nunu (~%20)
#xsec['Signal_VBF']      = 0.489E-03

xsec['WGamma']          =  461.6

##xsec['DiphotonBox_Pt_250toInf']     = 1.0
##xsec['DiphotonBox_Pt_25to250'] = 1.0

xsec['DiphotonBox_Pt_250toInf']     = 0.00032
xsec['DiphotonBox_Pt_25to250'] = 15.50



xsec['PJets_15to30']     =  200061.7 
xsec['PJets_30to50']     =  19931.62 
xsec['PJets_50to80']     =  3322.309 
xsec['PJets_80to120']    =  558.2865 
xsec['PJets_120to170']   =  108.0068 
xsec['PJets_170to300']   =  30.12207 
xsec['PJets_300to470']   =  2.138632 
xsec['PJets_470to800']   =  0.2119244 
xsec['PJets_800to1400']  =  0.007077847 
xsec['PJets_1400to1800'] =  4.510327E-5 
xsec['PJets_1800']       =  1.867141E-6 


xsec['DiPhotonJets']     = 1.0
xsec['W2lnuEl']      = 9170.0 
xsec['WtoLNuTau']     = 9170.0 
xsec['WtoLNuMu']      = 9170.0

# 2.886E8 *  0.0101 
xsec['QCD_20to30']   = 2.91486000000000000e+06
#  7.433E7 *  0.0621 
xsec['QCD_30to80']   = 4.61589300000000000e+06
# 1191000.0  *  0.1539 
xsec['QCD_80to170']  =  1.83294900000000023e+05
# 30990.0 *  0.148 
xsec['QCD_170to250'] =  4.58651999999999953e+03
#4250.0* 0.131
xsec['QCD_250to350'] = 556.75
#810.0 *0.11
xsec['QCD_350'] =  89.1
