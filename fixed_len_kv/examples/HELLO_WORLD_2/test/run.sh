#!/bin/bash
set -e
#  START -- Following are what you need to provide
hmap_root="$HOME/RSHMAP/"
util_root="$HOME/RSUTILS/"
prefix="hw2"
test_files="./test1.c "
test_exec="test1"
#  STOP -- Above are what you need to provide

export LUA_PATH="$HOME/?.lua;;"
cd ..
lua ../../utils/make_project.lua "$hmap_root" "$util_root" "$prefix"
cd - 

custom_sofile="../lib${prefix}_rs_hmap.so"
generic_sofile="${hmap_root}/fixed_len_kv/common/librs_hmap_core.so"
INCS=" -I../inc/ -I../gen_inc/ -I${util_root}/RSUTILS/inc/ -I${hmap_root}/fixed_len_kv/common/inc/"


gcc ./test_hw2.c \
  $custom_sofile \
  $generic_sofile \
  ${INCS} \
  -o test_hw2
echo "Created test_hw2 executable"
./test_hw2
rm -f _*
echo "Successfully completed $0 in $PWD"
