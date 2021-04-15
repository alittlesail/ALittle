#ifndef ALITTLE_AUDIO_INCLUDED
#define ALITTLE_AUDIO_INCLUDED

#include <map>
#include <vector>

#include "alittle_script.hpp"
#include "Carp/carp_lua.hpp"
#include "Carp/carp_mixer.hpp"
#include "Carp/carp_rwops_bind.hpp"

class ALittleAudio;
extern ALittleAudio s_alittle_audio;

class ALittleAudio
{
public:
	ALittleAudio()
	{
		m_channel_list.resize(CARP_MIXER_CHANNELS);
	}

	void Setup(int sample_rate, int channels)
	{
		s_carp_mixer.Setup(sample_rate, channels);
	}

	void Shutdown()
	{
		// 释放音效
		for (unsigned int i = 0; i < CARP_MIXER_CHANNELS; ++i)
		{
			if (m_channel_list[i].chunk)
			{
				s_carp_mixer.FreeChunk(m_channel_list[i].chunk);
				m_cache_map.erase(m_channel_list[i].file_path);
			}
			m_channel_list[i].chunk = nullptr;
			m_channel_list[i].file_path = "";
		}
		// 释放缓存
		for (auto it = m_cache_map.begin(); it != m_cache_map.end(); ++it)
		{
			s_carp_mixer.FreeChunk(it->second);
			it->second = nullptr;
		}

		// 关闭音效系统
		s_carp_mixer.Shutdown();
	}

public:
	// 请使用最新版本的ogg音频转换器（比如https://convertio.co/），否则会播放失败
	int StartChannel(const char* file_path, int loop)
	{
		if (file_path == nullptr)
		{
			CARP_ERROR("file_path is nil");
			return -1;
		}

		CarpMixerChunk* chunk = nullptr;

		// 先从缓存里面查找
		auto cache_it = m_cache_map.find(file_path);
		if (cache_it != m_cache_map.end()) chunk = cache_it->second;

		// 如果缓存没有，那么加载音效
		if (chunk == nullptr)
		{
			CarpLocalFile file;
			file.SetPath(file_path);
			if (!file.Load(false))
			{
				CARP_ERROR("chunk load failed:" << file_path);
				return -1;
			}
			chunk = s_carp_mixer.LoadChunk(file.GetContent(), file.GetSize());
			if (chunk == nullptr)
			{
				CARP_ERROR("chunk decode failed:" << file_path);
				return -1;
			}

			// 如果需要缓存，那么就放在缓存中
			if (cache_it != m_cache_map.end())
				cache_it->second = chunk;
		}

		// 播放音效
		int channel = s_carp_mixer.PlayChunk(chunk, 1.0f, loop, HandleChunkStoppedCallback);
		if (channel < 0)
		{
			CARP_ERROR("chunk play fialed:" << file_path);
			if (cache_it == m_cache_map.end()) s_carp_mixer.FreeChunk(chunk);
			return -1;
		}

		// 保存音效相关信息
		m_channel_list[channel].chunk = chunk;
		m_channel_list[channel].file_path = file_path;

		return channel;
	}

	bool StopChannel(int channel)
	{
		s_carp_mixer.StopChannel(channel);
		ClearChannel(channel);
		return true;
	}
	
	bool SetChannelVolume(int channel, float volume) const
	{
		if (volume < 0.0f) volume = 0.0f;
		else if (volume > 1.0f) volume = 1.0f;
		s_carp_mixer.SetChannelVolume(channel, volume);
		return true;
	}
	
	float GetChannelVolume(int channel) const { return s_carp_mixer.GetChannelVolume(channel); }

public:
	bool StartStream(int sample_rate, int channels)
	{
		return s_carp_mixer.StartStream(sample_rate, channels);
	}

	bool PushStreamSample(short left_sample, short right_sample)
	{
		return s_carp_mixer.PushStreamSample(left_sample, right_sample);
	}

	void SetStreamVolume(float volume)
	{
		s_carp_mixer.SetStreamVolume(volume);
	}

