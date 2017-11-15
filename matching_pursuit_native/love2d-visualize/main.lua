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
local debugX = 300

-- dark
require"output"
local b1 = {}
local b2 = {}
local b3 = {}
local b4 = {}
local b5 = {}
local b6 = {}
local b7 = {}
for i=1,64 do
  b1[i] = coeff[i]
  b2[i] = rec[i]+128
  b3[i] = image[i]+128
  b4[i] = (-mask[i]+1)*255
  b5[i] = coeff2[i]
  b6[i] = rec2[i]+128
  b7[i] = (mask[i] == 0) and b2[i] or b6[i]
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

local function item(list,data,w,h,name)
  table.insert(
    list,
    {
      ["canvas"] = readimage(data,8,8),
      ["data"] = data,
      ["name"] = name,
      ["width"]=w,
      ["height"]=h
    }
  )
end

function love.load()
  item(list,b3,8,8,"image")
  item(list,b4,8,8,"mask")
  item(list,b1,8,8,"coeff1")
  item(list,b2,8,8,"rec1")
  item(list,b5,8,8,"coeff2")
  item(list,b6,8,8,"rec2")
  item(list,b3,8,8,"combined")
end

function love.draw()
  local m_x, m_y = love.mouse.getPosition()

  for i,v in ipairs(list) do
    local x = offsetX+((i-1)%items_per_row)*spacing
    local y = offsetY+math.floor((i-1)/items_per_row)*spacing
    love.graphics.draw(v.canvas, x, y, 0, scale)
    if m_x > x and m_x < x + spacing and m_y > y and m_y < y + spacing then
      local data = v.data
      love.window.setTitle( v.name )
      for j,value in ipairs(data) do
        local grid = 28
        local x = debugX+50+((j-1)%v.width) * grid
        local y = math.floor((j-1)/v.height) * grid
        love.graphics.setColor(math.floor(value),math.floor(value),math.floor(value))
        love.graphics.printf(math.floor(value), x, y, grid,"right",0)
      end
      love.graphics.setColor(255,255,255)
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
