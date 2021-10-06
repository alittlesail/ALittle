#ifndef _ALITTLE_ALittleScriptInstanceDecElement_H_
#define _ALITTLE_ALittleScriptInstanceDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptVarAssignExprElement;

class ALittleScriptInstanceDecElement : public ABnfNodeElement
{
public:
    ALittleScriptInstanceDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptInstanceDecElement() { }

private:
    bool m_flag_VarAssignExpr = false;
    std::shared_ptr<ALittleScriptVarAssignExprElement> m_cache_VarAssignExpr;
public:
    std::shared_ptr<ALittleScriptVarAssignExprElement> GetVarAssignExpr();
};

#endif // _ALITTLE_ALittleScriptInstanceDecElement_H_
