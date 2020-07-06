#ifndef _ALITTLE_ALittleScriptElseExprElement_H_
#define _ALITTLE_ALittleScriptElseExprElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptElseBodyElement;
class ALittleScriptAllExprElement;
class ALittleScriptKeyElement;

class ALittleScriptElseExprElement : public ABnfNodeElement
{
public:
    ALittleScriptElseExprElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptElseExprElement() { }

private:
    bool m_flag_ElseBody = false;
    std::shared_ptr<ALittleScriptElseBodyElement> m_cache_ElseBody;
public:
    std::shared_ptr<ALittleScriptElseBodyElement> GetElseBody();
private:
    bool m_flag_AllExpr = false;
    std::shared_ptr<ALittleScriptAllExprElement> m_cache_AllExpr;
public:
    std::shared_ptr<ALittleScriptAllExprElement> GetAllExpr();
private:
    bool m_flag_Key = false;
    std::shared_ptr<ALittleScriptKeyElement> m_cache_Key;
public:
    std::shared_ptr<ALittleScriptKeyElement> GetKey();
};

#endif // _ALITTLE_ALittleScriptElseExprElement_H_
