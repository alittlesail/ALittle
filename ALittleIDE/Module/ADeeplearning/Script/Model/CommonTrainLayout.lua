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

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ADeeplearning.CommonTrainLayout = Lua.Class(ALittle.DisplayLayout, "ADeeplearning.CommonTrainLayout")

function ADeeplearning.CommonTrainLayout:TCtor()
	self._start_button.disabled = false
	self._stop_button.disabled = true
end

function ADeeplearning.CommonTrainLayout.__getter:model()
	return nil
end

function ADeeplearning.CommonTrainLayout:HandleStartClick(event)
	if self._loop ~= nil then
		return
	end
	self._start_button:DelayDisable()
	self._stop_button.disabled = false
	self._loop = ALittle.LoopFrame(Lua.Bind(self.UpdateFrame, self))
	A_WeakLoopSystem:AddUpdater(self._loop)
	self._total_train_count_text.text = 0
	self._cur_train_count_text.text = 0
	self._train_round_text.text = 0
	self._cur_right_count_text.text = 0
	self._stat:Init(1, ALittle.Math_Floor(self._stat.width), ALittle.Math_Floor(self._stat.height))
	self.model:Load(self._model_path)
	self.model:StartTraining()
end

function ADeeplearning.CommonTrainLayout:HandleStopClick(event)
	if self._loop == nil then
		return
	end
	self._start_button.disabled = false
	self._stop_button:DelayDisable()
	if self._loop ~= nil then
		A_WeakLoopSystem:RemoveUpdater(self._loop)
		self._loop = nil
	end
	self.model:StopTraining()
	self.model:Save(self._model_path)
	self:DispatchEvent(___all_struct[958494922], {})
end

function ADeeplearning.CommonTrainLayout:UpdateFrame(frame_time)
	self.model:HandleEvent()
	local has_loss = false
	while self.model:HasResult() do
		has_loss = true
		local loss = self.model:GetLoss()
		local right = self.model:GetRight()
		self._stat:AddValue(loss, right)
	end
	if has_loss then
		self._total_train_count_text.text = self.model:GetTotalTrainCount()
		self._cur_train_count_text.text = self.model:GetCurTrainCount()
		self._train_round_text.text = self.model:GetTrainRound()
		self._cur_right_count_text.text = self.model:GetCurRightCount()
		self._loss_average_text.text = ALittle.Math_Floor(self._stat:GetAverageValue() * 10000) / 10000
	end
end

end