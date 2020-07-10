
#ifndef _ALITTLE_ALITTLESCRIPTTRANSLATION_H_
#define _ALITTLE_ALITTLESCRIPTTRANSLATION_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>

#include "../../alanguage/Model/ABnfElement.h"
#include "../../alanguage/Model/ABnfGuess.h"

struct StructReflectInfo
{
    std::string content;        // 最终的结果
    bool generate = false;         // 是否生成

    std::string name;           // 带命名域的结构体名
    std::string ns_name;        // 命名域
    std::string rl_name;        // 不再命名域的结构体名
    int hash_code = 0;          // 哈希值
    std::vector<std::string> name_list;    // 成员名列表
    std::vector<std::string> type_list;    // 类型名列表
    std::unordered_map<std::string, std::string> option_map;    // 附加信息列表
};

class ALittleScriptNamespaceElementDecElement;

class ALittleScriptTranslation
{
protected:
    // 当前文件命名域
    std::string m_namespace_name;
    // 当前模块所在工程路径
    std::string m_module_path;
    // 当前文件路径
    std::string m_file_path;

protected:
    // 定义依赖
    std::unordered_set<std::string> m_define_rely;
    // 运行依赖
    std::unordered_set<std::string> m_run_rely;
    // 当前是否是定义依赖
    bool m_is_define_relay = false;

public:
    static std::shared_ptr<ALittleScriptTranslation> CreateTranslation(const std::string& language);

    ALittleScriptTranslation() {}
    virtual ~ALittleScriptTranslation() {}

protected:
    void AddRelay(ABnfElementPtr element);

    // 检查语法错误
    ABnfGuessError CheckErrorElement(ABnfElementPtr element, bool full_check);

public:
    virtual ABnfGuessError Generate(ABnfFile* file, bool full_check);

protected:
    virtual ABnfGuessError GenerateRoot(const std::vector<std::shared_ptr<ALittleScriptNamespaceElementDecElement>>& element_list, std::string& content)
    {
        content = "";
        return ABnfGuessError(nullptr, "未实现生成代码");
    }

    virtual std::string GetExt()
    {
        return "";
    }

public:
    static int StructReflectSort(const StructReflectInfo* a, const StructReflectInfo* b)
    {
        return a->hash_code - b->hash_code;
    }
};

#endif // _ALITTLE_ALITTLESCRIPTTRANSLATION_H_