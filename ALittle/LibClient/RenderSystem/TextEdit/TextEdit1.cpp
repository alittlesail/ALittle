
#include "TextEdit.h"

#include "ALittle/LibCommon/Helper/LogHelper.h"
#include "ALittle/LibClient/RenderSystem/DisplaySystem.h"
#include "ALittle/LibClient/RenderSystem/RenderSystem.h"

#include "Carp/carp_font.hpp"

namespace ALittle
{

void TextEdit::SetFont(const char* font_path, unsigned int font_size)
{
	if (m_font_path == font_path && m_font_size == font_size) return;
	m_font_path = font_path;
	m_font_size = font_size;
	// get font object
	m_font = g_DisplaySystem.GetFont(font_path, m_font_style, font_size);
	m_cursor_width = GetCursorWidth(font_size);

	if (m_font)
		m_cursor.SetHeight((float)(m_font->GetFontHeight()));

	m_width_map.clear();

	// get cur text
	std::string text = GetText();

	// clear text
	ClearText();

	// insert text
	InsertTextImpl(text.c_str());

	// reset cursor
	ResetCursor();
}

void TextEdit::SetText(const char* text)
{
	// clear text
	ClearText();

	// inset at cursor
	InsertTextImpl(text);

	// reset cursor
	ResetCursor();
}

void TextEdit::SetDefaultText(bool mode, const char* text)
{
	m_default_text_mode = mode;
	SetText(text);
}

void TextEdit::SetDefaultTextAlpha(float alpha)
{
	if (alpha > 1.0f) m_default_text_alpha = 255;
	else if (alpha < 0.0f) m_default_text_alpha = 0;
	else m_default_text_alpha = (unsigned char)(alpha*255);
}

bool TextEdit::IsDefaultText()
{
	return m_default_text_mode;
}

const char* TextEdit::GetText()
{
	m_text = "";

	LineCharInfoList::iterator line_it, line_end = m_linechar_list.end();
	for (line_it = m_linechar_list.begin(); line_it != line_end; ++line_it)
	{
		CharInfoList::iterator char_it, char_end = line_it->char_list.end();
		for (char_it = line_it->char_list.begin(); char_it != char_end; ++char_it)
			m_text.append(char_it->str);
	}

	return m_text.c_str();
}

const char* TextEdit::GetSelectText()
{
	m_select_text = "";

	// check selected text or not
	if (m_char_select_it == m_line_select_it->char_list.end())
		return m_select_text.c_str();

	// from down to up
	if (m_line_select_it->pre_height > m_line_cursor_it->pre_height)
	{
		LineCharInfoList::iterator line_it = m_line_cursor_it;
		while(true)
		{
			CharInfoList::iterator char_it, char_end;
			
			if (line_it == m_line_cursor_it) { char_it = m_char_cursor_it; ++ char_it; }
			else char_it = line_it->char_list.begin();
				
			if (line_it == m_line_select_it) { char_end = m_char_select_it; ++ char_end; }
			else char_end = line_it->char_list.end();

			for (; char_it != char_end; ++char_it)
				m_select_text.append(char_it->str);

			if (line_it == m_line_select_it) break;
			++ line_it;
		}
	}
	// from up to down
	else if (m_line_select_it->pre_height < m_line_cursor_it->pre_height)
	{
		LineCharInfoList::iterator line_it = m_line_select_it;
		while(true)
		{
			CharInfoList::iterator char_it, char_end;
	
			if (line_it == m_line_select_it) { char_it = m_char_select_it; ++ char_it; }
			else char_it = line_it->char_list.begin();
				
			if (line_it == m_line_cursor_it) { char_end = m_char_cursor_it; ++ char_end; }
			else char_end = line_it->char_list.end();

			for (; char_it != char_end; ++char_it)
				m_select_text.append(char_it->str);

			if (line_it == m_line_cursor_it) break;
			++ line_it;
		}
	}
	else
	{
		if (m_char_cursor_it->acc_width > m_char_select_it->acc_width)
		{
			CharInfoList::iterator char_it = m_char_select_it;
			CharInfoList::iterator char_end = m_char_cursor_it;
			++ char_end;
			++ char_it;

			for (; char_it != char_end; ++char_it)
				m_select_text.append(char_it->str);
		}
		else if (m_char_cursor_it->acc_width < m_char_select_it->acc_width)
		{
			CharInfoList::iterator char_it = m_char_cursor_it;
			CharInfoList::iterator char_end = m_char_select_it;
			++ char_end;
			++ char_it;

			for (; char_it != char_end; ++char_it)
				m_select_text.append(char_it->str);
		}
	}

	return m_select_text.c_str();
}

bool TextEdit::DeleteSelectText()
{
	if (!m_font) return false;

	// check selected or not
	if (m_char_select_it == m_line_select_it->char_list.end()) return false;

	// adjust cursor position
	LineCharInfoList::iterator line_begin_it;
	CharInfoList::iterator begin_it;
	LineCharInfoList::iterator line_end_it;
	CharInfoList::iterator end_it;
	if (m_line_select_it->pre_height > m_line_cursor_it->pre_height)
	{
		line_begin_it = m_line_cursor_it;
		begin_it = m_char_cursor_it;
		line_end_it = m_line_select_it;
		end_it = m_char_select_it;
	}
	else if (m_line_select_it->pre_height < m_line_cursor_it->pre_height)
	{
		line_begin_it = m_line_select_it;
		begin_it = m_char_select_it;
		line_end_it = m_line_cursor_it;
		end_it = m_char_cursor_it;
	}
	else
	{
		line_begin_it = m_line_select_it;
		line_end_it = m_line_cursor_it;
		begin_it = m_char_select_it;
		end_it = m_char_cursor_it;
		if (m_char_cursor_it->acc_width > m_char_select_it->acc_width)
		{
			begin_it = m_char_select_it;
			end_it = m_char_cursor_it;
		}
		else if (m_char_cursor_it->acc_width < m_char_select_it->acc_width)
		{
			begin_it = m_char_cursor_it;
			end_it = m_char_select_it;
		}
	}

	// adjust start line
	if (begin_it == line_begin_it->char_list.begin())
	{
		if (line_begin_it != m_linechar_list.begin() && line_begin_it->force_line == false)
		{
			-- line_begin_it;
			begin_it = line_begin_it->char_list.end();
			-- begin_it;
		}
	}

	// delete text info
	DeleteTextImpl(line_begin_it, begin_it, line_end_it, end_it);
	// adjust start iterator
	AdjustStartItAwayFromCursor((int)m_size.x / 2);
	// reset cursor
	ResetCursor();

	return true;
}

bool TextEdit::InsertText(const char* text)
{
	if (!m_font) return false;
	if (text && text[0] != 0) m_default_text_mode = false;

	// delete select text
	DeleteSelectText();

	// insert text at cursor
	InsertTextImpl(text);

	// adjust start iterator
	AdjustStartItCloseTOCursor((int)m_size.y);

	// reset cursor
	ResetCursor();

	return true;
}

bool TextEdit::DeleteText(bool left)
{
	if (!m_font) return false;
	// if selected text, then delete and return
	if (DeleteSelectText())	return true;

	if (left)
	{
		// check already at start char
		if (m_line_cursor_it == m_linechar_list.begin()
			&& m_char_cursor_it == m_line_cursor_it->char_list.begin())
			return false;

		LineCharInfoList::iterator line_begin_it = m_line_cursor_it;
		CharInfoList::iterator begin_it = m_char_cursor_it;
		LineCharInfoList::iterator line_end_it = m_line_cursor_it;
		CharInfoList::iterator end_it = m_char_cursor_it;

		// if cursor at end char of line, then delete end char at last line
		if (begin_it == line_begin_it->char_list.begin())
		{
			if (line_begin_it != m_linechar_list.begin())
			{
				-- line_begin_it;
				begin_it = line_begin_it->char_list.end();
				-- begin_it;
			}
		}
		else
		{
			-- begin_it;
			// if adjust forword is soft \n, then then delete end char at last line
			if (begin_it == line_begin_it->char_list.begin() && line_begin_it->force_line == false)
			{
				if (line_begin_it != m_linechar_list.begin())
				{
					-- line_begin_it;
					begin_it = line_begin_it->char_list.end();
					-- begin_it;
				}
			}
		}

		// delete text
		DeleteTextImpl(line_begin_it, begin_it, line_end_it, end_it);
		// adjust start iterator
		AdjustStartItAwayFromCursor((int)m_size.x / 2);
	}
	else
	{
		// check at line end char
		LineCharInfoList::iterator end_line = m_linechar_list.end();
		-- end_line;
		CharInfoList::iterator end_char = end_line->char_list.end();
		-- end_char;
		if (m_line_cursor_it == end_line && m_char_cursor_it == end_char) return false;

		LineCharInfoList::iterator line_begin_it = m_line_cursor_it;
		CharInfoList::iterator begin_it = m_char_cursor_it;
		LineCharInfoList::iterator line_end_it = m_line_cursor_it;
		CharInfoList::iterator end_it = m_char_cursor_it;

		end_char = line_end_it->char_list.end();
		-- end_char;
		// if at end char of line, then adjust next line at first char
		if (end_it == end_char)
		{
			if (line_end_it != end_line)
			{
				// set start position
				++ line_end_it;
				end_it = line_end_it->char_list.begin();
				// if not a force line, then dec end_it
				if (line_end_it->force_line == false)
				{
					++ end_it;
					// check param
					if (end_it == line_end_it->char_list.end())
						-- end_it;
				}
			}
		}
		else
		{
			++ end_it;
		}
		// delete text
		DeleteTextImpl(line_begin_it, begin_it, line_end_it, end_it);
	}

	// reset cursor
	ResetCursor();

	return true;
}

} // ALittle
