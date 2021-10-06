
#include "ALittleScriptProjectExport.h"

#include "alittlescript/Src/Index/ALittleScriptUtility.h"
#include "alittlescript/Src/Reference/ALittleScriptReferenceTemplate.h"
#include "alittlescript/Src/Translation/ALittleScriptTranslation.h"

void ALittleScriptProjectExport::ClearImpl()
{
    ClearIndex();
}

ALittleScriptProjectExport::ALittleScriptProjectExport()
	: m_target_language("Lua")
{
	m_language_set.insert("Lua");
	m_language_set.insert("JavaScript");
}

void ALittleScriptProjectExport::FindDefineImpl(const std::string& pre_input, const std::string& input, std::vector<ALanguageCompletionInfo>& info_list)
{
    std::list<std::string> pre_split;
    ABnfFactory::Split(pre_input, ".", pre_split);
    std::list<std::string> split;
    ABnfFactory::Split(input, ".", split);

	// ��ȡ������
    std::string namespace_name;
    bool namespace_in_input = false;
    if (!pre_split.empty())
    {
        namespace_name = pre_split.front();
        pre_split.pop_front();
    }
    else if (!split.empty())
    {
        namespace_in_input = true;
        namespace_name = split.front();
        split.pop_front();
    }

	// ����������ǿյģ���ô���ǻ�ȡ������
	if (namespace_name.empty())
	{
        std::unordered_map<std::string, std::shared_ptr<ALittleScriptNamespaceNameDecElement>> name_dec_map;
        FindNamespaceNameDecList(namespace_name, name_dec_map);
        for (auto& pair : name_dec_map)
            info_list.emplace_back(pair.second->GetElementText(), ALittleScriptIconType::NAMESPACE, pair.second->GetDescriptor());
        return;
	}

	// ��ȡ������
    std::string define_name;
    bool define_in_input = false;
	if (!pre_split.empty())
	{
		define_name = pre_split.front();
        pre_split.pop_front();
	}
    else if (!split.empty())
    {
        define_in_input = true;
        define_name = split.front();
        split.pop_front();
    }

	// ����������ǿյģ���ô�ͻ�ȡ������
	if (define_name.empty())
	{
        {
            std::vector<ABnfElementPtr> dec_list;
            FindGotoALittleNameDecList(ABnfElementType::CLASS_NAME, nullptr, namespace_name, u8"", true, dec_list);

            for (auto& dec : dec_list)
            {
            	if (namespace_in_input)
                    info_list.emplace_back(namespace_name + "." + dec->GetElementText(), ALittleScriptIconType::CLASS, dec->GetDescriptor());
                else
	                info_list.emplace_back(dec->GetElementText(), ALittleScriptIconType::CLASS, dec->GetDescriptor());
            }                
        }
        {
            std::vector<std::shared_ptr<ABnfElement>> dec_list;
            FindGotoALittleNameDecList(ABnfElementType::STRUCT_NAME, nullptr, namespace_name, u8"", true, dec_list);

            for (auto& dec : dec_list)
            {
                if (namespace_in_input)
                    info_list.emplace_back(namespace_name + "." + dec->GetElementText(), ALittleScriptIconType::STRUCT, dec->GetDescriptor());
                else
                    info_list.emplace_back(dec->GetElementText(), ALittleScriptIconType::STRUCT, dec->GetDescriptor());
            }
        }
        {
            std::vector<std::shared_ptr<ABnfElement>> dec_list;
            FindGotoALittleNameDecList(ABnfElementType::ENUM_NAME, nullptr, namespace_name, u8"", true, dec_list);

            for (auto& dec : dec_list)
            {
                if (namespace_in_input)
                    info_list.emplace_back(namespace_name + "." + dec->GetElementText(), ALittleScriptIconType::ENUM, dec->GetDescriptor());
                else
                    info_list.emplace_back(dec->GetElementText(), ALittleScriptIconType::ENUM, dec->GetDescriptor());
            }
        }
        return;
	}

    // ��ȡ������
    std::string var_name;
    if (!pre_split.empty())
    {
        var_name = pre_split.front();
        pre_split.pop_front();
    }
    else if (!split.empty())
    {
        var_name = split.front();
        split.pop_front();
    }

    if (var_name.empty())
    {
        {
            std::vector<ABnfElementPtr> dec_list;
            FindGotoALittleNameDecList(ABnfElementType::CLASS_NAME, nullptr, namespace_name, define_name, true, dec_list);

            for (auto& dec : dec_list)
            {
                auto class_dec = std::dynamic_pointer_cast<ALittleScriptClassDecElement>(dec->GetParent());
                if (class_dec == nullptr) continue;
                std::vector<std::shared_ptr<ABnfElement>> result;
                ALittleScriptUtility::FindClassAttrList(class_dec, ALittleScriptUtility::sAccessPrivateAndProtectedAndPublic, ClassAttrType::VAR, u8"", result, 100);
                for (auto& element : result)
                {
                    auto var_dec = std::dynamic_pointer_cast<ALittleScriptClassVarDecElement>(element);
                    if (var_dec == nullptr) continue;
                    auto name_dec = var_dec->GetClassVarNameDec();
                    if (name_dec == nullptr) continue;
                	if (namespace_in_input)
                        info_list.emplace_back(namespace_name + "." + define_name + "." + name_dec->GetElementText(), ALittleScriptIconType::VARIABLE, element->GetDescriptor());
                    else if (define_in_input)
                        info_list.emplace_back(define_name + "." + name_dec->GetElementText(), ALittleScriptIconType::VARIABLE, element->GetDescriptor());
                    else
	                    info_list.emplace_back(name_dec->GetElementText(), ALittleScriptIconType::VARIABLE, element->GetDescriptor());
                }
                result.clear();
                ALittleScriptUtility::FindClassAttrList(class_dec, ALittleScriptUtility::sAccessPrivateAndProtectedAndPublic, ClassAttrType::FUN, u8"", result, 100);
                ALittleScriptUtility::FilterSameName(result, result);
                for (auto& element : result)
                {
                    auto name_dec = std::dynamic_pointer_cast<ALittleScriptMethodNameDecElement>(element);
                    if (name_dec == nullptr) continue;
                    if (namespace_in_input)
                        info_list.emplace_back(namespace_name + "." + define_name + "." + name_dec->GetElementText(), ALittleScriptIconType::MEMBER_METHOD, element->GetDescriptor());
                    else if (define_in_input)
                        info_list.emplace_back(define_name + "." + name_dec->GetElementText(), ALittleScriptIconType::MEMBER_METHOD, element->GetDescriptor());
                    else
                        info_list.emplace_back(name_dec->GetElementText(), ALittleScriptIconType::MEMBER_METHOD, element->GetDescriptor());
                }
                    
                result.clear();
                ALittleScriptUtility::FindClassAttrList(class_dec, ALittleScriptUtility::sAccessPrivateAndProtectedAndPublic, ClassAttrType::STATIC, u8"", result, 100);
                for (auto& element : result)
                {
                    auto name_dec = std::dynamic_pointer_cast<ALittleScriptMethodNameDecElement>(element);
                    if (name_dec == nullptr) continue;
                    if (namespace_in_input)
                        info_list.emplace_back(namespace_name + "." + define_name + "." + name_dec->GetElementText(), ALittleScriptIconType::STATIC_METHOD, element->GetDescriptor());
                    else if (define_in_input)
                        info_list.emplace_back(define_name + "." + name_dec->GetElementText(), ALittleScriptIconType::STATIC_METHOD, element->GetDescriptor());
                    else
                        info_list.emplace_back(name_dec->GetElementText(), ALittleScriptIconType::STATIC_METHOD, element->GetDescriptor());
                }
            }
        }
        {
            std::vector<ABnfElementPtr> dec_list;
            FindGotoALittleNameDecList(ABnfElementType::STRUCT_NAME, nullptr, namespace_name, define_name, true, dec_list);

            for (auto& dec : dec_list)
            {
                auto struct_dec = std::dynamic_pointer_cast<ALittleScriptStructDecElement>(dec->GetParent());
                if (struct_dec == nullptr) continue;
                std::vector<std::shared_ptr<ALittleScriptStructVarDecElement>> result;
                ALittleScriptUtility::FindStructVarDecList(struct_dec, u8"", result, 100);
                for (auto& element : result)
                {
                    auto name_dec = element->GetStructVarNameDec();
                    if (name_dec == nullptr) continue;
                    if (namespace_in_input)
                        info_list.emplace_back(namespace_name + "." + define_name + "." + name_dec->GetElementText(), ALittleScriptIconType::PROPERTY, element->GetDescriptor());
                    else if (define_in_input)
                        info_list.emplace_back(define_name + "." + name_dec->GetElementText(), ALittleScriptIconType::PROPERTY, element->GetDescriptor());
                    else
                        info_list.emplace_back(name_dec->GetElementText(), ALittleScriptIconType::PROPERTY, element->GetDescriptor());
                }
            }
        }
        {
            std::vector<ABnfElementPtr> dec_list;
            FindGotoALittleNameDecList(ABnfElementType::ENUM_NAME, nullptr, namespace_name, define_name, true, dec_list);

            for (auto& dec : dec_list)
            {
                auto enum_dec = std::dynamic_pointer_cast<ALittleScriptEnumDecElement>(dec->GetParent());
                if (enum_dec == nullptr) continue;
                std::vector<std::shared_ptr<ALittleScriptEnumVarDecElement>> result;
                ALittleScriptUtility::FindEnumVarDecList(enum_dec, u8"", result);
                for (auto& element : result)
                {
                    auto name_dec = element->GetEnumVarNameDec();
                    if (name_dec == nullptr) continue;
                    if (namespace_in_input)
                        info_list.emplace_back(namespace_name + "." + define_name + "." + name_dec->GetElementText(), ALittleScriptIconType::PROPERTY, element->GetDescriptor());
                    else if (define_in_input)
                        info_list.emplace_back(define_name + "." + name_dec->GetElementText(), ALittleScriptIconType::PROPERTY, element->GetDescriptor());
                    else
                        info_list.emplace_back(name_dec->GetElementText(), ALittleScriptIconType::PROPERTY, element->GetDescriptor());
                }
            }
        }
        return;
    }
}

