
module("HelloWorld", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


function Main()
	ALittle.Log("HelloWorld")
	local all_in_one = {}
	local map = ALittle.File_GetFileAttrByDir("ALittle/Module/G2048/UI")
	for path, _ in ___pairs(map) do
		local json = ALittle.File_ReadJsonFromStdFile(path)
		for name, o in ___pairs(json) do
			all_in_one[name] = o
		end
	end
	ALittle.File_WriteJsonFromStdFile(all_in_one, "ALittle/Module/G2048/ui_all_in_one.json")
	A_Schedule:Run()
end

