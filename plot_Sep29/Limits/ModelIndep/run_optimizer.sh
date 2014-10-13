export METCUT=$1 
export MTCUT=$2

sed -e "s/METCUT/$METCUT/g" HZg_LimitHistos.py > HZg_LimitHistos_MET_$METCUT.py
sed -e "s/MTCUT/$MTCUT/g" HZg_LimitHistos_MET_$METCUT.py > HZg_LimitHistos_$MTCUT.py
python HZg_LimitHistos_$MTCUT.py
combine -M Asymptotic datacard_MET$1_MT$2.txt
rm HZg_LimitHistos_MET_$METCUT.py
rm HZg_LimitHistos_$MTCUT.py
mv higgsCombineTest.Asymptotic.mH120.root higgsCombineTest.Asymptotic.MET_$METCUT.MT_$MTCUT.root