void ALittleScriptProjectExport::FindGotoImpl(const std::string& text, ALanguageGotoInfo& info)
{
    std::vector<std::string> split;
    ABnfFactory::Split(text, ".", split);

    if (split.empty()) return;

    // ����������ǿյģ���ô���ǻ�ȡ������
    if (split.size() <= 1)
    {
        std::unordered_map<std::string, std::shared_ptr<ALittleScriptNamespaceNameDecElement>> name_dec_map;
        FindNamespaceNameDecList(split[0], name_dec_map);
        for (auto& pair : name_dec_map)
        {
            info.file_path = pair.second->GetFullPath();
            info.line_start = pair.second->GetStartLine();
            info.char_start = pair.second->GetStartCol();
            info.line_end = pair.second->GetEndLine();
            info.char_end = pair.second->GetEndCol();
            return;
        }
        return;
    }

	if (split.size() <= 2)
	{
        {
            std::vector<ABnfElementPtr> dec_list;
            FindGotoALittleNameDecList(ABnfElementType::CLASS_NAME, nullptr, split[0], split[1], true, dec_list);
            for (auto& dec : dec_list)
            {
                info.file_path = dec->GetFullPath();
                info.line_start = dec->GetStartLine();
                info.char_start = dec->GetStartCol();
                info.line_end = dec->GetEndLine();
                info.char_end = dec->GetEndCol();
                return;
            }
        }
        {
            std::vector<std::shared_ptr<ABnfElement>> dec_list;
            FindGotoALittleNameDecList(ABnfElementType::STRUCT_NAME, nullptr, split[0], split[1], true, dec_list);
            for (auto& dec : dec_list)
            {
                info.file_path = dec->GetFullPath();
                info.line_start = dec->GetStartLine();
                info.char_start = dec->GetStartCol();
                info.line_end = dec->GetEndLine();
                info.char_end = dec->GetEndCol();
                return;
            }
        }
        {
            std::vector<std::shared_ptr<ABnfElement>> dec_list;
            FindGotoALittleNameDecList(ABnfElementType::ENUM_NAME, nullptr, split[0], split[1], true, dec_list);
            for (auto& dec : dec_list)
            {
                info.file_path = dec->GetFullPath();
                info.line_start = dec->GetStartLine();
                info.char_start = dec->GetStartCol();
                info.line_end = dec->GetEndLine();
                info.char_end = dec->GetEndCol();
                return;
            }
        }
        return;
    }

    if (split.size() >= 3)
    {
        {
            std::vector<ABnfElementPtr> dec_list;
            FindGotoALittleNameDecList(ABnfElementType::CLASS_NAME, nullptr, split[0], split[1], true, dec_list);

            for (auto& dec : dec_list)
            {
                auto class_dec = std::dynamic_pointer_cast<ALittleScriptClassDecElement>(dec->GetParent());
                if (class_dec == nullptr) continue;
                std::vector<std::shared_ptr<ABnfElement>> result;
                ALittleScriptUtility::FindClassAttrList(class_dec, ALittleScriptUtility::sAccessPrivateAndProtectedAndPublic, ClassAttrType::VAR, split[2], result, 100);
                for (auto& element : result)
                {
                    info.file_path = element->GetFullPath();
                    info.line_start = element->GetStartLine();
                    info.char_start = element->GetStartCol();
                    info.line_end = element->GetEndLine();
                    info.char_end = element->GetEndCol();
                    return;
                }
                result.clear();
                ALittleScriptUtility::FindClassAttrList(class_dec, ALittleScriptUtility::sAccessPrivateAndProtectedAndPublic, ClassAttrType::FUN, split[2], result, 100);
                for (auto& element : result)
                {
                    info.file_path = element->GetFullPath();
                    info.line_start = element->GetStartLine();
                    info.char_start = element->GetStartCol();
                    info.line_end = element->GetEndLine();
                    info.char_end = element->GetEndCol();
                    return;
                }

                result.clear();
                ALittleScriptUtility::FindClassAttrList(class_dec, ALittleScriptUtility::sAccessPrivateAndProtectedAndPublic, ClassAttrType::STATIC, split[2], result, 100);
                for (auto& element : result)
                {
                    info.file_path = element->GetFullPath();
                    info.line_start = element->GetStartLine();
                    info.char_start = element->GetStartCol();
                    info.line_end = element->GetEndLine();
                    info.char_end = element->GetEndCol();
                    return;
                }
            }
        }
        {
            std::vector<ABnfElementPtr> dec_list;
            FindGotoALittleNameDecList(ABnfElementType::STRUCT_NAME, nullptr, split[0], split[1], true, dec_list);

            for (auto& dec : dec_list)
            {
                auto struct_dec = std::dynamic_pointer_cast<ALittleScriptStructDecElement>(dec->GetParent());
                if (struct_dec == nullptr) continue;
                std::vector<std::shared_ptr<ALittleScriptStructVarDecElement>> result;
                ALittleScriptUtility::FindStructVarDecList(struct_dec, split[2], result, 100);
                for (auto& element : result)
                {
                    info.file_path = element->GetFullPath();
                    info.line_start = element->GetStartLine();
                    info.char_start = element->GetStartCol();
                    info.line_end = element->GetEndLine();
                    info.char_end = element->GetEndCol();
                    return;
                }
            }
        }
        {
            std::vector<ABnfElementPtr> dec_list;
            FindGotoALittleNameDecList(ABnfElementType::ENUM_NAME, nullptr, split[0], split[1], true, dec_list);

            for (auto& dec : dec_list)
            {
                auto enum_dec = std::dynamic_pointer_cast<ALittleScriptEnumDecElement>(dec->GetParent());
                if (enum_dec == nullptr) continue;
                std::vector<std::shared_ptr<ALittleScriptEnumVarDecElement>> result;
                ALittleScriptUtility::FindEnumVarDecList(enum_dec, split[2], result);
                for (auto& element : result)
                {
                    info.file_path = element->GetFullPath();
                    info.line_start = element->GetStartLine();
                    info.char_start = element->GetStartCol();
                    info.line_end = element->GetEndLine();
                    info.char_end = element->GetEndCol();
                    return;
                }
            }
        }
        return;
    }
}

