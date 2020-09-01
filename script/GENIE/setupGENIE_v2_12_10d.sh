#!/bin/bash

echo calling setupGENIE_v2_12_10d.sh 

#all only valid for v2_12_10d -->
source /cvmfs/larsoft.opensciencegrid.org/products/setup
#ups list -aK+ genie | grep v2_12 |grep prof 
#setup genie v2_12_10d -q e17:prof
#ups active
#Active ups products:
setup fftw              v3_3_8          -f Linux64bit+3.10-2.17 -q prof            -z /cvmfs/larsoft.opensciencegrid.org/products
setup gcc               v7_3_0          -f Linux64bit+3.10-2.17                    -z /cvmfs/larsoft.opensciencegrid.org/products
#setup genie             v2_12_10d       -f Linux64bit+3.10-2.17 -q e17:prof        -z /cvmfs/larsoft.opensciencegrid.org/products
setup gsl               v2_5            -f Linux64bit+3.10-2.17 -q prof            -z /cvmfs/larsoft.opensciencegrid.org/products
setup lapack            v3_8_0c         -f Linux64bit+3.10-2.17 -q e17:prof        -z /cvmfs/larsoft.opensciencegrid.org/products
setup lhapdf            v5_9_1k         -f Linux64bit+3.10-2.17 -q e17:prof        -z /cvmfs/larsoft.opensciencegrid.org/products
setup libxml2           v2_9_9          -f Linux64bit+3.10-2.17 -q prof            -z /cvmfs/larsoft.opensciencegrid.org/products
setup log4cpp           v1_1_3b         -f Linux64bit+3.10-2.17 -q e17:prof        -z /cvmfs/larsoft.opensciencegrid.org/products
setup mysql_client      v5_5_62         -f Linux64bit+3.10-2.17 -q e17             -z /cvmfs/larsoft.opensciencegrid.org/products
setup numpy             v1_15_4b        -f Linux64bit+3.10-2.17 -q e17:p2715a:prof -z /cvmfs/larsoft.opensciencegrid.org/products
setup pdfsets           v5_9_1b         -f NULL                                    -z /cvmfs/larsoft.opensciencegrid.org/products
setup postgresql        v9_6_11b        -f Linux64bit+3.10-2.17 -q p2715a          -z /cvmfs/larsoft.opensciencegrid.org/products
setup pythia            v6_4_28p        -f Linux64bit+3.10-2.17 -q gcc730:prof     -z /cvmfs/larsoft.opensciencegrid.org/products
setup python            v2_7_15a        -f Linux64bit+3.10-2.17                    -z /cvmfs/larsoft.opensciencegrid.org/products
setup root              v6_16_00        -f Linux64bit+3.10-2.17 -q e17:prof        -z /cvmfs/larsoft.opensciencegrid.org/products
setup sqlite            v3_26_00_00     -f Linux64bit+3.10-2.17                    -z /cvmfs/larsoft.opensciencegrid.org/products
setup tbb               v2019_3         -f Linux64bit+3.10-2.17 -q e17:prof        -z /cvmfs/larsoft.opensciencegrid.org/products
setup ups               v6_0_8          -f Linux64bit+3.10-2.17                    -z /cvmfs/larsoft.opensciencegrid.org/products
setup xrootd            v4_8_5b         -f Linux64bit+3.10-2.17 -q e17:prof        -z /cvmfs/larsoft.opensciencegrid.org/products
# <--

export PYTHIA6=$PYTHIA6_LIBRARY
export GENIEbase=/minerva/app/users/xlu/software/GENIE
export myGENIE=${GENIEbase}/inuse

export GENIE=${myGENIE}/Generator
export PATH=${myGENIE}/Generator/bin:$PATH
export LD_LIBRARY_PATH=${myGENIE}/Generator/lib:$LD_LIBRARY_PATH
