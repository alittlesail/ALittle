
#ifndef _ALITTLE_ABNFPROJECTCLASS_H_
#define _ALITTLE_ABNFPROJECTCLASS_H_

#include "../../alanguage/Index/ABnfProject.h"
#include "ABnfFactoryClass.h"

#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>

class ABnfProjectClass : public ABnfProject
{
private:
    ABnfFactoryClass m_factory;

public:
    ABnfProjectClass(const std::string& full_path) : ABnfProject(full_path) {}
    virtual ~ABnfProjectClass() {}

    ABnfFactory& RefFactory() override { return m_factory; }
};

#endif // _ALITTLE_ABNFPROJECTCLASS_H_
