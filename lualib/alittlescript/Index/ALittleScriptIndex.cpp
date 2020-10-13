
#include "ALittleScriptIndex.h"
#include "ALittleScriptUtility.h"
#include "ALittleScriptAccessData.h"
#include "ALittleScriptClassData.h"
#include "ALittleScriptStructData.h"
#include "ALittleScriptEnumData.h"

#include "../../alanguage/Model/ABnfElement.h"
#include "../../alanguage/Index/ABnfProject.h"
#include "../../alanguage/Index/ABnfFile.h"

#include "../Generate/ALittleScriptNamespaceDecElement.h"
#include "../Generate/ALittleScriptNamespaceElementDecElement.h"
#include "../Generate/ALittleScriptClassDecElement.h"
#include "../Generate/ALittleScriptClassExtendsDecElement.h"
#include "../Generate/ALittleScriptNamespaceNameDecElement.h"
#include "../Generate/ALittleScriptStructNameDecElement.h"
#include "../Generate/ALittleScriptClassNameDecElement.h"
#include "../Generate/ALittleScriptClassDecElement.h"
#include "../Generate/ALittleScriptTemplateDecElement.h"
#include "../Generate/ALittleScriptClassBodyDecElement.h"
#include "../Generate/ALittleScriptClassElementDecElement.h"
#include "../Generate/ALittleScriptStructDecElement.h"
#include "../Generate/ALittleScriptStructBodyDecElement.h"
#include "../Generate/ALittleScriptEnumDecElement.h"
#include "../Generate/ALittleScriptEnumBodyDecElement.h"
#include "../Generate/ALittleScriptEnumNameDecElement.h"
#include "../Generate/ALittleScriptRootElement.h"
#include "../Generate/ALittleScriptGlobalMethodDecElement.h"
#include "../Generate/ALittleScriptMethodNameDecElement.h"
#include "../Generate/ALittleScriptInstanceDecElement.h"
#include "../Generate/ALittleScriptVarAssignExprElement.h"
#include "../Generate/ALittleScriptVarAssignDecElement.h"
#include "../Generate/ALittleScriptVarAssignNameDecElement.h"
#include "../Generate/ALittleScriptUsingDecElement.h"
#include "../Generate/ALittleScriptUsingNameDecElement.h"
#include "../Generate/ALittleScriptBlockCommentElement.h"
#include "../Generate/ALittleScriptLineCommentElement.h"

#include "../Guess/ALittleScriptGuessClass.h"
#include "../Guess/ALittleScriptGuessPrimitive.h"
#include "../Guess/ALittleScriptGuessConst.h"

#include <algorithm>

ALittleScriptStatic& ALittleScriptStatic::Inst()
{
    static ALittleScriptStatic inst;
    return inst;
}

