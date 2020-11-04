-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ADeeplearning == nil then _G.ADeeplearning = {} end
local ___pairs = pairs
local ___ipairs = ipairs


ADeeplearning.g_GConfig = nil
ADeeplearning.GCenter = Lua.Class(nil, "ADeeplearning.GCenter")

function ADeeplearning.GCenter:Setup()
	ADeeplearning.g_GConfig = ALittle.CreateConfigSystem(ADeeplearning.g_ModuleBasePath .. "/User.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(1)
	self._main_layer = ALittle.DisplayLayout(ADeeplearning.g_Control)
	self._main_layer.width_type = 4
	self._main_layer.height_type = 4
	ADeeplearning.g_LayerGroup:AddChild(self._main_layer, nil)
	self._dialog_layer = ALittle.DisplayLayout(ADeeplearning.g_Control)
	self._dialog_layer.width_type = 4
	self._dialog_layer.height_type = 4
	ADeeplearning.g_LayerGroup:AddChild(self._dialog_layer, nil)
	local main_scene = ADeeplearning.g_Control:CreateControl("main_scene")
	self._main_layer:AddChild(main_scene)
end

function ADeeplearning.GCenter:Shutdown()
end

function ADeeplearning.GCenter:Wav2MFCC(max_count)
	local model = deeplearning.DeeplearningSpeechModel(nil)
	model:Wav2MFCC(ADeeplearning.g_ModuleBasePath .. "Data/thchs30.txt", "D:/Users/IGG/Downloads/data_thchs30/data/", max_count, ADeeplearning.g_ModuleBasePath .. "Data/thchs30_word.dat", ADeeplearning.g_ModuleBasePath .. "Data/thchs30_speech.dat")
end

function ADeeplearning.GCenter:Thchs302DescFile(thchs30_path)
	local out_file = io.open(ADeeplearning.g_ModuleBasePath .. "Data/thchs30.txt", "w")
	local file_map = ALittle.File_GetFileAttrByDir(thchs30_path)
	for file_path, _ in ___pairs(file_map) do
		if ALittle.File_GetFileExtByPath(file_path) == "trn" then
			local content = ALittle.File_ReadTextFromStdFile(file_path)
			out_file:write(ALittle.File_GetJustFileNameByPath(file_path))
			out_file:write("\n")
			out_file:write(content)
		end
	end
	out_file:close()
end

ADeeplearning.g_GCenter = ADeeplearning.GCenter()
end