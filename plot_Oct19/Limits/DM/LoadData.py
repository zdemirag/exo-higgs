from ROOT import TFile

lumi = 1.0

######################################################

RootFiles = {}
Trees = {}

outdir = "/data1/zdemirag/Exo_Higgs_Analyzer/CMSSW_5_3_9/src/Oct14_NewReso_Root/met_pog_reso_x/higgsHistograms_"


#outdir = "/data1/zdemirag/Exo_Higgs_Analyzer/CMSSW_5_3_9/src/Jet30_NVtx/Jet_30_NVtx/higgsHistograms_"
#outdir = "/data1/zdemirag/Exo_Higgs_Analyzer/CMSSW_5_3_9/src/plotter_Aug17/root_Aug17/higgsHistograms_"

#Samples = ['efake_dd','SinglePhotonParked','PJets_15to30','PJets_30to50','PJets_50to80','PJets_80to120','PJets_120to170','PJets_170to300', 'PJets_300to470', 'PJets_470to800', 'PJets_800to1400', 'PJets_1400to1800','PJets_1800', 'WGamma','DiPhotonJets', 'DiphotonBox_Pt_250toInf', 'DiphotonBox_Pt_25to250', 'WtoLNuTau' , 'WtoLNuMu', 'qcd_dd', 'ZGamma_Inclusive','DM','GJets_HT_40_100','GJets_HT_100_200','GJets_HT_200_400','GJets_HT_400','MChi_70','MChi_120','ZGToLLG']

Samples = ['efake_dd','SinglePhotonParked', 'WGamma','DiPhotonJets', 'DiphotonBox_Pt_250toInf', 'DiphotonBox_Pt_25to250', 'WtoLNuTau' , 'WtoLNuMu', 'qcd_dd', 'ZGamma_Inclusive','GJets_HT_40To100','GJets_HT_100To200','GJets_HT_200To400','GJets_HT_400','MChi_70','MChi_120','MChi_80','MChi_90','MChi_100','ZGToLLG','DM','DM_AxialVector_10','DM_AxialVector_100','DM_AxialVector_1000','DM_AxialVector_200','DM_AxialVector_300','DM_AxialVector_500','DM_Vector_1','DM_Vector_10','DM_Vector_100','DM_Vector_1000','DM_Vector_300','DM_Vector_500']

for bg in Samples:
        RootFiles[bg] = TFile(outdir+bg+".root")
        Trees[bg]     = RootFiles[bg].Get("Analyzer/AnalyzerTree")


######################################################

Nevents = {}

Nevents['DM'] = 84000#100000.
Nevents['DM_AxialVector_1'] = 50000.
Nevents['DM_AxialVector_10'] = 50000.
Nevents['DM_AxialVector_100'] = 50000.
Nevents['DM_AxialVector_1000'] = 50000.
Nevents['DM_AxialVector_200'] = 50000.
Nevents['DM_AxialVector_300'] = 50000.
Nevents['DM_AxialVector_500'] = 50000.

Nevents['DM_Vector_1'] = 50000.
Nevents['DM_Vector_10'] = 50000.
Nevents['DM_Vector_100'] = 50000.
Nevents['DM_Vector_1000'] = 50000.
Nevents['DM_Vector_300'] = 50000.
Nevents['DM_Vector_500'] = 50000.


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



xsec['DM_AxialVector_1'] = 1.
xsec['DM_AxialVector_10'] = 0.001
xsec['DM_AxialVector_100'] = 1.
xsec['DM_AxialVector_1000'] = 1.
xsec['DM_AxialVector_200'] = 1.
xsec['DM_AxialVector_300'] = 1.
xsec['DM_AxialVector_500'] = 1.

xsec['DM_Vector_1'] = 1.
xsec['DM_Vector_10'] = 1.
xsec['DM_Vector_100'] = 1.
xsec['DM_Vector_1000'] = 1.
xsec['DM_Vector_300'] = 1.
xsec['DM_Vector_500'] = 1.


xsec['DM'] = 1.63721e-06

xsec['ZGamma_Inclusive'] = 123.9
#xsec['ZGamma_Inclusive'] = 93
#xsec['ZGamma_Inclusive'] = 34.316
xsec['ZGToLLG'] = 132.6

#xsec['MChi_70'] = 1.0
#xsec['MChi_80'] = 1.0
#xsec['MChi_90'] = 1.0
#xsec['MChi_100'] = 1.0
#xsec['MChi_120'] = 1.0

# SM higgs
xsec['MChi_70'] = 19.27
xsec['MChi_80'] = 19.27
xsec['MChi_90'] = 19.27
xsec['MChi_100'] = 19.27
xsec['MChi_120'] = 19.27

#Theory
#xsec['MChi_70'] = 1.090253
#xsec['MChi_80'] = 0.820263
#xsec['MChi_90'] = 0.544212
#xsec['MChi_100'] = 0.303971
#xsec['MChi_120'] = 0.017900

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