ALittleScriptStatic::ALittleScriptStatic()
{
    // 基础变量
    std::vector<std::shared_ptr<ABnfGuess>> tmp;
    tmp.resize(0); sIntGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessInt(false)); tmp.push_back(sIntGuess); sPrimitiveGuessListMap[sIntGuess->GetValue()] = tmp; sPrimitiveGuessMap[sIntGuess->GetValue()] = sIntGuess;
    tmp.resize(0); sDoubleGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessDouble(false)); tmp.push_back(sDoubleGuess); sPrimitiveGuessListMap[sDoubleGuess->GetValue()] = tmp; sPrimitiveGuessMap[sDoubleGuess->GetValue()] = sDoubleGuess;
    tmp.resize(0); sStringGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessString(false)); tmp.push_back(sStringGuess); sPrimitiveGuessListMap[sStringGuess->GetValue()] = tmp; sPrimitiveGuessMap[sStringGuess->GetValue()] = sStringGuess;
    tmp.resize(0); sBoolGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessBool(false)); tmp.push_back(sBoolGuess); sPrimitiveGuessListMap[sBoolGuess->GetValue()] = tmp; sPrimitiveGuessMap[sBoolGuess->GetValue()] = sBoolGuess;
    tmp.resize(0); sLongGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessLong(false)); tmp.push_back(sLongGuess); sPrimitiveGuessListMap[sLongGuess->GetValue()] = tmp; sPrimitiveGuessMap[sLongGuess->GetValue()] = sLongGuess;
    tmp.resize(0); sAnyGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessAny(false)); tmp.push_back(sAnyGuess); sPrimitiveGuessListMap[sAnyGuess->GetValue()] = tmp; sPrimitiveGuessMap[sAnyGuess->GetValue()] = sAnyGuess;

    tmp.resize(0); sConstIntGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessInt(true)); tmp.push_back(sConstIntGuess); sPrimitiveGuessListMap[sConstIntGuess->GetValue()] = tmp; sPrimitiveGuessMap[sConstIntGuess->GetValue()] = sConstIntGuess;
    tmp.resize(0); sConstDoubleGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessDouble(true)); tmp.push_back(sConstDoubleGuess); sPrimitiveGuessListMap[sConstDoubleGuess->GetValue()] = tmp; sPrimitiveGuessMap[sConstDoubleGuess->GetValue()] = sConstDoubleGuess;
    tmp.resize(0); sConstStringGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessString(true)); tmp.push_back(sConstStringGuess); sPrimitiveGuessListMap[sConstStringGuess->GetValue()] = tmp; sPrimitiveGuessMap[sConstStringGuess->GetValue()] = sConstStringGuess;
    tmp.resize(0); sConstBoolGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessBool(true)); tmp.push_back(sConstBoolGuess); sPrimitiveGuessListMap[sConstBoolGuess->GetValue()] = tmp; sPrimitiveGuessMap[sConstBoolGuess->GetValue()] = sConstBoolGuess;
    tmp.resize(0); sConstLongGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessLong(true)); tmp.push_back(sConstLongGuess); sPrimitiveGuessListMap[sConstLongGuess->GetValue()] = tmp; sPrimitiveGuessMap[sConstLongGuess->GetValue()] = sConstLongGuess;
    tmp.resize(0); sConstAnyGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessAny(true)); tmp.push_back(sConstAnyGuess); sPrimitiveGuessListMap[sConstAnyGuess->GetValue()] = tmp; sPrimitiveGuessMap[sConstAnyGuess->GetValue()] = sConstAnyGuess;

    // null常量
    sConstNullGuess.push_back(std::shared_ptr<ABnfGuess>(new ALittleScriptGuessConst("null")));

    // 控制关键字
    sCtrlKeyWord.insert("if");
    sCtrlKeyWord.insert("elseif");
    sCtrlKeyWord.insert("else");
    sCtrlKeyWord.insert("do");
    sCtrlKeyWord.insert("while");
    sCtrlKeyWord.insert("return");
    sCtrlKeyWord.insert("break");
    sCtrlKeyWord.insert("continue");
    sCtrlKeyWord.insert("for");
    sCtrlKeyWord.insert("in");
    sCtrlKeyWord.insert("throw");
    sCtrlKeyWord.insert("assert");
}

void ALittleScriptIndex::ClearIndex()
{
    m_guess_type_map.clear();
    m_guess_error_map.clear();
    m_class_data_map.clear();
    m_struct_data_map.clear();
    m_enum_data_map.clear();
    m_all_data_map.clear();
    m_global_access_map.clear();
    m_namespace_access_map.clear();
    m_file_access_map.clear();
}

const std::vector<std::shared_ptr<ABnfGuess>>* ALittleScriptIndex::GetGuessTypeList(std::shared_ptr<ABnfElement> element)
{
    auto it = m_guess_type_map.find(element->GetFile());
    if (it == m_guess_type_map.end()) return nullptr;
    auto sub_it = it->second.find(element);
    if (sub_it == it->second.end()) return nullptr;
    return &sub_it->second;
}

void ALittleScriptIndex::AddGuessTypeList(std::shared_ptr<ABnfElement> element, const std::vector<std::shared_ptr<ABnfGuess>>& guess_type_list)
{
    m_guess_type_map[element->GetFile()][element] = guess_type_list;
    auto it = m_guess_error_map.find(element->GetFile());
    if (it != m_guess_error_map.end()) it->second.erase(element);
}

