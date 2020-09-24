
#include "FileHelperEx.h"

#include "Carp/carp_log.hpp"
#include "Carp/carp_crypto.hpp"

#include <SDL.h>

#include <time.h>
#include <vector>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#include <io.h>
#include <sys/locking.h>
#ifdef __BORLANDC__
#include <utime.h>
#else
#include <sys/utime.h>
#endif
#include <fcntl.h>
#else
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <utime.h>
#endif

namespace ALittle
{

std::string FileHelperEx::BaseFilePath()
{
	std::string base_path;
#ifdef __ANDROID__
	base_path.append(SDL_AndroidGetInternalStoragePath()).append("/");
	return base_path;
#elif __IPHONEOS__
	base_path.append(iOS_GetResourcePath()).append("/");
	return base_path;
#elif _WIN32
	return base_path;
#else
	return base_path;
#endif
}

std::string FileHelperEx::ExternalFilePath()
{
#ifdef __ANDROID__
	std::string external_path;
	external_path.append(SDL_AndroidGetExternalStoragePath()).append("/");
	return external_path;
#elif __IPHONEOS__
	return BaseFilePath();
#elif _WIN32
	return BaseFilePath();
#else
	return BaseFilePath();
#endif
}

SDL_RWops* FileHelperEx::OpenFile(const std::string& path, bool only_from_asset, const char* mode)
{
	// only from asset
	if (only_from_asset)
		return SDL_RWFromFileByPlatform(path.c_str(), mode);

	// try outer path
	std::string file_path = path;
	if (path.size() && path.at(0) != '/')
		file_path = std::string() + FileHelperEx::BaseFilePath() + path;
	SDL_RWops* file = SDL_RWFromFile(file_path.c_str(), mode);

	// try asset path
	if (file == 0 && file_path != path)
		file = SDL_RWFromFileByPlatform(path.c_str(), mode);

	return file;
}

bool FileHelperEx::CpFile(const char* src_path, const char* dest_path, bool only_from_asset)
{
	if (src_path == 0 || dest_path == 0) return false;

	// open src file
	SDL_RWops* src_file = OpenFile(src_path, only_from_asset, "rb");
	if (src_file == 0) return false;

	// open dest file
	SDL_RWops* dest_file = OpenFile(dest_path, false, "wb");
	if (dest_file == 0)
	{
		SDL_RWclose(src_file);
		return false;
	}

	// define buffer, read and write
	char buff[1024];
	size_t read_size = 0;
	do
	{
		read_size = SDL_RWread(src_file, buff, 1, sizeof(buff));
		if (read_size == 0) break;
		SDL_RWwrite(dest_file, buff, 1, read_size);
	} while (true);

	// close all file
	SDL_RWclose(src_file);
	SDL_RWclose(dest_file);

	return true;
}

bool FileHelperEx::LoadFile(const std::string& path, bool only_from_asset, std::vector<char>& memory)
{
	// open src file
	SDL_RWops* file = OpenFile(path, only_from_asset, "rb");
	if (file == 0) return false;

	// get file size
	int size = (unsigned int)SDL_RWsize(file);
	memory.resize(size, 0);

	// read from memory
	if (size > 0) SDL_RWread(file, &(memory[0]), size, 1);
	// close file
	SDL_RWclose(file);

	return true;
}

bool FileHelperEx::SaveFile(const char* target_path, const char* content, int size)
{
	if (content == 0) return false;

	SDL_RWops* file = OpenFile(target_path, false, "wb");
	if (file == 0) return false;

	if (size <= 0) size = static_cast<int>(strlen(content));
	if (size > 0) SDL_RWwrite(file, content, 1, size);
	SDL_RWclose(file);

	return true;
}

std::string FileHelperEx::FileMD5(const std::string& file_path)
{
	SDL_RWops* file = FileHelperEx::OpenFile(file_path, false, "rb");
	if (file == 0)
	{
		CARP_ERROR("file_path is open failed!" << file_path);
		return "";
	}

	CarpCrypto::MD5_HASH Digest;
	CarpCrypto::Md5Context context;

	CarpCrypto::Md5Initialise(&context);

	unsigned char buffer[1024];
	while (true)
	{
		size_t read_size = SDL_RWread(file, buffer, 1, sizeof(buffer));
		if (read_size == 0) break;
		CarpCrypto::Md5Update(&context, buffer, (int)read_size);
	}
	SDL_RWclose(file);

	CarpCrypto::Md5Finalise(&context, &Digest);
	return CarpCrypto::Md4HashToString(&Digest);
}

} // ALittle
