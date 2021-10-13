#ifndef _ALITTLE_ALittleScriptStructVarNameDecElement_H_
#define _ALITTLE_ALittleScriptStructVarNameDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptIdElement;

class ALittleScriptStructVarNameDecElement : public ABnfNodeElement
{
public:
    ALittleScriptStructVarNameDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptStructVarNameDecElement() { }

private:
    bool m_flag_Id = false;
    std::shared_ptr<ALittleScriptIdElement> m_cache_Id;
public:
    std::shared_ptr<ALittleScriptIdElement> GetId();
};

#endif // _ALITTLE_ALittleScriptStructVarNameDecElement_H_