ABnfGuessError ALittleScriptIndex::GetGuessError(std::shared_ptr<ABnfElement> element)
{
    auto it = m_guess_error_map.find(element->GetFile());
    if (it == m_guess_error_map.end()) return nullptr;
    auto sub_it = it->second.find(element);
    if (sub_it == it->second.end()) return nullptr;
    return sub_it->second;
}

void ALittleScriptIndex::AddGuessError(std::shared_ptr<ABnfElement> element, const ABnfGuessError& error)
{
    m_guess_error_map[element->GetFile()][element] = error;
    auto it = m_guess_type_map.find(element->GetFile());
    if (it != m_guess_type_map.end()) it->second.erase(element);
}

// 删除文件夹
bool ALittleScriptIndex::GetDeepFilePaths(ABnfProject* project, const std::string& cur_path, const std::string& parent_path, std::vector<std::string>& result, std::string& error)
{
    if (project == nullptr) return true;
    if (!ALittleScriptUtility::IsDirExist(cur_path)) return true;

    // 初始化依赖信息
    std::unordered_map<std::string, RelayInfo> relay_map;

    std::vector<std::string> file_list;
    std::vector<std::string> dir_list;
    ALittleScriptUtility::GetNameListInFolder(cur_path, file_list, dir_list);
    for (auto& file : file_list)
    {
        auto full_path = cur_path + "/" + file;

        auto* abnf_file = project->GetFile(full_path);
        if (abnf_file == nullptr || ALittleScriptUtility::IsRegister(abnf_file)) continue;

        auto& relay_info = relay_map[full_path];
        std::set<std::string> relay_set;
        FindDefineRelay(project, full_path, relay_info.relay_set);
        relay_info.path = full_path;
        relay_info.rel_path = parent_path + file;
    }

    // 形成通路
    for (auto& pair : relay_map)
    {
        for (auto& child_path : pair.second.relay_set)
        {
            auto it = relay_map.find(child_path);
            if (it == relay_map.end()) continue;

            it->second.be_used_set.insert(&pair.second);
            pair.second.use_set.insert(&it->second);
        }
    }

    // 都放进列表中，并排序
    std::vector<RelayInfo*> info_list;
    for (auto& pair : relay_map)
        info_list.push_back(&pair.second);
    std::sort(info_list.begin(), info_list.end(), [](RelayInfo* a, RelayInfo* b)->bool { return a->path > b->path; });
    
    // 遍历列表
    while (info_list.size())
    {
        // 用于接收未处理的列表
        std::vector<RelayInfo*> new_info_list;
        // 遍历列表进行处理
        for (auto* relay_info : info_list)
        {
            // 如果已经没有依赖了，那么就添加进result，然后解除依赖关系
            if (relay_info->use_set.empty())
            {
                result.push_back(relay_info->rel_path);
                for (auto* be_used_info : relay_info->be_used_set)
                    be_used_info->use_set.erase(relay_info);
                relay_info->be_used_set.clear();
            }
            else {
                new_info_list.push_back(relay_info);
            }
        }
        // 如果一轮下来没有减少，那么就抛异常
        if (new_info_list.size() == info_list.size())
        {
            std::string content = "";
            for (auto* relayInfo : new_info_list)
            {
                content += relayInfo->rel_path + " -> ";
                for (auto* use_info : relayInfo->use_set)
                    content += use_info->rel_path;
                content += ";";
            }
            error = u8"出现循环引用 " + content;
            return false;
        }

        // 把收集的列表复制给info_list，进行下一轮循环
        info_list = new_info_list;
    }

    for (auto& file : dir_list)
    {
        if (!GetDeepFilePaths(project, cur_path + "/" + file, parent_path + file + "/", result, error))
            return false;
    }

    return true;
}

