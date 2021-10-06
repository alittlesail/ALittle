#ifndef _ALITTLE_ALittleScriptWhileExprElement_H_
#define _ALITTLE_ALittleScriptWhileExprElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptWhileConditionElement;
class ALittleScriptAllExprElement;
class ALittleScriptWhileBodyElement;
class ALittleScriptKeyElement;

class ALittleScriptWhileExprElement : public ABnfNodeElement
{
public:
    ALittleScriptWhileExprElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptWhileExprElement() { }

private:
    bool m_flag_WhileCondition = false;
    std::shared_ptr<ALittleScriptWhileConditionElement> m_cache_WhileCondition;
public:
    std::shared_ptr<ALittleScriptWhileConditionElement> GetWhileCondition();
private:
    bool m_flag_AllExpr = false;
    std::shared_ptr<ALittleScriptAllExprElement> m_cache_AllExpr;
public:
    std::shared_ptr<ALittleScriptAllExprElement> GetAllExpr();
private:
    bool m_flag_WhileBody = false;
    std::shared_ptr<ALittleScriptWhileBodyElement> m_cache_WhileBody;
public:
    std::shared_ptr<ALittleScriptWhileBodyElement> GetWhileBody();
private:
    bool m_flag_Key = false;
    std::shared_ptr<ALittleScriptKeyElement> m_cache_Key;
public:
    std::shared_ptr<ALittleScriptKeyElement> GetKey();
};

#endif // _ALITTLE_ALittleScriptWhileExprElement_H_
