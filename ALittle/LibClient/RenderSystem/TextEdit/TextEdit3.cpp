
#include "TextEdit.h"

#include "ALittle/LibCommon/Helper/LogHelper.h"
#include "ALittle/LibCommon/Helper/StringHelper.h"

#include "ALittle/LibClient/RenderSystem/DisplaySystem.h"
#include "ALittle/LibClient/RenderSystem/RenderSystem.h"

namespace ALittle
{

void TextEdit::CursorOffsetLR(bool left)
{
	// check selected or not
	if (m_char_select_it != m_line_select_it->char_list.end())
	{
		m_char_select_it = m_line_select_it->char_list.end();
		// reset cursor
		ResetCursor();
		return;
	}

	CursorOffsetLRImpl(left);
}

void TextEdit::CursorOffsetUD(bool up)
{
	// check selected or not
	if (m_char_select_it != m_line_select_it->char_list.end())
	{
		m_char_select_it = m_line_select_it->char_list.end();
		// reset cursor
		ResetCursor();
		return;
	}

	CursorOffsetUDImpl(up);
}

void TextEdit::SelectCursorOffsetLR(bool left)
{
	// init select iterator
	if (m_char_select_it == m_line_select_it->char_list.end())
	{
		m_line_select_it = m_line_cursor_it;
		m_char_select_it = m_char_cursor_it;
	}

	CursorOffsetLRImpl(left);
}

void TextEdit::SelectCursorOffsetUD(bool up)
{
	// init select iterator
	if (m_char_select_it == m_line_select_it->char_list.end())
	{
		m_line_select_it = m_line_cursor_it;
		m_char_select_it = m_char_cursor_it;
	}

	CursorOffsetUDImpl(up);
}

void TextEdit::SetCursorToHome()
{
	m_line_start_it = m_linechar_list.begin();
	// init cursor
	m_line_cursor_it = m_linechar_list.begin();
	m_char_cursor_it = m_line_cursor_it->char_list.begin();
	// inti selected
	m_line_select_it = m_linechar_list.begin();
	m_char_select_it = m_line_select_it->char_list.end();

	m_need_redraw = true;
	ResetCursor();
}

void TextEdit::SetCursorToEnd()
{
	m_line_select_it = m_linechar_list.begin();
	m_char_select_it = m_line_select_it->char_list.end();

	m_line_cursor_it = m_linechar_list.end();
	-- m_line_cursor_it;
	m_char_cursor_it = m_line_cursor_it->char_list.end();
	-- m_char_cursor_it;

	AdjustStartItCloseTOCursor((int)m_size.y);
	ResetCursor();
}

void TextEdit::SelectAll()
{
	m_line_select_it = m_linechar_list.begin();
	m_char_select_it = m_line_select_it->char_list.begin();

	m_line_cursor_it = m_linechar_list.end();
	-- m_line_cursor_it;
	m_char_cursor_it = m_line_cursor_it->char_list.end();
	-- m_char_cursor_it;

	AdjustStartItCloseTOCursor((int)m_size.y);

	ResetCursor();
}

void TextEdit::ClickCursor(float offset_x, float offset_y)
{
	m_char_select_it = m_line_select_it->char_list.end();

	// set cursor position
	GetIteratorByOffset(offset_x, offset_y, &m_line_cursor_it, &m_char_cursor_it);

	AdjustStartItCloseTOCursor((int)m_size.y);

	ResetCursor();
}

bool TextEdit::ClickWordCursor(float offset_x, float offset_y)
{
	// set cursor position
	GetIteratorByOffset(offset_x, offset_y, &m_line_cursor_it, &m_char_cursor_it);

	// find char to left
	m_char_select_it = m_char_cursor_it;
	m_line_select_it = m_line_cursor_it;

	while (true)
	{
		bool has_find = false;
		while (true)
		{
			if (m_char_cursor_it->str.size() == 1
				&& m_char_cursor_it->str[0] != '_'
				&& !StringHelper::IsNumber(m_char_cursor_it->str[0])
				&& !StringHelper::IsLetter(m_char_cursor_it->str[0]))
			{
				has_find = true;
				break;
			}
			if (m_char_cursor_it == m_line_cursor_it->char_list.begin()) break;
			-- m_char_cursor_it;
		}
		if (has_find) break;
		if (m_line_cursor_it == m_linechar_list.begin()) break;

		-- m_line_cursor_it;
		m_char_cursor_it = m_line_cursor_it->char_list.end();
		-- m_char_cursor_it;
	}

	// find char to right
	CharInfoList::iterator cursor_tmp = m_char_select_it;
	LineCharInfoList::iterator line_cursor_tmp = m_line_select_it;
	while (true)
	{
		++ cursor_tmp;
		if (cursor_tmp == m_line_select_it->char_list.end())
		{
			++ line_cursor_tmp;
			if (line_cursor_tmp == m_linechar_list.end()) break;
			cursor_tmp = line_cursor_tmp->char_list.begin();
		}
		if (cursor_tmp->str.size() == 1
			&& cursor_tmp->str[0] != '_'
			&& !StringHelper::IsNumber(cursor_tmp->str[0])
			&& !StringHelper::IsLetter(cursor_tmp->str[0]))
			break;
		m_char_select_it = cursor_tmp;
		m_line_select_it = line_cursor_tmp;
	}
	
	if (m_line_select_it == m_linechar_list.end())
	{
		-- m_line_select_it;
		m_char_select_it = m_line_select_it->char_list.end();
	}
	if (m_char_select_it == m_line_select_it->char_list.end())
		-- m_char_select_it;

	if (m_line_select_it == m_line_cursor_it && m_char_select_it == m_char_cursor_it)
		m_char_select_it = m_line_select_it->char_list.end();

	AdjustStartItCloseTOCursor((int)m_size.y);

	ResetCursor();

	return m_char_select_it != m_line_select_it->char_list.end();
}

unsigned int TextEdit::GetCursorWidth(unsigned int font_size)
{
	if (font_size < 15) return 1;
	if (font_size > 100) return 10;

	return ((unsigned int)(font_size/10));
}

void TextEdit::DragCursorBegin()
{
	m_line_select_it = m_line_cursor_it;
	m_char_select_it = m_char_cursor_it;
}

void TextEdit::DragCursor(float offset_x, float offset_y)
{
	// set cursor position
	GetIteratorByOffset(offset_x, offset_y, &m_line_cursor_it, &m_char_cursor_it);
	
	// if start line behind the cursor then rejuse to pre until the first line
	if (m_line_start_it->pre_height >= m_line_cursor_it->pre_height)
	{
		while(m_line_start_it != m_linechar_list.begin() && m_line_start_it->pre_height >= m_line_cursor_it->pre_height)
		{
			-- m_line_start_it;
			m_need_redraw = true;
		}
		ResetCursor();
		return;
	}

	// adjust start iterator
	if (m_line_cursor_it->acc_height - m_line_start_it->pre_height > (int)m_size.y)
		AdjustStartItCloseTOCursor((int)m_size.y);

	ResetCursor();
}

} // ALittle
