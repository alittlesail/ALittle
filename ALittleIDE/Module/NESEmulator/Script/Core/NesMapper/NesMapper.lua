-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


NESEmulator.NesMapper = Lua.Class(nil, "NESEmulator.NesMapper")

function NESEmulator.NesMapper:Ctor(nes)
	___rawset(self, "_nes", nes)
end

function NESEmulator.NesMapper:Reset()
	self._zapper_fired = false
	self._zapper_x = nil
	self._zapper_y = nil
end

function NESEmulator.NesMapper:LoadROM()
	return "not implement"
end

function NESEmulator.NesMapper:Load(address)
	return 0
end

function NESEmulator.NesMapper:Write(address, value)
end

function NESEmulator.NesMapper:ClockIrqCounter()
end

function NESEmulator.NesMapper:LatchAccess(address)
end

function NESEmulator.CreateNesMapper(nes, type)
	if type == 0 then
		return NESEmulator.NesMapper0(nes)
	end
	if type == 1 then
		return NESEmulator.NesMapper1(nes)
	end
	if type == 2 then
		return NESEmulator.NesMapper2(nes)
	end
	if type == 3 then
		return NESEmulator.NesMapper3(nes)
	end
	if type == 4 then
		return NESEmulator.NesMapper4(nes)
	end
	if type == 5 then
		return NESEmulator.NesMapper5(nes)
	end
	if type == 7 then
		return NESEmulator.NesMapper7(nes)
	end
	if type == 11 then
		return NESEmulator.NesMapper11(nes)
	end
	if type == 34 then
		return NESEmulator.NesMapper34(nes)
	end
	if type == 38 then
		return NESEmulator.NesMapper38(nes)
	end
	if type == 66 then
		return NESEmulator.NesMapper66(nes)
	end
	if type == 74 then
		return NESEmulator.NesMapper4(nes)
	end
	if type == 94 then
		return NESEmulator.NesMapper94(nes)
	end
	if type == 140 then
		return NESEmulator.NesMapper140(nes)
	end
	if type == 180 then
		return NESEmulator.NesMapper180(nes)
	end
	return nil
end

end