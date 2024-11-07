local do_subs = require 'RSUTILS/lua/do_subs'

assert(type(arg) == "table")
local infile  = assert(arg[1])
local outfile = assert(arg[2])
local tmpl_val = assert(arg[3])

local subs = {}
subs.__TMPL__ = tmpl_val

assert(do_subs(infile, outfile, subs))
print("cli_do_subs done ")
