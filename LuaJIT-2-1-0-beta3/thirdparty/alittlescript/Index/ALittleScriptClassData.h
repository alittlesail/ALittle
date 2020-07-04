
#ifndef _ALITTLE_ALITTLESCRIPTCLASSDATA_H_
#define _ALITTLE_ALITTLESCRIPTCLASSDATA_H_

#include <unordered_map>
#include <set>
#include <memory>

class ABnfElement;
enum ClassAccessType;
enum ClassAttrType;

class ALittleScriptClassData
{
private:
    // Key1:访问权限，Key2:属性类型，Key3:名称，Value:元素
    std::unordered_map<ClassAccessType, std::unordered_map<ClassAttrType, std::unordered_map<std::string, std::shared_ptr<ABnfElement>>>> m_element_map;

    // 获取元素集合    
    const std::unordered_map<std::string, std::shared_ptr<ABnfElement>>* GetElementMap(ClassAttrType attr_type, ClassAccessType access_type);

public:
    // 添加新元素
    void AddClassChildDec(std::shared_ptr<ABnfElement> dec);

    // 查找元素
    void FindClassAttrList(int access_level, ClassAttrType attr_type, const std::string& name, std::vector<std::shared_ptr<ABnfElement>>& result) const;
};

#endif // _ALITTLE_ALITTLESCRIPTCLASSDATA_H_
