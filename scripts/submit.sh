#!/bin/bash
#source /mnt/t3nfs01/data01/swshare/ROOT/root_v5.34.18_slc6_amd64/bin/thisroot.sh

MPAFPATH=$1
. /swshare/psit3/etc/profile.d/cms_ui_env.sh
. /$VO_CMS_SW_DIR/cmsset_default.sh
export $SCRAM_ARCH=slc6_amd64_gcc491
cd /mnt/t3nfs01/data01/shome/mmarionn/cmssw/cmg8020/src
eval `scramv1 runtime -sh`
#cmsenv

cd $MPAFPATH #/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/
source setup.sh
mkdir -p /scratch/$USER/logs/

name=${2##*/}

analysis -c $2 # &> /scratch/$USER/logs/$name.out
#cp /scratch/$USER/logs/$name.out $MPAF/workdir/logs/SUSY3L/
#gfal-copy  file://///scratch/$USER/logs/$1.log  srm://t3se01.psi.ch/pnfs/psi.ch/cms/trivcat/store/user/jhoss/logs/$1.log
#rm /scratch/$USER/logs/$name.out



