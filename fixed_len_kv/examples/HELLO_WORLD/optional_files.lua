local prefix = "hw1"
local repo = "_rs_hmap_" 
local fns_to_over_ride = {
  "key_cmp", 
  "pr", 
  "pr_key", 
  "pr_val", 
  "set_hash", 
  "val_update", 
}
local optional_src_files =  {}
for k, v in ipairs(fns_to_over_ride) do 
  optional_src_files[k] = prefix .. repo .. v .. ".c"
end
return optional_src_files
