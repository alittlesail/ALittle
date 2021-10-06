
#include "ALittleScriptUtility.h"
#include "ALittleScriptIndex.h"
#include "ALittleScriptAccessData.h"
#include "ALittleScriptClassData.h"
#include "ALittleScriptStructData.h"
#include "ALittleScriptEnumData.h"

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
#include "../Generate/ALittleScriptStructDecElement.h"
#include "../Generate/ALittleScriptStructNameDecElement.h"
#include "../Generate/ALittleScriptStructVarDecElement.h"
#include "../Generate/ALittleScriptEnumDecElement.h"
#include "../Generate/ALittleScriptEnumVarDecElement.h"
#include "../Generate/ALittleScriptStructExtendsDecElement.h"
#include "../Generate/ALittleScriptClassDecElement.h"
#include "../Generate/ALittleScriptClassExtendsDecElement.h"
#include "../Generate/ALittleScriptClassNameDecElement.h"
#include "../Generate/ALittleScriptClassBodyDecElement.h"
#include "../Generate/ALittleScriptClassCtorDecElement.h"
#include "../Generate/ALittleScriptMethodParamDecElement.h"
#include "../Generate/ALittleScriptMethodSetterParamDecElement.h"
#include "../Generate/ALittleScriptMethodParamNameDecElement.h"
#include "../Generate/ALittleScriptForStartStatElement.h"
#include "../Generate/ALittleScriptForStepConditionElement.h"
#include "../Generate/ALittleScriptForConditionElement.h"
#include "../Generate/ALittleScriptForExprElement.h"
#include "../Generate/ALittleScriptForStartStatElement.h"
#include "../Generate/ALittleScriptForPairDecElement.h"
#include "../Generate/ALittleScriptVarAssignNameDecElement.h"
#include "../Generate/ALittleScriptForConditionElement.h"
#include "../Generate/ALittleScriptForInConditionElement.h"
#include "../Generate/ALittleScriptMethodBodyDecElement.h"
#include "../Generate/ALittleScriptForExprElement.h"
#include "../Generate/ALittleScriptForBodyElement.h"
#include "../Generate/ALittleScriptIfExprElement.h"
#include "../Generate/ALittleScriptIfBodyElement.h"
#include "../Generate/ALittleScriptElseIfExprElement.h"
#include "../Generate/ALittleScriptElseIfBodyElement.h"
#include "../Generate/ALittleScriptElseExprElement.h"
#include "../Generate/ALittleScriptElseBodyElement.h"
#include "../Generate/ALittleScriptWhileExprElement.h"
#include "../Generate/ALittleScriptWhileBodyElement.h"
#include "../Generate/ALittleScriptDoWhileBodyElement.h"
#include "../Generate/ALittleScriptDoWhileExprElement.h"
#include "../Generate/ALittleScriptWrapExprElement.h"
#include "../Generate/ALittleScriptVarAssignExprElement.h"
#include "../Generate/ALittleScriptVarAssignDecElement.h"
#include "../Generate/ALittleScriptValueStatElement.h"
#include "../Generate/ALittleScriptRegisterModifierElement.h"
#include "../Generate/ALittleScriptConstModifierElement.h"
#include "../Generate/ALittleScriptNullableModifierElement.h"

#include "alanguage/Src/Index/ABnfFile.h"
#include "alanguage/Src/Index/ABnfProject.h"
#include "alanguage/Src/Model/ABnfGuess.h"

#include "../Guess/ALittleScriptGuessStruct.h"
#include "../Guess/ALittleScriptGuessList.h"
#include "../Guess/ALittleScriptGuessMap.h"
#include "../Guess/ALittleScriptGuessFunctor.h"
#include "../Guess/ALittleScriptGuessPrimitive.h"
#include "../Guess/ALittleScriptGuessClass.h"
#include "../Guess/ALittleScriptGuessReturnTail.h"

#include "../Reference/ALittleScriptLanguageModifierReference.h"

void ALittleScriptUtility::TrimLeft(std::string& target)
{
	const std::string::size_type pos = target.find_first_not_of(' ');
    if (pos == std::string::npos) return;
    if (pos == 0) return;

    target = target.substr(pos);
}

void ALittleScriptUtility::TrimRight(std::string& target)
{
	const std::string::size_type pos = target.find_last_not_of(' ');
    if (pos == std::string::npos) return;
    if (pos + 1 == target.size()) return;

    target = target.substr(0, pos + 1);
}

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

std::string ALittleScriptUtility::ChangeFileExtByPath(const std::string& file_path, const std::string& ext)
{
    std::string::size_type pos = file_path.find_last_of('.');
    if (pos == std::string::npos)
    {
        if (ext.empty()) return file_path;
        return file_path + "." + ext;
    }

    if (ext.empty()) return file_path.substr(0, pos);
    return file_path.substr(0, pos) + "." + ext;
}

std::string ALittleScriptUtility::GetFilePathByPath(const std::string& file_path)
{
    size_t index = 0;
    for (size_t i = file_path.size(); i > 0; --i)
    {
        if (file_path[i - 1] == '/' || file_path[i - 1] == '\\')
        {
            index = i - 1;
            break;
        }
    }
    return file_path.substr(0, index);
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

void ALittleScriptUtility::GetNameListInFolder(const std::string& path, std::vector<std::string>& file_list, std::vector<std::string>& dir_list)
{
#ifdef _WIN32
    //�ļ����
    std::intptr_t   hFile = 0;
    //�ļ���Ϣ
    struct _finddata_t file_info{};
    std::string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &file_info)) != -1)
    {
        do
        {
            //�������,�����б�
            if ((file_info.attrib & _A_SUBDIR))
            {
                if (strcmp(file_info.name, ".") != 0 && strcmp(file_info.name, "..") != 0)
                    dir_list.emplace_back(file_info.name);
            }
            else
            {
                file_list.emplace_back(file_info.name);
            }
        } while (_findnext(hFile, &file_info) == 0);
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
                    dir_list.push_back(ptr->d_name);
            }
            else
            {
                file_list.push_back(ptr->d_name);
            }
        }
        closedir(dir);
    }
#endif
}

// �ж��ַ����ǲ�������ֵ
bool ALittleScriptUtility::IsInt(const std::shared_ptr<ALittleScriptNumberElement>& element)
{
	if (element == nullptr) return false;
	const auto& text = element->GetElementText();
	if (text.find("0x") == 0) return true;
	return text.find('.') == std::string::npos;
}

// �����ϣֵ
inline int ALittleScriptUtility::JSHash(const std::string& content)
{
	const int l = static_cast<int>(content.size());
	int h = l;
	const int step = (l >> 5) + 1;

	for (int i = l; i >= step; i -= step)
	{
		h = h ^ ((h << 5) + static_cast<unsigned char>(content[i - 1]) + (h >> 2));
	}
	return h;
}

