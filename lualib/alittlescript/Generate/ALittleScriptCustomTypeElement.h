#ifndef _ALITTLE_ALittleScriptCustomTypeElement_H_
#define _ALITTLE_ALittleScriptCustomTypeElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptCustomTypeNameElement;
class ALittleScriptCustomTypeDotIdElement;
class ALittleScriptCustomTypeTemplateElement;

class ALittleScriptCustomTypeElement : public ABnfNodeElement
{
public:
    ALittleScriptCustomTypeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptCustomTypeElement() { }

private:
    bool m_flag_CustomTypeName = false;
    std::shared_ptr<ALittleScriptCustomTypeNameElement> m_cache_CustomTypeName;
public:
    std::shared_ptr<ALittleScriptCustomTypeNameElement> GetCustomTypeName();
private:
    bool m_flag_CustomTypeDotId = false;
    std::shared_ptr<ALittleScriptCustomTypeDotIdElement> m_cache_CustomTypeDotId;
public:
    std::shared_ptr<ALittleScriptCustomTypeDotIdElement> GetCustomTypeDotId();
private:
    bool m_flag_CustomTypeTemplate = false;
    std::shared_ptr<ALittleScriptCustomTypeTemplateElement> m_cache_CustomTypeTemplate;
public:
    std::shared_ptr<ALittleScriptCustomTypeTemplateElement> GetCustomTypeTemplate();
};

#endif // _ALITTLE_ALittleScriptCustomTypeElement_H_
