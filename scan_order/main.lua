local scan = require("scan")

local blocksize = 16
local A = {}
for i=1,256 do
  A[i] = scan.g_auiRasterToZscan[i-1]
end

-- Canvas list to display
local list = {}
-- Display options
local offsetX = 1
local offsetY = 1
local scale   = 32
local size    = blocksize
local spacing = scale * (size + 2)
local items_per_row = 1

-- Debug display
local debugX = spacing*items_per_row

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
  -- Load our basis
  local c1 = readimage(A,blocksize,blocksize)
  table.insert(list, {["canvas"]=c1, ["data"]=A})
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
        local grid = 35
        local x = debugX+50+((j-1)%blocksize) * grid
        local y = math.floor((j-1)/blocksize) * grid
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
