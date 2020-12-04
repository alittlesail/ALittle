-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


NESEmulator.NesPPUStatus = {
	STATUS_VRAMWRITE = 4,
	STATUS_SLSPRITECOUNT = 5,
	STATUS_SPRITE0HIT = 6,
	STATUS_VBLANK = 7,
}

NESEmulator.SCREEN_WIDTH = 256
NESEmulator.SCREEN_HEIGHT = 240
NESEmulator.PIXEL_COUNT = NESEmulator.SCREEN_WIDTH * NESEmulator.SCREEN_HEIGHT
NESEmulator.NesPPU = Lua.Class(nil, "NESEmulator.NesPPU")

function NESEmulator.NesPPU:Ctor(nes)
	___rawset(self, "_nes", nes)
end

function NESEmulator.NesPPU:Reset()
	self._vram_mem = {}
	local i = 0
	while true do
		if not(i < 0x8000) then break end
		self._vram_mem[i] = 0
		i = i+(1)
	end
	self._sprite_mem = {}
	local i = 0
	while true do
		if not(i < 0x100) then break end
		self._sprite_mem[i] = 0
		i = i+(1)
	end
	self._vram_address = nil
	self._vram_tmp_address = nil
	self._vram_buffered_read_value = 0
	self._first_write = true
	self._sram_address = 0
	self._current_mirroring = -1
	self._request_end_frame = false
	self._nmi_ok = false
	self._dummy_cycle_toggle = false
	self._valid_tile_data = false
	self._nmi_counter = 0
	self._scanline_already_rendered = nil
	self._f_nmi_on_vblank = 0
	self._f_sprite_size = 0
	self._f_bg_pattern_table = 0
	self._f_sp_pattern_table = 0
	self._f_addr_inc = 0
	self._f_ntbl_address = 0
	self._f_color = 0
	self._f_sp_visibility = 0
	self._f_bg_visibility = 0
	self._f_sp_clipping = 0
	self._f_bg_clipping = 0
	self._f_disp_type = 0
	self._cnt_fv = 0
	self._cnt_v = 0
	self._cnt_h = 0
	self._cnt_vt = 0
	self._cnt_ht = 0
	self._reg_fv = 0
	self._reg_v = 0
	self._reg_h = 0
	self._reg_vt = 0
	self._reg_ht = 0
	self._reg_fh = 0
	self._reg_s = 0
	self._cur_nt = nil
	self._attrib = {}
	self._buffer = {}
	self._bgbuffer = {}
	self._pixrendered = {}
	self._valid_tile_data = nil
	self._scantile = {}
	self._scanline = 0
	self._last_rendered_scanline = -1
	self._cur_x = 0
	self._spr_x = {}
	local i = 0
	while true do
		if not(i < 64) then break end
		self._spr_x[i] = 0
		i = i+(1)
	end
	self._spr_y = {}
	local i = 0
	while true do
		if not(i < 64) then break end
		self._spr_y[i] = 0
		i = i+(1)
	end
	self._spr_tile = {}
	local i = 0
	while true do
		if not(i < 64) then break end
		self._spr_tile[i] = 0
		i = i+(1)
	end
	self._spr_col = {}
	local i = 0
	while true do
		if not(i < 64) then break end
		self._spr_col[i] = 0
		i = i+(1)
	end
	self._vert_flip = {}
	local i = 0
	while true do
		if not(i < 64) then break end
		self._vert_flip[i] = false
		i = i+(1)
	end
	self._hori_flip = {}
	local i = 0
	while true do
		if not(i < 64) then break end
		self._hori_flip[i] = false
		i = i+(1)
	end
	self._bg_priority = {}
	local i = 0
	while true do
		if not(i < 64) then break end
		self._bg_priority[i] = false
		i = i+(1)
	end
	self._spr_0_hit_x = 0
	self._spr_0_hit_y = 0
	self._hit_spr_0 = false
	self._spr_palette = {}
	self._img_palette = {}
	self._pt_tile = {}
	local i = 0
	while true do
		if not(i < 512) then break end
		self._pt_tile[i] = NESEmulator.NesTile()
		i = i+(1)
	end
	self._ntable_1 = {}
	self._current_mirroring = -1
	self._name_table = {}
	local i = 0
	while true do
		if not(i < 4) then break end
		self._name_table[i] = NESEmulator.NesNameTable(32, 32, "Nt" .. i)
		i = i+(1)
	end
	self._vram_mirror_table = {}
	local i = 0
	while true do
		if not(i < 0x8000) then break end
		self._vram_mirror_table[i] = i
		i = i+(1)
	end
	self._pal_table = NESEmulator.NesPaletteTable()
	self._pal_table:LoadNTSCPalette()
	self:UpdateControlReg1(0)
	self:UpdateControlReg2(0)
end

