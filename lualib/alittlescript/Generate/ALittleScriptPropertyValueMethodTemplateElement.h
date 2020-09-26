#ifndef _ALITTLE_ALittleScriptPropertyValueMethodTemplateElement_H_
#define _ALITTLE_ALittleScriptPropertyValueMethodTemplateElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptAllTypeElement;
class ALittleScriptStringElement;

class ALittleScriptPropertyValueMethodTemplateElement : public ABnfNodeElement
{
public:
    ALittleScriptPropertyValueMethodTemplateElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptPropertyValueMethodTemplateElement() { }

private:
    bool m_flag_AllType = false;
    std::vector<std::shared_ptr<ALittleScriptAllTypeElement>> m_list_AllType;
public:
    const std::vector<std::shared_ptr<ALittleScriptAllTypeElement>>& GetAllTypeList();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptPropertyValueMethodTemplateElement_H_
