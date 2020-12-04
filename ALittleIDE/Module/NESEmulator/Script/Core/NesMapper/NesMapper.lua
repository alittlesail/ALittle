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
	return nil
end

end