function NESEmulator.NesPPU:SetMirroring(mirroring)
	if mirroring == self._current_mirroring then
		return
	end
	self._current_mirroring = mirroring
	self:TriggerRendering()
	if self._vram_mirror_table == nil then
		self._vram_mirror_table = {}
	end
	local i = 0
	while true do
		if not(i < 0x8000) then break end
		self._vram_mirror_table[i] = i
		i = i+(1)
	end
	self:DefineMirrorRegion(0x3f20, 0x3f00, 0x20)
	self:DefineMirrorRegion(0x3f40, 0x3f00, 0x20)
	self:DefineMirrorRegion(0x3f80, 0x3f00, 0x20)
	self:DefineMirrorRegion(0x3fc0, 0x3f00, 0x20)
	self:DefineMirrorRegion(0x3000, 0x2000, 0xf00)
	self:DefineMirrorRegion(0x4000, 0x0000, 0x4000)
	if mirroring == NESEmulator.NESMirroringType.HORIZONTAL_MIRRORING then
		self._ntable_1[0] = 0
		self._ntable_1[1] = 0
		self._ntable_1[2] = 1
		self._ntable_1[3] = 1
		self:DefineMirrorRegion(0x2400, 0x2000, 0x400)
		self:DefineMirrorRegion(0x2c00, 0x2800, 0x400)
	else
		if mirroring == NESEmulator.NESMirroringType.VERTICAL_MIRRORING then
			self._ntable_1[0] = 0
			self._ntable_1[1] = 1
			self._ntable_1[2] = 0
			self._ntable_1[3] = 1
			self:DefineMirrorRegion(0x2800, 0x2000, 0x400)
			self:DefineMirrorRegion(0x2c00, 0x2400, 0x400)
		else
			if mirroring == NESEmulator.NESMirroringType.SINGLESCREEN_MIRRORING then
				self._ntable_1[0] = 0
				self._ntable_1[1] = 0
				self._ntable_1[2] = 0
				self._ntable_1[3] = 0
				self:DefineMirrorRegion(0x2400, 0x2000, 0x400)
				self:DefineMirrorRegion(0x2800, 0x2000, 0x400)
				self:DefineMirrorRegion(0x2c00, 0x2000, 0x400)
			else
				if mirroring == NESEmulator.NESMirroringType.SINGLESCREEN_MIRRORING2 then
					self._ntable_1[0] = 1
					self._ntable_1[1] = 1
					self._ntable_1[2] = 1
					self._ntable_1[3] = 1
					self:DefineMirrorRegion(0x2400, 0x2400, 0x400)
					self:DefineMirrorRegion(0x2800, 0x2400, 0x400)
					self:DefineMirrorRegion(0x2c00, 0x2400, 0x400)
				else
					self._ntable_1[0] = 0
					self._ntable_1[1] = 1
					self._ntable_1[2] = 2
					self._ntable_1[3] = 3
				end
			end
		end
	end
end

function NESEmulator.NesPPU:DefineMirrorRegion(fromStart, toStart, size)
	local i = 0
	while true do
		if not(i < size) then break end
		self._vram_mirror_table[fromStart + i] = toStart + i
		i = i+(1)
	end
end

function NESEmulator.NesPPU:StartVBlank()
	self._nes._cpu:RequestIrq(NESEmulator.NesCPUIRQ.IRQ_NMI)
	if self._last_rendered_scanline < 239 then
		self:RenderFramePartially(self._last_rendered_scanline + 1, 240 - self._last_rendered_scanline)
	end
	self:EndFrame()
	self._last_rendered_scanline = -1
end

function NESEmulator.NesPPU:EndScanline()
	if self._scanline == 19 then
		if self._dummy_cycle_toggle then
			self._cur_x = 1
			self._dummy_cycle_toggle = not self._dummy_cycle_toggle
		end
	elseif self._scanline == 20 then
		self:SetStatusFlag(NESEmulator.NesPPUStatus.STATUS_VBLANK, false)
		self:SetStatusFlag(NESEmulator.NesPPUStatus.STATUS_SPRITE0HIT, false)
		self._hit_spr_0 = false
		self._spr_0_hit_x = -1
		self._spr_0_hit_y = -1
		if self._f_bg_visibility == 1 or self._f_sp_visibility == 1 then
			self._cnt_fv = self._reg_fv
			self._cnt_v = self._reg_v
			self._cnt_h = self._reg_h
			self._cnt_vt = self._reg_vt
			self._cnt_ht = self._reg_ht
			if self._f_bg_visibility == 1 then
				self:RenderBgScanline(false, 0)
			end
		end
		if self._f_bg_visibility == 1 and self._f_sp_visibility == 1 then
			self:CheckSprite0(0)
		end
		if self._f_bg_visibility == 1 or self._f_sp_visibility == 1 then
			self._nes._mmap:ClockIrqCounter()
		end
	elseif self._scanline == 261 then
		self:SetStatusFlag(NESEmulator.NesPPUStatus.STATUS_VBLANK, true)
		self._request_end_frame = true
		self._nmi_counter = 9
		self._scanline = -1
	else
		if self._scanline >= 21 and self._scanline <= 260 then
			if self._f_bg_visibility == 1 then
				if not self._scanline_already_rendered then
					self._cnt_ht = self._reg_ht
					self._cnt_h = self._reg_h
					self:RenderBgScanline(true, self._scanline + 1 - 21)
				end
				self._scanline_already_rendered = false
				if not self._hit_spr_0 and self._f_sp_visibility == 1 then
					if self._spr_x[0] >= -7 and self._spr_x[0] < 256 and self._spr_y[0] + 1 <= self._scanline - 20 and self._spr_y[0] + 1 + NESEmulator.ConditionExpr(self._f_sprite_size == 0, 8, 16) >= self._scanline - 20 then
						if self:CheckSprite0(self._scanline - 20) then
							self._hit_spr_0 = true
						end
					end
				end
			end
			if self._f_bg_visibility == 1 or self._f_sp_visibility == 1 then
				self._nes._mmap:ClockIrqCounter()
			end
		end
	end
	self._scanline = self._scanline + 1
	self:RegsToAddress()
	self:CntsToAddress()
