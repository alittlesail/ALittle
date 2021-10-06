#ifndef _ALITTLE_ALittleScriptCommandBodyDecElement_H_
#define _ALITTLE_ALittleScriptCommandBodyDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptTextElement;
class ALittleScriptStringElement;

class ALittleScriptCommandBodyDecElement : public ABnfNodeElement
{
public:
    ALittleScriptCommandBodyDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptCommandBodyDecElement() { }

private:
    bool m_flag_Text = false;
    std::shared_ptr<ALittleScriptTextElement> m_cache_Text;
public:
    std::shared_ptr<ALittleScriptTextElement> GetText();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptCommandBodyDecElement_H_
