
#include "ABnfFactory.h"
#include "ABnfFile.h"

#include "alanguage/Src/Model/ABnfElement.h"
#include "alanguage/Src/Model/ABnfNodeElement.h"
#include "alanguage/Src/Model/ABnfKeyElement.h"
#include "alanguage/Src/Model/ABnfStringElement.h"
#include "alanguage/Src/Model/ABnfRegexElement.h"
#include "alanguage/Src/Model/ABnfReference.h"
#include "alanguage/Src/Model/ARegex.h"

ABnfNodeElementPtr ABnfFactory::CreateNodeElement(ABnfFile* file, int line, int col, int offset, const std::string& type)
{
    return std::make_shared<ABnfNodeElement>(this, file, line, col, offset, type);
}

ABnfKeyElementPtr ABnfFactory::CreateKeyElement(ABnfFile* file, int line, int col, int offset, const std::string& type)
{
    return std::make_shared<ABnfKeyElement>(this, file, line, col, offset, type);
}

ABnfStringElementPtr ABnfFactory::CreateStringElement(ABnfFile* file, int line, int col, int offset, const std::string& type)
{
    return std::make_shared<ABnfStringElement>(this, file, line, col, offset, type);
}

ABnfRegexElementPtr ABnfFactory::CreateRegexElement(ABnfFile* file, int line, int col, int offset, const std::string& type, const std::shared_ptr<ARegex>& regex)
{
    return std::make_shared<ABnfRegexElement>(this, file, line, col, offset, type, regex);
}

ABnfReference* ABnfFactory::CreateReference(const ABnfElementPtr& element)
{
    return new ABnfReference();
}

ABnfFile* ABnfFactory::CreateFile(ABnfProject* project, const std::string& module_path, const std::string& full_path, const char* text, size_t len)
{
    return new ABnfFile(project, module_path, full_path, text, len, false);
}

std::string ABnfFactory::ReplaceAll(std::string str, const std::string& from, const std::string& to)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

bool ABnfFactory::WriteAllText(const std::string& file_path, const std::string& content)
{
    FILE* file = nullptr;
#ifdef _WIN32
    fopen_s(&file, file_path.c_str(), "wb");
#else
    file = fopen(file_path.c_str(), "wb");
#endif
    if (file == nullptr) return false;

    fwrite(content.c_str(), 1, content.size(), file);

    fclose(file);
    return true;
}