end

function NESEmulator.NesPPU:StartFrame()
	local bgColor = 0
	if self._f_disp_type == 0 then
		bgColor = self._img_palette[0]
	else
		if self._f_color == 0 then
			bgColor = 0x00000
		elseif self._f_color == 1 then
			bgColor = 0x00ff00
		elseif self._f_color == 2 then
			bgColor = 0xff0000
		elseif self._f_color == 3 then
			bgColor = 0x000000
		elseif self._f_color == 4 then
			bgColor = 0x0000ff
		else
			bgColor = 0x0
		end
	end
	local buffer = self._buffer
	local i = 0
	while true do
		if not(i < 256 * 240) then break end
		buffer[i] = bgColor
		i = i+(1)
	end
	local pixrendered = self._pixrendered
	local i = 0
	while true do
		if not(i < NESEmulator.PIXEL_COUNT) then break end
		pixrendered[i] = 65
		i = i+(1)
	end
end

function NESEmulator.NesPPU:EndFrame()
	local buffer = self._buffer
	if self._show_spr_0_hit then
		if self._spr_x[0] >= 0 and self._spr_x[0] < 256 and self._spr_y[0] >= 0 and self._spr_y[0] < 240 then
			local i = 0
			while true do
				if not(i < 256) then break end
				buffer[(self._spr_y[0] << 8) + i] = 0xff5555
				i = i+(1)
			end
			local i = 0
			while true do
				if not(i < 240) then break end
				buffer[(i << 8) + self._spr_x[0]] = 0xff5555
				i = i+(1)
			end
		end
		if self._spr_0_hit_x >= 0 and self._spr_0_hit_x < 256 and self._spr_0_hit_y >= 0 and self._spr_0_hit_y < 240 then
			local i = 0
			while true do
				if not(i < 256) then break end
				buffer[(self._spr_0_hit_y << 8) + i] = 0x55ff55
				i = i+(1)
			end
			local i = 0
			while true do
				if not(i < 240) then break end
				buffer[(i << 8) + self._spr_0_hit_x] = 0x55ff55
				i = i+(1)
			end
		end
	end
	if self._clip_to_tv_size or self._f_bg_clipping == 0 or self._f_sp_clipping == 0 then
		local y = 0
		while true do
			if not(y < 240) then break end
			local x = 0
			while true do
				if not(x < 8) then break end
				buffer[(y << 8) + x] = 0
				x = x+(1)
			end
			y = y+(1)
		end
	end
	if self._clip_to_tv_size then
		local y = 0
		while true do
			if not(y < 240) then break end
			local x = 0
			while true do
				if not(x < 8) then break end
				buffer[(y << 8) + 255 - x] = 0
				x = x+(1)
			end
			y = y+(1)
		end
	end
	if self._clip_to_tv_size then
		local y = 0
		while true do
			if not(y < 8) then break end
			local x = 0
			while true do
				if not(x < 256) then break end
				buffer[(y << 8) + x] = 0
				buffer[((239 - y) << 8) + x] = 0
				x = x+(1)
			end
			y = y+(1)
		end
	end
	self._nes:OnFrame(buffer)
end

function NESEmulator.NesPPU:UpdateControlReg1(value)
	self:TriggerRendering()
	self._f_nmi_on_vblank = (value >> 7) & 1
	self._f_sprite_size = (value >> 5) & 1
	self._f_bg_pattern_table = (value >> 4) & 1
	self._f_sp_pattern_table = (value >> 3) & 1
	self._f_addr_inc = (value >> 2) & 1
	self._f_ntbl_address = value & 3
	self._reg_v = (value >> 1) & 1
	self._reg_h = value & 1
	self._reg_s = (value >> 4) & 1
end

