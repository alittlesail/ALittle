
#include "TextInput.h"

#include "ALittle/LibClient/RenderSystem/DisplaySystem.h"
#include "ALittle/LibClient/RenderSystem/RenderSystem.h"

#include "ALittle/LibCommon/Helper/StringHelper.h"
#include "ALittle/LibCommon/Helper/LogHelper.h"

namespace ALittle
{

void TextInput::CursorOffset(bool left)
{
	// If the current status for the selected text
	if (m_select_it != m_char_list.end())
	{
		m_select_it = m_char_list.end();
		// To reset the cursor position
		ResetCursor();
		return;
	}

	CursorOffsetImpl(left);
}

void TextInput::SelectCursorOffset(bool left)
{
	// Set select starting point
	if (m_select_it == m_char_list.end())
		m_select_it = m_cursor_it;

	// Offset the cursor around
	CursorOffsetImpl(left);
}

void TextInput::SelectAll()
{
	m_select_it = m_char_list.begin();
	m_cursor_it = m_char_list.end();
	-- m_cursor_it;

	// Adjust the starting position
	if (m_cursor_it->pre_width - m_start_it->pre_width > (int)m_size.x)
		RejustStartItCloseTOCursor((int)m_size.x);
	
	ResetCursor();
}

void TextInput::SetCursorToHome()
{
	if (m_start_it->pre_width > 0)
		m_need_redraw = true;

	m_select_it = m_char_list.end();
	m_start_it = m_char_list.begin();
	m_cursor_it = m_char_list.begin();

	ResetCursor();
}

void TextInput::SetCursorToEnd()
{
	m_select_it = m_char_list.end();
	m_cursor_it = m_char_list.end();
	-- m_cursor_it;

	// Adjust the starting position
	if (m_cursor_it->pre_width - m_start_it->pre_width > (int)m_size.x)
		RejustStartItCloseTOCursor((int)m_size.x);

	ResetCursor();
}

void TextInput::ClickCursor(float offset)
{
	m_select_it = m_char_list.end();

	// Set cursor position
	m_cursor_it = GetIteratorByOffset(offset);

	ResetCursor();
}

bool TextInput::ClickWordCursor(float offset)
{
	// Set cursor position
	m_cursor_it = GetIteratorByOffset(offset);

	// find char to left
	m_select_it = m_cursor_it;
	CharInfoList::iterator cursor_tmp = m_cursor_it;
	while (cursor_tmp != m_char_list.begin())
	{
		-- cursor_tmp;
		if (cursor_tmp->str.size() == 1
			&& cursor_tmp->str[0] != '_'
			&& !StringHelper::IsNumber(cursor_tmp->str[0])
			&& !StringHelper::IsLetter(cursor_tmp->str[0]))
			break;
		-- m_cursor_it;
	}
	// find char to right
	while (m_select_it != m_char_list.end())
	{
		if (m_select_it->str.size() == 1
			&& m_select_it->str[0] != '_'
			&& !StringHelper::IsNumber(m_select_it->str[0])
			&& !StringHelper::IsLetter(m_select_it->str[0]))
			break;
		++ m_select_it;
	}
	if (m_select_it == m_char_list.end())
		-- m_select_it;

	if (m_select_it == m_cursor_it)
		m_select_it = m_char_list.end();
	else if (m_select_it != m_char_list.end())
		RejustStartItCloseTOCursor((int)m_size.x);

	ResetCursor();

	return m_select_it != m_char_list.end();
}

unsigned int TextInput::GetCursorWidth(unsigned int font_size)
{
	if (font_size < 15) return 1;
	if (font_size > 100) return 10;

	return ((unsigned int)(font_size/10));
}

void TextInput::DragCursorBegin()
{
	m_select_it = m_cursor_it;
}

void TextInput::DragCursor(float offset_x, float offset_y)
{
	m_cursor_it = GetIteratorByOffset(offset_x);
	
	if (m_start_it->pre_width >= m_cursor_it->pre_width)
	{
		while(m_start_it != m_char_list.begin() && m_start_it->pre_width >= m_cursor_it->pre_width)
		{
			-- m_start_it;
			m_need_redraw = true;
		}
		ResetCursor();
		return;
	}

	if (m_cursor_it->pre_width - m_start_it->pre_width > (int)m_size.x)
	{
		RejustStartItCloseTOCursor((int)m_size.x);
		ResetCursor();
		return;
	}

	ResetCursor();
}

} // ALittle
