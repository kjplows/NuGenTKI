dir0=$(pwd)

for anaid in GFS0PIMINERvAGiBUULE_CarbonOnly GFSPIZEROMINERvAGiBUULE_CarbonOnly GFSPIZEROMINERvAGENIEv3OOBLE_CarbonOnly GFS0PIMINERvAGENIEv3OOBLE_CarbonOnly 

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

    commonVar="enu muonmomentum muontheta Q2 xBj xrest Wtrue Wrest "

    if [  $anaid == GFS0PIMINERvAGENIEv3OOBLE_CarbonOnly -o $anaid == GFS0PIMINERvAGiBUULE_CarbonOnly ]
    then
        varray=${commonVar}" protonmomentum protontheta dpt dphit dalphat neutronmomentum"
    elif [ $anaid == GFSPIZEROMINERvAGENIEv3OOBLE_CarbonOnly -o $anaid == GFSPIZEROMINERvAGiBUULE_CarbonOnly ]
    then
        varray=${commonVar}" protonmomentum protontheta pionmomentum piontheta pionEk baryonmomentum baryontheta baryonmass dpt dphit dalphat neutronmomentum dpTT "

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

        root -b -l -q 'getStack.C("'${fin}'", "'${anaid}'","'${tag}'","'${var}'")'

    done
done

echo nfile $nfile

if [ $nfile != 0 ]
then
    cd outStack/${anaid}
    ls *.root
    hadd ${anaid}.root *.root > seemerge.log
fi

done


