import os

metcut = 60

while metcut<200:
    metcut += 5
    mtcut = 0
    while mtcut<200:
        os.system("bash run_optimizer.sh "+str(metcut)+" "+ str(mtcut) )
        mtcut += 5
