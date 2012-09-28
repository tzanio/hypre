#!/bin/sh
#BHEADER**********************************************************************
# Copyright (c) 2008,  Lawrence Livermore National Security, LLC.
# Produced at the Lawrence Livermore National Laboratory.
# This file is part of HYPRE.  See file COPYRIGHT for details.
#
# HYPRE is free software; you can redistribute it and/or modify it under the
# terms of the GNU Lesser General Public License (as published by the Free
# Software Foundation) version 2.1 dated February 1999.
#
# $Revision$
#EHEADER**********************************************************************




testname=`basename $0 .sh`

# Echo usage information
case $1 in
   -h|-help)
      cat <<EOF

   **** Only run this script on one of the tux machines. ****

   $0 [-h|-help] {src_dir}

   where: {src_dir}  is the hypre source directory
          -h|-help   prints this usage information and exits

   This script runs a number of tests suitable for the tux machines.

   Example usage: $0 ..

EOF
      exit
      ;;
esac

# Setup
test_dir=`pwd`
output_dir=`pwd`/$testname.dir
rm -fr $output_dir
mkdir -p $output_dir
src_dir=$1
shift

# Test runtest tests with debugging and insure turned on
./test.sh debug.sh $src_dir --with-insure
mv -f debug.??? $output_dir

# Test examples
./test.sh examples.sh $src_dir/examples
mv -f examples.??? $output_dir

# Test babel build (only if 'babel-runtime' directory is present)
if [ -d $src_dir/babel-runtime ]; then
   opt="--with-babel"
   output_subdir="$output_dir/build--with-babel"
   mkdir -p $output_subdir
   ./test.sh configure.sh $src_dir $opt
   mv -f configure.??? $output_subdir
   ./test.sh make.sh $src_dir test
   mv -f make.??? $output_subdir
fi

# Test other builds (last one is the default build)
# temporarily change word delimeter in order to have spaces in options
tmpIFS=$IFS
IFS=:
configure_opts="--without-MPI:--with-strict-checking:--enable-shared:--with-no-global-partition --enable-debug: "
for opt in $configure_opts
do
   # only use first part of $opt for subdir name
   output_subdir=$output_dir/build`echo $opt | awk '{print $1}'`
   mkdir -p $output_subdir
   ./test.sh configure.sh $src_dir $opt
   mv -f configure.??? $output_subdir
   ./test.sh make.sh $src_dir test
   mv -f make.??? $output_subdir
done
IFS=$tmpIFS

# Test linking for different languages
link_opts="all++ all77"
for opt in $link_opts
do
   output_subdir=$output_dir/link$opt
   mkdir -p $output_subdir
   ./test.sh link.sh $src_dir $opt
   mv -f link.??? $output_subdir
done

# Run tests with --enable-bigint configured
opt="--enable-bigint --enable-debug"
output_subdir="$output_dir/run--enable-bigint"
mkdir -p $output_subdir
./test.sh configure.sh $src_dir $opt
mv -f configure.??? $output_subdir
./test.sh make.sh $src_dir test
mv -f make.??? $output_subdir
./test.sh run.sh $src_dir
mv -f run.??? $output_subdir

# Test documentation build (only if 'docs_misc' directory is present)
if [ -d $src_dir/docs_misc ]; then
   ./test.sh docs.sh $src_dir
   mv -f docs.??? $output_dir
fi

# Check for 'int' and 'MPI_'
./test.sh check-int.sh $src_dir
mv -f check-int.??? $output_dir
./test.sh check-mpi.sh $src_dir
mv -f check-mpi.??? $output_dir

# Echo to stderr all nonempty error files in $output_dir
for errfile in $( find $output_dir ! -size 0 -name "*.err" )
do
   echo $errfile >&2
done