ABnfGuessError ALittleScriptIndex::FindDefineRelay(ABnfProject* project, const std::string& file_path, std::set<std::string>& result)
{
    if (project == nullptr) return nullptr;
    auto* file = project->GetFile(file_path);
    if (file == nullptr) return nullptr;

    auto dec = ALittleScriptUtility::GetNamespaceDec(file);
    if (dec == nullptr) return nullptr;
    const auto& element_dec_list = dec->GetNamespaceElementDecList();
    for (auto& element_dec : element_dec_list)
    {
        if (element_dec->GetClassDec() != nullptr)
        {
            auto extendsDec = element_dec->GetClassDec()->GetClassExtendsDec();
            if (extendsDec == nullptr) continue;
            ABnfGuessPtr guess;
            auto error = extendsDec->GuessType(guess);
            if (!std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess)) continue;
            auto element = std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess)->GetElement();
            if (element == nullptr) continue;
            if (file_path == element->GetFullPath()) continue;
            result.insert(element->GetFullPath());
        }
    }
    return nullptr;
}

void ALittleScriptIndex::FindNamespaceNameDecList(const std::string& namespace_name, std::unordered_map<std::string, std::shared_ptr<ALittleScriptNamespaceNameDecElement>>& result)
{
    if (namespace_name.empty())
    {
        for (auto& pair : m_all_data_map)
        {
            for (auto& sub_pair : pair.second)
                result[sub_pair.first->GetElementText()] = sub_pair.first;
        }
    }
    else
    {
        auto it = m_all_data_map.find(namespace_name);
        if (it != m_all_data_map.end())
        {
            for (auto& pair : it->second)
                result[pair.first->GetElementText()] = pair.first;
        }
    }
}

void ALittleScriptIndex::FindALittleNameDecList(ABnfElementType type, ABnfFile* file, const std::string& namespace_name, const std::string& name, bool find_in_global, std::vector<std::shared_ptr<ABnfElement>>& result)
{
    // 查本文件的
    auto file_namespace_name = ALittleScriptUtility::GetNamespaceName(file);
    if (file_namespace_name == namespace_name)
    {
        auto it = m_file_access_map.find(file);
        if (it != m_file_access_map.end())
            it->second.FindNameDecList(type, name, result);
    }

    // 查本命名域的
    if (file_namespace_name == namespace_name)
    {
        auto it = m_namespace_access_map.find(namespace_name);
        if (it != m_namespace_access_map.end())
            it->second.FindNameDecList(type, name, result);
    }

    // 查全局下
    if (find_in_global)
    {
        if (type == ABnfElementType::INSTANCE_NAME)
        {
            for (auto& pair : m_global_access_map)
                pair.second.FindNameDecList(type, name, result);
        }
        else
        {
            auto it = m_global_access_map.find(namespace_name);
            if (it != m_global_access_map.end())
                it->second.FindNameDecList(type, name, result);
        }
    }
}

void ALittleScriptIndex::FindGotoALittleNameDecList(ABnfElementType type, ABnfFile* file, const std::string& namespace_name, const std::string& name, bool find_in_global, std::vector<std::shared_ptr<ABnfElement>>& result)
{
    // 查本文件的
    auto file_namespace_name = ALittleScriptUtility::GetNamespaceName(file);
    if (file_namespace_name == namespace_name)
    {
        auto it = m_file_access_map.find(file);
        if (it != m_file_access_map.end())
            it->second.FindNameDecList(type, name, result);
    }

    // 查本命名域的
    auto it = m_namespace_access_map.find(namespace_name);
    if (it != m_namespace_access_map.end())
		it->second.FindNameDecList(type, name, result);

    // 查全局下
    if (find_in_global)
    {
        if (type == ABnfElementType::INSTANCE_NAME)
        {
            for (auto& pair : m_global_access_map)
                pair.second.FindNameDecList(type, name, result);
        }
        else
        {
            auto it = m_global_access_map.find(namespace_name);
            if (it != m_global_access_map.end())
                it->second.FindNameDecList(type, name, result);
        }
    }
}

ABnfGuessError ALittleScriptIndex::FindALittleStructGuessList(const std::string& namespace_name, const std::string& name, std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = FindALittleNameDec(ABnfElementType::STRUCT_NAME, nullptr, namespace_name, name, true);
    if (std::dynamic_pointer_cast<ALittleScriptStructNameDecElement>(element))
        return element->GuessTypes(guess_list);
    guess_list.clear();
    return nullptr;
}

