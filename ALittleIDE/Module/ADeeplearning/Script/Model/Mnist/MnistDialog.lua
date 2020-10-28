-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ADeeplearning == nil then _G.ADeeplearning = {} end
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ALittle.Dialog, " extends class:ALittle.Dialog is nil")
ADeeplearning.MnistDialog = Lua.Class(ALittle.Dialog, "ADeeplearning.MnistDialog")

function ADeeplearning.MnistDialog:TCtor()
	self._train:AddEventListener(___all_struct[958494922], self, self.HandleChanged)
end

function ADeeplearning.MnistDialog:HandleChanged(event)
	self._test:Reset()
end

end