function NESEmulator.NesPPU:UpdateControlReg2(value)
	self:TriggerRendering()
	self._f_color = (value >> 5) & 7
	self._f_sp_visibility = (value >> 4) & 1
	self._f_bg_visibility = (value >> 3) & 1
	self._f_sp_clipping = (value >> 2) & 1
	self._f_bg_clipping = (value >> 1) & 1
	self._f_disp_type = value & 1
	if self._f_disp_type == 0 then
		self._pal_table:SetEmphasis(self._f_color)
	end
	self:UpdatePalettes()
end

function NESEmulator.NesPPU:SetStatusFlag(flag, value)
	local n = 1 << flag
	self._nes._cpu._mem[0x2002] = (self._nes._cpu._mem[0x2002] & (255 - n)) | NESEmulator.ConditionExpr(value, n, 0)
end

function NESEmulator.NesPPU:ReadStatusRegister()
	local tmp = self._nes._cpu._mem[0x2002]
	self._first_write = true
	self:SetStatusFlag(NESEmulator.NesPPUStatus.STATUS_VBLANK, false)
	return tmp
end

function NESEmulator.NesPPU:WriteSRAMAddress(address)
	self._sram_address = address
end

function NESEmulator.NesPPU:SramLoad()
	return self._sprite_mem[self._sram_address]
end

function NESEmulator.NesPPU:SramWrite(value)
	self._sprite_mem[self._sram_address] = value
	self:SpriteRamWriteUpdate(self._sram_address, value)
	self._sram_address = self._sram_address + 1
	self._sram_address = self._sram_address % (0x100)
end

function NESEmulator.NesPPU:ScrollWrite(value)
	self:TriggerRendering()
	if self._first_write then
		self._reg_ht = (value >> 3) & 31
		self._reg_fh = value & 7
	else
		self._reg_fv = value & 7
		self._reg_vt = (value >> 3) & 31
	end
	self._first_write = not self._first_write
end

function NESEmulator.NesPPU:WriteVRAMAddress(address)
	if self._first_write then
		self._reg_fv = (address >> 4) & 3
		self._reg_v = (address >> 3) & 1
		self._reg_h = (address >> 2) & 1
		self._reg_vt = (self._reg_vt & 7) | ((address & 3) << 3)
	else
		self:TriggerRendering()
		self._reg_vt = (self._reg_vt & 24) | ((address >> 5) & 7)
		self._reg_ht = address & 31
		self._cnt_fv = self._reg_fv
		self._cnt_v = self._reg_v
		self._cnt_h = self._reg_h
		self._cnt_vt = self._reg_vt
		self._cnt_ht = self._reg_ht
		self:CheckSprite0(self._scanline - 20)
	end
	self._first_write = not self._first_write
	self:CntsToAddress()
	if self._vram_address < 0x2000 then
		self._nes._mmap:LatchAccess(self._vram_address)
	end
end

function NESEmulator.NesPPU:VramLoad()
	local tmp = 0
	self:CntsToAddress()
	self:RegsToAddress()
	if self._vram_address <= 0x3eff then
		tmp = self._vram_buffered_read_value
		if self._vram_address < 0x2000 then
			self._vram_buffered_read_value = self._vram_mem[self._vram_address]
		else
			self._vram_buffered_read_value = self:MirroredLoad(self._vram_address)
		end
		if self._vram_address < 0x2000 then
			self._nes._mmap:LatchAccess(self._vram_address)
		end
		self._vram_address = self._vram_address + (NESEmulator.ConditionExpr(self._f_addr_inc == 1, 32, 1))
		self:CntsFromAddress()
		self:RegsFromAddress()
		return tmp
	end
	tmp = self:MirroredLoad(self._vram_address)
	self._vram_address = self._vram_address + (NESEmulator.ConditionExpr(self._f_addr_inc == 1, 32, 1))
	self:CntsFromAddress()
	self:RegsFromAddress()
	return tmp
end

function NESEmulator.NesPPU:VramWrite(value)
	self:TriggerRendering()
	self:CntsToAddress()
	self:RegsToAddress()
	if self._vram_address >= 0x2000 then
		self:MirroredWrite(self._vram_address, value)
	else
		self:WriteMem(self._vram_address, value)
		self._nes._mmap:LatchAccess(self._vram_address)
	end
	if self._f_addr_inc == 1 then
		self._vram_address = self._vram_address + (32)
	else
		self._vram_address = self._vram_address + (1)
	end
	self:RegsFromAddress()
	self:CntsFromAddress()
end

function NESEmulator.NesPPU:SramDMA(value)
	local baseAddress = value * 0x100
	local data = 0
	local i = self._sram_address
	while true do
		if not(i < 256) then break end
		data = self._nes._cpu._mem[baseAddress + i]
		self._sprite_mem[i] = data
		self:SpriteRamWriteUpdate(i, data)
		i = i+(1)
	end
	self._nes._cpu:HaltCycles(513)
end

