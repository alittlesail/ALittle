
#ifndef _ALITTLE_ABNFFILE_H_
#define _ALITTLE_ABNFFILE_H_

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class ABnf;
class ABnfProject;
class ABnfRuleInfo;
class ABnfNodeElement;
using ABnfNodeElementPtr = std::shared_ptr<ABnfNodeElement>;
class ABnfElement;
using ABnfElementPtr = std::shared_ptr<ABnfElement>;
class ABnfGuess;
using ABnfGuessPtr = std::shared_ptr<ABnfGuess>;

struct ALanguageQuickInfo;
struct ALanguageColorInfo;
struct ALanguageGotoInfo;
struct ALanguageCompletionInfo;
struct ALanguageErrorInfo;
struct ALanguageParameterInfo;

class ABnfFile
{
protected:
    // 根节点
    ABnfNodeElementPtr m_root;
    // 工程信息
    ABnfProject* m_project = nullptr;
    // 文件路径
    std::string m_full_path;
    // 模块路径
    std::string m_module_path;
    // 文本字符串
    std::string m_text;
    // 是否是ui创建
    bool m_in_ui = true;

    int m_analysis_version = -1;
    int m_error_version = -1;
    int m_color_version = -1;
    // 收集错误
    std::unordered_map<ABnfElementPtr, std::string> m_analysis_error_map;
    std::unordered_map<ABnfElementPtr, std::string> m_check_error_map;
    std::unordered_map<int, std::vector<ALanguageColorInfo>> m_color_map;

    // 持有ABnfGuess的引用
    std::vector<ABnfGuessPtr> m_guess_cache;

public:
    ABnfFile(ABnfProject* project, const std::string& module_path, const std::string& full_path, const char* text, size_t len, bool in_ui);
    virtual ~ABnfFile() = default;

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

    // 是否包含改文本
    bool ContainText(const std::string& text) const;

    // 获取颜色
    // it_line 从0开始算
    const std::vector<ALanguageColorInfo>* QueryColor(int version, int it_line);
    // 获取节点信息
    bool QueryInfo(int version, int it_line, int it_char, ALanguageQuickInfo& info);
    // 获取跳转
    bool QueryGoto(int version, int it_line, int it_char, ALanguageGotoInfo& info);
    // 获取提示
    bool QueryComplete(int version, int it_line, int it_char
        , std::vector<ALanguageCompletionInfo>& info_list
        , int& line_start, int& char_start, int& line_end, int& char_end);
    // 获取参数列表
    bool QueryParamList(int version, int it_line, int it_char
        , std::vector<ALanguageParameterInfo>& param_list
        , int& line_start, int& char_start, int& line_end, int& char_end);
    // 获取参数下标
    int QueryParamIndex(int version, int it_line, int it_char, int* start_offset);
    // 获取错误
    bool QueryError(int version, bool force, std::vector<ALanguageErrorInfo>& info_list);
    // 获取插入缩进
    int QueryDesiredIndent(int version, int it_line, int it_char);
    // 获取格式化缩进
    int QueryFormatIndent(int version, int it_line, int it_char);
    // 查询自动匹配
    bool QueryAutoPair(int version, int it_line, int it_char, const std::string& left_pair, const std::string& right_pair);
    // utf8字符切割
    static int GetByteCountOfOneWord(unsigned char first_char);

public:
    // 移除内容
    virtual void OnRemove() {}
    // 添加ABnfGuess，为了持有这个对象的引用
    inline void AddGuessType(const ABnfGuessPtr& ptr) { m_guess_cache.push_back(ptr); }
    // 清空引用
    inline void ClearGuessType() { m_guess_cache.resize(0); }

public:
    // 解析文本
    void AnalysisText(int version);
    // 解析错误
    void AnalysisError(int version, bool force);
    // 解析着色
    void AnalysisColor(int version);

public:
    // 获取文件路径
    inline const std::string& GetFullPath() const { return m_full_path; }
    // 获取文件路径
    inline const std::string& GetModulePath() const { return m_module_path; }
    // 获取工程信息
    inline ABnfProject* GetProject() const { return m_project; }
    // 获取文本
    inline const std::string& GetText() const { return m_text; }
    // 获取文本长度
    inline int GetLength() const { return static_cast<int>(m_text.size()); }
    // 获取文本子串
    inline std::string Substring(int start, int length) const { return m_text.substr(start, length); }
    
public:
    // 获取根节点
    ABnfNodeElementPtr GetRoot() const { return m_root; }
    
public:
    // 更新解析
    virtual void UpdateAnalysis();
    // 强制错误解析
    virtual void OnForceAnalysisError() {}

    // 清空错误信息
    inline void ClearAnalysisError() { m_analysis_error_map.clear(); }
    inline void ClearCheckError() { m_check_error_map.clear(); }
    inline bool HasError() const { return m_analysis_error_map.size() > 0 || m_check_error_map.size() > 0; }

    // 获取所有错误节点
    inline const std::unordered_map<ABnfElementPtr, std::string>& GetAnalysisErrorMap() const { return m_analysis_error_map; }
    inline const std::unordered_map<ABnfElementPtr, std::string>& GetCheckErrorMap() const { return m_check_error_map; }

    // 添加错误节点
    inline void AddAnalysisErrorInfo(const ABnfElementPtr& element, const std::string& error) { if (element == nullptr) return; m_analysis_error_map[element] = error; }
    inline void AddCheckErrorInfo(const ABnfElementPtr& element, const std::string& error) { if (element == nullptr) return; m_check_error_map[element] = error; }

    // 收集语法着色
    void CollectColor(const ABnfElementPtr& element, const std::unordered_map<std::string, ABnfRuleInfo*>& rule_set, bool blur);
    // 收集语法错误
    void CollectError(const ABnfElementPtr& element);
    // 收集语义错误
    void AnalysisError(const ABnfElementPtr& element);
};

#endif