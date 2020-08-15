
#ifndef _ALITTLE_TEXTURECUTLOADER_H_
#define _ALITTLE_TEXTURECUTLOADER_H_

#include <SDL.h>
#include <vector>
#include <string>
#include "ALittle/LibClient/ThreadSystem/Task.h"

namespace ALittle
{


class TextureCutLoader : public Task
{
public:
	TextureCutLoader() : m_max_width(0), m_max_height(0) {}
	~TextureCutLoader() { }

public:
	static void HandleEvent(unsigned int event_type, void* data1, void* data2);

public:
	int GetID() const;
	void SetPath(const char* file_path, int max_width, int max_height);
    void Start();
	const char* GetPath() const { return m_file_path.c_str(); }
	int GetMaxWidth() const { return m_max_width; }
	int GetMaxHeight() const { return m_max_height; }
	
public:
	void Execute();
	void Abandon();

private:
	std::string m_file_path;
	int m_max_width;
	int m_max_height;
};
    
} // ALittle

#endif // _ALITTLE_TEXTURECUTLOADER_H_
