#ifndef ALITTLE_TEXTINPUT_INCLUDED
#define ALITTLE_TEXTINPUT_INCLUDED
#include "alittle_font.hpp"
#include "alittle_image.hpp"
#include "alittle_quad.hpp"
#include "Carp/carp_font.hpp"

class ALittleTextInput : public ALittleImage
{
public:
	ALittleTextInput()
	{
		m_cursor.SetVisible(false);
		ClearText();
	}
	~ALittleTextInput()
	{
		delete m_texture;
	}

	static void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.deriveClass<ALittleTextInput, ALittleImage>("__CPPAPITextInput")
			.addConstructor<void(*)()>()
			.addFunction("SetScaleX", &ALittleTextInput::SetScaleX)
			.addFunction("SetScaleY", &ALittleTextInput::SetScaleY)
			.addFunction("SetCenterX", &ALittleTextInput::SetCenterX)
			.addFunction("SetCenterY", &ALittleTextInput::SetCenterY)
			.addFunction("SetAngle", &ALittleTextInput::SetAngle)
			.addFunction("SetX", &ALittleTextInput::SetX)
			.addFunction("SetY", &ALittleTextInput::SetY)
			.addFunction("SetWidth", &ALittleTextInput::SetWidth)
			.addFunction("SetHeight", &ALittleTextInput::SetHeight)
			.addFunction("SetRed", &ALittleTextInput::SetRed)
			.addFunction("SetGreen", &ALittleTextInput::SetGreen)
			.addFunction("SetBlue", &ALittleTextInput::SetBlue)
			.addFunction("SetAlpha", &ALittleTextInput::SetAlpha)
			.addFunction("SetCursorRed", &ALittleTextInput::SetCursorRed)
			.addFunction("SetCursorGreen", &ALittleTextInput::SetCursorGreen)
			.addFunction("SetCursorBlue", &ALittleTextInput::SetCursorBlue)
			.addFunction("SetCursorAlpha", &ALittleTextInput::SetCursorAlpha)
			.addFunction("SetFont", &ALittleTextInput::SetFont)
			.addFunction("SetText", &ALittleTextInput::SetText)
			.addFunction("SetDefaultText", &ALittleTextInput::SetDefaultText)
			.addFunction("SetDefaultTextAlpha", &ALittleTextInput::SetDefaultTextAlpha)
			.addFunction("IsDefaultText", &ALittleTextInput::IsDefaultText)
			.addFunction("SetVisible", &ALittleTextInput::SetVisible)
			.addFunction("GetText", &ALittleTextInput::GetText)
			.addFunction("InsertText", &ALittleTextInput::InsertText)
			.addFunction("DeleteText", &ALittleTextInput::DeleteText)
			.addFunction("CursorOffset", &ALittleTextInput::CursorOffset)
			.addFunction("SelectCursorOffset", &ALittleTextInput::SelectCursorOffset)
			.addFunction("SelectAll", &ALittleTextInput::SelectAll)
			.addFunction("ClickCursor", &ALittleTextInput::ClickCursor)
			.addFunction("ClickWordCursor", &ALittleTextInput::ClickWordCursor)
			.addFunction("ShowCursor", &ALittleTextInput::ShowCursor)
			.addFunction("SetCursorToHome", &ALittleTextInput::SetCursorToHome)
			.addFunction("SetCursorToEnd", &ALittleTextInput::SetCursorToEnd)
			.addFunction("SetBold", &ALittleTextInput::SetBold)
			.addFunction("SetDeleteline", &ALittleTextInput::SetDeleteline)
			.addFunction("SetUnderline", &ALittleTextInput::SetUnderline)
			.addFunction("SetItalic", &ALittleTextInput::SetItalic)
			.addFunction("SetPasswordMode", &ALittleTextInput::SetPasswordMode)
			.addFunction("SetClip", &ALittleTextInput::SetClip)
			.addFunction("SetFlip", &ALittleTextInput::SetFlip)
			.addFunction("GetSelectText", &ALittleTextInput::GetSelectText)
			.addFunction("DeleteSelectText", &ALittleTextInput::DeleteSelectText)
			.addFunction("DragCursorBegin", &ALittleTextInput::DragCursorBegin)
			.addFunction("DragCursor", &ALittleTextInput::DragCursor)
			.addFunction("GetCursorX", &ALittleTextInput::GetCursorX)
			.addFunction("GetCursorY", &ALittleTextInput::GetCursorY)
			.addFunction("GetCursorHeight", &ALittleTextInput::GetCursorHeight)
			.addFunction("NeedDraw", &ALittleTextInput::NeedDraw)
			.endClass();
	}

	void SetX(float x) override { ALittleImage::SetX(x); }
	void SetY(float y) override { ALittleImage::SetY(y); }

	void SetAngle(float angle) override { ALittleImage::SetAngle(angle); }

	void SetScaleX(float x) override { ALittleImage::SetScaleX(x); }
	void SetScaleY(float y) override { ALittleImage::SetScaleY(y); }

	void SetCenterX(float x) override { ALittleImage::SetCenterX(x); }
	void SetCenterY(float y) override { ALittleImage::SetCenterY(y); }

	void SetRed(float red) override { ALittleImage::SetRed(red); }
	void SetGreen(float green) override { ALittleImage::SetGreen(green); }
	void SetBlue(float blue) override { ALittleImage::SetBlue(blue); }
	void SetAlpha(float alpha) override { ALittleImage::SetAlpha(alpha); }

	void SetVisible(bool visible) override { ALittleImage::SetVisible(visible); }
	void SetClip(bool clip) override { ALittleImage::SetClip(clip); }

	void SetFlip(int flip) override { ALittleImage::SetFlip(flip); }

