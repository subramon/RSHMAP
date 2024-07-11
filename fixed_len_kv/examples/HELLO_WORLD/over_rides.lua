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
local over_rides =  {}
for k, v in ipairs(fns_to_over_ride) do 
  over_rides[k] = prefix .. repo .. v .. ".c"
end
return over_rides