function NESEmulator.NesPPU:RegsFromAddress()
	local address = (self._vram_tmp_address >> 8) & 0xff
	self._reg_fv = (address >> 4) & 7
	self._reg_v = (address >> 3) & 1
	self._reg_h = (address >> 2) & 1
	self._reg_vt = (self._reg_vt & 7) | ((address & 3) << 3)
	address = self._vram_tmp_address & 0xff
	self._reg_vt = (self._reg_vt & 24) | ((address >> 5) & 7)
	self._reg_ht = address & 31
end

function NESEmulator.NesPPU:CntsFromAddress()
	local address = (self._vram_address >> 8) & 0xff
	self._cnt_fv = (address >> 4) & 3
	self._cnt_v = (address >> 3) & 1
	self._cnt_h = (address >> 2) & 1
	self._cnt_vt = (self._cnt_vt & 7) | ((address & 3) << 3)
	address = self._vram_address & 0xff
	self._cnt_vt = (self._cnt_vt & 24) | ((address >> 5) & 7)
	self._cnt_ht = address & 31
end

function NESEmulator.NesPPU:RegsToAddress()
	local b1 = (self._reg_fv & 7) << 4
	b1 = b1 | (self._reg_v & 1) << 3
	b1 = b1 | (self._reg_h & 1) << 2
	b1 = b1 | (self._reg_vt >> 3) & 3
	local b2 = (self._reg_vt & 7) << 5
	b2 = b2 | self._reg_ht & 31
	self._vram_tmp_address = ((b1 << 8) | b2) & 0x7fff
end

function NESEmulator.NesPPU:CntsToAddress()
	local b1 = (self._cnt_fv & 7) << 4
	b1 = b1 | (self._cnt_v & 1) << 3
	b1 = b1 | (self._cnt_h & 1) << 2
	b1 = b1 | (self._cnt_vt >> 3) & 3
	local b2 = (self._cnt_vt & 7) << 5
	b2 = b2 | self._cnt_ht & 31
	self._vram_address = ((b1 << 8) | b2) & 0x7fff
end

function NESEmulator.NesPPU:IncTileCounter(count)
	local i = count
	while true do
		if not(i ~= 0) then break end
		self._cnt_ht = self._cnt_ht + 1
		if self._cnt_ht == 32 then
			self._cnt_ht = 0
			self._cnt_vt = self._cnt_vt + 1
			if self._cnt_vt >= 30 then
				self._cnt_h = self._cnt_h + 1
				if self._cnt_h == 2 then
					self._cnt_h = 0
					self._cnt_v = self._cnt_v + 1
					if self._cnt_v == 2 then
						self._cnt_v = 0
						self._cnt_fv = self._cnt_fv + 1
						self._cnt_fv = self._cnt_fv & 0x7
					end
				end
			end
		end
		i = i+(-1)
	end
end

function NESEmulator.NesPPU:MirroredLoad(address)
	return self._vram_mem[self._vram_mirror_table[address]]
end

function NESEmulator.NesPPU:MirroredWrite(address, value)
	if address >= 0x3f00 and address < 0x3f20 then
		if address == 0x3f00 or address == 0x3f10 then
			self:WriteMem(0x3f00, value)
			self:WriteMem(0x3f10, value)
		else
			if address == 0x3f04 or address == 0x3f14 then
				self:WriteMem(0x3f04, value)
				self:WriteMem(0x3f14, value)
			else
				if address == 0x3f08 or address == 0x3f18 then
					self:WriteMem(0x3f08, value)
					self:WriteMem(0x3f18, value)
				else
					if address == 0x3f0c or address == 0x3f1c then
						self:WriteMem(0x3f0c, value)
						self:WriteMem(0x3f1c, value)
					else
						self:WriteMem(address, value)
					end
				end
			end
		end
	else
		if address < 0x8000 then
			self:WriteMem(self._vram_mirror_table[address], value)
		else
			ALittle.Log("Invalid VRAM address: " .. address)
		end
	end
end

function NESEmulator.NesPPU:TriggerRendering()
	if self._scanline >= 21 and self._scanline <= 260 then
		self:RenderFramePartially(self._last_rendered_scanline + 1, self._scanline - 21 - self._last_rendered_scanline)
		self._last_rendered_scanline = self._scanline - 21
	end
end

function NESEmulator.NesPPU:RenderFramePartially(startScan, scanCount)
	if self._f_sp_visibility == 1 then
		self:RenderSpritesPartially(startScan, scanCount, true)
	end
	if self._f_bg_visibility == 1 then
		local si = startScan << 8
		local ei = (startScan + scanCount) << 8
		if ei > 0xf000 then
			ei = 0xf000
		end
		local buffer = self._buffer
		local bgbuffer = self._bgbuffer
		local pixrendered = self._pixrendered
		local destIndex = si
		while true do
			if not(destIndex < ei) then break end
			if pixrendered[destIndex] > 0xff then
				buffer[destIndex] = bgbuffer[destIndex]
			end
			destIndex = destIndex+(1)
		end
	end
	if self._f_sp_visibility == 1 then
		self:RenderSpritesPartially(startScan, scanCount, false)
	end
	self._valid_tile_data = false
