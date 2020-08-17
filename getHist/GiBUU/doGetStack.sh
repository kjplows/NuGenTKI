anaid=GFSPIZEROMINERvAGiBUULE_CarbonOnly

mkdir outStack/${anaid} -p
ls outStack/${anaid}
echo
echo

for locdir in ${anaid}{,nu,nubar}
do
    echo locdir $locdir
    echo
    fin=outplot/${locdir}.root

    if [ ! -e $fin ]
    then
        continue
    fi

    ls $fin
    echo
    tag=$(basename $fin | awk -F\. '{print $1}')
    echo tag $tag
    echo

    commonVar="muonmomentum muontheta enu Q2 xBj xrest Wtrue Wrest "

    if [  $anaid == GFS0PIMINERvAGiBUUPiCut2Fixed -o $anaid == GFS0PIMINERvAGiBUUNOFSIPiCut2Fixed  -o $anaid == GFS0PIMINERvAGiBUURepCleanCodeSubNpiCarbonOnly ]
    then
        varray=${commonVar}"dphit protonmomentum protontheta dalphat dpt neutronmomentum"

    elif [ $anaid == GFS0piMINERvAGiBUU -o $anaid == GFS1piMINERvAGiBUU -o $anaid == GFS0piMMEGiBUU -o $anaid == GFSEXP1piT2KGiBUU -o $anaid == GFSPIZEROMINERvAGiBUU -o $anaid == GFSPIZEROMINERvAGiBUUPiCut2Fixed -o $anaid == GFSPIZEROMINERvAGiBUUNOFSIPiCut2Fixed -o $anaid == GFSPIZEROMINERvAGiBUULE_CarbonOnly ]
    then
# dpTT dpTy  protonTT pionTT 
        varray=${commonVar}"dphit protonmomentum protontheta dalphat dpt neutronmomentum pionEk pionmomentum piontheta baryonmomentum baryontheta baryonmass dpTT"
    elif [  $anaid == DUNEEXCL3_CH ]
    then
        varray=${commonVar}"protonmomentum protontheta pionEk pionmomentum piontheta baryonmomentum baryontheta baryonmass dpTT dpTT20s dpTT10s dpTT5s dpTT2s "
    elif [ $anaid == LOWRECOILMINERvAGiBUU ]
    then
        varray=${commonVar}$(echo eav{0,1,2,3,4,5} q3)
    elif [ $anaid == MINERvAMEGiBUUMMECCQE ]
#MMECCQEMINERvAMEGiBUU ]
    then
        varray=${commonVar}$(echo  q2qe muonpt mupz muonptVSmupz mupzVSmuonpt)
#muonpt{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14} mupz{0,1,2,3,4,5,6,7,8,9,10,11,12}
    elif [ $anaid == NUBAR1PIMINERvAGiBUU ]
    then
        varray=${commonVar}"pionEk piontheta pionmomentum"
    else
        echo wrong anaid $anaid
        exit
    fi

    echo $varray

    #continue

    for var in $varray
    do
        echo var $var 
        echo
    
        root -b -l -q 'getStack.C("'${fin}'", "'${anaid}'","'${tag}'","'${var}'")'

    done
done

cd outStack/${anaid}
ls *.root
hadd ${anaid}.root *.root > seemerge.log


