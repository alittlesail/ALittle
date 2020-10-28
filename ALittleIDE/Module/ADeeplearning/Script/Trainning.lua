-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ADeeplearning == nil then _G.ADeeplearning = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function ADeeplearning.TrainningMnist()
	local model_file_path = ADeeplearning.g_ModuleBasePath .. "Other/mnist.model"
	local mnist = deeplearning.DeeplearningMnistModel()
	local model_file
	if ALittle.File_GetFileAttr(model_file_path) ~= nil then
		model_file = model_file_path
	end
	mnist:Init(model_file, ADeeplearning.g_ModuleBasePath .. "Data/train-images.idx3-ubyte", ADeeplearning.g_ModuleBasePath .. "Data/train-labels.idx1-ubyte")
	local i = 1
	while true do
		if not(i < 1000) then break end
		local loss = mnist:Training()
		ALittle.Log(loss)
		i = i+(1)
	end
	mnist:Save(model_file_path)
end

end