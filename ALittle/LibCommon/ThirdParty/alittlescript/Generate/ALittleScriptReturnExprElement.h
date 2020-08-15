#ifndef _ALITTLE_ALittleScriptReturnExprElement_H_
#define _ALITTLE_ALittleScriptReturnExprElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptValueStatElement;
class ALittleScriptReturnYieldElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptReturnExprElement : public ABnfNodeElement
{
public:
    ALittleScriptReturnExprElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptReturnExprElement() { }

private:
    bool m_flag_ValueStat = false;
    std::vector<std::shared_ptr<ALittleScriptValueStatElement>> m_list_ValueStat;
public:
    const std::vector<std::shared_ptr<ALittleScriptValueStatElement>>& GetValueStatList();
private:
    bool m_flag_ReturnYield = false;
    std::shared_ptr<ALittleScriptReturnYieldElement> m_cache_ReturnYield;
public:
    std::shared_ptr<ALittleScriptReturnYieldElement> GetReturnYield();
private:
    bool m_flag_Key = false;
    std::shared_ptr<ALittleScriptKeyElement> m_cache_Key;
public:
    std::shared_ptr<ALittleScriptKeyElement> GetKey();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptReturnExprElement_H_
