-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(384201948, "ALittle.ChunkInfo", {
name = "ALittle.ChunkInfo", ns_name = "ALittle", rl_name = "ChunkInfo", hash_code = 384201948,
name_list = {"file_path","callback","channel","volume","mute"},
type_list = {"string","Functor<(string,int)>","int","double","bool"},
option_map = {}
})

ALittle.AudioSystem = Lua.Class(nil, "ALittle.AudioSystem")

function ALittle.AudioSystem:Ctor()
	___rawset(self, "_chunk_map", {})
	___rawset(self, "_app_background", false)
	___rawset(self, "_all_chunk_mute", false)
	A_OtherSystem:AddEventListener(___all_struct[521107426], self, self.HandleDidEnterBackground)
	A_OtherSystem:AddEventListener(___all_struct[760325696], self, self.HandleDidEnterForeground)
end

function ALittle.AudioSystem:HandleDidEnterBackground(event)
	self._app_background = true
	self:UpdateAllChunkVolume()
end

function ALittle.AudioSystem:HandleDidEnterForeground(event)
	self._app_background = false
	self:UpdateAllChunkVolume()
end

function ALittle.AudioSystem:UpdateChunkVolume(info)
	local real_volume = info.volume
	if info.mute or self._app_background or self._all_chunk_mute then
		real_volume = 0
	end
	__CPPAPI_AudioSystem:SetChunkVolume(info.channel, real_volume)
end

function ALittle.AudioSystem:UpdateAllChunkVolume()
	for k, v in ___pairs(self._chunk_map) do
		self:UpdateChunkVolume(v)
	end
end

function ALittle.AudioSystem:SetAllChunkMute(mute)
	if self._all_chunk_mute == mute then
		return
	end
	self._all_chunk_mute = mute
	self:UpdateAllChunkVolume()
end

function ALittle.AudioSystem:GetAllChunkMute()
	return self._all_chunk_mute
end

function ALittle.AudioSystem:AddChunkCache(file_path)
	__CPPAPI_AudioSystem:AddChunkCache(file_path)
end

function ALittle.AudioSystem:RemoveChunkCache(file_path)
	__CPPAPI_AudioSystem:RemoveChunkCache(file_path)
end

function ALittle.AudioSystem:StartChunk(file_path, loop, callback)
	if loop == nil then
		loop = 1
	end
	local channel = __CPPAPI_AudioSystem:StartChunk(file_path, loop)
	if channel < 0 then
		return -1
	end
	local info = {}
	info.file_path = file_path
	info.callback = callback
	info.channel = channel
	info.volume = __CPPAPI_AudioSystem:GetChunkVolume(channel)
	info.mute = false
	self._chunk_map[channel] = info
	self:UpdateChunkVolume(info)
	return channel
end

function ALittle.AudioSystem:StopChunk(channel)
	local info = self._chunk_map[channel]
	if info == nil then
		return
	end
	self._chunk_map[channel] = nil
	__CPPAPI_AudioSystem:StopChunk(channel)
end

function ALittle.AudioSystem:SetChunkMute(channel, mute)
	local info = self._chunk_map[channel]
	if info == nil then
		return
	end
	if info.mute == mute then
		return
	end
	info.mute = mute
	self:UpdateChunkVolume(info)
end

function ALittle.AudioSystem:GetChunkMute(channel)
	local info = self._chunk_map[channel]
	if info == nil then
		return false
	end
	return info.mute
end

function ALittle.AudioSystem:SetChunkVolume(channel, volume)
	local info = self._chunk_map[channel]
	if info == nil then
		return
	end
	info.volume = volume
	self:UpdateChunkVolume(info)
end

function ALittle.AudioSystem:GetChunkVolume(channel)
	local info = self._chunk_map[channel]
	if info == nil then
		return 0
	end
	return info.volume
end

function ALittle.AudioSystem:HandleAudioChunkStoppedEvent(channel)
	local info = self._chunk_map[channel]
	if info == nil then
		return
	end
	self._chunk_map[channel] = nil
	if info.callback == nil then
		return
	end
	info.callback(info.file_path, info.channel)
end

_G.A_AudioSystem = ALittle.AudioSystem()
end