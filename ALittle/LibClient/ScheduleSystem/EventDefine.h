
#ifndef _ALITTLE_EVENTDEFINE_H_
#define _ALITTLE_EVENTDEFINE_H_

namespace ALittle
{

#define UNKNOW_EVENT				0   // unknow event

#define EMPTY_EVENT					1	// empty event for wake up schedule system

// don't change this value below //////////////////////////////////////
#define HTTP_DOWNLOADING_EVENT		11	// http downloading 
#define HTTP_DOWNLOAD_SUCCEED_EVENT	12	// http download succeed
#define HTTP_DOWNLOAD_FAILED_EVENT	13	// http download failed
#define HTTP_UPLOADING_EVENT		14	// http uploading
#define HTTP_UPLOAD_SUCCEED_EVENT	15	// http upload succeed
#define HTTP_UPLOAD_FAILED_EVENT	16	// http upload failed

// ///////////////////////////////////////////////////////////////////

#define NET_MESSAGE					31	// net message for NetSystem
#define NET_DISCONNECT				32	// NetSystem disconnected
#define NET_CONNECT_SUCCEED			33	// NetSystem connect succeed
#define NET_CONNECT_FAILED			34	// NetSystem connect failed
#define NET_HTTP_SUCCEED			35	// HTTP Request GET or POST succeed
#define NET_HTTP_FAILED				36	// HTTP Request GET or POST failed

#define NET_UMESSAGE				41	// net udp message for UNetSystem

#define EXTERNAL_INVOKE_LUA			50  // 外部调用lua接口
#define CONSOLE_INVOKE_LUA			51  // 控制台调用lua接口

#define TEXTURE_LOAD_SUCCEED		81	// texture load succeed
#define TEXTURE_LOAD_FAILED			82	// texture load failed

#define TEXTURECUT_LOAD_SUCCEED		83	// texture cut load succeed
#define TEXTURECUT_LOAD_FAILED		84	// texture cut load failed

#define CSV_LOAD_SUCCEED		    85	// texture load succeed
#define CSV_LOAD_FAILED			    86	// texture load failed

#define CHUNK_STOPED				101 // SDL_Mixer Mix_Chunk stoped
#define MUSIC_STOPED				102 // SDL_Mixer Mix_Music stoped

} // ALittle

#endif // _ALITTLE_EVENTDEFINE_H_