public:
	void SetWidth(float width) override
	{
		width = floor(width);
		if (m_size.x == width) return;

		if (width > m_real_width || width < m_real_width)
			m_need_redraw = true;

		m_size.x = (float)width;

		m_self_matrix_dirty = true;
	}
	void SetHeight(float height) override
	{
		height = floor(height);
		m_size.y = height;

		m_cursor.SetHeight(height);

		m_self_matrix_dirty = true;
	}

public:
	void SetCursorRed(float red) { m_cursor.SetRed(red); }
	void SetCursorGreen(float green) { m_cursor.SetGreen(green); }
	void SetCursorBlue(float blue) { m_cursor.SetBlue(blue); }
	void SetCursorAlpha(float alpha) { m_cursor.SetAlpha(alpha); }

public:
	void SetBold(bool bold)
	{
		const bool is_bold = (m_font_style & CARP_FONT_STYLE_BOLD) != 0;
		if (is_bold == bold) return;

		if (bold) m_font_style |= CARP_FONT_STYLE_BOLD;
		else m_font_style &= ~CARP_FONT_STYLE_BOLD;

		if (!m_font_path.empty() && m_font_size > 0)
			m_font = s_alittle_font.GetFont(m_font_path.c_str(), m_font_size, m_font_style);

		std::string text = GetText();
		ClearText();
		InsertTextImpl(text.c_str());
		ResetCursor();
	}
	
	void SetUnderline(bool underline)
	{
		const bool is_underline = (m_font_style & CARP_FONT_STYLE_UNDERLINE) != 0;
		if (is_underline == underline) return;

		if (underline) m_font_style |= CARP_FONT_STYLE_UNDERLINE;
		else m_font_style &= ~CARP_FONT_STYLE_UNDERLINE;

		if (!m_font_path.empty() && m_font_size > 0)
			m_font = s_alittle_font.GetFont(m_font_path.c_str(), m_font_size, m_font_style);
		m_need_redraw = true;
	}
	
	void SetDeleteline(bool deleteline)
	{
		const bool is_deleteline = (m_font_style & CARP_FONT_STYLE_DELETELINE) != 0;
		if (is_deleteline == deleteline) return;

		if (deleteline) m_font_style |= CARP_FONT_STYLE_DELETELINE;
		else m_font_style &= ~CARP_FONT_STYLE_DELETELINE;

		if (!m_font_path.empty() && m_font_size > 0)
			m_font = s_alittle_font.GetFont(m_font_path.c_str(), m_font_size, m_font_style);
		m_need_redraw = true;
	}
	
	void SetItalic(bool italic)
	{
		const bool is_italic = (m_font_style & CARP_FONT_STYLE_ITALIC) != 0;
		if (is_italic == italic) return;

		if (italic)
			m_font_style |= CARP_FONT_STYLE_ITALIC;
		else
			m_font_style &= ~CARP_FONT_STYLE_ITALIC;

		if (!m_font_path.empty() && m_font_size > 0)
			m_font = s_alittle_font.GetFont(m_font_path.c_str(), m_font_size, m_font_style);
		m_need_redraw = true;
	}

