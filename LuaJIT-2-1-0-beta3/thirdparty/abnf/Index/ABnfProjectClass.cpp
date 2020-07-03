
#include "ABnfProjectClass.h"
#include "ABnfFileClass.h"
#include "../../alanguage/Model/ABnf.h"
#include "../../alanguage/Model/ABnfNodeElement.h"

void ABnfProjectClass::Generate(const std::string& full_path, int query_id, int version, const std::string& target_path, const std::string& language_name)
{
    auto it = m_file_map.find(full_path);
    if (it != m_file_map.end())
    {
        auto* file = dynamic_cast<ABnfFileClass*>(it->second);
        if (file != nullptr)
        {
            std::string error = file->Generate(version, target_path, language_name);

            std::unique_lock<std::mutex> lock(m_output_lock);
            m_outputs.push_back([query_id, error](lua_State* L)->int
            {
                lua_newtable(L);
                lua_pushinteger(L, query_id);
                lua_setfield(L, -2, "query_id");
                if (error.size())
                {
                    lua_pushstring(L, error.c_str());
                    lua_setfield(L, -2, "result");
                }
                return 1;
            });

            return;
        }
    }

    std::unique_lock<std::mutex> lock(m_output_lock);
    m_outputs.push_back([query_id](lua_State* L) -> int {
        lua_newtable(L);
        lua_pushinteger(L, query_id);
        lua_setfield(L, -2, "query_id");
        return 1;
        });
}
