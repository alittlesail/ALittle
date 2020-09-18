
#include "TextEdit.h"

#include "ALittle/LibCommon/Helper/LogHelper.h"
#include "ALittle/LibCommon/Helper/StringHelper.h"
extern "C" {
#include "ALittle/LibCommon/ThirdParty/utf8/utf8.h"
}

#include "ALittle/LibClient/RenderSystem/DisplaySystem.h"
#include "ALittle/LibClient/RenderSystem/RenderSystem.h"
#include "ALittle/LibClient/Helper/FontHelper.h"

namespace ALittle
{

int TextEdit::GetRealHeight()
{
	if (m_linechar_list.size() == 0) return 0;
	if (m_linechar_list.size() == 1 && m_linechar_list.back().char_list.size() == 1) return 0;
	return m_linechar_list.back().acc_height;
}

int TextEdit::GetLineWidth(int line_index)
{
	if (line_index < 0) return 0;
	if (line_index >= (int)m_linechar_list.size()) return 0;
	LineCharInfoList::iterator it = m_linechar_list.begin();
	while (line_index)
	{
		++ it;
		-- line_index;
	}
	CharInfoList& char_list = it->char_list;
	if (char_list.size() == 0) return 0;
	return char_list.back().acc_width;
}

int TextEdit::GetLineCount()
{
	return static_cast<int>(m_linechar_list.size());
}

int TextEdit::GetScrollOffset()
{
	if (m_line_start_it == m_linechar_list.end()) return 0;
	return m_line_start_it->pre_height;
}

void TextEdit::ClearText()
{
	// clear list
	m_linechar_list.clear();

	// add a line, and add a end char to this line
	m_linechar_list.push_back(LineCharInfo());
	LineCharInfo& line_info = m_linechar_list.back();
	line_info.acc_height = 0;
	line_info.pre_height = 0;
	line_info.force_line = false;
	line_info.char_list.push_back(CharInfo());
	CharInfo& char_info = line_info.char_list.back();
	char_info.acc_width = 0;
	char_info.pre_width = 0;
	char_info.str = "";

	// clear text
	m_text = "";

	// init start
	m_line_start_it = m_linechar_list.begin();
	// init cursor
	m_line_cursor_it = m_linechar_list.begin();
	m_char_cursor_it = m_line_cursor_it->char_list.begin();
	// inti selected
	m_line_select_it = m_linechar_list.begin();
	m_char_select_it = m_line_select_it->char_list.end();

	m_need_redraw = true;
}

void TextEdit::AdjustStartItAwayFromCursor(int distance)
{
	if (m_line_start_it->pre_height > m_line_cursor_it->pre_height)
	{
		m_line_start_it = m_line_cursor_it;

		m_need_redraw = true;
	}
}
	
void TextEdit::AdjustStartItCloseTOCursor(int distance)
{
	while (m_line_start_it != m_line_cursor_it)
	{
		if (m_line_cursor_it->acc_height - m_line_start_it->pre_height < distance)
			break;

		++ m_line_start_it;

		m_need_redraw = true;
	}
}

void TextEdit::ResetCursor()
{
	if (!m_font) return;

	// handle not selected text
	if (m_char_select_it == m_line_select_it->char_list.end()
		|| (m_line_select_it == m_line_cursor_it && m_char_select_it == m_char_cursor_it))
	{
		// hide cursor
		m_select_1.SetVisible(false);
		m_select_2.SetVisible(false);
		m_select_3.SetVisible(false);

		// set cursor width
		m_cursor.SetWidth((float)m_cursor_width);
		// set cursor position
		m_cursor.SetY((float)(m_line_cursor_it->pre_height - m_line_start_it->pre_height));
		m_cursor.SetX((float)(m_char_cursor_it->acc_width));
		return;
	}

	// handle selected cursor
	if (m_line_select_it->pre_height > m_line_cursor_it->pre_height)
	{
		LineCharInfoList::iterator line_it;

		line_it = m_line_cursor_it;
		m_select_1.SetVisible(true);
		int select_1_y = (m_line_cursor_it->pre_height - m_line_start_it->pre_height);
		int select_1_height = (m_line_cursor_it->acc_height - m_line_cursor_it->pre_height);
		if (select_1_y < 0) select_1_y = 0;
		if (select_1_y + select_1_height >(int)m_size.y) select_1_height = (int)m_size.y - select_1_y;
		if (select_1_height <= 0) m_select_1.SetVisible(false);
		m_select_1.SetY((float)select_1_y);
		m_select_1.SetX((float)m_char_cursor_it->acc_width);
		m_select_1.SetHeight((float)select_1_height);
		m_select_1.SetWidth(m_size.x - m_char_cursor_it->acc_width);

		m_select_3.SetVisible(m_line_cursor_it->acc_height != m_line_select_it->pre_height);
		int select_3_y = m_line_cursor_it->acc_height - m_line_start_it->pre_height;
		if (select_3_y < 0) select_3_y = 0;
		int select_3_height = m_line_select_it->pre_height - m_line_cursor_it->acc_height;
		if (select_3_y + select_3_height >(int)m_size.y) select_3_height = (int)m_size.y - select_3_y;
		if (select_3_height <= 0) m_select_3.SetVisible(false);
		m_select_3.SetY((float)select_3_y);
		m_select_3.SetX(0);
		m_select_3.SetHeight((float)select_3_height);
		m_select_3.SetWidth(m_size.x);

		line_it = m_line_select_it;
		m_select_2.SetVisible(true);
		int select_2_y = m_line_select_it->pre_height - m_line_start_it->pre_height;
		if (select_2_y < 0) select_2_y = 0;
		int select_2_height = m_line_select_it->acc_height - m_line_select_it->pre_height;
		if (select_2_y + select_2_height >(int)m_size.y) select_2_height = (int)m_size.y - select_2_y;
		if (select_2_height <= 0) m_select_2.SetVisible(false);
		m_select_2.SetY((float)select_2_y);
		m_select_2.SetX(0);
		m_select_2.SetHeight((float)select_2_height);
		m_select_2.SetWidth((float)(m_char_select_it->acc_width));
	}
	else if (m_line_select_it->pre_height < m_line_cursor_it->pre_height)
	{
		LineCharInfoList::iterator line_it;

		line_it = m_line_select_it;
		m_select_1.SetVisible(true);
		int select_1_y = (m_line_select_it->pre_height - m_line_start_it->pre_height);
		int select_1_height = (m_line_select_it->acc_height - m_line_select_it->pre_height);
		if (select_1_y < 0)
		{
			if (select_1_y + select_1_height < 0)
				m_select_1.SetVisible(false);
			else
			{
				select_1_height = select_1_y + select_1_height;
				select_1_y = 0;
			}
		}
		m_select_1.SetY((float)select_1_y);
		m_select_1.SetX((float)m_char_select_it->acc_width);
		m_select_1.SetHeight((float)select_1_height);
		m_select_1.SetWidth(m_size.x - m_char_select_it->acc_width);

		line_it = m_line_cursor_it;
		m_select_2.SetVisible(true);
		int select_2_y = (m_line_cursor_it->pre_height - m_line_start_it->pre_height);
		if (select_2_y < 0) select_2_y = 0;
		int select_2_height = (m_line_cursor_it->acc_height - m_line_cursor_it->pre_height);
		if (select_2_y + select_2_height >(int)m_size.y) select_2_height = (int)m_size.y - select_2_y;
		if (select_2_height <= 0) m_select_2.SetVisible(false);
		m_select_2.SetY((float)select_2_y);
		m_select_2.SetX(0);
		m_select_2.SetHeight((float)select_2_height);
		m_select_2.SetWidth((float)m_char_cursor_it->acc_width);

		m_select_3.SetVisible(m_line_select_it->acc_height != m_line_cursor_it->pre_height);
		int select_3_y = (m_line_select_it->acc_height - m_line_start_it->pre_height);
		if (select_3_y < 0) select_3_y = 0;
		int select_3_height = (int)m_size.y - select_3_y;
		if (select_2_height > 0) select_3_height = select_2_y - select_3_y;
		if (select_3_height <= 0) m_select_3.SetVisible(false);
		m_select_3.SetY((float)select_3_y);
		m_select_3.SetX(0);
		m_select_3.SetWidth(m_size.x);
		m_select_3.SetHeight((float)select_3_height);
	}
	else
	{
		m_select_1.SetVisible(false);
		m_select_2.SetVisible(false);
		m_select_3.SetVisible(false);

		if (m_char_cursor_it->acc_width > m_char_select_it->acc_width)
		{
			m_select_1.SetVisible(true);
			int select_1_y = (m_line_cursor_it->pre_height - m_line_start_it->pre_height);
			if (select_1_y < 0) select_1_y = 0;
			int select_1_height = (m_line_cursor_it->acc_height - m_line_cursor_it->pre_height);
			if (select_1_y + select_1_height >(int)m_size.y) select_1_height = (int)m_size.y - select_1_y;
			if (select_1_height <= 0) m_select_1.SetVisible(false);
			m_select_1.SetX((float)m_char_select_it->acc_width);
			m_select_1.SetY((float)select_1_y);

			m_select_1.SetHeight((float)select_1_height);
			m_select_1.SetWidth((float)(m_char_cursor_it->acc_width - m_char_select_it->acc_width));
		}
		else if (m_char_cursor_it->acc_width < m_char_select_it->acc_width)
		{
			m_select_1.SetVisible(true);
			int select_1_y = (m_line_cursor_it->pre_height - m_line_start_it->pre_height);
			if (select_1_y < 0) select_1_y = 0;
			int select_1_height = (m_line_cursor_it->acc_height - m_line_cursor_it->pre_height);
			if (select_1_y + select_1_height >(int)m_size.y) select_1_height = (int)m_size.y - select_1_y;
			if (select_1_height <= 0) m_select_1.SetVisible(false);
			m_select_1.SetX((float)m_char_cursor_it->acc_width);
			m_select_1.SetY((float)select_1_y);

			m_select_1.SetHeight((float)select_1_height);
			m_select_1.SetWidth((float)(m_char_select_it->acc_width - m_char_cursor_it->acc_width));
		}
	}
}

void TextEdit::DeleteTextImpl(LineCharInfoList::iterator line_begin_it, CharInfoList::iterator begin_it
								, LineCharInfoList::iterator line_end_it, CharInfoList::iterator end_it)
{
	if (!m_font) return;

	// init position
	LineCharInfoList::iterator line_delete_begin = line_begin_it;
	LineCharInfoList::iterator line_delete_end = line_end_it;
	CharInfoList::iterator char_delete_begin = begin_it;
	CharInfoList::iterator char_delete_end = end_it;
	// adjust real start and end position
	if (line_begin_it->pre_height > line_end_it->pre_height)
	{
		line_delete_begin = line_end_it;
		char_delete_begin = end_it;

		line_delete_end = line_begin_it;
		char_delete_end = begin_it;
	}
	else if (line_begin_it->pre_height == line_end_it->pre_height)
	{
		if (begin_it->acc_width > end_it->acc_width)
		{
			char_delete_begin = end_it;
			char_delete_end = begin_it;
		}
	}

	// if start line in the middle of these two line, then delete is then new start
	if (m_line_start_it->pre_height >= line_delete_begin->pre_height)
		m_line_start_it = line_delete_begin;

	// calc text
	std::string calc_text_1 = "";

	// calc line_delete_begin this line
	CharInfoList::iterator char_it = line_delete_begin->char_list.begin();
	++ char_it;
	++ char_delete_begin;
	while(char_it != char_delete_begin)
	{
		calc_text_1.append(char_it->str);
		++ char_it;
	}

	std::string calc_text_2 = "";
	// calc line_delete_end this line
	char_it = char_delete_end;
	++ char_it;
	while(char_it != line_delete_end->char_list.end())
	{
		calc_text_2.append(char_it->str);
		++ char_it;
	}

	// handle last lines
	LineCharInfoList::iterator line_it = line_delete_end;
	++ line_it;
	LineCharInfoList::iterator free_line_it = m_linechar_list.end();
	while (line_it != m_linechar_list.end())
	{
		// break when force line
		if (line_it->force_line)
		{
			free_line_it = line_it;
			break;
		}

		// add char
		CharInfoList::iterator char_it = line_it->char_list.begin(); 
		for (; char_it != line_it->char_list.end(); ++char_it)
			calc_text_2.append(char_it->str);
		++ line_it;
	}

	// delete from line_delete_begin(not include this) to the end, then recalc
	CharInfo char_info = line_delete_begin->char_list.front();
	line_delete_begin->char_list.clear();
	line_delete_begin->char_list.push_back(char_info);
	
	// save free line list
	LineCharInfoList free_line_list;
	while (free_line_it != m_linechar_list.end())
	{
		free_line_list.push_back(*free_line_it);
		++ free_line_it;
	}

	line_it = line_delete_begin;
	++ line_it;
	while(line_it != m_linechar_list.end())
		line_it = m_linechar_list.erase(line_it);

	// calc text and get cursor position
	InsertTextUtil(calc_text_1.c_str(), &m_line_cursor_it, &m_char_cursor_it);

	// continue insert text
	InsertTextUtil(calc_text_2.c_str());

	// add to last line
	if (free_line_list.size())
	{
		// get line gap + line height
		int line_skip = FontHelper::GetFontHeight(m_font) + FontHelper::GetFontLineGap(m_font);

		// get last line height
		LineCharInfoList::iterator last_line = m_linechar_list.end();
		-- last_line;
		if (last_line->char_list.size() == 1 && last_line->force_line)
			last_line->acc_height = last_line->pre_height + line_skip;
		int start_y = last_line->acc_height;
		// add free line list
		LineCharInfoList::iterator free_line_end = free_line_list.end();
		for (free_line_it = free_line_list.begin(); free_line_it != free_line_end; ++free_line_it)
		{
			// reset line height
			int line_height = free_line_it->acc_height - free_line_it->pre_height;
			free_line_it->pre_height = start_y;
			start_y = start_y + line_height;
			free_line_it->acc_height = start_y;

			m_linechar_list.push_back(*free_line_it);
		}
	}

	// set not selected text
	m_line_select_it = m_linechar_list.end(); -- m_line_select_it;
	m_char_select_it = m_line_select_it->char_list.end();

	m_need_redraw = true;
}

void TextEdit::InsertTextImpl(const char* text)
{
	if (!m_font) return;
	// calc text length
	int text_len = static_cast<int>(strlen(text));
	if (text_len <= 0) return;

//handle current line text///////////////////////////////////////////////////////////////////////////////

	std::string calc_text_1 = "";
	// prepare text forword
	CharInfoList::iterator char_it = m_line_cursor_it->char_list.begin();
	++ char_it;
	CharInfoList::iterator char_end_it = m_char_cursor_it;
	++ char_end_it;
	while (char_it != char_end_it)
	{
		calc_text_1.append(char_it->str);
		++ char_it;
	}
	// add new text
	calc_text_1.append(text);
	
	std::string calc_text_2 = "";
	// add old text
	char_it = m_char_cursor_it;
	++ char_it;
	while (char_it != m_line_cursor_it->char_list.end())
	{
		calc_text_2.append(char_it->str);
		++ char_it;
	}

//add last lines///////////////////////////////////////////////////////////////////////////////
	LineCharInfoList::iterator line_it = m_line_cursor_it;
	++ line_it;
	LineCharInfoList::iterator free_line_it = m_linechar_list.end();
	while (line_it != m_linechar_list.end())
	{
		if (line_it->force_line)
		{
			free_line_it = line_it;
			break;
		}
		
		CharInfoList::iterator char_it = line_it->char_list.begin();
		for (; char_it != line_it->char_list.end(); ++ char_it)
			calc_text_2.append(char_it->str);
		++ line_it;
	}

	// delete line and add end char
	CharInfo char_info = m_line_cursor_it->char_list.front();
	m_line_cursor_it->char_list.clear();
	m_line_cursor_it->char_list.push_back(char_info);

	// save free line list
	LineCharInfoList free_line_list;
	while (free_line_it != m_linechar_list.end())
	{
		free_line_list.push_back(*free_line_it);
		++ free_line_it;
	}

	line_it = m_line_cursor_it;
	++ line_it;
	while (line_it != m_linechar_list.end())
		line_it = m_linechar_list.erase(line_it);

	// calc text, and get cursor position
	InsertTextUtil(calc_text_1.c_str(), &m_line_cursor_it, &m_char_cursor_it);

	// continue insert text
	InsertTextUtil(calc_text_2.c_str());

	// add to last line
	if (free_line_list.size())
	{
		// get line gap + line height
		int line_skip = FontHelper::GetFontHeight(m_font) + FontHelper::GetFontLineGap(m_font);

		// get last line height
		LineCharInfoList::iterator last_line = m_linechar_list.end();
		-- last_line;
		if (last_line->char_list.size() == 1 && last_line->force_line)
			last_line->acc_height = last_line->pre_height + line_skip;
		int start_y = last_line->acc_height;
		// add free line list
		LineCharInfoList::iterator free_line_end = free_line_list.end();
		for (free_line_it = free_line_list.begin(); free_line_it != free_line_end; ++free_line_it)
		{
			// reset line height
			int line_height = free_line_it->acc_height - free_line_it->pre_height;
			free_line_it->pre_height = start_y;
			start_y = start_y + line_height;
			free_line_it->acc_height = start_y;

			m_linechar_list.push_back(*free_line_it);
		}
	}

	// set not selected
	m_line_select_it = m_linechar_list.end(); -- m_line_select_it;
	m_char_select_it = m_line_select_it->char_list.end();

	m_need_redraw = true;
}

void TextEdit::InsertTextUtil(const char* text, LineCharInfoList::iterator* line_begin_it, CharInfoList::iterator* begin_it)
{
	// get line gap + line height
	int line_skip = FontHelper::GetFontHeight(m_font) + FontHelper::GetFontLineGap(m_font);

	const char* str = text;
	std::string current_char = "";
	std::string last_char = "";
	// get last line
	LineCharInfoList::iterator line_it = m_linechar_list.end();
	-- line_it;
	if (line_it->acc_height == 0) line_it->acc_height = line_skip;

	// init line position, char position
	if (line_begin_it) *line_begin_it = line_it;
	if (begin_it)
	{
		*begin_it = line_it->char_list.end();
		-- (*begin_it);
	}

	// start calc
	while (*str)
	{
		// get utf8 byte count
		int byte_count = utf8_GetByteCountOfOneWord(*str);
		current_char.assign(str, byte_count);

		// if is \n
		if (current_char == "\n")
		{
			// change current line to force
			if (line_it->force_line == false && line_it->char_list.size() == 1)
			{
				line_it->force_line = true;
				line_it->char_list.begin()->str = "\n";
			}
			else
			{
				m_linechar_list.push_back(LineCharInfo());
				LineCharInfoList::iterator new_line_it = m_linechar_list.end();
				-- new_line_it;
				new_line_it->force_line = true;
				new_line_it->pre_height = line_it->acc_height;
				new_line_it->acc_height = new_line_it->pre_height + line_skip;

				new_line_it->char_list.push_back(CharInfo());
				CharInfo* new_char_info = &(new_line_it->char_list.back());
				new_char_info->str = "\n";
				new_char_info->acc_width = 0;
				new_char_info->pre_width = 0;

				if (line_begin_it) *line_begin_it = new_line_it;

				if (begin_it)
				{
					*begin_it = new_line_it->char_list.end();
					-- (*begin_it);
				}

				line_it = new_line_it;
			}

			last_char = "";
			str += byte_count;
		}
		else if (current_char == "\t")
		{
			int char_width = 0, height;
			GetCharSize("    ", char_width, height);
			
			CharInfo* char_info = &(line_it->char_list.back());
			line_it->char_list.push_back(CharInfo());
			CharInfo* new_char_info = &(line_it->char_list.back());
			new_char_info->str = current_char;
			new_char_info->acc_width = char_info->acc_width + char_width;
			new_char_info->pre_width = char_info->acc_width;
		
			if (line_begin_it) *line_begin_it = line_it;
			if (begin_it)
			{
				*begin_it = line_it->char_list.end();
				-- (*begin_it);
			}

			last_char = "    ";
			str += byte_count;
		}
		else if (current_char == "\r")
		{
			CharInfo* char_info = 0;
			if (line_it->char_list.size()) char_info = &(line_it->char_list.back());
			line_it->char_list.push_back(CharInfo());
			CharInfo* new_char_info = &(line_it->char_list.back());
			new_char_info->str = current_char;
			new_char_info->acc_width = char_info ? char_info->acc_width : 0;
			new_char_info->pre_width = char_info ? char_info->pre_width : 0;

			if (line_begin_it) *line_begin_it = line_it;
			if (begin_it)
			{
				*begin_it = line_it->char_list.end();
				-- (*begin_it);
			}

			str += byte_count;
		}
		else
		{
			int char_width = 0, height;
			GetCharSize(current_char.c_str(), char_width, height);

			CharInfo* char_info = &(line_it->char_list.back());
			if (char_info->acc_width + char_width <= (int)m_size.x || (int)m_size.x <= char_width)
			{
				line_it->char_list.push_back(CharInfo());
				CharInfo* new_char_info = &(line_it->char_list.back());
				new_char_info->str = current_char;
				new_char_info->acc_width = char_info->acc_width + char_width;
				new_char_info->pre_width = char_info->acc_width;

				if (line_begin_it) *line_begin_it = line_it;
				if (begin_it)
				{
					*begin_it = line_it->char_list.end();
					-- (*begin_it);
				}

				last_char = current_char;
				str += byte_count;
			}
			else
			{
				m_linechar_list.push_back(LineCharInfo());
				LineCharInfoList::iterator new_line_it = m_linechar_list.end();
				-- new_line_it;
				new_line_it->force_line = false;
				new_line_it->pre_height = line_it->acc_height;
				new_line_it->acc_height = new_line_it->pre_height + line_skip;

				new_line_it->char_list.push_back(CharInfo());
				CharInfo* new_char_info = &(new_line_it->char_list.back());
				new_char_info->str = "";
				new_char_info->acc_width = 0;
				new_char_info->pre_width = 0;

				line_it = new_line_it;
				last_char = "";
			}
		}
	}
}

void TextEdit::GetCharSize(const char* text, int& width, int& height)
{
	// get font height
	height = FontHelper::GetFontHeight(m_font);

	// find text height
	std::map<std::string, int>::iterator it = m_width_map.find(text);
	if (it != m_width_map.end())
	{
		width = it->second;
		return;
	}

	width = FontHelper::CutTextWidth(text, m_font);
	// save size
	m_width_map[text] = width;
}

} // ALittle