public:
	void SetPasswordMode(bool mode)
	{
		if (m_password_mode == mode) return;
		m_password_mode = mode;

		std::string text = GetText();
		ClearText();
		InsertTextImpl(text.c_str());
		ResetCursor();
	}

public:
	void ShowCursor(bool show)
	{
		m_cursor.SetVisible(show);
	}

	//=====================================================================================
private:
	struct CharInfo
	{
		std::string str;		// str content
		int text_index;			// text index

		int pre_width;			// total width text(not include this)
		int acc_width;			// total width text(include this)
	};
	typedef std::list<CharInfo> CharInfoList;
	/**
	 * clear text
	 */
	void ClearText()
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
	/**
	 * reset cursor
	 */
	void ResetCursor()
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
	/**
	 * Closer to the starting position and distance
	 * @param distance
	 */
	void AdjustStartItCloseToCursor(int distance)
	{
		while (m_start_it != m_cursor_it)
		{
			if (m_cursor_it->pre_width - m_start_it->pre_width < distance)
				break;

			++m_start_it;

			m_need_redraw = true;
		}
	}
	/**
	 * wawy from Starting position and distance
	 * @param distance
	 */
	void AdjustStartItAwayFromCursor(int distance)
	{
		// If the starting position is equal to the cursor position
		if (m_start_it == m_cursor_it && m_start_it != m_char_list.begin())
		{
			// To calculate the starting position
			CharInfoList::iterator begin_it = m_cursor_it;
			while (m_cursor_it->pre_width - begin_it->pre_width < distance
				&& begin_it != m_char_list.begin())
				--begin_it;
			// Copies the result to the starting position
			m_start_it = begin_it;

			m_need_redraw = true;
		}
	}
	/**
	 * Delete the specified range node
	 * @param begin_it
	 * @param end_it
	 */
	void DeleteTextImpl(CharInfoList::iterator begin_it, CharInfoList::iterator end_it)
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
			--calc_it;
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
	/**
	 * Insert text at the location of the cursor
	 * @param text
	 */
	void InsertTextImpl(const char* text)
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
		while (*str)
		{
			// Forward migration
			int byte_count = CarpString::UTF8GetByteCountOfOneWord(*str);
			// Save the information
			m_cursor_it = m_char_list.insert(m_cursor_it, CharInfo());
			if (adjust_start_it) { --m_start_it; adjust_start_it = false; }
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
				--calc_it;
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
			++m_cursor_it;
			// offset
			str += byte_count;
		}
		// Bridging the cursor pointing to the current character
		CharInfoList::iterator calc_it = m_cursor_it;
		--calc_it;
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

	//=====================================================================================
