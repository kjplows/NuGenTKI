export             GFSa9nuCH="list/Filelist_GENIEOOB_a1_BeamNu_EnuMINERvA_TargetCH.list"
#"list/GENIEOOB_BeamNubar_EnuMINERvA_TargetCH.list"
#"list/GENIEOOB_BeamNu_EnuMINERvA_TargetCH.list"
#"list/GENIEOOB_BeamNu_EnuT2K_TargetCH.list"
#"list/GENIEISO_BeamNu_EnuMINERvA_TargetCH.list"
#

export       LOWRECOILa1nuCH=${GFSa9nuCH}

export LOWRECOILa1nubarCH=
#"list/GENIEISO_BeamNubar_EnuMINERvA_TargetCH.list"
#"list/GENIEOOB_BeamNubar_EnuMINERvA_TargetCH.list"

export  NUBAR1PIa2nubarCH=${LOWRECOILa1nubarCH}

export CLRa5nuCH=
#"list/GENIEISO_BeamNu_EnuMINERvA_TargetCH.list"
#"list/GENIEISO_BeamNu_Enu3000_TargetCH.list"
#
export RESPSa6nuCH=
#"list/GENIEISO_BeamNu_EnuMINERvA_TargetCH.list"

export GFSEXPa3nuCH=
#"list/GENIEOOB_BeamNu_EnuT2K_TargetCH.list"

export          MMECCQEnuCH=
#"list/GENIEOOB_BeamNu_EnuMME_TargetCH.list"

export GFSPIZEROa7nuCH="list/Filelist_GENIEOOB_a1_BeamNu_EnuMINERvA_TargetCH.list"
#"list/Filelist_singleTest_dcGENIE2LFGHN_BeamNu_EnuMINERvA_TargetCH.list"
#Filelist_dcGENIE2LFGHN_BeamNu_EnuMINERvA_TargetCH.list"
#Filelist_GENIE2LFGHN_${aaa}_BeamNu_EnuMINERvA_TargetCH.list"
#"list/GENIEOOB_BeamNu_EnuMINERvA_TargetCH.list"

export NUGASa8nubar=
#"list/GENIEOOB_BeamNubar_EnuDUNE_TargetHydrogen.list"
#"list/GENIEOOB_BeamNubar_Enu24000800_TargetP50.list"

ntostop=
#10000000

tag=MINERvAGENIEOOB_cleanCodetest_
#MINERvAGENIEOOB_LE_
#MINERvA${aaa}GENIEPIZERO
#DUNEGENIEOOB${ntostop}
#24000800GENIEOOBP50HONLY${ntostop}
#MINERvAGENIEOOB
#MINERvAMEGENIEOOB
#MINERvAGENIEOOB
#GENIEOOBT2K
#
#MINERvAGENIEISOiniAngle
#2Boost
#3GeVGENIEISOCLRfull
#3GeVGENIEISOw2onsignKNsrc${ntostop}
#3GeVGENIEISOw2onsign${ntostop}
#MINERvAGENIEISOw2
#MINERvAGENIEOOB
#MINERvAGENIEISO

####################################

mkexe.sh anaGenerator

#GFS 7 : PIZERO
opt=${tag}GFSPIZEROa7nuCH;    nohup ./doAna.sh $GFSPIZEROa7nuCH    ${opt} 7 ${ntostop} > see${opt}.log &

exit

#GFS 9 : 0PI
opt=${tag}GFSa9nuCH;          nohup ./doAna.sh $GFSa9nuCH          ${opt} 9 ${ntostop} > see${opt}.log &

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

##################################################################################################################################################
#
##################################################################################################################################################

#NUBAR1PI 2
nohup ./doAna.sh list/BeamNubar_EnuMINERvA_TargetCH.list nubarCHMINERvAGENIEa2 2 > seenubarCHMINERvAGENIEa2.log &

exit

