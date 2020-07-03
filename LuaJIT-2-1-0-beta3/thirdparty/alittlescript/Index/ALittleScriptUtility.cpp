
#include "ALittleScriptUtility.h"

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

#include "../Generate/ALittleScriptNumberElement.h"
#include "../Generate/ALittleScriptModifierElement.h"
#include "../Generate/ALittleScriptLanguageModifierElement.h"
#include "../Generate/ALittleScriptAttributeModifierElement.h"
#include "../Generate/ALittleScriptPropertyValueElement.h"
#include "../Generate/ALittleScriptNamespaceDecElement.h"
#include "../Generate/ALittleScriptNamespaceNameDecElement.h"
#include "../Generate/ALittleScriptClassCtorDecElement.h"
#include "../Generate/ALittleScriptClassGetterDecElement.h"
#include "../Generate/ALittleScriptClassSetterDecElement.h"
#include "../Generate/ALittleScriptClassMethodDecElement.h"
#include "../Generate/ALittleScriptClassElementDecElement.h"
#include "../Generate/ALittleScriptClassVarDecElement.h"
#include "../Generate/ALittleScriptGlobalMethodDecElement.h"
#include "../Generate/ALittleScriptModifierElement.h"
#include "../Generate/ALittleScriptNamespaceElementDecElement.h"
#include "../Generate/ALittleScriptMethodParamOneDecElement.h"
#include "../Generate/ALittleScriptAllExprElement.h"
#include "../Generate/ALittleScriptClassElementDecElement.h"
#include "../Generate/ALittleScriptCoroutineModifierElement.h"
#include "../Generate/ALittleScriptProtocolModifierElement.h"
#include "../Generate/ALittleScriptCommandModifierElement.h"
#include "../Generate/ALittleScriptCommandBodyDecElement.h"
#include "../Generate/ALittleScriptTextElement.h"
#include "../Generate/ALittleScriptKeyElement.h"
#include "../Generate/ALittleScriptAccessModifierElement.h"
#include "../Generate/ALittleScriptRootElement.h"
#include "../Generate/ALittleScriptClassStaticDecElement.h"

#include "../../alanguage/Index/ABnfFile.h"

void ALittleScriptUtility::CreateFolder(const std::string& path)
{
#ifdef _WIN32
	int result = _mkdir(path.c_str());
#else
	mkdir(path.c_str(), S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP |
		S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH);
#endif
}

void ALittleScriptUtility::CreateDeepFolder(const std::string& path)
{
	if (path.empty()) return;

	std::string sub_path;
	for (size_t i = 0; i < path.size(); ++i)
	{
		if (path[i] == '/' || path[i] == '\\')
			CreateFolder(sub_path);
		sub_path.push_back(path[i]);
	}
	CreateFolder(sub_path);
}

bool ALittleScriptUtility::IsFileExist(const std::string& path)
{
#ifdef _WIN32
#define STAT_STRUCT struct _stati64
#define STAT_FUNC _stati64
#else
#define STAT_STRUCT struct stat
#define STAT_FUNC stat
#endif
    STAT_STRUCT buffer;
    if (STAT_FUNC(path.c_str(), &buffer)) return false;
    return (buffer.st_mode & S_IFREG) != 0;
}

bool ALittleScriptUtility::IsDirExist(const std::string& path)
{
#ifdef _WIN32
#define STAT_STRUCT struct _stati64
#define STAT_FUNC _stati64
#else
#define STAT_STRUCT struct stat
#define STAT_FUNC stat
#endif
    STAT_STRUCT buffer;
    if (STAT_FUNC(path.c_str(), &buffer)) return false;
    return (buffer.st_mode & S_IFDIR) != 0;
}

void ALittleScriptUtility::GetNameListInFolder(const std::string& path, NameType type, std::vector<std::string>& out)
{
#ifdef _WIN32
    //文件句柄
    long   hFile = 0;
    //文件信息
    struct _finddata_t fileinfo;
    std::string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            //如果不是,加入列表
            if ((fileinfo.attrib & _A_SUBDIR))
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                {
                    if (type == NameType::NT_ALL || type == NameType::NT_DIR)
                        out.push_back(fileinfo.name);
                }
            }
            else
            {
                if (type == NameType::NT_ALL || type == NameType::NT_FILE)
                    out.push_back(fileinfo.name);
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
#else
    DIR* dir;
    struct    dirent* ptr;
    dir = opendir(path.c_str()); ///open the dir
    if (dir != NULL)
    {
        while ((ptr = readdir(dir)) != NULL) ///read the list of this dir
        {
            if (ptr->d_type == DT_DIR)
            {
                if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
                {
                    if (type == NameType::NT_ALL || type == NameType::NT_DIR)
                        out.push_back(ptr->d_name);
                }
            }
            else
            {
                if (type == NameType::NT_ALL || type == NameType::NT_FILE)
                    out.push_back(ptr->d_name);
            }
        }
        closedir(dir);
    }
#endif
}

