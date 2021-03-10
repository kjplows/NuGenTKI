date

source ~/setupGENIE.sh

if [ ! -e ${GENIEbase} ]
then
    return
fi

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
tuneTag=G18_10b_00_000
#G18_01a_00_000 #diffractive/lambda production interactions, hA FSI
#G18_01a_02_11a #re-tune free-nucleon xsec model, using bubble-chamber CC1pi, CC2pi, CC-inclusive xsec data
#G18_01b_00_000 #as G18_01a but hN FSI
#G18_01b_02_11a
#G18_02a_00_000 #As G18_01a, updated Berger-Sehgal for RES,COH
#G18_02a_02_11a
#G18_02b_00_000 #As G18_01b
#G18_02b_02_11a
#G18_10a_00_000 #Similar to G18_02a. LFG. Nieves for CCQE, 2p2h
#G18_10a_02_11a 
#G18_10b_00_000 #Similar to G18_02b.
#G18_10b_02_11a
#G18_10i_00_000 #Similat to G18_10a. Axial param z-exp.
#G18_10j_00_000 #Similar to G18_10b.

tmpGENIEtune=$(echo $tuneTag|tr -d '_')
splineroot=$(readlink -f $(find ${GENIEspline}| grep $tmpGENIEtune | grep .root))
splinefile=$(readlink -f $(find ${GENIEspline}| grep $tmpGENIEtune | grep small))
echo tuneTag $tuneTag
echo tmpGENIEtune $tmpGENIEtune
echo GENIEspline $GENIEspline
echo splineroot $splineroot
echo splinefile $splinefile

if [ -z ${splinefile} ]
then
    echo null splinefile!!
    exit
fi

#######################################
## Accessing the unofficial anti-numu RHC playlist-6A flux
export MYPLOTUTILS="/minerva/app/users/kplows/cmtuser/Minerva_v22r1p1_kplows_publicfluxes/Ana/PlotUtils"
export MYFLUXFILES=$MYPLOTUTILS"/data/flux/ME_fluxes_for_generators"
#######################################

model=" --event-generator-list Default+CCMEC "

aaa=V3MEBAR_H_NOFSI
#V3LEBAR
#V3LE
#V3ME
#v2TJ
#v2DC
#V2RG
#v3OOB

jobid=k1${aaa}

GENIETAG="GENIE_${aaa}_Tune${tuneTag}"
#"GENIE_${aaa}_Tune${tuneTag}"

nevt=500000 #with 2 jobs this is fine comrade
#20000
#200000
#10
#

for imultiple in $( seq 1 2) #JOHN YOU SHOULD NEVER RUN MORE THAN 4 PROCESSES ON A GPVM
#Use the batch system for more jobs. So gotta figure that out. 
#$( seq 1 2) 
#
do
    for enu in ${MME}
#${MINERVA_LE}
# ${MME}
#${DUNE}
#2400 800
#${T2K}
#3000
#600 3000 6000
    do

        for beam in $NUBAR
#$NUUUU 
#$NUBAR
        do

        for target in Hydrogen
