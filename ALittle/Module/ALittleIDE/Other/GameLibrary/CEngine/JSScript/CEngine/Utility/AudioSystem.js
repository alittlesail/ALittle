{
if (typeof ALittle === "undefined") ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(384201948, "ALittle.ChunkInfo", {
name : "ALittle.ChunkInfo", ns_name : "ALittle", rl_name : "ChunkInfo", hash_code : 384201948,
name_list : ["file_path","callback","channel","volume","mute"],
type_list : ["string","Functor<(string,int)>","int","double","bool"],
option_map : {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})

ALittle.AudioSystem = JavaScript.Class(undefined, {
	Ctor : function() {
		this._chunk_map = new Map();
		this._app_background = false;
		this._all_chunk_mute = false;
		this._music_mute = false;
		this._music_valume = 1;
	},
	Setup : function() {
		A_OtherSystem.AddEventListener(___all_struct.get(521107426), this, this.HandleDidEnterBackground);
		A_OtherSystem.AddEventListener(___all_struct.get(760325696), this, this.HandleDidEnterForeground);
	},
	Shutdown : function() {
	},
	HandleDidEnterBackground : function(event) {
		this._app_background = true;
		this.UpdateAllChunkVolume();
		this.UpdateMusicVolume();
	},
	HandleDidEnterForeground : function(event) {
		this._app_background = false;
		this.UpdateAllChunkVolume();
		this.UpdateMusicVolume();
	},
	UpdateChunkVolume : function(info) {
		let real_volume = info.volume;
		if (info.mute || this._app_background || this._all_chunk_mute) {
			real_volume = 0;
		}
		__CPPAPI_AudioSystem.SetChunkVolume(info.channel, real_volume);
	},
	UpdateMusicVolume : function() {
		let real_volume = this._music_valume;
		if (this._music_mute || this._app_background) {
			real_volume = 0;
		}
		__CPPAPI_AudioSystem.SetMusicVolume(real_volume);
	},
	UpdateAllChunkVolume : function() {
		for (let [k, v] of this._chunk_map) {
			if (v === undefined) continue;
			this.UpdateChunkVolume(v);
		}
	},
	SetAllChunkMute : function(mute) {
		if (this._all_chunk_mute === mute) {
			return;
		}
		this._all_chunk_mute = mute;
		this.UpdateAllChunkVolume();
	},
	SetMusicMute : function(mute) {
		if (this._music_mute === mute) {
			return;
		}
		this._music_mute = mute;
		this.UpdateMusicVolume();
	},
	GetAllChunkMute : function() {
		return this._all_chunk_mute;
	},
	GetMusicMute : function() {
		return this._music_mute;
	},
	AddChunkCache : function(file_path) {
		__CPPAPI_AudioSystem.AddChunkCache(file_path);
	},
	RemoveChunkCache : function(file_path) {
		__CPPAPI_AudioSystem.RemoveChunkCache(file_path);
	},
	StartChunk : function(file_path, loop, callback) {
		if (loop === undefined) {
			loop = 1;
		}
		let channel = __CPPAPI_AudioSystem.StartChunk(file_path, loop);
		if (channel < 0) {
			return -1;
		}
		let info = {};
		info.file_path = file_path;
		info.callback = callback;
		info.channel = channel;
		info.volume = __CPPAPI_AudioSystem.GetChunkVolume(channel);
		info.mute = false;
		this._chunk_map.set(channel, info);
		this.UpdateChunkVolume(info);
		return channel;
	},
	StopChunk : function(channel) {
		let info = this._chunk_map.get(channel);
		if (info === undefined) {
			return;
		}
		this._chunk_map.delete(channel);
		__CPPAPI_AudioSystem.StopChunk(channel);
	},
	SetChunkMute : function(channel, mute) {
		let info = this._chunk_map.get(channel);
		if (info === undefined) {
			return;
		}
		if (info.mute === mute) {
			return;
		}
		info.mute = mute;
		this.UpdateChunkVolume(info);
	},
	GetChunkMute : function(channel) {
		let info = this._chunk_map.get(channel);
		if (info === undefined) {
			return false;
		}
		return info.mute;
	},
	SetChunkVolume : function(channel, volume) {
		let info = this._chunk_map.get(channel);
		if (info === undefined) {
			return;
		}
		info.volume = volume;
		this.UpdateChunkVolume(info);
	},
	GetChunkVolume : function(channel) {
		let info = this._chunk_map.get(channel);
		if (info === undefined) {
			return 0;
		}
		return info.volume;
	},
	HandleAudioChunkStopedEvent : function(channel) {
		let info = this._chunk_map.get(channel);
		if (info === undefined) {
			return;
		}
		this._chunk_map.delete(channel);
		if (info.callback === undefined) {
			return;
		}
		info.callback(info.file_path, info.channel);
	},
	StartMusic : function(file_path, loop) {
		if (loop === undefined) {
			loop = 1;
		}
		let result = __CPPAPI_AudioSystem.StartMusic(file_path, loop);
		if (result) {
			return false;
		}
		this._music_valume = __CPPAPI_AudioSystem.GetMusicVolume();
		this.UpdateMusicVolume();
		return result;
	},
	StopMusic : function() {
		__CPPAPI_AudioSystem.StopMusic();
	},
	StartRecord : function(file_path) {
		return __CPPAPI_AudioSystem.StartRecord(file_path);
	},
	IsRecording : function() {
		return __CPPAPI_AudioSystem.IsRecording();
	},
	StopRecord : function() {
		__CPPAPI_AudioSystem.StopRecord();
	},
}, "ALittle.AudioSystem");

window.A_AudioSystem = ALittle.NewObject(ALittle.AudioSystem);
}