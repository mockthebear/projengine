-- {texto,tipo,r,g,b,?,x,y)
-- { spr,type,sizex,sizey,x_off,y_off,POSX,POSY



local mapa = {

{0,1,0,0,0,0,100,100}
--{22,1,0,0,0,0,32,0}

 }


local n = 3311
function toUi16(n)
return string.char(math.floor((n+1)/256)) .. string.char((n+1)%256);
end
function toIn16(n)
	return n:sub(1,1):byte()*256 + n:sub(2,2):byte()
end

local txt = {}

local objC = toUi16(#mapa)

local objs = ""
-- [2 id] [2 type] [2 sizex] [2 sizey] [2 x_off] [2 y_off] [2 x_pos] [2 y_pos]
for i=1,#mapa do
	if (tonumber(mapa[i][1])) then
		objs = objs.."/"..toUi16(mapa[i][1])..toUi16(mapa[i][2])..toUi16(mapa[i][3])..toUi16(mapa[i][4])..toUi16(mapa[i][5])..toUi16(mapa[i][6])..toUi16(mapa[i][7])..toUi16(mapa[i][8])
	else
		objs = objs.."/"..toUi16(1)..toUi16(mapa[i][2])..toUi16(mapa[i][3])..toUi16(mapa[i][4])..toUi16(mapa[i][5])..toUi16(mapa[i][6])..toUi16(mapa[i][7])..toUi16(mapa[i][8])
		txt[#txt+1] = mapa[i][1];
	end
end

local map = objC..objs
local ttx = ''
for i=1,#txt do
	ttx = ttx .. toUi16(txt[i]:len())..txt[i]
	print(txt[i])
end
local txtC = toUi16(#txt)

local f1 = io.open('map.map','wb')

print(map:len())
f1:write(map..'G'..txtC..ttx)

f1:close()