void ALittleScriptProjectExport::SetTargetLanguage(const std::string& language)
{
	m_target_language = language;
}

void ALittleScriptProjectExport::SetTargetLanguageUI(const std::string& language)
{
    m_target_language_ui = language;
}

void ALittleScriptProjectExport::Generate(int query_id, const std::string& full_path)
{
    const auto it = m_file_map.find(full_path);
    if (it != m_file_map.end())
    {
        auto translation = ALittleScriptTranslation::CreateTranslation(m_target_language);
        auto gen_error = translation->Generate(it->second, true);

        std::string error_full_path;
        int line_start = 0;
        int char_start = 0;
        int line_end = 0;
        int char_end = 0;
        std::string error;
        if (gen_error)
        {
            if (gen_error.element != nullptr)
            {
                error_full_path = gen_error.element->GetFullPath();
                line_start = gen_error.element->GetStartLine();
                char_start = gen_error.element->GetStartCol();
                line_end = gen_error.element->GetEndLine();
                char_end = gen_error.element->GetEndCol();
            }
            error = gen_error.error;
        }

        
        std::unique_lock<std::mutex> lock(m_output_lock);
        m_outputs.emplace_back([query_id, error_full_path, line_start, char_start, line_end, char_end, error](lua_State* L)->int
        {
            lua_newtable(L);
            lua_pushinteger(L, query_id);
            lua_setfield(L, -2, "query_id");
            if (!error.empty())
            {
                lua_newtable(L);
                lua_pushinteger(L, line_start + 1);
                lua_setfield(L, -2, "line_start");
                lua_pushinteger(L, char_start + 1);
                lua_setfield(L, -2, "char_start");
                lua_pushinteger(L, line_end + 1);
                lua_setfield(L, -2, "line_end");
                lua_pushinteger(L, char_end);
                lua_setfield(L, -2, "char_end");
                lua_pushstring(L, error_full_path.c_str());
                lua_setfield(L, -2, "full_path");
                lua_pushstring(L, error.c_str());
                lua_setfield(L, -2, "error");

                lua_setfield(L, -2, "result");
            }
            return 1;
        });

        return;
    }

    std::unique_lock<std::mutex> lock(m_output_lock);
    m_outputs.emplace_back([query_id, full_path](lua_State* L) -> int {
        lua_newtable(L);
        lua_pushinteger(L, query_id);
        lua_setfield(L, -2, "query_id");

        std::string error = "can't find file_path:";
        error += full_path;
        lua_newtable(L);
        lua_pushstring(L, full_path.c_str());
        lua_setfield(L, -2, "full_path");
        lua_pushstring(L, error.c_str());
        lua_setfield(L, -2, "error");

        lua_setfield(L, -2, "result");
        return 1;
    });
}

