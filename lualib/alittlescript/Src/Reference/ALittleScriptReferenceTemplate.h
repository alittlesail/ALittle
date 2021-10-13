
#ifndef _ALITTLE_ALITTLESCRIPTREFERENCETEMPLATE_H_
#define _ALITTLE_ALITTLESCRIPTREFERENCETEMPLATE_H_

#include "alanguage/Src/Model/ABnfReference.h"

#include <memory>

class ALittleScriptIndex;

class ALittleScriptReference : public ABnfReference
{
private:
    int m_format_indent = -1;
    int m_desire_indent = -1;
    ABnfElementWeakPtr m_ref_element;

public:
    ALittleScriptReference(const ABnfElementPtr& p_element);
    virtual ~ALittleScriptReference() = default;

    // 鼠标移入时，显示的快捷信息
    virtual void QueryQuickInfo(std::string& info) override;

    virtual int QueryDesiredIndent(int it_line, int it_char, const ABnfElementPtr& select) override;

    virtual int QueryFormatIndent(int it_line, int it_char, const ABnfElementPtr& select) override;
    virtual int QueryParamIndex(int it_line, int it_char, const ABnfElementPtr& select, int& start_offset) override;

    virtual bool QueryKeyWord(const ABnfElementPtr& select, std::vector<ALanguageCompletionInfo>& list) override;

    // 函数调用时的函数提示
    virtual bool QueryParamList(int& line_start, int& char_start, int& line_end, int& char_end, std::vector<ALanguageParameterInfo>& param_list) override;

    ALittleScriptIndex* GetIndex() const;
};

enum ALittleScriptColorType
{
    COMMENT = 1,
    DEFINE_NAME = 2,
    VAR_NAME = 3,
    CUSTOM_NAME = 4,
    CTRL_KEYWORD = 5,
    KEYWORD = 6,
    METHOD_NAME = 7,
    DEFAULT = 8,
    TEXT = 9,
};

enum ALittleScriptIconType
{
    CLASS = 1,
    STRUCT = 2,
    PROPERTY = 3,
    NAMESPACE = 4,
    TEMPLATE = 5,
    ENUM = 6,
    LANGUAGE = 7,
    GLOBAL_METHOD = 8,
    MEMBER_METHOD = 9,
    FIELD_METHOD = 10,
    STATIC_METHOD = 11,
    INSTANCE = 12,
    PARAM = 13,
    VARIABLE = 14,
};

template <typename T>
class ALittleScriptReferenceTemplate : public ALittleScriptReference
{
protected:
    std::weak_ptr<T> m_element;

public:
    ALittleScriptReferenceTemplate(ABnfElementPtr p_element) : ALittleScriptReference(p_element) { m_element = std::dynamic_pointer_cast<T>(p_element); }
    virtual ~ALittleScriptReferenceTemplate() {}
};

#endif // _ALITTLE_ALITTLESCRIPTREFERENCETEMPLATE_H_