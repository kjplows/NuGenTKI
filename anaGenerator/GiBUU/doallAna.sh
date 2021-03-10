export GFS0PIa9nuH="list/GiBUUMINERvA_ME_Neutrino_more_ensembles_FixedFlux_Hydrogen_100files.list"
#
#"list/GiBUUMINERvA_ME_Neutrino_more_ensembles_Hydrogen_100files.list"
#"list/GiBUUMINERvA_ME_Neutrino_NoFSI_H_100files.list"
#"list/GiBUUMINERvA_ME_Neutrino_more_ensembles_Hydrogen_250files.list"
#"list/GiBUUMINERvA_ME_Neutrino_more_ensembles_Hydrogen_500files.list"
#"list/GiBUUMINERvA_ME_Neutrino_more_ensembles_FixedFlux_Hydrogen_250files.list" #bugged
#
#"list/GiBUUMINERvA_LE_Neutrino_more_ensembles_Hydrogen_2000files.list"
#"list/GiBUUMINERvA_LE_Neutrino_more_ensembles_Hydrogen_250files.list"
#"list/GiBUUMINERvA_LE_Neutrino_more_ensembles_H_Hydrogen_1000files.list"

export GFS0PIa9nuC="list/GiBUUMINERvA_ME_Neutrino_more_ensembles_FixedFlux_Carbon_100files.list"
#"list/GiBUUMINERvA_ME_Neutrino_more_ensembles_Carbon_100files.list"
#"list/GiBUUMINERvA_ME_Neutrino_NoFSI_C_100files.list"
#"list/GiBUUMINERvA_ME_Antineutrino_buggedflux_Carbon_100files.list"
#"list/GiBUUMINERvA_ME_Neutrino_more_ensembles_Carbon_500files.list"
#"list/GiBUUMINERvA_ME_Neutrino_more_ensembles_FixedFlux_Carbon_250files.list" #bugged
#"list/GiBUUMINERvA_ME_Neutrino_more_ensembles_Carbon_250files.list"
#"list/GiBUUMINERvA_LE_Neutrino_more_ensembles_Carbon_250files.list"
#'list/Filelist_GiBUUMINERvALE_nu_T0_Carbon.list'

export GFS0PIa9nuNOFSIC=
#"list/GiBUUMINERvA_LE_Neutrino_NoFSI_Carbon_250files.list"

export GFSPIZEROa7nuH=${GFS0PIa9nuH}
export GFSPIZEROa7nuC=${GFS0PIa9nuC}
export GFSPIZEROa7nuNOFSIC=${GFS0PIa9nuNOFSIC}

export EXCL3a10nuH=
export EXCL3a10nubarH=
export EXCL3a10nuC=
export EXCL3a10nubarC=

export LOWRECOILa1nuC=""
export LOWRECOILa1nubarC=""
export LOWRECOILa1nuH=""
export LOWRECOILa1nubarH=""

export NUBAR1PIa2nubarC=""
export NUBAR1PIa2nubarH=""

export MMECCQEa4nuC=""

export GFSa0nuH=${GFS0PIa9nuH}
#"list/GiBUUMINERvA_ME_Neutrino_more_ensembles_FixedFlux_Hydrogen_100files.list"
#"list/GiBUUMINERvA_ME_Antineutrino_buggedflux_Hydrogen_100files.list"
#"list/GiBUUMINERvA_ME_Antineutrino_NoFSI_H_100files.list"
#
export GFSa3nuC=""
export GFSa0nuC=${GFS0PIa9nuC}
#"list/GiBUUMINERvA_ME_Neutrino_more_ensembles_FixedFlux_Carbon_100files.list"
#"list/GiBUUMINERvA_ME_Neutrino_more_ensembles_FixedFlux_Carbon_100files.list"
#"list/GiBUUMINERvA_ME_Antineutrino_NoFSI_C_100files.list"
#

export NUGASa8P50=

nfile=

tag=MINERvAGiBUU_METWO_UNPHNOF
#MINERvAGiBUU_LE_
#MINERvALE_GiBUU_test_
#MINERvAGiBUU_PIZEROrep_${nfile}_
#DUNEGiBUU_${nfile}_
#MINERvAGiBUU_protectedBkg_${nfile}_
#MINERvAGiBUU_PiCut2Fixed_${nfile}_

