#!/bin/bash

cd /afs/cern.ch/user/m/mmarionn/workspace/private/cmssw/cmg944slc6/src
eval `scramv1 runtime -sh`

cd /afs/cern.ch/user/m/mmarionn/workspace/private/MPAF/
source setup.sh

analysis -c $1 -d $2
