
#ifndef _ALITTLE_ALITTLESCRIPTENUMDATA_H_
#define _ALITTLE_ALITTLESCRIPTENUMDATA_H_

#include <unordered_map>
#include <set>
#include <memory>

class ALittleScriptEnumVarDecElement;
class ABnfElement;

class ALittleScriptEnumData
{
private:
    // Key:名称，Value:成员
    std::unordered_map<std::string, std::shared_ptr<ALittleScriptEnumVarDecElement>> m_element_map;

public:
    // 添加新元素
    void AddVarDec(const std::shared_ptr<ABnfElement>& dec, const std::shared_ptr<ABnfElement>& next_dec);

    // 查找元素
    void FindVarDecList(const std::string& name, std::vector<std::shared_ptr<ALittleScriptEnumVarDecElement>>& result) const;
};

#endif // _ALITTLE_ALITTLESCRIPTENUMDATA_H_
