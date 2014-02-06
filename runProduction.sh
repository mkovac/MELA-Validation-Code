#!/bin/bash

#list="
#Graviton2PH2ToZZTo4L_M-125p6_8TeV-JHUGenV3_false
#Graviton2PH3ToZZTo4L_M-125p6_8TeV-JHUGenV3_false
#Graviton2PH6ToZZTo4L_M-125p6_8TeV-JHUGenV3_false
#Graviton2PH7ToZZTo4L_M-125p6_8TeV-JHUGenV3_false
#Graviton2MH10ToZZTo4L_M-125p6_8TeV-JHUGenV3_false
#Graviton2MH9ToZZTo4L_M-125p6_8TeV-JHUGenV3_false
#qqbar_Graviton2BPToZZTo4L_M-125p6_8TeV-JHUGenV3_false
#qqbar_Graviton2HMToZZTo4L_M-125p6_8TeV-JHUGenV3_false
#qqbar_Graviton2HPToZZTo4L_M-125p6_8TeV-JHUGenV3_false
#qqbar_Graviton2PH2ToZZTo4L_M-125p6_8TeV-JHUGenV3_false
#qqbar_Graviton2PH3ToZZTo4L_M-125p6_8TeV-JHUGenV3_false
#qqbar_Graviton2PH6ToZZTo4L_M-125p6_8TeV-JHUGenV3_false
#qqbar_Graviton2PH7ToZZTo4L_M-125p6_8TeV-JHUGenV3_false
#qqbar_Graviton2MH10ToZZTo4L_M-125p6_8TeV-JHUGenV3_false
#qqbar_Graviton2MH9ToZZTo4L_M-125p6_8TeV-JHUGenV3_false
#"

#HZZ4lTree_powheg15jhuGenV3H126
#HZZ4lTree_jhuGenV3Grav2MHH126
#HZZ4lTree_jhuGenV3qqGravH126
#HZZ4lTree_jhuGenV3Grav2PBH126
#HZZ4lTree_jhuGenV3Grav2PHH126
#HZZ4lTree_jhuGenV3GravPMH126

#Graviton2PH2ToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e2mu
#Graviton2PH3ToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e2mu
#Graviton2PH6ToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e2mu
#Graviton2PH7ToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e2mu
#Graviton2MH10ToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e2mu
#Graviton2MH9ToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e2mu
#qqbar_Graviton2BPToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e2mu
#qqbar_Graviton2HMToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e2mu
#qqbar_Graviton2HPToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e2mu
#qqbar_Graviton2PH2ToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e2mu
#qqbar_Graviton2PH3ToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e2mu
#qqbar_Graviton2PH6ToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e2mu
#qqbar_Graviton2PH7ToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e2mu
#qqbar_Graviton2MH10ToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e2mu
#qqbar_Graviton2MH9ToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e


#for i in `ls inputTrees/8TeV/2e2mu/`; do echo ${i/".root"/""}; done

outDir="/home/llr/cms/kovac/CMS/Analysis/SpinParity/Validation/CMSSW_5_3_9/src/ZZMatrixElement/MELA/test/Validation/outputTrees"

for i in `cat list/statTreesList.txt`;
do

fileName=`echo $i | awk -F all/ '{print $2}'`

# No Tuning
#out_2e2mu=${outDir}/8TeV/notTuned/Cuts/2e2mu/${fileName}
#out_4e=${outDir}/8TeV/notTuned/Cuts/4e/${fileName}
#out_4mu=${outDir}/8TeV/notTuned/Cuts/4mu/${fileName}

# Tuned
out_2e2mu=${outDir}/8TeV/Tuned/noCuts/2e2mu/${fileName}
out_4e=${outDir}/8TeV/Tuned/noCuts/4e/${fileName}
out_4mu=${outDir}/8TeV/Tuned/noCuts/4mu/${fileName}

# For generator level trees
#./run -limitStat -interactive -fileList $i -out ${out_2e2mu} -channel 2e2mu > log/${fileName}_2e2mu.txt &
#./run -limitStat -interactive -fileList $i -out ${out_4e}  -channel 4e  > log/${fileName}_4e.txt  &
#./run -limitStat -interactive -fileList $i -out ${out_4mu} -channel 4mu > log/${fileName}_4mu.txt &

# For statistical trees
./run -limitStat -interactive -fileList ${i/all/2e2mu} -out ${out_2e2mu} -channel 2e2mu > log/${fileName}_2e2mu.txt &
./run -limitStat -interactive -fileList ${i/all/4e}  -out ${out_4e}  -channel 4e  > log/${fileName}_4e.txt  &
./run -limitStat -interactive -fileList ${i/all/4mu} -out ${out_4mu} -channel 4mu > log/${fileName}_4mu.txt &

#echo ${i/all/2e2mu}

done