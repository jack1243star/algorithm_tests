local transform = require("transform")
local ffi = require("ffi")

local IDCT = transform.IDCT

local basis = {}

function basis.create_basis(size)
  local length = size*size

  local input = ffi.new("int[1024]")
  local output = ffi.new("int[1024]")

  local A = {}

  -- iterate through each element
  for i=1,length do
    for j=0,length-1 do
      input[j] = 0
    end
--    input[i-1] = 8192+192+32+16+4+2
    input[i-1] = 8192
    IDCT(input, output, size, size)

    local B = {}
    local l = 1
    for j=0,size-1 do
      for k=0,size-1 do
        B[l] = output[(j*size)+k]
        l = l+1
      end
    end

    A[i] = B
  end

  return A
end

return basis
