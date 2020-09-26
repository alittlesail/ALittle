#ifndef _ALITTLE_ALittleScriptForEndStatElement_H_
#define _ALITTLE_ALittleScriptForEndStatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptValueStatElement;

class ALittleScriptForEndStatElement : public ABnfNodeElement
{
public:
    ALittleScriptForEndStatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptForEndStatElement() { }

private:
    bool m_flag_ValueStat = false;
    std::shared_ptr<ALittleScriptValueStatElement> m_cache_ValueStat;
public:
    std::shared_ptr<ALittleScriptValueStatElement> GetValueStat();
};

#endif // _ALITTLE_ALittleScriptForEndStatElement_H_
