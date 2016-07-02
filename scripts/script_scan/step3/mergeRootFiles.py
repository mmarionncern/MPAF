import glob
import os

command = "hadd /mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/merged_2fb_Bkg.root "
arr = glob.glob("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg*")

for i in range(len(arr)):
    command += arr[i]
    command += " " 

os.system(command)




