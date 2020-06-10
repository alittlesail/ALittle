
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

OPSDateSelectType = {
	SELECT_DAY = "ABrowser_OPS_OPSDate_Select_Day",
}

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
OPSDate = ALittle.Class(ALittle.DisplayLayout, "ABrowser.OPSDate")

function OPSDate:Ctor(ctrl_sys)
	___rawset(self, "_target", nil)
	___rawset(self, "_mon_map_day", {})
	self._mon_map_day[1] = 31
	self._mon_map_day[3] = 31
	self._mon_map_day[5] = 31
	self._mon_map_day[7] = 31
	self._mon_map_day[8] = 31
	self._mon_map_day[10] = 31
	self._mon_map_day[12] = 31
	self._mon_map_day[2] = 28
	self._mon_map_day[4] = 30
	self._mon_map_day[6] = 30
	self._mon_map_day[9] = 30
	self._mon_map_day[11] = 30
	___rawset(self, "_day_container_group_name", A_TextRadioButtonManager:CreateGroupName())
end

function OPSDate:TCtor()
	for i = 1, 12, 1 do
		local mon_container_x = "_mon_container_" .. i
		local mon_container = self[mon_container_x]
		mon_container._user_data = i
	end
	local group_name = A_TextRadioButtonManager:CreateGroupName()
	for i = 0, 23, 1 do
		local hour_container_x = "_hour_container_" .. i
		local hour_container = self[hour_container_x]
		hour_container._user_data = i
		hour_container.group_name = group_name
	end
	group_name = A_TextRadioButtonManager:CreateGroupName()
	for i = 0, 59, 1 do
		local min_container_x = "_min_container_" .. i
		local min_container = self[min_container_x]
		min_container._user_data = i
		min_container.group_name = group_name
	end
	group_name = A_TextRadioButtonManager:CreateGroupName()
	for i = 0, 59, 1 do
		local sec_container_x = "_sec_container_" .. i
		local sec_container = self[sec_container_x]
		sec_container._user_data = i
		sec_container.group_name = group_name
	end
	for i = 1, 42, 1 do
		local day_container_x = "_day_container_" .. i
		local day_container = self[day_container_x]
		day_container.group_name = self._day_container_group_name
	end
end

function OPSDate:GetDayCountByMonth(year, month)
	if month == 2 then
		if (year % 4 == 0 and year % 100 ~= 0) or (year % 400 == 0) then
			return 29
		else
			return 28
		end
	else
		return self._mon_map_day[month]
	end
end

function OPSDate:Show(target, time_text, select_type, default_hour, default_min, default_sec)
	self._target = target
	self._select_type = select_type
	local x, y = target:LocalToGlobal()
	y = y + target.height
	if y + self.height > A_UISystem.view_height then
		y = A_UISystem.view_height - self.height
	end
	if x + self.width > A_UISystem.view_width then
		x = A_UISystem.view_width - self.width
	end
	self.x = x
	self.y = y
	local loop = ALittle.LoopFunction(ALittle.Bind(A_LayerManager.ShowFromRight, A_LayerManager, self, nil), 1, 1, 1)
	loop:Start()
	self._year_container.visible = false
	self._mon_container.visible = false
	self._sec_container.visible = false
	self._min_container.visible = false
	self._hour_container.visible = false
	if self._select_type == OPSDateSelectType.SELECT_DAY then
		self._cur_hour_text.disabled = true
		self._cur_min_text.disabled = true
		self._cur_sec_text.disabled = true
		self._cur_hour_text.red = 0.6
		self._cur_min_text.red = 0.6
		self._cur_sec_text.red = 0.6
		self._cur_hour_text.green = 0.6
		self._cur_min_text.green = 0.6
		self._cur_sec_text.green = 0.6
		self._cur_hour_text.blue = 0.6
		self._cur_min_text.blue = 0.6
		self._cur_sec_text.blue = 0.6
	else
		self._cur_hour_text.disabled = false
		self._cur_min_text.disabled = false
		self._cur_sec_text.disabled = false
		self._cur_hour_text.red = 0
		self._cur_min_text.red = 0
		self._cur_sec_text.red = 0
		self._cur_hour_text.green = 0.4
		self._cur_min_text.green = 0.4
		self._cur_sec_text.green = 0.4
		self._cur_hour_text.blue = 0.3
		self._cur_min_text.blue = 0.3
		self._cur_sec_text.blue = 0.3
	end
	local time = OPSDate.StringToTime(time_text)
	if time == nil then
		time = os.time()
	end
	self:SetTime(time, time, default_hour, default_min, default_sec)
end