public:
	/**
	 * set font
	 * @param font_path
	 * @param font_size
	 */
	void SetFont(const char* font_path, unsigned int font_size)
	{
		if (m_font_path == font_path && m_font_size == font_size) return;
		m_font = s_alittle_font.GetFont(font_path, font_size, m_font_style);
		m_cursor_width = GetCursorWidth(font_size);

		std::string text = GetText();
		ClearText();
		InsertTextImpl(text.c_str());
		ResetCursor();
	}
	/**
	 * set text
	 * @param text
	 */
	void SetText(const char* text)
	{
		if (!text) return;
		ClearText();
		InsertTextImpl(text);
		ResetCursor();
	}
	/**
	 * set default text, it shows when textedit is empty
	 * @param mode: default or not
	 * @param text: default text
	 */
	void SetDefaultText(bool mode, const char* text)
	{
		m_default_text_mode = mode;
		SetText(text);
	}
	/*
	 * set default alpha
	 * @param alpha
	 */
	void SetDefaultTextAlpha(float alpha)
	{
		if (alpha > 1.0f) m_default_text_alpha = 255;
		else if (alpha < 0.0f) m_default_text_alpha = 0;
		else m_default_text_alpha = (unsigned char)(alpha * 255);
	}
	/**
	 * get default mode or not
	 * @return default or not
	 */
	bool IsDefaultText() const
	{
		return m_default_text_mode;
	}
	/**
	 * get text
	 * @return text
	 */
	const char* GetText()
	{
		m_text = "";
		for (CharInfoList::iterator it = m_char_list.begin(); it != m_char_list.end(); ++it)
			m_text.append(it->str);
		return m_text.c_str();
	}
	/**
	 * get selected text
	 * @return text
	 */
	const char* GetSelectText()
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
	/**
	 * delete selected text
	 * @return delete or not
	 */
	bool DeleteSelectText()
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
	/**
	 * insert text
	 * @param text
	 * @return insert or not
	 */
	bool InsertText(const char* text)
	{
		if (!m_font) return false;
		if (text && text[0] != 0) m_default_text_mode = false;

		DeleteSelectText();
		InsertTextImpl(text);
		AdjustStartItCloseToCursor((int)m_size.x);
		ResetCursor();

		return true;
	}
	/**
	 * delete one char
	 * @param left true:delete left, false:delete right
	 * @return delete or not
	 */
	bool DeleteText(bool left)
	{
		if (!m_font) return false;
		// If the current selected text can be removed, then remove the returned directly
		if (DeleteSelectText())	return true;

		CharInfoList::iterator it = m_cursor_it;
		if (left)
		{
			if (m_cursor_it == m_char_list.begin()) return false;
			--it;
			DeleteTextImpl(it, m_cursor_it);
			// Adjust the start cursor
			AdjustStartItAwayFromCursor((int)m_size.x / 2);
		}
		else
		{
			if (m_cursor_it->str.size() == 0) return false;
			++m_cursor_it;
			DeleteTextImpl(it, m_cursor_it);
		}
		// Set cursor position
		ResetCursor();

		return true;
	}

	//=====================================================================================
private:
	/**
	 * offset cursor left or right
	 * @param left true: offset left, false: offset right
	 */
	void CursorOffsetImpl(bool left)
	{
		if (left)
		{
			if (m_cursor_it == m_char_list.begin()) return;

			if (m_cursor_it != m_start_it)
			{
				--m_cursor_it;

				ResetCursor();
				return;
			}

			--m_cursor_it;
			--m_start_it;

			m_need_redraw = true;

			AdjustStartItAwayFromCursor((int)m_size.x / 2);

			ResetCursor();
			return;
		}

		if (m_cursor_it->str.size() == 0) return;

		++m_cursor_it;
		AdjustStartItCloseToCursor((int)m_size.x);

		ResetCursor();
	}

	/**
	 * get iterator by offset x
	 * @param offset
	 * @return char info iterator
	 */
	CharInfoList::iterator GetIteratorByOffset(float offset)
	{
		// Starting from the text
		float real_offset = offset + m_start_it->pre_width;

		std::list<CharInfo>::iterator cursor_it = m_start_it;
		while (cursor_it->str.size())
		{
			if (real_offset > cursor_it->acc_width)
			{
				++cursor_it;
				continue;
			}

			float half_char_width = (cursor_it->acc_width - cursor_it->pre_width) * 0.5f;
			if (real_offset - cursor_it->pre_width > half_char_width)
				++cursor_it;

			break;
		}

		return cursor_it;
	}

	/*
	*  resize cursor width by font_size
	* @param font_size
	*/
	unsigned int GetCursorWidth(unsigned int font_size)
	{
		if (font_size < 15) return 1;
		if (font_size > 100) return 10;

		return ((unsigned int)(font_size / 10));
	}
