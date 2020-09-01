#!/bin/bash

echo calling setupGENIE_v3_00_06.sh

#all only valid for v3_00_06 -->
source /cvmfs/larsoft.opensciencegrid.org/products/setup
#ups list -aK+ genie | grep v3_00_06 |grep prof
##genie" "v3_00_06i" "Linux64bit+3.10-2.17" "e19:prof" "" 
#setup genie v3_00_06i -q e19:prof
#ups active
#Active ups products:
setup fftw              v3_3_8a         -f Linux64bit+3.10-2.17 -q prof            -z /cvmfs/larsoft.opensciencegrid.org/products
setup gcc               v8_2_0          -f Linux64bit+3.10-2.17                    -z /cvmfs/larsoft.opensciencegrid.org/products
#genie             v3_00_06i       -f Linux64bit+3.10-2.17 -q e19:prof        -z /cvmfs/larsoft.opensciencegrid.org/products
setup gsl               v2_5            -f Linux64bit+3.10-2.17 -q prof            -z /cvmfs/larsoft.opensciencegrid.org/products
setup lapack            v3_8_0c         -f Linux64bit+3.10-2.17 -q e19:prof        -z /cvmfs/larsoft.opensciencegrid.org/products
setup lhapdf            v6_2_3d         -f Linux64bit+3.10-2.17 -q e19:p372:prof   -z /cvmfs/larsoft.opensciencegrid.org/products
setup libxml2           v2_9_9          -f Linux64bit+3.10-2.17 -q prof            -z /cvmfs/larsoft.opensciencegrid.org/products
setup log4cpp           v1_1_3b         -f Linux64bit+3.10-2.17 -q e19:prof        -z /cvmfs/larsoft.opensciencegrid.org/products
setup login             v1_6            -f NULL                                    -z /grid/fermiapp/products/common/db
setup mysql_client      v5_5_62         -f Linux64bit+3.10-2.17 -q e19             -z /cvmfs/larsoft.opensciencegrid.org/products
setup numpy             v1_15_4b        -f Linux64bit+3.10-2.17 -q e19:p372:prof   -z /cvmfs/larsoft.opensciencegrid.org/products
setup postgresql        v9_6_11b        -f Linux64bit+3.10-2.17 -q p372            -z /cvmfs/larsoft.opensciencegrid.org/products
setup pythia            v6_4_28p        -f Linux64bit+3.10-2.17 -q gcc820:prof     -z /cvmfs/larsoft.opensciencegrid.org/products
setup python            v3_7_2          -f Linux64bit+3.10-2.17                    -z /cvmfs/larsoft.opensciencegrid.org/products
setup root              v6_18_04d       -f Linux64bit+3.10-2.17 -q e19:prof        -z /cvmfs/larsoft.opensciencegrid.org/products
setup setpath           v1_11           -f NULL                                    -z /grid/fermiapp/products/common/db
setup shrc              v1_10           -f Linux+2                                 -z /grid/fermiapp/products/common/db
setup sqlite            v3_26_00_00     -f Linux64bit+3.10-2.17                    -z /cvmfs/larsoft.opensciencegrid.org/products
setup tbb               v2019_3         -f Linux64bit+3.10-2.17 -q e19:prof        -z /cvmfs/larsoft.opensciencegrid.org/products
setup ups               v6_0_8          -f Linux64bit+3.10-2.17                    -z /cvmfs/larsoft.opensciencegrid.org/products
setup xrootd            v4_8_5c         -f Linux64bit+3.10-2.17 -q e19:prof        -z /cvmfs/larsoft.opensciencegrid.org/products
# <--

export PYTHIA6=$PYTHIA6_LIBRARY
export GENIEbase=/minerva/app/users/xlu/software/GENIE
export myGENIE=${GENIEbase}/inuse

export GENIE=${myGENIE}/Generator
export PATH=${myGENIE}/Generator/bin:$PATH
export LD_LIBRARY_PATH=${myGENIE}/Generator/lib:$LD_LIBRARY_PATH