#LOWRECOIL 1
nohup ./doAna.sh list/BeamNu_EnuMINERvA_TargetCH.list      nuCHMINERvAGENIEa1 1 > seenuCHMINERvAGENIEa1.log &
nohup ./doAna.sh list/BeamNubar_EnuMINERvA_TargetCH.list nubarHMINERvAGENIEa1 1 > seenubarHMINERvAGENIEa1.log &
exit

#GFS 0 CH MINERvA
nohup ./doAna.sh list/BeamNu_EnuMINERvA_TargetCH.list nuCHMINERvAGENIEa0 0 > seenuCHMINERvAGENIEa0.log &

exit

####################################################################### GiBUU from before =====================
#GFS 3 carbon T2K T0

nohup ./doAna.sh list/noEuCut/FinalEventsList_005_T2K_nu_freeDelta_T0_noFSInoFSInoFSInoFSI_Flux9_noEuCut_1kruns_1000jobs.log nuNOFSINOFSIcarbonT2KT0GiBUU2019a3exp3trackphasespaceNoMeson 3 > seenuNOFSINOFSIcarbonT2KT0GiBUU2019a3exp3trackphasespaceNoMeson.LOG &
#nohup ./doAna.sh list/noEuCut/FinalEventsList_005_T2K_nu_freeDelta_T0_FSI_Flux9_noEuCut_1kruns_1000jobs.log nuCarbonT2KT0GiBUU2019a3exp3trackphasespaceNoMeson                            3 > seenuCarbonT2KT0GiBUU2019a3exp3trackphasespaceNoMeson.log &

exit

#GFS 0 carbon MINERvA and T2K T0 
nohup ./doAna.sh list/noEuCut/FinalEventsList_005_MINERvA_nu_freeDelta_T0_FSI_Flux25_noEuCut_1kruns_2_998jobs.log nuCarbonMINERvAT0GiBUU2019a0xBj 0 > seenuCarbonMINERvAT0GiBUU2019a0xBj.log &
nohup ./doAna.sh list/noEuCut/FinalEventsList_005_T2K_nu_freeDelta_T0_FSI_Flux9_noEuCut_1kruns_1000jobs.log       nuCarbonT2KT0GiBUU2019a0xBj 0 > seenuCarbonT2KT0GiBUU2019a0xBj.log &

#nohup ./doAna.sh list/noEuCut/FinalEventsList_005_T2K_nu_freeDelta_T0_noFSInoFSInoFSInoFSI_Flux9_noEuCut_1kruns_1000jobs.log nuNOFSINOFSIcarbonT2KT0GFS1piGiBUU2019v1a0 0 > seenuNOFSINOFSIcarbonT2KT0GFS1piGiBUU2019v1a0.log &

exit

#NUBAR1PI 2 sigmaEnu

nohup ./doAna.sh list/sigmaEnu/eventlist_005_MINERvA_nubar_freeDelta_T0_Flux25_carbonEuCut_1kruns_77jobs.log                 nubarCarbonNUBAR1PIsigmaEnuv10a2                     2 > seenubarCarbonNUBAR1PIsigmaEnuv10a2.log &
nohup ./doAna.sh list/sigmaEnu/eventlist_005_MINERvA_nubar_freeDelta_T0_Flux25_hydrogenEuCut_1kruns_77jobs.log               nubarHydrogenNUBAR1PIsigmaEnuv10a2                   2 > seenubarHydrogenNUBAR1PIsigmaEnuv10a2.log &
nohup ./doAna.sh list/sigmaEnu/eventlist_005_MINERvA_nubar_freeDelta_T0_Flux25_noFSInoFSInoFSI_carbonEuCut_1kruns_77jobs.log nubarCarbonnoFSInoFSInoFSInoFSINUBAR1PIsigmaEnuv10a2 2 > seenubarCarbonnoFSInoFSInoFSInoFSINUBAR1PIsigmaEnuv10a2.log &

