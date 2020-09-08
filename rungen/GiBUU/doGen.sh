dir0=$(pwd)

jobid=1
nrepeat=2
#600
#125

for rawjobcard in MINERvALE_nu_T0_Carbon.job
do
    
batchtag=$(basename $rawjobcard | awk -F\. '{print $1}')
echo $batchtag

dirtag=$(dirname $rawjobcard )/output/GiBUU${batchtag}_${jobid}
echo $dirtag

jobcard=$(readlink -f ${rawjobcard})
echo ${jobcard}

gibuuexe=$(readlink -f GiBUU.x)
echo GiBUU exe $gibuuexe
echo GiBUU jobcard $jobcard

for kk in $(seq 1 ${nrepeat})
do
    dir=${dir0}/${dirtag}_out${kk}

    echo ${dir}
    
    mkdir -p ${dir}
        
    cd ${dir}

    cp ${jobcard} .

    jobfile=s${jobid}.sh
###
    cat > ${jobfile} <<EOF

cd ${dir}

    job1="${gibuuexe} < $(basename ${jobcard}) > see_${batchtag}.log"
    echo \$job1

date

    eval \$job1

date
EOF

###
    chmod +x ${jobfile}
        
#120TimeStep
    #qsub -lcput=3:20:00  -N $jobfile  ./$jobfile  #10k runs take 12.5h
#150TimeStep
    #qsub -lcput=4:10:00  -N $jobfile  ./$jobfile  #10k runs take 12.5h
        
    nohup ./$jobfile &

    cd $dir0
    
    jobid=$( expr ${jobid} + 1 )

    echo
done

done

