
#include "AudioSystem.h"

#include "SDL.h"

#include "ALittle/LibClient/Tool/MemoryPool.h"
#include "ALittle/LibClient/ScheduleSystem/EventDefine.h"
#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"
#include "ALittle/LibClient/Helper/FileHelperEx.h"
#include "ALittle/LibClient/ScriptSystem/ScriptSystemEx.h"

#include "ALittle/LibCommon/Helper/FileHelper.h"
#include "ALittle/LibCommon/Helper/StringHelper.h"
#include "ALittle/LibCommon/Helper/LogHelper.h"

namespace ALittle
{

#define AUDIO_MIX_CHANNELS MIX_CHANNELS
#define AUDIO_MIX_DEFAULT_FREQUENCY MIX_DEFAULT_FREQUENCY
#define AUDIO_CHANNEL_NUM 2

#define RECORD_CHANNEL_NUM 1
#define RECORD_FREQUENCY 8000

AudioSystem::AudioSystem()
: m_mixer_init(false), m_music(nullptr)
, m_is_recording(false), m_record_device(0), m_record_file(nullptr), m_record_encoder(nullptr)
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
	// 设置回调
	Mix_ChannelFinished(HandleChunkStopedForMixer);
	Mix_HookMusicFinished(HandleMusicStopedForMixer);

	// 设置通道数量
	Mix_AllocateChannels(AUDIO_MIX_CHANNELS);
	m_channel_list.resize(AUDIO_MIX_CHANNELS);
	
	// 注册回调
	g_ScheduleSystem.RegisterHandle(CHUNK_STOPED, HandleChunkStopedForLua);
	g_ScheduleSystem.RegisterHandle(MUSIC_STOPED, HandleMusicStopedForLua);
}

void AudioSystem::Shutdown()
{
	// 停止录音
	StopRecord();
	
	// 如果还没有初始化，那么就直接返回
	if (m_mixer_init == false) return;
	m_mixer_init = false;

	// 释放音效
	for (unsigned int i = 0; i < AUDIO_MIX_CHANNELS; ++i)
	{
		if (m_channel_list[i].chunk)
		{
			Mix_FreeChunk(m_channel_list[i].chunk);
			m_cache_map.erase(m_channel_list[i].file_path);
		}
		m_channel_list[i].chunk = nullptr;
		m_channel_list[i].file_path = "";
	}
	// 释放缓存
	for (auto it = m_cache_map.begin(); it != m_cache_map.end(); ++it)
		Mix_FreeChunk(it->second);
	m_cache_map.clear();

	// 释放背景音乐
	if (m_music)
	{
		Mix_FreeMusic(m_music);
		m_music = nullptr;
	}

	// 关闭音效系统
	Mix_CloseAudio();
}

bool AudioSystem::InitMixer()
{
	// 初始化音效系统
	if (m_mixer_init == true) return true;

	int ret = Mix_OpenAudio(AUDIO_MIX_DEFAULT_FREQUENCY, AUDIO_S16, AUDIO_CHANNEL_NUM, 4096);
	if (ret == -1) return false;
	m_mixer_init = true;
	return true;
}

