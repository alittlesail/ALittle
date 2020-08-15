
#ifndef _ALITTLE_LOCALFILE_H_
#define _ALITTLE_LOCALFILE_H_

#include <stdio.h>
#include <time.h>
#include <string>
#include <vector>

#include <SDL.h>

namespace ALittle
{

class LocalFile
{
public:
	LocalFile();
	virtual ~LocalFile();

public:
	/**
	* set file path
	*/
	void SetPath(const char* path);
	/**
	* load from normal dir, if not exist then load from asset dir
	* @return succeed or not
	*/
	bool Load();

	/**
	* load from asset dir
	* @return succeed or not
	*/
	bool LoadBySDL();

	/**
	* Decrypt
	*/
	void Decrypt(const char* key);

	/**
	* Crypt
	*/
	void Encrypt(const char* key);

	/**
	* clear
	*/
	void Clear();

	/**
	* save to
	*/
	void Save(const char* file_path);

private:
	/**
	* clear
	*/
	void ClearMemory();

public:
	const char* GetContent() const;
	const char* GetPath() const;
	int GetSize() const;

public:
	char ReadChar(int offset) const;
	unsigned int ReadUInt(int offset) const;
	int ReadInt(int offset) const;
	float ReadFloat(int offset) const;
	double ReadDouble(int offset) const;

private:
	std::string m_path;		// file path

private:
	char* m_memory;			// content
	int m_size;				// file_size

public:
	/**
	* load from normal dir, if not exist then load from asset dir
	* read as a file
	* @return succeed or not
	*/
	bool Open(bool only_from_asset);
	int Read(char* buffer, int buffer_size, bool auto_close_file);
	void Seek(int offset);

private:
	int m_cur_offset;
	SDL_RWops* m_read_rwops;
};

} // ALittle

#endif // _ALITTLE_LOCALFILE_H_
