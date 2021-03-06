{
//=========Macro generated from canvas: c/c
//=========  (Sun Oct 12 15:27:53 2014) by ROOT version5.32/00
   TCanvas *c = new TCanvas("c", "c",0,22,700,700);
   c->SetHighLightColor(2);
   c->Range(-187.5,-3.821513,187.5,24.20291);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   
   TH1D *frame_12598920__3 = new TH1D("frame_12598920__3","(ST_after>500 && ST_after<1000)",100,-150,150);
   frame_12598920__3->SetMinimum(-1.01907);
   frame_12598920__3->SetMaximum(21.40047);
   frame_12598920__3->SetDirectory(0);
   frame_12598920__3->SetStats(0);
   frame_12598920__3->GetXaxis()->SetTitle("U_{y}");
   frame_12598920__3->GetYaxis()->SetTitle("Events / ( 3 )");
   frame_12598920__3->GetYaxis()->SetTitleOffset(1.2);
   frame_12598920__3->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(100);
   grae->SetName("h_dataset_all");
   grae->SetTitle("Histogram of dataset_all_plot__Uy");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(8);
   grae->SetPoint(0,-148.5,0.06427239);
   grae->SetPointError(0,1.5,1.5,0.04548732,0.04548732);
   grae->SetPoint(1,-145.5,0.08837698);
   grae->SetPointError(1,1.5,1.5,0.05238821,0.05238821);
   grae->SetPoint(2,-142.5,0);
   grae->SetPointError(2,1.5,1.5,0,0);
   grae->SetPoint(3,-139.5,0.05492037);
   grae->SetPointError(3,1.5,1.5,0.03892227,0.03892227);
   grae->SetPoint(4,-136.5,0.1024282);
   grae->SetPointError(4,1.5,1.5,0.05940068,0.05940068);
   grae->SetPoint(5,-133.5,0.06538162);
   grae->SetPointError(5,1.5,1.5,0.04649287,0.04649287);
   grae->SetPoint(6,-130.5,0.09093598);
   grae->SetPointError(6,1.5,1.5,0.05263223,0.05263223);
   grae->SetPoint(7,-127.5,0.1747833);
   grae->SetPointError(7,1.5,1.5,0.0786582,0.0786582);
   grae->SetPoint(8,-124.5,0.1795578);
   grae->SetPointError(8,1.5,1.5,0.07540768,0.07540768);
   grae->SetPoint(9,-121.5,0.1254338);
   grae->SetPointError(9,1.5,1.5,0.06348909,0.06348909);
   grae->SetPoint(10,-118.5,0.1756957);
   grae->SetPointError(10,1.5,1.5,0.0747432,0.0747432);
   grae->SetPoint(11,-115.5,0.1278211);
   grae->SetPointError(11,1.5,1.5,0.0642477,0.0642477);
   grae->SetPoint(12,-112.5,0.05920766);
   grae->SetPointError(12,1.5,1.5,0.04229807,0.04229807);
   grae->SetPoint(13,-109.5,0.1195736);
   grae->SetPointError(13,1.5,1.5,0.05998603,0.05998603);
   grae->SetPoint(14,-106.5,0.2039112);
   grae->SetPointError(14,1.5,1.5,0.07895453,0.07895453);
   grae->SetPoint(15,-103.5,0.1501916);
   grae->SetPointError(15,1.5,1.5,0.075112,0.075112);
   grae->SetPoint(16,-100.5,0.202035);
   grae->SetPointError(16,1.5,1.5,0.07895598,0.07895598);
   grae->SetPoint(17,-97.5,0.3262053);
   grae->SetPointError(17,1.5,1.5,0.1043581,0.1043581);
   grae->SetPoint(18,-94.5,0.1874592);
   grae->SetPointError(18,1.5,1.5,0.07717302,0.07717302);
   grae->SetPoint(19,-91.5,0.2211502);
   grae->SetPointError(19,1.5,1.5,0.08567051,0.08567051);
   grae->SetPoint(20,-88.5,0.4884315);
   grae->SetPointError(20,1.5,1.5,0.1283881,0.1283881);
   grae->SetPoint(21,-85.5,0.7052982);
   grae->SetPointError(21,1.5,1.5,0.1556005,0.1556005);
   grae->SetPoint(22,-82.5,0.6370926);
   grae->SetPointError(22,1.5,1.5,0.1474283,0.1474283);
   grae->SetPoint(23,-79.5,0.3823845);
   grae->SetPointError(23,1.5,1.5,0.1119455,0.1119455);
   grae->SetPoint(24,-76.5,0.602126);
   grae->SetPointError(24,1.5,1.5,0.1463754,0.1463754);
   grae->SetPoint(25,-73.5,0.9833964);
   grae->SetPointError(25,1.5,1.5,0.1828832,0.1828832);
   grae->SetPoint(26,-70.5,0.9147615);
   grae->SetPointError(26,1.5,1.5,0.1751717,0.1751717);
   grae->SetPoint(27,-67.5,1.120494);
   grae->SetPointError(27,1.5,1.5,0.1914521,0.1914521);
   grae->SetPoint(28,-64.5,1.168942);
   grae->SetPointError(28,1.5,1.5,0.1986268,0.1986268);
   grae->SetPoint(29,-61.5,1.602448);
   grae->SetPointError(29,1.5,1.5,0.2287929,0.2287929);
   grae->SetPoint(30,-58.5,1.848793);
   grae->SetPointError(30,1.5,1.5,0.2462304,0.2462304);
   grae->SetPoint(31,-55.5,2.036221);
   grae->SetPointError(31,1.5,1.5,0.2605696,0.2605696);
   grae->SetPoint(32,-52.5,2.541203);
   grae->SetPointError(32,1.5,1.5,0.2866162,0.2866162);
   grae->SetPoint(33,-49.5,2.727554);
   grae->SetPointError(33,1.5,1.5,0.3008901,0.3008901);
   grae->SetPoint(34,-46.5,3.845853);
   grae->SetPointError(34,1.5,1.5,0.3637044,0.3637044);
   grae->SetPoint(35,-43.5,4.521722);
   grae->SetPointError(35,1.5,1.5,0.3909839,0.3909839);
   grae->SetPoint(36,-40.5,5.271991);
   grae->SetPointError(36,1.5,1.5,0.4167323,0.4167323);
   grae->SetPoint(37,-37.5,5.595696);
   grae->SetPointError(37,1.5,1.5,0.4365864,0.4365864);
   grae->SetPoint(38,-34.5,7.316494);
   grae->SetPointError(38,1.5,1.5,0.4968422,0.4968422);
   grae->SetPoint(39,-31.5,7.322419);
   grae->SetPointError(39,1.5,1.5,0.4962273,0.4962273);
   grae->SetPoint(40,-28.5,8.216095);
   grae->SetPointError(40,1.5,1.5,0.5207658,0.5207658);
   grae->SetPoint(41,-25.5,9.604108);
   grae->SetPointError(41,1.5,1.5,0.5706705,0.5706705);
   grae->SetPoint(42,-22.5,11.6577);
   grae->SetPointError(42,1.5,1.5,0.6216841,0.6216841);
   grae->SetPoint(43,-19.5,13.43898);
   grae->SetPointError(43,1.5,1.5,0.6678372,0.6678372);
   grae->SetPoint(44,-16.5,14.47244);
   grae->SetPointError(44,1.5,1.5,0.693532,0.693532);
   grae->SetPoint(45,-13.5,15.96337);
   grae->SetPointError(45,1.5,1.5,0.7273217,0.7273217);
   grae->SetPoint(46,-10.5,17.24732);
   grae->SetPointError(46,1.5,1.5,0.7567224,0.7567224);
   grae->SetPoint(47,-7.5,17.19582);
   grae->SetPointError(47,1.5,1.5,0.7559179,0.7559179);
   grae->SetPoint(48,-4.5,18.0493);
   grae->SetPointError(48,1.5,1.5,0.7779599,0.7779599);
   grae->SetPoint(49,-1.5,19.57632);
   grae->SetPointError(49,1.5,1.5,0.8050838,0.8050838);
   grae->SetPoint(50,1.5,18.05618);
   grae->SetPointError(50,1.5,1.5,0.7720533,0.7720533);
   grae->SetPoint(51,4.5,18.77876);
   grae->SetPointError(51,1.5,1.5,0.7886637,0.7886637);
   grae->SetPoint(52,7.5,18.2258);
   grae->SetPointError(52,1.5,1.5,0.775467,0.775467);
   grae->SetPoint(53,10.5,17.02469);
   grae->SetPointError(53,1.5,1.5,0.7508478,0.7508478);
   grae->SetPoint(54,13.5,14.78529);
   grae->SetPointError(54,1.5,1.5,0.7038544,0.7038544);
   grae->SetPoint(55,16.5,14.01635);
   grae->SetPointError(55,1.5,1.5,0.6817904,0.6817904);
   grae->SetPoint(56,19.5,13.1755);
   grae->SetPointError(56,1.5,1.5,0.6579945,0.6579945);
   grae->SetPoint(57,22.5,11.66188);
   grae->SetPointError(57,1.5,1.5,0.6266645,0.6266645);
   grae->SetPoint(58,25.5,9.687626);
   grae->SetPointError(58,1.5,1.5,0.5638111,0.5638111);
   grae->SetPoint(59,28.5,8.75786);
   grae->SetPointError(59,1.5,1.5,0.5398763,0.5398763);
   grae->SetPoint(60,31.5,8.479243);
   grae->SetPointError(60,1.5,1.5,0.5288027,0.5288027);
   grae->SetPoint(61,34.5,6.514854);
   grae->SetPointError(61,1.5,1.5,0.4637334,0.4637334);
   grae->SetPoint(62,37.5,5.370109);
   grae->SetPointError(62,1.5,1.5,0.4221081,0.4221081);
   grae->SetPoint(63,40.5,5.063918);
   grae->SetPointError(63,1.5,1.5,0.4104872,0.4104872);
   grae->SetPoint(64,43.5,4.270283);
   grae->SetPointError(64,1.5,1.5,0.378131,0.378131);
   grae->SetPoint(65,46.5,3.629172);
   grae->SetPointError(65,1.5,1.5,0.3438359,0.3438359);
   grae->SetPoint(66,49.5,2.834294);
   grae->SetPointError(66,1.5,1.5,0.3077769,0.3077769);
   grae->SetPoint(67,52.5,2.030432);
   grae->SetPointError(67,1.5,1.5,0.2586206,0.2586206);
   grae->SetPoint(68,55.5,1.784261);
   grae->SetPointError(68,1.5,1.5,0.2454818,0.2454818);
   grae->SetPoint(69,58.5,1.509651);
   grae->SetPointError(69,1.5,1.5,0.2249903,0.2249903);
   grae->SetPoint(70,61.5,1.71267);
   grae->SetPointError(70,1.5,1.5,0.2387071,0.2387071);
   grae->SetPoint(71,64.5,1.608398);
   grae->SetPointError(71,1.5,1.5,0.2348124,0.2348124);
   grae->SetPoint(72,67.5,0.8704954);
   grae->SetPointError(72,1.5,1.5,0.1676655,0.1676655);
   grae->SetPoint(73,70.5,0.9839586);
   grae->SetPointError(73,1.5,1.5,0.1781936,0.1781936);
   grae->SetPoint(74,73.5,0.6620749);
   grae->SetPointError(74,1.5,1.5,0.1490798,0.1490798);
   grae->SetPoint(75,76.5,0.5797707);
   grae->SetPointError(75,1.5,1.5,0.140538,0.140538);
   grae->SetPoint(76,79.5,0.6874473);
   grae->SetPointError(76,1.5,1.5,0.1549145,0.1549145);
   grae->SetPoint(77,82.5,0.5894461);
   grae->SetPointError(77,1.5,1.5,0.141921,0.141921);
   grae->SetPoint(78,85.5,0.397485);
   grae->SetPointError(78,1.5,1.5,0.1115529,0.1115529);
   grae->SetPoint(79,88.5,0.605747);
   grae->SetPointError(79,1.5,1.5,0.1421887,0.1421887);
   grae->SetPoint(80,91.5,0.1882278);
   grae->SetPointError(80,1.5,1.5,0.07934243,0.07934243);
   grae->SetPoint(81,94.5,0.464188);
   grae->SetPointError(81,1.5,1.5,0.1246631,0.1246631);
   grae->SetPoint(82,97.5,0.2367699);
   grae->SetPointError(82,1.5,1.5,0.09021882,0.09021882);
   grae->SetPoint(83,100.5,0.344151);
   grae->SetPointError(83,1.5,1.5,0.1093893,0.1093893);
   grae->SetPoint(84,103.5,0.1941206);
   grae->SetPointError(84,1.5,1.5,0.08518047,0.08518047);
   grae->SetPoint(85,106.5,0.1342207);
   grae->SetPointError(85,1.5,1.5,0.06760227,0.06760227);
   grae->SetPoint(86,109.5,0.2191634);
   grae->SetPointError(86,1.5,1.5,0.08294547,0.08294547);
   grae->SetPoint(87,112.5,0.07092065);
   grae->SetPointError(87,1.5,1.5,0.05037278,0.05037278);
   grae->SetPoint(88,115.5,0.1068157);
   grae->SetPointError(88,1.5,1.5,0.06211038,0.06211038);
   grae->SetPoint(89,118.5,0.03855495);
   grae->SetPointError(89,1.5,1.5,0.03855495,0.03855495);
   grae->SetPoint(90,121.5,0.02731159);
   grae->SetPointError(90,1.5,1.5,0.02731159,0.02731159);
   grae->SetPoint(91,124.5,0.06826604);
   grae->SetPointError(91,1.5,1.5,0.04835667,0.04835667);
   grae->SetPoint(92,127.5,0.03796543);
   grae->SetPointError(92,1.5,1.5,0.03796543,0.03796543);
   grae->SetPoint(93,130.5,0.1706226);
   grae->SetPointError(93,1.5,1.5,0.07681285,0.07681285);
   grae->SetPoint(94,133.5,0);
   grae->SetPointError(94,1.5,1.5,0,0);
   grae->SetPoint(95,136.5,0.1045196);
   grae->SetPointError(95,1.5,1.5,0.0609489,0.0609489);
   grae->SetPoint(96,139.5,0.03781854);
   grae->SetPointError(96,1.5,1.5,0.03781854,0.03781854);
   grae->SetPoint(97,142.5,0.02756053);
   grae->SetPointError(97,1.5,1.5,0.02756053,0.02756053);
   grae->SetPoint(98,145.5,0.1124034);
   grae->SetPointError(98,1.5,1.5,0.064908,0.064908);
   grae->SetPoint(99,148.5,0);
   grae->SetPointError(99,1.5,1.5,0,0);
   
   TH1F *Graph_h_dataset_all2 = new TH1F("Graph_h_dataset_all2","Histogram of dataset_all_plot__Uy",100,-180,180);
   Graph_h_dataset_all2->SetMinimum(-2.03814);
   Graph_h_dataset_all2->SetMaximum(22.41954);
   Graph_h_dataset_all2->SetDirectory(0);
   Graph_h_dataset_all2->SetStats(0);
   grae->SetHistogram(Graph_h_dataset_all2);
   
   grae->Draw("p");
   
   TGraph *graph = new TGraph(102);
   graph->SetName("v_Norm[Uy]_Range[fit_nll_v_dataset_all]_NormRange[fit_nll_v_dataset_all]");
   graph->SetTitle("Projection of v");
   graph->SetFillColor(1);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#0000ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(3);
   graph->SetPoint(0,-64.87060309,1.38405016);
   graph->SetPoint(1,-63.57319103,1.463193088);
   graph->SetPoint(2,-62.27577896,1.549253022);
   graph->SetPoint(3,-60.9783669,1.642916158);
   graph->SetPoint(4,-59.68095484,1.744924975);
   graph->SetPoint(5,-58.38354278,1.856078814);
   graph->SetPoint(6,-57.08613072,1.977233441);
   graph->SetPoint(7,-55.78871866,2.109299409);
   graph->SetPoint(8,-54.49130659,2.25323897);
   graph->SetPoint(9,-53.19389453,2.41006135);
   graph->SetPoint(10,-51.89648247,2.580816135);
   graph->SetPoint(11,-50.59907041,2.766584585);
   graph->SetPoint(12,-49.30165835,2.968468678);
   graph->SetPoint(13,-48.00424629,3.18757773);
   graph->SetPoint(14,-46.70683422,3.425012475);
   graph->SetPoint(15,-45.40942216,3.681846554);
   graph->SetPoint(16,-44.1120101,3.959105413);
   graph->SetPoint(17,-42.81459804,4.257742712);
   graph->SetPoint(18,-41.51718598,4.578614403);
   graph->SetPoint(19,-40.21977391,4.922450766);
   graph->SetPoint(20,-38.92236185,5.289826784);
   graph->SetPoint(21,-37.62494979,5.681131339);
   graph->SetPoint(22,-36.32753773,6.096535829);
   graph->SetPoint(23,-35.03012567,6.535962919);
   graph->SetPoint(24,-33.73271361,6.999056203);
   graph->SetPoint(25,-32.43530154,7.485151676);
   graph->SetPoint(26,-31.13788948,7.993251935);
   graph->SetPoint(27,-29.84047742,8.52200411);
   graph->SetPoint(28,-28.54306536,9.069682484);
   graph->SetPoint(29,-27.2456533,9.634176779);
   graph->SetPoint(30,-25.94824124,10.21298701);
   graph->SetPoint(31,-24.65082917,10.80322568);
   graph->SetPoint(32,-23.35341711,11.40162807);
   graph->SetPoint(33,-22.05600505,12.00457097);
   graph->SetPoint(34,-20.75859299,12.60810029);
   graph->SetPoint(35,-19.46118093,13.20796759);
   graph->SetPoint(36,-18.16376886,13.79967518);
   graph->SetPoint(37,-16.8663568,14.37852958);
   graph->SetPoint(38,-15.56894474,14.93970241);
   graph->SetPoint(39,-14.27153268,15.47829771);
   graph->SetPoint(40,-12.97412062,15.98942461);
   graph->SetPoint(41,-11.67670856,16.46827363);
   graph->SetPoint(42,-10.37929649,16.91019515);
   graph->SetPoint(43,-9.081884432,17.31077807);
   graph->SetPoint(44,-7.784472371,17.66592686);
   graph->SetPoint(45,-6.487060309,17.97193508);
   graph->SetPoint(46,-5.189648247,18.22555336);
   graph->SetPoint(47,-3.892236185,18.42405016);
   graph->SetPoint(48,-2.594824124,18.56526363);
   graph->SetPoint(49,-1.297412062,18.64764308);
   graph->SetPoint(50,0,18.67027907);
   graph->SetPoint(51,1.297412062,18.63292108);
   graph->SetPoint(52,2.594824124,18.53598242);
   graph->SetPoint(53,3.892236185,18.38053215);
   graph->SetPoint(54,5.189648247,18.16827429);
   graph->SetPoint(55,6.487060309,17.90151489);
   graph->SetPoint(56,7.784472371,17.58311783);
   graph->SetPoint(57,9.081884432,17.21645069);
   graph->SetPoint(58,10.37929649,16.805322);
   graph->SetPoint(59,11.67670856,16.35391178);
   graph->SetPoint(60,12.97412062,15.86669694);
   graph->SetPoint(61,14.27153268,15.34837367);
   graph->SetPoint(62,15.56894474,14.80377867);
   graph->SetPoint(63,16.8663568,14.23781101);
   graph->SetPoint(64,18.16376886,13.65535659);
   graph->SetPoint(65,19.46118093,13.06121669);
   graph->SetPoint(66,20.75859299,12.46004206);
   graph->SetPoint(67,22.05600505,11.85627381);
   graph->SetPoint(68,23.35341711,11.25409195);
   graph->SetPoint(69,24.65082917,10.65737234);
   graph->SetPoint(70,25.94824124,10.06965235);
   graph->SetPoint(71,27.2456533,9.49410547);
   graph->SetPoint(72,28.54306536,8.933524648);
   graph->SetPoint(73,29.84047742,8.390314066);
   graph->SetPoint(74,31.13788948,7.866488806);
   graph->SetPoint(75,32.43530154,7.363681694);
   graph->SetPoint(76,33.73271361,6.883156489);
   graph->SetPoint(77,35.03012567,6.425826504);
   graph->SetPoint(78,36.32753773,5.992277686);
   graph->SetPoint(79,37.62494979,5.582795172);
   graph->SetPoint(80,38.92236185,5.197392348);
   graph->SetPoint(81,40.21977391,4.835841487);
   graph->SetPoint(82,41.51718598,4.497705103);
   graph->SetPoint(83,42.81459804,4.182367255);
   graph->SetPoint(84,44.1120101,3.889064108);
   graph->SetPoint(85,45.40942216,3.616913196);
   graph->SetPoint(86,46.70683422,3.364940913);
   graph->SetPoint(87,48.00424629,3.132107883);
   graph->SetPoint(88,49.30165835,2.917331953);
   graph->SetPoint(89,50.59907041,2.719508669);
   graph->SetPoint(90,51.89648247,2.537529141);
   graph->SetPoint(91,53.19389453,2.370295336);
   graph->SetPoint(92,54.49130659,2.216732846);
   graph->SetPoint(93,55.78871866,2.075801278);
   graph->SetPoint(94,57.08613072,1.946502407);
   graph->SetPoint(95,58.38354278,1.827886306);
   graph->SetPoint(96,59.68095484,1.719055652);
   graph->SetPoint(97,60.9783669,1.619168436);
   graph->SetPoint(98,62.27577896,1.527439283);
   graph->SetPoint(99,63.57319103,1.443139626);
   graph->SetPoint(100,64.87060309,1.365596908);
   graph->SetPoint(101,64.87060309,1.365596908);
   
   TH1F *Graph_v_Norm[Uy]_Range[fit_nll_v_dataset_all]_NormRange[fit_nll_v_dataset_all]2 = new TH1F("Graph_v_Norm[Uy]_Range[fit_nll_v_dataset_all]_NormRange[fit_nll_v_dataset_all]2","Projection of v",102,-77.84472,77.84472);
   Graph_v_Norm[Uy]_Range[fit_nll_v_dataset_all]_NormRange[fit_nll_v_dataset_all]2->SetMinimum(0);
   Graph_v_Norm[Uy]_Range[fit_nll_v_dataset_all]_NormRange[fit_nll_v_dataset_all]2->SetMaximum(20.40075);
   Graph_v_Norm[Uy]_Range[fit_nll_v_dataset_all]_NormRange[fit_nll_v_dataset_all]2->SetDirectory(0);
   Graph_v_Norm[Uy]_Range[fit_nll_v_dataset_all]_NormRange[fit_nll_v_dataset_all]2->SetStats(0);
   graph->SetHistogram(Graph_v_Norm[Uy]_Range[fit_nll_v_dataset_all]_NormRange[fit_nll_v_dataset_all]2);
   
   graph->Draw("l");
   
   TPaveText *pt = new TPaveText(0.57,0.72,0.9,0.9,"BRNDC");
   pt->SetName("v_paramBox");
   pt->SetBorderSize(1);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.04);
   TText *text = pt->AddText("mass = -0.16 +/- 0.3");
   text = pt->AddText("sigma =  18 +/- 1");
   text = pt->AddText("width =  21 +/- 3");
   pt->Draw();
   
   pt = new TPaveText(0.1,0.72,0.45,0.9,"BRNDC");
   pt->SetName("dataset_all_statBox");
   pt->SetBorderSize(1);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.04);
   text = pt->AddText("RMS =  32 +/- 1");
   text = pt->AddText("Mean = -0.2 +/- 2");
   text = pt->AddText("Entries =  397.9");
   pt->Draw();
   
   pt = new TPaveText(0.1273408,0.5485893,0.3277154,0.6489028,"BRNDC");
   pt->SetFillColor(0);
   pt->SetLineColor(0);
   pt->SetTextColor(2);
   pt->SetTextSize(0.04);
   text = pt->AddText("#chi^{2} fit = 0.83");
   pt->Draw();
   
   TH1D *frame_12598920__4 = new TH1D("frame_12598920__4","(ST_after>500 && ST_after<1000)",100,-150,150);
   frame_12598920__4->SetMinimum(-1.01907);
   frame_12598920__4->SetMaximum(21.40047);
   frame_12598920__4->SetDirectory(0);
   frame_12598920__4->SetStats(0);
   frame_12598920__4->GetXaxis()->SetTitle("U_{y}");
   frame_12598920__4->GetYaxis()->SetTitle("Events / ( 3 )");
   frame_12598920__4->GetYaxis()->SetTitleOffset(1.2);
   frame_12598920__4->Draw("AXISSAME");
   
   pt = new TPaveText(0.01,0.9414286,0.71,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(1);
   pt->SetFillColor(0);
   text = pt->AddText("(ST_after>500 && ST_after<1000)");
   pt->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