// ����ṹ��Ĺ�ϣֵ
int ALittleScriptUtility::StructHash(const std::shared_ptr<ALittleScriptGuessStruct>& guess)
{
	if (guess == nullptr) return 0;
	return JSHash(guess->namespace_name + "." + guess->struct_name) + JSHash(guess->namespace_name) + JSHash(guess->struct_name);
}

bool ALittleScriptUtility::IsLanguageEnable(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list)
{
	for (const auto& element : element_list)
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

// �Ƿ�ʹ��ԭ��
bool ALittleScriptUtility::IsNative(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list)
{
	for (const auto& element : element_list)
	{
		if (element->GetAttributeModifier() != nullptr)
		{
			return element->GetAttributeModifier()->GetNativeModifier() != nullptr;
		}
	}
	return false;
}

// ���await
ABnfGuessError ALittleScriptUtility::CheckInvokeAwait(std::shared_ptr<ABnfElement> element)
{
    // ���������ڵĺ�������Ҫ��await����async����
	std::shared_ptr<ABnfElement> parent = element;
    while (parent != nullptr)
    {
        if (std::dynamic_pointer_cast<ALittleScriptPropertyValueElement>(parent))
        {
            element = parent;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptNamespaceDecElement>(parent))
        {
            return ABnfGuessError(element, u8"ȫ�ֱ��ʽ���ܵ��ô���await�ĺ���");
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassCtorDecElement>(parent))
        {
            return ABnfGuessError(element, u8"���캯���ڲ��ܵ��ô���await�ĺ���");
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(parent))
        {
            return ABnfGuessError(element, u8"getter�����ڲ��ܵ��ô���await�ĺ���");
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(parent))
        {
            return ABnfGuessError(element, u8"setter�����ڲ��ܵ��ô���await�ĺ���");
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent))
        {
            const auto& modifier = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(parent->GetParent())->GetModifierList();
			if (GetCoroutineType(modifier).empty())
                return ABnfGuessError(element, u8"���ں���û��async��await����");
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent))
        {
            const auto& modifier = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(parent->GetParent())->GetModifierList();
            if (GetCoroutineType(modifier).empty())
                return ABnfGuessError(element, u8"���ں���û��async��await����");
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent))
        {
            const auto& modifier = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(parent->GetParent())->GetModifierList();
            if (GetCoroutineType(modifier).empty())
                return ABnfGuessError(element, u8"���ں���û��async��await����");
            break;
        }
        parent = parent->GetParent();
    }

    return nullptr;
}

