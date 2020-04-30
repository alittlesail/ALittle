-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = GetAllStruct()

RegStruct(384201948, "ALittle.ChunkInfo", {
name = "ALittle.ChunkInfo", ns_name = "ALittle", rl_name = "ChunkInfo", hash_code = 384201948,
name_list = {"file_path","callback","channel","volume","mute"},
type_list = {"string","Functor<(string,int)>","int","double","bool"},
option_map = {}
})
RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})

AudioSystem = Lua.Class(nil, "ALittle.AudioSystem")

function AudioSystem:Ctor()
	___rawset(self, "_chunk_map", {})
	___rawset(self, "_app_background", false)
	___rawset(self, "_all_chunk_mute", false)
	___rawset(self, "_music_mute", false)
	___rawset(self, "_music_valume", 1)
	A_OtherSystem:AddEventListener(___all_struct[521107426], self, self.HandleDidEnterBackground)
	A_OtherSystem:AddEventListener(___all_struct[760325696], self, self.HandleDidEnterForeground)
end

function AudioSystem:HandleDidEnterBackground(event)
	self._app_background = true
	self:UpdateAllChunkVolume()
	self:UpdateMusicVolume()
end

function AudioSystem:HandleDidEnterForeground(event)
	self._app_background = false
	self:UpdateAllChunkVolume()
	self:UpdateMusicVolume()
end

function AudioSystem:UpdateChunkVolume(info)
	local real_volume = info.volume
	if info.mute or self._app_background or self._all_chunk_mute then
		real_volume = 0
	end
	__CPPAPI_AudioSystem:SetChunkVolume(info.channel, real_volume)
end

function AudioSystem:UpdateMusicVolume()
	local real_volume = self._music_valume
	if self._music_mute or self._app_background then
		real_volume = 0
	end
	__CPPAPI_AudioSystem:SetMusicVolume(real_volume)
end

function AudioSystem:UpdateAllChunkVolume()
	for k, v in ___pairs(self._chunk_map) do
		self:UpdateChunkVolume(v)
	end
end

function AudioSystem:SetAllChunkMute(mute)
	if self._all_chunk_mute == mute then
		return
	end
	self._all_chunk_mute = mute
	self:UpdateAllChunkVolume()
end

function AudioSystem:SetMusicMute(mute)
	if self._music_mute == mute then
		return
	end
	self._music_mute = mute
	self:UpdateMusicVolume()
end

function AudioSystem:GetAllChunkMute()
	return self._all_chunk_mute
end

function AudioSystem:GetMusicMute()
	return self._music_mute
end

function AudioSystem:AddChunkCache(file_path)
	__CPPAPI_AudioSystem:AddChunkCache(file_path)
end

function AudioSystem:RemoveChunkCache(file_path)
	__CPPAPI_AudioSystem:RemoveChunkCache(file_path)
end

function AudioSystem:StartChunk(file_path, loop, callback)
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

function AudioSystem:StopChunk(channel)
	local info = self._chunk_map[channel]
	if info == nil then
		return
	end
	self._chunk_map[channel] = nil
	__CPPAPI_AudioSystem:StopChunk(channel)
end

function AudioSystem:SetChunkMute(channel, mute)
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

function AudioSystem:GetChunkMute(channel)
	local info = self._chunk_map[channel]
	if info == nil then
		return false
	end
	return info.mute
end

function AudioSystem:SetChunkVolume(channel, volume)
	local info = self._chunk_map[channel]
	if info == nil then
		return
	end
	info.volume = volume
	self:UpdateChunkVolume(info)
end

function AudioSystem:GetChunkVolume(channel)
	local info = self._chunk_map[channel]
	if info == nil then
		return 0
	end
	return info.volume
end

function AudioSystem:HandleAudioChunkStopedEvent(channel)
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

function AudioSystem:StartMusic(file_path, loop)
	if loop == nil then
		loop = 1
	end
	local result = __CPPAPI_AudioSystem:StartMusic(file_path, loop)
	if result then
		return false
	end
	self._music_valume = __CPPAPI_AudioSystem:GetMusicVolume()
	self:UpdateMusicVolume()
	return result
end

function AudioSystem:StopMusic()
	__CPPAPI_AudioSystem:StopMusic()
end

function AudioSystem:StartRecord(file_path)
	return __CPPAPI_AudioSystem:StartRecord(file_path)
end

function AudioSystem:IsRecording()
	return __CPPAPI_AudioSystem:IsRecording()
end

function AudioSystem:StopRecord()
	__CPPAPI_AudioSystem:StopRecord()
end

_G.A_AudioSystem = AudioSystem()
