
#ifndef _ALITTLE_ABNFFILECLASS_H_
#define _ALITTLE_ABNFFILECLASS_H_

#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>

#include "alanguage/Src/Index/ABnfFile.h"

class ABnfFileClass : public ABnfFile
{
private:
    // ������ӳ���������
    std::unordered_map<std::string, std::map<ABnfNodeElementPtr, std::string>> m_rule;
    // ��ȡ����
    std::unordered_map<std::string, std::unordered_set<ABnfNodeElementPtr>> m_index;

public:
	ABnfFileClass(ABnfProject* project, const std::string& full_path, const char* text, size_t len, bool in_ui);
    virtual ~ABnfFileClass() = default;

    inline const std::unordered_map<std::string, std::map<ABnfNodeElementPtr, std::string>>& GetRuleSet() const { return m_rule; }
    inline const std::unordered_map<std::string, std::unordered_set<ABnfNodeElementPtr>>& GetIndex() const { return m_index; }

    // ���·�������
    void UpdateAnalysis() override;
    // �ռ�����
    void CollectIndex(const ABnfNodeElementPtr& node);
    // �ռ�����ID
    void CollectRule();

public:
    // ����C++����
    std::string Generate(int version, const std::string& target_path, const std::string& language_name);

private:
    struct CollectCompileInfo
    {
        // 0 ��ʾû�У�1��ʾһ��������1��ʾ���
        std::unordered_map<std::string, int> id_map;
        int has_string = 0;
        int has_regex = 0;
        int has_key = 0;
    };
    void CollectCompile(const ABnfElementPtr& element, CollectCompileInfo& info, bool multi) const;
};

#endif // _ALITTLE_ABNFFILECLASS_H_
