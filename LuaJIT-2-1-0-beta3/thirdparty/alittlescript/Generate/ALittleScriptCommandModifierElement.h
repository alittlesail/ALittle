#ifndef _ALITTLE_ALittleScriptCommandModifierElement_H_
#define _ALITTLE_ALittleScriptCommandModifierElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptCommandBodyDecElement;
class ALittleScriptKeyElement;

class ALittleScriptCommandModifierElement : public ABnfNodeElement
{
public:
    ALittleScriptCommandModifierElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptCommandModifierElement() { }

private:
    bool m_flag_CommandBodyDec = false;
    std::shared_ptr<ALittleScriptCommandBodyDecElement> m_cache_CommandBodyDec;
public:
    std::shared_ptr<ALittleScriptCommandBodyDecElement> GetCommandBodyDec();
private:
    bool m_flag_Key = false;
    std::shared_ptr<ALittleScriptKeyElement> m_cache_Key;
public:
    std::shared_ptr<ALittleScriptKeyElement> GetKey();
};

#endif // _ALITTLE_ALittleScriptCommandModifierElement_H_
