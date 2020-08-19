export GFSa9nuCH="list/Filelist_GENIE_V2RG_BeamNu_EnuMINERvA_TargetCarbon.list"
#"list/Filelist_GENIEOOB_a1_BeamNu_EnuMINERvA_TargetCarbon.list"
export GFSPIZEROa7nuCH=${GFSa9nuCH}

export LOWRECOILa1nuCH=${GFSa9nuCH}

export LOWRECOILa1nubarCH=

export NUBAR1PIa2nubarCH=${LOWRECOILa1nubarCH}

export CLRa5nuCH=

export RESPSa6nuCH=

export GFSEXPa3nuCH=

export MMECCQEnuCH=

export NUGASa8nubar=

ntostop=
#10000000

tag=MINERvAGENIE_V2RG_LE_
#MINERvAGENIEv3OOB_LE_

####################################

mkexe.sh anaGenerator -I${NUGENTKI}/include

#exit

#GFS 9 : 0PI
opt=${tag}GFSa9nuCH;          nohup ./doAna.sh $GFSa9nuCH          ${opt} 9 ${ntostop} > see${opt}.log &

#exit

#GFS 7 : PIZERO
opt=${tag}GFSPIZEROa7nuCH;    nohup ./doAna.sh $GFSPIZEROa7nuCH    ${opt} 7 ${ntostop} > see${opt}.log &

exit

#NUGAS 8
opt=${tag}NUGASa8nubar;         nohup ./doAna.sh $NUGASa8nubar         ${opt} 8 ${ntostop} > see${opt}.log &

exit

#MMECCQE 4 
opt=${tag}MMECCQEnuCH;         nohup ./doAna.sh $MMECCQEnuCH        ${opt} 4 ${nfile} > see${opt}.log &

exit



#GFS 3
opt=${tag}GFSEXPa3nuCH;          nohup ./doAna.sh $GFSEXPa3nuCH          ${opt} 3 > see${opt}.log &

exit

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
