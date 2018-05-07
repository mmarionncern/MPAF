#!/bin/bash

source /mnt/t3nfs01/data01/swshare/ROOT/root_v5.34.18_slc6_amd64/bin/thisroot.sh

MPAFPATH=$1
cd $MPAFPATH
source setup.sh
cd display
root -b -l cards/tmpFiles/$2