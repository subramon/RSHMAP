local plpath  = require 'pl.path'
local plfile  = require 'pl.file'

local qcflags = [[ -std=gnu99  -fPIC      -O3  -Wall -W -Waggregate-return -Wcast-align -Wmissing-prototypes -Wnested-externs -Wshadow -Wwrite-strings -Wunused-variable  -Wunused-parameter -Wno-pedantic -fopenmp -Wno-unused-label  -Wmissing-declarations -Wredundant-decls -Wnested-externs  -Wstrict-prototypes -Wmissing-prototypes -Wpointer-arith  -Wshadow -Wcast-qual -Wcast-align -Wwrite-strings  -Wold-style-definition -Wsuggest-attribute=noreturn ]]

local is_in = require 'Q/UTILS/lua/is_in'
local exec = require 'Q/UTILS/lua/exec_and_capture_stdout'
local do_subs = require 'Q/UTILS/lua/do_subs'
local extract_func_decl = require 'Q/UTILS/lua/extract_func_decl'

assert(type(arg) == "table")

local git_root = assert(arg[1])
local tmpl_val = assert(arg[2])
assert(plpath.isdir(git_root))
assert(#tmpl_val > 0)

local root_dir = git_root .. "/RSHMAP/fixed_len_kv"
local src_tmpl_dir = root_dir .. "/src/"
local inc_tmpl_dir = root_dir .. "/inc/"

local incs = "-I./inc/ -I./gen_inc/ -I" .. root_dir .. "/common/inc/ "
local optional_src_files = require 'optional_files' 
-- TODO Do more testing of optional files 
assert(type(optional_src_files) == "table")
--= START checks 
mandatory_inc_files =  {
  tmpl_val .. "_rs_hmap_types.h", 
}

local gen_inc_files = {
  "rs_hmap_struct.h",
}
-- These files need to be created in gen_src/ directory 
local gen_src_files = {
  "rs_hmap_chk.c",
  "rs_hmap_del.c",
  "rs_hmap_destroy.c",
  "rs_hmap_freeze.c",
  "rs_hmap_get.c",
  "rs_hmap_insert.c",
  "rs_hmap_instantiate.c",
  "rs_hmap_key_cmp.c",
  "rs_hmap_pr.c",
  "rs_hmap_pr_key.c",
  "rs_hmap_pr_val.c",
  "rs_hmap_put.c",
  "rs_hmap_resize.c",
  "rs_hmap_set_hash.c",
  "rs_hmap_unfreeze.c",
  "rs_hmap_val_update.c",
}

-- Remove files where user wants to over-ride default implementation
local T = {}
for _, v in ipairs(gen_src_files) do 
  local x = tmpl_val .. "_" .. v
  if ( is_in(x, optional_src_files) ) then
    print("Not using default file " .. v)
  else
    T[#T+1] = v
  end
end
gen_src_files = T 


--=  STOP checks 

assert(plpath.isdir("./inc/"))
assert(plpath.isdir("./src/"))
if ( not plpath.isdir("./gen_inc/") ) then plpath.mkdir("./gen_inc/") end
if ( not plpath.isdir("./gen_src/") ) then plpath.mkdir("./gen_src/") end

--[[
for k, v in pairs(optional_src_files) do 
  local src_file = "./src/" .. v
  assert(plpath.isfile(src_file), "File not found " .. src_file)
end
--]]

assert(type(mandatory_inc_files) == "table")
for k, v in pairs(mandatory_inc_files) do 
  local filename = "./inc/" .. v
  assert(plpath.isfile(filename), "File not found " .. filename)
end

-- generate files 
local subs = {}
subs.__TMPL__ = tmpl_val

for k, v in pairs(gen_inc_files) do 
  local from = inc_tmpl_dir .. v 
  assert(plpath.isfile(from), "File not found " .. from)
  local to = "./gen_inc/" .. tmpl_val .. "_" .. v 
  plfile.delete(to)
  assert(do_subs(from, to, subs))
end
-- generate .c files 
for k, v in pairs(gen_src_files) do 
  local from = src_tmpl_dir .. v 
  assert(plpath.isfile(from), "File not found " .. from)
  local to = "./gen_src/" .. tmpl_val .. "_" .. v 
  plfile.delete(to)
  assert(do_subs(from, to, subs))
end
-- generate function declarations
for k, v in pairs(optional_src_files) do 
  local from = "./src/" .. v 
  local to   = "./gen_inc/" .. v
        to   = string.gsub(to, "%.c", ".h")
  plfile.delete(to)
  local status = extract_func_decl(from, "./gen_inc/")
  if ( not status ) then 
    error("Unable to  generate function declaration for " .. from)
  else
    print("Created function declaration for " .. from)
  end
end
-- generate function declarations
for k, v in pairs(gen_src_files) do 
  local from = "./gen_src/" .. tmpl_val .. "_" .. v 
  local to   = string.gsub(from, "gen_src", "gen_inc")
        to   = string.gsub(to, "%.c", ".h")
  plfile.delete(to)
  local status = extract_func_decl(from, "./gen_inc/")
  if ( not status ) then 
    error("Unable to  generate function declaration for " .. from)
  end
end
-- generate .o files 
local dotos = {}
for k, v in pairs(gen_src_files) do 
  local dotc = "./gen_src/" .. tmpl_val .. "_" .. v 
  local doto = string.gsub(dotc, "%.c", ".o")
  assert(plpath.isfile(dotc), "File not found " .. dotc)
  plfile.delete(doto)
  local q_cmd = string.format("gcc -c %s %s %s -o %s",
         qcflags, incs, dotc, doto)
  print("Creating " .. doto)
  assert(exec(q_cmd), q_cmd)
  assert(plpath.isfile(doto), "File not found " .. doto)
  dotos[#dotos +1] = doto
end
for k, v in pairs(optional_src_files) do 
  local dotc = "./src/" .. v
  local doto = string.gsub(dotc, "%.c", ".o")
  assert(plpath.isfile(dotc), "File not found " .. dotc)
  plfile.delete(doto)
  local q_cmd = string.format("gcc -c %s %s %s -o %s",
         qcflags, incs, dotc, doto)
  print("Creating " .. doto)
  assert(exec(q_cmd), q_cmd)
  assert(plpath.isfile(doto), "File not found " .. doto)
  dotos[#dotos +1] = doto
end
-- Create .so file 
dotos = table.concat(dotos, " ")
local sofile = "lib" .. tmpl_val .. "_rs_hmap.so"
local q_cmd = string.format("gcc -shared %s -o %s",
         dotos, sofile)
plfile.delete(sofile)
print("Creating " .. sofile)
assert(exec(q_cmd), q_cmd)
assert(plpath.isfile(sofile), "File not found " .. sofile)
print("DONE")

