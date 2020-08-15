
#ifndef _ALITTLE_AUDIOSYSTEM_H_
#define _ALITTLE_AUDIOSYSTEM_H_

#include <map>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_mixer.h>

extern "C" {
#include "bcg729/bcg729/decoder.h"
#include "bcg729/bcg729/encoder.h"
};

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

private:
	bool InitMixer();
	bool m_mixer_init;				// audio system init or not

public:
	int StartChunk(const char* file_path, int loop);
	bool StopChunk(int channel);
	bool SetChunkVolume(int channel, float volume);
	float GetChunkVolume(int channel);

private:
	Mix_Chunk* LoadChunk(const std::string& file_path);
	void G729Decode(unsigned char* buffer, int buffer_len, short* sample_data);

public:
	void AddChunkCache(const char* file_path);
	void RemoveChunkCache(const char* file_path);

public:
	static void HandleChunkStopedForMixer(int channel);
	static void HandleChunkStopedForLua(unsigned int event_type, void* data1, void* data2);

public:
	bool StartMusic(const char* file_path, int loop);
	void StopMusic();
	bool SetMusicVolume(float volume);
	float GetMusicVolume();

public:
	static void HandleMusicStopedForMixer();
	static void HandleMusicStopedForLua(unsigned int event_type, void* data1, void* data2);

public:
	bool StartRecord(const char* file_path);
	void StopRecord();
	bool IsRecording() const { return m_is_recording; }

private:
	static void RecordCallback(void *udata, Uint8 *stream, int len);

private:
	struct ChannelInfo
	{
		ChannelInfo() : chunk(nullptr) {}
		Mix_Chunk* chunk;
		std::string file_path;
	};
	std::vector<ChannelInfo> m_channel_list;

private:
	typedef std::map<std::string, Mix_Chunk*> MixChunkCache;
	MixChunkCache m_cache_map;

private:
	Mix_Music* m_music;

private:
	bool m_is_recording;
	int m_record_device;
	SDL_RWops* m_record_file;
	bcg729EncoderChannelContextStruct* m_record_encoder;

private:
	AudioSystem();
	~AudioSystem();
};

} // ALittle

#define g_AudioSystem ALittle::AudioSystem::Instance()

#endif // _ALITTLE_AUDIOSYSTEM_H_
