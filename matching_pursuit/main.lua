local mp = require("matching_pursuit")

-- Canvas list to display
local list = {}
-- Display options
local offsetX = 1
local offsetY = 1
local scale   = 20
local size    = 8
local spacing = scale * size + 6
local items_per_row = 2

-- Debug display
local debugX = 700

local image = {
  219, 219, 219, 219, 219, 219, 219, 219,
  219, 219, 219, 219, 219, 219, 219, 219,
   18, 141, 216, 211,  38, 172, 216, 210,
  180,  28, 160, 160, 128, 196, 203, 198,
  202,  80, 128, 196,  36, 160, 200, 196,
  202,  80, 128, 195,  36, 159, 200, 195,
  176,  31, 182, 197,  54, 129, 199, 154,
   21, 157, 199, 201, 154,  17,  17,  51,
}
local mask = {
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  1,0,0,0,1,0,0,0,
  0,1,0,0,1,0,0,0,
  0,1,0,0,1,0,0,0,
  0,1,0,0,1,0,0,0,
  0,1,0,0,1,0,0,0,
  1,0,0,0,0,1,1,1,
}

local b1 = {}
for i,v in ipairs(image) do
  b1[i] = image[i]-128
end

local b2 = {}
for i,v in ipairs(mask) do
  b2[i] = (mask[i]-1) * -255
end

-- dark
local b3 = {}
local b4 = {}
local coeff,out = mp(b1,mask,20)
for i=1,#image do
  b3[i] = coeff[i-1]
  b4[i] = out[i-1]+128
end

-- light
local b5 = {}
local b6 = {}
for i,v in ipairs(mask) do mask[i] = - (mask[i]-1) end
coeff,out = mp(b1,mask,20)
for i=1,#image do
  b5[i] = coeff[i-1]
  b6[i] = out[i-1]+128
end

-- combined
local b7 = {}
for i,v in ipairs(mask) do
  if v == 0 then
    b7[i] = b4[i]
  else
    b7[i] = b6[i]
  end
end

local function readimage(bytes, width, height)
  -- Gather points to display
  local points = {}
  for i=1,#bytes do
    local x = (i-1) % width
    local y = math.floor((i-1) / width)
    local point = {x,y,bytes[i],bytes[i],bytes[i]}
    table.insert(points, point)
  end

  -- Draw to a canvas
  local canvas = love.graphics.newCanvas( width, height )
  canvas:renderTo(function()
    love.graphics.points(points)
  end)
  canvas:setFilter( "nearest", "nearest" )

  return canvas
end

function love.load()
  local c1 = readimage(image,8,8)
  table.insert(list, {["canvas"]=c1, ["data"]=image})
  local c2 = readimage(b2,8,8)
  table.insert(list, {["canvas"]=c2, ["data"]=b2})
  local c3 = readimage(b3,8,8)
  table.insert(list, {["canvas"]=c3, ["data"]=b3})
  local c4 = readimage(b4,8,8)
  table.insert(list, {["canvas"]=c4, ["data"]=b4})
  local c5 = readimage(b5,8,8)
  table.insert(list, {["canvas"]=c5, ["data"]=b5})
  local c6 = readimage(b6,8,8)
  table.insert(list, {["canvas"]=c6, ["data"]=b6})
  local c7 = readimage(b7,8,8)
  table.insert(list, {["canvas"]=c7, ["data"]=b7})
end

function love.draw()
  local m_x, m_y = love.mouse.getPosition()

  for i,v in ipairs(list) do
    local x = offsetX+((i-1)%items_per_row)*spacing
    local y = offsetY+math.floor((i-1)/items_per_row)*spacing
    love.graphics.draw(v.canvas, x, y, 0, scale)
    if m_x > x and m_x < x + spacing and m_y > y and m_y < y + spacing then
      local data = v.data
      for j,value in ipairs(data) do
        local grid = 50
        local x = debugX+50+((j-1)%8) * grid
        local y = math.floor((j-1)/8) * grid
        love.graphics.printf(math.floor(value), x, y, grid,"right")
      end
    end
  end
end

function love.keypressed( key )
  if key == "space" then
    love.load()
  end
  if key == "backspace" then
    table.remove(list)
  end
end
