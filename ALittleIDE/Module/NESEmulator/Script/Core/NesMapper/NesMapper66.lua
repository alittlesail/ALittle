-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(NESEmulator.NesMapper0, " extends class:NESEmulator.NesMapper0 is nil")
NESEmulator.NesMapper66 = Lua.Class(NESEmulator.NesMapper0, "NESEmulator.NesMapper66")

function NESEmulator.NesMapper66:Write(address, value)
	if address < 0x8000 then
		NESEmulator.NesMapper0.Write(self, address, value)
		return
	else
		self:Load32kRomBank((value >> 4) & 3, 0x8000)
		self:Load8kVromBank((value & 3) * 2, 0x0000)
	end
end

end