exit

#NUBAR1PI 2  

nohup ./doAna.sh list/EuCut1500to10000/005_MINERvA_nubar_freeDelta_T0_noFSInoFSInoFSInoFSI_Flux25_EuCut1500to10000_1kruns_999jobs.log nubarCarbonnoFSInoFSInoFSInoFSINUBAR1PIv9a2 2 > seenubarCarbonnoFSInoFSInoFSInoFSINUBAR1PIv9a2.log & 
nohup ./doAna.sh list/EuCut1500to10000/005_MINERvA_nubar_freeDelta_T0_FSI_Flux25_EuCut1500to10000_1kruns_960jobs.log                  nubarCarbonNUBAR1PIv9a2 2                     > seenubarCarbonNUBAR1PIv9a2.log &
nohup ./doAna.sh list/EuCut1500to10000/005_MINERvA_nubar_freeDelta_T0_noFSI_Flux25_EuCut1500to10000_hydrogen_1kruns_1000jobs.log      nubarHydrogenNUBAR1PIv9a2 2                   > seenubarHydrogenNUBAR1PIv9a2.log &

exit


#LOWRECOIL 1 2019-06-13 GiBUU2019

nohup ./doAna.sh list/EuCut2to6/eventlist_005_MINERvA_nu_freeDelta_T0_FSI_Flux25_EuCut2to6_1kruns_id2007_976jobs.log                        nuCarbonLOWRECOILv8a1GiBUU2019 1 >      seenuCarbonLOWRECOILv8a1GiBUU2019.log &
nohup ./doAna.sh list/EuCut2to6/eventlist_005_MINERvA_nu_freeDelta_T0_noFSI_Flux25_EuCut2to6_hydrogen_1kruns_id8_1000jobs.log             nuHydrogenLOWRECOILv8a1GiBUU2019 1 >    seenuHydrogenLOWRECOILv8a1GiBUU2019.log &
nohup ./doAna.sh list/EuCut2to6/eventlist_005_MINERvA_nubar_freeDelta_T0_FSI_Flux25_EuCut2to6_1000runs_id7_990jobs.log                   nubarCarbonLOWRECOILv8a1GiBUU2019 1 >   seenubarCarbonLOWRECOILv8a1GiBUU2019.log &
nohup ./doAna.sh list/EuCut2to6/eventlist_005_MINERvA_nubar_freeDelta_T0_noFSI_Flux25_EuCut2to6_hydrogen_1000runs_id1007_1000jobs.log  nubarHydrogenLOWRECOILv8a1GiBUU2019 1 > seenubarHydrogenLOWRECOILv8a1GiBUU2019.log &

exit

#LOWRECOIL 1 v14 flux cut fixed, 2019-01-13 with lineR cut for protons and all pions

nohup ./doAna.sh list/EuCut2to6/FinalEventList_n_MINERvA_nubar_freeDelta_T0_noFSI_Flux14_EuCut2to6_hydrogen_1000runs_1kjobs_15.log  nubarHydrogenLOWRECOILv14a1cutR 1 > seenubarHydrogenLOWRECOILv14a1cutR.log &
nohup ./doAna.sh list/EuCut2to6/FinalEventList_n_MINERvA_nubar_freeDelta_T0_FSI_Flux14_EuCut2to6_1000runs_992jobs_14.log            nubarCarbonLOWRECOILv14a1cutR 1 > seenubarCarbonLOWRECOILv14a1cutR.log &
nohup ./doAna.sh list/EuCut2to6/FinalEventList_n_MINERvA_nu_freeDelta_T0_FSI_Flux25_EuCut2to6_1kruns_935jobs_14.log             nuCarbonLOWRECOILv14a1cutR 1 > seenuCarbonLOWRECOILv14a1cutR.log &
nohup ./doAna.sh list/EuCut2to6/FinalEventList_n_MINERvA_nu_freeDelta_T0_noFSI_Flux25_EuCut2to6_hydrogen_1kruns_1kjobs_14.log   nuHydrogenLOWRECOILv14a1cutR 1 > seenuHydrogenLOWRECOILv14a1cutR.log &

