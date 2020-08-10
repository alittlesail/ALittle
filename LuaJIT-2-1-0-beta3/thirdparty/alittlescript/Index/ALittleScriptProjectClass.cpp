
#include "ALittleScriptProjectClass.h"
#include "../Translation/ALittleScriptTranslation.h"

void ALittleScriptProjectClass::ClearImpl()
{
    ClearIndex();
}

ALittleScriptProjectClass::ALittleScriptProjectClass()
	: m_target_language("Lua")
{
	m_language_set.insert("Lua");
	m_language_set.insert("JavaScript");
}

ALittleScriptProjectClass::~ALittleScriptProjectClass()
{
}

void ALittleScriptProjectClass::SetTargetLanguage(const std::string& language)
{
	m_target_language = language;
}

void ALittleScriptProjectClass::SetTargetLanguageUI(const std::string& language)
{
    m_target_language_ui = language;
}

void ALittleScriptProjectClass::Generate(int query_id, const std::string& full_path)
{
    auto it = m_file_map.find(full_path);
    if (it != m_file_map.end())
    {
        auto translation = ALittleScriptTranslation::CreateTranslation(m_target_language);
        auto gen_error = translation->Generate(it->second, true);

        std::string full_path;
        int line_start = 0;
        int char_start = 0;
        int line_end = 0;
        int char_end = 0;
        std::string error;
        if (gen_error)
        {
            if (gen_error.element != nullptr)
            {
                full_path = gen_error.element->GetFullPath();
                line_start = gen_error.element->GetStartLine();
                char_start = gen_error.element->GetStartCol();
                line_end = gen_error.element->GetEndLine();
                char_end = gen_error.element->GetEndCol();
            }
            error = gen_error.error;
        }

        
        std::unique_lock<std::mutex> lock(m_output_lock);
        m_outputs.push_back([query_id, full_path, line_start, char_start, line_end, char_end, error](lua_State* L)->int
        {
            lua_newtable(L);
            lua_pushinteger(L, query_id);
            lua_setfield(L, -2, "query_id");
            if (error.size())
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
                lua_pushstring(L, full_path.c_str());
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
    m_outputs.push_back([query_id, full_path](lua_State* L) -> int {
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

void ALittleScriptProjectClass::GetAllNamespace(int query_id)
{
    std::unordered_map<std::string, std::shared_ptr<ALittleScriptNamespaceNameDecElement>> result;
    FindNamespaceNameDecList("", result);
    std::vector<std::string> name_list;
    name_list.reserve(result.size());
    for (auto& pair : result)
        name_list.push_back(pair.first);

    std::unique_lock<std::mutex> lock(m_output_lock);
    m_outputs.push_back([query_id, name_list](lua_State* L)->int
    {
        lua_newtable(L);
        lua_pushinteger(L, query_id);
        lua_setfield(L, -2, "query_id");
    	
        lua_newtable(L);
    	for (size_t i = 0; i < name_list.size(); ++i)
    	{
            lua_pushstring(L, name_list[i].c_str());
            lua_rawseti(L, -2, static_cast<int>(i) + 1);
    	}

        lua_setfield(L, -2, "result");
        return 1;
    });
}

void ALittleScriptProjectClass::GetAllClass(int query_id, const std::string& namespace_name)
{
    std::vector<std::shared_ptr<ABnfElement>> result;
    FindALittleNameDecList(ABnfElementType::CLASS_NAME, nullptr, namespace_name, "", true, result);
    std::vector<std::string> name_list;
    name_list.reserve(result.size());
    for (auto& element : result)
        name_list.push_back(element->GetElementText());

    std::unique_lock<std::mutex> lock(m_output_lock);
    m_outputs.push_back([query_id, name_list](lua_State* L)->int
    {
        lua_newtable(L);
        lua_pushinteger(L, query_id);
        lua_setfield(L, -2, "query_id");

        lua_newtable(L);
        for (size_t i = 0; i < name_list.size(); ++i)
        {
            lua_pushstring(L, name_list[i].c_str());
            lua_rawseti(L, -2, static_cast<int>(i) + 1);
        }
    	
        lua_setfield(L, -2, "result");
        return 1;
    });
}

