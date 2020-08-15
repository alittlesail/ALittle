
#ifndef _ALITTLE_FILEHELPER_H_
#define _ALITTLE_FILEHELPER_H_

#include <string>
#include <vector>

struct SDL_RWops;

namespace ALittle
{

class FileHelper
{
public:
    // 创建文件夹
	static void CreateFolder(const std::string& path);
	// 删除文件夹
	static void DeleteFolder(const std::string& path);

    // 递归创建文件夹
	static void CreateDeepFolder(const std::string& path);

    // 判断文件是否存在
	static bool IsFileExist(const std::string& path);

	// 判断文件夹是否存在
	static bool IsDirExist(const std::string& path);

	// 获取文件夹下的所有文件
	static void GetNameListInFolder(const std::string& path, std::vector<std::string>& file_list, std::vector<std::string>& dir_list);

    // 从路径中获取文件扩展名
	static std::string GetFileExtByPath(const std::string& file_path);
	// 改变扩展名
	static std::string ChangeFileExtByPath(const std::string& file_path, const std::string& ext);

	// 从路径中获取文件名
	static std::string GetFileNameByPath(const std::string& file_path);

	// 从路径中获取文件名
	static std::string GetFilePathByPath(const std::string& file_path);

    // 从路径中获取文件名(不带后缀)
    static std::string GetJustFileNameByPath(const std::string& file_path);

	// 为文件结尾添加路径分隔符
	static std::string TryAddFileSeparator(const std::string& file_path);

	// 加载文件
	static bool LoadStdFile(const std::string& file_path, std::vector<char>& out);
	// 写入文件
	static bool WriteToStdFile(const std::string& file_path, const std::vector<char>& out);
};

} // ALittle

#endif // _ALITTLE_FILEHELPER_H_
