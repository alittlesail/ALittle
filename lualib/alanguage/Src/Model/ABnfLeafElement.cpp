
#include "ABnfLeafElement.h"

#include "alanguage/Src/Index/ABnfFile.h"

ABnfLeafElement::ABnfLeafElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& value)
    : ABnfElement(factory, file, line, col, offset)
{
    m_value = value;
}

// 根据偏移位置，获取期望的元素
ABnfElementPtr ABnfLeafElement::GetException(int offset)
{
    if (offset < GetStart()) return nullptr;
    if (offset >= GetEnd()) return nullptr;
    return shared_from_this();
}

// 根据偏移位置，获取期望的元素
ABnfElementPtr ABnfLeafElement::GetException(int it_line, int it_char)
{
    const auto start_line = GetStartLine();
    const auto end_line = GetEndLine();

    if (start_line > it_line) return nullptr;
    if (end_line < it_line) return nullptr;

    if (start_line == it_line && GetStartCol() > it_char) return nullptr;
    if (end_line == it_line && GetEndCol() <= it_char) return nullptr;

    return shared_from_this();
}

void ABnfLeafElement::CalcEnd()
{
    m_end_line = m_line;
    m_end_col = m_col;

    for (size_t i = 0; i < m_value.size(); ++i)
    {
        const char value = m_file->GetText()[m_start + i];
        if (value == '\n')
        {
            m_end_col = 1;
            ++m_end_line;
        }
        else
        {
            ++m_end_col;
        }
    }
}
