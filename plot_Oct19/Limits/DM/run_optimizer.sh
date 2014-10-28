export SUFFIX=$1
sed -e "s/SUFFIX/$SUFFIX/g" HZg_LimitHistos.py > HZg_LimitHistos_$SUFFIX.py
python HZg_LimitHistos_$SUFFIX.py
combine -M Asymptotic datacard_$1.txt --run blind
rm HZg_LimitHistos_$SUFFIX.py
mv higgsCombineTest.Asymptotic.mH120.root higgsCombineTest.Asymptotic.m_$SUFFIX.root
