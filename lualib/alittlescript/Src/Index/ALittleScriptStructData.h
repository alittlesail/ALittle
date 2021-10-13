
#ifndef _ALITTLE_ALITTLESCRIPTSTRUCTDATA_H_
#define _ALITTLE_ALITTLESCRIPTSTRUCTDATA_H_

#include <unordered_map>
#include <set>
#include <memory>

class ALittleScriptStructVarDecElement;
class ABnfElement;

class ALittleScriptStructData
{
private:
    // Key:���ƣ�Value:��Ա
    std::unordered_map<std::string, std::shared_ptr<ALittleScriptStructVarDecElement>> m_element_map;

public:
    // �����Ԫ��
    void AddVarDec(const std::shared_ptr<ABnfElement>& dec, const std::shared_ptr<ABnfElement>& next_dec);

    // ����Ԫ��
    void FindVarDecList(const std::string& name, std::vector<std::shared_ptr<ALittleScriptStructVarDecElement>>& result) const;
};

#endif // _ALITTLE_ALITTLESCRIPTSTRUCTDATA_H_
