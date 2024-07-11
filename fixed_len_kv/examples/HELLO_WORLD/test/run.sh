#!/bin/bash
set -e
# START -- These are what you need to provide
hmap_root="$HOME"  # Set this for your use case
util_root="$HOME"  # Set this for your use case
prefix="hw1"      # Set this for your use case
test_files="./test1.c " 
test_exec="test1"
export LUA_PATH="$util_root/?.lua;;"
echo "LUA_PATH= $LUA_PATH"
#  STOP -- Above are what you need to provide

cd ..
lua  ${hmap_root}/RSHMAP/utils/make_project.lua "$hmap_root" "$util_root" "$prefix"
cd - 
custom_sofile="../lib${prefix}_rs_hmap.so"
generic_sofile="${hmap_root}/RSHMAP/fixed_len_kv/common/librs_hmap_core.so"
INCS=" -I../inc/ -I../gen_inc/ -I${util_root}/RSUTILS/inc/ -I${hmap_root}/RSHMAP/fixed_len_kv/common/inc/"
gcc ${test_files} \
  $custom_sofile \
  $generic_sofile \
  ${INCS} \
  -o test1 
echo "Created ${test_exec} executable"
./${test_exec}
echo "Successfully completed $0 in $PWD"