// �ж��Ƿ����
ABnfGuessError ALittleScriptUtility::CheckError(const std::shared_ptr<ABnfElement>& parent, const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list)
{
    int register_count = 0;
    int coroutine_count = 0;
    int access_count = 0;

    int language_count = 0;
    int const_count = 0;
    int nullable_count = 0;
    int proto_cmd_count = 0;
    int native_count = 0;

    for (const auto& element : element_list)
    {
        if (element->GetRegisterModifier() != nullptr)
        {
            ++register_count;

            if (register_count > 1)
                return ABnfGuessError(element->GetRegisterModifier(), u8"register���η�ֻ�ܶ���һ��");

            // registerֻ������namespace
            if (!std::dynamic_pointer_cast<ALittleScriptNamespaceDecElement>(parent))
                return ABnfGuessError(element->GetRegisterModifier(), u8"registerֻ������namespace");
        }
        else if (element->GetCoroutineModifier() != nullptr)
        {
            ++coroutine_count;

            if (coroutine_count > 1)
                return ABnfGuessError(element->GetCoroutineModifier(), u8"Э�����η�ֻ�ܶ���һ��");

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
                return ABnfGuessError(element->GetCoroutineModifier(), u8"Э�����η�����ȫ�ֺ��������Ա�������ྲ̬����");
        }
        else if (element->GetAccessModifier() != nullptr)
        {
            ++access_count;

            if (access_count > 1)
                return ABnfGuessError(element->GetAccessModifier(), u8"�������η�ֻ�ܶ���һ��");
            
            if (std::dynamic_pointer_cast<ALittleScriptMethodParamOneDecElement>(parent))
                return ABnfGuessError(element->GetAccessModifier(), u8"�������η��������κ����β�");
                
            if (std::dynamic_pointer_cast<ALittleScriptNamespaceDecElement>(parent))
                return ABnfGuessError(element->GetAccessModifier(), u8"�������η���������namespace");
                
            if (std::dynamic_pointer_cast<ALittleScriptAllExprElement>(parent))
                return ABnfGuessError(element->GetAccessModifier(), u8"�������η��������α��ʽ�б�");
        }
        else if (element->GetAttributeModifier() != nullptr)
        {
            auto attribute = element->GetAttributeModifier();
            if (attribute->GetLanguageModifier() != nullptr)
            {
                ++language_count;
                if (language_count > 1)
                    return ABnfGuessError(attribute->GetLanguageModifier(), u8"Language���η����ֻ����һ��");

                if (std::dynamic_pointer_cast<ALittleScriptMethodParamOneDecElement>(parent))
                    return ABnfGuessError(attribute, u8"Language���η��������κ����β�");
            }
            else if (attribute->GetConstModifier() != nullptr)
            {
                ++const_count;
                if (const_count > 1)
                    return ABnfGuessError(attribute->GetConstModifier(), u8"Const���η����ֻ����һ��");

                bool has_error = true;
                if (std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(parent))
                {
                    auto class_element_dec = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(parent);
                    has_error = class_element_dec->GetClassGetterDec() == nullptr
                        && class_element_dec->GetClassSetterDec() == nullptr
                        && class_element_dec->GetClassMethodDec() == nullptr;
                }

                if (has_error)
                    return ABnfGuessError(attribute, u8"Const���η�������getter��������setter���������Ա����");
            }
            else if (attribute->GetNullableModifier() != nullptr)
            {
                ++nullable_count;
                if (nullable_count > 1)
                    return ABnfGuessError(attribute->GetNullableModifier(), u8"Nullable���η����ֻ����һ��");

                if (!std::dynamic_pointer_cast<ALittleScriptMethodParamOneDecElement>(parent))
                    return ABnfGuessError(attribute->GetNullableModifier(), u8"Nullableֻ�����κ����β�");
            }
            else if (attribute->GetProtocolModifier() != nullptr)
            {
                ++proto_cmd_count;
                if (proto_cmd_count > 1)
                    return ABnfGuessError(attribute->GetProtocolModifier(), u8"Э�����η����������η����ֻ����һ��");
                
                bool has_error = true;
                if (std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(parent))
                {
                    auto namespace_element_dec = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(parent);
                    has_error = namespace_element_dec->GetGlobalMethodDec() == nullptr;
                }

                if (has_error)
                    return ABnfGuessError(attribute, u8"Э�����η�ֻ������ȫ�ֺ���");
            }
            else if (attribute->GetCommandModifier() != nullptr)
            {
                ++proto_cmd_count;
                if (proto_cmd_count > 1)
                    return ABnfGuessError(attribute->GetCommandModifier(), u8"Э�����η����������η����ֻ����һ��");

                bool has_error = true;
                if (std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(parent))
                {
                    auto namespace_element_dec = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(parent);
                    has_error = namespace_element_dec->GetGlobalMethodDec() == nullptr;
                }

                if (has_error)
                    return ABnfGuessError(attribute, u8"�������η�ֻ������ȫ�ֺ���");
            }
            else if (attribute->GetNativeModifier() != nullptr)
            {
                ++native_count;
                if (native_count > 1)
                    return ABnfGuessError(attribute->GetCommandModifier(), u8"ԭ�����η����������η����ֻ����һ��");

                bool has_error = true;
                if (std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(parent))
                {
                    auto class_element_dec = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(parent);
                    if (class_element_dec->GetClassVarDec() != nullptr)
                    {
                        ABnfGuessPtr guess;
                        auto error = class_element_dec->GetClassVarDec()->GuessType(guess);
                        if (error) return error;

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
                    return ABnfGuessError(attribute, u8"Native���η�ֻ������class�����ԱList�ı�����for���ʽ");
            }
        }
    }

    return nullptr;
}

// ��ȡ�Ƿ���register
bool ALittleScriptUtility::IsRegister(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list)
{
    for (const auto& element : element_list)
    {
        if (element->GetRegisterModifier() != nullptr)
            return true;
    }
    return false;
}

// ��ȡ�Ƿ���Const
bool ALittleScriptUtility::IsConst(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list)
{
    for (const auto& element : element_list)
    {
        if (element->GetAttributeModifier() != nullptr
            && element->GetAttributeModifier()->GetConstModifier() != nullptr)
            return true;
    }
    return false;
}

// ��ȡ�Ƿ���Nullable
bool ALittleScriptUtility::IsNullable(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list)
{
    for (const auto& element : element_list)
    {
        if (element->GetAttributeModifier() != nullptr
            && element->GetAttributeModifier()->GetNullableModifier() != nullptr)
            return true;
    }
    return false;
}

// ��ȡЭ������
std::string ALittleScriptUtility::GetCoroutineType(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list)
{
    for (const auto& element : element_list)
    {
        if (element->GetCoroutineModifier() != nullptr)
        {
            return element->GetCoroutineModifier()->GetElementText();
        }
    }
    return "";
}

// ��ȡЭ������
std::string ALittleScriptUtility::GetProtocolType(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list)
{
    for (const auto& element : element_list)
    {
        if (element->GetAttributeModifier() != nullptr
            && element->GetAttributeModifier()->GetProtocolModifier() != nullptr)
        {
            return element->GetAttributeModifier()->GetProtocolModifier()->GetElementText();
        }

    }
    return "";
}

// ��ȡ��������
bool ALittleScriptUtility::GetCommandDetail(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list, std::string& cmd, std::string& desc)
{
    for (const auto& element : element_list)
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

// ��ȡ����Ȩ������
ClassAccessType ALittleScriptUtility::CalcAccessType(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list)
{
    for (const auto& element : element_list)
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

// ��ȡĳ��Ԫ�ص����������
std::shared_ptr<ALittleScriptNamespaceDecElement> ALittleScriptUtility::GetNamespaceDec(ABnfFile* file)
{
    if (file == nullptr) return nullptr;
    auto root = std::dynamic_pointer_cast<ALittleScriptRootElement>(file->GetRoot());
    if (root == nullptr) return nullptr;

    return root->GetNamespaceDec();
}

// ��ȡĳ��Ԫ�ص�������������
std::shared_ptr<ALittleScriptNamespaceNameDecElement> ALittleScriptUtility::GetNamespaceNameDec(ABnfFile* file)
{
    auto namespace_dec = GetNamespaceDec(file);
    if (namespace_dec == nullptr) return nullptr;

    return namespace_dec->GetNamespaceNameDec();
}

// �ж�ĳ���ǲ���register
bool ALittleScriptUtility::IsRegister(const std::shared_ptr<ABnfElement>& element)
{
    auto namespace_dec = GetNamespaceDec(element->GetFile());
    if (namespace_dec == nullptr) return false;

    return IsRegister(namespace_dec->GetModifierList());
}

// �ж�ĳ���ǲ���register
bool ALittleScriptUtility::IsRegister(ABnfFile* file)
{
    if (file == nullptr) return false;
    auto namespace_dec = GetNamespaceDec(file);
    if (namespace_dec == nullptr) return false;

    return IsRegister(namespace_dec->GetModifierList());
}

// ��ȡĳ��Ԫ�ص���������
const std::string& ALittleScriptUtility::GetNamespaceName(const std::shared_ptr<ABnfElement>& element)
{
    static std::string empty;
    if (element == nullptr) return empty;
    auto namespace_name_dec = GetNamespaceNameDec(element->GetFile());
    if (namespace_name_dec == nullptr) return empty;
    return namespace_name_dec->GetElementText();
}

// ��ȡ��������
const std::string& ALittleScriptUtility::GetNamespaceName(ABnfFile* file)
{
    static std::string empty;
    auto namespace_name_dec = GetNamespaceNameDec(file);
    if (namespace_name_dec == nullptr) return empty;
    return namespace_name_dec->GetElementText();
}

// ��ȡ���Ԫ�����ڵ���
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

// ��ȡ���Ԫ�����ڵĺ���ģ��
std::shared_ptr<ALittleScriptTemplateDecElement> ALittleScriptUtility::FindMethodTemplateDecFromParent(std::shared_ptr<ABnfElement> dec)
{
    while (dec != nullptr)
    {
        if (std::dynamic_pointer_cast<ALittleScriptRootElement>(dec))
            return nullptr;
        
        if (std::dynamic_pointer_cast<ALittleScriptClassDecElement>(dec))
            return nullptr;
        
        if (std::dynamic_pointer_cast<ALittleScriptClassCtorDecElement>(dec))
            return nullptr;
        
        if (std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(dec))
            return nullptr;
        
        if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(dec))
            return std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(dec)->GetTemplateDec();
        
        if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(dec))
            return std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(dec)->GetTemplateDec();
        
        if (std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(dec))
            return std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(dec)->GetTemplateDec();

        dec = dec->GetParent();
    }
    return nullptr;
}

// ����Ƿ��ھ�̬������
bool ALittleScriptUtility::IsInClassStaticMethod(const std::shared_ptr<ABnfElement>& dec)
{
    std::shared_ptr<ABnfElement> parent = dec;
    while (true)
    {
        if (parent == nullptr) break;

        if (std::dynamic_pointer_cast<ALittleScriptRootElement>(parent))
            return false;
        
        if (std::dynamic_pointer_cast<ALittleScriptClassDecElement>(parent))
            return false;
        
        if (std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(parent))
            return false;
        
        if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent))
            return false;
        
        if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent))
            return true;
        
        if (std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent))
            return false;

        parent = parent->GetParent();
    }

    return false;
}

