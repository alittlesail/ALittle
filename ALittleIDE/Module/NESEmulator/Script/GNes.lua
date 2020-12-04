-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(NESEmulator.NesCore, " extends class:NESEmulator.NesCore is nil")
NESEmulator.GNes = Lua.Class(NESEmulator.NesCore, "NESEmulator.GNes")

function NESEmulator.GNes:Setup(image)
	self._image = image
	self:Reset()
	if self._loop_frame ~= nil then
		self._loop_frame:Stop()
	end
	local nes_rom = ALittle.LocalFile()
	if nes_rom:Load(NESEmulator.g_ModuleBasePath .. "Other/Battle City (J).nes") then
		local error = self:ReloadROM(nes_rom)
		ALittle.Log("ReloadROM", error)
		self._loop_frame = ALittle.LoopFrame(Lua.Bind(self.UpdateFrame, self))
		self._loop_frame:Start()
	end
end

function NESEmulator.GNes:OnFrame(frame_buffer)
	local surface = self._image:GetSurface(true)
	local x = 0
	while true do
		if not(x < NESEmulator.SCREEN_WIDTH) then break end
		local y = 0
		while true do
			if not(y < NESEmulator.SCREEN_HEIGHT) then break end
			local index = y * NESEmulator.SCREEN_WIDTH + x
			local color = frame_buffer[index] | 0xFF000000
			carp.SetCarpSurfacePixel(surface, x, y, color)
			y = y+(1)
		end
		x = x+(1)
	end
end

function NESEmulator.GNes:UpdateFrame(frame_time)
	local error = self:Frame()
	if error ~= nil then
		ALittle.Log(error)
		if self._loop_frame ~= nil then
			self._loop_frame:Stop()
		end
	end
end

function NESEmulator.GNes:Shutdown()
	if self._loop_frame ~= nil then
		self._loop_frame:Stop()
	end
end

_G.g_GNes = NESEmulator.GNes()
end