// 判断字符串是不是整型值
bool ALittleScriptUtility::IsInt(const std::shared_ptr<ALittleScriptNumberElement>& element)
{
	if (element == nullptr) return false;
	const auto& text = element->GetElementText();
	if (text.find("0x") == 0) return true;
	return text.find('.') == std::string::npos;
}

// 计算哈希值
inline int ALittleScriptUtility::JSHash(const std::string& content)
{
	int l = static_cast<int>(content.size());
	int h = l;
	int step = (l >> 5) + 1;

	for (int i = l; i >= step; i -= step)
	{
		h = h ^ ((h << 5) + static_cast<unsigned char>(content[i - 1]) + (h >> 2));
	}
	return h;
}

// 计算结构体的哈希值
int ALittleScriptUtility::StructHash(const std::shared_ptr<ALittleScriptGuessStruct>& guess)
{
	if (guess == nullptr) return 0;
	return JSHash(guess->namespace_name + "." + guess->struct_name) + JSHash(guess->namespace_name) + JSHash(guess->struct_name);
}

bool ALittleScriptUtility::IsLanguageEnable(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list)
{
	for (auto& element : element_list)
	{
		if (element->GetAttributeModifier() != nullptr)
		{
			auto language = element->GetAttributeModifier()->GetLanguageModifier();
			if (language != nullptr)
			{
				auto* modifier = dynamic_cast<ALittleScriptLanguageModifierReference*>(language->GetReference());
				if (modifier == nullptr) return false;

				return modifier->IsLanguageEnable();
			}
		}
	}

	return true;
}

// 是否使用原生
bool ALittleScriptUtility::IsNative(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list)
{
	for (auto& element : element_list)
	{
		if (element->GetAttributeModifier() != nullptr)
		{
			return element->GetAttributeModifier()->GetNativeModifier() != nullptr;
		}
	}

	return false;
}

// 检查await
bool ALittleScriptUtility::CheckInvokeAwaitError(std::shared_ptr<ABnfElement> element, ABnfGuessError& error)
{
    // 检查这次所在的函数必须要有await或者async修饰
	std::shared_ptr<ABnfElement> parent = element;
    while (parent != nullptr)
    {
        if (std::dynamic_pointer_cast<ALittleScriptPropertyValueElement>(parent))
        {
            element = parent;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptNamespaceDecElement>(parent))
        {
			error.element = element;
			error.error = u8"全局表达式不能调用带有await的函数";
			return true;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassCtorDecElement>(parent))
        {
			error.element = element;
			error.error = u8"构造函数内不能调用带有await的函数";
			return true;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(parent))
        {
			error.element = element;
			error.error = u8"getter函数内不能调用带有await的函数";
			return true;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(parent))
        {
			error.element = element;
			error.error = u8"setter函数内不能调用带有await的函数";
			return true;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent))
        {
            auto modifier = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(parent->GetParent())->GetModifierList();
            std::string type;
			if (!GetCoroutineType(modifier, type))
			{
				error.element = element;
				error.error = u8"所在函数没有async或await修饰";
				return true;
			}
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent))
        {
            auto modifier = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(parent->GetParent())->GetModifierList();
            std::string type;
            if (!GetCoroutineType(modifier, type))
            {
				error.element = element;
				error.error = u8"所在函数没有async或await修饰";
				return true;
			}
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent))
        {
            auto modifier = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(parent->GetParent())->GetModifierList();
            std::string type;
            if (!GetCoroutineType(modifier, type))
            {
				error.element = element;
				error.error = u8"所在函数没有async或await修饰";
				return true;
			}
            break;
        }
        parent = parent->GetParent();
    }

    return false;
}

