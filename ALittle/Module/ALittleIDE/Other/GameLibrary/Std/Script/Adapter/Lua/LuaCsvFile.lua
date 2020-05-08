-- ALittle Generate Lua And Do Not Edit This Line!
module("Lua", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.ICsvFile, " extends class:ALittle.ICsvFile is nil")
LuaCsvFile = Lua.Class(ALittle.ICsvFile, "Lua.LuaCsvFile")

function LuaCsvFile:Load(path)
	self._path = path
	self._csv = csv.create()
	local error = csv.load(self._csv, path)
	if error ~= nil then
		ALittle.Error(error)
	end
	return error == nil
end

function LuaCsvFile:Close()
	if self._csv ~= nil then
		csv.clear(self._csv)
		self._csv = nil
	end
end

function LuaCsvFile:ReadCell(row, col)
	if self._csv == nil then
		return ""
	end
	return csv.readcell(self._csv, row, col)
end

function LuaCsvFile:GetRowCount()
	if self._csv == nil then
		return 0
	end
	return csv.rowcount(self._csv)
end

function LuaCsvFile:GetColCount()
	if self._csv == nil then
		return 0
	end
	return csv.colcount(self._csv)
end

