#!/bin/bash

SIGS=(
T1tttt_mG_1500_mN_100
T1tttt_mG_1800_mN_100
T1tttt_mG_1500_mN_400
T1tttt_mG_1800_mN_400
T1tttt_mG_1500_mN_1000
T1tttt_mG_1800_mN_1000
T1tttt_mG_1500_mN_1200
T1tttt_mG_1600_mN_300
T5qqqqVV_noDM_mG_1200_mN_100
T5qqqqVV_noDM_mG_1500_mN_100
T5qqqqVV_noDM_mG_1200_mN_400
T5qqqqVV_noDM_mG_1500_mN_400
T5qqqqVV_noDM_mG_1200_mN_800
T5qqqqVV_noDM_mG_1500_mN_800
T5qqqqVV_noDM_mG_1200_mN_1000
T5qqqqVV_noDM_mG_1500_mN_1200
T1tttt_mG_1500_mN_1275
T5qqqqVV_noDM_mG_1500_mN_1375
)

TYPES=(
standard_V2
#combined
flavor_V2
charge_V2
)

cfg=ssdl2016LeptonIdCard.C #ssdl2016Plots.C #ssdl2016LeptonIdCard.C

for i in ${SIGS[@]}; do
    for t in ${TYPES[@]}; do
	cp cards/${cfg} cards/tmpFiles/ssdl2016LeptonIdCard.C
	sed -i 's|SIGNAL|'$i'|' cards/tmpFiles/ssdl2016LeptonIdCard.C
	sed -i 's|TYPE|'$t'|' cards/tmpFiles/ssdl2016LeptonIdCard.C

	root -l cards/tmpFiles/ssdl2016LeptonIdCard.C #> log${i}_${t}
    done
done