function OPSDate:SetTime(time, no_time, default_hour, default_min, default_sec)
	local cur_year = tonumber(os.date("%Y", time))
	self._cur_year_text.text = cur_year .. "年"
	self._cur_year_text._user_data = cur_year
	local cur_mon = tonumber(os.date("%m", time))
	local cur_mon_str = cur_mon .. "月"
	if cur_mon < 10 then
		cur_mon_str = "0" .. cur_mon .. "月"
	end
	self._cur_mon_text.text = cur_mon_str
	self._cur_mon_text._user_data = cur_mon
	if self._select_type == OPSDateSelectType.SELECT_DAY or no_time == nil then
		if default_hour == nil then
			default_hour = 0
		end
		self._cur_hour_text.text = tostring(default_hour)
		self._cur_hour_text._user_data = default_hour
		if default_min == nil then
			default_min = 0
		end
		self._cur_min_text.text = tostring(default_min)
		self._cur_min_text._user_data = default_min
		if default_sec == nil then
			default_sec = 0
		end
		self._cur_sec_text.text = tostring(default_sec)
		self._cur_sec_text._user_data = default_sec
		self:RefreshDay(math.floor(tonumber(os.date("%d", time))))
		return
	end
	local cur_hour = tonumber(os.date("%H", time))
	local cur_hour_str = tostring(cur_hour)
	if cur_hour < 10 then
		cur_hour_str = "0" .. cur_hour
	end
	self._cur_hour_text.text = cur_hour_str
	self._cur_hour_text._user_data = cur_hour
	local cur_min = tonumber(os.date("%M", time))
	local cur_min_str = tostring(cur_min)
	if cur_min < 10 then
		cur_min_str = "0" .. cur_min
	end
	self._cur_min_text.text = cur_min_str
	self._cur_min_text._user_data = cur_min
	local cur_sec = tonumber(os.date("%S", time))
	local cur_sec_str = tostring(cur_sec)
	if cur_sec < 10 then
		cur_sec_str = "0" .. cur_sec
	end
	self._cur_sec_text.text = cur_sec_str
	self._cur_sec_text._user_data = cur_sec
	self:RefreshDay(math.floor(tonumber(os.date("%d", time))))
end

function OPSDate:HandleCurYearLButtonDown(event)
	if self._year_container.visible then
		self._year_container.visible = false
		return
	end
	self._year_container.visible = true
	self._mon_container.visible = false
	self._hour_container.visible = false
	self._min_container.visible = false
	self._sec_container.visible = false
	local cur_year = self._cur_year_text._user_data
	local begin_year = 0
	if cur_year % 2 == 0 then
		begin_year = cur_year - 5
	else
		begin_year = cur_year - 4
	end
	self:RefreshYearContainer(begin_year)
end

function OPSDate:HandleCurYearDescClick(event)
	local cur_year = self._cur_year_text._user_data
	cur_year = cur_year - 1
	self._cur_year_text.text = cur_year .. "年"
	self._cur_year_text._user_data = cur_year
	self:RefreshDay()
end

function OPSDate:HandleCurYearAddClick(event)
	local cur_year = self._cur_year_text._user_data
	cur_year = cur_year + 1
	self._cur_year_text.text = cur_year .. "年"
	self._cur_year_text._user_data = cur_year
	self:RefreshDay()
end

function OPSDate:HandleYearContainerUpClick(event)
	local begin_year = self._year_container_1._user_data
	begin_year = begin_year - 10
	self:RefreshYearContainer(begin_year)
end

function OPSDate:HandleYearContainerDownClick(event)
	local begin_year = self._year_container_1._user_data
	begin_year = begin_year + 10
	self:RefreshYearContainer(begin_year)
end

function OPSDate:HandleYearContainerSelectClick(event)
	local object = event.target
	self._cur_year_text.text = object.text
	self._cur_year_text._user_data = object._user_data
	self._year_container.visible = false
	self:RefreshDay()
end

function OPSDate:RefreshYearContainer(begin_year)
	for i = 1, 10, 1 do
		local year_container_x = "_year_container_" .. i
		local year_container = self[year_container_x]
		year_container.text = (begin_year + i - 1) .. "年"
		year_container._user_data = begin_year + i - 1
	end
end

function OPSDate:HandleCurMonLButtonDown(event)
	if self._mon_container.visible then
		self._mon_container.visible = false
		return
	end
	self._year_container.visible = false
	self._mon_container.visible = true
	self._hour_container.visible = false
	self._min_container.visible = false
	self._sec_container.visible = false
end

