#!/bin/bash

qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/FakeRatio/FakeRatio2015Bmu.out -e $MPAF/workdir/logs/FakeRatio/FakeRatio2015Bmu.err $MPAF/scripts/submit.sh $MPAF/cfg/FakeRatio2015Bmu.cfg
qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/FakeRatio/FakeRatio2015Bel.out -e $MPAF/workdir/logs/FakeRatio/FakeRatio2015Bel.err $MPAF/scripts/submit.sh $MPAF/cfg/FakeRatio2015Bel.cfg

