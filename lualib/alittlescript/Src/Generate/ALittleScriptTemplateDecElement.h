#ifndef _ALITTLE_ALittleScriptTemplateDecElement_H_
#define _ALITTLE_ALittleScriptTemplateDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptTemplatePairDecElement;
class ALittleScriptStringElement;

class ALittleScriptTemplateDecElement : public ABnfNodeElement
{
public:
    ALittleScriptTemplateDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptTemplateDecElement() { }

private:
    bool m_flag_TemplatePairDec = false;
    std::vector<std::shared_ptr<ALittleScriptTemplatePairDecElement>> m_list_TemplatePairDec;
public:
    const std::vector<std::shared_ptr<ALittleScriptTemplatePairDecElement>>& GetTemplatePairDecList();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptTemplateDecElement_H_