// �������ƣ���ȡ����ṹ��ĳ�Ա�б�
void ALittleScriptUtility::FindStructVarDecList(const std::shared_ptr<ALittleScriptStructDecElement>& dec, const std::string& name, std::vector<std::shared_ptr<ALittleScriptStructVarDecElement>>& result, int deep)
{
    if (deep <= 0) return;

    // ����ǰ
    const auto* data = dynamic_cast<ALittleScriptIndex*>(dec->GetFile()->GetProject())->GetStructData(dec);
    if (data != nullptr)
        data->FindVarDecList(name, result);

    // ����̳�
    const auto extends_dec = FindStructExtends(dec);
    if (extends_dec != nullptr)
        FindStructVarDecList(extends_dec, name, result, deep - 1);
}

// �������ƣ���ȡ���ö���еĳ�Ա
void ALittleScriptUtility::FindEnumVarDecList(const std::shared_ptr<ALittleScriptEnumDecElement>& dec, const std::string& name, std::vector<std::shared_ptr<ALittleScriptEnumVarDecElement>>& result)
{
    const auto* data = dynamic_cast<ALittleScriptIndex*>(dec->GetFile()->GetProject())->GetEnumData(dec);
    if (data != nullptr)
        data->FindVarDecList(name, result);
}

// ����struct�ĸ���
std::shared_ptr<ALittleScriptStructDecElement> ALittleScriptUtility::FindStructExtends(const std::shared_ptr<ALittleScriptStructDecElement>& dec)
{
    // ��ȡ�̳�
    auto extends_dec = dec->GetStructExtendsDec();
    if (extends_dec == nullptr) return nullptr;

    // ��ȡ�ṹ����
    auto name_dec = extends_dec->GetStructNameDec();
    if (name_dec == nullptr) return nullptr;

    // ��ȡ������
    std::string namespace_name;
    auto extends_namespace_name_dec = extends_dec->GetNamespaceNameDec();
    if (extends_namespace_name_dec != nullptr)
        namespace_name = extends_namespace_name_dec->GetElementText();
    else
        namespace_name = GetNamespaceName(dec);

    // ��ȡԪ�ض���
    const auto result = dynamic_cast<ALittleScriptIndex*>(dec->GetFile()->GetProject())->FindALittleNameDec(
        ABnfElementType::STRUCT_NAME, dec->GetFile(), namespace_name, name_dec->GetElementText(), true);
    if (std::dynamic_pointer_cast<ALittleScriptStructNameDecElement>(result))
        return std::dynamic_pointer_cast<ALittleScriptStructDecElement>(result->GetParent());

    return nullptr;
}

// ����class�ĸ���
std::shared_ptr<ALittleScriptClassDecElement> ALittleScriptUtility::FindClassExtends(const std::shared_ptr<ALittleScriptClassDecElement>& dec)
{
    // ��ȡ�̳�
    auto extends_dec = dec->GetClassExtendsDec();
    if (extends_dec == nullptr) return nullptr;

    // ��ȡ����
    auto name_dec = extends_dec->GetClassNameDec();
    if (name_dec == nullptr) return nullptr;

    // ��ȡ������
    std::string namespace_name;
    auto extends_namespace_name_dec = extends_dec->GetNamespaceNameDec();
    if (extends_namespace_name_dec != nullptr)
        namespace_name = extends_namespace_name_dec->GetElementText();
    else
        namespace_name = GetNamespaceName(dec);

    // ��ȡԪ�ض���
    const auto result = dynamic_cast<ALittleScriptIndex*>(dec->GetFile()->GetProject())->FindALittleNameDec(
        ABnfElementType::CLASS_NAME, dec->GetFile(), namespace_name, name_dec->GetElementText(), true);
    if (std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(result))
        return std::dynamic_pointer_cast<ALittleScriptClassDecElement>(result->GetParent());

    return nullptr;
}

// ����������ͬ��Ԫ��
void ALittleScriptUtility::FilterSameName(const std::vector<std::shared_ptr<ABnfElement>>& list, std::vector<std::shared_ptr<ABnfElement>>& out)
{
    std::map<std::string, std::shared_ptr<ABnfElement>> map;
    for (int i = static_cast<int>(list.size()) - 1; i >= 0; --i)
        map[list[i]->GetElementText()] = list[i];

    out.resize(0);
    for (auto& pair : map) out.push_back(pair.second);
}

// ������dec������У���targetDec��Ա�ķ���Ȩ��
int ALittleScriptUtility::CalcAccessLevelByTargetClassDec(int access_level, const std::shared_ptr<ALittleScriptClassDecElement>& dec
    , const std::shared_ptr<ALittleScriptClassDecElement>& target_dec)
{
    // �����ǰ����Ȩ���Ѿ�ֻʣ��public����ֱ�ӷ���
    if (access_level <= sAccessOnlyPublic)
        return access_level;

    // ���dec��Ŀ��decһ�£���ôֱ�ӷ���
    if (dec == target_dec)
        return access_level;

    // ���dec�ĸ��࣬Ȼ���жϸ����targetDec�ķ���Ȩ��
    const auto extends_dec = FindClassExtends(dec);
    if (extends_dec != nullptr)
        return CalcAccessLevelByTargetClassDec(access_level, extends_dec, target_dec);

    // ���û�и��࣬����Ƿ�������ͬ�������£��������ô���Է���public��protected
    if (GetNamespaceName(dec) == GetNamespaceName(target_dec))
        return sAccessProtectedAndPublic;

    // ����ֻ�ܷ���public
    return sAccessOnlyPublic;
}

