local jit = jit

-- Check LuaJIT version
if type(jit) == 'table' then
  print(jit.version)
end

-- Load ffi library
local ffi = require("ffi")

-- Provide C prototype
ffi.cdef[[
void Init ();
unsigned int g_auiZscanToRaster [ 256 ];
unsigned int g_auiRasterToZscan [ 256 ];
unsigned int g_auiRasterToPelX  [ 256 ];
unsigned int g_auiRasterToPelY  [ 256 ];
]]

-- Load the native library (fib.dll)
local scanlib = ffi.load("../lib/scan")
scanlib.Init()

local scan = {}

scan.g_auiZscanToRaster = scanlib.g_auiZscanToRaster
scan.g_auiRasterToZscan = scanlib.g_auiRasterToZscan
scan.g_auiRasterToPelX  = scanlib.g_auiRasterToPelX
scan.g_auiRasterToPelY  = scanlib.g_auiRasterToPelY

return scan