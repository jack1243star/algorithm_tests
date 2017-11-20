local function PSNR(size, dist)
  local fRefValue = 255 * 255 * size
  return 10.0 * math.log10( fRefValue / dist )
end

local function readp2(filename)
  local f = io.open(filename)
  local magic_string = f:read("*l")
  local w = f:read("*n")
  local h = f:read("*n")
  local d = f:read("*n")
  local image = {}
  for i=1,w*h do image[i] = f:read("*n") end
  f:close()
  return w,h,image
end

local function writep2(filename,w,h,data)
  local f = io.open(filename,"w")
  f:write("P2\n")
  f:write(string.format("%d %d\n",w,h))
  f:write("255\n")
  local image = {}
  for i=1,w*h do f:write(data[i].." ") end
  f:close()
end

local function copy(src,dst,x,y,w,h,stride)
  for i=0,h-1 do
    local offsetY = y+i
    for j=0,w-1 do
      local offsetX = x+j
      dst[stride*offsetY+offsetX+1] = src[stride*offsetY+offsetX+1]
    end
  end
end

function fsize (filename)
  local file = io.open(filename)
  local size = file:seek("end")    -- get file size
  file:close()
  return size
end

local function test(name)
  local f = io.open("../../Project/"..name.."/mp_log.txt")
  local datastr = "return {"..f:read("*a").."}"
  f:close()
  local data,err = load(datastr)()

  local total = 0
  local count = 0
  local bits_change = 0
  local dist_change = 0
  local lambda

  local tmp = 0

  local before_psnr, before_ssd, before_bits
  local after_psnr, after_ssd, after_bits


  local w,h,org = readp2("../../Project/"..name.."/org.pgm")
  local w,h,rec = readp2("../../Project/"..name.."/rec.pgm")
  local w,h,mprec = readp2("../../Project/"..name.."/mp_rec.pgm")

  for i,v in ipairs(data) do
    if v.tag == 'summary' then
      before_psnr, before_ssd = v.PSNR, v.SSD
      lambda = v.lambda
    end
  end

  for i,v in ipairs(data) do
    if v.tag == 'PU' then
      total = total + 1
      if v.mpCost < v.nonMpCost then
        count = count + 1

        local nonMpBits = math.floor(((v.nonMpCost-v.nonMpDist)/lambda)+0.1)
--        print(v.mpBits,v.mpDist,nonMpBits,v.nonMpDist)
        bits_change = bits_change - nonMpBits + v.mpBits
        dist_change = dist_change - v.nonMpDist + v.mpDist

        copy(mprec,rec,v.L,v.T,v.w,v.h,w)
      end
    end
  end

  writep2("test.pgm",w,h,rec)

  print(count.." out of "..total)
--  print("Bits: "..bits_change)
--  print("Dist: "..dist_change)
--  print("PSNR: "..before_psnr)
--  print(" SSD: "..before_ssd)

  local dist = 0
  for i=1,w*h do
    local temp = (org[i] - rec[i]) * (org[i] - rec[i])
    dist = dist + temp
  end
  after_ssd = dist
--  print(after_ssd)
  after_psnr = PSNR(w*h, after_ssd) 
--  print(after_psnr)
  before_bits = 8*fsize("../../Project/"..name.."/str.bin")
  after_bits = before_bits+bits_change
  
  before_bpp = before_bits / (w*h)
  after_bpp = after_bits / (w*h)
  return before_bpp, before_psnr, after_bpp, after_psnr
end

local testname = "test3"
local f = io.open(testname..".txt", "w")
for qp=27,30,3 do
  local bits, psnr, mp_bits, mp_psnr = test(testname.."-"..qp)
  f:write(string.format("%f %f %f %f\n", bits, psnr, mp_bits, mp_psnr))
end
f:close()
