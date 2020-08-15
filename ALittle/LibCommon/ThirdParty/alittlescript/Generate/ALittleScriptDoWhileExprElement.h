#ifndef _ALITTLE_ALittleScriptDoWhileExprElement_H_
#define _ALITTLE_ALittleScriptDoWhileExprElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptDoWhileBodyElement;
class ALittleScriptDoWhileConditionElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptDoWhileExprElement : public ABnfNodeElement
{
public:
    ALittleScriptDoWhileExprElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptDoWhileExprElement() { }

private:
    bool m_flag_DoWhileBody = false;
    std::shared_ptr<ALittleScriptDoWhileBodyElement> m_cache_DoWhileBody;
public:
    std::shared_ptr<ALittleScriptDoWhileBodyElement> GetDoWhileBody();
private:
    bool m_flag_DoWhileCondition = false;
    std::shared_ptr<ALittleScriptDoWhileConditionElement> m_cache_DoWhileCondition;
public:
    std::shared_ptr<ALittleScriptDoWhileConditionElement> GetDoWhileCondition();
private:
    bool m_flag_Key = false;
    std::vector<std::shared_ptr<ALittleScriptKeyElement>> m_list_Key;
public:
    const std::vector<std::shared_ptr<ALittleScriptKeyElement>>& GetKeyList();
private:
    bool m_flag_String = false;
    std::shared_ptr<ALittleScriptStringElement> m_cache_String;
public:
    std::shared_ptr<ALittleScriptStringElement> GetString();
};

#endif // _ALITTLE_ALittleScriptDoWhileExprElement_H_