// 判断是否存在
bool ALittleScriptUtility::CheckError(std::shared_ptr<ABnfElement> parent, const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list, ABnfGuessError& error)
{
    int register_count = 0;
    int coroutine_count = 0;
    int access_count = 0;

    int language_count = 0;
    int const_count = 0;
    int nullable_count = 0;
    int proto_cmd_count = 0;
    int native_count = 0;

    for (auto& element : element_list)
    {
        if (element->GetRegisterModifier() != nullptr)
        {
            ++register_count;

            if (register_count > 1)
            {
                error.element = element->GetRegisterModifier();
                error.error = u8"register修饰符只能定义一个";
                return true;
            }

            // register只能修饰namespace
            if (!std::dynamic_pointer_cast<ALittleScriptNamespaceDecElement>(parent))
            {
                error.element = element->GetRegisterModifier();
                error.error = u8"register只能修饰namespace";
                return true;
            }
        }
        else if (element->GetCoroutineModifier() != nullptr)
        {
            ++coroutine_count;

            if (coroutine_count > 1)
            {
                error.element = element->GetCoroutineModifier();
                error.error = u8"协程修饰符只能定义一个";
                return true;
            }   

            bool has_error = true;

            if (std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(parent))
            {
                auto namespace_element_dec = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(parent);
                has_error = namespace_element_dec->GetGlobalMethodDec() == nullptr;
            }
            else if (std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(parent))
            {
                auto class_element_dec = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(parent);
                has_error = class_element_dec->GetClassMethodDec() == nullptr
                    && class_element_dec->GetClassStaticDec() == nullptr;
            }

            if (has_error)
            {
                error.element = element->GetCoroutineModifier();
                error.error = u8"协程修饰符修饰全局函数，类成员函数，类静态函数";
                return true;
            }   
        }
        else if (element->GetAccessModifier() != nullptr)
        {
            ++access_count;

            if (access_count > 1)
            {
                error.element = element->GetAccessModifier();
                error.error = u8"访问修饰符只能定义一个";
                return true;
            }
            
            if (std::dynamic_pointer_cast<ALittleScriptMethodParamOneDecElement>(parent))
            {
                error.element = element->GetAccessModifier();
                error.error = u8"访问修饰符不能修饰函数形参";
                return true;
            }
                
            if (std::dynamic_pointer_cast<ALittleScriptNamespaceDecElement>(parent))
            {
                error.element = element->GetAccessModifier();
                error.error = u8"访问修饰符不能修饰namespace";
                return true;
            }
                
            if (std::dynamic_pointer_cast<ALittleScriptAllExprElement>(parent))
            {
                error.element = element->GetAccessModifier();
                error.error = u8"访问修饰符不能修饰表达式列表";
                return true;
            }   
        }
        else if (element->GetAttributeModifier() != nullptr)
        {
            auto attribute = element->GetAttributeModifier();
            if (attribute->GetLanguageModifier() != nullptr)
            {
                ++language_count;
                if (language_count > 1)
                {
                    error.element = attribute->GetLanguageModifier();
                    error.error = u8"Language修饰符最多只能有一个";
                    return true;
                }   

                if (std::dynamic_pointer_cast<ALittleScriptMethodParamOneDecElement>(parent))
                {
                    error.element = attribute;
                    error.error = u8"Language修饰符不能修饰函数形参";
                    return true;
                }   
            }
            else if (attribute->GetConstModifier() != nullptr)
            {
                ++const_count;
                if (const_count > 1)
                {
                    error.element = attribute->GetConstModifier();
                    error.error = u8"Const修饰符最多只能有一个";
                    return true;
                }
                bool has_error = true;
                if (std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(parent))
                {
                    auto class_element_dec = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(parent);
                    has_error = class_element_dec->GetClassGetterDec() == nullptr
                        && class_element_dec->GetClassSetterDec() == nullptr
                        && class_element_dec->GetClassMethodDec() == nullptr;
                }

                if (has_error)
                {
                    error.element = attribute;
                    error.error = u8"Const修饰符修饰类getter函数，类setter函数，类成员函数";
                    return true;
                }   
            }
            else if (attribute->GetNullableModifier() != nullptr)
            {
                ++nullable_count;
                if (nullable_count > 1)
                {
                    error.element = attribute->GetNullableModifier();
                    error.error = u8"Nullable修饰符最多只能有一个";
                    return true;
                }   

                if (!std::dynamic_pointer_cast<ALittleScriptMethodParamOneDecElement>(parent))
                {
                    error.element = attribute->GetNullableModifier();
                    error.error = u8"Nullable只能修饰函数形参";
                    return true;
                }   
            }
            else if (attribute->GetProtocolModifier() != nullptr)
            {
                ++proto_cmd_count;
                if (proto_cmd_count > 1)
                {
                    error.element = attribute->GetProtocolModifier();
                    error.error = u8"协议修饰符和命令修饰符最多只能有一个";
                    return true;
                }
                
                bool has_error = true;
                if (std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(parent))
                {
                    auto namespace_element_dec = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(parent);
                    has_error = namespace_element_dec->GetGlobalMethodDec() == nullptr;
                }

                if (has_error)
                {
                    error.element = attribute;
                    error.error = u8"协议修饰符只能修饰全局函数";
                    return true;
                }   
            }
            else if (attribute->GetCommandModifier() != nullptr)
            {
                ++proto_cmd_count;
                if (proto_cmd_count > 1)
                {
                    error.element = attribute->GetCommandModifier();
                    error.error = "协议修饰符和命令修饰符最多只能有一个";
                    return true;
                }   

                bool has_error = true;
                if (std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(parent))
                {
                    auto namespace_element_dec = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(parent);
                    has_error = namespace_element_dec->GetGlobalMethodDec() == nullptr;
                }

                if (has_error)
                {
                    error.element = attribute;
                    error.error = u8"命令修饰符只能修饰全局函数";
                    return true;
                }   
            }
            else if (attribute->GetNativeModifier() != nullptr)
            {
                ++native_count;
                if (native_count > 1)
                {
                    error.element = attribute->GetCommandModifier();
                    error.error = u8"原生修饰符和命令修饰符最多只能有一个";
                    return true;
                }

                bool has_error = true;
                if (std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(parent))
                {
                    auto class_element_dec = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(parent);
                    if (class_element_dec->GetClassVarDec() != nullptr)
                    {
                        auto guess = class_element_dec->GetClassVarDec()->GuessType(error);
                        if (guess == nullptr) return true;

                        if (std::dynamic_pointer_cast<ALittleScriptGuessList>(guess))
                            has_error = false;
                    }
                }
                else if (std::dynamic_pointer_cast<ALittleScriptAllExprElement>(parent))
                {
                    auto all_expr = std::dynamic_pointer_cast<ALittleScriptAllExprElement>(parent);
                    if (all_expr->GetForExpr() != nullptr)
                        has_error = false;
                }
                else if (std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(parent))
                {
                    auto namespace_element_dec = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(parent);
                    has_error = namespace_element_dec->GetClassDec() == nullptr;
                }

                if (has_error)
                {
                    error.element = attribute;
                    error.error = u8"Native修饰符只能修饰class、类成员List的变量、for表达式";
                    return true;
                }   
            }
        }
    }

    return false;
}