function OPSDate:HandleMonContainerSelectClick(event)
	local object = event.target
	self._cur_mon_text.text = object.text
	self._cur_mon_text._user_data = event.target._user_data
	self._mon_container.visible = false
	self:RefreshDay()
end

function OPSDate:HandleCurMonDescClick(event)
	local cur_mon = self._cur_mon_text._user_data
	cur_mon = cur_mon - 1
	if cur_mon <= 0 then
		local cur_year = self._cur_year_text._user_data
		cur_year = cur_year - 1
		self._cur_year_text.text = cur_year .. "年"
		self._cur_year_text._user_data = cur_year
		cur_mon = 12
	end
	local cur_mon_str = cur_mon .. "月"
	if cur_mon < 10 then
		cur_mon_str = "0" .. cur_mon .. "月"
	end
	self._cur_mon_text.text = cur_mon_str
	self._cur_mon_text._user_data = cur_mon
	self:RefreshDay()
end

function OPSDate:HandleCurMonAddClick(event)
	local cur_mon = self._cur_mon_text._user_data
	cur_mon = cur_mon + 1
	if cur_mon > 12 then
		local cur_year = self._cur_year_text._user_data
		cur_year = cur_year + 1
		self._cur_year_text.text = cur_year .. "年"
		self._cur_year_text._user_data = cur_year
		cur_mon = 1
	end
	local cur_mon_str = cur_mon .. "月"
	if cur_mon < 10 then
		cur_mon_str = "0" .. cur_mon .. "月"
	end
	self._cur_mon_text.text = cur_mon_str
	self._cur_mon_text._user_data = cur_mon
	self:RefreshDay()
end

function OPSDate:HandleHourContainerCloseClick(event)
	self._hour_container.visible = false
end

function OPSDate:HandleCurHourLButtonDown(event)
	if self._hour_container.visible then
		self._hour_container.visible = false
		return
	end
	self._year_container.visible = false
	self._mon_container.visible = false
	self._hour_container.visible = true
	self._min_container.visible = false
	self._sec_container.visible = false
	local cur_hour = self._cur_hour_text._user_data
	local hour_container_x = "_hour_container_" .. cur_hour
	local hour_container = self[hour_container_x]
	hour_container.selected = true
end

function OPSDate:HandleHourContainerSelectClick(event)
	local object = event.target
	if object.selected == false then
		return
	end
	local target_hour = event.target._user_data
	self._cur_hour_text._user_data = target_hour
	if target_hour < 10 then
		self._cur_hour_text.text = "0" .. target_hour
	else
		self._cur_hour_text.text = tostring(target_hour)
	end
	self._hour_container.visible = false
end

function OPSDate:HandleMinContainerCloseClick(event)
	self._min_container.visible = false
end

function OPSDate:HandleCurMinLButtonDown(event)
	if self._min_container.visible then
		self._min_container.visible = false
		return
	end
	self._year_container.visible = false
	self._mon_container.visible = false
	self._hour_container.visible = false
	self._min_container.visible = true
	self._sec_container.visible = false
	local cur_min = self._cur_min_text._user_data
	local min_container_x = "_min_container_" .. cur_min
	local min_container = self[min_container_x]
	min_container.selected = true
end

function OPSDate:HandleMinContainerSelectClick(event)
	local object = event.target
	if object.selected == false then
		return
	end
	local target_min = event.target._user_data
	self._cur_min_text._user_data = target_min
	if target_min < 10 then
		self._cur_min_text.text = "0" .. target_min
	else
		self._cur_min_text.text = tostring(target_min)
	end
	self._min_container.visible = false
end

function OPSDate:HandleSecContainerCloseClick(event)
	self._sec_container.visible = false
end

function OPSDate:HandleCurSecLButtonDown(event)
	if self._sec_container.visible then
		self._sec_container.visible = false
		return
	end
	self._year_container.visible = false
	self._mon_container.visible = false
	self._hour_container.visible = false
	self._min_container.visible = false
	self._sec_container.visible = true
	local cur_sec = self._cur_sec_text._user_data
	local sec_container_x = "_sec_container_" .. cur_sec
	local sec_container = self[sec_container_x]
	sec_container.selected = true
end

function OPSDate:HandleSecContainerSelectClick(event)
	local object = event.target
	if object.selected == false then
		return
	end
	local target_sec = event.target._user_data
	self._cur_sec_text._user_data = target_sec
	if target_sec < 10 then
		self._cur_sec_text.text = "0" .. target_sec
	else
		self._cur_sec_text.text = tostring(target_sec)
	end
	self._sec_container.visible = false
end

function OPSDate:HandleCurClearClick(event)
	self._target.text = ""
	A_LayerManager:HideFromRight(self)
