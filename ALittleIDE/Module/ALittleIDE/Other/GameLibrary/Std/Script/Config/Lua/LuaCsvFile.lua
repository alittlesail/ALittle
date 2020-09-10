-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Lua == nil then _G.Lua = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.ICsvFile, " extends class:ALittle.ICsvFile is nil")
Lua.LuaCsvFile = Lua.Class(ALittle.ICsvFile, "Lua.LuaCsvFile")

function Lua.LuaCsvFile:Load(path)
	self._path = path
	self._csv = csv.create()
	local error = csv.load(self._csv, path)
	if error ~= nil then
		ALittle.Error(error)
	end
	return error == nil
end

function Lua.LuaCsvFile:Close()
	if self._csv ~= nil then
		csv.clear(self._csv)
		self._csv = nil
	end
end

function Lua.LuaCsvFile:ReadCell(row, col)
	if self._csv == nil then
		return ""
	end
	return csv.readcell(self._csv, row, col)
end

function Lua.LuaCsvFile:GetRowCount()
	if self._csv == nil then
		return 0
	end
	return csv.rowcount(self._csv)
end

function Lua.LuaCsvFile:GetColCount()
	if self._csv == nil then
		return 0
	end
	return csv.colcount(self._csv)
end

end