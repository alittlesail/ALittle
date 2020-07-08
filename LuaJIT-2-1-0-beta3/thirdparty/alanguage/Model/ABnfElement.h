
#ifndef _ALITTLE_ABNFELEMENT_H_
#define _ALITTLE_ABNFELEMENT_H_

#include <memory>
#include <string>
#include <vector>

#include "ABnfGuess.h"

class ABnfFactory;
class ABnfFile;
class ABnfReference;
class ABnfElement;
using ABnfElementPtr = std::shared_ptr<ABnfElement>;
using ABnfElementWeakPtr = std::weak_ptr<ABnfElement>;

class ABnfGuess;
using ABnfGuessPtr = std::shared_ptr<ABnfGuess>;

class ABnfElement : public std::enable_shared_from_this<ABnfElement>
{
protected:
    ABnfFactory* m_factory = nullptr;             // 对象工厂
    ABnfFile* m_file = nullptr;           // 所在的解析
    ABnfElementWeakPtr m_parent;          // 父节点
    ABnfReference* m_reference = nullptr;         // 引用

    std::string m_element_text;         // 文本缓存    
    int m_start = 0;                       // 文本偏移
    int m_line = 1;                        // 所在行
    int m_col = 1;                         // 所在列

public:
    ABnfElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset);
    virtual ~ABnfElement();

    virtual bool IsLeafOrHasChildOrError() { return false; }
    virtual bool IsError() { return false; }
    virtual bool IsNode() { return false; }

    // 获取引用
    ABnfReference* GetReference();
    // 获取类型
    virtual ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list);

    // 获取第一个类型
    virtual ABnfGuessError GuessType(ABnfGuessPtr& out);

    // 获取解析细节
    inline ABnfFile* GetFile() { return m_file; }
    // 获取文件全路径
    const std::string& GetFullPath();
    // 获取所在工程路径
    const std::string& GetProjectPath();

    // 设置父节点
    void SetParent(ABnfElementPtr parent);
    ABnfElementPtr GetParent();

    // 当前节点是否和指定范围有交集
    bool IntersectsWith(int start, int end);

    // 根据偏移位置，获取期望的元素
    virtual ABnfElementPtr GetException(int offset) { return nullptr; }
    // 根据行列，获取期望的元素
    virtual ABnfElementPtr GetException(int it_line, int it_char) { return nullptr; }

    // 获取节点偏移
    virtual int GetStart() { return m_start; }

    // 获取节点长度
    virtual int GetEnd() { return m_start; }

    // 获取节点长度
    virtual int GetLength() { return GetEnd() - GetStart(); }

    virtual int GetLengthWithoutError() { return GetEnd() - GetStart(); }

    // 获取支节点类型
    virtual const std::string& GetNodeType();
    // 获取叶结点类型
    virtual const std::string& GetLeafType();

    // 获取文本
    virtual const std::string& GetElementText();

    // 获取去掉单引号对和双引号对之后的字符串
    virtual std::string GetElementString();

    // 获取当前是第几行，从1开始算
    virtual int GetStartLine() { return m_line; }

    // 获取当前是第几列，从1开始算
    virtual int GetStartCol() { return m_col; }
    // 计算indent
    virtual int GetStartIndent();

    // 获取结束位置是第几列，从1开始算
    virtual int GetEndLine() { return m_line; }
    // 获取结束位置是第几行，从1开始算
    virtual int GetEndCol() { return m_col; }

    // 向前找到第一个\n并且，中间没有空格和\t
    virtual int FindForwardFirstEnterAndHaveNotSpaceOrTab();
};

#endif // _ALITTLE_ABNFELEMENT_H_