// ��������Ԫ�ط���targetDec�ķ���Ȩ��
int ALittleScriptUtility::CalcAccessLevelByTargetClassDecForElement(const std::shared_ptr<ABnfElement>& element, const std::shared_ptr<ALittleScriptClassDecElement>& target_dec)
{
    // Ĭ��Ϊpublic
    int access_level = sAccessOnlyPublic;

    // ������Ԫ�������У���ô����ͨ�����targetDec����Ȩ��ֱ�Ӽ���
    const auto dec = FindClassDecFromParent(element);
    if (dec != nullptr)
    {
        access_level = CalcAccessLevelByTargetClassDec(sAccessPrivateAndProtectedAndPublic, dec, target_dec);
    }
    // ���Ԫ�ز������У���ôelement��lua�У����ߺ�targetDec��ͬ���򷵻�sAccessProtectedAndPublic
    // �����ͬһ���ļ��У��򷵻�sAccessPrivateAndProtectedAndPublic
    else
    {
	    const std::string namespace_name = GetNamespaceName(element);
        if (element->GetFullPath() == target_dec->GetFullPath())
            access_level = sAccessPrivateAndProtectedAndPublic;
        else if (namespace_name == "alittle" || namespace_name == GetNamespaceName(target_dec))
            access_level = sAccessProtectedAndPublic;
    }

    return access_level;
}

// �������ƣ���ȡ�����б�
void ALittleScriptUtility::FindClassMethodNameDecList(const std::shared_ptr<ALittleScriptClassDecElement>& dec, int access_level, const std::string& name, std::vector<std::shared_ptr<ABnfElement>>& result, int deep)
{
    // ��������������޵ݹ�
    if (deep <= 0) return;

    // �������е�Ԫ��
    const auto* data = dynamic_cast<ALittleScriptIndex*>(dec->GetFile()->GetProject())->GetClassData(dec);
    if (data != nullptr)
    {
        data->FindClassAttrList(access_level, ClassAttrType::FUN, name, result);
        data->FindClassAttrList(access_level, ClassAttrType::GETTER, name, result);
        data->FindClassAttrList(access_level, ClassAttrType::SETTER, name, result);
        data->FindClassAttrList(access_level, ClassAttrType::STATIC, name, result);
    }

    // ����̳�
    const auto extends_dec = FindClassExtends(dec);
    if (extends_dec != nullptr)
        FindClassMethodNameDecList(extends_dec, access_level, name, result, deep - 1);
}

// �������ƣ���ȡ��������б�
void ALittleScriptUtility::FindClassAttrList(const std::shared_ptr<ALittleScriptClassDecElement>& dec, int access_level, ClassAttrType attr_type, const std::string& name, std::vector<std::shared_ptr<ABnfElement>>& result, int deep)
{
    // ��������������޵ݹ�
    if (deep <= 0) return;

    // �����Ա
    dynamic_cast<ALittleScriptIndex*>(dec->GetFile()->GetProject())->FindClassAttrList(dec, access_level, attr_type, name, result);

    // ����̳�
    const auto extends_dec = FindClassExtends(dec);
    if (extends_dec != nullptr)
        FindClassAttrList(extends_dec, access_level, attr_type, name, result, deep - 1);
}

// �������ƣ���ȡ�̳еĹ��캯��
std::shared_ptr<ALittleScriptClassCtorDecElement> ALittleScriptUtility::FindFirstCtorDecFromExtends(const std::shared_ptr<ALittleScriptClassDecElement> & dec, int deep)
{
    // ��������������޵ݹ�
    if (deep <= 0) return nullptr;

    // ��ȡclass��
    auto body_dec = dec->GetClassBodyDec();
    if (body_dec == nullptr) return nullptr;

    // �����Ա����
    const auto& element_dec_list = body_dec->GetClassElementDecList();
    for (const auto& element_dec : element_dec_list)
    {
        if (element_dec->GetClassCtorDec() != nullptr)
            return element_dec->GetClassCtorDec();
    }

    // ����̳�
    const auto extends_dec = FindClassExtends(dec);
    if (extends_dec != nullptr)
        return FindFirstCtorDecFromExtends(extends_dec, deep - 1);

    return nullptr;
}

// �������ƣ���ȡ�̳е�����
std::shared_ptr<ABnfElement> ALittleScriptUtility::FindFirstClassAttrFromExtends(const std::shared_ptr<ALittleScriptClassDecElement>& dec, ClassAttrType attr_type, const std::string& name, int deep)
{
    // ��������������޵ݹ�
    if (deep <= 0) return nullptr;

    // ����setter����
    auto result = dynamic_cast<ALittleScriptIndex*>(dec->GetFile()->GetProject())->FindClassAttr(dec,
        sAccessPrivateAndProtectedAndPublic, attr_type, name);
    if (result != nullptr) return result;

    // ����̳�
    const auto extends_dec = FindClassExtends(dec);
    if (extends_dec != nullptr)
        return FindFirstClassAttrFromExtends(extends_dec, attr_type, name, deep - 1);

    return nullptr;
}

// �������ƣ����Һ����Ĳ����б�
void ALittleScriptUtility::FindMethodParamNameDecList(const std::shared_ptr<ABnfElement>& method_dec, const std::string& name, std::vector<std::shared_ptr<ALittleScriptMethodParamNameDecElement>>& result)
{
    result.resize(0);

    std::vector<std::shared_ptr<ALittleScriptMethodParamOneDecElement>> param_one_dec_list;
    // �����캯���Ĳ����б�
    if (std::dynamic_pointer_cast<ALittleScriptClassCtorDecElement>(method_dec))
    {
        auto method_param_dec = std::dynamic_pointer_cast<ALittleScriptClassCtorDecElement>(method_dec)->GetMethodParamDec();
        if (method_param_dec != nullptr)
            param_one_dec_list = method_param_dec->GetMethodParamOneDecList();
    }
    // �����Ա�����Ĳ����б�
    else if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(method_dec))
    {
        auto method_param_dec = std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(method_dec)->GetMethodParamDec();
        if (method_param_dec != nullptr)
            param_one_dec_list = method_param_dec->GetMethodParamOneDecList();
    }
    // ����̬�����Ĳ����б�
    else if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(method_dec))
    {
        auto method_param_dec = std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(method_dec)->GetMethodParamDec();
        if (method_param_dec != nullptr)
            param_one_dec_list = method_param_dec->GetMethodParamOneDecList();
    }
    // ����setter�����Ĳ����б�
    else if (std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(method_dec))
    {
        auto method_setter_param_dec = std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(method_dec)->GetMethodSetterParamDec();
        if (method_setter_param_dec != nullptr)
        {
            const auto param_one_dec = method_setter_param_dec->GetMethodParamOneDec();
            if (param_one_dec != nullptr)
                param_one_dec_list.push_back(param_one_dec);
        }
    }
    // ����ȫ�ֺ����Ĳ����б�
    else if (std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(method_dec))
    {
        auto method_param_dec = std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(method_dec)->GetMethodParamDec();
        if (method_param_dec != nullptr)
            param_one_dec_list = method_param_dec->GetMethodParamOneDecList();
    }

    // �ռ����еĲ�����Ԫ��
    for (auto& one_dec : param_one_dec_list)
    {
        auto name_dec = one_dec->GetMethodParamNameDec();
        if (name_dec == nullptr) continue;
        if (name.empty() || name_dec->GetElementText() == name)
            result.push_back(name_dec);
    }
}

