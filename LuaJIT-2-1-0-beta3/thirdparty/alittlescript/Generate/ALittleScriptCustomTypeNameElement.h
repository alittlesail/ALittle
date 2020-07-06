#ifndef _ALITTLE_ALittleScriptCustomTypeNameElement_H_
#define _ALITTLE_ALittleScriptCustomTypeNameElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptIdElement;

class ALittleScriptCustomTypeNameElement : public ABnfNodeElement
{
public:
    ALittleScriptCustomTypeNameElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptCustomTypeNameElement() { }

private:
    bool m_flag_Id = false;
    std::shared_ptr<ALittleScriptIdElement> m_cache_Id;
public:
    std::shared_ptr<ALittleScriptIdElement> GetId();
};

#endif // _ALITTLE_ALittleScriptCustomTypeNameElement_H_