ABnfGuessError ALittleScriptIndex::FindALittleStructGuess(const std::string& namespace_name, const std::string& name, ABnfGuessPtr& guess)
{
    auto element = FindALittleNameDec(ABnfElementType::STRUCT_NAME, nullptr, namespace_name, name, true);
    if (std::dynamic_pointer_cast<ALittleScriptStructNameDecElement>(element))
        return element->GuessType(guess);
    guess = nullptr;
    return nullptr;
}

ABnfGuessError ALittleScriptIndex::FindALittleClassGuessList(const std::string& namespace_name, const std::string& name, std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = FindALittleNameDec(ABnfElementType::CLASS_NAME, nullptr, namespace_name, name, true);
    if (std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(element))
        return element->GuessTypes(guess_list);
    guess_list.clear();
    return nullptr;
}

void ALittleScriptIndex::FindClassAttrList(std::shared_ptr<ALittleScriptClassDecElement> dec, int access_level, ClassAttrType attr_type, const std::string& name, std::vector<std::shared_ptr<ABnfElement>>& result)
{
    auto name_dec = dec->GetClassNameDec();
    if (name_dec == nullptr) return;

    auto it = m_class_data_map.find(dec->GetFile());
    if (it == m_class_data_map.end()) return;
    auto sub_it = it->second.find(name_dec->GetElementText());
    if (sub_it == it->second.end()) return;

    sub_it->second.FindClassAttrList(access_level, attr_type, name, result);
}

std::shared_ptr<ABnfElement> ALittleScriptIndex::FindClassAttr(std::shared_ptr<ALittleScriptClassDecElement> dec, int access_level, ClassAttrType attr_type, const std::string& name)
{
    std::vector<std::shared_ptr<ABnfElement>> result;
    FindClassAttrList(dec, access_level, attr_type, name, result);
    if (result.empty()) return nullptr;
    return result[0];
}

// 添加类索引数据
void ALittleScriptIndex::AddClassData(std::shared_ptr<ALittleScriptClassDecElement> dec)
{
    auto name_dec = dec->GetClassNameDec();
    if (name_dec == nullptr) return;

    auto& map = m_class_data_map[dec->GetFile()];
    auto& class_data = map[name_dec->GetElementText()] = ALittleScriptClassData();

    auto template_dec = dec->GetTemplateDec();
    if (template_dec != nullptr)
        class_data.AddClassChildDec(template_dec, nullptr, nullptr);

    auto body_dec = dec->GetClassBodyDec();
    if (body_dec == nullptr) return;

    const auto& child_list = body_dec->GetChilds();
    for (size_t i = 0; i < child_list.size(); ++i)
    {
        ABnfElementPtr pre_child;
        if (i > 0) pre_child = child_list[i - 1];
        ABnfElementPtr next_child;
        if (i < child_list.size() - 1) next_child = child_list[i + 1];
        class_data.AddClassChildDec(child_list[i], pre_child, next_child);
    }
}

// 获取类索引数据
const ALittleScriptClassData* ALittleScriptIndex::GetClassData(std::shared_ptr<ALittleScriptClassDecElement> dec)
{
    auto name_dec = dec->GetClassNameDec();
    if (name_dec == nullptr) return nullptr;
    auto it = m_class_data_map.find(dec->GetFile());
    if (it == m_class_data_map.end()) return nullptr;
    auto sub_it = it->second.find(name_dec->GetElementText());
    if (sub_it == it->second.end()) return nullptr;
    return &sub_it->second;
}

// 添加结构体数据
void ALittleScriptIndex::AddStructData(std::shared_ptr<ALittleScriptStructDecElement> dec)
{
    auto name_dec = dec->GetStructNameDec();
    if (name_dec == nullptr) return;

    auto& map = m_struct_data_map[dec->GetFile()];
    auto& struct_data = map[name_dec->GetElementText()] = ALittleScriptStructData();

    auto body_dec = dec->GetStructBodyDec();
    if (body_dec == nullptr) return;

    const auto& child_list = body_dec->GetChilds();
    for (size_t i = 0; i < child_list.size(); ++i)
    {
        ABnfElementPtr next_child;
        if (i < child_list.size() - 1) next_child = child_list[i + 1];
        struct_data.AddVarDec(child_list[i], next_child);
    }
}

