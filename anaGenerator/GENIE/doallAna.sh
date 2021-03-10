export GFS0PIa9nuCH=
#"list/Filelist_GENIE_V3test_BeamNu_EnuME_TargetCarbon.txt"
#"list/Filelist_GENIE_V3_BeamNu_EnuMINERvA_TargetCH.txt"
#"list/Filelist_GENIE_V3test_BeamNu_EnuMINERvA_TargetCarbon.txt"
#"list/Filelist_GENIE_v2TJ_BeamNu_EnuMINERvA_TargetCarbon.list"
#"list/Filelist_GENIE_v2DC_BeamNu_EnuMINERvA_TargetCarbon.list"
#"list/Filelist_GENIE_v3OOB_BeamNu_EnuMINERvA_TargetCarbon.list"
#"list/Filelist_GENIE_V2RG_BeamNu_EnuMINERvA_TargetCarbon.list"

export GFSPIZEROa7nuCH="list/Filelist_GENIEV3_BeamNu_EnuME_TargetCH.txt"
export GFSPIZEROa7nuC="list/Filelist_GENIEV3_BeamNu_NOFSI_EnuME_TargetCarbon.txt"
#"list/Filelist_GENIEV3_BeamNu_EnuME_TargetCarbon_NOFSI.txt"
#
export GFSPIZEROa7nuH="list/Filelist_GENIEV3_BeamNu_NOFSI_EnuME_TargetHydrogen.txt"
#"list/Filelist_GENIEV3_BeamNu_NOFSI_EnuME_TargetHydrogen.txt"
#

export LOWRECOILa1nuCH=${GFS0PIa9nuCH}

export LOWRECOILa1nubarCH=

export NUBAR1PIa2nubarCH=${LOWRECOILa1nubarCH}

export CLRa5nuCH=

export RESPSa6nuCH=

export GFSEXPa3nuCH=

export MMECCQEnuCH=

export NUGASa8nubar=

export GFSa0nuCH="list/Filelist_GENIEV3_BeamNu_EnuME_TargetCH.txt"
#${GFS0PIa9nuCH}
export GFSa0nuC="list/Filelist_GENIEV3_BeamNubar_EnuME_TargetCarbon.txt"
#"list/Filelist_GENIEV3_BeamNubar_NOFSI_EnuME_TargetCarbon.txt"
#"list/Filelist_GENIEV3_BeamNu_NOFSITWO_EnuME_TargetCarbon.txt"
#"list/Filelist_GENIEV3_BeamNubar_NOFSI_EnuME_TargetCarbon.txt"
#${GFSPIZEROa7nuC}
#
#"list/Filelist_GENIEV3_BeamNu_EnuME_TargetCarbon.txt"
#"list/Filelist_GENIEV3_BeamNu_EnuMINERvA_TargetCarbon.txt"
#"list/Filelist_GENIEV3_BeamNubar_EnuME_TargetCarbon.txt"
export GFSa0nuH="list/Filelist_GENIEV3_BeamNubar_EnuME_TargetHydrogen.txt"
#"list/Filelist_GENIEV3_BeamNu_NOFSITWO_EnuME_TargetHydrogen.txt"
#"list/Filelist_GENIEV3_BeamNubar_NOFSI_EnuME_TargetHydrogen.txt"
#${GFSPIZEROa7nuH}
#
#"list/Filelist_GENIEV3_BeamNu_EnuME_TargetHydrogen.txt"
#"list/Filelist_GENIEV3_BeamNubar_EnuME_TargetHydrogen.txt"
#"list/Filelist_GENIEV3_BeamNu_EnuMINERvA_TargetHydrogen.txt"

ntostop=
#10000000

tag=MINERvAGENIE_V3MEBAR
#MINERvAGENIE_V3MEBAR
#MINERvAGENIE_V3LE
#MINERvAGENIE_V3test_
#MINERvAGENIE_v2TJ_LE_
#MINERvAGENIE_v2DC_LE_
#MINERvAGENIE_v3OOB_LE_
#MINERvAGENIE_V2RG_LE_

####################################

#mkexe.sh anaGenerator -I${NUGENTKI}/include
mkexe.sh anaGenerator_BACKUP -I${NUGENTKI}/include

#exit

#GFS 9 : 0PI
#opt=${tag}GFS0PIa9nuCH;          nohup ./doAna.sh $GFS0PIa9nuCH          ${opt} 9 ${ntostop} > see${opt}.log &

#exit

#GFS 7 : PIZERO
#opt=${tag}GFSPIZEROa7nuCH;    nohup ./doAna.sh $GFSPIZEROa7nuCH    ${opt} 7 ${ntostop} > see${opt}.log &
#opt=${tag}GFSPIZEROa7nuC;    nohup ./doAna.sh $GFSPIZEROa7nuC    ${opt} 7 ${ntostop} > see${opt}.log &
#opt=${tag}GFSPIZEROa7nuH;    nohup ./doAna.sh $GFSPIZEROa7nuH    ${opt} 7 ${ntostop} > see${opt}.log &

#GFS 0 : PION
#opt=${tag}GFSa0nuCH;          nohup ./doAna.sh $GFSa0nuCH          ${opt} 0 ${ntostop} > see${opt}.log &
opt=${tag}GFSa0nuC;          nohup ./doAna.sh $GFSa0nuC          ${opt} 0 ${ntostop} > see${opt}.log &
opt=${tag}GFSa0nuH;          nohup ./doAna.sh $GFSa0nuH          ${opt} 0 ${ntostop} > see${opt}.log &

exit

#NUGAS 8
opt=${tag}NUGASa8nubar;         nohup ./doAna.sh $NUGASa8nubar         ${opt} 8 ${ntostop} > see${opt}.log &

exit

#MMECCQE 4 
opt=${tag}MMECCQEnuCH;         nohup ./doAna.sh $MMECCQEnuCH        ${opt} 4 ${nfile} > see${opt}.log &

exit


#backup in case my changes go badly
#GFS 3
#opt=${tag}GFSEXPa3nuCH;          nohup ./doAna.sh $GFSEXPa3nuCH          ${opt} 3 > see${opt}.log &

#exit

#RESPS 6
opt=${tag}RESPSa6nuCH;        nohup ./doAna.sh $RESPSa6nuCH        ${opt} 6 ${ntostop} > see${opt}.log &

exit

#CLR 5
opt=${tag}CLRa5nuCH;          nohup ./doAna.sh $CLRa5nuCH          ${opt} 5 ${ntostop} > see${opt}.log &


#LOWRECOIL 1
opt=${tag}LOWRECOILa1nuCH;    nohup ./doAna.sh $LOWRECOILa1nuCH    ${opt} 1 > see${opt}.log &
opt=${tag}LOWRECOILa1nubarCH; nohup ./doAna.sh $LOWRECOILa1nubarCH ${opt} 1 > see${opt}.log &

#NUBAR1PI 2
opt=${tag}NUBAR1PIa2nubarCH;  nohup ./doAna.sh $NUBAR1PIa2nubarCH  ${opt} 2 > see${opt}.log &

exit