//=========================================================================
void AudioSystem::RegisterToScript(ScriptSystem& script_system)
{
	lua_State* L = script_system.GetLuaState();

	luabridge::getGlobalNamespace(L)
		.beginClass<AudioSystem>("__CPPAPIAudioSystem")
		.addFunction("AddChunkCache", &AudioSystem::AddChunkCache)
		.addFunction("RemoveChunkCache", &AudioSystem::RemoveChunkCache)
		.addFunction("StartChunk", &AudioSystem::StartChunk)
		.addFunction("StopChunk", &AudioSystem::StopChunk)
		.addFunction("SetChunkVolume", &AudioSystem::SetChunkVolume)
		.addFunction("GetChunkVolume", &AudioSystem::GetChunkVolume)
		.addFunction("StartMusic", &AudioSystem::StartMusic)
		.addFunction("StopMusic", &AudioSystem::StopMusic)
		.addFunction("SetMusicVolume", &AudioSystem::SetMusicVolume)
		.addFunction("GetMusicVolume", &AudioSystem::GetMusicVolume)
		.addFunction("StartRecord", &AudioSystem::StartRecord)
		.addFunction("StopRecord", &AudioSystem::StopRecord)
		.addFunction("IsRecording", &AudioSystem::IsRecording)
		.endClass();

	luabridge::setGlobal(L, this, "__CPPAPI_AudioSystem");
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

	Mix_Chunk* chunk = it->second;
	m_cache_map.erase(it);

	if (chunk == nullptr) return;

	// 如果正在播放就返回，否则就释放音效
	for (unsigned int i = 0; i < AUDIO_MIX_CHANNELS; ++i)
	{
		if (m_channel_list[i].chunk == chunk)
			return;
	}

	Mix_FreeChunk(chunk);
}

int AudioSystem::StartChunk(const char* file_path, int loop)
{
	if (file_path == nullptr)
	{
		ALITTLE_ERROR("file_path is nil");
		return -1;
	}
	if (!InitMixer()) return -1;

	Mix_Chunk* chunk = nullptr;
	
	// 先从缓存里面查找
	MixChunkCache::iterator cache_it = m_cache_map.find(file_path);
	if (cache_it != m_cache_map.end()) chunk = cache_it->second;

	// 如果缓存没有，那么加载音效
	if (chunk == nullptr)
	{
		chunk = LoadChunk(file_path);
		if (chunk == nullptr)
		{
			ALITTLE_ERROR("chunk load failed:" << Mix_GetError());
			return -1;
		}

		// 如果需要缓存，那么就放在缓存中
		if (cache_it != m_cache_map.end())
			cache_it->second = chunk;
	}

	if (loop <= 0)
		loop = -1;
	else
		--loop;

	// 查找空闲的通道
	int index = -1;
	for (unsigned int i = 0; i < AUDIO_MIX_CHANNELS; ++i)
	{
		if (m_channel_list[i].chunk == nullptr)
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		ALITTLE_ERROR("can't find empty channel to play:" << file_path);
		if (cache_it == m_cache_map.end()) Mix_FreeChunk(chunk);
		return -1;
	}
	
	// 播放音效
	int channel = Mix_PlayChannel(index, chunk, loop);
	if (channel < 0)
	{
		ALITTLE_ERROR("chunk play fialed:" << Mix_GetError());
		if (cache_it == m_cache_map.end()) Mix_FreeChunk(chunk);
		return -1;
	}

	// 保存音效相关信息
	m_channel_list[channel].chunk = chunk;
	m_channel_list[channel].file_path = file_path;

	return channel;
}

bool AudioSystem::StopChunk(int channel)
{
	Mix_HaltChannel(channel);
	return true;
}

bool AudioSystem::SetChunkVolume(int channel, float volume)
{
	if (volume < 0.0f) volume = 0.0f;
	else if (volume > 1.0f) volume = 1.0f;
	Mix_Volume(channel, static_cast<int>(volume * MIX_MAX_VOLUME));
	return true;
}

float AudioSystem::GetChunkVolume(int channel)
{
	return Mix_Volume(channel, -1) / static_cast<float>(MIX_MAX_VOLUME);
}