// �������ƣ����ұ��������ڵĶ���Ԫ��
void ALittleScriptUtility::FindVarAssignNameDecList(const std::shared_ptr<ABnfElement>& element, const std::string& name, std::vector<std::shared_ptr<ALittleScriptVarAssignNameDecElement>>& result)
{
    result.resize(0);

    // ��������ڵı��ʽ
    auto parent = element;
    while (parent != nullptr)
    {
        if (std::dynamic_pointer_cast<ALittleScriptAllExprElement>(parent))
        {
            FindVarAssignNameDecList(std::dynamic_pointer_cast<ALittleScriptAllExprElement>(parent), result, name);
            break;
        }
        if (std::dynamic_pointer_cast<ALittleScriptForStartStatElement>(parent))
        {
            const auto for_step_condition = std::dynamic_pointer_cast<ALittleScriptForStepConditionElement>(parent->GetParent());
            if (for_step_condition == nullptr) break;
            const auto for_condition = std::dynamic_pointer_cast<ALittleScriptForConditionElement>(for_step_condition->GetParent());
            if (for_condition == nullptr) break;
            const auto for_expr = std::dynamic_pointer_cast<ALittleScriptForExprElement>(for_condition->GetParent());
            if (for_expr == nullptr) break;
            const auto all_expr = std::dynamic_pointer_cast<ALittleScriptAllExprElement>(for_expr->GetParent());
            if (all_expr == nullptr) break;
            FindVarAssignNameDecList(all_expr, result, name);
            break;
        }
        if (std::dynamic_pointer_cast<ALittleScriptForStepConditionElement>(parent))
        {
            const auto for_condition = std::dynamic_pointer_cast<ALittleScriptForConditionElement>(parent->GetParent());
            if (for_condition == nullptr) break;
            const auto for_expr = std::dynamic_pointer_cast<ALittleScriptForExprElement>(for_condition->GetParent());
            if (for_expr == nullptr) break;
            FindVarAssignNameDecList(for_expr, result, name);
            break;
        }
        parent = parent->GetParent();
    }
}

// �������ƣ����Ҷ�����ʽ���б�
void ALittleScriptUtility::FindVarAssignNameDecList(const std::shared_ptr<ALittleScriptAllExprElement>& all_expr, std::vector<std::shared_ptr<ALittleScriptVarAssignNameDecElement>>& result, const std::string& name)
{
    auto parent = all_expr->GetParent();
    std::vector<std::shared_ptr<ALittleScriptAllExprElement>> all_expr_list;

    // ��������
    if (std::dynamic_pointer_cast<ALittleScriptMethodBodyDecElement>(parent))
    {
        auto cur_expr = std::dynamic_pointer_cast<ALittleScriptMethodBodyDecElement>(parent);
        all_expr_list = cur_expr->GetAllExprList();
    }
    // ����forѭ��
    else if (std::dynamic_pointer_cast<ALittleScriptForExprElement>(parent) || std::dynamic_pointer_cast<ALittleScriptForBodyElement>(parent))
    {
        if (std::dynamic_pointer_cast<ALittleScriptForBodyElement>(parent)) parent = parent->GetParent();
        FindVarAssignNameDecList(std::dynamic_pointer_cast<ALittleScriptAllExprElement>(parent->GetParent()), result, name);

        auto cur_expr = std::dynamic_pointer_cast<ALittleScriptForExprElement>(parent);

        // ��ȡfor�ڲ��ı��ʽ
        if (cur_expr->GetForBody() != nullptr)
            all_expr_list = cur_expr->GetForBody()->GetAllExprList();
        if (cur_expr->GetAllExpr() != nullptr)
        {
            all_expr_list.push_back(cur_expr->GetAllExpr());
        }

        const auto for_condition = cur_expr->GetForCondition();
        if (for_condition != nullptr)
            FindVarAssignNameDecList(for_condition, result, name);
    }
    // ����whileѭ��
    else if (std::dynamic_pointer_cast<ALittleScriptWhileExprElement>(parent) || std::dynamic_pointer_cast<ALittleScriptWhileBodyElement>(parent))
    {
        if (std::dynamic_pointer_cast<ALittleScriptWhileBodyElement>(parent)) parent = parent->GetParent();
        FindVarAssignNameDecList(std::dynamic_pointer_cast<ALittleScriptAllExprElement>(parent->GetParent()), result, name);
        auto cur_expr = std::dynamic_pointer_cast<ALittleScriptWhileExprElement>(parent);
        if (cur_expr->GetWhileBody() != nullptr)
            all_expr_list = cur_expr->GetWhileBody()->GetAllExprList();
        else if (cur_expr->GetAllExpr() != nullptr)
        {
            all_expr_list.push_back(cur_expr->GetAllExpr());
        }
    }
    // ����do while
    else if (std::dynamic_pointer_cast<ALittleScriptDoWhileExprElement>(parent) || std::dynamic_pointer_cast<ALittleScriptDoWhileBodyElement>(parent))
    {
        if (std::dynamic_pointer_cast<ALittleScriptDoWhileBodyElement>(parent)) parent = parent->GetParent();
        FindVarAssignNameDecList(std::dynamic_pointer_cast<ALittleScriptAllExprElement>(parent->GetParent()), result, name);
        auto cur_expr = std::dynamic_pointer_cast<ALittleScriptDoWhileExprElement>(parent);
        if (cur_expr->GetDoWhileBody() != nullptr)
            all_expr_list = cur_expr->GetDoWhileBody()->GetAllExprList();
    }
    // ���� if
    else if (std::dynamic_pointer_cast<ALittleScriptIfExprElement>(parent) || std::dynamic_pointer_cast<ALittleScriptIfBodyElement>(parent))
    {
        if (std::dynamic_pointer_cast<ALittleScriptIfBodyElement>(parent)) parent = parent->GetParent();
        FindVarAssignNameDecList(std::dynamic_pointer_cast<ALittleScriptAllExprElement>(parent->GetParent()), result, name);
        auto cur_expr = std::dynamic_pointer_cast<ALittleScriptIfExprElement>(parent);
        if (cur_expr->GetIfBody() != nullptr)
            all_expr_list = cur_expr->GetIfBody()->GetAllExprList();
        else if (cur_expr->GetAllExpr() != nullptr)
        {
            all_expr_list.push_back(cur_expr->GetAllExpr());
        }
    }
    // ���� else if
    else if (std::dynamic_pointer_cast<ALittleScriptElseIfExprElement>(parent) || std::dynamic_pointer_cast<ALittleScriptElseIfBodyElement>(parent))
    {
        if (std::dynamic_pointer_cast<ALittleScriptElseIfBodyElement>(parent)) parent = parent->GetParent();
        FindVarAssignNameDecList(std::dynamic_pointer_cast<ALittleScriptAllExprElement>(parent->GetParent()->GetParent()), result, name);
        auto cur_expr = std::dynamic_pointer_cast<ALittleScriptElseIfExprElement>(parent);
        if (cur_expr->GetElseIfBody() != nullptr)
            all_expr_list = cur_expr->GetElseIfBody()->GetAllExprList();
        else if (cur_expr->GetAllExpr() != nullptr)
        {
            all_expr_list.push_back(cur_expr->GetAllExpr());
        }
    }
    // ���� else
    else if (std::dynamic_pointer_cast<ALittleScriptElseExprElement>(parent) || std::dynamic_pointer_cast<ALittleScriptElseBodyElement>(parent))
    {
        if (std::dynamic_pointer_cast<ALittleScriptElseBodyElement>(parent)) parent = parent->GetParent();
        FindVarAssignNameDecList(std::dynamic_pointer_cast<ALittleScriptAllExprElement>(parent->GetParent()->GetParent()), result, name);
        auto cur_expr = std::dynamic_pointer_cast<ALittleScriptElseExprElement>(parent);
        if (cur_expr->GetElseBody() != nullptr)
            all_expr_list = cur_expr->GetElseBody()->GetAllExprList();
        else if (cur_expr->GetAllExpr() != nullptr)
        {
            all_expr_list.push_back(cur_expr->GetAllExpr());
        }
    }
    // ���� wrap
    else if (std::dynamic_pointer_cast<ALittleScriptWrapExprElement>(parent))
    {
        FindVarAssignNameDecList(std::dynamic_pointer_cast<ALittleScriptAllExprElement>(parent->GetParent()), result, name);
        auto cur_expr = std::dynamic_pointer_cast<ALittleScriptWrapExprElement>(parent);
        all_expr_list = cur_expr->GetAllExprList();
    }

    if (all_expr_list.empty()) return;

    for (auto& expr : all_expr_list)
    {
        // ����Ѿ���������ǰ����ô�Ϳ��Է�����
        if (expr == all_expr) return;

        // ��ȡ������ʽ
        auto var_assign_expr = expr->GetVarAssignExpr();
        if (var_assign_expr == nullptr) continue;

        // ��ȡ�������б�
        const auto& var_assign_dec_list = var_assign_expr->GetVarAssignDecList();
        for (const auto& var_assign_dec : var_assign_dec_list)
        {
            auto var_assign_name_dec = var_assign_dec->GetVarAssignNameDec();
            if (var_assign_name_dec == nullptr) continue;
            if (name.empty() || name == var_assign_name_dec->GetElementText())
                result.push_back(var_assign_name_dec);
        }
    }
}

