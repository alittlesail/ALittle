
#ifndef _ALITTLE_ABNFERRORELEMENT_H_
#define _ALITTLE_ABNFERRORELEMENT_H_

#include <string>

#include "ABnfElement.h"

class ABnfErrorElement : public ABnfElement
{
private:
    std::string m_value;                   // �ڵ�ֵ
    ABnfElementPtr m_target;               // ����Ҫƥ���Ŀ��Ԫ��

public:
    ABnfErrorElement(ABnfFactory* factory, ABnfFile* file
        , int line, int col, int offset
        , const std::string& value, const ABnfElementPtr& target)
        : ABnfElement(factory, file, line, col, offset)
    {
        m_value = value;
        m_target = target;
    }
    virtual ~ABnfErrorElement() = default;

    bool IsLeafOrHasChildOrError() override { return true; }
    bool IsError() override { return true; }

    ABnfElementPtr GetTargetElement() const { return m_target; }

    // ��ýڵ��������
    inline const std::string& GetValue() const { return m_value; }
    // ����ƫ��λ�ã���ȡ������Ԫ��
    ABnfElementPtr GetException(int offset) override
    {
        if (offset == GetStart()) return shared_from_this();
        return nullptr;
    }
    // �������У���ȡ������Ԫ��
    ABnfElementPtr GetException(int it_line, int it_char) override
    {
        if (it_line == GetStartLine() && it_char == GetStartCol()) return shared_from_this();
        return nullptr;
    }
};

#endif