public:
	/**
	 * offset cursor left or right
	 * @param left true: offset left, false: offset right
	 */
	void CursorOffset(bool left)
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

	/**
	 * offset select cursor left or right
	 * @param left true: offset left, false: offset right
	 */
	void SelectCursorOffset(bool left)
	{
		// Set select starting point
		if (m_select_it == m_char_list.end())
			m_select_it = m_cursor_it;

		// Offset the cursor around
		CursorOffsetImpl(left);
	}
	/**
	 * offset cursor to home
	 */
	void SetCursorToHome()
	{
		if (m_start_it->pre_width > 0)
			m_need_redraw = true;

		m_select_it = m_char_list.end();
		m_start_it = m_char_list.begin();
		m_cursor_it = m_char_list.begin();

		ResetCursor();
	}
	/**
	 * offset cursor to end
	 */
	void SetCursorToEnd()
	{
		m_select_it = m_char_list.end();
		m_cursor_it = m_char_list.end();
		--m_cursor_it;

		// Adjust the starting position
		if (m_cursor_it->pre_width - m_start_it->pre_width > (int)m_size.x)
			AdjustStartItCloseToCursor((int)m_size.x);

		ResetCursor();
	}
	/**
	 * select all text
	 */
	void SelectAll()
	{
		m_select_it = m_char_list.begin();
		m_cursor_it = m_char_list.end();
		--m_cursor_it;

		// Adjust the starting position
		if (m_cursor_it->pre_width - m_start_it->pre_width > (int)m_size.x)
			AdjustStartItCloseToCursor((int)m_size.x);

		ResetCursor();
	}
	/**
	 * set cursor offset by x
	 * @param offset
	 */
	void ClickCursor(float offset)
	{
		m_select_it = m_char_list.end();

		// Set cursor position
		m_cursor_it = GetIteratorByOffset(offset);

		ResetCursor();
	}
	/**
	 * set cursor offset by x
	 * @param offset
	 */
	bool ClickWordCursor(float offset)
	{
		// Set cursor position
		m_cursor_it = GetIteratorByOffset(offset);

		// find char to left
		m_select_it = m_cursor_it;
		CharInfoList::iterator cursor_tmp = m_cursor_it;
		while (cursor_tmp != m_char_list.begin())
		{
			--cursor_tmp;
			if (cursor_tmp->str.size() == 1
				&& cursor_tmp->str[0] != '_'
				&& !CarpString::IsNumber(cursor_tmp->str[0])
				&& !CarpString::IsLetter(cursor_tmp->str[0]))
				break;
			--m_cursor_it;
		}
		// find char to right
		while (m_select_it != m_char_list.end())
		{
			if (m_select_it->str.size() == 1
				&& m_select_it->str[0] != '_'
				&& !CarpString::IsNumber(m_select_it->str[0])
				&& !CarpString::IsLetter(m_select_it->str[0]))
				break;
			++m_select_it;
		}
		if (m_select_it == m_char_list.end())
			--m_select_it;

		if (m_select_it == m_cursor_it)
			m_select_it = m_char_list.end();
		else if (m_select_it != m_char_list.end())
			AdjustStartItCloseToCursor((int)m_size.x);

		ResetCursor();

		return m_select_it != m_char_list.end();
	}
	/**
	 * cursor drag begin
	 */
	void DragCursorBegin()
	{
		m_select_it = m_cursor_it;
	}
	/**
	 * cursor draging
	 * @param offset_x
	 * @param offset_y
	 */
	void DragCursor(float offset_x, float offset_y)
	{
		m_cursor_it = GetIteratorByOffset(offset_x);

		if (m_start_it->pre_width >= m_cursor_it->pre_width)
		{
			while (m_start_it != m_char_list.begin() && m_start_it->pre_width >= m_cursor_it->pre_width)
			{
				--m_start_it;
				m_need_redraw = true;
			}
			ResetCursor();
			return;
		}

		if (m_cursor_it->pre_width - m_start_it->pre_width > (int)m_size.x)
		{
			AdjustStartItCloseToCursor((int)m_size.x);
			ResetCursor();
			return;
		}

		ResetCursor();
	}
	/**
	 * get cursor x
	 * @return x
	 */
	int GetCursorX() { return m_cursor.GetX(); }
	/**
	 * get cursor y
	 * @return y
	 */
	int GetCursorY() { return m_cursor.GetY() - (int)m_pos.y; }
	/**
	 * get cursor height
	 * @return height
	 */
	int GetCursorHeight() { return m_cursor.GetHeight(); }

