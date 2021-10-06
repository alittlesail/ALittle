#ifndef _ALITTLE_ALittleScriptTemplatePairDecElement_H_
#define _ALITTLE_ALittleScriptTemplatePairDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptTemplateNameDecElement;
class ALittleScriptTemplateExtendsDecElement;

class ALittleScriptTemplatePairDecElement : public ABnfNodeElement
{
public:
    ALittleScriptTemplatePairDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptTemplatePairDecElement() { }

private:
    bool m_flag_TemplateNameDec = false;
    std::shared_ptr<ALittleScriptTemplateNameDecElement> m_cache_TemplateNameDec;
public:
    std::shared_ptr<ALittleScriptTemplateNameDecElement> GetTemplateNameDec();
private:
    bool m_flag_TemplateExtendsDec = false;
    std::shared_ptr<ALittleScriptTemplateExtendsDecElement> m_cache_TemplateExtendsDec;
public:
    std::shared_ptr<ALittleScriptTemplateExtendsDecElement> GetTemplateExtendsDec();
};

#endif // _ALITTLE_ALittleScriptTemplatePairDecElement_H_