exit

#LOWRECOIL v21 CugnonFSI

nohup ./doAna.sh   list/EuCut2to6/CugnonFSI/FinalEventList_n_MINERvA_nubar_freeDelta_T0_FSI_Flux14_EuCut2to6_1000runs_CugnonFSI_930jobs.log   nubarCarbonLOWRECOILCugnonFSIv21a1 1 > seenubarCarbonLOWRECOILCugnonFSIv21a1.log &
nohup ./doAna.sh   list/EuCut2to6/CugnonFSI/FinalEventList_n_MINERvA_nu_freeDelta_T0_FSI_Flux25_EuCut2to6_1kruns_CugnonFSI_892jobs.log        nuCarbonLOWRECOILCugnonFSIv21a1    1 > seenuCarbonLOWRECOILCugnonFSIv21a1.log &

exit

#GFS 0 nubar

nohup ./doAna.sh list/FinalEventList_n_MINERvA_nubar_freeDelta_T0_noFSI_Flux14_noEuCut_hydrogen_1000runs_1kjobs_17.log nubarHydrogenGFSv16a0 0 > seenubarHydrogenGFSv16a0.log &
nohup ./doAna.sh list/FinalEventList_n_MINERvA_nubar_freeDelta_T0_FSI_Flux14_noEuCut_1000runs_999jobs_17.log           nubarCarbonGFSv16a0   0 > seenubarCarbonGFSv16a0.log &

exit

#LOWRECOIL 1 v16 noFSI

nohup ./doAna.sh list/FinalEventList_n_MINERvA_nubar_freeDelta_T0_noFSInoFSInoFSInoFSI_Flux14_EuCut2to6_1000runs_1kjobs_16.log nubarCarbonLOWRECOILnoFSInoFSInoFSInoFSIv15a1 1 > seenubarCarbonLOWRECOILnoFSInoFSInoFSInoFSIv15a1.log &
nohup ./doAna.sh list/FinalEventList_n_MINERvA_nu_freeDelta_T0_noFSInoFSInoFSI_Flux25_EuCut2to6_1kruns_1kjobs_16.log           nuCarbonLOWRECOILnoFSInoFSInoFSInoFSIv15a1 1 > seenuCarbonLOWRECOILnoFSInoFSInoFSInoFSIv15a1.log &

exit

#LOWRECOIL 1 v14 flux cut fixed                                                                                                                                                                                                    

nohup ./doAna.sh list/FinalEventList_n_MINERvA_nubar_freeDelta_T0_noFSI_Flux14_EuCut2to6_hydrogen_1000runs_1kjobs_15.log  nubarHydrogenLOWRECOILv14a1 1 > seenubarHydrogenLOWRECOILv14a1.log &
nohup ./doAna.sh list/FinalEventList_n_MINERvA_nubar_freeDelta_T0_FSI_Flux14_EuCut2to6_1000runs_992jobs_14.log            nubarCarbonLOWRECOILv14a1 1 > seenubarCarbonLOWRECOILv14a1.log &
nohup ./doAna.sh list/FinalEventList_n_MINERvA_nu_freeDelta_T0_FSI_Flux25_EuCut2to6_1kruns_935jobs_14.log             nuCarbonLOWRECOILv14a1 1 > seenuCarbonLOWRECOILv14a1.log &
nohup ./doAna.sh list/FinalEventList_n_MINERvA_nu_freeDelta_T0_noFSI_Flux25_EuCut2to6_hydrogen_1kruns_1kjobs_14.log   nuHydrogenLOWRECOILv14a1 1 > seenuHydrogenLOWRECOILv14a1.log &

exit