// 获取是否是register
bool ALittleScriptUtility::IsRegister(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list)
{
    for (auto& element : element_list)
    {
        if (element->GetRegisterModifier() != nullptr)
            return true;
    }
    return false;
}

// 获取是否是Const
bool ALittleScriptUtility::IsConst(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list)
{
    for (auto& element : element_list)
    {
        if (element->GetAttributeModifier() != nullptr
            && element->GetAttributeModifier()->GetConstModifier() != nullptr)
            return true;
    }
    return false;
}

// 获取是否是Nullable
bool ALittleScriptUtility::IsNullable(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list)
{
    for (auto& element : element_list)
    {
        if (element->GetAttributeModifier() != nullptr
            && element->GetAttributeModifier()->GetNullableModifier() != nullptr)
            return true;
    }
    return false;
}

// 获取协程类型
bool ALittleScriptUtility::GetCoroutineType(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list, std::string& out)
{
    for (auto& element : element_list)
    {
        if (element->GetCoroutineModifier() != nullptr)
        {
            out = element->GetCoroutineModifier()->GetElementText();
            return true;
        }
    }
    return false;
}

// 获取协议类型
bool ALittleScriptUtility::GetProtocolType(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list, std::string& out)
{
    for (auto& element : element_list)
    {
        if (element->GetAttributeModifier() != nullptr
            && element->GetAttributeModifier()->GetProtocolModifier() != nullptr)
        {
            out = element->GetAttributeModifier()->GetProtocolModifier()->GetElementText();
            return true;
        }

    }
    return false;
}

// 获取命令类型
bool ALittleScriptUtility::GetCommandDetail(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list, std::string& cmd, std::string& desc)
{
    for (auto& element : element_list)
    {
        if (element->GetAttributeModifier() != nullptr
            && element->GetAttributeModifier()->GetCommandModifier() != nullptr)
        {
            auto body_dec = element->GetAttributeModifier()->GetCommandModifier()->GetCommandBodyDec();
            if (body_dec != nullptr && body_dec->GetText() != nullptr)
                desc = body_dec->GetText()->GetElementString();
            cmd = element->GetAttributeModifier()->GetCommandModifier()->GetKey()->GetElementText();
            return true;
        }
    }
    return false;
}

