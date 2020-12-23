-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(152169657, "AUIPlugin.ABnfColor", {
name = "AUIPlugin.ABnfColor", ns_name = "AUIPlugin", rl_name = "ABnfColor", hash_code = 152169657,
name_list = {"red","green","blue"},
type_list = {"double","double","double"},
option_map = {}
})

AUIPlugin.AUICodeLanguage = Lua.Class(nil, "AUIPlugin.AUICodeLanguage")

function AUIPlugin.AUICodeLanguage:Ctor(project, full_path)
	___rawset(self, "_version", 1)
	___rawset(self, "_project", project)
	___rawset(self, "_full_path", full_path)
	___rawset(self, "_auto_pair", {})
	self._auto_pair["{"] = "}"
	self._auto_pair["["] = "]"
	self._auto_pair["("] = ")"
	self._auto_pair["<"] = ">"
	self._auto_pair["\""] = "\""
	self._auto_pair["'"] = "'"
end

function AUIPlugin.AUICodeLanguage.__getter:version()
	return self._version
end

function AUIPlugin.AUICodeLanguage:OnOpen(content)
end

function AUIPlugin.AUICodeLanguage:OnClose()
end

function AUIPlugin.AUICodeLanguage:OnShow()
end

function AUIPlugin.AUICodeLanguage:OnHide()
end

function AUIPlugin.AUICodeLanguage:OnSave()
end

function AUIPlugin.AUICodeLanguage:OnTabRightMenu(menu)
end

function AUIPlugin.AUICodeLanguage:SetText(content)
	self._version = self._version + (1)
	alanguage.abnffile_settext(self._abnf_file, self._version, content)
end

function AUIPlugin.AUICodeLanguage:InsertText(content, it_line, it_char)
	self._version = self._version + (1)
	alanguage.abnffile_inserttext(self._abnf_file, self._version, content, it_line, it_char)
end

function AUIPlugin.AUICodeLanguage:DeleteText(it_line_start, it_char_start, it_line_end, it_char_end)
	self._version = self._version + (1)
	alanguage.abnffile_deletetext(self._abnf_file, self._version, it_line_start, it_char_start, it_line_end, it_char_end)
end

function AUIPlugin.AUICodeLanguage:QueryColor(line)
	local ___COROUTINE = coroutine.running()
	local query_id = self._project:Add(___COROUTINE)
	alanguage.abnffile_querycolor(self._abnf_file, query_id, self._version, line)
	return coroutine.yield()
end

function AUIPlugin.AUICodeLanguage:QueryInfo(line, char)
	local ___COROUTINE = coroutine.running()
	local query_id = self._project:Add(___COROUTINE)
	alanguage.abnffile_queryinfo(self._abnf_file, query_id, self._version, line, char)
	return coroutine.yield()
end

function AUIPlugin.AUICodeLanguage:QueryGoto(line, char)
	local ___COROUTINE = coroutine.running()
	local query_id = self._project:Add(___COROUTINE)
	alanguage.abnffile_querygoto(self._abnf_file, query_id, self._version, line, char)
	return coroutine.yield()
end

function AUIPlugin.AUICodeLanguage:QueryComplete(line, char)
	local ___COROUTINE = coroutine.running()
	local query_id = self._project:Add(___COROUTINE)
	alanguage.abnffile_querycomplete(self._abnf_file, query_id, self._version, line, char)
	return coroutine.yield()
end

function AUIPlugin.AUICodeLanguage:QueryParamList(line, char)
	local ___COROUTINE = coroutine.running()
	local query_id = self._project:Add(___COROUTINE)
	alanguage.abnffile_queryparamlist(self._abnf_file, query_id, self._version, line, char)
	return coroutine.yield()
end

function AUIPlugin.AUICodeLanguage:QueryParamIndex(line, char)
	return alanguage.abnffile_queryparamindex(self._abnf_file, self._version, line, char)
end

function AUIPlugin.AUICodeLanguage:QueryError(force)
	local ___COROUTINE = coroutine.running()
	local query_id = self._project:Add(___COROUTINE)
	alanguage.abnffile_queryerror(self._abnf_file, query_id, self._version, force)
	return coroutine.yield()
end

function AUIPlugin.AUICodeLanguage:QueryDesiredIndent(line, char)
	return alanguage.abnffile_querydesiredindent(self._abnf_file, self._version, line, char)
end

function AUIPlugin.AUICodeLanguage:QueryFormateIndent(line, char)
	return alanguage.abnffile_queryformateindent(self._abnf_file, self._version, line, char)
end

function AUIPlugin.AUICodeLanguage:QueryAutoPair(line, char, input)
	local right = self._auto_pair[input]
	if right == nil then
		return nil
	end
	if not alanguage.abnffile_queryautopair(self._abnf_file, self._version, line, char, input, right) then
		return nil
	end
	return right
end

function AUIPlugin.AUICodeLanguage:QueryAutoFormat(input)
	return false
end

function AUIPlugin.AUICodeLanguage:NeedAutoFormat()
	return false
end

function AUIPlugin.AUICodeLanguage:QueryColorValue(tag)
	return nil
end

function AUIPlugin.AUICodeLanguage:QueryCompleteIcon(tag)
	return nil
end

end