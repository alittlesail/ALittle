
#ifndef _ALITTLE_ABNFFILE_H_
#define _ALITTLE_ABNFFILE_H_

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <unordered_map>

class ABnf;
class ABnfProject;
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
    std::map<ABnfElementPtr, std::string> m_analysis_error_map;
    std::map<ABnfElementPtr, std::string> m_check_error_map;
    std::unordered_map<int, std::vector<ALanguageColorInfo>> m_color_map;

    // 持有ABnfGuess的引用
    std::vector<ABnfGuessPtr> m_guess_cache;

public:
    ABnfFile(ABnfProject* project, const std::string& module_path, const std::string& full_path, const char* text, size_t len, bool in_ui);
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
    const std::vector<ALanguageColorInfo>* QueryColor(int version, int it_line);
    // 获取节点信息
    bool QueryInfo(int version, int it_line, int it_char, ALanguageQuickInfo& info);
    // 获取跳转
    bool QueryGoto(int version, int it_line, int it_char, ALanguageGotoInfo& info);
    // 获取提示
    bool QueryComplete(int version, int it_line, int it_char
        , std::vector<ALanguageCompletionInfo>& info_list
        , int& line_start, int& char_start, int& line_end, int& char_end);
    // 获取错误
    bool QueryError(int version, bool force, std::vector<ALanguageErrorInfo>& info_list);
    // 获取插入缩进
    int QueryDesiredIndent(int version, int it_line, int it_char);
    // 获取格式化缩进
    int QueryFormateIndent(int version, int it_line, int it_char);
    // utf8字符切割
    static int GetByteCountOfOneWord(unsigned char first_char);

public:
    // 移除内容
    virtual void OnRemove() {}
    // 添加ABnfGuess，为了持有这个对象的引用
    inline void AddGuessType(ABnfGuessPtr ptr) { m_guess_cache.push_back(ptr); }
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
    inline ABnfProject* GetProject() { return m_project; }
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

    // 清空错误信息
    inline void ClearAnalysisError() { m_analysis_error_map.clear(); }
    inline void ClearCheckError() { m_check_error_map.clear(); }
    inline bool HasError() const { return m_analysis_error_map.size() > 0 || m_check_error_map.size() > 0; }

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