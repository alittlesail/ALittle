-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(152169657, "AUIPlugin.ABnfColor", {
name = "AUIPlugin.ABnfColor", ns_name = "AUIPlugin", rl_name = "ABnfColor", hash_code = 152169657,
name_list = {"red","green","blue"},
type_list = {"double","double","double"},
option_map = {}
})

AUICodeLanguage = Lua.Class(nil, "AUIPlugin.AUICodeLanguage")

function AUICodeLanguage:Ctor(project, full_path)
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

function AUICodeLanguage.__getter:version()
	return self._version
end

function AUICodeLanguage:OnOpen(content)
end

function AUICodeLanguage:OnClose()
end

function AUICodeLanguage:OnShow()
end

function AUICodeLanguage:OnHide()
end

function AUICodeLanguage:OnSave()
end

function AUICodeLanguage:OnTabRightMenu(menu)
end

function AUICodeLanguage:SetText(content)
	self._version = self._version + (1)
	alanguage.abnffile_settext(self._abnf_file, self._version, content)
end

function AUICodeLanguage:InsertText(content, it_line, it_char)
	self._version = self._version + (1)
	alanguage.abnffile_inserttext(self._abnf_file, self._version, content, it_line, it_char)
end

function AUICodeLanguage:DeleteText(it_line_start, it_char_start, it_line_end, it_char_end)
	self._version = self._version + (1)
	alanguage.abnffile_deletetext(self._abnf_file, self._version, it_line_start, it_char_start, it_line_end, it_char_end)
end

function AUICodeLanguage:QueryColor(line)
	local ___COROUTINE = coroutine.running()
	local query_id = self._project:Add(___COROUTINE)
	alanguage.abnffile_querycolor(self._abnf_file, query_id, self._version, line)
	return coroutine.yield()
end

function AUICodeLanguage:QueryInfo(line, char)
	local ___COROUTINE = coroutine.running()
	local query_id = self._project:Add(___COROUTINE)
	alanguage.abnffile_queryinfo(self._abnf_file, query_id, self._version, line, char)
	return coroutine.yield()
end

function AUICodeLanguage:QueryGoto(line, char)
	local ___COROUTINE = coroutine.running()
	local query_id = self._project:Add(___COROUTINE)
	alanguage.abnffile_querygoto(self._abnf_file, query_id, self._version, line, char)
	return coroutine.yield()
end

function AUICodeLanguage:QueryComplete(line, char)
	local ___COROUTINE = coroutine.running()
	local query_id = self._project:Add(___COROUTINE)
	alanguage.abnffile_querycomplete(self._abnf_file, query_id, self._version, line, char)
	return coroutine.yield()
end

function AUICodeLanguage:QuerySigntureHelp(line, char)
	local ___COROUTINE = coroutine.running()
	local query_id = self._project:Add(___COROUTINE)
	alanguage.abnffile_querycomplete(self._abnf_file, query_id, self._version, line, char)
	return coroutine.yield()
end

function AUICodeLanguage:QueryError(force)
	local ___COROUTINE = coroutine.running()
	local query_id = self._project:Add(___COROUTINE)
	alanguage.abnffile_queryerror(self._abnf_file, query_id, self._version, force)
	return coroutine.yield()
end

function AUICodeLanguage:QueryDesiredIndent(line, char)
	return alanguage.abnffile_querydesiredindent(self._abnf_file, self._version, line, char)
end

function AUICodeLanguage:QueryFormateIndent(line, char)
	return alanguage.abnffile_queryformateindent(self._abnf_file, self._version, line, char)
end

function AUICodeLanguage:QueryAutoPair(line, char, input)
	local right = self._auto_pair[input]
	if right == nil then
		return nil
	end
	if not alanguage.abnffile_queryautopair(self._abnf_file, self._version, line, char, input, right) then
		return nil
	end
	return right
end

function AUICodeLanguage:QueryAutoFormat(input)
	return false
end

function AUICodeLanguage:NeedAutoFormat()
	return false
end

function AUICodeLanguage:QueryColorValue(tag)
	return nil
end

function AUICodeLanguage:QueryCompleteIcon(tag)
	return nil
end

