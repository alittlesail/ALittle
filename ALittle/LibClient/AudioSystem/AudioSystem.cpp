
#include "AudioSystem.h"

#include "SDL.h"

#include "ALittle/LibClient/ScheduleSystem/EventDefine.h"
#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"
#include "ALittle/LibClient/Helper/FileHelperEx.h"
#include "ALittle/LibClient/ScriptSystem/ScriptSystemEx.h"
#include "ALittle/LibClient/Tool/MemoryPool.h"
#include "ALittle/LibClient/Tool/LocalFile.h"

#include "ALittle/LibCommon/Helper/FileHelper.h"
#include "ALittle/LibCommon/Helper/StringHelper.h"
#include "ALittle/LibCommon/Helper/LogHelper.h"

#include "Carp/carp_mixer.h"

namespace ALittle
{

AudioSystem::AudioSystem()
{
}

AudioSystem::~AudioSystem()
{
}

AudioSystem& AudioSystem::Instance()
{
	static AudioSystem instance;
	return instance;
}

//=========================================================================
void AudioSystem::Setup()
{
	m_channel_list.resize(CARP_MIXER_CHANNELS);
	
	// 注册回调
	g_ScheduleSystem.RegisterHandle(CHUNK_STOPED, HandleChunkStopedForLua);
}

void AudioSystem::Shutdown()
{
	// 释放音效
	for (unsigned int i = 0; i < CARP_MIXER_CHANNELS; ++i)
	{
		if (m_channel_list[i].chunk)
		{
			carp_mixer_free_chunk(m_channel_list[i].chunk);
			m_cache_map.erase(m_channel_list[i].file_path);
		}
		m_channel_list[i].chunk = nullptr;
		m_channel_list[i].file_path = "";
	}
	// 释放缓存
	for (auto it = m_cache_map.begin(); it != m_cache_map.end(); ++it)
		carp_mixer_free_chunk(it->second);
	m_cache_map.clear();

	// 关闭音效系统
	carp_mixer_shutdown();
}

//=========================================================================
void AudioSystem::RegisterToScript(ScriptSystem& script_system)
{
	lua_State* l = script_system.GetLuaState();

	luabridge::getGlobalNamespace(l)
		.beginClass<AudioSystem>("__CPPAPIAudioSystem")
		.addFunction("AddChunkCache", &AudioSystem::AddChunkCache)
		.addFunction("RemoveChunkCache", &AudioSystem::RemoveChunkCache)
		.addFunction("StartChunk", &AudioSystem::StartChunk)
		.addFunction("StopChunk", &AudioSystem::StopChunk)
		.addFunction("SetChunkVolume", &AudioSystem::SetChunkVolume)
		.addFunction("GetChunkVolume", &AudioSystem::GetChunkVolume)
		.endClass();

	luabridge::setGlobal(l, this, "__CPPAPI_AudioSystem");
}

void AudioSystem::AddChunkCache(const char* file_path)
{
	if (file_path == nullptr) return;

	MixChunkCache::iterator it = m_cache_map.find(file_path);
	if (it != m_cache_map.end()) return;

	m_cache_map[file_path] = nullptr;
}

void AudioSystem::RemoveChunkCache(const char* file_path)
{
	if (file_path == nullptr) return;

	MixChunkCache::iterator it = m_cache_map.find(file_path);
	if (it == m_cache_map.end()) return;

	carp_mixer_chunk_t* chunk = it->second;
	m_cache_map.erase(it);

	if (chunk == nullptr) return;

	// 如果正在播放就返回，否则就释放音效
	for (unsigned int i = 0; i < CARP_MIXER_CHANNELS; ++i)
	{
		if (m_channel_list[i].chunk == chunk)
			return;
	}

	carp_mixer_free_chunk(chunk);
}

int AudioSystem::StartChunk(const char* file_path, int loop)
{
	if (file_path == nullptr)
	{
		ALITTLE_ERROR("file_path is nil");
		return -1;
	}
	
	carp_mixer_chunk_t* chunk = nullptr;
	
	// 先从缓存里面查找
	MixChunkCache::iterator cache_it = m_cache_map.find(file_path);
	if (cache_it != m_cache_map.end()) chunk = cache_it->second;

	// 如果缓存没有，那么加载音效
	if (chunk == nullptr)
	{
		chunk = LoadChunk(file_path);
		if (chunk == nullptr)
		{
			ALITTLE_ERROR("chunk load failed:" << file_path);
			return -1;
		}

		// 如果需要缓存，那么就放在缓存中
		if (cache_it != m_cache_map.end())
			cache_it->second = chunk;
	}

	// 播放音效
	int channel = carp_mixer_play_chunk(chunk, 1.0f, loop, HandleChunkStopedForMixer);
	if (channel < 0)
	{
		ALITTLE_ERROR("chunk play fialed:" << file_path);
		if (cache_it == m_cache_map.end()) carp_mixer_free_chunk(chunk);
		return -1;
	}

	// 保存音效相关信息
	m_channel_list[channel].chunk = chunk;
	m_channel_list[channel].file_path = file_path;

	return channel;
}

bool AudioSystem::StopChunk(int channel)
{
	carp_mixer_stop_channel(channel);
	return true;
}

bool AudioSystem::SetChunkVolume(int channel, float volume)
{
	if (volume < 0.0f) volume = 0.0f;
	else if (volume > 1.0f) volume = 1.0f;
	carp_mixer_set_volume(channel, volume);
	return true;
}

float AudioSystem::GetChunkVolume(int channel)
{
	return carp_mixer_get_volume(channel);
}

carp_mixer_chunk_t* AudioSystem::LoadChunk(const std::string& file_path)
{
	LocalFile file;
	file.SetPath(file_path.c_str());
	if (!file.Load()) return nullptr;
	return carp_mixer_load_chunk(file.GetContent(), file.GetSize());
}

void AudioSystem::HandleChunkStopedForMixer(int channel)
{
	void* data = nullptr;
	memcpy(&data, &channel, sizeof(int));
	g_ScheduleSystem.PushUserEvent(CHUNK_STOPED, data);
}

void AudioSystem::HandleChunkStopedForLua(unsigned int event_type, void* data1, void* data2)
{
	int channel = 0;
	memcpy(&channel, &data1, sizeof(int));
	if (channel < 0 || channel >= static_cast<int>(g_AudioSystem.m_channel_list.size()))
		return;

	AudioSystem::ChannelInfo& info = g_AudioSystem.m_channel_list[channel];
	if (info.chunk)
	{
		// 如果不需要缓存，那么播放完毕就直接释放
		MixChunkCache::iterator it = g_AudioSystem.m_cache_map.find(info.file_path);
		if (it == g_AudioSystem.m_cache_map.end())
		{
			carp_mixer_free_chunk(info.chunk);
		}
		// 如果需要缓存，那么就放进缓存区
		else
		{
			if (it->second == nullptr)
				it->second = info.chunk;
			else if (it->second != info.chunk)
				carp_mixer_free_chunk(info.chunk);
		}
	}
	// 初始化通道数据
	info.chunk = nullptr;
	info.file_path = "";

	g_ScriptSystem.Invoke("__ALITTLEAPI_AudioChunkStopedEvent", channel);
}

} // ALittle
