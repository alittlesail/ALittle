#include "ABnfFactory.h"
#include "ABnfElement.h"
#include "ABnfNodeElement.h"
#include "ABnfKeyElement.h"
#include "ABnfStringElement.h"
#include "ABnfRegexElement.h"

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
