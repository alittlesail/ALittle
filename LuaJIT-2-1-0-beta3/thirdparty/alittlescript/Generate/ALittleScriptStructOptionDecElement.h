#ifndef _ALITTLE_ALittleScriptStructOptionDecElement_H_
#define _ALITTLE_ALittleScriptStructOptionDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptStructOptionNameDecElement;
class ALittleScriptTextElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptStructOptionDecElement : public ABnfNodeElement
{
public:
    ALittleScriptStructOptionDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptStructOptionDecElement() { }

private:
    bool m_flag_StructOptionNameDec = false;
    std::shared_ptr<ALittleScriptStructOptionNameDecElement> m_cache_StructOptionNameDec;
public:
    std::shared_ptr<ALittleScriptStructOptionNameDecElement> GetStructOptionNameDec();
private:
    bool m_flag_Text = false;
    std::shared_ptr<ALittleScriptTextElement> m_cache_Text;
public:
    std::shared_ptr<ALittleScriptTextElement> GetText();
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

#endif // _ALITTLE_ALittleScriptStructOptionDecElement_H_
