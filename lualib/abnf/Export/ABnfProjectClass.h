
#ifndef _ALITTLE_ABNFPROJECTCLASS_H_
#define _ALITTLE_ABNFPROJECTCLASS_H_

#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>

#include "abnf/Src/Index/ABnfFactoryClass.h"
#include "alanguage/Export/ABnfProjectExport.h"

class ABnfProjectClass : public ABnfProjectExport
{
private:
    ABnfFactoryClass m_factory;

public:
    ABnfProjectClass() {}
    virtual ~ABnfProjectClass() {}

    ABnfFactory& RefFactory() override { return m_factory; }

    void Generate(const std::string& full_path, int query_id, int version, const std::string& target_path, const std::string& language_name);
};

#endif // _ALITTLE_ABNFPROJECTCLASS_H_
