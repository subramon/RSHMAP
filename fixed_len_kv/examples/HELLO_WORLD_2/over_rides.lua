local prefix = "hw2"
local repo = "_rs_hmap_" 
local fns_to_over_ride = {
  "key_cmp", 
  -- "pr", -- will keep default  
  "pr_key", 
  "pr_val", 
  -- "set_hash",  -- will keep default 
  "val_update", 
}
local ove_rides =  {}
for k, v in ipairs(fns_to_over_ride) do 
  ove_rides[k] = prefix .. repo .. v .. ".c"
end
return ove_rides
