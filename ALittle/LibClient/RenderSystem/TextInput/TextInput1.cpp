
#include "TextInput.h"

#include "ALittle/LibCommon/Helper/LogHelper.h"
#include "ALittle/LibClient/RenderSystem/DisplaySystem.h"
#include "ALittle/LibClient/RenderSystem/RenderSystem.h"

namespace ALittle
{

void TextInput::SetFont(const char* font_path, unsigned int font_size)
{
	if (m_font_path == font_path && m_font_size == font_size) return;
	m_font = g_DisplaySystem.GetFont(font_path, m_font_style, font_size);
	m_cursor_width = GetCursorWidth(font_size);

	std::string text = GetText();

	ClearText();

	InsertTextImpl(text.c_str());

	ResetCursor();
}

void TextInput::SetText(const char* text)
{
	if (!text) return;

	ClearText();

	InsertTextImpl(text);

	ResetCursor();
}

void TextInput::SetDefaultText(bool mode, const char* text)
{
	m_default_text_mode = mode;
	SetText(text);
}

void TextInput::SetDefaultTextAlpha(float alpha)
{
	if (alpha > 1.0f) m_default_text_alpha = 255;
	else if (alpha < 0.0f) m_default_text_alpha = 0;
	else m_default_text_alpha = (unsigned char)(alpha*255);
}

bool TextInput::IsDefaultText()
{
	return m_default_text_mode;
}

const char* TextInput::GetText()
{
	m_text = "";
	for (CharInfoList::iterator it = m_char_list.begin(); it != m_char_list.end(); ++it)
		m_text.append(it->str);
	return m_text.c_str();
}

const char* TextInput::GetSelectText()
{
	m_select_text = "";

	if (m_select_it != m_char_list.end())
	{
		// init start and end position
		CharInfoList::iterator delete_begin = m_select_it;
		CharInfoList::iterator delete_end = m_cursor_it;
		if (m_select_it->pre_width > m_cursor_it->pre_width)
		{
			delete_begin = m_cursor_it;
			delete_end = m_select_it;
		}

		// append char to a string
		for (CharInfoList::iterator it = delete_begin; it != delete_end; ++it)
			m_select_text.append(it->str);
	}

	return m_select_text.c_str();
}

bool TextInput::DeleteSelectText()
{
	if (!m_font) return false;
	// selected text or not
	if (m_select_it == m_char_list.end()) return false;
	// adjust cursor position
	CharInfoList::iterator it = m_cursor_it;
	if (m_select_it->pre_width > m_cursor_it->pre_width)
		m_cursor_it = m_select_it;
	// delete text
	DeleteTextImpl(m_select_it, it);
	// adjust start iterator
	AdjustStartItAwayFromCursor((int)m_size.x / 2);
	// set not selected
	m_select_it = m_char_list.end();
	// reset cursor
	ResetCursor();

	return true;
}

bool TextInput::InsertText(const char* text)
{
	if (!m_font) return false;
	if (text && text[0] != 0) m_default_text_mode = false;

	DeleteSelectText();

	InsertTextImpl(text);

	AdjustStartItCloseTOCursor((int)m_size.x);

	ResetCursor();

	return true;
}

bool TextInput::DeleteText(bool left)
{
	if (!m_font) return false;
	// If the current selected text can be removed, then remove the returned directly
	if (DeleteSelectText())	return true;

	CharInfoList::iterator it = m_cursor_it;
	if (left)
	{
		if (m_cursor_it == m_char_list.begin()) return false;
		-- it;
		DeleteTextImpl(it, m_cursor_it);
		// Adjust the start cursor
		AdjustStartItAwayFromCursor((int)m_size.x / 2);
	}
	else
	{
		if (m_cursor_it->str.size() == 0) return false;
		++ m_cursor_it;
		DeleteTextImpl(it, m_cursor_it);
	}
	// Set cursor position
	ResetCursor();

	return true;
}

} // ALittle
