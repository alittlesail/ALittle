
#ifndef _ALITTLE_FILEHELPEREX_H_
#define _ALITTLE_FILEHELPEREX_H_

#include <string>
#include <vector>
#include <set>

struct SDL_RWops;

namespace ALittle
{

class FileHelperEx
{
public:
	// 获取基本路径
	static std::string BaseFilePath();

	// 获取外部路径
	static std::string ExternalFilePath();

	// 计算文件的md5
	static std::string FileMD5(const std::string& file_path);

	// 打开文件
	static SDL_RWops* OpenFile(const std::string& path, bool only_from_asset, const char* mode);

	// 复制文件
	static bool CpFile(const char* src_path, const char* dest_path, bool only_from_asset);

	// 加载文件
	static bool LoadFile(const std::string& path, bool only_from_asset, std::vector<char>& memory);

	// 保存到文件
	static bool SaveFile(const char* target_path, const char* content, int size);
};

} // ALittle

#endif // _ALITTLE_FILEHELPEREX_H_
