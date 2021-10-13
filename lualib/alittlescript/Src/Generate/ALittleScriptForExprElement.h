#ifndef _ALITTLE_ALittleScriptForExprElement_H_
#define _ALITTLE_ALittleScriptForExprElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptForConditionElement;
class ALittleScriptForBodyElement;
class ALittleScriptAllExprElement;
class ALittleScriptKeyElement;

class ALittleScriptForExprElement : public ABnfNodeElement
{
public:
    ALittleScriptForExprElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptForExprElement() { }

private:
    bool m_flag_ForCondition = false;
    std::shared_ptr<ALittleScriptForConditionElement> m_cache_ForCondition;
public:
    std::shared_ptr<ALittleScriptForConditionElement> GetForCondition();
private:
    bool m_flag_ForBody = false;
    std::shared_ptr<ALittleScriptForBodyElement> m_cache_ForBody;
public:
    std::shared_ptr<ALittleScriptForBodyElement> GetForBody();
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

#endif // _ALITTLE_ALittleScriptForExprElement_H_