end

function NESEmulator.NesPPU:RenderBgScanline(bgbuffer, scan)
	local baseTile = NESEmulator.ConditionExpr(self._reg_s == 0, 0, 256)
	local destIndex = (scan << 8) - self._reg_fh
	self._cur_nt = self._ntable_1[self._cnt_v + self._cnt_v + self._cnt_h]
	self._cnt_ht = self._reg_ht
	self._cnt_h = self._reg_h
	self._cur_nt = self._ntable_1[self._cnt_v + self._cnt_v + self._cnt_h]
	if scan < 240 and scan - self._cnt_fv >= 0 then
		local tscanoffset = self._cnt_fv << 3
		local scantile = self._scantile
		local attrib = self._attrib
		local ptTile = self._pt_tile
		local nameTable = self._name_table
		local imgPalette = self._img_palette
		local pixrendered = self._pixrendered
		local targetBuffer = self._buffer
		if bgbuffer ~= nil then
			targetBuffer = self._bgbuffer
		end
		local t
		local tpix
		local att = 0
		local col = 0
		local tile = 0
		while true do
			if not(tile < 32) then break end
			if scan >= 0 then
				if self._valid_tile_data then
					t = scantile[tile]
					if t == nil then
						goto continue_1
					end
					tpix = t._pix
					att = attrib[tile]
				else
					t = ptTile[baseTile + nameTable[self._cur_nt]:GetTileIndex(self._cnt_ht, self._cnt_vt)]
					if t == nil then
						goto continue_1
					end
					tpix = t._pix
					att = nameTable[self._cur_nt]:GetAttrib(self._cnt_ht, self._cnt_vt)
					scantile[tile] = t
					attrib[tile] = att
				end
				local sx = 0
				local x = (tile << 3) - self._reg_fh
				if x > -8 then
					if x < 0 then
						destIndex = destIndex - (x)
						sx = -x
					end
					if t._opaque[self._cnt_fv] then
						while sx < 8 do
							targetBuffer[destIndex] = imgPalette[tpix[tscanoffset + sx] + att]
							pixrendered[destIndex] = pixrendered[destIndex] | 256
							destIndex = destIndex + 1
							sx = sx + 1
						end
					else
						while sx < 8 do
							col = tpix[tscanoffset + sx]
							if col ~= 0 then
								targetBuffer[destIndex] = imgPalette[col + att]
								pixrendered[destIndex] = pixrendered[destIndex] | 256
							end
							destIndex = destIndex + 1
							sx = sx + 1
						end
					end
				end
			end
			self._cnt_ht = self._cnt_ht + 1
			if self._cnt_ht == 32 then
				self._cnt_ht = 0
				self._cnt_h = self._cnt_h + 1
				self._cnt_h = self._cnt_h % (2)
				self._cur_nt = self._ntable_1[(self._cnt_v << 1) + self._cnt_h]
			end
			::continue_1::
			tile = tile+(1)
		end
		self._valid_tile_data = true
	end
	self._cnt_fv = self._cnt_fv + 1
	if self._cnt_fv == 8 then
		self._cnt_fv = 0
		self._cnt_vt = self._cnt_vt + 1
		if self._cnt_vt == 30 then
			self._cnt_vt = 0
			self._cnt_v = self._cnt_v + 1
			self._cnt_v = self._cnt_v % (2)
			self._cur_nt = self._ntable_1[(self._cnt_v << 1) + self._cnt_h]
		else
			if self._cnt_vt == 32 then
				self._cnt_vt = 0
			end
		end
		self._valid_tile_data = false
	end
end

