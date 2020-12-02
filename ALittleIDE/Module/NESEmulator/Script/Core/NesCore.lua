-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


NESEmulator.NesCore = Lua.Class(nil, "NESEmulator.NesCore")

function NESEmulator.NesCore:OnFrame(frame_buffer)
end

function NESEmulator.NesCore:OnAudioSample(left, right)
end

function NESEmulator.NesCore:OnStatusUpdate(content)
end

function NESEmulator.NesCore:Ctor()
	___rawset(self, "_sample_rate", 48000)
	___rawset(self, "_frame_rate", 60)
	___rawset(self, "_frame_count", 0)
	___rawset(self, "_frame_time", 1000 / self._frame_rate)
end

end