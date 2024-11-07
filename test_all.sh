#!/bin/bash
set -e
cd fixed_len_kv//examples/HELLO_WORLD/test/
bash run.sh 
cd -
#------------------------
cd fixed_len_kv//examples/HELLO_WORLD_2/test/
bash run.sh 
cd -
#------------------------
echo "Successfully completed $0 in $PWD"
