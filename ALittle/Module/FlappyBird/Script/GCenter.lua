
module("FlappyBird", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


g_GConfig = nil
GCenter = Lua.Class(nil, "FlappyBird.GCenter")

function GCenter:Ctor()
end

function GCenter:Setup()
	g_GConfig = ALittle.CreateConfigSystem(g_ModuleBasePath .. "/User.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(5, 2)
	self._main_layer = ALittle.DisplayLayout(g_Control)
	self._main_layer.width_type = 4
	self._main_layer.height_type = 4
	g_LayerGroup:AddChild(self._main_layer, nil)
	self._dialog_layer = ALittle.DisplayLayout(g_Control)
	self._dialog_layer.width_type = 4
	self._dialog_layer.height_type = 4
	g_LayerGroup:AddChild(self._dialog_layer, nil)
	self._main_scene = g_Control:CreateControl("main_scene", self, self._main_layer)
	self._main_scene.visible = false
	self._main_menu = g_Control:CreateControl("main_menu", self, nil)
	self._dialog_layer:AddChild(self._main_menu, nil)
	self._main_menu.visible = true
	self._game_over.visible = false
	self._game_title.visible = true
	self._max_score_text._user_data = g_GConfig:GetConfig("max_score", 0)
	self._max_score_text.text = self._max_score_text._user_data
	self._frame_anti = ALittle.LoopFrame(Lua.Bind(self.LoopGroundFrame, self))
end

function GCenter:Restart()
	self._ground_frame_acc = 0
	self._next_pipe_gap = 0
	self._next_pipe_up = 50
	self._flying = false
	self._dieing = false
	self._bird.y = self._bg.height / 2
	self._bird.x = 0
	self._bird.angle = 0
	self._bird.visible = true
	self._bird:Play()
	self._game_over.visible = false
	self._score_text.text = "0"
	self._score_text._user_data = 0
	self._pipe_container:RemoveAllChild()
	self._frame_anti:Start()
end

function GCenter:LoopGroundFrame(frame_time)
	local scale = 20
	if not self._dieing then
		local cur_score = self._score_text._user_data + frame_time
		self._score_text._user_data = cur_score
		self._score_text.text = ALittle.Math_Floor(cur_score / 100)
	end
	local total_time = (self._ground.width - self._main_scene.width) * scale
	self._ground_frame_acc = self._ground_frame_acc + (frame_time)
	if self._ground_frame_acc > total_time then
		self._ground_frame_acc = (self._ground_frame_acc % total_time)
	end
	self._ground.x = -self._ground_frame_acc / scale
	if self._bird.x + self._bird.width / 2 < self._bg.width / 2 then
		self._bird.x = self._bird.x + (frame_time / scale)
	else
		local create_pipe = false
		if self._pipe_container.child_count == 0 then
			create_pipe = true
		else
			local pipe = self._pipe_container.childs[self._pipe_container.child_count]
			local right = pipe.x + pipe.width
			if self._bg.width - right > self._next_pipe_gap then
				create_pipe = true
			end
			pipe = self._pipe_container.childs[1]
			if pipe.x + pipe.width < 0 then
				self._pipe_container:RemoveChild(pipe)
			end
		end
		if create_pipe then
			local pipe = g_Control:CreateControl("pipe")
			self._pipe_container:AddChild(pipe)
			local total_height = self._bg.height - self._ground.height
			local half_height = total_height / 2
			if ALittle.Math_RandomInt(1, 100) <= self._next_pipe_up then
				local min_y = ALittle.Math_Floor(-pipe.height + pipe.height / 4)
				local max_y = ALittle.Math_Floor(half_height - pipe.height)
				pipe.y = ALittle.Math_RandomInt(min_y, max_y)
				self._next_pipe_up = 30
			else
				local min_y = ALittle.Math_Floor(half_height)
				local max_y = ALittle.Math_Floor(total_height - pipe.height / 4)
				pipe.y = ALittle.Math_RandomInt(min_y, max_y)
				self._next_pipe_up = 70
			end
			pipe.x = self._bg.width
			self._next_pipe_gap = ALittle.Math_RandomInt(50, 100)
		end
		for index, child in ___ipairs(self._pipe_container.childs) do
			child.x = child.x - (frame_time / scale)
		end
	end
	if self._dieing then
		self._bird.y = self._bird.y + (frame_time / scale) * 2
		if self._bird.y <= 0 or self._bird.y + self._bird.height >= self._bg.height - self._ground.height then
			self:ShowGameOver()
		end
	else
		if self._flying then
			self._bird.y = self._bird.y - (frame_time / scale) * 2
		else
			self._bird.y = self._bird.y + (frame_time / scale) * 1.5
		end
		for index, child in ___ipairs(self._pipe_container.childs) do
			local left = self._bird.x + 5
			local right = self._bird.x + self._bird.width - 5
			local top = self._bird.y + 5
			local bottom = self._bird.y + self._bird.height - 5
			if (left > child.x and left <= child.x + child.width or right > child.x and right <= child.x + child.width) and (top > child.y and top <= child.y + child.height or bottom > child.y and bottom <= child.y + child.height) then
				self._dieing = true
				break
			end
		end
		if self._bird.y <= 0 or self._bird.y + self._bird.height >= self._bg.height - self._ground.height then
			self._dieing = true
		end
		if self._dieing then
			self._bird.angle = -60
			self._bird:Stop()
		end
	end
end

function GCenter:HandleStartClick(event)
	self._main_menu.visible = false
	self._main_scene.visible = true
	self:Restart()
end

function GCenter:HandleLButtonDown(event)
	self._tip_1.visible = false
	self._tip_2.visible = false
	self._flying = true
end

function GCenter:HandleLButtonUp(event)
	self._flying = false
end

function GCenter:ShowGameOver()
	self._main_menu.visible = true
	self._main_scene.visible = false
	self._game_over.visible = true
	self._game_title.visible = false
	self._bird:Stop()
	self._frame_anti:Stop()
	if self._max_score_text._user_data < self._score_text._user_data then
		self._max_score_text._user_data = self._score_text._user_data
		self._max_score_text.text = self._max_score_text._user_data
		g_GConfig:SetConfig("max_score", ALittle.Math_Floor(self._max_score_text._user_data / 100), nil)
	end
	return true
end

function GCenter:Shutdown()
	self._bird:Stop()
	self._frame_anti:Stop()
end

g_GCenter = GCenter()
