-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
AUIPlugin.AUIImageCutPlugin = Lua.Class(ALittle.DisplayLayout, "AUIPlugin.AUIImageCutPlugin")

function AUIPlugin.AUIImageCutPlugin:Ctor(ctrl_sys)
	___rawset(self, "_is_circle", false)
	___rawset(self, "_cut_size", 200)
	___rawset(self, "_MAX_WIDTH", 200)
	___rawset(self, "_MAX_HEIGHT", 200)
	___rawset(self, "_cut_center_x", 0)
	___rawset(self, "_cut_center_y", 0)
	___rawset(self, "_cut_center_w", 0)
	___rawset(self, "_cut_center_h", 0)
end

function AUIPlugin.AUIImageCutPlugin:EditTexture(file_path, is_circle, cut_size)
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
	self._src_image = ALittle.Image(AUIPlugin.g_Control)
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
	self._src_image:SetTextureCut(file_path, ALittle.Math_Floor(max_width), ALittle.Math_Floor(max_height), false, Lua.Bind(self.LoadTextureCallback, self))
end

function AUIPlugin.AUIImageCutPlugin:Clear()
	if self._src_image ~= nil then
		self._image_container:RemoveChild(self._src_image)
		self._src_image = nil
	end
	self._edit_container.visible = false
end

function AUIPlugin.AUIImageCutPlugin:Cut(target_path)
	if self._cut_center_w <= 0 then
		return false
	end
	if self._cut_center_h <= 0 then
		return false
	end
	if target_path == nil then
		target_path = self._file_path
	end
	local surface = carp.LoadCarpSurface(self._file_path)
	if surface == nil then
		return false
	end
	local width = carp.GetCarpSurfaceWidth(surface)
	local height = carp.GetCarpSurfaceHeight(surface)
	local rate_w = self._edit_container.width / width
	local rate_h = self._edit_container.height / height
	local cut_x = ALittle.Math_Floor(self._cut_center_x / rate_w)
	local cut_y = ALittle.Math_Floor(self._cut_center_y / rate_h)
	local cut_width = ALittle.Math_Ceil(self._cut_center_w / rate_w)
	local cut_height = ALittle.Math_Ceil(self._cut_center_h / rate_h)
	local new_width = cut_width
	if new_width > self._MAX_WIDTH then
		new_width = self._MAX_WIDTH
	end
	local new_height = cut_height
	if new_height > self._MAX_HEIGHT then
		new_height = self._MAX_HEIGHT
	end
	local new_surface = carp.CreateCarpSurface(ALittle.Math_Floor(new_width), ALittle.Math_Floor(new_height))
	carp.CutBlitCarpSurface(surface, new_surface, cut_x .. "," .. cut_y .. "," .. cut_width .. "," .. cut_height, "0,0," .. new_width .. "," .. new_height)
	carp.FreeCarpSurface(surface)
	if self._is_circle then
		local new_center = new_width / 2
		local gradual_len = ALittle.Math_Floor(new_center * 0.05)
		local row = 0
		while true do
			if not(row <= new_height - 1) then break end
			local col = 0
			while true do
				if not(col <= new_width - 1) then break end
				local x2 = (new_center - col) * (new_center - col)
				local y2 = (new_center - row) * (new_center - row)
				local distance = ALittle.Math_Sqrt(x2 + y2)
				if distance > new_center then
					carp.SetCarpSurfacePixel(new_surface, col, row, 0)
				elseif gradual_len > 0 and new_center - distance < gradual_len then
					local color = carp.GetCarpSurfacePixel(new_surface, col, row)
					local src_alpha = carp.GetPixelAlpha(color)
					local dst_alpha = ALittle.Math_Sin((3.14159625 / 2) * (new_center - distance) / gradual_len) * 255
					if src_alpha < dst_alpha then
						dst_alpha = src_alpha
					end
					color = carp.SetPixelAlpha(color, ALittle.Math_Ceil(dst_alpha))
					carp.SetCarpSurfacePixel(new_surface, col, row, color)
				end
				col = col+(1)
			end
			row = row+(1)
		end
	end
	local result = carp.SaveCarpSurface(new_surface, target_path)
	carp.FreeCarpSurface(new_surface)
	return result
end

function AUIPlugin.AUIImageCutPlugin:LoadTextureCallback(image, result)
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

function AUIPlugin.AUIImageCutPlugin:UpdateEditQuad(x, y, w, h)
	self._edit_grid9.top_size = y
	self._edit_grid9.bottom_size = ALittle.Math_Ceil(self._edit_container.height - y - h)
	self._edit_grid9.left_size = x
	self._edit_grid9.right_size = ALittle.Math_Ceil(self._edit_container.width - x - w)
	self._left_top_drag.x = x - self._left_top_drag.width / 2
	self._left_top_drag.y = y - self._left_top_drag.height / 2
	self._right_top_drag.x = x + w - self._right_top_drag.width / 2
	self._right_top_drag.y = y - self._right_top_drag.height / 2
	self._left_bottom_drag.x = x - self._left_bottom_drag.width / 2
	self._left_bottom_drag.y = y + h - self._left_bottom_drag.height / 2
	self._right_bottom_drag.x = x + w - self._right_bottom_drag.width / 2
	self._right_bottom_drag.y = y + h - self._right_bottom_drag.height / 2
end

function AUIPlugin.AUIImageCutPlugin:HandleDrag(event)
	if event.target == self._left_top_drag then
		local delta_x = event.delta_x
		local delta_y = event.delta_y
		if self._is_circle then
			if ALittle.Math_Abs(delta_x) > ALittle.Math_Abs(delta_y) then
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
			if ALittle.Math_Abs(delta_x) > ALittle.Math_Abs(delta_y) then
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
			if ALittle.Math_Abs(delta_x) > ALittle.Math_Abs(delta_y) then
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
			if ALittle.Math_Abs(delta_x) > ALittle.Math_Abs(delta_y) then
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

end