
#include "ALittleScriptProjectClass.h"

#include "ALittleScriptUtility.h"
#include "../Reference/ALittleScriptReferenceTemplate.h"
#include "../Translation/ALittleScriptTranslation.h"

ALittleScriptProjectClass::ALittleScriptProjectClass()
	: m_target_language("Lua")
{
	m_language_set.insert("Lua");
	m_language_set.insert("JavaScript");
}

void ALittleScriptProjectClass::SetTargetLanguage(const std::string& language)
{
	m_target_language = language;
}

void ALittleScriptProjectClass::GenerateAll()
{
    for (auto& pair : m_file_map)
    {
        auto translation = ALittleScriptTranslation::CreateTranslation(m_target_language);
        auto gen_error = translation->Generate(pair.second, true);

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

        if (error.empty())
            printf("file:%s succeed\n", error_full_path.c_str());
        else
        {
            printf("file:%s(%d, %d) error:%s\n", error_full_path.c_str(), line_start, char_start, error.c_str());
            return;
        }
    }
}
