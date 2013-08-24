require('socket')

local socketmain = socket.bind("*",80)
local N = 1;
local playerpos = {
	{33,33},
	{609,417},
	{609,33},
	{33,417},
	{33,33},
	{609,417},
}
local PLAYERS = {}



local MAP = {}



for y=1,13 do
	MAP[y] = {}
	for x=1,19 do
		if  (y%2 == 0)  and  (x%2 == 0) then
			MAP[y][x] = 2
		else
			if math.random(1,10) <= 8 then
				MAP[y][x] = 1
			else
				MAP[y][x] = 0
			end
		end
	end
end

--Cleaning player pos:

MAP[1][1] = 0
MAP[1][2] = 0
MAP[2][1] = 0

MAP[13][19] = 0
MAP[12][19] = 0
MAP[13][18] = 0

MAP[1][19] = 0
MAP[2][19] = 0
MAP[1][18] = 0


MAP[13][1] = 0
MAP[12][1] = 0
MAP[13][2] = 0


while true do
	socketmain:settimeout(0.01)
	local user = socketmain:accept()
	--Alguem conectou!
	if user then
		local ip = user:getpeername()
		print('Conected: '..ip)
		for e,v in pairs(PLAYERS) do
			v[1]:send('ep:'..playerpos[N][1]..':'..playerpos[N][2]..':'..N..'\n')
		end
		PLAYERS[N] = {user,ip,N,0,0,0,6}
		user:send('!\n')
		N = N+1;
		N = N%5 +1

	end
	--Player control
	for i,b in pairs(PLAYERS) do
		b[1]:settimeout(0.0)
		local packet,statuses = b[1]:receive()
		if packet then
			if packet:match("GET /.+") then
				print('Is a browser =[')
				b[1]:settimeout(1)
				local s = b[1]:receive()
				while s do
					b[1]:settimeout(0.5)
					s = b[1]:receive()
				end
				STR = [[
					Hello! This is not a webserver.... [%s]
				]]
				b[1]:send(STR:format(b[2]))
				b[1]:close()
				PLAYERS[i] = nil;
			elseif packet == '?' then

				b[1]:send('cp:'..playerpos[b[3]][1]..':'..playerpos[b[3]][2]..'\n')
				local cb = ''
				for y=1,13 do
					for x=1,19 do
						if (MAP[y][x] == 1) then
							cb = cb..';'..x..','..y..';'
						end
					end
				end
				print(cb:len())
				b[1]:send('SZB'..cb:len()..'\n')
				print(b[1]:send(cb..'\n'))
				for e,v in pairs(PLAYERS) do
					if (e ~= i) then
						b[1]:send('ep:'..playerpos[v[3]][1]..':'..playerpos[v[3]][2]..':'..v[3]..'\n')
					end
				end
				--Get players
				--b[1]:send('ep:'..playerpos[N][1]..':'..playerpos[N][2]..'\n')

			elseif packet:match('B:(%d+):(%d+)') then
				local x,y = packet:match('B:(%d+):(%d+)')
				x = tonumber(x)
				y = tonumber(y)
				x = x - x%32;
				y = y - y%32;
				if MAP[y/32] and MAP[y/32][x/32] == 0 then
					for e,v in pairs(PLAYERS) do
						v[1]:send('B:'..(x+6)..':'..(y+6)..':'..b[7]..'\n')
					end
					for i=1,b[7] do
						if MAP[(y/32)+i] and MAP[(y/32)+i][(x/32)] == 1 then
							MAP[(y/32)+i][(x/32)] = 0
							if math.random(1,10) <= 9 then
								for e,v in pairs(PLAYERS) do
									v[1]:send('STF:'..(x)..':'..(y+(i*32))..'\n')
								end
							end
							break
						elseif MAP[(y/32)+i] and MAP[(y/32)+i][(x/32)] == 2 then
							break

						end
					end
					for i=1,b[7] do
						if MAP[(y/32)-i] and MAP[(y/32)-i][(x/32)] == 1 then
							MAP[(y/32)-i][(x/32)] = 0
							if math.random(1,10) <= 9 then
								for e,v in pairs(PLAYERS) do
									v[1]:send('STF:'..(x)..':'..(y-(i*32))..'\n')
								end
							end
							break
						elseif MAP[(y/32)-i] and MAP[(y/32)-i][(x/32)] == 2 then
							break

						end
					end
					for i=1,b[7] do
						if MAP[(y/32)][(x/32)+i] == 1 then
							MAP[(y/32)][(x/32)+i] = 0
							if math.random(1,10) <= 9 then
								for e,v in pairs(PLAYERS) do
									v[1]:send('STF:'..(x+(i*32))..':'..(y)..'\n')
								end
							end
							break
						elseif MAP[(y/32)][(x/32)+i] == 2 then
							break

						end
					end
					for i=1,b[7] do
						if MAP[(y/32)][(x/32)-i] == 1 then
							MAP[(y/32)][(x/32)-i] = 0
							if math.random(1,10) <= 9 then
								for e,v in pairs(PLAYERS) do
									v[1]:send('STF:'..(x-(i*32))..':'..(y)..'\n')
								end
							end
							break
						elseif MAP[(y/32)][(x/32)-i] == 2 then
							break

						end



					end
				end
			elseif packet:match('S(%l):(.+)') then
				local le,S = packet:match('S(%l):(.+)')
				for e,v in pairs(PLAYERS) do
					if (e ~= i) then
						v[1]:send('S'..le..':'..b[3]..':'..S..'\n')
					end
				end

			elseif packet:match('S(%l)!:(.+)') then
				local le,S = packet:match('S(%l)!:(.+)')
				for e,v in pairs(PLAYERS) do
					if (e ~= i) then
						v[1]:send('U'..le..':'..b[3]..':'..S..'\n')
					end
				end
			elseif packet:match('PP:(%d+):(%d+)') then
				local x,y = packet:match('PP:(%d+):(%d+)')
				b[5] = tonumber(x)
				b[6] = tonumber(y)
				for e,v in pairs(PLAYERS) do
					if (e ~= i) then
						v[1]:send('se:'..x..':'..y..':'..b[3]..'\n')
					end
				end

			end
		else
			if statuses == 'closed' then
				b[1]:close()
				local id = b[3]

				print(b[2]..' closed.')
				PLAYERS[i] = nil;
				collectgarbage()
				for e,v in pairs(PLAYERS) do
					v[1]:send('ed:'..id..'\n')
				end
			end
		end
	end
end
