date

################################################################################################
#ii has to be outside the loop
ii=1

#1000010010 [   H1]
#1000060120 [  C12]
TGT_H=1000010010
TGT_C=1000060120

#Standard atomic weight (±)39.948(1)[1]
#1000180400 [ Ar40]
TGT_AR=1000180400

#1000080160 [  O16]
TGT_O=1000080160

#1000260560 [ Fe56]
TGT_FE=1000260560

#Standard atomic weight (±)207.2(1)[1]
#1000822070 [Pb207]
TGT_PB=1000822070

MINERVA_LE="MINERvA"
MME="MME"

T2K="T2K"

DUNE="DUNE"

NUUUU="Nu"
NUBAR="Nubar"

################################################################################################
aaa=V2
jobid=c1${aaa}
#x3

GENIETAG="GENIEOOB_${aaa}"
#"GENIE2LFGHN_${aaa}"
#"GENIEISO"

nevt=100000
#1000
#5000
#100000
#10000

for imultiple in $( seq 1 10) 
#$( seq 1 100 ) 
#$( seq 1 300 ) 
#$( seq 1 1000 )  
do
    for enu in ${MINERVA_LE} 
#${DUNE}
#2400 800
#${T2K}
#${MME}
#3000
#600 3000 6000
    do

        for beam in $NUUUU 
#$NUBAR
#
#
        do

        for target in Carbon
#CH
#Carbon
#Hydrogen
#P50
#$(echo Carbon Oxygen Lead Iron Argon Hydrogen )
#CH )
# Hydrogen Carbon)
        do

