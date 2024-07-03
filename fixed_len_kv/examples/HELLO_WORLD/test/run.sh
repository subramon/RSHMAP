#!/bin/bash
set -e
# START -- These are what you need to provide
git_root="$HOME"  # Set this for your use case
prefix="hw1"      # Set this for your use case
test_files="./test1.c " 
test_exec="test1"
#  STOP -- Above are what you need to provide

cd ..
lua  ${git_root}/RSHMAP/utils/make_project.lua "$git_root" "$prefix"
cd - 
custom_sofile="../lib${prefix}_rs_hmap.so"
generic_sofile="${git_root}/RSHMAP/fixed_len_kv/common/librs_hmap_core.so"
INCS=" -I../inc/ -I../gen_inc/ -I${git_root}/RSHMAP/fixed_len_kv/common/inc/"
gcc ${test_files} \
  $custom_sofile \
  $generic_sofile \
  ${INCS} \
  -o test1 
echo "Created ${test_exec} executable"
./${test_exec}
echo "Successfully completed $0 in $PWD"
