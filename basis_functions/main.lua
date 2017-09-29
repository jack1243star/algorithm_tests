local basis = require("basis")
local ffi = require("ffi")

local blocksize = 16
local A = basis.create_basis(blocksize)

-- Canvas list to display
local list = {}
-- Display options
local offsetX = 1
local offsetY = 1
local scale   = 2
local size    = blocksize
local spacing = scale * (size + 2)
local items_per_row = blocksize

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
  for i,v in ipairs(A) do
    local b1 = {}
    for _,w in ipairs(v) do table.insert(b1,w+128) end
    local c1 = readimage(b1,blocksize,blocksize)
    table.insert(list, {["canvas"]=c1, ["data"]=A[i], ["num"]=i})
  end

  -- Load the result from dct2basemx
--  local B = {}
--  local pat = "(%S+)"
--  for line in io.lines("dct2basemx.txt") do
--    local matrix = {}
--    for numstr in string.gmatch(line, pat) do
--      table.insert(matrix, tonumber(numstr)/0.125*64+128)
--      print(tonumber(numstr))
--    end
--    table.insert(B, matrix)
--  end
--  for i,v in ipairs(B) do
--    local c = readimage(v,8,8)
--    table.insert(list, {["canvas"]=c, ["data"]=v, ["num"]=i})
--  end
end

function love.draw()
  local m_x, m_y = love.mouse.getPosition()

  for i,v in ipairs(list) do
    local x = offsetX+((i-1)%items_per_row)*spacing
    local y = offsetY+math.floor((i-1)/items_per_row)*spacing
    love.graphics.draw(v.canvas, x, y, 0, scale)
    if m_x > x and m_x < x + spacing and m_y > y and m_y < y + spacing then
      love.graphics.print('['..v.num..']', debugX, 0)
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