Mix_Chunk* AudioSystem::LoadChunk(const std::string& file_path)
{
	SDL_RWops* src_file = FileHelperEx::OpenFile(file_path, false, "rb");
	if (src_file == nullptr)
	{
		ALITTLE_ERROR("can't find or open failed:" << file_path);
		return nullptr;
	}

	// 如果不是G729格式，那么就直接使用Mixer的函数加载
	std::string ext = FileHelper::GetFileExtByPath(file_path);
	StringHelper::UpperString(ext);
	if (ext != "G729") return Mix_LoadWAV_RW(src_file, SDL_TRUE);

	// 频率转换
	SDL_AudioCVT pcmcvt;
	if (SDL_BuildAudioCVT(&pcmcvt,
		AUDIO_S16, RECORD_CHANNEL_NUM, RECORD_FREQUENCY,
		AUDIO_S16, AUDIO_CHANNEL_NUM, AUDIO_MIX_DEFAULT_FREQUENCY) < 0)
	{
		ALITTLE_ERROR("SDL_BuildAudioCVT failed:" << file_path);
		SDL_RWclose(src_file);
		return 0;
	}


	// 读取文件大小
	int file_size = (int)SDL_RWsize(src_file);
	if (file_size == 0)
	{
		SDL_RWclose(src_file);
		return 0;
	}

	// 申请内存
	unsigned char* file_memory = (unsigned char*)g_MemoryPoolGroup.Create(file_size);
	SDL_RWread(src_file, file_memory, 1, file_size);
	SDL_RWclose(src_file);

	// G729解码
	int sample_count = (int)ceil(file_size / 10.0f) * 80;;
	int new_size = sample_count * sizeof(short);
	short* sample_data = (short*)g_MemoryPoolGroup.Create(new_size);
	G729Decode(file_memory, file_size, sample_data);
	g_MemoryPoolGroup.Release(file_memory);

	// 编码转换
	int sample_size = ((AUDIO_S16 & 0xFF) / 8) * RECORD_CHANNEL_NUM;
	pcmcvt.len = new_size & ~(sample_size - 1);
	pcmcvt.buf = (Uint8 *)SDL_calloc(1, static_cast<size_t>(pcmcvt.len)*pcmcvt.len_mult);
	SDL_memcpy(pcmcvt.buf, sample_data, pcmcvt.len);
	g_MemoryPoolGroup.Release(sample_data);
	if (SDL_ConvertAudio(&pcmcvt) < 0)
	{
		SDL_free(pcmcvt.buf);
		return 0;
	}

	// 转为音效
	Mix_Chunk* chunk = Mix_QuickLoad_RAW(pcmcvt.buf, pcmcvt.len_cvt);
	if (chunk)
	{
		chunk->allocated = 1;
		return chunk;
	}

	// 释放
	SDL_free(pcmcvt.buf);
	return 0;
}

void AudioSystem::G729Decode(unsigned char* buffer, int buffer_len, short* sample_data)
{
	bcg729DecoderChannelContextStruct* decoder = initBcg729DecoderChannel();

	int count = buffer_len / 10;
	for (int i = 0; i < count; ++i)
	{
		bcg729Decoder(decoder, buffer, 0, sample_data);
		buffer += 10;
		sample_data += 80;
	}

	count = buffer_len % 10;
	if (count > 0)
	{
		unsigned char tmp_bffer[10] = { 0 };
		memcpy(tmp_bffer, buffer, count);
		bcg729Decoder(decoder, tmp_bffer, 1, sample_data);
	}

	closeBcg729DecoderChannel(decoder);
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
			Mix_FreeChunk(info.chunk);
		}
		// 如果需要缓存，那么就放进缓存区
		else
		{
			if (it->second == nullptr)
				it->second = info.chunk;
			else if (it->second != info.chunk)
				Mix_FreeChunk(info.chunk);
		}
	}
	// 初始化通道数据
	info.chunk = nullptr;
	info.file_path = "";

	g_ScriptSystem.Invoke("__ALITTLEAPI_AudioChunkStopedEvent", channel);
}

bool AudioSystem::StartMusic(const char* file_path, int loop)
{
	if (!InitMixer()) return false;

	SDL_RWops* play_file = FileHelperEx::OpenFile(file_path, false, "rb");
	if (play_file == nullptr)
	{
		ALITTLE_ERROR("can't find or open failed:" << file_path);
		return false;
	}

	Mix_Music* music = Mix_LoadMUS_RW(play_file, SDL_TRUE);
	if (music == nullptr)
	{
		ALITTLE_ERROR("music create failed:" << Mix_GetError());
		return false;
	}

	if (m_music)
	{
		Mix_FreeMusic(m_music);
		m_music = nullptr;
	}

	if (loop <= 0)
		loop = -1;
	else
		--loop;

	m_music = music;
	Mix_PlayMusic(m_music, loop);

	return true;
}

