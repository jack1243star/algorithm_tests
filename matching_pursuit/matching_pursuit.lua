local ffi = require("ffi")

local transform = require("transform")
local DCT = transform.DCT
local IDCT = transform.IDCT

local basis = require("basis")
local A = basis.create_basis(8)

local function bpb(bb, mask, ep, iterations)
  if #bb ~= #mask then
    error("bb and mask differ in size")
  end

  local tbs = math.sqrt(#bb)

  -- 2D basis functions as rows of A
  -- local A = basis.create_basis(tbs)

  -- Output transform coefficients
  local yt = {}
  for i=1,#bb do yt[i] = 0 end

  -- Masked block
  local xt = {}
  for i=1,#bb do xt[i] = bb[i] * mask[i] end

  -- Sum of mask
  local ml = 0
  for i=1,#mask do ml = ml + mask[i] end

  -- Mean square error
  -- err = sum(sum((bb.*mask).^2))/ml;
  local err = 0
  for i=1,#bb do err = err + math.pow(bb[i] * mask[i],2) end
  err = err / ml
  print("    err = "..err)
  print("- - - - - - - -")

  local xt_c = ffi.new("int[1024]", xt)
  local yt_c = ffi.new("int[1024]", yt)
  local tmp_c = ffi.new("int[1024]")
  local output_c = ffi.new("int[1024]")

  local tries = 0
  while err > ep
--  and tries < iterations
  do
    tries = tries + 1

    -- tmp=dct(dct(xt)')';
    DCT(xt_c, tmp_c, tbs, tbs)


--  [dummy ix]=max(abs(tmp(:)));
    local ix
    local maximum = -5e+20
    for i=0,#bb-1 do
      if math.abs(tmp_c[i]) > maximum then
        ix = i
        maximum = math.abs(tmp_c[i])
      end
    end
    print("     ix = "..ix)
    print("maximum = "..maximum)
    
    local tmp = tmp_c[ix]

--  xt = xt - tmp(ix)*reshape(A(ix,:), tbs, tbs).*mask;
    local basis = A[ix+1]
    for i=1,#mask do
      xt_c[i-1] = xt_c[i-1] - tmp * basis[i] * mask[i] / 8192
    end

--  yt(ix) = yt(ix) + tmp(ix);
    yt_c[ix] = yt_c[ix] + tmp

--  err = sum(sum(((idct(idct(yt)')'-bb).*mask).^2))/ml;
    IDCT(yt_c, output_c, tbs, tbs)
    local diff
    local sum = 0
    for i=1,#bb do
      diff = (output_c[i-1] - bb[i]) * mask[i]
      sum = sum + math.pow(diff,2)
    end
    err = sum / ml
    print("    err = "..err)
    print("- - - - - - - -")
  end

  IDCT(yt_c, output_c, tbs, tbs)

  return yt_c, output_c
end

return bpb