// 获取结构体数据
const ALittleScriptStructData* ALittleScriptIndex::GetStructData(std::shared_ptr<ALittleScriptStructDecElement> dec)
{
    auto name_dec = dec->GetStructNameDec();
    if (name_dec == nullptr) return nullptr;
    auto it = m_struct_data_map.find(dec->GetFile());
    if (it == m_struct_data_map.end()) return nullptr;
    auto sub_it = it->second.find(name_dec->GetElementText());
    if (sub_it == it->second.end()) return nullptr;
    return &sub_it->second;
}

// 添加枚举数据
void ALittleScriptIndex::AddEnumData(std::shared_ptr<ALittleScriptEnumDecElement> dec)
{
    auto name_dec = dec->GetEnumNameDec();
    if (name_dec == nullptr) return;

    auto& map = m_enum_data_map[dec->GetFile()];
    auto& enum_data = map[name_dec->GetElementText()] = ALittleScriptEnumData();

    auto body_dec = dec->GetEnumBodyDec();
    if (body_dec == nullptr) return;

    const auto& child_list = body_dec->GetChilds();
    for (size_t i = 0; i < child_list.size(); ++i)
    {
        ABnfElementPtr next_child;
        if (i < child_list.size() - 1) next_child = child_list[i + 1];
        enum_data.AddVarDec(child_list[i], next_child);
    }
}

// 获取枚举数据
const ALittleScriptEnumData* ALittleScriptIndex::GetEnumData(std::shared_ptr<ALittleScriptEnumDecElement> dec)
{
    auto name_dec = dec->GetEnumNameDec();
    if (name_dec == nullptr) return nullptr;
    auto it = m_enum_data_map.find(dec->GetFile());
    if (it == m_enum_data_map.end()) return nullptr;
    auto sub_it = it->second.find(name_dec->GetElementText());
    if (sub_it == it->second.end()) return nullptr;
    return &sub_it->second;
}

