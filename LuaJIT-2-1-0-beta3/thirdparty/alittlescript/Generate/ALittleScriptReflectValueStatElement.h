#ifndef _ALITTLE_ALittleScriptReflectValueStatElement_H_
#define _ALITTLE_ALittleScriptReflectValueStatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptValueStatElement;
class ALittleScriptStringElement;

class ALittleScriptReflectValueStatElement : public ABnfNodeElement
{
public:
    ALittleScriptReflectValueStatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptReflectValueStatElement() { }

private:
    bool m_flag_ValueStat = false;
    std::shared_ptr<ALittleScriptValueStatElement> m_cache_ValueStat;
public:
    std::shared_ptr<ALittleScriptValueStatElement> GetValueStat();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptReflectValueStatElement_H_
