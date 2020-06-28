
#ifndef _ALITTLE_ABNFLEAFELEMENT_H_
#define _ALITTLE_ABNFLEAFELEMENT_H_

#include "ABnfElement.h"

class ABnfLeafElement : public ABnfElement
{
protected:
    std::string m_value;                   // 节点值

private:
    int m_end_line = -1;
    int m_end_col = -1;

    void CalcEnd();

public:
    ABnfLeafElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& value);
    virtual ~ABnfLeafElement() {}

    bool IsLeafOrHasChildOrError() override { return true; }

    // 获取节点长度
    int GetEnd() override { return m_start + static_cast<int>(m_value.size()); }

    // 获取结束位置是第几行
    int GetEndLine() override { if (m_end_line < 0) CalcEnd(); return m_end_line; }

    // 获取结束位置是第几列
    int GetEndCol() override { if (m_end_col < 0) CalcEnd(); return m_end_col; }

    // 获取节点文本
    const std::string& GetValue() { return m_value; }

    // 根据偏移位置，获取期望的元素
    ABnfElementPtr GetException(int offset) override;
};

#endif // _ALITTLE_ABNFLEAFELEMENT_H_