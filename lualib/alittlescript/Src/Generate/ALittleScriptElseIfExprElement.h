#ifndef _ALITTLE_ALittleScriptElseIfExprElement_H_
#define _ALITTLE_ALittleScriptElseIfExprElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptElseIfConditionElement;
class ALittleScriptElseIfBodyElement;
class ALittleScriptAllExprElement;
class ALittleScriptKeyElement;

class ALittleScriptElseIfExprElement : public ABnfNodeElement
{
public:
    ALittleScriptElseIfExprElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptElseIfExprElement() { }

private:
    bool m_flag_ElseIfCondition = false;
    std::shared_ptr<ALittleScriptElseIfConditionElement> m_cache_ElseIfCondition;
public:
    std::shared_ptr<ALittleScriptElseIfConditionElement> GetElseIfCondition();
private:
    bool m_flag_ElseIfBody = false;
    std::shared_ptr<ALittleScriptElseIfBodyElement> m_cache_ElseIfBody;
public:
    std::shared_ptr<ALittleScriptElseIfBodyElement> GetElseIfBody();
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

#endif // _ALITTLE_ALittleScriptElseIfExprElement_H_