function NESEmulator.NesPPU:RenderSpritesPartially(startscan, scancount, bgPri)
	if self._f_sp_visibility == 1 then
		local i = 0
		while true do
			if not(i < 64) then break end
			if self._bg_priority[i] == bgPri and self._spr_x[i] >= 0 and self._spr_x[i] < 256 and self._spr_y[i] + 8 >= startscan and self._spr_y[i] < startscan + scancount then
				if self._f_sprite_size == 0 then
					local srcy1 = 0
					local srcy2 = 8
					if self._spr_y[i] < startscan then
						srcy1 = startscan - self._spr_y[i] - 1
					end
					if self._spr_y[i] + 8 > startscan + scancount then
						srcy2 = startscan + scancount - self._spr_y[i] + 1
					end
					if self._f_sp_pattern_table == 0 then
						self._pt_tile[self._spr_tile[i]]:Render(self._buffer, 0, srcy1, 8, srcy2, self._spr_x[i], self._spr_y[i] + 1, self._spr_col[i], self._spr_palette, self._hori_flip[i], self._vert_flip[i], i, self._pixrendered)
					else
						self._pt_tile[self._spr_tile[i] + 256]:Render(self._buffer, 0, srcy1, 8, srcy2, self._spr_x[i], self._spr_y[i] + 1, self._spr_col[i], self._spr_palette, self._hori_flip[i], self._vert_flip[i], i, self._pixrendered)
					end
				else
					local top = self._spr_tile[i]
					if (top & 1) ~= 0 then
						top = self._spr_tile[i] - 1 + 256
					end
					local srcy1 = 0
					local srcy2 = 8
					if self._spr_y[i] < startscan then
						srcy1 = startscan - self._spr_y[i] - 1
					end
					if self._spr_y[i] + 8 > startscan + scancount then
						srcy2 = startscan + scancount - self._spr_y[i]
					end
					self._pt_tile[top + NESEmulator.ConditionExpr(self._vert_flip[i], 1, 0)]:Render(self._buffer, 0, srcy1, 8, srcy2, self._spr_x[i], self._spr_y[i] + 1, self._spr_col[i], self._spr_palette, self._hori_flip[i], self._vert_flip[i], i, self._pixrendered)
					srcy1 = 0
					srcy2 = 8
					if self._spr_y[i] + 8 < startscan then
						srcy1 = startscan - (self._spr_y[i] + 8 + 1)
					end
					if self._spr_y[i] + 16 > startscan + scancount then
						srcy2 = startscan + scancount - (self._spr_y[i] + 8)
					end
					self._pt_tile[top + NESEmulator.ConditionExpr(self._vert_flip[i], 0, 1)]:Render(self._buffer, 0, srcy1, 8, srcy2, self._spr_x[i], self._spr_y[i] + 1 + 8, self._spr_col[i], self._spr_palette, self._hori_flip[i], self._vert_flip[i], i, self._pixrendered)
				end
			end
			i = i+(1)
		end
	end
end

function NESEmulator.NesPPU:CheckSprite0(scan)
	self._spr_0_hit_x = -1
	self._spr_0_hit_y = -1
	local toffset = 0
	local tIndexAdd = NESEmulator.ConditionExpr(self._f_sp_pattern_table == 0, 0, 256)
	local bufferIndex = 0
	local x = self._spr_x[0]
	local y = self._spr_y[0] + 1
	local t
	if self._f_sprite_size == 0 then
		if y <= scan and y + 8 > scan and x >= -7 and x < 256 then
			t = self._pt_tile[self._spr_tile[0] + tIndexAdd]
			if self._vert_flip[0] then
				toffset = 7 - (scan - y)
			else
				toffset = scan - y
			end
			toffset = toffset * (8)
			bufferIndex = scan * 256 + x
			if self._hori_flip[0] then
				local i = 7
				while true do
					if not(i >= 0) then break end
					if x >= 0 and x < 256 then
						if bufferIndex >= 0 and bufferIndex < 61440 and self._pixrendered[bufferIndex] ~= 0 then
							if t._pix[toffset + i] ~= 0 then
								self._spr_0_hit_x = bufferIndex % 256
								self._spr_0_hit_y = scan
								return true
							end
						end
					end
					x = x + 1
					bufferIndex = bufferIndex + 1
					i = i+(-1)
				end
			else
				local i = 0
				while true do
					if not(i < 8) then break end
					if x >= 0 and x < 256 then
						if bufferIndex >= 0 and bufferIndex < 61440 and self._pixrendered[bufferIndex] ~= 0 then
							if t._pix[toffset + i] ~= 0 then
								self._spr_0_hit_x = bufferIndex % 256
								self._spr_0_hit_y = scan
								return true
							end
						end
					end
					x = x + 1
					bufferIndex = bufferIndex + 1
					i = i+(1)
				end
			end
		end
	else
		if y <= scan and y + 16 > scan and x >= -7 and x < 256 then
			if self._vert_flip[0] then
				toffset = 15 - (scan - y)
			else
				toffset = scan - y
			end
			if toffset < 8 then
				t = self._pt_tile[self._spr_tile[0] + NESEmulator.ConditionExpr(self._vert_flip[0], 1, 0) + NESEmulator.ConditionExpr((self._spr_tile[0] & 1) ~= 0, 255, 0)]
			else
				t = self._pt_tile[self._spr_tile[0] + NESEmulator.ConditionExpr(self._vert_flip[0], 0, 1) + NESEmulator.ConditionExpr((self._spr_tile[0] & 1) ~= 0, 255, 0)]
				if self._vert_flip[0] then
					toffset = 15 - toffset
				else
					toffset = toffset - (8)
				end
			end
			toffset = toffset * (8)
			bufferIndex = scan * 256 + x
			if self._hori_flip[0] then
				local i = 7
				while true do
					if not(i >= 0) then break end
					if x >= 0 and x < 256 then
						if bufferIndex >= 0 and bufferIndex < 61440 and self._pixrendered[bufferIndex] ~= 0 then
							if t._pix[toffset + i] ~= 0 then
								self._spr_0_hit_x = bufferIndex % 256
								self._spr_0_hit_y = scan
								return true
							end
						end
					end
					x = x + 1
					bufferIndex = bufferIndex + 1
					i = i+(-1)
				end
			else
				local i = 0
				while true do
					if not(i < 8) then break end
					if x >= 0 and x < 256 then
						if bufferIndex >= 0 and bufferIndex < 61440 and self._pixrendered[bufferIndex] ~= 0 then
							if t._pix[toffset + i] ~= 0 then
								self._spr_0_hit_x = bufferIndex % 256
								self._spr_0_hit_y = scan
								return true
							end
						end
					end
					x = x + 1
					bufferIndex = bufferIndex + 1
					i = i+(1)
				end
			end
		end
	end
	return false