void ALittleScriptIndex::AddRoot(std::shared_ptr<ALittleScriptRootElement> root)
{
    // 清除标记
    root->GetFile()->ClearGuessType();
    m_guess_type_map.erase(root->GetFile());
    m_guess_error_map.erase(root->GetFile());
    m_class_data_map.erase(root->GetFile());
    m_struct_data_map.erase(root->GetFile());
    m_enum_data_map.erase(root->GetFile());

    auto namespace_dec = root->GetNamespaceDec();
    if (namespace_dec == nullptr) return;
    auto namespace_name_dec = namespace_dec->GetNamespaceNameDec();
    if (namespace_name_dec == nullptr) return;

    // 获取命名域名
    const auto& name = namespace_name_dec->GetElementText();

    auto& all_access_data = m_all_data_map[name][namespace_name_dec] = ALittleScriptAccessData();
    auto& global_access_data = m_global_access_map[name];
    auto& namespace_access_data = m_namespace_access_map[name];
    auto& file_access_data = m_file_access_map[root->GetFile()];

    const auto& child_list = namespace_dec->GetChilds();
    for (size_t i = 0; i < child_list.size(); ++i)
    {
        auto child = child_list[i];
        ABnfElementPtr pre_child;
        if (i > 0) pre_child = child_list[i - 1];
        ABnfElementPtr next_child;
        if (i < child_list.size() - 1) next_child = child_list[i + 1];

        auto namespace_element = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(child);
        if (namespace_element) {
            // 添加类
            if (namespace_element->GetClassDec() != nullptr)
            {
                auto class_dec = namespace_element->GetClassDec();
                auto name_dec = class_dec->GetClassNameDec();
                if (name_dec == nullptr) continue;

                // 如果pre_dec是注释，那么就去描述
                if (std::dynamic_pointer_cast<ALittleScriptBlockCommentElement>(pre_child) || std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(pre_child))
                    name_dec->SetDescriptor(pre_child->GetElementText());

                // 添加类数据
                AddClassData(class_dec);
                // 添加到全权限
                all_access_data.AddNameDec(name_dec);
                // 按访问权限划分
                auto access_type = ALittleScriptUtility::CalcAccessType(namespace_element->GetModifierList());
                if (access_type == ClassAccessType::PUBLIC)
                    global_access_data.AddNameDec(name_dec);
                else if (access_type == ClassAccessType::PROTECTED)
                    namespace_access_data.AddNameDec(name_dec);
                else if (access_type == ClassAccessType::PRIVATE)
                    file_access_data.AddNameDec(name_dec);
            }
            // 添加枚举
            else if (namespace_element->GetEnumDec() != nullptr)
            {
                auto enum_dec = namespace_element->GetEnumDec();
                auto name_dec = enum_dec->GetEnumNameDec();
                if (name_dec == nullptr) continue;

                // 如果pre_dec是注释，那么就去描述
                if (std::dynamic_pointer_cast<ALittleScriptBlockCommentElement>(pre_child) || std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(pre_child))
                    name_dec->SetDescriptor(pre_child->GetElementText());

                //  添加枚举数据
                AddEnumData(enum_dec);
                // 添加到全权限
                all_access_data.AddNameDec(name_dec);
                // 按访问权限划分
                auto access_type = ALittleScriptUtility::CalcAccessType(namespace_element->GetModifierList());
                if (access_type == ClassAccessType::PUBLIC)
                    global_access_data.AddNameDec(name_dec);
                else if (access_type == ClassAccessType::PROTECTED)
                    namespace_access_data.AddNameDec(name_dec);
                else if (access_type == ClassAccessType::PRIVATE)
                    file_access_data.AddNameDec(name_dec);
            }
            // 添加结构体
            else if (namespace_element->GetStructDec() != nullptr)
            {
                auto struct_dec = namespace_element->GetStructDec();
                auto name_dec = struct_dec->GetStructNameDec();
                if (name_dec == nullptr) continue;

                // 如果pre_dec是注释，那么就去描述
                if (std::dynamic_pointer_cast<ALittleScriptBlockCommentElement>(pre_child) || std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(pre_child))
                    name_dec->SetDescriptor(pre_child->GetElementText());


                //  添加结构体数据
                AddStructData(struct_dec);
                // 添加到全权限
                all_access_data.AddNameDec(name_dec);
                // 按访问权限划分
                auto access_type = ALittleScriptUtility::CalcAccessType(namespace_element->GetModifierList());
                if (access_type == ClassAccessType::PUBLIC)
                    global_access_data.AddNameDec(name_dec);
                else if (access_type == ClassAccessType::PROTECTED)
                    namespace_access_data.AddNameDec(name_dec);
                else if (access_type == ClassAccessType::PRIVATE)
                    file_access_data.AddNameDec(name_dec);
            }
            // 添加全局函数
            else if (namespace_element->GetGlobalMethodDec() != nullptr)
            {
                auto method_dec = namespace_element->GetGlobalMethodDec();
                auto name_dec = method_dec->GetMethodNameDec();
                if (name_dec == nullptr) continue;

                // 如果pre_dec是注释，那么就去描述
                if (std::dynamic_pointer_cast<ALittleScriptBlockCommentElement>(pre_child) || std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(pre_child))
                    name_dec->SetDescriptor(pre_child->GetElementText());


                // 添加到全权限
                all_access_data.AddNameDec(name_dec);
                // 按访问权限划分
                auto access_type = ALittleScriptUtility::CalcAccessType(namespace_element->GetModifierList());
                if (access_type == ClassAccessType::PUBLIC)
                    global_access_data.AddNameDec(name_dec);
                else if (access_type == ClassAccessType::PROTECTED)
                    namespace_access_data.AddNameDec(name_dec);
                else if (access_type == ClassAccessType::PRIVATE)
                    file_access_data.AddNameDec(name_dec);
            }
            // 添加单例
            else if (namespace_element->GetInstanceDec() != nullptr)
            {
                auto instance_dec = namespace_element->GetInstanceDec();
                auto access_type = ALittleScriptUtility::CalcAccessType(namespace_element->GetModifierList());

                auto var_assign_expr = instance_dec->GetVarAssignExpr();
                if (var_assign_expr == nullptr) continue;
                const auto& var_assign_dec_list = var_assign_expr->GetVarAssignDecList();
                for (auto& var_assign_dec : var_assign_dec_list)
                {
                    auto name_dec = var_assign_dec->GetVarAssignNameDec();
                    if (name_dec == nullptr) continue;

                    // 如果pre_dec是注释，那么就去描述
                    if (std::dynamic_pointer_cast<ALittleScriptBlockCommentElement>(pre_child) || std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(pre_child))
                        name_dec->SetDescriptor(pre_child->GetElementText());

                    // 添加到全权限
                    all_access_data.AddNameDec(name_dec);
                    // 按访问权限划分
                    if (access_type == ClassAccessType::PUBLIC)
                        global_access_data.AddNameDec(name_dec);
                    else if (access_type == ClassAccessType::PROTECTED)
                        namespace_access_data.AddNameDec(name_dec);
                    else if (access_type == ClassAccessType::PRIVATE)
                        file_access_data.AddNameDec(name_dec);
                }
            }
            // 添加using
            else if (namespace_element->GetUsingDec() != nullptr)
            {
                auto using_dec = namespace_element->GetUsingDec();
                auto name_dec = using_dec->GetUsingNameDec();
                if (name_dec == nullptr) continue;

                // 如果pre_dec是注释，那么就去描述
                if (std::dynamic_pointer_cast<ALittleScriptBlockCommentElement>(pre_child) || std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(pre_child))
                    name_dec->SetDescriptor(pre_child->GetElementText());

                // 添加到全权限
                all_access_data.AddNameDec(name_dec);
                // 按访问权限划分
                auto access_type = ALittleScriptUtility::CalcAccessType(namespace_element->GetModifierList());
                if (access_type == ClassAccessType::PUBLIC)
                    global_access_data.AddNameDec(name_dec);
                else if (access_type == ClassAccessType::PROTECTED)
                    namespace_access_data.AddNameDec(name_dec);
                else if (access_type == ClassAccessType::PRIVATE)
                    file_access_data.AddNameDec(name_dec);
            }
        }
    }
}