// 获取访问权限类型
ClassAccessType ALittleScriptUtility::CalcAccessType(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list)
{
    for (auto& element : element_list)
    {
        if (element->GetAccessModifier() != nullptr)
        {
            const auto& text = element->GetAccessModifier()->GetElementText();
            if (text == "public")
                return ClassAccessType::PUBLIC;
            else if (text == "protected")
                return ClassAccessType::PROTECTED;

            return ClassAccessType::PRIVATE;
        }
    }

    return ClassAccessType::PRIVATE;
}

// 获取某个元素的命名域对象
std::shared_ptr<ALittleScriptNamespaceDecElement> ALittleScriptUtility::GetNamespaceDec(ABnfFile* file)
{
    if (file == nullptr) return nullptr;
    auto root = std::dynamic_pointer_cast<ALittleScriptRootElement>(file->GetRoot());
    if (root == nullptr) return nullptr;

    return root->GetNamespaceDec();
}

// 获取某个元素的命名域名对象
std::shared_ptr<ALittleScriptNamespaceNameDecElement> ALittleScriptUtility::GetNamespaceNameDec(ABnfFile* file)
{
    auto namesapce_dec = GetNamespaceDec(file);
    if (namesapce_dec == nullptr) return nullptr;

    return namesapce_dec->GetNamespaceNameDec();
}

// 判断某个是不是register
bool ALittleScriptUtility::IsRegister(std::shared_ptr<ABnfElement> element)
{
    auto namespace_dec = GetNamespaceDec(element->GetFile());
    if (namespace_dec == nullptr) return false;

    return IsRegister(namespace_dec->GetModifierList());
}

// 获取某个元素的命名域名
const std::string& ALittleScriptUtility::GetNamespaceName(std::shared_ptr<ABnfElement> element)
{
    static std::string empty;
    if (element == nullptr) return empty;
    auto namespace_name_dec = GetNamespaceNameDec(element->GetFile());
    if (namespace_name_dec == nullptr) return empty;
    return namespace_name_dec->GetElementText();
}

// 获取命名域名
const std::string& ALittleScriptUtility::GetNamespaceName(ABnfFile* file)
{
    static std::string empty;
    auto namespace_name_dec = GetNamespaceNameDec(file);
    if (namespace_name_dec == nullptr) return empty;
    return namespace_name_dec->GetElementText();
}

// 获取这个元素所在的类
std::shared_ptr<ALittleScriptClassDecElement> ALittleScriptUtility::FindClassDecFromParent(std::shared_ptr<ABnfElement> dec)
{
    while (dec != nullptr)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptClassDecElement>(dec);
        if (node) return node;
        dec = dec->GetParent();
    }
    return nullptr;
}

// 获取这个元素所在的函数模板
std::shared_ptr<ALittleScriptTemplateDecElement> ALittleScriptUtility::FindMethodTemplateDecFromParent(std::shared_ptr<ABnfElement> dec)
{
    while (dec != nullptr)
    {
        if (std::dynamic_pointer_cast<ALittleScriptRootElement>(dec))
            return nullptr;
        else if (std::dynamic_pointer_cast<ALittleScriptClassDecElement>(dec))
            return nullptr;
        else if (std::dynamic_pointer_cast<ALittleScriptClassCtorDecElement>(dec))
            return nullptr;
        else if (std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(dec))
            return nullptr;
        else if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(dec))
            return std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(dec)->GetTemplateDec();
        else if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(dec))
            return std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(dec)->GetTemplateDec();
        else if (std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(dec))
            return std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(dec)->GetTemplateDec();

        dec = dec->GetParent();
    }
    return nullptr;
}

// 检查是否在静态函数中
bool ALittleScriptUtility::IsInClassStaticMethod(std::shared_ptr<ABnfElement> dec)
{
    std::shared_ptr<ABnfElement> parent = dec;
    while (true)
    {
        if (parent == nullptr) break;

        if (std::dynamic_pointer_cast<ALittleScriptRootElement>(parent))
            return false;
        else if (std::dynamic_pointer_cast<ALittleScriptClassDecElement>(parent))
            return false;
        else if (std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(parent))
            return false;
        else if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent))
            return false;
        else if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent))
            return true;
        else if (std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent))
            return false;

        parent = parent->GetParent();
    }

    return false;
}
