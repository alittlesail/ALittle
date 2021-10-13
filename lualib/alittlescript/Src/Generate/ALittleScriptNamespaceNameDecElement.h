#ifndef _ALITTLE_ALittleScriptNamespaceNameDecElement_H_
#define _ALITTLE_ALittleScriptNamespaceNameDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptIdElement;

class ALittleScriptNamespaceNameDecElement : public ABnfNodeElement
{
public:
    ALittleScriptNamespaceNameDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptNamespaceNameDecElement() { }

private:
    bool m_flag_Id = false;
    std::shared_ptr<ALittleScriptIdElement> m_cache_Id;
public:
    std::shared_ptr<ALittleScriptIdElement> GetId();
};

#endif // _ALITTLE_ALittleScriptNamespaceNameDecElement_H_
