
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDEImageCutPlugin = ALittle.Class(ALittle.DisplayLayout, "ALittleIDE.IDEImageCutPlugin")

function IDEImageCutPlugin:Ctor(ctrl_sys)
	___rawset(self, "_is_circle", false)
	___rawset(self, "_cut_size", 200)
	___rawset(self, "_MAX_WIDTH", 200)
	___rawset(self, "_MAX_HEIGHT", 200)
	___rawset(self, "_cut_center_x", 0)
	___rawset(self, "_cut_center_y", 0)
	___rawset(self, "_cut_center_w", 0)
	___rawset(self, "_cut_center_h", 0)
end

function IDEImageCutPlugin:TCtor()
end

function IDEImageCutPlugin:EditTexture(file_path, is_circle, cut_size)
	self._is_circle = is_circle or false
	if cut_size == nil then
		cut_size = 200
	end
	self._cut_size = cut_size
	self._file_path = file_path
	if self._src_image ~= nil then
		self._image_container:RemoveChild(self._src_image)
		self._src_image = nil
	end
	self._src_image = ALittle.Image(g_Control)
	self._image_container:AddChild(self._src_image)
	self._edit_container.visible = false
	self._edit_container.x = 0
	self._edit_container.y = 0
	self._edit_container.width_type = 4
	self._edit_container.width_value = 0
	self._edit_container.height_type = 4
	self._edit_container.height_value = 0
	local max_width = ALittle.System_GetMaxTextureWidth()
	if max_width > self._edit_container.width then
		max_width = self._edit_container.width
	end
	local max_height = ALittle.System_GetMaxTextureHeight()
	if max_height > self._edit_container.height then
		max_height = self._edit_container.height
	end
	self._src_image.x_type = 3
	self._src_image.y_type = 3
	self._src_image:SetTextureCut(file_path, math.floor(max_width), math.floor(max_height), false, ALittle.Bind(self.LoadTextureCallback, self))
end

function IDEImageCutPlugin:Clear()
	if self._src_image ~= nil then
		self._image_container:RemoveChild(self._src_image)
		self._src_image = nil
	end
	self._edit_container.visible = false
end

function IDEImageCutPlugin:Cut(target_path)
	if self._cut_center_w <= 0 then
		return false
	end
	if self._cut_center_h <= 0 then
		return false
	end
	if target_path == nil then
		target_path = self._file_path
	end
	local surface = ALittle.System_LoadSurface(self._file_path)
	if surface == nil then
		return false
	end
	local width = ALittle.System_GetSurfaceWidth(surface)
	local height = ALittle.System_GetSurfaceHeight(surface)
	local rate_w = self._edit_container.width / width
	local rate_h = self._edit_container.height / height
	local cut_x = math.floor(self._cut_center_x / rate_w)
	local cut_y = math.floor(self._cut_center_y / rate_h)
	local cut_width = math.ceil(self._cut_center_w / rate_w)
	local cut_height = math.ceil(self._cut_center_h / rate_h)
	local new_width = cut_width
	if new_width > self._MAX_WIDTH then
		new_width = self._MAX_WIDTH
	end
	local new_height = cut_height
	if new_height > self._MAX_HEIGHT then
		new_height = self._MAX_HEIGHT
	end
	local new_surface = ALittle.System_CreateSurface(math.floor(new_width), math.floor(new_height))
	ALittle.System_CutBlitSurface(new_surface, surface, "0,0," .. new_width .. "," .. new_height, cut_x .. "," .. cut_y .. "," .. cut_width .. "," .. cut_height)
	ALittle.System_FreeSurface(surface)
	if self._is_circle then
		local new_center = new_width / 2
		local gradual_len = math.floor(new_center * 0.05)
		for row = 0, new_height - 1, 1 do
			for col = 0, new_width - 1, 1 do
				local x2 = (new_center - col) * (new_center - col)
				local y2 = (new_center - row) * (new_center - row)
				local distance = math.sqrt(x2 + y2)
				if distance > new_center then
					ALittle.System_SetSurfacePixel(new_surface, col, row, 0)
				elseif gradual_len > 0 and new_center - distance < gradual_len then
					local color = ALittle.System_GetSurfacePixel(new_surface, col, row)
					local src_alpha = ALittle.System_GetPixelAlpha(color)
					local dst_alpha = math.sin((3.14159625 / 2) * (new_center - distance) / gradual_len) * 255
					if src_alpha < dst_alpha then
						dst_alpha = src_alpha
					end
					color = ALittle.System_SetPixelAlpha(color, math.ceil(dst_alpha))
					ALittle.System_SetSurfacePixel(new_surface, col, row, color)
				end
			end
		end
	end
	local result = ALittle.System_SaveSurface(new_surface, target_path)
	ALittle.System_FreeSurface(new_surface)
	return result
end