################################################################################################

        echo $enu $beam
        

            if [ $target == Hydrogen ]
            then
                tgt=$TGT_H
                
            elif [ $target == Carbon ]
            then
                tgt=$TGT_C
                
            elif [ $target == CH ]
            then
                tgt=$TGT_H"["$(echo "scale = 10; 1/13" |bc)"],"$TGT_C"["$(echo "scale = 10; 12/13" |bc)"]"
            elif [ $target == P50 ] 
            then
                tgt=$TGT_H"["$(echo "scale = 10; 4/56" |bc)"],"$TGT_C"["$(echo "scale = 10; 12/56" |bc)"],"$TGT_AR"["$(echo "scale = 10; 40/56" |bc)"]"
            elif [ $target == Oxygen ]
            then
                tgt=$TGT_O
            elif [ $target == Lead ]
            then
                tgt=$TGT_PB
            elif [ $target == Iron ]
            then 
                tgt=$TGT_FE
            elif [ $target == Argon ]
            then
                tgt=$TGT_AR
            else
                echo bad target $target
                exit
            fi

            tag=ii$(printf "%03d" $ii)_${GENIETAG}_Beam${beam}_Enu${enu}_Target${target}
        
            dir=job$jobid/$tag
        
            mkdir -p $dir
            cd $dir
            pwd
        
        
            jobfile=${jobid}n$(printf "%03d" $ii).sh
        
            localseed=$(printf "%d%d%03d" "'${jobid:0:1}" ${jobid:1:1} $ii )
        
            if [ $enu == ${MINERVA_LE} ]
            then

                if [ $beam == ${NUUUU} ]
                then
                    energyTerm="-e 0,100 -f /data/t2k/xlu/software/GENIE/flux/minerva_flux.root,numu_fhc"
                    ###energyTerm="-e 0,100 -f /data/t2k/coplowe/flux_files/MINERvAflux2013/numi_flux_nu_fhc.root,flux_E_cvweighted_CV_WithErr"
                else
                    energyTerm="-e 0,100 -f /data/t2k/xlu/software/GENIE/flux/minerva_flux.root,numubar_rhc"
                fi

            elif [ $enu == ${MME} ]
            then
                if [ $beam == ${NUUUU} ]
                then
                    energyTerm="-e 0,100 -f /data/t2k/xlu/software/GENIE/flux/Unofficial_NumuMEFlux_NueConstrained.root,flux_E_cvweighted_CV_WithStatErr"
                else
                    echo "No MINERvA ME for anti-neutrino!"
                    return
                fi

            elif [ $enu == ${T2K} ]
            then
                if [ $beam == ${NUUUU} ]
                then
                    energyTerm="-e 0,100 -f /data/t2k/xlu/software/GENIE/flux/T2K/t2kflux_2016_plus250kA.root,enu_nd280_numu"
                else
                    energyTerm="-e 0,100 -f /data/t2k/xlu/software/GENIE/flux/T2K/t2kflux_2016_minus250kA.root,enu_nd280_numub"
                fi

            elif [ $enu == ${DUNE} ]
            then 
                if [ $beam == ${NUUUU} ]
                then
                    energyTerm="-e 0,100 -f /data/t2k/xlu/software/GENIE/flux/DUNE/histos_g4lbne_v3r5p4_QGSP_BERT_OptimizedEngineeredNov2017_neutrino_LBNEND_fastmc.root,numu_flux"
                else
                    energyTerm="-e 0,100 -f /data/t2k/xlu/software/GENIE/flux/DUNE/histos_g4lbne_v3r5p4_QGSP_BERT_OptimizedEngineeredNov2017_antineutrino_LBNEND_fastmc.root,numubar_flux"
                fi
            else            
            
                tmpEnergy=$(echo "scale = 3; $enu/1000" |bc)
                energyTerm="-e ${tmpEnergy}";

            fi

            if [ $beam == ${NUUUU} ]
            then
                nuTerm="-p 14"
            else
                nuTerm="-p -14"
            fi

            #cmd="gevgen -n $nevt ${energyTerm} ${nuTerm} -t $tgt --seed ${localseed} --cross-sections /data/t2k/xlu/software/GENIE/gxspl.xml -o output${tag}.root --event-generator-list Default+CCMEC > seeEvgen${tag}.log; tail -n 150 seeEvgen${tag}.log > tmp; mv tmp seeEvgen${tag}.log; gntpc -i output${tag}.root -f rootracker > seeNtpc${tag}.log; tail -n 150 seeNtpc${tag}.log > tmp; mv tmp seeNtpc${tag}.log"

            #for RES there is no 2p2h
            #echo; echo; echo NO MEC!!!; echo; echo; echo
            #cmd="gevgen -n $nevt ${energyTerm} ${nuTerm} -t $tgt --seed ${localseed} --cross-sections /data/t2k/xlu/software/GENIE/gxspl.xml -o output${tag}.root --event-generator-list Default > seeEvgen${tag}.log; tail -n 150 seeEvgen${tag}.log > tmp; mv tmp seeEvgen${tag}.log; gntpc -i output${tag}.root -f rootracker > seeNtpc${tag}.log; tail -n 150 seeNtpc${tag}.log > tmp; mv tmp seeNtpc${tag}.log"

             cmd="gevgen -n $nevt ${energyTerm} ${nuTerm} -t $tgt --seed ${localseed} --cross-sections $(readlink -f /data/t2k/xlu/software/GENIE/inuse/spline/gxspl-FNALsmall.xml) -o output${tag}.root  > seeEvgen${tag}.log; tail -n 150 seeEvgen${tag}.log > tmp; mv tmp seeEvgen${tag}.log; gntpc -i output${tag}.root -f rootracker > seeNtpc${tag}.log; tail -n 150 seeNtpc${tag}.log > tmp; mv tmp seeNtpc${tag}.log"
                
            echo $cmd
            echo
        
            cat > $jobfile <<EOF

source $(readlink -f ~/setupGENIE.sh)

cd $(pwd)

date

#echo UserPhysicsOptions.xml $(readlink -f /data/t2k/xlu/software/GENIE/UserPhysicsOptions.xml)

${cmd}

date

EOF
            
            chmod +x $jobfile
        
        
            #condor_qsub -l cput=04:00:00 -N $jobfile  ./$jobfile 
            
            cat > myjob.submit <<EOF
executable              = ${jobfile}
getenv                  = true
output                  = results.output.\$(ClusterId)
error                   = results.error.\$(ClusterId)
log                     = results.log.\$(ClusterId)
notification            = never
queue 1
EOF

            #condor_submit myjob.submit

            nohup ./$jobfile &

            cd -
        
            ii=$( expr $ii + 1 )

        done
        
        done

    done

done

date
