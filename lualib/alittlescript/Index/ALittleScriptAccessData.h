
#ifndef _ALITTLE_ALITTLESCRIPTACCESSDATA_H_
#define _ALITTLE_ALITTLESCRIPTACCESSDATA_H_

#include <unordered_map>
#include <set>
#include <memory>

#include "ALittleScriptDefine.h"

class ABnfElement;

class ALittleScriptAccessData
{
private:
	// Key1:元素类型，Key2:名称，Value:对应的元素集合
	std::unordered_map<ABnfElementType, std::unordered_map<std::string, std::set<std::shared_ptr<ABnfElement>>>> m_element_map;

public:
    // 获取集合
    const std::unordered_map<ABnfElementType, std::unordered_map<std::string, std::set<std::shared_ptr<ABnfElement>>>>& GetElementMap() const { return m_element_map; }

    // 添加新元素
    void AddNameDec(const std::shared_ptr<ABnfElement>& dec);

    // 查找元素
    void FindNameDecList(ABnfElementType type, const std::string& name, std::vector<std::shared_ptr<ABnfElement>>& result);

    // 移除元素
    void RemoveNameDec(const std::shared_ptr<ABnfElement>& dec);
};

#endif // _ALITTLE_ALITTLESCRIPTACCESSDATA_H_
