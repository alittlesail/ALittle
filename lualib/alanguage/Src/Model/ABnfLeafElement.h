
#ifndef _ALITTLE_ABNFLEAFELEMENT_H_
#define _ALITTLE_ABNFLEAFELEMENT_H_

#include "ABnfElement.h"

class ABnfLeafElement : public ABnfElement
{
protected:
    std::string m_value;                   // �ڵ�ֵ

private:
    int m_end_line = -1;
    int m_end_col = -1;

    void CalcEnd();

public:
    ABnfLeafElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& value);
    virtual ~ABnfLeafElement() = default;

    bool IsLeafOrHasChildOrError() override { return true; }

    // ��ȡ�ڵ㳤��
    int GetEnd() override { return m_start + static_cast<int>(m_value.size()); }

    // ��ȡ����λ���ǵڼ���
    int GetEndLine() override { if (m_end_line < 0) CalcEnd(); return m_end_line; }

    // ��ȡ����λ���ǵڼ���
    int GetEndCol() override { if (m_end_col < 0) CalcEnd(); return m_end_col; }

    // ��ȡ�ڵ��ı�
    const std::string& GetValue() const { return m_value; }

    // ����ƫ��λ�ã���ȡ������Ԫ��
    ABnfElementPtr GetException(int offset) override;

    // �������У���ȡ������Ԫ��
    ABnfElementPtr GetException(int it_line, int it_char) override;
};

#endif // _ALITTLE_ABNFLEAFELEMENT_H_