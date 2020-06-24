
#ifndef _ALITTLE_ABNFREFERENCE_H_
#define _ALITTLE_ABNFREFERENCE_H_

#include "ABnfGuess.h"
#include "ALanguageHelperInfo.h"

#include <memory>

class ABnfReference
{
public:
    ABnfReference() { }
    virtual ~ABnfReference() {}

    // 检查错误
    virtual void CheckError(ABnfGuessError& error) { }

    // 获取类型
    virtual void GuessTypes(std::vector<ABnfGuess>& guess_list, ABnfGuessError& error) { }

    // 返回多个表达式的类型
    virtual bool MultiGuessTypes() { return false; }

    // 获取缩进
    virtual int GetDesiredIndentation(int offset, ABnfElementPtr select) { return 0; }

    // 获取缩进
    virtual int GetFormatIndentation(int offset, ABnfElementPtr select) { return 0; }

    // 函数调用时的函数提示
    virtual void QuerySignatureHelp(int& start, int& length, ALanguageSignatureInfo& info)
    {
        start = 0;
        length = 0;
    }

    // 鼠标移入时，显示的快捷信息
    virtual void QueryQuickInfo(std::string& info) { }

    // 输入智能补全
    virtual bool QueryCompletion(int offset, std::vector<ALanguageCompletionInfo>& list) { return false; }

    // 配色
    virtual void QueryClassificationTag(bool& blur, std::string& tag) { blur = false; }

    // 高亮拾取
    virtual bool PeekHighlightWord() { return false; }

    // 所有高亮
    virtual void QueryHighlightWordTag(std::vector<ALanguageHighlightWordInfo>& list) { }

    // 跳转
    virtual ABnfElementPtr GotoDefinition() { return nullptr; }

    // 是否可以跳转
    virtual bool CanGotoDefinition() { return true; }
};

template <typename T>
class ABnfReferenceTemplate : public ABnfReference
{
protected:
    std::shared_ptr<T> m_element;

public:
    ABnfReferenceTemplate(ABnfElementPtr element) { m_element = std::dynamic_pointer_cast<T>(element); }
};

#endif // _ALITTLE_ABNFREFERENCE_H_