#!/bin/bash

echo -e "\nCalling useRoofit.sh...\n\n"
echo -e "################################################"

for ((i=1;i<8;i++)) {
 if   [[ $i == 1 ]]; then
   lw=30;
   uv=40;
 elif [[ $i == 2 ]]; then
   lw=40;
   uv=50;
 elif [[ $i == 3 ]]; then
   lw=50;
   uv=60;
 elif [[ $i == 4 ]]; then
   lw=60;
   uv=70;
 elif [[ $i == 5 ]]; then
   lw=70;
   uv=80;
 elif [[ $i == 6 ]]; then
   lw=80;
   uv=100;
 elif [[ $i == 7 ]]; then
   lw=100;
   uv=130;
 else
   echo "-- WARNING! Check your for loop..."
 fi
 
 echo -e " Editting and executing RooFit for bin: ${i}, ${lw}<phoEt<${uv}"
 sed "s/NUMBER/${i}/g" RooFitTemplateFitExample.C > RooFitTemplateFitExample_tmp_${i}.C
 sed "s/LOWER/${lw}/g" RooFitTemplateFitExample_tmp_${i}.C > RooFitTemplateFitExample_tmp_${i}_${i}.C
 sed "s/UPPER/${uv}/g" RooFitTemplateFitExample_tmp_${i}_${i}.C > RooFitTemplateFitExample_tmp.C
 root -l -b -q RooFitTemplateFitExample_tmp.C > results_${i}.txt
 rm RooFitTemplateFitExample_tmp.C RooFitTemplateFitExample_tmp_${i}.C RooFitTemplateFitExample_tmp_${i}_${i}.C
}

bins=`cat results_* | grep "FAKE_RATE" | wc -l`
echo -e "\n OK, I have $bins files, with FR for each bin:"
cat results_* | grep "FAKE_RATE"
cat results_* | grep "FAKE_RATE" > FROutput.txt

echo -e "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo -e " Performing the final fit..."
root -l -b -q FINFIT.C > fitresults.txt
echo -e " OK, fitResult.png created."
echo -e "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

mkdir results
mkdir results/plots
mkdir results/logs
mv template_* results_* fitresults.txt fitResult.png  results/.
cp FROutput.txt results/.
mv results/*.p*  results/plots/.
mv results/*txt results/logs/.
#cp FROutput.txt forSystematics/.

echo -e "\n\n Done! Please find all template and final fit plots in ./results dir."
echo -e "\n################################################"
echo -e "\n\nuseRoofit.sh END.\n"



