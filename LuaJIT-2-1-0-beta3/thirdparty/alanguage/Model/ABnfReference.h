
#ifndef _ALITTLE_ABNFREFERENCE_H_
#define _ALITTLE_ABNFREFERENCE_H_

#include "ABnfGuess.h"
#include "ALanguageHelperInfo.h"

#include <memory>

class ABnfElement;
using ABnfElementPtr = std::shared_ptr<ABnfElement>;
using ABnfElementWeakPtr = std::weak_ptr<ABnfElement>;
class ABnfGuess;
using ABnfGuessPtr = std::shared_ptr<ABnfGuess>;

class ABnfReference
{
public:
    ABnfReference() { }
    virtual ~ABnfReference() { }

    // 检查错误
    virtual ABnfGuessError CheckError() { return nullptr; }

    // 获取类型
    virtual ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) { return nullptr; }

    // 返回多个表达式的类型
    virtual bool MultiGuessTypes() { return false; }

    // 获取缩进
    virtual int QueryDesiredIndent(int it_line, int it_char, ABnfElementPtr select) { return 0; }

    // 获取缩进
    virtual int QueryFormateIndent(int it_line, int it_char, ABnfElementPtr select) { return 0; }

    // 函数调用时的函数提示
    virtual bool QueryParamList(int& line_start, int& char_start, int& line_end, int& char_end, std::vector<ALanguageParameterInfo>& param_list) { return false; }

    // 获取参数下标
    virtual int QueryParamIndex(int it_line, int it_char, ABnfElementPtr select, int& start_offset) { return -1; }

    // 鼠标移入时，显示的快捷信息
    virtual void QueryQuickInfo(std::string& info) { }

    // 输入智能补全
    virtual bool QueryCompletion(ABnfElementPtr select, std::vector<ALanguageCompletionInfo>& list) { return false; }
    virtual bool QueryKeyWord(ABnfElementPtr select, std::vector<ALanguageCompletionInfo>& list) { return false; }

    // 配色
    virtual int QueryClassificationTag(bool& blur) { blur = false; return 0; }

    // 高亮拾取
    virtual bool PeekHighlightWord() { return false; }

    // 所有高亮
    virtual void QueryHighlightWordTag(std::vector<ALanguageHighlightWordInfo>& list) { }

    // 跳转
    virtual ABnfElementPtr GotoDefinition() { return nullptr; }

    // 是否可以跳转
    virtual bool CanGotoDefinition() { return true; }
};

#endif // _ALITTLE_ABNFREFERENCE_H_