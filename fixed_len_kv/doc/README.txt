# Decide on a prefix. This should be unique. 
prefix="foo"
# Use HELLO_WORLD/ as a template

GIT_ROOT=$HOME # This is directory where you have checked out RSHMAP
rm -rf ${prefix}/
cp -r $GIT_ROOT/fixed_len_kv/examples/HELLO_WORLD/ ${prefix}
cd ${prefix}/
rm -rf gen_inc/*.h
rm -rf gen_src/*.h
rm -rf src/*.o
rm -rf *.so
cd ${prefix}/inc
mv hw1_rs_hmap_key_type.h ${prefix}_rs_hmap_key_type.h
mv hw1_rs_hmap_val_type.h ${prefix}_rs_hmap_val_type.h
# Edit the above files to create the key/value you want 

# If you want to over-ride any of the default implementations,
# specify them in ${prefix}/over_rides.lua
# The files that you can over-write are 

# 1) ${prefix}_rs_hmap_val_update.c
# 2) ${prefix}_key_cmp.c
# 3) ${prefix}_pr_key.c
# 4) ${prefix}_pr_val.c
# 5) ${prefix}_pr.c
# Note that the function signature should match that in 
# $GIT_ROOT/fixed_len_kv/src/
# Execute the following to make sure things work
lua  ${GIT_ROOT}/RSHMAP/utils/make_project.lua ${GIT_ROOT} ${prefix}


=================== Testing ==================
Modify run.sh as needed