// ����������
bool ALittleScriptUtility::IsPairsFunction(const std::vector<ABnfGuessPtr>& guess_list)
{
    // guess_list���ȱ�����3
    if (guess_list.size() != 3) return false;
    // ��һ�������Ǻ���
    auto guess = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess_list[0]);
    if (!guess) return false;
    // �������ܴ�await
    if (guess->await_modifier) return false;
    // �������ܴ�proto
    if (!guess->proto.empty()) return false;
    // ����������ģ�庯��
    if (!guess->template_param_list.empty()) return false;
    // ��������������2��
    if (guess->param_list.size() != 2) return false;
    if (guess->param_nullable_list.size() != 2) return false;
    // �����Ĳ������ܴ�Nullable
    if (guess->param_nullable_list[0]) return false;
    if (guess->param_nullable_list[1]) return false;
    // ���������в���ռλ��
    const auto param_tail_e = guess->param_tail.lock();
    if (param_tail_e != nullptr) return false;
    // ���������з���ֵ������������������Ҳ��ʾfor�ı����б������
    if (!guess->return_list.empty()) return false;
    // ���������з���ֵռλ��
    const auto return_tail_e = guess->return_tail.lock();
    if (return_tail_e != nullptr) return false;
    // �����ĵ�һ�����������guess_list�ڶ�������һ��
    const auto param_list_0 = guess->param_list[0].lock();
    if (param_list_0 == nullptr || param_list_0->GetValue() != guess_list[1]->GetValue()) return false;
    // �����ĵڶ������������guess_list�ڶ�������һ��
    const auto param_list_1 = guess->param_list[1].lock();
    if (param_list_1 == nullptr || param_list_1->GetValue() != guess_list[2]->GetValue()) return false;
    return true;
}

// ������ʽ��Ҫʹ��ʲô���ı�����ʽ
ABnfGuessError ALittleScriptUtility::CalcPairsTypeForLua(const std::shared_ptr<ALittleScriptValueStatElement>& value_stat, std::string& result)
{
    result = "";
    std::vector<ABnfGuessPtr> guess_list;
    auto error = value_stat->GuessTypes(guess_list);
    if (error) return error;

    // �س���ģ������
    if (guess_list.size() == 1 && std::dynamic_pointer_cast<ALittleScriptGuessList>(guess_list[0]))
    {
        result = "___ipairs";
        return nullptr;
    }
    else if (guess_list.size() == 1 && std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess_list[0]))
    {
        result = "___pairs";
        return nullptr;
    }

    // �Ѿ��ǵ��������ˣ��Ͳ���Ҫ��Χ����
    if (IsPairsFunction(guess_list)) return nullptr;

    return ABnfGuessError(value_stat, u8"�ñ��ʽ���ܱ���");
}

