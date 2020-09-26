#ifndef _ALITTLE_ALittleScriptConstValueElement_H_
#define _ALITTLE_ALittleScriptConstValueElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptTextElement;
class ALittleScriptNumberElement;
class ALittleScriptKeyElement;

class ALittleScriptConstValueElement : public ABnfNodeElement
{
public:
    ALittleScriptConstValueElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptConstValueElement() { }

private:
    bool m_flag_Text = false;
    std::shared_ptr<ALittleScriptTextElement> m_cache_Text;
public:
    std::shared_ptr<ALittleScriptTextElement> GetText();
private:
    bool m_flag_Number = false;
    std::shared_ptr<ALittleScriptNumberElement> m_cache_Number;
public:
    std::shared_ptr<ALittleScriptNumberElement> GetNumber();
private:
    bool m_flag_Key = false;
    std::shared_ptr<ALittleScriptKeyElement> m_cache_Key;
public:
    std::shared_ptr<ALittleScriptKeyElement> GetKey();
};

#endif // _ALITTLE_ALittleScriptConstValueElement_H_