public:
	void NeedDraw() { m_need_redraw = true; }
	void Render(const CarpMatrix2D& parent, bool parent_changed) override
	{
		if (m_clip) return;
		if (!m_visible) return;
		if (m_color.a <= 0) return;

		if (m_need_redraw)
		{
			Draw();
			m_need_redraw = false;
			SetSelfMatrixDirty();
		}

		bool global_changed = UpdateGlobalMatrix2D(parent, parent_changed);
		UpdateVertexCoord();
		UpdateTextureCoord();

		if (m_texture)
		{
			if (m_default_text_mode)
			{
				CarpColor4 color = m_color;
				color.a = m_default_text_alpha;
				m_texture->Render(color, m_vertex_coord, m_texture_coord);
			}
			else
			{
				m_texture->Render(m_color, m_vertex_coord, m_texture_coord);
			}
		}

		m_cursor.Render(m_global_matrix, global_changed);
	}
	void UpdateVertexCoord() override
	{
		if (!m_vertex_dirty) return;
		m_vertex_dirty = false;

		CarpVector2D coord[4];
		coord[0].x = 0.0f; coord[0].y = 0.0f;
		coord[1].x = (float)m_real_width; coord[1].y = 0.0f;
		coord[2].x = (float)m_real_width; coord[2].y = (float)m_real_height;
		coord[3].x = 0.0f; coord[3].y = (float)m_real_height;

		int index = 0;
		for (int i = 0; i < 4; ++i)
		{
			coord[i].Multiply(m_global_matrix);
			m_vertex_coord[index++] = coord[i].x;
			m_vertex_coord[index++] = coord[i].y;
		}
	}

private:
	void Draw()
	{
		// release current texture
		if (m_texture)
		{
			delete m_texture;
			m_texture = 0;
		}

		// check param
		if (!m_font || !m_char_list.size() || m_size.x <= 0 || m_size.y <= 0) return;

		// According to the width of the current, capture the real rendering portion of the string
		std::string content;
		content.reserve(m_text.size());
		CharInfoList::iterator char_it = m_start_it;
		while (char_it != m_char_list.end())
		{
			if ((int)m_size.x < char_it->acc_width - m_start_it->pre_width) break;
			if (!m_default_text_mode && m_password_mode && char_it->str.size())
				content.append("*");
			else
				content.append(char_it->str);
			++char_it;
		}

		// render text to surface
		if (content.size() == 0) return;
		auto* surface = s_alittle_font.CreateSurface(m_font, content.c_str());
		if (!surface)
		{
			CARP_ERROR("CreateSurface failed!");
			return;
		}

		// save size
		m_real_width = surface->GetWidth();
		m_real_height = surface->GetHeight();

		m_texture = new ALittleSurfaceTexture(surface, ALittleTextureRenderMode::ATRM_NEAREST);
		m_vertex_dirty = true;
	}

private:
	bool m_need_redraw = false;

private:
	int m_real_width = 0, m_real_height = 0;

private:
	unsigned int m_cursor_width = 1;
	//////////////////////////////////////////////////////////////////////////////
		// all text
	std::string m_text;
	// select text
	std::string m_select_text;
	// all char info
	CharInfoList m_char_list;
	// font object
	CarpFont* m_font = nullptr;
	std::string m_font_path;
	unsigned int m_font_size = 0;
	// font style
	unsigned int m_font_style = CARP_FONT_STYLE_NORMAL;
	// password mode or not
	bool m_password_mode = false;
	// default mode or not
	bool m_default_text_mode = true;
	// default text alpha
	unsigned char m_default_text_alpha = 255;
	//////////////////////////////////////////////////////////////////////////////
private:
	// start iterator
	CharInfoList::iterator m_start_it;
	// cursor iterator
	CharInfoList::iterator m_cursor_it;
	// select iterator
	CharInfoList::iterator m_select_it;

	/////////////////////////////////////////////////////////////////////////////
private:
	ALittleQuad m_cursor;
};

#endif
