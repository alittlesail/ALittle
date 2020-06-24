
#ifndef _ALITTLE_ABNFFILE_H_
#define _ALITTLE_ABNFFILE_H_

#include <string>
#include <vector>
#include <memory>

class ABnf;
using ABnfPtr = std::shared_ptr<ABnf>;
class ABnfProject;
class ABnfNodeElement;
using ABnfNodeElementPtr = std::shared_ptr<ABnfNodeElement>;
class ABnfElement;
using ABnfElementPtr = std::shared_ptr<ABnfElement>;

class ABnfFile
{
protected:
    // 工程信息
    ABnfProject* m_project = nullptr;
    // 解析器
    ABnfPtr m_abnf;
    // 文件路径
    std::string m_full_path;
    // 文本字符串
    std::string m_text;

public:
    ABnfFile(ABnfProject* project, const std::string& full_path, ABnfPtr abnf, const char* text, size_t len);

    // 设置文本
    void SetText(const char* text, size_t len);

    // 插入文本
    // it_line 从0开始算
    // it_char 从0开始算
    void InsertText(const char* content, size_t len, size_t it_line, size_t it_char);

    // 删除文本
    // it_line_start 从0开始算
    // it_char_start 从0开始算
    // it_line_end 从0开始算
    // it_char_end 从0开始算
    void DeleteText(size_t it_line_start, size_t it_char_start, size_t it_line_end, size_t it_char_end);

private:
    // utf8字符切割
    static int GetByteCountOfOneWord(unsigned char first_char);

public:
    // 格式化当前文件
    virtual std::string FormatDocument() { return ""; }
    // 编译当前文件
    virtual bool CompileDocument() { return false; }
    // 格式化当前项目
    virtual bool CompileProject() { return false; }
    // 触发保存文件
    virtual void OnSave() { }

public:
    // 获取文件路径
    inline const std::string& GetFullPath() const { return m_full_path; }
    // 获取文本
    inline const std::string& GetText() { return m_text; }
    // 获取文本长度
    inline int GetLength() { return static_cast<int>(m_text.size()); }
    // 获取文本子串
    inline std::string Substring(int start, int length) { return m_text.substr(start, length); }
    
public:
    // 获取根节点
    virtual ABnfNodeElementPtr GetRoot();
    // 更新解析
    virtual void UpdateAnalysis() { }
    // 清空解析信息
    virtual void ClearAnalysisError() { }
    // 更新错误信息
    virtual void UpdateError() { }
    // 清空错误信息
    virtual void ClearCheckError() { }

    // 获取当前所有错误节点
    virtual void GetAnalysisErrorMap(std::unordered_map<ABnfElement, std::string>& out) { }
    // 获取所有错误节点
    virtual void GetCheckErrorMap(std::unordered_map<ABnfElement, std::string>& out) { }
};

#endif // _ALITTLE_ABNFFILE_H_