function IDEImageCutPlugin:LoadTextureCallback(image, result)
	if result == false then
		return
	end
	if self._src_image ~= image then
		return
	end
	image.width = image.texture_width
	image.height = image.texture_height
	image:UpdateLayout()
	self._edit_container.visible = true
	self._edit_container.x = image.x
	self._edit_container.y = image.y
	self._edit_container.width = image.width
	self._edit_container.height = image.height
	if self._cut_size > image.width then
		self._cut_size = image.width
	end
	if self._cut_size > image.height then
		self._cut_size = image.height
	end
	self._cut_center_x = (image.width - self._cut_size) / 2
	self._cut_center_y = (image.height - self._cut_size) / 2
	self._cut_center_w = self._cut_size
	self._cut_center_h = self._cut_size
	self:UpdateEditQuad(self._cut_center_x, self._cut_center_y, self._cut_center_w, self._cut_center_h)
end

function IDEImageCutPlugin:UpdateEditQuad(x, y, w, h)
	self._edit_grid9.top_size = y
	self._edit_grid9.bottom_size = math.ceil(self._edit_container.height - y - h)
	self._edit_grid9.left_size = x
	self._edit_grid9.right_size = math.ceil(self._edit_container.width - x - w)
	self._left_top_drag.x = x - self._left_top_drag.width / 2
	self._left_top_drag.y = y - self._left_top_drag.height / 2
	self._right_top_drag.x = x + w - self._right_top_drag.width / 2
	self._right_top_drag.y = y - self._right_top_drag.height / 2
	self._left_bottom_drag.x = x - self._left_bottom_drag.width / 2
	self._left_bottom_drag.y = y + h - self._left_bottom_drag.height / 2
	self._right_bottom_drag.x = x + w - self._right_bottom_drag.width / 2
	self._right_bottom_drag.y = y + h - self._right_bottom_drag.height / 2
end

function IDEImageCutPlugin:HandleDrag(event)
	if event.target == self._left_top_drag then
		local delta_x = event.delta_x
		local delta_y = event.delta_y
		if self._is_circle then
			if math.abs(delta_x) > math.abs(delta_y) then
				delta_y = delta_x
			else
				delta_x = delta_y
			end
		end
		self._cut_center_x = self._cut_center_x + delta_x
		self._cut_center_y = self._cut_center_y + delta_y
		self._cut_center_w = self._cut_center_w - delta_x
		self._cut_center_h = self._cut_center_h - delta_y
	elseif event.target == self._right_top_drag then
		local delta_x = event.delta_x
		local delta_y = event.delta_y
		if self._is_circle then
			if math.abs(delta_x) > math.abs(delta_y) then
				delta_y = -delta_x
			else
				delta_x = -delta_y
			end
		end
		self._cut_center_y = self._cut_center_y + delta_y
		self._cut_center_w = self._cut_center_w + delta_x
		self._cut_center_h = self._cut_center_h - delta_y
	elseif event.target == self._left_bottom_drag then
		local delta_x = event.delta_x
		local delta_y = event.delta_y
		if self._is_circle then
			if math.abs(delta_x) > math.abs(delta_y) then
				delta_y = -delta_x
			else
				delta_x = -delta_y
			end
		end
		self._cut_center_x = self._cut_center_x + delta_x
		self._cut_center_w = self._cut_center_w - delta_x
		self._cut_center_h = self._cut_center_h + delta_y
	elseif event.target == self._right_bottom_drag then
		local delta_x = event.delta_x
		local delta_y = event.delta_y
		if self._is_circle then
			if math.abs(delta_x) > math.abs(delta_y) then
				delta_y = delta_x
			else
				delta_x = delta_y
			end
		end
		self._cut_center_w = self._cut_center_w + delta_x
		self._cut_center_h = self._cut_center_h + delta_y
	elseif event.target == self._center_drag then
		self._cut_center_x = self._cut_center_x + event.delta_x
		self._cut_center_y = self._cut_center_y + event.delta_y
	end
	if self._cut_center_x < 0 then
		self._cut_center_x = 0
	end
	if self._cut_center_x > self._edit_container.width then
		self._cut_center_x = self._edit_container.width
	end
	if self._cut_center_y < 0 then
		self._cut_center_y = 0
	end
	if self._cut_center_y > self._edit_container.height then
		self._cut_center_y = self._edit_container.height
	end
	if self._cut_center_x + self._cut_center_w > self._edit_container.width then
		self._cut_center_w = self._edit_container.width - self._cut_center_x
	end
	if self._cut_center_w < 0 then
		self._cut_center_w = 0
	end
	if self._cut_center_y + self._cut_center_h > self._edit_container.height then
		self._cut_center_h = self._edit_container.height - self._cut_center_y
	end
	if self._cut_center_h < 0 then
		self._cut_center_h = 0
	end
	self:UpdateEditQuad(self._cut_center_x, self._cut_center_y, self._cut_center_w, self._cut_center_h)
end

