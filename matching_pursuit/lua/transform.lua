local jit = jit

-- Check LuaJIT version
if type(jit) == 'table' then
  print(jit.version)
end

-- Load ffi library
local ffi = require("ffi")

-- Provide C prototype
ffi.cdef[[
void xTrMxN(int bitDepth, int *block, int *coeff, int iWidth, int iHeight, bool useDST, const int maxLog2TrDynamicRange);
void xITrMxN(int bitDepth, int *coeff, int *block, int iWidth, int iHeight, bool useDST, const int maxLog2TrDynamicRange);
]]

-- Load the native library (fib.dll)
local TComTrQuant = ffi.load("../lib/TComTrQuant")
--local partialButterfly8 = TComTrQuant.partialButterfly8
local xTrMxN = TComTrQuant.xTrMxN
local xITrMxN = TComTrQuant.xITrMxN

local transform = {}

function transform.DCT(input, output, width, height)
  xTrMxN(8, input, output, width, height, false, 15)
end

function transform.IDCT(input, output, width, height)
  xITrMxN(8, input, output, width, height, false, 15)
end

return transform