#ifndef _ALITTLE_ALittleScriptMethodReturnOneDecElement_H_
#define _ALITTLE_ALittleScriptMethodReturnOneDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptMethodReturnTailDecElement;
class ALittleScriptAllTypeElement;

class ALittleScriptMethodReturnOneDecElement : public ABnfNodeElement
{
public:
    ALittleScriptMethodReturnOneDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptMethodReturnOneDecElement() { }

private:
    bool m_flag_MethodReturnTailDec = false;
    std::shared_ptr<ALittleScriptMethodReturnTailDecElement> m_cache_MethodReturnTailDec;
public:
    std::shared_ptr<ALittleScriptMethodReturnTailDecElement> GetMethodReturnTailDec();
private:
    bool m_flag_AllType = false;
    std::shared_ptr<ALittleScriptAllTypeElement> m_cache_AllType;
public:
    std::shared_ptr<ALittleScriptAllTypeElement> GetAllType();
};

#endif // _ALITTLE_ALittleScriptMethodReturnOneDecElement_H_