end

function NESEmulator.NesPPU:WriteMem(address, value)
	self._vram_mem[address] = value
	if address < 0x2000 then
		self._vram_mem[address] = value
		self:PatternWrite(address, value)
	else
		if address >= 0x2000 and address < 0x23c0 then
			self:NameTableWrite(self._ntable_1[0], address - 0x2000, value)
		else
			if address >= 0x23c0 and address < 0x2400 then
				self:AttribTableWrite(self._ntable_1[0], address - 0x23c0, value)
			else
				if address >= 0x2400 and address < 0x27c0 then
					self:NameTableWrite(self._ntable_1[1], address - 0x2400, value)
				else
					if address >= 0x27c0 and address < 0x2800 then
						self:AttribTableWrite(self._ntable_1[1], address - 0x27c0, value)
					else
						if address >= 0x2800 and address < 0x2bc0 then
							self:NameTableWrite(self._ntable_1[2], address - 0x2800, value)
						else
							if address >= 0x2bc0 and address < 0x2c00 then
								self:AttribTableWrite(self._ntable_1[2], address - 0x2bc0, value)
							else
								if address >= 0x2c00 and address < 0x2fc0 then
									self:NameTableWrite(self._ntable_1[3], address - 0x2c00, value)
								else
									if address >= 0x2fc0 and address < 0x3000 then
										self:AttribTableWrite(self._ntable_1[3], address - 0x2fc0, value)
									else
										if address >= 0x3f00 and address < 0x3f20 then
											self:UpdatePalettes()
										end
									end
								end
							end
						end
					end
				end
			end
		end
	end
end

function NESEmulator.NesPPU:UpdatePalettes()
	local i = 0
	while true do
		if not(i < 16) then break end
		if self._f_disp_type == 0 then
			self._img_palette[i] = self._pal_table:GetEntry(self._vram_mem[0x3f00 + i] & 63)
		else
			self._img_palette[i] = self._pal_table:GetEntry(self._vram_mem[0x3f00 + i] & 32)
		end
		i = i+(1)
	end
	local i = 0
	while true do
		if not(i < 16) then break end
		if self._f_disp_type == 0 then
			self._spr_palette[i] = self._pal_table:GetEntry(self._vram_mem[0x3f10 + i] & 63)
		else
			self._spr_palette[i] = self._pal_table:GetEntry(self._vram_mem[0x3f10 + i] & 32)
		end
		i = i+(1)
	end
end

function NESEmulator.NesPPU:PatternWrite(address, value)
	local tileIndex = ALittle.Math_Floor(address / 16)
	local leftOver = address % 16
	if leftOver < 8 then
		self._pt_tile[tileIndex]:SetScanline(leftOver, value, self._vram_mem[address + 8])
	else
		self._pt_tile[tileIndex]:SetScanline(leftOver - 8, self._vram_mem[address - 8], value)
	end
end

function NESEmulator.NesPPU:NameTableWrite(index, address, value)
	self._name_table[index]._tile[address] = value
	self:CheckSprite0(self._scanline - 20)
end

function NESEmulator.NesPPU:AttribTableWrite(index, address, value)
	self._name_table[index]:WriteAttrib(address, value)
end

function NESEmulator.NesPPU:SpriteRamWriteUpdate(address, value)
	local tIndex = ALittle.Math_Floor(address / 4)
	if tIndex == 0 then
		self:CheckSprite0(self._scanline - 20)
	end
	if address % 4 == 0 then
		self._spr_y[tIndex] = value
	else
		if address % 4 == 1 then
			self._spr_tile[tIndex] = value
		else
			if address % 4 == 2 then
				self._vert_flip[tIndex] = (value & 0x80) ~= 0
				self._hori_flip[tIndex] = (value & 0x40) ~= 0
				self._bg_priority[tIndex] = (value & 0x20) ~= 0
				self._spr_col[tIndex] = (value & 3) << 2
			else
				if address % 4 == 3 then
					self._spr_x[tIndex] = value
				end
			end
		end
	end
end

function NESEmulator.NesPPU:DoNMI()
	self:SetStatusFlag(NESEmulator.NesPPUStatus.STATUS_VBLANK, true)
	self._nes._cpu:RequestIrq(NESEmulator.NesCPUIRQ.IRQ_NMI)
end

function NESEmulator.NesPPU:IsPixelWhite(x, y)
	self:TriggerRendering()
	return self._buffer[(y << 8) + x] == 0xffffff
end

end