#ifndef _ALITTLE_ALittleScriptClassBodyDecElement_H_
#define _ALITTLE_ALittleScriptClassBodyDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptClassElementDecElement;
class ALittleScriptStringElement;

class ALittleScriptClassBodyDecElement : public ABnfNodeElement
{
public:
    ALittleScriptClassBodyDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptClassBodyDecElement() { }

private:
    bool m_flag_ClassElementDec = false;
    std::vector<std::shared_ptr<ALittleScriptClassElementDecElement>> m_list_ClassElementDec;
public:
    const std::vector<std::shared_ptr<ALittleScriptClassElementDecElement>>& GetClassElementDecList();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptClassBodyDecElement_H_
