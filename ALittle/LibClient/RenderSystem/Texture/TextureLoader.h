
#ifndef _ALITTLE_TEXTURELOADER_H_
#define _ALITTLE_TEXTURELOADER_H_

#include <SDL.h>
#include <vector>
#include <string>
#include "Carp/carp_task_consumer.hpp"

namespace ALittle
{

class TextureLoader : public CarpTask
{
public:
	TextureLoader() : m_crypt_mode(0), m_width(0), m_height(0) {}
	~TextureLoader() {}

public:
	static void HandleEvent(unsigned int event_type, void* data1, void* data2);

public:
    void Start();
	int GetID() const;
	void SetPath(const char* file_path, const char* atlas_info, int width, int height, bool crypt_mode);
	const char* GetPath() const { return m_file_path.c_str(); }
	
public:
	void Execute() override;
	void Abandon() override;

private:
	std::string m_file_path;
	std::string m_atlas_info;
	bool m_crypt_mode;
	int m_width, m_height;
};

} // ALittle

#endif // _ALITTLE_TEXTURELOADER_H_