end

function OPSDate:HandleCurNowClick(event)
	self._target.text = os.date("%Y-%m-%d %H:%M:%S", os.time())
	A_LayerManager:HideFromRight(self)
end

function OPSDate:HandleCurConfirmClick(event)
	local time_table = {}
	time_table.hour = self._cur_hour_text._user_data
	time_table.min = self._cur_min_text._user_data
	time_table.sec = self._cur_sec_text._user_data
	local group = A_TextRadioButtonManager:GetGroupByName(self._day_container_group_name)
	if group ~= nil then
		for k, v in ___pairs(group) do
			if v.selected then
				local user_data = v._user_data
				time_table.year = user_data.year
				time_table.month = user_data.month
				time_table.day = user_data.day
				break
			end
		end
	end
	if self._select_type == OPSDateSelectType.SELECT_DAY then
		self._target.text = os.date("%Y-%m-%d", os.time(time_table))
	else
		self._target.text = os.date("%Y-%m-%d %H:%M:%S", os.time(time_table))
	end
	A_LayerManager:HideFromRight(self)
end

function OPSDate:RefreshDay(day)
	local cur_year = self._cur_year_text._user_data
	local cur_mon = self._cur_mon_text._user_data
	local time_table = {}
	time_table.year = cur_year
	time_table.month = cur_mon
	time_table.day = 1
	time_table.hour = 0
	time_table.min = 0
	time_table.sec = 0
	local time = os.time(time_table)
	time_table = ALittle.DateInfo(time)
	local index = time_table.wday
	local target_mon = time_table.month
	local target_year = time_table.year
	if target_mon == 1 then
		target_mon = 12
		target_year = target_year - 1
	else
		target_mon = target_mon - 1
	end
	local day_count = self:GetDayCountByMonth(target_year, target_mon)
	local start_day = day_count - (index - 2)
	for i = 1, index - 1, 1 do
		local day_container_x = "_day_container_" .. i
		local target = self[day_container_x]
		target.text = tostring(start_day)
		local user_data = {}
		target._user_data = user_data
		user_data.year = target_year
		user_data.month = target_mon
		user_data.day = start_day
		target.show_text.red = 153 / 255
		target.show_text.green = 153 / 255
		target.show_text.blue = 153 / 255
		start_day = start_day + 1
	end
	day_count = self:GetDayCountByMonth(time_table.year, time_table.month)
	for i = 1, day_count, 1 do
		local day_container_x = "_day_container_" .. (index + i - 1)
		local target = self[day_container_x]
		target.text = tostring(i)
		local user_data = {}
		target._user_data = user_data
		user_data.year = time_table.year
		user_data.month = time_table.month
		user_data.day = i
		if day ~= nil and i == day then
			target.selected = true
		end
		target.show_text.red = 0 / 255
		target.show_text.green = 98 / 255
		target.show_text.blue = 90 / 255
	end
	target_mon = time_table.month
	target_year = time_table.year
	target_mon = target_mon + 1
	if target_mon > 12 then
		target_mon = 1
		target_year = time_table.year + 1
	end
	start_day = 1
	for i = index + day_count, 42, 1 do
		local day_container_x = "_day_container_" .. i
		local target = self[day_container_x]
		target.text = tostring(start_day)
		local user_data = {}
		target._user_data = user_data
		user_data.year = target_year
		user_data.month = target_mon
		user_data.day = start_day
		target.show_text.red = 153 / 255
		target.show_text.green = 153 / 255
		target.show_text.blue = 153 / 255
		start_day = start_day + 1
	end
end

function OPSDate.StringToTime(text)
	local time = nil
	local start_index, end_index, year, mon, day, hour, min, sec = string.find(text, "^(%d%d%d%d)-(%d%d)-(%d%d) (%d%d).(%d%d).(%d%d)$")
	if start_index == nil then
		start_index, end_index, year, mon, day = string.find(text, "^(%d%d%d%d)-(%d%d)-(%d%d)$")
		if start_index ~= nil then
			hour = "0"
			min = "0"
			sec = "0"
		end
	end
	if year ~= nil and mon ~= nil and day ~= nil and hour ~= nil and min ~= nil and sec ~= nil then
		local time_table = {}
		time_table.year = math.floor(tonumber(year))
		time_table.month = math.floor(tonumber(mon))
		time_table.day = math.floor(tonumber(day))
		time_table.hour = math.floor(tonumber(hour))
		time_table.min = math.floor(tonumber(min))
		time_table.sec = math.floor(tonumber(sec))
		time = os.time(time_table)
	end
	return time
end

