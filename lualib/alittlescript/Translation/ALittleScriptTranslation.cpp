#include "ALittleScriptTranslation.h"

#include "../Index/ALittleScriptProjectClass.h"
#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptFileClass.h"

#include "../Generate/ALittleScriptRootElement.h"

#include "../../alanguage/Model/ABnfReference.h"
#include "../../alanguage/Model/ABnfErrorElement.h"

#include "ALittleScriptTranslationLua.h"
#include "ALittleScriptTranslationJavaScript.h"

std::shared_ptr<ALittleScriptTranslation> ALittleScriptTranslation::CreateTranslation(const std::string& language)
{
    if (language == "Lua")
        return std::shared_ptr<ALittleScriptTranslation>(new ALittleScriptTranslationLua());
    else if (language == "JavaScript")
        return std::shared_ptr<ALittleScriptTranslation>(new ALittleScriptTranslationJavaScript());
    return std::shared_ptr<ALittleScriptTranslation>(new ALittleScriptTranslation());
}

void ALittleScriptTranslation::AddRelay(ABnfElementPtr element)
{
    if (element == nullptr) return;

    auto full_path = element->GetFullPath();
    if (full_path == m_file_path) return;

    if (ALittleScriptUtility::IsRegister(element)) return;

    if (m_is_define_relay)
    {
        m_define_rely.insert(full_path);
        return;
    }

    m_run_rely.insert(full_path);
}

// 检查语法错误
ABnfGuessError ALittleScriptTranslation::CheckErrorElement(ABnfElementPtr element, bool full_check)
{
    if (std::dynamic_pointer_cast<ABnfErrorElement>(element))
    {
        auto error_element = std::dynamic_pointer_cast<ABnfErrorElement>(element);
        return ABnfGuessError(element, error_element->GetValue());
    }

    // 判断语义错误
    if (full_check)
    {
        auto error = element->GetReference()->CheckError();
        if (error) return error;
    }

    auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
    if (!node) return nullptr;

    for (auto& child : node->GetChilds())
    {
        auto error = CheckErrorElement(child, full_check);
        if (error) return error;
    }

    return nullptr;
}

ABnfGuessError ALittleScriptTranslation::Generate(ABnfFile* file, bool full_check)
{
    // 解析失败
    auto root_dec = std::dynamic_pointer_cast<ALittleScriptRootElement>(file->GetRoot());
    if (root_dec == nullptr) return ABnfGuessError(nullptr, "文件还未解析");
    auto namespace_dec = root_dec->GetNamespaceDec();
    if (namespace_dec == nullptr) return ABnfGuessError(nullptr, "命名域没有定义名字");

    auto name_dec = namespace_dec->GetNamespaceNameDec();
    if (name_dec == nullptr) return ABnfGuessError(nullptr, "命名域没有定义名字");

    m_namespace_name = name_dec->GetElementText();

    m_module_path = file->GetModulePath();
    m_file_path = file->GetFullPath();

    // 如果命名域有register标记，那么就不需要生成
    if (ALittleScriptUtility::IsRegister(namespace_dec->GetModifierList())) return nullptr;
    if (!ALittleScriptUtility::IsLanguageEnable(namespace_dec->GetModifierList())) return nullptr;

    // 获取语法错误
    auto error = CheckErrorElement(file->GetRoot(), full_check);
    if (error) return error;

    // 获取工作目录
    std::string path_error;
    auto full_path = ALittleScriptUtility::CalcTargetFullPath(m_module_path, file->GetFullPath(), GetExt(), path_error);
    if (full_path.empty()) return ABnfGuessError(nullptr, path_error);
    std::string full_dir = ALittleScriptUtility::GetFilePathByPath(full_path);
    ALittleScriptUtility::CreateDeepFolder(full_dir);
    if (!ALittleScriptUtility::IsDirExist(full_dir))
        return ABnfGuessError(nullptr, u8"文件夹创建失败:" + full_dir);

    // 生成代码
    std::string content;
    error = GenerateRoot(namespace_dec->GetNamespaceElementDecList(), content);
    if (error) return error;

    ABnfFactory::WriteAllText(full_path, content);
    return nullptr;
}
