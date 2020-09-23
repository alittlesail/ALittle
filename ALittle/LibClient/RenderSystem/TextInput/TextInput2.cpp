
#include "TextInput.h"

extern "C" {
#include "ALittle/LibCommon/ThirdParty/utf8/utf8.h"
}

#include "ALittle/LibClient/RenderSystem/DisplaySystem.h"
#include "ALittle/LibClient/RenderSystem/RenderSystem.h"
#include "Carp/carp_font.hpp"

namespace ALittle
{

void TextInput::ClearText()
{
	// clear char list
	m_char_list.clear();

	// clear text
	m_text = "";

	// add a end char
	m_char_list.push_back(CharInfo());
	CharInfo& info = m_char_list.back();
	info.acc_width = 0;
	info.pre_width = 0;
	info.text_index = 0;
	info.str = "";

	// reset all iterator
	m_start_it = m_char_list.begin();
	m_cursor_it = m_char_list.begin();
	m_select_it = m_char_list.end();

	m_need_redraw = true;
}

void TextInput::AdjustStartItAwayFromCursor(int distance)
{
	// If the starting position is equal to the cursor position
	if (m_start_it == m_cursor_it && m_start_it != m_char_list.begin())
	{
		// To calculate the starting position
		CharInfoList::iterator begin_it = m_cursor_it;
		while(m_cursor_it->pre_width - begin_it->pre_width < distance
			&& begin_it != m_char_list.begin())
			-- begin_it;
		// Copies the result to the starting position
		m_start_it = begin_it;

		m_need_redraw = true;
	}
}
	
void TextInput::AdjustStartItCloseTOCursor(int distance)
{
	while (m_start_it != m_cursor_it)
	{
		if (m_cursor_it->pre_width - m_start_it->pre_width < distance)
			break;

		++ m_start_it;

		m_need_redraw = true;
	}
}

void TextInput::ResetCursor()
{
	if (!m_font) return;

	// If not selected text
	if (m_select_it == m_char_list.end() || m_select_it == m_cursor_it)
	{
		// Set the cursor width
		m_cursor.SetWidth((float)m_cursor_width);
		// Set cursor position
		m_cursor.SetX((float)(m_cursor_it->pre_width - m_start_it->pre_width));
		return;
	}
	
	// Set start and end position
	CharInfoList::iterator delete_begin = m_select_it;
	CharInfoList::iterator delete_end = m_cursor_it;
	if (m_select_it->pre_width > m_cursor_it->pre_width)
	{
		delete_begin = m_cursor_it;
		delete_end = m_select_it;
	}

	// Set cursor position
	int cursor_x = 0;
	if (delete_begin->pre_width > m_start_it->pre_width)
		cursor_x = (delete_begin->pre_width - m_start_it->pre_width);
	m_cursor.SetX((float)cursor_x);

	// Set the cursor width
	int cursor_width = (delete_end->pre_width - delete_begin->pre_width);
	if (cursor_width + cursor_x > (int)m_size.x)
		cursor_width = (int)m_size.x - cursor_x;
	m_cursor.SetWidth((float)ceil((float)cursor_width));
}

void TextInput::DeleteTextImpl(CharInfoList::iterator begin_it, CharInfoList::iterator end_it)
{
	if (!m_font) return;
	if (begin_it == end_it) return;

	// Set start and end position
	CharInfoList::iterator delete_begin = begin_it;
	CharInfoList::iterator delete_end = end_it;
	if (begin_it->pre_width > end_it->pre_width)
	{
		delete_begin = end_it;
		delete_end = begin_it;
	}

	// If the starting position among them adjust the starting position for the final position
	if (m_start_it->pre_width >= delete_begin->pre_width)
		m_start_it = delete_end;

	// Calculate the char length
	int select_text_len = 0;
	for (CharInfoList::iterator it = delete_begin; it != delete_end; ++it)
		select_text_len += static_cast<int>(it->str.size());
	
	// Calculated width character
	std::string calc_text;
	int acc_width = 0;
	CharInfoList::iterator calc_it = delete_begin;
	if (calc_it != m_char_list.begin())
	{
		-- calc_it;
		calc_text.append(calc_it->str);
		acc_width = calc_it->acc_width;
	}
	// Bridging the cursor to the end of the characters
	int width_1 = 0;
	if (m_password_mode)
		width_1 = m_font->CutTextWidth("*a");
	else
		width_1 = m_font->CutTextWidth((calc_it->str + "a").c_str());
	int width_2 = 0;
	if (m_password_mode)
	{
		if (delete_end->str.size())
			width_2 = m_font->CutTextWidth("**a");
		else
			width_2 = m_font->CutTextWidth("*a");
	}
	else
		width_2 = m_font->CutTextWidth((calc_it->str + delete_end->str + "a").c_str());
	int offset_width = (width_2 - width_1 + acc_width) - delete_end->acc_width;
	// Recalculate, from the current cursor back until the end, the width of the characters
	for (CharInfoList::iterator it = delete_end; it != m_char_list.end(); ++it)
	{
		it->acc_width += offset_width;
		it->pre_width += offset_width;
		it->text_index -= select_text_len;
	}
	// Delete the selected node
	for (CharInfoList::iterator it = delete_begin; it != delete_end;)
		it = m_char_list.erase(it);

	m_need_redraw = true;
}

void TextInput::InsertTextImpl(const char* text)
{
	if (!m_font) return;
	// The computed text length
	int text_len = static_cast<int>(strlen(text));
	if (text_len <= 0) return;

	// Whether the current cursor position to the starting position
	bool adjust_start_it = (m_start_it == m_cursor_it);
	// Initialize
	const char* str = text;
	// The starting point for each character, each character width
	while(*str)
	{
		// Forward migration
		int byte_count = utf8_GetByteCountOfOneWord(*str);
		// Save the information
		m_cursor_it = m_char_list.insert(m_cursor_it, CharInfo());
		if (adjust_start_it) { -- m_start_it; adjust_start_it = false; }
		// copy string
		m_cursor_it->str.assign(str, byte_count);
		// Set the current character index
		CharInfoList::iterator calc_it = m_cursor_it;
		if (calc_it == m_char_list.begin())
		{
			m_cursor_it->text_index = 0;
			m_cursor_it->pre_width = 0;

			int width_1 = m_font->CutTextWidth("a");
			int width_2 = 0;
			if (m_password_mode)
				width_2 = m_font->CutTextWidth("*a");
			else
				width_2 = m_font->CutTextWidth((calc_it->str + "a").c_str());
			m_cursor_it->acc_width = width_2 - width_1;
		}
		else
		{
			-- calc_it;
			m_cursor_it->text_index = calc_it->text_index + byte_count;
			m_cursor_it->pre_width = calc_it->acc_width;
			
			int width_1 = 0;
			if (m_password_mode)
				width_1 = m_font->CutTextWidth("*a");
			else
				width_1 = m_font->CutTextWidth((calc_it->str + "a").c_str());
			int width_2 = 0;
			if (m_password_mode)
				width_2 = m_font->CutTextWidth("**a");
			else
				width_2 = m_font->CutTextWidth((calc_it->str + m_cursor_it->str + "a").c_str());
			m_cursor_it->acc_width = width_2 - width_1 + calc_it->acc_width;
		}
		// The cursor backward step
		++ m_cursor_it;
		// offset
		str += byte_count;
	}
	// Bridging the cursor pointing to the current character
	CharInfoList::iterator calc_it = m_cursor_it;
	-- calc_it;
	int width_1 = 0;
	if (m_password_mode)
		width_1 = m_font->CutTextWidth("*a");
	else
		width_1 = m_font->CutTextWidth((calc_it->str + "a").c_str());
	int width_2 = 0;
	if (m_password_mode)
	{
		if (m_cursor_it->str.size())
			width_2 = m_font->CutTextWidth("**a");
		else
			width_2 = m_font->CutTextWidth("*a");
	}
	else
		width_2 = m_font->CutTextWidth((calc_it->str + m_cursor_it->str + "a").c_str());
	// Recalculate, from the current cursor back until the end, the width of the characters
	int offset_width = width_2 - width_1 + calc_it->acc_width - m_cursor_it->acc_width;
	for (CharInfoList::iterator it = m_cursor_it; it != m_char_list.end(); ++it)
	{
		it->acc_width += offset_width;
		it->pre_width += offset_width;
		it->text_index += text_len;
	}

	m_need_redraw = true;
}

} // ALittle
