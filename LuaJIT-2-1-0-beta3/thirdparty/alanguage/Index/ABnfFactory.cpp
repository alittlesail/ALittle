#include "ABnfFactory.h"
#include "ABnfFile.h"
#include "../Model/ABnfElement.h"
#include "../Model/ABnfNodeElement.h"
#include "../Model/ABnfKeyElement.h"
#include "../Model/ABnfStringElement.h"
#include "../Model/ABnfRegexElement.h"
#include "../Model/ABnfReference.h"

ABnfNodeElementPtr ABnfFactory::CreateNodeElement(ABnfFile* file, int line, int col, int offset, const std::string& type)
{
    return ABnfNodeElementPtr(new ABnfNodeElement(this, file, line, col, offset, type));
}

ABnfKeyElementPtr ABnfFactory::CreateKeyElement(ABnfFile* file, int line, int col, int offset, const std::string& type)
{
    return ABnfKeyElementPtr(new ABnfKeyElement(this, file, line, col, offset, type));
}

ABnfStringElementPtr ABnfFactory::CreateStringElement(ABnfFile* file, int line, int col, int offset, const std::string& type)
{
    return ABnfStringElementPtr(new ABnfStringElement(this, file, line, col, offset, type));
}

ABnfRegexElementPtr ABnfFactory::CreateRegexElement(ABnfFile* file, int line, int col, int offset, const std::string& type, std::shared_ptr<std::regex> regex)
{
    return ABnfRegexElementPtr(new ABnfRegexElement(this, file, line, col, offset, type, regex));
}

ABnfReference* ABnfFactory::CreateReference(ABnfElementPtr element)
{
    return new ABnfReferenceTemplate<ABnfElement>(element);
}

ABnfFile* ABnfFactory::CreateFile(ABnfProject* project, const std::string& full_path, const char* text, size_t len)
{
    return new ABnfFile(project, full_path, text, len, false);
}
