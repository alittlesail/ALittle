#ifndef _ALITTLE_ALittleScriptCustomTypeDotIdElement_H_
#define _ALITTLE_ALittleScriptCustomTypeDotIdElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptCustomTypeDotIdNameElement;
class ALittleScriptStringElement;

class ALittleScriptCustomTypeDotIdElement : public ABnfNodeElement
{
public:
    ALittleScriptCustomTypeDotIdElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptCustomTypeDotIdElement() { }

private:
    bool m_flag_CustomTypeDotIdName = false;
    std::shared_ptr<ALittleScriptCustomTypeDotIdNameElement> m_cache_CustomTypeDotIdName;
public:
    std::shared_ptr<ALittleScriptCustomTypeDotIdNameElement> GetCustomTypeDotIdName();
private:
    bool m_flag_String = false;
    std::shared_ptr<ALittleScriptStringElement> m_cache_String;
public:
    std::shared_ptr<ALittleScriptStringElement> GetString();
};

#endif // _ALITTLE_ALittleScriptCustomTypeDotIdElement_H_
