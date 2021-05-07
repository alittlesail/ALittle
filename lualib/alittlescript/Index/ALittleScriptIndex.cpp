
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
#include "../Generate/ALittleScriptClassBodyDecElement.h"
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
#include "../Generate/ALittleScriptTemplateDecElement.h"

#include "../Guess/ALittleScriptGuessClass.h"
#include "../Guess/ALittleScriptGuessPrimitive.h"
#include "../Guess/ALittleScriptGuessConst.h"
#include "../Guess/ALittleScriptGuessList.h"

ALittleScriptStatic& ALittleScriptStatic::Inst()
{
    static ALittleScriptStatic inst;
    return inst;
}

ALittleScriptStatic::ALittleScriptStatic()
{
    // ��������
    std::vector<std::shared_ptr<ABnfGuess>> tmp;
    tmp.resize(0); sIntGuess = std::make_shared<ALittleScriptGuessInt>(false); tmp.push_back(sIntGuess); sPrimitiveGuessListMap[sIntGuess->GetValue()] = tmp; sPrimitiveGuessMap[sIntGuess->GetValue()] = sIntGuess;
    tmp.resize(0); sDoubleGuess = std::make_shared<ALittleScriptGuessDouble>(false); tmp.push_back(sDoubleGuess); sPrimitiveGuessListMap[sDoubleGuess->GetValue()] = tmp; sPrimitiveGuessMap[sDoubleGuess->GetValue()] = sDoubleGuess;
    tmp.resize(0); sStringGuess = std::make_shared<ALittleScriptGuessString>(false); tmp.push_back(sStringGuess); sPrimitiveGuessListMap[sStringGuess->GetValue()] = tmp; sPrimitiveGuessMap[sStringGuess->GetValue()] = sStringGuess;
    tmp.resize(0); sBoolGuess = std::make_shared<ALittleScriptGuessBool>(false); tmp.push_back(sBoolGuess); sPrimitiveGuessListMap[sBoolGuess->GetValue()] = tmp; sPrimitiveGuessMap[sBoolGuess->GetValue()] = sBoolGuess;
    tmp.resize(0); sLongGuess = std::make_shared<ALittleScriptGuessLong>(false); tmp.push_back(sLongGuess); sPrimitiveGuessListMap[sLongGuess->GetValue()] = tmp; sPrimitiveGuessMap[sLongGuess->GetValue()] = sLongGuess;
    tmp.resize(0); sAnyGuess = std::make_shared<ALittleScriptGuessAny>(false); tmp.push_back(sAnyGuess); sPrimitiveGuessListMap[sAnyGuess->GetValue()] = tmp; sPrimitiveGuessMap[sAnyGuess->GetValue()] = sAnyGuess;

    tmp.resize(0); sConstIntGuess = std::make_shared<ALittleScriptGuessInt>(true); tmp.push_back(sConstIntGuess); sPrimitiveGuessListMap[sConstIntGuess->GetValue()] = tmp; sPrimitiveGuessMap[sConstIntGuess->GetValue()] = sConstIntGuess;
    tmp.resize(0); sConstDoubleGuess = std::make_shared<ALittleScriptGuessDouble>(true); tmp.push_back(sConstDoubleGuess); sPrimitiveGuessListMap[sConstDoubleGuess->GetValue()] = tmp; sPrimitiveGuessMap[sConstDoubleGuess->GetValue()] = sConstDoubleGuess;
    tmp.resize(0); sConstStringGuess = std::make_shared<ALittleScriptGuessString>(true); tmp.push_back(sConstStringGuess); sPrimitiveGuessListMap[sConstStringGuess->GetValue()] = tmp; sPrimitiveGuessMap[sConstStringGuess->GetValue()] = sConstStringGuess;
    tmp.resize(0); sConstBoolGuess = std::make_shared<ALittleScriptGuessBool>(true); tmp.push_back(sConstBoolGuess); sPrimitiveGuessListMap[sConstBoolGuess->GetValue()] = tmp; sPrimitiveGuessMap[sConstBoolGuess->GetValue()] = sConstBoolGuess;
    tmp.resize(0); sConstLongGuess = std::make_shared<ALittleScriptGuessLong>(true); tmp.push_back(sConstLongGuess); sPrimitiveGuessListMap[sConstLongGuess->GetValue()] = tmp; sPrimitiveGuessMap[sConstLongGuess->GetValue()] = sConstLongGuess;
    tmp.resize(0); sConstAnyGuess = std::make_shared<ALittleScriptGuessAny>(true); tmp.push_back(sConstAnyGuess); sPrimitiveGuessListMap[sConstAnyGuess->GetValue()] = tmp; sPrimitiveGuessMap[sConstAnyGuess->GetValue()] = sConstAnyGuess;

    sStringListGuess = std::make_shared<ALittleScriptGuessList>(sStringGuess, false, false);
    sStringListGuess->UpdateValue();
    sStringListListGuess = std::make_shared<ALittleScriptGuessList>(sStringListGuess, false, false);
    sStringListListGuess->UpdateValue();

    // null����
    sConstNullGuess.push_back(std::make_shared<ALittleScriptGuessConst>("null"));

    // ���ƹؼ���
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

const std::vector<std::shared_ptr<ABnfGuess>>* ALittleScriptIndex::GetGuessTypeList(const std::shared_ptr<ABnfElement>& element)
{
    auto it = m_guess_type_map.find(element->GetFile());
    if (it == m_guess_type_map.end()) return nullptr;
    auto sub_it = it->second.find(element);
    if (sub_it == it->second.end()) return nullptr;
    return &sub_it->second;
}

void ALittleScriptIndex::AddGuessTypeList(const std::shared_ptr<ABnfElement>& element, const std::vector<std::shared_ptr<ABnfGuess>>& guess_type_list)
{
    m_guess_type_map[element->GetFile()][element] = guess_type_list;
    auto it = m_guess_error_map.find(element->GetFile());
    if (it != m_guess_error_map.end()) it->second.erase(element);
}

ABnfGuessError ALittleScriptIndex::GetGuessError(const std::shared_ptr<ABnfElement>& element)
{
    auto it = m_guess_error_map.find(element->GetFile());
    if (it == m_guess_error_map.end()) return nullptr;
    const auto sub_it = it->second.find(element);
    if (sub_it == it->second.end()) return nullptr;
    return sub_it->second;
}

void ALittleScriptIndex::AddGuessError(const std::shared_ptr<ABnfElement>& element, const ABnfGuessError& error)
{
    m_guess_error_map[element->GetFile()][element] = error;
    auto it = m_guess_type_map.find(element->GetFile());
    if (it != m_guess_type_map.end()) it->second.erase(element);
}

bool ALittleScriptIndex::GetDeepFilePaths(ABnfProject* project, const std::string& cur_path, const std::string& parent_path, std::map<std::string, RelayInfo>& rely_map, std::string& error)
{
    if (!GetDeepFilePathsImpl(project, cur_path, parent_path, rely_map, error)) return false;

    // �γ�ͨ·
    for (auto& pair : rely_map)
    {
        for (const auto& child_path : pair.second.rely_set)
        {
            auto it = rely_map.find(child_path);
            if (it == rely_map.end()) continue;

            it->second.be_used_set.insert(&pair.second);
            pair.second.use_set.insert(&it->second);
        }
    }

    return true;
}

bool ALittleScriptIndex::GetDeepFilePathsImpl(ABnfProject* project, const std::string& cur_path, const std::string& parent_path, std::map<std::string, RelayInfo>& rely_map, std::string& error)
{
    if (project == nullptr) return true;
    if (!ALittleScriptUtility::IsDirExist(cur_path)) return true;

    std::vector<std::string> file_list;
    std::vector<std::string> dir_list;
    ALittleScriptUtility::GetNameListInFolder(cur_path, file_list, dir_list);
    for (auto& file : file_list)
    {
        auto full_path = cur_path;
        full_path += "/";
        full_path += file;

        auto* abnf_file = project->GetFile(full_path);
        if (abnf_file == nullptr || ALittleScriptUtility::IsRegister(abnf_file)) continue;

        auto& relay_info = rely_map[full_path];
        FindDefineRelay(project, full_path, relay_info.rely_set);
        relay_info.full_path = full_path;
        relay_info.rel_path = parent_path + ALittleScriptUtility::ChangeFileExtByPath(file, "");
    }

    for (auto& file : dir_list)
    {
        auto full_path = cur_path;
        full_path += "/";
        full_path += file;

        if (!GetDeepFilePaths(project, full_path, parent_path + file + "/", rely_map, error))
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
    for (const auto& element_dec : element_dec_list)
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
    // �鱾�ļ���
    const auto file_namespace_name = ALittleScriptUtility::GetNamespaceName(file);
    if (file_namespace_name == namespace_name)
    {
        auto it = m_file_access_map.find(file);
        if (it != m_file_access_map.end())
            it->second.FindNameDecList(type, name, result);
    }

    // �鱾�������
    if (file_namespace_name == namespace_name)
    {
        auto it = m_namespace_access_map.find(namespace_name);
        if (it != m_namespace_access_map.end())
            it->second.FindNameDecList(type, name, result);
    }

    // ��ȫ����
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
    // �鱾�ļ���
    const auto file_namespace_name = ALittleScriptUtility::GetNamespaceName(file);
    if (file_namespace_name == namespace_name)
    {
        auto it = m_file_access_map.find(file);
        if (it != m_file_access_map.end())
            it->second.FindNameDecList(type, name, result);
    }

    // �鱾�������
    auto it = m_namespace_access_map.find(namespace_name);
    if (it != m_namespace_access_map.end())
		it->second.FindNameDecList(type, name, result);

    // ��ȫ����
    if (find_in_global)
    {
        if (type == ABnfElementType::INSTANCE_NAME)
        {
            for (auto& pair : m_global_access_map)
                pair.second.FindNameDecList(type, name, result);
        }
        else
        {
            it = m_global_access_map.find(namespace_name);
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

void ALittleScriptIndex::FindClassAttrList(const std::shared_ptr<ALittleScriptClassDecElement>& dec, int access_level, ClassAttrType attr_type, const std::string& name, std::vector<std::shared_ptr<ABnfElement>>& result)
{
    auto name_dec = dec->GetClassNameDec();
    if (name_dec == nullptr) return;

    auto it = m_class_data_map.find(dec->GetFile());
    if (it == m_class_data_map.end()) return;
    const auto sub_it = it->second.find(name_dec->GetElementText());
    if (sub_it == it->second.end()) return;

    sub_it->second.FindClassAttrList(access_level, attr_type, name, result);
}

std::shared_ptr<ABnfElement> ALittleScriptIndex::FindClassAttr(const std::shared_ptr<ALittleScriptClassDecElement>& dec, int access_level, ClassAttrType attr_type, const std::string& name)
{
    std::vector<std::shared_ptr<ABnfElement>> result;
    FindClassAttrList(dec, access_level, attr_type, name, result);
    if (result.empty()) return nullptr;
    return result[0];
}

// �������������
void ALittleScriptIndex::AddClassData(const std::shared_ptr<ALittleScriptClassDecElement>& dec)
{
    auto name_dec = dec->GetClassNameDec();
    if (name_dec == nullptr) return;

    auto& map = m_class_data_map[dec->GetFile()];
    auto& class_data = map[name_dec->GetElementText()] = ALittleScriptClassData();

    const auto template_dec = dec->GetTemplateDec();
    if (template_dec != nullptr)
        class_data.AddClassChildDec(template_dec, nullptr, nullptr);

    const auto body_dec = dec->GetClassBodyDec();
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

// ��ȡ����������
const ALittleScriptClassData* ALittleScriptIndex::GetClassData(const std::shared_ptr<ALittleScriptClassDecElement>& dec)
{
    auto name_dec = dec->GetClassNameDec();
    if (name_dec == nullptr) return nullptr;
    auto it = m_class_data_map.find(dec->GetFile());
    if (it == m_class_data_map.end()) return nullptr;
    auto sub_it = it->second.find(name_dec->GetElementText());
    if (sub_it == it->second.end()) return nullptr;
    return &sub_it->second;
}

// ��ӽṹ������
void ALittleScriptIndex::AddStructData(const std::shared_ptr<ALittleScriptStructDecElement>& dec)
{
    auto name_dec = dec->GetStructNameDec();
    if (name_dec == nullptr) return;

    auto& map = m_struct_data_map[dec->GetFile()];
    auto& struct_data = map[name_dec->GetElementText()] = ALittleScriptStructData();

    const auto body_dec = dec->GetStructBodyDec();
    if (body_dec == nullptr) return;

    const auto& child_list = body_dec->GetChilds();
    for (size_t i = 0; i < child_list.size(); ++i)
    {
        ABnfElementPtr next_child;
        if (i < child_list.size() - 1) next_child = child_list[i + 1];
        struct_data.AddVarDec(child_list[i], next_child);
    }
}

// ��ȡ�ṹ������
const ALittleScriptStructData* ALittleScriptIndex::GetStructData(const std::shared_ptr<ALittleScriptStructDecElement>& dec)
{
    auto name_dec = dec->GetStructNameDec();
    if (name_dec == nullptr) return nullptr;
    auto it = m_struct_data_map.find(dec->GetFile());
    if (it == m_struct_data_map.end()) return nullptr;
    auto sub_it = it->second.find(name_dec->GetElementText());
    if (sub_it == it->second.end()) return nullptr;
    return &sub_it->second;
}

// ���ö������
void ALittleScriptIndex::AddEnumData(const std::shared_ptr<ALittleScriptEnumDecElement>& dec)
{
    auto name_dec = dec->GetEnumNameDec();
    if (name_dec == nullptr) return;

    auto& map = m_enum_data_map[dec->GetFile()];
    auto& enum_data = map[name_dec->GetElementText()] = ALittleScriptEnumData();

    const auto body_dec = dec->GetEnumBodyDec();
    if (body_dec == nullptr) return;

    const auto& child_list = body_dec->GetChilds();
    for (size_t i = 0; i < child_list.size(); ++i)
    {
        ABnfElementPtr next_child;
        if (i < child_list.size() - 1) next_child = child_list[i + 1];
        enum_data.AddVarDec(child_list[i], next_child);
    }
}

// ��ȡö������
const ALittleScriptEnumData* ALittleScriptIndex::GetEnumData(const std::shared_ptr<ALittleScriptEnumDecElement>& dec)
{
    auto name_dec = dec->GetEnumNameDec();
    if (name_dec == nullptr) return nullptr;
    auto it = m_enum_data_map.find(dec->GetFile());
    if (it == m_enum_data_map.end()) return nullptr;
    auto sub_it = it->second.find(name_dec->GetElementText());
    if (sub_it == it->second.end()) return nullptr;
    return &sub_it->second;
}

void ALittleScriptIndex::AddRoot(const std::shared_ptr<ALittleScriptRootElement>& root)
{
    // ������
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

    // ��ȡ��������
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

        auto namespace_element = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(child);
        if (namespace_element) {
            // �����
            if (namespace_element->GetClassDec() != nullptr)
            {
                auto class_dec = namespace_element->GetClassDec();
                auto name_dec = class_dec->GetClassNameDec();
                if (name_dec == nullptr) continue;

                // ���pre_dec��ע�ͣ���ô��ȥ����
                if (std::dynamic_pointer_cast<ALittleScriptBlockCommentElement>(pre_child) || std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(pre_child))
                    name_dec->SetDescriptor(pre_child->GetElementText());

                // ���������
                AddClassData(class_dec);
                // ��ӵ�ȫȨ��
                all_access_data.AddNameDec(name_dec);
                // ������Ȩ�޻���
                const auto access_type = ALittleScriptUtility::CalcAccessType(namespace_element->GetModifierList());
                if (access_type == ClassAccessType::PUBLIC)
                    global_access_data.AddNameDec(name_dec);
                else if (access_type == ClassAccessType::PROTECTED)
                    namespace_access_data.AddNameDec(name_dec);
                else if (access_type == ClassAccessType::PRIVATE)
                    file_access_data.AddNameDec(name_dec);
            }
            // ���ö��
            else if (namespace_element->GetEnumDec() != nullptr)
            {
                auto enum_dec = namespace_element->GetEnumDec();
                auto name_dec = enum_dec->GetEnumNameDec();
                if (name_dec == nullptr) continue;

                // ���pre_dec��ע�ͣ���ô��ȥ����
                if (std::dynamic_pointer_cast<ALittleScriptBlockCommentElement>(pre_child) || std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(pre_child))
                    name_dec->SetDescriptor(pre_child->GetElementText());

                //  ���ö������
                AddEnumData(enum_dec);
                // ��ӵ�ȫȨ��
                all_access_data.AddNameDec(name_dec);
                // ������Ȩ�޻���
                const auto access_type = ALittleScriptUtility::CalcAccessType(namespace_element->GetModifierList());
                if (access_type == ClassAccessType::PUBLIC)
                    global_access_data.AddNameDec(name_dec);
                else if (access_type == ClassAccessType::PROTECTED)
                    namespace_access_data.AddNameDec(name_dec);
                else if (access_type == ClassAccessType::PRIVATE)
                    file_access_data.AddNameDec(name_dec);
            }
            // ��ӽṹ��
            else if (namespace_element->GetStructDec() != nullptr)
            {
                auto struct_dec = namespace_element->GetStructDec();
                auto name_dec = struct_dec->GetStructNameDec();
                if (name_dec == nullptr) continue;

                // ���pre_dec��ע�ͣ���ô��ȥ����
                if (std::dynamic_pointer_cast<ALittleScriptBlockCommentElement>(pre_child) || std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(pre_child))
                    name_dec->SetDescriptor(pre_child->GetElementText());


                //  ��ӽṹ������
                AddStructData(struct_dec);
                // ��ӵ�ȫȨ��
                all_access_data.AddNameDec(name_dec);
                // ������Ȩ�޻���
                const auto access_type = ALittleScriptUtility::CalcAccessType(namespace_element->GetModifierList());
                if (access_type == ClassAccessType::PUBLIC)
                    global_access_data.AddNameDec(name_dec);
                else if (access_type == ClassAccessType::PROTECTED)
                    namespace_access_data.AddNameDec(name_dec);
                else if (access_type == ClassAccessType::PRIVATE)
                    file_access_data.AddNameDec(name_dec);
            }
            // ���ȫ�ֺ���
            else if (namespace_element->GetGlobalMethodDec() != nullptr)
            {
                auto method_dec = namespace_element->GetGlobalMethodDec();
                auto name_dec = method_dec->GetMethodNameDec();
                if (name_dec == nullptr) continue;

                // ���pre_dec��ע�ͣ���ô��ȥ����
                if (std::dynamic_pointer_cast<ALittleScriptBlockCommentElement>(pre_child) || std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(pre_child))
                    name_dec->SetDescriptor(pre_child->GetElementText());


                // ��ӵ�ȫȨ��
                all_access_data.AddNameDec(name_dec);
                // ������Ȩ�޻���
                const auto access_type = ALittleScriptUtility::CalcAccessType(namespace_element->GetModifierList());
                if (access_type == ClassAccessType::PUBLIC)
                    global_access_data.AddNameDec(name_dec);
                else if (access_type == ClassAccessType::PROTECTED)
                    namespace_access_data.AddNameDec(name_dec);
                else if (access_type == ClassAccessType::PRIVATE)
                    file_access_data.AddNameDec(name_dec);
            }
            // ��ӵ���
            else if (namespace_element->GetInstanceDec() != nullptr)
            {
                auto instance_dec = namespace_element->GetInstanceDec();
                const auto access_type = ALittleScriptUtility::CalcAccessType(namespace_element->GetModifierList());

                auto var_assign_expr = instance_dec->GetVarAssignExpr();
                if (var_assign_expr == nullptr) continue;
                const auto& var_assign_dec_list = var_assign_expr->GetVarAssignDecList();
                for (const auto& var_assign_dec : var_assign_dec_list)
                {
                    auto name_dec = var_assign_dec->GetVarAssignNameDec();
                    if (name_dec == nullptr) continue;

                    // ���pre_dec��ע�ͣ���ô��ȥ����
                    if (std::dynamic_pointer_cast<ALittleScriptBlockCommentElement>(pre_child) || std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(pre_child))
                        name_dec->SetDescriptor(pre_child->GetElementText());

                    // ��ӵ�ȫȨ��
                    all_access_data.AddNameDec(name_dec);
                    // ������Ȩ�޻���
                    if (access_type == ClassAccessType::PUBLIC)
                        global_access_data.AddNameDec(name_dec);
                    else if (access_type == ClassAccessType::PROTECTED)
                        namespace_access_data.AddNameDec(name_dec);
                    else if (access_type == ClassAccessType::PRIVATE)
                        file_access_data.AddNameDec(name_dec);
                }
            }
            // ���using
            else if (namespace_element->GetUsingDec() != nullptr)
            {
                auto using_dec = namespace_element->GetUsingDec();
                auto name_dec = using_dec->GetUsingNameDec();
                if (name_dec == nullptr) continue;

                // ���pre_dec��ע�ͣ���ô��ȥ����
                if (std::dynamic_pointer_cast<ALittleScriptBlockCommentElement>(pre_child) || std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(pre_child))
                    name_dec->SetDescriptor(pre_child->GetElementText());

                // ��ӵ�ȫȨ��
                all_access_data.AddNameDec(name_dec);
                // ������Ȩ�޻���
                const auto access_type = ALittleScriptUtility::CalcAccessType(namespace_element->GetModifierList());
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

// �Ƴ�������
void ALittleScriptIndex::RemoveRoot(const std::shared_ptr<ALittleScriptRootElement>& root)
{
    // ������
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
    const auto sub_it = it->second.find(namespace_name_dec);
    if (sub_it == it->second.end()) return;

    auto global_access_it = m_global_access_map.find(name);
    auto namespace_access_it = m_namespace_access_map.find(name);
    auto file_access_it = m_file_access_map.find(root->GetFile());

    for (const auto& pair : sub_it->second.GetElementMap())
    {
        for (const auto& element_pair : pair.second)
        {
            for (const auto& name_dec : element_pair.second)
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
