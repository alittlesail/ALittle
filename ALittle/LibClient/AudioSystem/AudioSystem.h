
#ifndef _ALITTLE_AUDIOSYSTEM_H_
#define _ALITTLE_AUDIOSYSTEM_H_

#include <map>
#include <string>
#include <vector>

struct CarpMixerChunk;
class CarpMixer;

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
	CarpMixerChunk* LoadChunk(const std::string& file_path);

public:
	void AddChunkCache(const char* file_path);
	void RemoveChunkCache(const char* file_path);

public:
	static void HandleChunkStoppedForMixer(int channel);
	static void HandleChunkStoppedForLua(unsigned int event_type, void* data1, void* data2);

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

	CarpMixer* m_mixer = nullptr;

private:
	AudioSystem();
	~AudioSystem();
};

} // ALittle

#define g_AudioSystem ALittle::AudioSystem::Instance()

#endif // _ALITTLE_AUDIOSYSTEM_H_
