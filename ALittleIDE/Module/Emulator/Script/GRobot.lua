-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Emulator == nil then _G.Emulator = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
Emulator.GRobot = Lua.Class(ALittle.DisplayLayout, "Emulator.GRobot")

function Emulator.GRobot:Setup()
	self._start_button.visible = true
	self._stop_button.visible = false
	self._login_ip_input.text = Emulator.g_GConfig:GetString("login_ip", "127.0.0.1")
	local data_list = Emulator.g_GConfig:GetConfig("login_ip_list", {})
	if ALittle.List_Find(data_list, self._login_ip_input.text) == nil then
		ALittle.List_Push(data_list, self._login_ip_input.text)
	end
	self._ip_dropdown.data_list = data_list
	self._ip_dropdown.text = ""
	self._login_port_input.text = ALittle.String_ToString(Emulator.g_GConfig:GetInt("login_port", 0))
end

function Emulator.GRobot:HandleBlueprintSearchClick(event)
end

function Emulator.GRobot:HandleIpSelectChanged(event)
	self._login_ip_input.text = self._ip_dropdown.text
	self._ip_dropdown.text = ""
end

function Emulator.GRobot:HandleStartClick(event)
end

function Emulator.GRobot:HandleStopClick(event)
end

function Emulator.GRobot:HandleFileTreeRightMenu(user_info, menu)
end

function Emulator.GRobot:HandleSettingChanged()
	self._blueprint_filetree:SetRoot(Emulator.g_GConfig:GetString("blueprint_root", ""), Lua.Bind(self.HandleFileTreeRightMenu, self))
	self._detail_scroll_screen:SetContainer(nil)
	self._log_scroll_screen:RemoveAllChild()
end

end