####################################

mkexe.sh anaGenerator_BACKUP -I${NUGENTKI}/include

#exit

#GFS 7
#opt=${tag}GFSPIZEROa7nuH;        nohup ./doAna.sh $GFSPIZEROa7nuH        ${opt} 7 ${nfile} > see${opt}.log &
#opt=${tag}GFSPIZEROa7nuC;        nohup ./doAna.sh $GFSPIZEROa7nuC        ${opt} 7 ${nfile} > see${opt}.log &
#opt=${tag}GFSPIZEROa7nuNOFSIC;   nohup ./doAna.sh $GFSPIZEROa7nuNOFSIC   ${opt} 7 ${nfile} > see${opt}.log &

#exit

#GFS0PI 9
#opt=${tag}GFS0PIa9nuH;              nohup ./doAna.sh $GFS0PIa9nuH               ${opt} 9 ${nfile} > see${opt}.log & 
#opt=${tag}GFS0PIa9nuC;              nohup ./doAna.sh $GFS0PIa9nuC               ${opt} 9 ${nfile} > see${opt}.log &
#echo "We have reached the command" > see${opt}.log 
#opt=${tag}GFS0PIa9nuNOFSIC;         nohup ./doAna.sh $GFS0PIa9nuNOFSIC          ${opt} 9 ${nfile} > see${opt}.log & 

#GFS 0
opt=${tag}GFSa0nuC;              nohup ./doAna.sh $GFSa0nuC              ${opt}  0 ${nfile} > see${opt}.log &
opt=${tag}GFSa0nuH;              nohup ./doAna.sh $GFSa0nuH              ${opt}  0 ${nfile} > see${opt}.log &

exit

#EXCL3 10

opt=${tag}EXCL3a10nuH;           nohup ./doAna.sh $EXCL3a10nuH           ${opt} 10 ${nfile} > see${opt}.log &
opt=${tag}EXCL3a10nubarH;        nohup ./doAna.sh $EXCL3a10nubarH        ${opt} 10 ${nfile} > see${opt}.log &
opt=${tag}EXCL3a10nuC;           nohup ./doAna.sh $EXCL3a10nuC           ${opt} 10 ${nfile} > see${opt}.log &
opt=${tag}EXCL3a10nubarC;        nohup ./doAna.sh $EXCL3a10nubarC        ${opt} 10 ${nfile} > see${opt}.log &

exit


#NUGAS 8
opt=${tag}NUGASa8P50;         nohup ./doAna.sh $NUGASa8P50         ${opt} 8 ${nfile} > see${opt}.log &

exit


#MMECCQE 4 only carbon
opt=${tag}MMECCQEa4nuC;        nohup ./doAna.sh $MMECCQEa4nuC        ${opt} 4 ${nfile} > see${opt}.log & 

exit

#GFS 3
opt=${tag}GFSa3nuC;          nohup ./doAna.sh $GFSa3nuC          ${opt} 3 > see${opt}.log &

exit


#LOWRECOIL 1
opt=${tag}LOWRECOILa1nuC;    nohup ./doAna.sh $LOWRECOILa1nuC    ${opt} 1 > see${opt}.log &
opt=${tag}LOWRECOILa1nubarC; nohup ./doAna.sh $LOWRECOILa1nubarC ${opt} 1 > see${opt}.log &
opt=${tag}LOWRECOILa1nuH;    nohup ./doAna.sh $LOWRECOILa1nuH    ${opt} 1 > see${opt}.log &
opt=${tag}LOWRECOILa1nubarH; nohup ./doAna.sh $LOWRECOILa1nubarH ${opt} 1 > see${opt}.log &

#NUBAR1PI 2
opt=${tag}NUBAR1PIa2nubarC;  nohup ./doAna.sh $NUBAR1PIa2nubarC  ${opt} 2 > see${opt}.log &
opt=${tag}NUBAR1PIa2nubarH;  nohup ./doAna.sh $NUBAR1PIa2nubarH  ${opt} 2 > see${opt}.log &
  
exit

