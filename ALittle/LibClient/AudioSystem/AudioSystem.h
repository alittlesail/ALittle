
#ifndef _ALITTLE_AUDIOSYSTEM_H_
#define _ALITTLE_AUDIOSYSTEM_H_

#include <map>
#include <string>
#include <vector>

#include <SDL.h>

typedef struct _carp_mixer_chunk_t carp_mixer_chunk_t;

namespace ALittle
{

class ScriptSystem;

class AudioSystem
{
public:
	static AudioSystem& Instance();

public:
	void Setup();
	void Shutdown();
	void RegisterToScript(ScriptSystem& script_system);

public:
	// 请使用最新版本的ogg音频转换器（比如https://convertio.co/），否则会播放失败
	int StartChunk(const char* file_path, int loop);
	bool StopChunk(int channel);
	bool SetChunkVolume(int channel, float volume);
	float GetChunkVolume(int channel);

private:
	carp_mixer_chunk_t* LoadChunk(const std::string& file_path);

public:
	void AddChunkCache(const char* file_path);
	void RemoveChunkCache(const char* file_path);

public:
	static void HandleChunkStopedForMixer(int channel);
	static void HandleChunkStopedForLua(unsigned int event_type, void* data1, void* data2);

private:
	struct ChannelInfo
	{
		ChannelInfo() : chunk(nullptr) {}
		carp_mixer_chunk_t* chunk;
		std::string file_path;
	};
	std::vector<ChannelInfo> m_channel_list;

private:
	typedef std::map<std::string, carp_mixer_chunk_t*> MixChunkCache;
	MixChunkCache m_cache_map;

private:
	AudioSystem();
	~AudioSystem();
};

} // ALittle

#define g_AudioSystem ALittle::AudioSystem::Instance()

#endif // _ALITTLE_AUDIOSYSTEM_H_
