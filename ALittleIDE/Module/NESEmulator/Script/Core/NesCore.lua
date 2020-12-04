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

function NESEmulator.NesCore:OnBatteryRamWrite(address, value)
end

function NESEmulator.NesCore:Ctor()
	___rawset(self, "_sample_rate", 48000)
	___rawset(self, "_preferred_frame_rate", 60)
	___rawset(self, "_emulate_sound", true)
	___rawset(self, "_fps_frame_count", 0)
	___rawset(self, "_last_fps_time", 0)
	___rawset(self, "_controllers", {})
	___rawset(self, "_frame_time", 1000 / self._preferred_frame_rate)
	___rawset(self, "_cpu", NESEmulator.NesCPU(self))
	___rawset(self, "_ppu", NESEmulator.NesPPU(self))
	___rawset(self, "_papu", NESEmulator.NesPAPU(self))
	___rawset(self, "_mmap", nil)
	self._controllers[1] = NESEmulator.NesController()
	self._controllers[2] = NESEmulator.NesController()
	self:OnStatusUpdate("Ready to load a ROM.")
end

function NESEmulator.NesCore:Reset()
	if self._mmap ~= nil then
		self._mmap:Reset()
	end
	self._cpu:Reset()
	self._ppu:Reset()
	self._papu:Reset()
	self._last_fps_time = 0
	self._fps_frame_count = 0
	self._run_error = nil
end

function NESEmulator.NesCore:Frame()
	if self._run_error ~= nil then
		return self._run_error
	end
	self._ppu:StartFrame()
	local cycles = 0
	local emulate_sound = self._emulate_sound
	local cpu = self._cpu
	local ppu = self._ppu
	local papu = self._papu
	local run = true
	while run do
		if cpu._cycles_to_halt == 0 then
			cycles = cpu:Emulate()
			if emulate_sound then
				papu:ClockFrameCounter(cycles)
			end
			cycles = cycles * (3)
		else
			if cpu._cycles_to_halt > 8 then
				cycles = 24
				if emulate_sound then
					papu:ClockFrameCounter(8)
				end
				cpu._cycles_to_halt = cpu._cycles_to_halt - (8)
			else
				cycles = cpu._cycles_to_halt * 3
				if emulate_sound then
					papu:ClockFrameCounter(cpu._cycles_to_halt)
				end
				cpu._cycles_to_halt = 0
			end
		end
		while cycles > 0 do
			if ppu._cur_x == ppu._spr_0_hit_x and ppu._f_sp_visibility == 1 and ppu._scanline - 21 == ppu._spr_0_hit_y then
				ppu:SetStatusFlag(NESEmulator.NesPPUStatus.STATUS_SPRITE0HIT, true)
			end
			if ppu._request_end_frame then
				ppu._nmi_counter = ppu._nmi_counter - 1
				if ppu._nmi_counter == 0 then
					ppu._request_end_frame = false
					ppu:StartVBlank()
					run = false
					break
				end
			end
			ppu._cur_x = ppu._cur_x + 1
			if ppu._cur_x == 341 then
				ppu._cur_x = 0
				ppu:EndScanline()
			end
			cycles = cycles - 1
		end
	end
	self._fps_frame_count = self._fps_frame_count + 1
	return self._run_error
end

function NESEmulator.NesCore:ButtonDown(controller, button)
	self._controllers[controller]:ButtonDown(button)
end

function NESEmulator.NesCore:ButtonUp(controller, button)
	self._controllers[controller]:ButtonUp(button)
end

function NESEmulator.NesCore:ZapperMove(x, y)
	if self._mmap == nil then
		return
	end
	self._mmap._zapper_x = x
	self._mmap._zapper_y = x
end

function NESEmulator.NesCore:ZapperFireUp()
	if self._mmap == nil then
		return
	end
	self._mmap._zapper_fired = false
end

function NESEmulator.NesCore:ZapperFireDown()
	if self._mmap == nil then
		return
	end
	self._mmap._zapper_fired = true
end

function NESEmulator.NesCore:GetFPS()
	local now = ALittle.System_GetCurMSTime()
	local fps = 0.0
	if self._last_fps_time ~= 0 then
		fps = self._fps_frame_count / ((now - self._last_fps_time) / 1000)
	end
	self._fps_frame_count = 0
	self._last_fps_time = now
	return fps
end

function NESEmulator.NesCore:ReloadROM(data)
	local rom = NESEmulator.NesRom(self)
	local error = rom:Load(data, nil)
	if error ~= nil then
		return error
	end
	local mapper = rom:CreateMapper()
	if mapper == nil then
		return "not support mapper type"
	end
	self._rom = rom
	self._rom_data = data
	self:Reset()
	self._mmap = mapper
	self._mmap:LoadROM()
	self._ppu:SetMirroring(self._rom:GetMirroringType())
	return nil
end

function NESEmulator.NesCore:SetFramerate(rate)
	self._preferred_frame_rate = rate
	self._frame_time = 1000 / rate
end

function NESEmulator.NesCore:Stop(error)
	self._run_error = error
end

end