dir0=$(pwd)

for anaid in GFSPIZEROMINERvAOOBGENIE
#GFSPIZEROMINERvAdcGENIELFGHN
#{RG,DC}
#MMECCQEMINERvAMEGENIEOOB
#GFSPIZEROMINERvAGENIEOOB
#GFSEXP1piT2KGENIEOOB
#
#GFS{0,1}pi{T2K,MINERvA}GENIEOOB
#GFS1piT2KGENIEOOB
#GFS0piT2KGENIEOOB
#
#CLR3GeVGENIEISOw2onsignKNsrc10000000
#CLR3GeVGENIEISOw2onsign
#GFS0piMINERvAGENIEISOw2 GFS1piMINERvAGENIEISOw2 LOWRECOILMINERvAGENIEISOw2 NUBAR1PIMINERvAGENIEISOw2 CLRMINERvAGENIEISOw2 
#GFS0piMINERvAGENIEISO GFS1piMINERvAGENIEISO LOWRECOILMINERvAGENIEISO NUBAR1PIMINERvAGENIEISO 
#GFS0piMINERvAGENIEOOB GFS1piMINERvAGENIEOOB LOWRECOILMINERvAGENIEOOB NUBAR1PIMINERvAGENIEOOB 
#

do

echo
echo "===============================================================" $anaid
cd $dir0

mkdir outStack/${anaid} -p
ls outStack/${anaid}
echo
echo

for locdir in ${anaid}nu{,bar} 
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

    commonVar="muonmomentum muontheta enu Q2 xBj xrest Wtrue Wrest RESmass adlerPhi oobphi lrsign KNsrc "
    #patchcommon=" pseudoPhi pseudosign "
    if [  $anaid == GFSEXP1piT2KGENIEOOB -o $anaid == GFS0piT2KGENIEOOB -o $anaid == GFS0piMINERvAGENIEOOB -o $anaid == GFS1piT2KGENIEOOB -o $anaid == GFS1piMINERvAGENIEOOB -o $anaid == GFSPIZEROMINERvAGENIEOOB -o $anaid == GFSPIZEROMINERvAGENIEOOBw2 ]
    then
        varray=${commonVar}" dphit protonmomentum protontheta dalphat dpt protonTT pionTT neutronmomentum pionEk pionmomentum piontheta baryonmomentum baryontheta baryonmass dpTT lrdpTT lrdpt KNdpt "
    elif [ $anaid ==  GFSPIZEROMINERvARGGENIELFGHN -o $anaid ==  GFSPIZEROMINERvADCGENIELFGHN -o $anaid ==  GFSPIZEROMINERvAdcGENIELFGHN -o $anaid == GFSPIZEROMINERvAOOBGENIE ]
    then
        varray=${commonVar}" dphit protonmomentum protontheta dalphat dpt protonTT pionTT neutronmomentum pionEk pionmomentum piontheta baryonmomentum baryontheta baryonmass dpTT "
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

cd outStack/${anaid}
ls *.root
hadd ${anaid}.root *.root > seemerge.log

done