// ������ʽ��for��ʹ��in����of
ABnfGuessError ALittleScriptUtility::CalcPairsTypeForJavaScript(const std::shared_ptr<ALittleScriptValueStatElement>& value_stat, std::string& result, bool& is_native)
{
    result = "Other";
    is_native = false;
    std::vector<ABnfGuessPtr> guess_list;
    auto error = value_stat->GuessTypes(guess_list);
    if (error) return error;

    // �س���ģ������
    if (guess_list.size() == 1 && std::dynamic_pointer_cast<ALittleScriptGuessList>(guess_list[0]))
    {
        result = "List";
        is_native = std::dynamic_pointer_cast<ALittleScriptGuessList>(guess_list[0])->is_native;
        return nullptr;
    }
    else if (guess_list.size() == 1 && std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess_list[0]))
    {
        if (std::dynamic_pointer_cast<ALittleScriptGuessString>(std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess_list[0])->key_type.lock()))
            result = "Object";
        else
            result = "Map";
        return nullptr;
    }

    // �Ѿ��ǵ��������ˣ��Ͳ���Ҫ��Χ����
    if (IsPairsFunction(guess_list)) return nullptr;

    return ABnfGuessError(value_stat, u8"�ñ��ʽ���ܱ���");
}

// �ж� parent�Ƿ���child�ĸ���
ABnfGuessError ALittleScriptUtility::IsClassSuper(const std::shared_ptr<ALittleScriptClassDecElement>& child, const std::string& parent, bool& result)
{
    result = false;
    // ��ȡ�̳�
    auto extends_dec = child->GetClassExtendsDec();
    if (extends_dec == nullptr) return nullptr;

    // ��ȡ����
    auto name_dec = extends_dec->GetClassNameDec();
    if (name_dec == nullptr) return nullptr;

    // ��ȡ����
    ABnfGuessPtr guess;
    auto error = name_dec->GuessType(guess);
    if (error) return error;

    // �����жϸ���ĸ���
    const auto guess_class = std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess);
    if (guess_class == nullptr) return nullptr;

    // ����Ƿ�һ��
    if (guess_class->GetValueWithoutConst() == parent)
    {
        result = true;
        return nullptr;
    }

    return IsClassSuper(guess_class->class_dec.lock(), parent, result);
}

// �ж� parent�Ƿ���child�ĸ���
ABnfGuessError ALittleScriptUtility::IsStructSuper(const std::shared_ptr<ABnfElement>& child, const std::string& parent, bool& result)
{
    result = false;

    auto struct_child = std::dynamic_pointer_cast<ALittleScriptStructDecElement>(child);
    if (struct_child == nullptr) return nullptr;

    // ��ȡ�̳�
    auto extends_dec = struct_child->GetStructExtendsDec();
    if (extends_dec == nullptr) return nullptr;

    // ��ȡ�ṹ����
    auto name_dec = extends_dec->GetStructNameDec();
    if (name_dec == nullptr) return nullptr;

    // ��ȡ����
    ABnfGuessPtr guess;
    auto error = name_dec->GuessType(guess);
    if (error) return error;

    // �����жϸ��ṹ��ĸ��ṹ��
    const auto guess_struct = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess);
    if (guess_struct == nullptr) return nullptr;

    // �ж��Ƿ�һ��
    if (guess_struct->GetValueWithoutConst() == parent)
    {
        result = true;
        return nullptr;
    }

    return IsStructSuper(guess_struct->struct_dec.lock(), parent, result);
}

// ��ȡĿ���·��
std::string ALittleScriptUtility::CalcRootFullPath(const std::string& project_path, const std::string& ext)
{
    std::string out_pre;
    if (ext == "js") out_pre = "JS";
    return project_path + out_pre + "Script/";
}

// ��ȡĿ���ļ�·��
std::string ALittleScriptUtility::CalcTargetFullPath(const std::string& project_path, const std::string& ali_full_path, const std::string& ext, std::string& error)
{
    error = "";
    const std::string ali_rel_path = ChangeFileExtByPath(ali_full_path.substr(project_path.size()), ext);
    if (ali_rel_path.find("src/") != 0)
    {
        error = u8"��Ѵ����ļ�����Ŀ¼�µ�src�ļ�����:" + project_path + "src/";
        return "";
    }

    return CalcRootFullPath(project_path, ext) + ali_rel_path.substr(strlen("src/"));
}

// �ж�ValueStat
ABnfGuessError ALittleScriptUtility::CalcReturnCount(const std::shared_ptr<ALittleScriptValueStatElement>& value_stat, int& count, std::vector<ABnfGuessPtr>& guess_list)
{
    count = 0;
    // ��ȡ�ұ߱��ʽ��
    auto error = value_stat->GuessTypes(guess_list);
    if (error) return error;

    count = static_cast<int>(guess_list.size());
    if (!guess_list.empty() && std::dynamic_pointer_cast<ALittleScriptGuessReturnTail>(guess_list.back()))
        count = -1;

    return nullptr;
}

void ALittleScriptUtility::FindVarAssignNameDecList(const std::shared_ptr<ALittleScriptForExprElement>& for_expr, std::vector<std::shared_ptr<ALittleScriptVarAssignNameDecElement>>& result, const std::string& name)
{
    FindVarAssignNameDecList(std::dynamic_pointer_cast<ALittleScriptAllExprElement>(for_expr->GetParent()), result, name);

    const auto for_condition = for_expr->GetForCondition();
    if (for_condition != nullptr)
        FindVarAssignNameDecList(for_condition, result, name);
}

void ALittleScriptUtility::FindVarAssignNameDecList(const std::shared_ptr<ALittleScriptForConditionElement>& for_condition, std::vector<std::shared_ptr<ALittleScriptVarAssignNameDecElement>>& result, const std::string& name)
{
    auto for_pair_dec = for_condition->GetForPairDec();
    if (for_pair_dec != nullptr)
    {
        // ����ʽ��for��һ����ʱ����
        if (for_condition->GetForStepCondition() != nullptr)
        {
            const auto start_stat = for_condition->GetForStepCondition()->GetForStartStat();
            if (start_stat != nullptr)
            {
                auto var_assign_name_dec = for_pair_dec->GetVarAssignNameDec();
                if (var_assign_name_dec != nullptr)
                {
                    if (name.empty() || name == var_assign_name_dec->GetElementText())
                        result.push_back(var_assign_name_dec);
                }
            }
        }
        // ����ʽ��for�ж����ʱ����
        else if (for_condition->GetForInCondition() != nullptr)
        {
            const auto& pair_dec_list_temp = for_condition->GetForInCondition()->GetForPairDecList();
            std::vector<std::shared_ptr<ALittleScriptForPairDecElement>> pair_dec_list;
            pair_dec_list.push_back(for_pair_dec);
            for (const auto& pair_dec : pair_dec_list_temp) pair_dec_list.push_back(pair_dec);

            for (auto& pair_dec : pair_dec_list)
            {
                auto var_assign_name_dec = pair_dec->GetVarAssignNameDec();
                if (var_assign_name_dec != nullptr)
                {
                    if (name.empty() || name == var_assign_name_dec->GetElementText())
                        result.push_back(var_assign_name_dec);
                }
            }
        }
    }
}