	float GetStreamVolume() const
	{
		return s_carp_mixer.GetStreamVolume();
	}

	void StopStream()
	{
		s_carp_mixer.StopStream();
	}

public:
	void AddChunkCache(const char* file_path)
	{
		if (file_path == nullptr) return;
		const auto it = m_cache_map.find(file_path);
		if (it != m_cache_map.end()) return;
		m_cache_map[file_path] = nullptr;
	}
	
	void RemoveChunkCache(const char* file_path)
	{
		if (file_path == nullptr) return;

		auto it = m_cache_map.find(file_path);
		if (it == m_cache_map.end()) return;

		CarpMixerChunk* chunk = it->second;
		m_cache_map.erase(it);

		if (chunk == nullptr) return;

		// 如果正在播放就返回，否则就释放音效
		for (unsigned int i = 0; i < CARP_MIXER_CHANNELS; ++i)
		{
			if (m_channel_list[i].chunk == chunk)
				return;
		}

		s_carp_mixer.FreeChunk(chunk);
	}

public:
	void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.beginClass<ALittleAudio>("__CPPAPIAudioSystem")
			.addFunction("Setup", &ALittleAudio::Setup)
			.addFunction("AddChunkCache", &ALittleAudio::AddChunkCache)
			.addFunction("RemoveChunkCache", &ALittleAudio::RemoveChunkCache)
			.addFunction("StartChannel", &ALittleAudio::StartChannel)
			.addFunction("StopChannel", &ALittleAudio::StopChannel)
			.addFunction("SetChannelVolume", &ALittleAudio::SetChannelVolume)
			.addFunction("GetChannelVolume", &ALittleAudio::GetChannelVolume)
			.addFunction("StartStream", &ALittleAudio::StartStream)
			.addFunction("StopStream", &ALittleAudio::StopStream)
			.addFunction("PushStreamSample", &ALittleAudio::PushStreamSample)
			.addFunction("SetStreamVolume", &ALittleAudio::SetStreamVolume)
			.addFunction("GetStreamVolume", &ALittleAudio::GetStreamVolume)
			.endClass();

		luabridge::setGlobal(l_state, this, "__CPPAPI_AudioSystem");
	}

private:
	static void HandleChunkStoppedCallback(int channel)
	{
		s_carp_task_consumer.PushEvent([channel]()
		{
			s_alittle_audio.ClearChannel(channel);
			s_alittle_script.Invoke("__ALITTLEAPI_AudioChannelStoppedEvent", channel);
		});
	}

	void ClearChannel(int channel)
	{
		if (channel < 0 || channel >= static_cast<int>(m_channel_list.size()))
			return;

		ChannelInfo& info = m_channel_list[channel];
		if (info.chunk)
		{
			// 如果不需要缓存，那么播放完毕就直接释放
			auto it = m_cache_map.find(info.file_path);
			if (it == m_cache_map.end())
			{
				s_carp_mixer.FreeChunk(info.chunk);
			}
			// 如果需要缓存，那么就放进缓存区
			else
			{
				if (it->second == nullptr)
					it->second = info.chunk;
				else if (it->second != info.chunk)
					s_carp_mixer.FreeChunk(info.chunk);
			}
		}
		// 初始化通道数据
		info.chunk = nullptr;
		info.file_path = "";
	}

private:
	struct ChannelInfo
	{
		CarpMixerChunk* chunk = nullptr;
		std::string file_path;
	};
	std::vector<ChannelInfo> m_channel_list;

private:
	typedef std::map<std::string, CarpMixerChunk*> MixChunkCache;
	MixChunkCache m_cache_map;
};

#endif


#ifdef ALITTLE_AUDIO_IMPL
#ifndef ALITTLE_AUDIO_IMPL_INCLUDE
#define ALITTLE_AUDIO_IMPL_INCLUDE
ALittleAudio s_alittle_audio;

#ifdef ALITTLE_SOKOL_IMPL
#define CARP_MIXER_IMPL
#include "Carp/carp_mixer.hpp"
#endif

#endif
#endif

