dir0=$(pwd)

for anaid in MINERvAMEBARGiBUUGFSa0t4nuHydrogen MINERvAMEBARGiBUUGFSa0t4nuCarbon
#MINERvAMEGiBUUGFSPIZEROa7t4nuCarbon MINERvAMEGiBUUGFSPIZEROa7t4nuHydrogen
#MINERvAMEBARGiBUUGFSa0t4nuCarbon MINERvAMEBARGiBUUGFSa0t4nuHydrogen
#MINERvAMEGiBUUGFSa0t4nuCarbon MINERvAMEGiBUUGFSa0t4nuHydrogen MINERvAMEGiBUUGFSa0t4nuCH
#MINERvAMEGiBUUGFSa0t4nuHydrogen
#MINERvAMEGENIEGFSa0t4nuHydrogen
#MINERvALEGiBUUGFSa0t4nuHydrogen 
#MINERvALEGiBUUGFSa0t4nuCarbon
#MINERvALEGiBUUGFS0PIa9t1nuCarbon MINERvALEGiBUUGFSPIZEROa7t4nuCarbon
#MINERvAGENIEGFSPIZEROa7t4nuCarbon MINERvAGENIEGFS0PIa9t1nuCarbon
#GFS0PIMINERvAGiBUULE_CarbonOnly GFSPIZEROMINERvAGiBUULE_CarbonOnly GFSPIZEROMINERvAGENIEv2TJ_LE_CarbonOnly GFS0PIMINERvAGENIEv2TJ_LE_CarbonOnly
#GFSPIZEROMINERvAGENIE_v2DC_LE_CarbonOnly GFS0PIMINERvAGENIE_v2DC_LE_CarbonOnly
#GFSPIZEROMINERvAGENIE_V2RG_LE_CarbonOnly GFS0PIMINERvAGENIE_V2RG_LE_CarbonOnly 
#GFSPIZEROMINERvAGENIE_v3OOB_LE_CarbonOnly GFS0PIMINERvAGENIE_v3OOB_LE_CarbonOnly


do

echo
echo "===============================================================" $anaid
cd $dir0

#directory will be made in getStack.C

nfile=0
for locdir in ${anaid}{,nu{,bar}}
do
    echo locdir $locdir
    echo
    fin=outplot/${locdir}.root

    if [ ! -e $fin ]
    then
        continue
    fi

    nfile=$( expr $nfile + 1 )
        
    ls $fin
    echo
    tag=$(basename $fin | awk -F\. '{print $1}')
    echo tag $tag
    echo

    commonVar="enu omegamup chi muonmomentum muontheta muonmomentumVStheta Q2 xBj xrest Wtrue Wrest "
    #commonVar="chi "

    if [  $anaid == GFS0PIMINERvAGENIE_v3OOB_LE_CarbonOnly -o $anaid == GFS0PIMINERvAGENIE_v2DC_LE_CarbonOnly -o $anaid == GFS0PIMINERvAGENIE_V2RG_LE_CarbonOnly -o $anaid == GFS0PIMINERvAGiBUULE_CarbonOnly -o $anaid == GFS0PIMINERvAGENIEv2TJ_LE_CarbonOnly -o $anaid == MINERvAGENIEGFS0PIa9t1nuCarbon  -o $anaid == MINERvALEGiBUUGFS0PIa9t1nuCarbon ]
    then
        varray=${commonVar}" protonmomentum protontheta dpt dphit dalphat neutronmomentum"
    elif [ $anaid == GFSPIZEROMINERvAGENIE_v3OOB_LE_CarbonOnly -o $anaid == GFSPIZEROMINERvAGENIE_v2DC_LE_CarbonOnly -o $anaid == GFSPIZEROMINERvAGENIE_V2RG_LE_CarbonOnly -o $anaid == GFSPIZEROMINERvAGiBUULE_CarbonOnly -o $anaid == GFSPIZEROMINERvAGENIEv2TJ_LE_CarbonOnly -o $anaid == MINERvAGENIEGFSPIZEROa7t4nuCarbon -o $anaid == MINERvALEGiBUUGFSPIZEROa7t4nuCarbon -o $anaid == MINERvAGENIEGFSa0t2nuCarbon -o $anaid == MINERvALEGiBUUGFSa0t2nuCarbon -o $anaid == MINERvALEGiBUUGFSa0t4nuCarbon -o $anaid==MINERvALEGiBUUGFSa0t4nuHydrogen -o $anaid == MINERvAMEBARGiBUUGFSa0t4nuCarbon -o $anaid == MINERvAMEBARGiBUUGFSa0t4nuHydrogen -o $anaid == MINERvAMEGiBUUGFSPIZEROa7t4nuCarbon -o $anaid == MINERvAMEGiBUUGFSPIZEROa7t4nuHydrogen ]
    then
        varray=${commonVar}" protonmomentum protontheta pionmomentum piontheta pionmomentumVStheta pionEk pionEkVStheta pionEkVSomegamup omegamupVStheta pionTmax pionTmaxVStheta baryonmomentum baryontheta baryonmass dpt dphit dalphat neutronmomentum dpTT chiVSdalphat "
	#varray=${commonVar}

    elif [  $anaid == DUNEEXCL3_CH ]                                                                                           
    then                                                                                                                       
        varray=${commonVar}"protonmomentum protontheta pionEk pionmomentum piontheta baryonmomentum baryontheta baryonmass dpT\
T dpTT20s dpTT10s dpTT5s dpTT2s "
    elif [ $anaid == LOWRECOILMINERvAGENIEOOB -o $anaid == LOWRECOILMINERvAGENIEISO  -o $anaid == LOWRECOILMINERvAGENIEISOw2 ]
    then
        varray=${commonVar}$(echo " " Eav{0,1,2,3,4,5} q3)
    elif [ $anaid == NUBAR1PIMINERvAGENIEOOB -o $anaid == NUBAR1PIMINERvAGENIEISO  -o $anaid == NUBAR1PIMINERvAGENIEISOw2 ]
    then
        varray=${commonVar}" pionEk piontheta pionmomentum"
    elif [ $anaid == MMECCQEMINERvAMEGENIEOOB ]
    then
        varray=${commonVar}$(echo q2qe muonpt mupz muonptVSmupz mupzVSmuonpt )
# ErecoilTIMES1E3VSmupzVSmuonpt 
#muonpt{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14} mupz{0,1,2,3,4,5,6,7,8,9,10,11,12} 
    else
        echo wrong anaid $anaid
        exit
    fi

    echo    
    echo $varray
    echo

    for var in $varray
    do

        echo var $var 
        echo

        root -b -l -q 'getStack2.C("'${fin}'", "'${anaid}'","'${tag}'","'${var}'")'

    done
done

echo nfile $nfile

if [ $nfile != 0 ]
then
    cd outStack/${anaid}
    ls *.root
    hadd  ${anaid}.root *.root > seemerge.log
fi

done

