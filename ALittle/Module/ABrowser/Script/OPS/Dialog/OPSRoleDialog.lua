
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1112289965, "ABrowser.OPSPermission", {
name = "ABrowser.OPSPermission", ns_name = "ABrowser", rl_name = "OPSPermission", hash_code = 1112289965,
name_list = {"name","value"},
type_list = {"string","string"},
option_map = {}
})
ALittle.RegStruct(1954508001, "ABrowser.AOPSPermission", {
name = "ABrowser.AOPSPermission", ns_name = "ABrowser", rl_name = "AOPSPermission", hash_code = 1954508001,
name_list = {"permission_map"},
type_list = {"Map<string,List<ABrowser.OPSPermission>>"},
option_map = {}
})
ALittle.RegStruct(9945790, "ABrowser.OPSRoleSelectedInfo", {
name = "ABrowser.OPSRoleSelectedInfo", ns_name = "ABrowser", rl_name = "OPSRoleSelectedInfo", hash_code = 9945790,
name_list = {"selected","value"},
type_list = {"bool","string"},
option_map = {}
})
ALittle.RegStruct(201822355, "ABrowser.OPSTreeItemUserData", {
name = "ABrowser.OPSTreeItemUserData", ns_name = "ABrowser", rl_name = "OPSTreeItemUserData", hash_code = 201822355,
name_list = {"key","value"},
type_list = {"string","string"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-132651217, "ABrowser.OPSTreeCheckChangeEvent", {
name = "ABrowser.OPSTreeCheckChangeEvent", ns_name = "ABrowser", rl_name = "OPSTreeCheckChangeEvent", hash_code = -132651217,
name_list = {"target","selected"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})

assert(ABrowser.OPSBaseDialog, " extends class:ABrowser.OPSBaseDialog is nil")
OPSRoleDialog = Lua.Class(ABrowser.OPSBaseDialog, "ABrowser.OPSRoleDialog")

function OPSRoleDialog:Ctor(ctrl_sys)
	___rawset(self, "_result_map", {})
	___rawset(self, "_selected_permission_map", {})
end

function OPSRoleDialog:Clear()
	self._input.text = ""
	self._result_map = {}
	self._scroll_list:RemoveAllChild()
end

function OPSRoleDialog:Show()
	if self._data ~= nil then
		self._input.text = self._data["role_name"]
		self.selected_permission_map = self._data["permission"]
		self._title.text = "修改角色"
	else
		self._title.text = "新建角色"
	end
	local error, content = self._center.login_logic:HttpPostRequest("QOPSPermission", {})
	if error ~= nil then
		self._center.tool_logic:ShowCenterWeakNotice("权限数据获取失败，请检查网络或关闭360等管理软件", false)
		return
	end
	local result, msg = Lua.TCall(ALittle.String_JsonDecode, content)
	if result ~= nil then
		self._center.tool_logic:ShowCenterWeakNotice("返回数据错误，请联系管理员", false)
		return
	end
	if msg["error"] ~= nil then
		self._center.tool_logic:ShowCenterWeakNotice(msg["error"], false)
		return
	end
	self._scroll_list:RemoveAllChild()
	self._scroll_list.clip_atonce = false
	local json = msg
	for k_1, v_1 in ___pairs(json.permission_map) do
		local tree = g_Control:CreateControl("ops_tree_permission")
		tree.text = k_1
		tree.drag_trans_target = self._scroll_list
		tree:AddEventListener(___all_struct[-132651217], self, self.HandleTreeHeadChange)
		tree._user_data = v_1
		for k_2, v_2 in ___ipairs(v_1) do
			local item = g_Control:CreateControl("ops_tree_body_permission")
			item.text = v_2.name
			item.drag_trans_target = self._scroll_list
			item:AddEventListener(___all_struct[-132651217], self, self.HandleTreeBodyChang)
			tree:AddItem(item)
			local user_data = {}
			item._user_data = user_data
			user_data.key = v_2.name
			user_data.value = v_2.value
			if self._data ~= nil then
				if self._selected_permission_map[v_2.value] == v_2.value then
					item.selected = true
				else
					item.selected = false
				end
			end
		end
		self._scroll_list:AddChild(tree)
	end
	self._scroll_list.clip_atonce = true
	self:ShowFromModal()
end
OPSRoleDialog.Show = Lua.CoWrap(OPSRoleDialog.Show)

function OPSRoleDialog.__setter:disabled(value)
	self._input.disabled = value
	if value then
		self._input_name.red = 0.7
		self._input_name.green = 0.7
		self._input_name.blue = 0.7
	else
		self._input_name.red = 0.4
		self._input_name.green = 0.4
		self._input_name.blue = 0.4
	end
end

function OPSRoleDialog.__setter:selected_permission_map(list)
	self._selected_permission_map = {}
	local temp = ALittle.String_Split(list, ",")
	for k, v in ___ipairs(temp) do
		self._selected_permission_map[v] = v
	end
end

function OPSRoleDialog:OtherParam(param)
	local role_permission = {}
	for k, v in ___pairs(self._result_map) do
		if v.selected then
			role_permission[v.value] = true
		end
	end
	if self._data ~= nil then
		param["role_id"] = self._data["role_id"]
	end
	param["role_permission"] = role_permission
	param["role_name"] = self._input.text
end

function OPSRoleDialog:HandleTreeHeadChange(event)
	local object = event.target
	local selected = event.selected
	local list = object._user_data
	if selected then
		for k, v in ___ipairs(list) do
			local info = {}
			info.selected = true
			info.value = v.value
			self._result_map[v.value] = info
		end
	else
		for k, v in ___ipairs(list) do
			local info = {}
			info.selected = false
			info.value = v.value
			self._result_map[v.value] = info
		end
	end
end

function OPSRoleDialog:HandleTreeBodyChang(event)
	local object = event.target
	local selected = event.selected
	local info = object._user_data
	if selected then
		if self._result_map[info.value] ~= nil then
			self._result_map[info.value].selected = selected
		else
			self._result_map[info.value] = {}
			self._result_map[info.value].selected = selected
			self._result_map[info.value].value = info.value
		end
	else
		if self._result_map[info.value] ~= nil then
			self._result_map[info.value].selected = selected
		else
			self._result_map[info.value] = {}
			self._result_map[info.value].selected = selected
			self._result_map[info.value].value = info.value
		end
	end
	self:CheckSelectAll(event.target)
end

function OPSRoleDialog:CheckSelectAll(target)
	local parent = target._logic_parent
	local childs = parent.body.childs
	for i, v in ___ipairs(childs) do
		if v.selected == false then
			parent.selected = false
			return
		end
	end
	parent.selected = true
end

assert(ABrowser.OPSTree, " extends class:ABrowser.OPSTree is nil")
OPSTreePermission = Lua.Class(ABrowser.OPSTree, "ABrowser.OPSTreePermission")

function OPSTreePermission:HandleHeadChenkButtonChange(event)
	local object = event.target
	local selected = object.selected
	local childs = self._body.childs
	if selected then
		for i, v in ___ipairs(childs) do
			v.selected = true
		end
	else
		for i, v in ___ipairs(childs) do
			v.selected = false
		end
	end
	local e = {}
	e.target = self
	e.selected = selected
	self:DispatchEvent(___all_struct[-132651217], e)
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
OPSTreeBodyPermission = Lua.Class(ALittle.DisplayLayout, "ABrowser.OPSTreeBodyPermission")

function OPSTreeBodyPermission.__setter:text(value)
	self._body_btn.text = value
end

function OPSTreeBodyPermission.__setter:selected(value)
	self._body_chk.selected = value
	local e = {}
	e.target = self
	e.selected = self._body_chk.selected
	self:DispatchEvent(___all_struct[-132651217], e)
end

function OPSTreeBodyPermission.__getter:selected()
	return self._body_chk.selected
end

function OPSTreeBodyPermission.__setter:drag_trans_target(target)
	self._body_btn.drag_trans_target = target
end

function OPSTreeBodyPermission:HandleBodyClick(event)
	self._body_chk.selected = not self._body_chk.selected
	local e = {}
	e.target = self
	e.selected = self._body_chk.selected
	self:DispatchEvent(___all_struct[-132651217], e)
end