// 移除命名域
void ALittleScriptIndex::RemoveRoot(std::shared_ptr<ALittleScriptRootElement> root)
{
    // 清除标记
    root->GetFile()->ClearGuessType();
    m_guess_type_map.erase(root->GetFile());
    m_guess_error_map.erase(root->GetFile());
    m_class_data_map.erase(root->GetFile());
    m_struct_data_map.erase(root->GetFile());
    m_enum_data_map.erase(root->GetFile());

    auto namespace_dec = root->GetNamespaceDec();
    if (namespace_dec == nullptr) return;
    auto namespace_name_dec = namespace_dec->GetNamespaceNameDec();
    if (namespace_name_dec == nullptr) return;

    const auto& name = namespace_name_dec->GetElementText();

    auto it = m_all_data_map.find(name);
    if (it == m_all_data_map.end()) return;
    auto sub_it = it->second.find(namespace_name_dec);
    if (sub_it == it->second.end()) return;

    auto global_access_it = m_global_access_map.find(name);
    auto namespace_access_it = m_namespace_access_map.find(name);
    auto file_access_it = m_file_access_map.find(root->GetFile());

    for (auto& pair : sub_it->second.GetElementMap())
    {
        for (auto& element_pair : pair.second)
        {
            for (auto& name_dec : element_pair.second)
            {
                if (global_access_it != m_global_access_map.end()) global_access_it->second.RemoveNameDec(name_dec);
                if (namespace_access_it != m_namespace_access_map.end()) namespace_access_it->second.RemoveNameDec(name_dec);
                if (file_access_it != m_file_access_map.end()) file_access_it->second.RemoveNameDec(name_dec);
            }
        }
    }

    it->second.erase(sub_it);
    if (it->second.empty()) m_all_data_map.erase(it);
}

void ALittleScriptIndex::RemoveGuess(ABnfFile* file)
{
    if (file == nullptr) return;

    file->ClearGuessType();
    m_guess_type_map.erase(file);
    m_guess_error_map.erase(file);
}