#Hydrogen
#Carbon
#CH
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
	    #output/job$jobid/$tag
        
            mkdir -p $dir
            cd $dir
            pwd
        
        
            jobfile=${jobid}n$(printf "%03d" $ii).sh
        
            localseed=$(printf "%d%d%03d" "'${jobid:0:1}" ${jobid:1:1} $ii )
        
            if [ $enu == ${MINERVA_LE} ]
            then

                if [ $beam == ${NUUUU} ]
                then
                    energyTerm="-e 0,100 -f ${GENIEbase}/flux/minerva_flux.root,numu_fhc"
                else
                    energyTerm="-e 0,100 -f ${GENIEbase}/flux/minerva_flux.root,numubar_rhc"
                fi

            elif [ $enu == ${MME} ]
            then
                if [ $beam == ${NUUUU} ]
                then
                    energyTerm="-e 0,100 -f ${MYFLUXFILES}/Unofficial_NumuMEFlux_NueConstrained.root,flux_E_cvweighted_CV_WithStatErr"
		    #"-e 0,100 -f ${GENIEbase}/flux/Unofficial_NumuMEFlux_NueConstrained.root,flux_E_cvweighted_CV_WithStatErr"
                else
		    if [ ! -e ${MYFLUXFILES} ]
		    then
			echo "MYFLUXFILES not found at ${MYFLUXFILES}"
		    fi
		    energyTerm="-e 0,100 -f ${MYFLUXFILES}/flux-gen2thin-minervame6A_root5.root,flux_E_cvweighted_CV_WithStatErr"
		    #idea is I just want to make a chi ME prediction for now, can always run FluxReweighter (with eroica?) and save that first..
                    #echo "No MINERvA ME for anti-neutrino!"
                    return
                fi

            elif [ $enu == ${T2K} ]
            then
                if [ $beam == ${NUUUU} ]
                then
                    energyTerm="-e 0,100 -f ${GENIEbase}/flux/T2K/t2kflux_2016_plus250kA.root,enu_nd280_numu"
                else
                    energyTerm="-e 0,100 -f ${GENIEbase}/flux/T2K/t2kflux_2016_minus250kA.root,enu_nd280_numub"
                fi

            elif [ $enu == ${DUNE} ]
            then 
                if [ $beam == ${NUUUU} ]
                then
                    energyTerm="-e 0,100 -f ${GENIEbase}/flux/DUNE/histos_g4lbne_v3r5p4_QGSP_BERT_OptimizedEngineeredNov2017_neutrino_LBNEND_fastmc.root,numu_flux"
                else
                    energyTerm="-e 0,100 -f ${GENIEbase}/flux/DUNE/histos_g4lbne_v3r5p4_QGSP_BERT_OptimizedEngineeredNov2017_antineutrino_LBNEND_fastmc.root,numubar_flux"
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

            #cmd="gevgen -n $nevt ${energyTerm} ${nuTerm} -t $tgt --seed ${localseed} --cross-sections ${GENIEbase}/gxspl.xml -o output${tag}.root --event-generator-list Default+CCMEC > seeEvgen${tag}.log; tail -n 150 seeEvgen${tag}.log > tmp; mv tmp seeEvgen${tag}.log; gntpc -i output${tag}.root -f rootracker > seeNtpc${tag}.log; tail -n 150 seeNtpc${tag}.log > tmp; mv tmp seeNtpc${tag}.log"

            #for RES there is no 2p2h
            #echo; echo; echo NO MEC!!!; echo; echo; echo
            #cmd="gevgen -n $nevt ${energyTerm} ${nuTerm} -t $tgt --seed ${localseed} --cross-sections ${GENIEbase}/gxspl.xml -o output${tag}.root --event-generator-list Default > seeEvgen${tag}.log; tail -n 150 seeEvgen${tag}.log > tmp; mv tmp seeEvgen${tag}.log; gntpc -i output${tag}.root -f rootracker > seeNtpc${tag}.log; tail -n 150 seeNtpc${tag}.log > tmp; mv tmp seeNtpc${tag}.log"

            #cmd="gevgen ${model} -n $nevt ${energyTerm} ${nuTerm} -t $tgt --seed ${localseed} --cross-sections $(readlink -f ${GENIEbase}/inuse/spline/gxspl-FNALsmall.xml) -o output${tag}.root  > seeEvgen${tag}.log; tail -n 150 seeEvgen${tag}.log > tmp; mv tmp seeEvgen${tag}.log; gntpc -i output${tag}.root -f rootracker > seeNtpc${tag}.log; tail -n 150 seeNtpc${tag}.log > tmp; mv tmp seeNtpc${tag}.log"

            #cmd="ln -s ${splineroot}; gevgen ${model} --tune ${tuneTag} -n $nevt ${energyTerm} ${nuTerm} -t $tgt --seed ${localseed} --cross-sections ${splinefile} -o output${tag}.root  > seeEvgen${tag}.log; gntpc --tune ${tuneTag} -i output${tag}.root -f rootracker > seeNtpc${tag}.log"
            

	    cmd="ln -s ${splineroot}; gevgen ${model} --tune ${tuneTag} -n $nevt ${energyTerm} ${nuTerm} -t $tgt --seed ${localseed} --cross-sections ${splinefile} -o output${tag}.root  > seeEvgen${tag}.log; tail -n 150 seeEvgen${tag}.log > tmp; mv tmp seeEvgen${tag}.log; gntpc --tune ${tuneTag} -i output${tag}.root -f rootracker > seeNtpc${tag}.log; tail -n 150 seeNtpc${tag}.log > tmp; mv tmp seeNtpc${tag}.log"

	    dirdat=/minerva/data/users/kjp/GENIE/genGENIE/job$jobid

	    #cmd2="mkdir -p ${dirdat}; cd ..; mv ${tag} ${dirdat}; rm -r ${tag};"

                
            echo $cmd
            echo
	    #echo $cmd2
	    echo
        
            cat > $jobfile <<EOF

source $(readlink -f ~/setupGENIE.sh)

cd $(pwd)

date

${cmd}

date

EOF
            
            chmod +x $jobfile
        
        
           # condor_qsub -l cput=04:00:00 -N $jobfile  ./$jobfile 
            
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
