#ifndef _ALITTLE_ALittleScriptIfExprElement_H_
#define _ALITTLE_ALittleScriptIfExprElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptIfConditionElement;
class ALittleScriptAllExprElement;
class ALittleScriptIfBodyElement;
class ALittleScriptElseIfExprElement;
class ALittleScriptElseExprElement;
class ALittleScriptKeyElement;

class ALittleScriptIfExprElement : public ABnfNodeElement
{
public:
    ALittleScriptIfExprElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptIfExprElement() { }

private:
    bool m_flag_IfCondition = false;
    std::shared_ptr<ALittleScriptIfConditionElement> m_cache_IfCondition;
public:
    std::shared_ptr<ALittleScriptIfConditionElement> GetIfCondition();
private:
    bool m_flag_AllExpr = false;
    std::shared_ptr<ALittleScriptAllExprElement> m_cache_AllExpr;
public:
    std::shared_ptr<ALittleScriptAllExprElement> GetAllExpr();
private:
    bool m_flag_IfBody = false;
    std::shared_ptr<ALittleScriptIfBodyElement> m_cache_IfBody;
public:
    std::shared_ptr<ALittleScriptIfBodyElement> GetIfBody();
private:
    bool m_flag_ElseIfExpr = false;
    std::vector<std::shared_ptr<ALittleScriptElseIfExprElement>> m_list_ElseIfExpr;
public:
    const std::vector<std::shared_ptr<ALittleScriptElseIfExprElement>>& GetElseIfExprList();
private:
    bool m_flag_ElseExpr = false;
    std::shared_ptr<ALittleScriptElseExprElement> m_cache_ElseExpr;
public:
    std::shared_ptr<ALittleScriptElseExprElement> GetElseExpr();
private:
    bool m_flag_Key = false;
    std::shared_ptr<ALittleScriptKeyElement> m_cache_Key;
public:
    std::shared_ptr<ALittleScriptKeyElement> GetKey();
};

#endif // _ALITTLE_ALittleScriptIfExprElement_H_
