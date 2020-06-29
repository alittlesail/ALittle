
#ifndef _ALITTLE_ABNFFILE_H_
#define _ALITTLE_ABNFFILE_H_

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <unordered_map>
extern "C" {
#include "../alanguage.h"
}

class ABnf;
class ABnfProject;
class ABnfNodeElement;
using ABnfNodeElementPtr = std::shared_ptr<ABnfNodeElement>;
class ABnfElement;
using ABnfElementPtr = std::shared_ptr<ABnfElement>;
struct ABnfQueryColor;

class ABnfFile
{
protected:
    // 根节点
    ABnfNodeElementPtr m_root;
    // 工程信息
    ABnfProject* m_project = nullptr;
    // 解析器
    ABnf* m_abnf = nullptr;
    // 文件路径
    std::string m_full_path;
    // 文本字符串
    std::string m_text;

    int m_version = 0;
    // 收集错误
    std::map<ABnfElementPtr, std::string> m_analysis_error_map;
    std::map<ABnfElementPtr, std::string> m_check_error_map;
    std::unordered_map<int, std::vector<struct ABnfQueryColor>> m_color_map;

public:
    ABnfFile(ABnfProject* project, const std::string& full_path, ABnf* abnf, const char* text, size_t len);
    virtual ~ABnfFile();

    // 设置文本
    void SetText(const char* text, size_t len);

    // 插入文本
    // it_line 从0开始算
    // it_char 从0开始算
    void InsertText(const char* content, size_t len, int it_line, int it_char);

    // 删除文本
    // it_line_start 从0开始算
    // it_char_start 从0开始算
    // it_line_end 从0开始算
    // it_char_end 从0开始算
    void DeleteText(int it_line_start, int it_char_start, int it_line_end, int it_char_end);

    // 获取颜色
    // it_line 从0开始算
    const std::vector<struct ABnfQueryColor>* QueryColor(int version, int it_line);
    // 获取节点信息
    bool QueryInfo(int version, int it_line, int it_char
        , std::string& info, int& line_start, int& char_start, int& line_end, int& char_end);

    // utf8字符切割
    static int GetByteCountOfOneWord(unsigned char first_char);

private:
    // 解析一条龙
    void AnalysisText(int version);

public:
    // 获取文件路径
    inline const std::string& GetFullPath() const { return m_full_path; }
    // 获取工程信息
    inline const ABnfProject* GetProjectInfo() { return m_project; }
    // 获取文本
    inline const std::string& GetText() { return m_text; }
    // 获取文本长度
    inline int GetLength() { return static_cast<int>(m_text.size()); }
    // 获取文本子串
    inline std::string Substring(int start, int length) { return m_text.substr(start, length); }
    
public:
    // 获取根节点
    ABnfNodeElementPtr GetRoot() { return m_root; }
    
public:
    // 更新解析
    virtual void UpdateAnalysis() { }
    // 更新错误信息
    virtual void UpdateError() { }

    // 清空错误信息
    inline void ClearAnalysisError() { m_analysis_error_map.clear(); }
    inline void ClearCheckError() { m_check_error_map.clear(); }

    // 获取所有错误节点
    inline const std::map<ABnfElementPtr, std::string>& GetAnalysisErrorMap() { return m_analysis_error_map; }
    inline const std::map<ABnfElementPtr, std::string>& GetCheckErrorMap() { return m_check_error_map; }

    // 添加错误节点
    inline void AddAnalysisErrorInfo(ABnfElementPtr element, const std::string& error) { if (element == nullptr) return; m_analysis_error_map[element] = error; }
    inline void AddCheckErrorInfo(ABnfElementPtr element, const std::string& error) { if (element == nullptr) return; m_check_error_map[element] = error; }

    // 收集语法着色
    void CollectColor(ABnfElementPtr element, bool blur);
    // 收集语法错误
    void CollectError(ABnfElementPtr element);
    // 收集语义错误
    void AnalysisError(ABnfElementPtr element);
};

#endif // _ALITTLE_ABNFFILE_H_