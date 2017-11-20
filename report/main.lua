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

local f = io.open("../../Project/mp_log.txt")
local datastr = "return {"..f:read("*a").."}"
f:close()
local data,err = load(datastr)()

local total = 0
local count = 0
local bits_change = 0
local dist_change = 0
local lambda = 57.908390375799925

local tmp = 0

local before_psnr, before_ssd
local after_psnr, after_ssd

for i,v in ipairs(data) do
  if v.tag == 'PU' then
    total = total + 1
    if v.mpCost < v.nonMpCost then
      count = count + 1

      local nonMpBits = math.floor(((v.nonMpCost-v.nonMpDist)/lambda)+0.1)
      print(v.mpBits,v.mpDist,nonMpBits,v.nonMpDist)
      bits_change = bits_change - nonMpBits + v.mpBits
      dist_change = dist_change - v.nonMpDist + v.mpDist
      tmp = tmp + v.nonMpDist
    end
  elseif v.tag == 'summary' then
    before_psnr, before_ssd = v.PSNR, v.SSD
  end
end

print(count.." out of "..total)
print("Bits: "..bits_change)
print("Dist: "..dist_change)
print("PSNR: "..before_psnr)
print(" SSD: "..before_ssd)
print(tmp)

local w,h,org = readp2("../../Project/org.pgm")
local w,h,rec = readp2("../../Project/rec.pgm")
local dist = 0
for i=1,w*h do
  local temp = (org[i] - rec[i]) * (org[i] - rec[i])
  dist = dist + temp
end
print(dist)

--print(PSNR(192*128, before_ssd))