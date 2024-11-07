local extract_func_decl = require 'RSUTILS/lua/extract_func_decl'

assert(type(arg) == "table")
local infile = assert(arg[1])
local opdir  = assert(arg[2])


assert(extract_func_decl(infile, opdir))
print("DONE")
