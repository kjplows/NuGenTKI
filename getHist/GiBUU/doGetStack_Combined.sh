dir0=$(pwd)

for anaidC in MINERvAMEGiBUUGFSa0t4nuCarbon
#
#MINERvALEGiBUUGFSa0t4nuCarbon
#MINERvALEGENIEGFSa0t4nuCarbon
#MINERvAMEGENIEGFSa0t4nuCarbon
#MINERvAMEGiBUUFFGFSa0t4nuCarbon
#MINERvAMEGENIEGFSa0t4nuCarbon
#MINERvAMEGENIEGFSa0t4nuCarbon
#MINERvALEGiBUUGFS0PIa9t1nuCarbon MINERvALEGiBUUGFSPIZEROa7t4nuCarbon
#MINERvAGENIEGFSPIZEROa7t4nuCarbon MINERvAGENIEGFS0PIa9t1nuCarbon
#GFS0PIMINERvAGiBUULE_CarbonOnly GFSPIZEROMINERvAGiBUULE_CarbonOnly GFSPIZEROMINERvAGENIEv2TJ_LE_CarbonOnly GFS0PIMINERvAGENIEv2TJ_LE_CarbonOnly
#GFSPIZEROMINERvAGENIE_v2DC_LE_CarbonOnly GFS0PIMINERvAGENIE_v2DC_LE_CarbonOnly
#GFSPIZEROMINERvAGENIE_V2RG_LE_CarbonOnly GFS0PIMINERvAGENIE_V2RG_LE_CarbonOnly 
#GFSPIZEROMINERvAGENIE_v3OOB_LE_CarbonOnly GFS0PIMINERvAGENIE_v3OOB_LE_CarbonOnly
do

for anaidH in MINERvAMEGiBUUGFSa0t4nuHydrogen
#
#MINERvALEGiBUUGFSa0t4nuHydrogen
#MINERvALEGENIEGFSa0t4nuHydrogen
#MINERvAMEGENIEGFSa0t4nuHydrogen
#MINERvAMEGiBUUFFGFSa0t4nuHydrogen
#MINERvAMEGENIEGFSa0t4nuHydrogen
#MINERvAMEGENIEGFSa0t4nuHydrogen

do

echo
echo "===============================================================" $anaidC " " $anaidH
cd $dir0

anaid=${anaidC::-6}
anaid+=CH

#directory will be made in getStack.C

nfile=0
for locdirC in ${anaidC}{,nu{,bar}}
do
for locdirH in ${anaidH}{,nu{,bar}}
do
    echo locdirC $locdirC
    echo locdirH $locdirH
    echo
    finC=outplot/${locdirC}.root
    finH=outplot/${locdirH}.root

    if [ ! -e $finC ]
    then
        continue
    fi
    if [ ! -e $finH ]
    then
        continue
    fi

    nfile=$( expr $nfile + 1 )
        
    ls $finC
    echo
    tag=$(basename $finC | awk -F\. '{print $1}')
    echo tag $tag
    echo

    commonVar="enu muonmomentum muontheta muonmomentumVStheta Q2 xBj xrest Wtrue Wrest "

    if [  $anaidC == GFS0PIMINERvAGENIE_v3OOB_LE_CarbonOnly -o $anaidC == GFS0PIMINERvAGENIE_v2DC_LE_CarbonOnly -o $anaidC == GFS0PIMINERvAGENIE_V2RG_LE_CarbonOnly -o $anaidC == GFS0PIMINERvAGiBUULE_CarbonOnly -o $anaidC == GFS0PIMINERvAGENIEv2TJ_LE_CarbonOnly -o $anaidC == MINERvAGENIEGFS0PIa9t1nuCarbon  -o $anaidC == MINERvALEGiBUUGFS0PIa9t1nuCarbon ]
    then
        varray=${commonVar}" protonmomentum protontheta dpt dphit dalphat neutronmomentum"
    elif [ $anaidC == GFSPIZEROMINERvAGENIE_v3OOB_LE_CarbonOnly -o $anaidC == GFSPIZEROMINERvAGENIE_v2DC_LE_CarbonOnly -o $anaidC == GFSPIZEROMINERvAGENIE_V2RG_LE_CarbonOnly -o $anaidC == GFSPIZEROMINERvAGiBUULE_CarbonOnly -o $anaidC == GFSPIZEROMINERvAGENIEv2TJ_LE_CarbonOnly -o $anaidC == MINERvAGENIEGFSPIZEROa7t4nuCarbon -o $anaidC == MINERvALEGiBUUGFSPIZEROa7t4nuCarbon -o $anaidC == MINERvAGENIEGFSa0t2nuCarbon -o $anaidC == MINERvALEGiBUUGFSa0t2nuCarbon -o $anaidC == MINERvALEGiBUUGFSa0t4nuCarbon -o $anaidC==MINERvAMEGiBUUGFSa0t4nuCarbon -o $anaidC == MINERvAMEGENIEGFSa0t4nuCarbon ]
    then
        varray=${commonVar}" protonmomentum protontheta pionmomentum piontheta pionmomentumVStheta pionEk pionEkVStheta baryonmomentum baryontheta baryonmass dpt dphit dalphat neutronmomentum dpTT "

    elif [  $anaidC == DUNEEXCL3_CH ]                                                                                           
    then                                                                                                                       
        varray=${commonVar}"protonmomentum protontheta pionEk pionmomentum piontheta baryonmomentum baryontheta baryonmass dpT\
T dpTT20s dpTT10s dpTT5s dpTT2s "
    elif [ $anaidC == LOWRECOILMINERvAGENIEOOB -o $anaidC == LOWRECOILMINERvAGENIEISO  -o $anaidC == LOWRECOILMINERvAGENIEISOw2 ]
    then
        varray=${commonVar}$(echo " " Eav{0,1,2,3,4,5} q3)
    elif [ $anaidC == NUBAR1PIMINERvAGENIEOOB -o $anaidC == NUBAR1PIMINERvAGENIEISO  -o $anaidC == NUBAR1PIMINERvAGENIEISOw2 ]
    then
        varray=${commonVar}" pionEk piontheta pionmomentum"
    elif [ $anaidC == MMECCQEMINERvAMEGENIEOOB ]
    then
        varray=${commonVar}$(echo q2qe muonpt mupz muonptVSmupz mupzVSmuonpt )
# ErecoilTIMES1E3VSmupzVSmuonpt 
#muonpt{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14} mupz{0,1,2,3,4,5,6,7,8,9,10,11,12} 
    else
        echo wrong anaidC $anaidC
        exit
    fi

    echo    
    echo $varray
    echo

    for var in $varray
    do

        echo var $var 
        echo

        root -b -l -q 'getStack4.C("'${finC}'","'${finH}'", "'${anaidC}'","'${anaidH}'","'${tag}'","'${var}'")'

    done #locdirH loop
    done #locdirC loop
done #anaidH loop
done #anaidC loop

echo nfile $nfile

if [ $nfile != 0 ]
then
    cd outStack/${anaid}
    ls *.root
    hadd ${anaid}.root *.root > seemerge.log
fi

done

