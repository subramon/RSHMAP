#!/bin/bash
set -e
cd ..
git_root="../../../../.."
git_root="$HOME"
tmpl="hw2"
lua  ../../../utils/make_project.lua "$git_root" "$tmpl"
cd - 
gcc ./test_hw2.c \
  ../libhw2_rs_hmap.so ../../../common/librs_hmap_core.so \
  -I../inc/ -I../gen_inc/ -I../../../common/inc/ \
  -o test_hw2
echo "Created test_hw2 executable"
./test_hw2
rm -f _*
echo "Successfully completed $0 in $PWD"
