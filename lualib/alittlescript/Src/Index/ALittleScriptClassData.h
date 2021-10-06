
#ifndef _ALITTLE_ALITTLESCRIPTCLASSDATA_H_
#define _ALITTLE_ALITTLESCRIPTCLASSDATA_H_

#include <unordered_map>
#include <memory>

#include "ALittleScriptDefine.h"

class ABnfElement;

class ALittleScriptClassData
{
private:
    // Key1:����Ȩ�ޣ�Key2:�������ͣ�Key3:���ƣ�Value:Ԫ��
    std::unordered_map<ClassAccessType, std::unordered_map<ClassAttrType, std::unordered_map<std::string, std::shared_ptr<ABnfElement>>>> m_element_map;

    // ��ȡԪ�ؼ���    
    const std::unordered_map<std::string, std::shared_ptr<ABnfElement>>* GetElementMap(ClassAttrType attr_type, ClassAccessType access_type) const;

public:
    // �����Ԫ��
    void AddClassChildDec(std::shared_ptr<ABnfElement> dec, const std::shared_ptr<ABnfElement>& pre_dec, const std::shared_ptr<ABnfElement>& next_dec);

    // ����Ԫ��
    void FindClassAttrList(int access_level, ClassAttrType attr_type, const std::string& name, std::vector<std::shared_ptr<ABnfElement>>& result) const;
};

#endif // _ALITTLE_ALITTLESCRIPTCLASSDATA_H_
