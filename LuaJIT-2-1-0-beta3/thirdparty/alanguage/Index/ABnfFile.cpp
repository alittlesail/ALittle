
#include "ABnfFile.h"
#include "../Model/ABnf.h"
#include "../Model/ABnfNodeElement.h"

ABnfFile::ABnfFile(ABnfProject* project, const std::string& full_path, ABnf* abnf, const char* text, size_t len)
{
    m_project = project;
    m_abnf = abnf;
    m_full_path = full_path;
    SetText(text, len);
}

// 设置文本
void ABnfFile::SetText(const char* text, size_t len)
{
    m_text.assign(text, len);
}

// 插入文本
// it_line 从0开始算
// it_char 从0开始算
void ABnfFile::InsertText(const char* content, size_t len, int it_line, int it_char)
{
    int cur_line = 0;
    int cur_char = 0;

    int index = 0;
    while (index < m_text.size())
    {
        if (cur_line == it_line && cur_char == it_char) break;

        int byte_count = GetByteCountOfOneWord(m_text[index]);
        if (byte_count == 1 && m_text[index] == '\n')
        {
            ++cur_line;
            cur_char = 0;
        }
        else
        {
            ++cur_char;
        }

        index += byte_count;
    }

    m_text.insert(index, content, len);
}

// 删除文本
// it_line_start 从0开始算
// it_char_start 从0开始算
// it_line_end 从0开始算
// it_char_end 从0开始算
void ABnfFile::DeleteText(int it_line_start, int it_char_start, int it_line_end, int it_char_end)
{
    bool swap = false;
    if (it_line_start > it_line_end)
        swap = true;
    else if (it_line_start == it_line_end)
        swap = it_char_start > it_char_end;
    if (swap)
    {
        std::swap(it_line_start, it_line_end);
        std::swap(it_char_start, it_char_end);
    }

    int cur_line = 0;
    int cur_char = 0;

    int start_index = 0;
    while (start_index < m_text.size())
    {
        if (cur_line == it_line_start && cur_char == it_char_start) break;

        int byte_count = GetByteCountOfOneWord(m_text[start_index]);
        if (byte_count == 1 && m_text[start_index] == '\n')
        {
            ++cur_line;
            cur_char = 0;
        }
        else
        {
            ++cur_char;
        }

        start_index += byte_count;
    }

    int end_index = start_index;
    while (end_index < m_text.size())
    {
        int byte_count = GetByteCountOfOneWord(m_text[end_index]);

        if (cur_line == it_line_end && cur_char == it_char_end)
        {
            end_index += byte_count;
            break;
        }

        if (byte_count == 1 && m_text[end_index] == '\n')
        {
            ++cur_line;
            cur_char = 0;
        }
        else
        {
            ++cur_char;
        }

        end_index += byte_count;
    }

    m_text.erase(start_index, end_index - start_index);
}

int ABnfFile::GetByteCountOfOneWord(unsigned char first_char)
{
    unsigned char temp = 0x80;
    int num = 0;

    unsigned char char_value = first_char;

    if (char_value < 0x80) // ascii code.(0-127)
        return 1;
    while (temp & char_value)
    {
        ++num;
        temp = temp >> 1;
    }

    return num;
}

// 获取根节点
ABnfNodeElementPtr ABnfFile::GetRoot() { return nullptr; }
