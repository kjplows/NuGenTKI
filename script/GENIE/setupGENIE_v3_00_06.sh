#!/bin/bash

echo calling setupGENIE_v3_00_06.sh

#all only valid for v3_00_06 -->
source /cvmfs/larsoft.opensciencegrid.org/products/setup
#ups list -aK+ genie | grep v3_00_06 |grep prof | grep e17
##enie" "v3_00_06d" "Linux64bit+3.10-2.17" "e17:prof" "" 
#setup genie v3_00_06d -q e17:prof
#ups active
#Active ups products:

setup clhep             v2_3_4_6        -f Linux64bit+3.10-2.17 -q e17:prof        -z /cvmfs/larsoft.opensciencegrid.org/products
setup fftw              v3_3_6_pl2      -f Linux64bit+3.10-2.17 -q prof            -z /cvmfs/larsoft.opensciencegrid.org/products
setup gcc               v7_3_0          -f Linux64bit+3.10-2.17                    -z /cvmfs/larsoft.opensciencegrid.org/products
setup gsl               v2_4            -f Linux64bit+3.10-2.17 -q prof            -z /cvmfs/larsoft.opensciencegrid.org/products
setup lhapdf            v5_9_1k         -f Linux64bit+3.10-2.17 -q e17:prof        -z /cvmfs/larsoft.opensciencegrid.org/products
setup libxml2           v2_9_5          -f Linux64bit+3.10-2.17 -q prof            -z /cvmfs/larsoft.opensciencegrid.org/products
setup log4cpp           v1_1_3a         -f Linux64bit+3.10-2.17 -q e17:prof        -z /cvmfs/larsoft.opensciencegrid.org/products
setup mysql_client      v5_5_58a        -f Linux64bit+3.10-2.17 -q e17             -z /cvmfs/larsoft.opensciencegrid.org/products
setup pdfsets           v5_9_1b         -f NULL                                    -z /cvmfs/larsoft.opensciencegrid.org/products
setup postgresql        v9_6_6a         -f Linux64bit+3.10-2.17 -q p2714b          -z /cvmfs/larsoft.opensciencegrid.org/products
setup pythia            v6_4_28k        -f Linux64bit+3.10-2.17 -q gcc730:prof     -z /cvmfs/larsoft.opensciencegrid.org/products
setup python            v2_7_14b        -f Linux64bit+3.10-2.17                    -z /cvmfs/larsoft.opensciencegrid.org/products
setup root              v6_12_06a       -f Linux64bit+3.10-2.17 -q e17:prof        -z /cvmfs/larsoft.opensciencegrid.org/products
setup sqlite            v3_20_01_00     -f Linux64bit+3.10-2.17                    -z /cvmfs/larsoft.opensciencegrid.org/products
setup tbb               v2018_2a        -f Linux64bit+3.10-2.17 -q e17:prof        -z /cvmfs/larsoft.opensciencegrid.org/products
setup xrootd            v4_8_0b         -f Linux64bit+3.10-2.17 -q e17:prof        -z /cvmfs/larsoft.opensciencegrid.org/products

# <--

export PYTHIA6=$PYTHIA6_LIBRARY

export GENIEbase=/minerva/app/users/xlu/software/GENIE
export myGENIE=${GENIEbase}/inuse

#only needed for v3
export LHAPATH=${myGENIE}/GENIESupport/lhapdfv5

export GENIE=${myGENIE}/Generator
export PATH=${myGENIE}/Generator/bin:$PATH
export LD_LIBRARY_PATH=${myGENIE}/Generator/lib:$LD_LIBRARY_PATH
