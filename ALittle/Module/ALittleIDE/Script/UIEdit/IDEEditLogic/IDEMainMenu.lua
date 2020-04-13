
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(1255897792, "ALittleIDE.IDEMainMenuImageInfo", {
name = "ALittleIDE.IDEMainMenuImageInfo", ns_name = "ALittleIDE", rl_name = "IDEMainMenuImageInfo", hash_code = 1255897792,
name_list = {"file_name","x","y","width","height"},
type_list = {"string","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(1020446174, "ALittleIDE.IDEMainMenuFramePlayInfo", {
name = "ALittleIDE.IDEMainMenuFramePlayInfo", ns_name = "ALittleIDE", rl_name = "IDEMainMenuFramePlayInfo", hash_code = 1020446174,
name_list = {"width","height","root_path","image_list","image_count"},
type_list = {"double","double","string","List<ALittleIDE.IDEMainMenuImageInfo>","int"},
option_map = {}
})

IDEMainMenu = Lua.Class(nil, "ALittleIDE.IDEMainMenu")

function IDEMainMenu:ShowFileMenu(event)
	if self._menu_file_menu == nil then
		self._menu_file_menu = g_Control:CreateControl("ide_file_menu", self)
	end
	local x, y = event.target:LocalToGlobal()
	self._menu_file_menu.x = x
	self._menu_file_menu.y = y + event.target.height
	A_LayerManager:ShowFromRight(self._menu_file_menu)
end

function IDEMainMenu:HandleNewProject(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDEProjectManager:ShowNewProject()
end

function IDEMainMenu:HandleOpenProject(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDEProjectManager:ShowOpenProject()
end

function IDEMainMenu:HandleSettingProject(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDEProjectManager:ShowSettingProject(nil)
end

function IDEMainMenu:HandleSaveProject(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDETabManager:SaveAllTab()
end

function IDEMainMenu:HandleRefreshProject(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDEProjectManager:RefreshProject()
end

function IDEMainMenu:HandleExportProject(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDEProjectManager:ShowExportProject()
end

function IDEMainMenu:HandleRun(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDEProjectManager:RunProject()
end

function IDEMainMenu:ShowEditMenu(event)
	if self._menu_edit_menu == nil then
		self._menu_edit_menu = g_Control:CreateControl("ide_edit_menu", self)
	end
	local x, y = event.target:LocalToGlobal()
	self._menu_edit_menu.x = x
	self._menu_edit_menu.y = y + event.target.height
	A_LayerManager:ShowFromRight(self._menu_edit_menu)
end

function IDEMainMenu:HandleNewControl(event)
	A_LayerManager:HideFromRight(self._menu_edit_menu)
	g_IDEControlManager:ShowNewControl()
end

function IDEMainMenu:HandleUndoRevoke(event)
	A_LayerManager:HideFromRight(self._menu_edit_menu)
	g_IDEUICenter:HandleUndoRevoke(nil)
end

function IDEMainMenu:HandleDoRevoke(event)
	A_LayerManager:HideFromRight(self._menu_edit_menu)
	g_IDEUICenter:HandleDoRevoke(nil)
end

function IDEMainMenu:ShowToolMenu(event)
	if self._menu_tool_menu == nil then
		self._menu_tool_menu = g_Control:CreateControl("ide_tool_menu", self)
	end
	local x, y = event.target:LocalToGlobal()
	self._menu_tool_menu.x = x
	self._menu_tool_menu.y = y + event.target.height
	A_LayerManager:ShowFromRight(self._menu_tool_menu)
end

function IDEMainMenu:HandleGenJsonTemplateCodeClick(event)
	A_LayerManager:HideFromRight(self._menu_tool_menu)
	if self._gen_json_template_code_dialog == nil then
		self._gen_json_template_code_dialog = g_Control:CreateControl("ide_gen_json_template_code_dialog", self, g_IDECenter.dialog_layer)
	end
	self._gen_json_template_code_dialog.visible = true
end

function IDEMainMenu.GenTemplate(num)
	local code = "#define JSON_MACRO_" .. (num * 2 + 1) .. "(Name"
	local i = 0
	while true do
		if not(i <= num - 1) then break end
		code = code .. ", t" .. i .. ", m" .. i
		i = i+(1)
	end
	code = code .. ") \\\n"
	code = code .. "class Name : public ALittle::Json { \\\n"
	code = code .. "public: \\\n"
	code = code .. "\tvirtual const char* GetID() const { return #Name; } \\\n"
	code = code .. "\tinline static const char* GetStaticID() { return #Name; } \\\n"
	code = code .. "public: \\\n"
	code = code .. "\tvirtual void Serialize(ALittle::JsonValue& v, ALittle::JsonAlloc& a) const { \\\n"
	local i = 0
	while true do
		if not(i <= num - 1) then break end
		code = code .. "\t\tALittle::JsonTemplate::Json_Serialize(m" .. i .. ", #m" .. i .. ", (int)sizeof(#m" .. i .. ")-1, v, a); \\\n"
		i = i+(1)
	end
	code = code .. "\t} \\\n"
	code = code .. "\tvirtual void Deserialize(const ALittle::JsonValue& v) { \\\n"
	local i = 0
	while true do
		if not(i <= num - 1) then break end
		code = code .. "\t\tALittle::JsonTemplate::Json_Deserialize(m" .. i .. ", #m" .. i .. ", (int)sizeof(#m" .. i .. ")-1, v); \\\n"
		i = i+(1)
	end
	code = code .. "\t} \\\n"
	code = code .. "\tvirtual void Serialize(ALittle::ValueMap& v) const { \\\n"
	local i = 0
	while true do
		if not(i <= num - 1) then break end
		code = code .. "\t\tALittle::JsonTemplate::Json_SerializeValueMap(m" .. i .. ", #m" .. i .. ", v); \\\n"
		i = i+(1)
	end
	code = code .. "\t} \\\n"
	code = code .. "\tvirtual void Deserialize(const ALittle::ValueMap& v) { \\\n"
	local i = 0
	while true do
		if not(i <= num - 1) then break end
		code = code .. "\t\tALittle::JsonTemplate::Json_DeserializeValueMap(m" .. i .. ", #m" .. i .. ", v); \\\n"
		i = i+(1)
	end
	code = code .. "\t} \\\n"
	code = code .. "\tvirtual const std::vector<std::string>& GetNameList() const { \\\n"
	code = code .. "\t\tstatic std::vector<std::string> s_list; \\\n"
	code = code .. "\t\tif (s_list.empty()) { \\\n"
	local i = 0
	while true do
		if not(i <= num - 1) then break end
		code = code .. "\t\t\ts_list.push_back(#m" .. i .. "); \\\n"
		i = i+(1)
	end
	code = code .. "\t\t} return s_list; \\\n"
	code = code .. "\t} \\\n"
	code = code .. "\tvirtual const std::vector<std::string>& GetTypeList() const { \\\n"
	code = code .. "\t\tstatic std::vector<std::string> s_list; \\\n"
	code = code .. "\t\tif (s_list.empty()) { \\\n"
	local i = 0
	while true do
		if not(i <= num - 1) then break end
		code = code .. "\t\t\ts_list.push_back(#t" .. i .. "); \\\n"
		i = i+(1)
	end
	code = code .. "\t\t} return s_list; \\\n"
	code = code .. "\t} \\\n"
	code = code .. "\tvirtual void Reset() { *this = Name(); } \\\n"
	code = code .. "\tvirtual ~Name() { } \\\n"
	code = code .. "\tName() : "
	local i = 0
	while true do
		if not(i <= num - 1) then break end
		if i > 0 then
			code = code .. ", "
		end
		code = code .. "m" .. i .. "()"
		i = i+(1)
	end
	code = code .. " {} \\\n"
	code = code .. "\t"
	local i = 0
	while true do
		if not(i <= num - 1) then break end
		if i > 0 then
			code = code .. " "
		end
		code = code .. "t" .. i .. " m" .. i .. ";"
		i = i+(1)
	end
	code = code .. " \\\n"
	code = code .. "}\n"
	return code
end

function IDEMainMenu:HandleGenJsonTemplateCode(event)
	local template_count = ALittle.Math_ToInt(self._json_template_count.text)
	if template_count == nil then
		template_count = 20
	end
	local file_count = ALittle.Math_ToInt(self._json_template_file_count.text)
	if file_count == nil then
		file_count = 0
	end
	local num = 1
	local file_index = 1
	while true do
		if not(file_index <= file_count) then break end
		local code_head = "\n#ifndef _ALITTLE_JSON_" .. file_index .. "_H_\n#define _ALITTLE_JSON_" .. file_index .. "_H_\n\n"
		code_head = code_head .. "#include \"Json.h\"\n\n"
		local code_foot = "\n#endif // _ALITTLE_JSON_" .. file_index .. "_H_\n"
		local code_list = {}
		local index = 1
		code_list[index] = code_head
		local template_index = 1
		while true do
			if not(template_index <= template_count) then break end
			index = index + 1
			code_list[index] = IDEMainMenu.GenTemplate(num)
			num = num + 1
			template_index = template_index+(1)
		end
		index = index + 1
		code_list[index] = code_foot
		local content = ALittle.String_Join(code_list, "")
		ALittle.File_WriteTextToFile(content, "Json_" .. file_index .. ".h")
		file_index = file_index+(1)
	end
	local code = "\n#ifndef _ALITTLE_JSON_ALL_H_\n#define _ALITTLE_JSON_ALL_H_\n\n"
	local file_index = 1
	while true do
		if not(file_index <= file_count) then break end
		code = code .. "#include \"Json_" .. file_index .. ".h\"\n"
		file_index = file_index+(1)
	end
	local max_count = file_count * template_count * 2 + 1
	code = code .. "\n#define VA_JSON_EXPAND(...) __VA_ARGS__\n"
	code = code .. "#define VA_JSON_FILTER_("
	local i = 1
	while true do
		if not(i <= max_count) then break end
		if i > 1 then
			code = code .. ","
		end
		code = code .. "_" .. i
		i = i+(1)
	end
	code = code .. ",_N,...) _N\n"
	code = code .. "#define VA_JSON_NUMBER_() "
	local i = max_count
	while true do
		if not(i >= 1) then break end
		if i < max_count then
			code = code .. ","
		end
		code = code .. i
		i = i+(-1)
	end
	code = code .. "\n"
	code = code .. "#define VA_JSON_HELPER(...) VA_JSON_EXPAND(VA_JSON_FILTER_(__VA_ARGS__))\n"
	code = code .. "#define VA_JSON_COUNT(...) VA_JSON_HELPER(__VA_ARGS__, VA_JSON_NUMBER_())\n"
	code = code .. "#define VA_JSON_CAT(X, Y) X##Y\n"
	code = code .. "#define VA_JSON_JOIN(X, Y) VA_JSON_CAT(X, Y)\n"
	code = code .. "#define VA_JSON_PROXY(F, ...) VA_JSON_EXPAND(F(__VA_ARGS__))\n"
	code = code .. "\n#define JSON_MACRO(...) VA_JSON_PROXY(VA_JSON_JOIN(JSON_MACRO_, VA_JSON_COUNT(__VA_ARGS__)), __VA_ARGS__)\n"
	code = code .. "\ntypedef JSON_MACRO(EmptyJson) EmptyJson;\ntypedef JSON_MACRO(ResultJson, bool, result, std::string, reason) ResultJson;\n"
	code = code .. "\n#endif // _ALITTLE_JSON_ALL_H_\n"
	ALittle.File_WriteTextToFile(code, "Json_ALL.h")
	g_IDETool:ShowNotice("提示", "生成成功")
end

function IDEMainMenu:HandleGenServerModuleCodeClick(event)
	A_LayerManager:HideFromRight(self._menu_tool_menu)
	if self._gen_server_module_code_dialog == nil then
		self._gen_server_module_code_dialog = g_Control:CreateControl("ide_gen_server_module_code_dialog", self, g_IDECenter.dialog_layer)
	end
	self._gen_server_module_code_dialog.visible = true
end

function IDEMainMenu:HandleGenServerModuleCode(event)
	local module_name = self._server_module_code_name.text
	local base_path = g_ModuleBasePathEx .. "/ServerModuleCode/" .. module_name
	ALittle.File_MakeDeepDir(base_path)
	local file_map = ALittle.File_GetFileAttrByDir(g_ModuleBasePath .. "/Other/ServerTemplate")
	for file_path, attr in ___pairs(file_map) do
		local file_name = ALittle.File_GetFileNameByPath(file_path)
		file_name = ALittle.String_Replace(file_name, "abcd@module_name@abcd", module_name)
		file_name = ALittle.String_Replace(file_name, "abcd@upper_module_name@abcd", ALittle.String_Upper(module_name))
		file_name = ALittle.String_Replace(file_name, "abcd@lower_module_name@abcd", ALittle.String_Lower(module_name))
		local content = ALittle.File_ReadTextFromFile(file_path)
		if content ~= nil then
			content = ALittle.String_Replace(content, "abcd@module_name@abcd", module_name)
			content = ALittle.String_Replace(content, "abcd@upper_module_name@abcd", ALittle.String_Upper(module_name))
			content = ALittle.String_Replace(content, "abcd@lower_module_name@abcd", ALittle.String_Lower(module_name))
			local full_path = base_path .. "/" .. file_name
			ALittle.File_WriteTextToFile(content, full_path)
		end
	end
	g_IDETool:ShowNotice("提示", "生成成功")
end

function IDEMainMenu:HandleFramePlayFromPList(event)
	A_LayerManager:HideFromRight(self._menu_tool_menu)
	if self._frameplay_plist_dialog == nil then
		self._frameplay_plist_dialog = g_Control:CreateControl("ide_frameplay_plist_dialog", self, g_IDECenter.dialog_layer)
	end
	self._frameplay_plist_dialog.visible = true
end

function IDEMainMenu.ImageListInFramePlayCmp(a, b)
	return a.file_name < a.file_name
end

function IDEMainMenu:HandleViewLog(event)
	A_LayerManager:HideFromRight(self._menu_tool_menu)
	if self._view_log_dialog == nil then
		self._view_log_dialog = g_Control:CreateControl("ide_view_log_dialog", self, g_IDECenter.dialog_layer)
		self:HandleViewLogRefresh(nil)
	end
	self._view_log_dialog.visible = true
end

function IDEMainMenu:HandleViewLogRefresh(event)
	local file_name = ALittle.Time_GetCurYMD(ALittle.Time_GetCurTime()) .. ".log"
	local file_path = ALittle.File_BaseFilePath() .. "Log/" .. file_name
	local content = ALittle.File_ReadTextFromFile(file_path, false)
	if content == nil then
		return
	end
	local content_list = ALittle.String_Split(content, "\n")
	local content_len = ALittle.List_MaxN(content_list)
	local copy_len = content_len - 100
	if copy_len < 1 then
		copy_len = 1
	end
	local log_list = {}
	local log_list_count = 0
	local i = content_len
	while true do
		if not(i >= copy_len) then break end
		log_list_count = log_list_count + 1
		log_list[log_list_count] = content_list[i]
		i = i+(-1)
	end
	self._view_log_content.text = ALittle.String_Join(log_list, "\n")
end

function IDEMainMenu:HandleViewLogClose(event)
	self._view_log_dialog.visible = false
end

g_IDEMainMenu = IDEMainMenu()