void AudioSystem::StopMusic()
{
	if (m_music)
	{
		Mix_FreeMusic(m_music);
		m_music = nullptr;
	}
}

bool AudioSystem::SetMusicVolume(float volume)
{
	if (volume < 0.0f) volume = 0.0f;
	else if (volume > 1.0f) volume = 1.0f;
	Mix_VolumeMusic(static_cast<int>(volume * MIX_MAX_VOLUME));
	return true;
}

float AudioSystem::GetMusicVolume()
{
	return Mix_VolumeMusic(-1) / static_cast<float>(MIX_MAX_VOLUME);
}

void AudioSystem::HandleMusicStopedForMixer()
{
}

void AudioSystem::HandleMusicStopedForLua(unsigned int event_type, void * data1, void * data2)
{
}

/* Mixing function */
void AudioSystem::RecordCallback(void *udata, Uint8 *stream, int len)
{
	if (len < 1600) return;

	unsigned char memory[100] = { 0 };

	AudioSystem* self = &g_AudioSystem;
	if (self->m_is_recording && self->m_record_file && self->m_record_encoder)
	{
		unsigned char* memory_tmp = memory;
		Uint8* stream_tmp = stream;
		for (int i = 0; i < 10; ++i)
		{
			bcg729Encoder(self->m_record_encoder, (short*)stream_tmp, memory_tmp);
			memory_tmp += 10;
			stream_tmp += 160;
		}
		SDL_RWwrite(self->m_record_file, memory, 1, 100);
	}
}

bool AudioSystem::StartRecord(const char* file_path)
{
	StopRecord();

	if (file_path == nullptr)
	{
		ALITTLE_ERROR("file_path is nil");
		return false;
	}

	m_record_encoder = initBcg729EncoderChannel();

	m_record_file = FileHelperEx::OpenFile(file_path, false, "wb");
	if (!m_record_file)
	{
		if (m_record_file) { SDL_RWclose(m_record_file); m_record_file = nullptr; }
		if (m_record_encoder) { closeBcg729EncoderChannel(m_record_encoder); m_record_encoder = nullptr; }
		ALITTLE_ERROR(file_path << " open failed with mode:wb");
		return false;
	}

	if (m_record_device == 0)
	{
		/* Set the desired format and frequency */
		SDL_AudioSpec desired;
		memset(&desired, 0, sizeof(desired));
		desired.freq = 8000;
		desired.format = AUDIO_S16;
		desired.channels = 1;
		desired.samples = 800;
		desired.callback = RecordCallback;
		desired.userdata = NULL;

		SDL_AudioSpec obtained;
		memset(&obtained, 0, sizeof(obtained));

		/* Accept nearly any audio format */
		m_record_device = SDL_OpenAudioDevice(NULL, SDL_TRUE, &desired, &obtained, 0);
		if (m_record_device == 0)
		{
			ALITTLE_ERROR("SDL_OpenAudioDevice failed!" << SDL_GetError());
			if (m_record_file) { SDL_RWclose(m_record_file); m_record_file = nullptr; }
			if (m_record_encoder) { closeBcg729EncoderChannel(m_record_encoder); m_record_encoder = nullptr; }
			return false;
		}
		SDL_PauseAudioDevice(m_record_device, 0);
	}

	m_is_recording = true;
	return true;
}

void AudioSystem::StopRecord()
{
	m_is_recording = false;
	if (m_record_device) { SDL_CloseAudioDevice(m_record_device); m_record_device = 0; }
	if (m_record_file) { SDL_RWclose(m_record_file); m_record_file = nullptr; }
	if (m_record_encoder) { closeBcg729EncoderChannel(m_record_encoder); m_record_encoder = nullptr; }
}

} // ALittle
