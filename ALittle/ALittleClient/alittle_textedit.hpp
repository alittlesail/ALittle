#ifndef ALITTLE_TEXTEDIT_INCLUDED
#define ALITTLE_TEXTEDIT_INCLUDED (1)
#include "alittle_font.hpp"
#include "alittle_image.hpp"
#include "alittle_quad.hpp"
#include "Carp/carp_font.hpp"

class ALittleTextEdit : public ALittleImage
{
public:
	ALittleTextEdit()
	{
		m_cursor.SetVisible(false);

		m_select_1.SetVisible(false);
		m_select_2.SetVisible(false);
		m_select_3.SetVisible(false);

		ClearText();
	}
	~ALittleTextEdit()
	{
		delete m_texture;
	}

	static void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.deriveClass<ALittleTextEdit, ALittleImage>("__CPPAPITextEdit")
			.addConstructor<void(*)()>()
			.addFunction("SetScaleX", &ALittleTextEdit::SetScaleX)
			.addFunction("SetScaleY", &ALittleTextEdit::SetScaleY)
			.addFunction("SetCenterX", &ALittleTextEdit::SetCenterX)
			.addFunction("SetCenterY", &ALittleTextEdit::SetCenterY)
			.addFunction("SetAngle", &ALittleTextEdit::SetAngle)
			.addFunction("SetX", &ALittleTextEdit::SetX)
			.addFunction("SetY", &ALittleTextEdit::SetY)
			.addFunction("SetWidth", &ALittleTextEdit::SetWidth)
			.addFunction("SetHeight", &ALittleTextEdit::SetHeight)
			.addFunction("SetRed", &ALittleTextEdit::SetRed)
			.addFunction("SetGreen", &ALittleTextEdit::SetGreen)
			.addFunction("SetBlue", &ALittleTextEdit::SetBlue)
			.addFunction("SetAlpha", &ALittleTextEdit::SetAlpha)
			.addFunction("SetCursorRed", &ALittleTextEdit::SetCursorRed)
			.addFunction("SetCursorGreen", &ALittleTextEdit::SetCursorGreen)
			.addFunction("SetCursorBlue", &ALittleTextEdit::SetCursorBlue)
			.addFunction("SetCursorAlpha", &ALittleTextEdit::SetCursorAlpha)
			.addFunction("SetFont", &ALittleTextEdit::SetFont)
			.addFunction("SetText", &ALittleTextEdit::SetText)
			.addFunction("SetDefaultText", &ALittleTextEdit::SetDefaultText)
			.addFunction("SetDefaultTextAlpha", &ALittleTextEdit::SetDefaultTextAlpha)
			.addFunction("IsDefaultText", &ALittleTextEdit::IsDefaultText)
			.addFunction("SetVisible", &ALittleTextEdit::SetVisible)
			.addFunction("GetText", &ALittleTextEdit::GetText)
			.addFunction("InsertText", &ALittleTextEdit::InsertText)
			.addFunction("DeleteText", &ALittleTextEdit::DeleteText)
			.addFunction("CursorOffsetLR", &ALittleTextEdit::CursorOffsetLR)
			.addFunction("SelectCursorOffsetLR", &ALittleTextEdit::SelectCursorOffsetLR)
			.addFunction("CursorOffsetUD", &ALittleTextEdit::CursorOffsetUD)
			.addFunction("SelectCursorOffsetUD", &ALittleTextEdit::SelectCursorOffsetUD)
			.addFunction("ClickCursor", &ALittleTextEdit::ClickCursor)
			.addFunction("ClickWordCursor", &ALittleTextEdit::ClickWordCursor)
			.addFunction("ShowCursor", &ALittleTextEdit::ShowCursor)
			.addFunction("SetCursorToHome", &ALittleTextEdit::SetCursorToHome)
			.addFunction("SetCursorToEnd", &ALittleTextEdit::SetCursorToEnd)
			.addFunction("SelectAll", &ALittleTextEdit::SelectAll)
			.addFunction("SetBold", &ALittleTextEdit::SetBold)
			.addFunction("SetDeleteline", &ALittleTextEdit::SetDeleteline)
			.addFunction("SetUnderline", &ALittleTextEdit::SetUnderline)
			.addFunction("SetItalic", &ALittleTextEdit::SetItalic)
			.addFunction("SetClip", &ALittleTextEdit::SetClip)
			.addFunction("SetFlip", &ALittleTextEdit::SetFlip)
			.addFunction("GetSelectText", &ALittleTextEdit::GetSelectText)
			.addFunction("DeleteSelectText", &ALittleTextEdit::DeleteSelectText)
			.addFunction("DragCursorBegin", &ALittleTextEdit::DragCursorBegin)
			.addFunction("DragCursor", &ALittleTextEdit::DragCursor)
			.addFunction("GetCursorX", &ALittleTextEdit::GetCursorX)
			.addFunction("GetCursorY", &ALittleTextEdit::GetCursorY)
			.addFunction("GetCursorHeight", &ALittleTextEdit::GetCursorHeight)
			.addFunction("GetRealHeight", &ALittleTextEdit::GetRealHeight)
			.addFunction("GetLineWidth", &ALittleTextEdit::GetLineWidth)
			.addFunction("GetLineCount", &ALittleTextEdit::GetLineCount)
			.addFunction("GetScrollOffset", &ALittleTextEdit::GetScrollOffset)
			.addFunction("NeedDraw", &ALittleTextEdit::NeedDraw)
			.endClass();
	}

#ifdef __EMSCRIPTEN__
	void SetX(float x) { Image::SetX(x); }
	void SetY(float y) { Image::SetY(y); }

	void SetAngle(float angle) { Image::SetAngle(angle); }

	void SetScaleX(float x) { Image::SetScaleX(x); }
	void SetScaleY(float y) { Image::SetScaleY(y); }

	void SetCenterX(float x) { Image::SetCenterX(x); }
	void SetCenterY(float y) { Image::SetCenterY(y); }

	void SetRed(float red) { Image::SetRed(red); }
	void SetGreen(float green) { Image::SetGreen(green); }
	void SetBlue(float blue) { Image::SetBlue(blue); }
	void SetAlpha(float alpha) { Image::SetAlpha(alpha); }

	void SetVisible(bool visible) { Image::SetVisible(visible); }
	void SetClip(bool clip) { Image::SetClip(clip); }

	void SetFlip(int flip) { Image::SetFlip(flip); }
#endif

public:
	void SetWidth(float width) override
	{
		width = floor(width);
		if (m_size.x == width) return;

		m_size.x = width;

		m_width_map.clear();

		std::string text = GetText();

		ClearText();

		InsertTextImpl(text.c_str());

		ResetCursor();

		m_self_matrix_dirty = true;
	}
	void SetHeight(float height) override
	{
		height = floor(height);
		if (m_size.y == height) return;
		m_size.y = height;

		AdjustStartItCloseToCursor(static_cast<int>(height));

		ResetCursor();

		m_self_matrix_dirty = true;
	}

public:
	void SetCursorRed(float red)
	{
		m_cursor.SetRed(red);
		m_select_1.SetRed(red);
		m_select_2.SetRed(red);
		m_select_3.SetRed(red);
	}
	void SetCursorGreen(float green)
	{
		m_cursor.SetGreen(green);
		m_select_1.SetGreen(green);
		m_select_2.SetGreen(green);
		m_select_3.SetGreen(green);
	}
	void SetCursorBlue(float blue)
	{
		m_cursor.SetBlue(blue);
		m_select_1.SetBlue(blue);
		m_select_2.SetBlue(blue);
		m_select_3.SetBlue(blue);
	}
	void SetCursorAlpha(float alpha)
	{
		m_cursor.SetAlpha(alpha);
		m_select_1.SetAlpha(alpha);
		m_select_2.SetAlpha(alpha);
		m_select_3.SetAlpha(alpha);
	}

public:
	void SetBold(bool bold)
	{
		const bool is_bold = (m_font_style & CARP_FONT_STYLE_BOLD) != 0;
		if (is_bold == bold) return;

		if (bold) m_font_style |= CARP_FONT_STYLE_BOLD;
		else m_font_style &= ~CARP_FONT_STYLE_BOLD;

		if (!m_font_path.empty() && m_font_size > 0)
			m_font = s_alittle_font.GetFont(m_font_path.c_str(), m_font_size, m_font_style);

		m_width_map.clear();
		const std::string text = GetText();
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

		if (italic) m_font_style |= CARP_FONT_STYLE_ITALIC;
		else m_font_style &= ~CARP_FONT_STYLE_ITALIC;

		if (!m_font_path.empty() && m_font_size > 0)
			m_font = s_alittle_font.GetFont(m_font_path.c_str(), m_font_size, m_font_style);

		m_need_redraw = true;
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
		std::string str;		// utf8 char content
		int pre_width;			// total width before this (not include this)
		int acc_width;			// total width at this (include this)
	};
	typedef std::list<CharInfo> CharInfoList;
	struct LineCharInfo
	{
		CharInfoList char_list;	// utf8 char list
		int pre_height;			// total height before this (not include this)
		int acc_height;			// total height at this (include this)
		bool force_line;		// true force \n false soft \n
	};
	typedef std::list<LineCharInfo> LineCharInfoList;

public:
	/**
	 * get real height of text edit
	 * @return real height
	 */
	int GetRealHeight()
	{
		if (m_linechar_list.size() == 0) return 0;
		if (m_linechar_list.size() == 1 && m_linechar_list.back().char_list.size() == 1) return 0;
		return m_linechar_list.back().acc_height;
	}

	/**
	 * get line real width
	 * @param line_index
	 * @return width
	 */
	int GetLineWidth(int line_index)
	{
		if (line_index < 0) return 0;
		if (line_index >= static_cast<int>(m_linechar_list.size())) return 0;
		LineCharInfoList::iterator it = m_linechar_list.begin();
		while (line_index)
		{
			++it;
			--line_index;
		}
		CharInfoList& char_list = it->char_list;
		if (char_list.size() == 0) return 0;
		return char_list.back().acc_width;
	}

	/**
	 * get line count
	 * @return count
	 */
	int GetLineCount() const
	{
		return static_cast<int>(m_linechar_list.size());
	}

	/**
	 * get text offset from start line
	 * @return offset
	 */
	int GetScrollOffset() const
	{
		if (m_line_start_it == m_linechar_list.end()) return 0;
		return m_line_start_it->pre_height;
	}

private:
	/**
	 * clear all info
	 */
	void ClearText()
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
		// init selected
		m_line_select_it = m_linechar_list.begin();
		m_char_select_it = m_line_select_it->char_list.end();

		m_need_redraw = true;
	}

	/**
	 * reset cursor position
	 */
	void ResetCursor()
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
			m_cursor.SetWidth(static_cast<float>(m_cursor_width));
			// set cursor position
			m_cursor.SetY(static_cast<float>(m_line_cursor_it->pre_height - m_line_start_it->pre_height));
			m_cursor.SetX(static_cast<float>(m_char_cursor_it->acc_width));
			return;
		}

		// handle selected cursor
		if (m_line_select_it->pre_height > m_line_cursor_it->pre_height)
		{
			LineCharInfoList::iterator line_it = m_line_cursor_it;
			m_select_1.SetVisible(true);
			int select_1_y = (m_line_cursor_it->pre_height - m_line_start_it->pre_height);
			int select_1_height = (m_line_cursor_it->acc_height - m_line_cursor_it->pre_height);
			if (select_1_y < 0) select_1_y = 0;
			if (select_1_y + select_1_height > (int)m_size.y) select_1_height = (int)m_size.y - select_1_y;
			if (select_1_height <= 0) m_select_1.SetVisible(false);
			m_select_1.SetY((float)select_1_y);
			m_select_1.SetX((float)m_char_cursor_it->acc_width);
			m_select_1.SetHeight((float)select_1_height);
			m_select_1.SetWidth(m_size.x - m_char_cursor_it->acc_width);

			m_select_3.SetVisible(m_line_cursor_it->acc_height != m_line_select_it->pre_height);
			int select_3_y = m_line_cursor_it->acc_height - m_line_start_it->pre_height;
			if (select_3_y < 0) select_3_y = 0;
			int select_3_height = m_line_select_it->pre_height - m_line_cursor_it->acc_height;
			if (select_3_y + select_3_height > (int)m_size.y) select_3_height = (int)m_size.y - select_3_y;
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
			if (select_2_y + select_2_height > (int)m_size.y) select_2_height = (int)m_size.y - select_2_y;
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
			if (select_2_y + select_2_height > (int)m_size.y) select_2_height = (int)m_size.y - select_2_y;
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
				if (select_1_y + select_1_height > (int)m_size.y) select_1_height = (int)m_size.y - select_1_y;
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
				if (select_1_y + select_1_height > (int)m_size.y) select_1_height = (int)m_size.y - select_1_y;
				if (select_1_height <= 0) m_select_1.SetVisible(false);
				m_select_1.SetX((float)m_char_cursor_it->acc_width);
				m_select_1.SetY((float)select_1_y);

				m_select_1.SetHeight((float)select_1_height);
				m_select_1.SetWidth((float)(m_char_select_it->acc_width - m_char_cursor_it->acc_width));
			}
		}
	}

	/**
	 * adjust start iterator close to Cursor
	 * @param distance at last
	 */
	void AdjustStartItCloseToCursor(int distance)
	{
		while (m_line_start_it != m_line_cursor_it)
		{
			if (m_line_cursor_it->acc_height - m_line_start_it->pre_height < distance)
				break;

			++m_line_start_it;

			m_need_redraw = true;
		}
	}
	
	/**
	 * adjust start iterator away from Cursor
	 * @param distance at most
	 */
	void AdjustStartItAwayFromCursor(int distance)
	{
		if (m_line_start_it->pre_height > m_line_cursor_it->pre_height)
		{
			m_line_start_it = m_line_cursor_it;

			m_need_redraw = true;
		}
	}
	/**
	 * delete text info
	 * @param line_begin_it: begin line iterator
	 * @param begin_it: begin char iterator at line_begin_it
	 * @param line_end_it: end line iterator
	 * @param end_it: end char iterator at line_end_it
	 */
	void DeleteTextImpl(LineCharInfoList::iterator line_begin_it, CharInfoList::iterator begin_it
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
		++char_it;
		++char_delete_begin;
		while (char_it != char_delete_begin)
		{
			calc_text_1.append(char_it->str);
			++char_it;
		}

		std::string calc_text_2 = "";
		// calc line_delete_end this line
		char_it = char_delete_end;
		++char_it;
		while (char_it != line_delete_end->char_list.end())
		{
			calc_text_2.append(char_it->str);
			++char_it;
		}

		// handle last lines
		LineCharInfoList::iterator line_it = line_delete_end;
		++line_it;
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
			++line_it;
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
			++free_line_it;
		}

		line_it = line_delete_begin;
		++line_it;
		while (line_it != m_linechar_list.end())
			line_it = m_linechar_list.erase(line_it);

		// calc text and get cursor position
		InsertTextUtil(calc_text_1.c_str(), &m_line_cursor_it, &m_char_cursor_it);

		// continue insert text
		InsertTextUtil(calc_text_2.c_str());

		// add to last line
		if (free_line_list.size())
		{
			// get line gap + line height
			int line_skip = m_font->GetLineSkip();

			// get last line height
			LineCharInfoList::iterator last_line = m_linechar_list.end();
			--last_line;
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
		m_line_select_it = m_linechar_list.end(); --m_line_select_it;
		m_char_select_it = m_line_select_it->char_list.end();

		m_need_redraw = true;
	}
	/**
	 * insert text to cursor
	 * @param text
	 */
	void InsertTextImpl(const char* text)
	{
		if (!m_font) return;
		// calc text length
		int text_len = static_cast<int>(strlen(text));
		if (text_len <= 0) return;

		//handle current line text///////////////////////////////////////////////////////////////////////////////

		std::string calc_text_1 = "";
		// prepare text forword
		CharInfoList::iterator char_it = m_line_cursor_it->char_list.begin();
		++char_it;
		CharInfoList::iterator char_end_it = m_char_cursor_it;
		++char_end_it;
		while (char_it != char_end_it)
		{
			calc_text_1.append(char_it->str);
			++char_it;
		}
		// add new text
		calc_text_1.append(text);

		std::string calc_text_2 = "";
		// add old text
		char_it = m_char_cursor_it;
		++char_it;
		while (char_it != m_line_cursor_it->char_list.end())
		{
			calc_text_2.append(char_it->str);
			++char_it;
		}

		//add last lines///////////////////////////////////////////////////////////////////////////////
		LineCharInfoList::iterator line_it = m_line_cursor_it;
		++line_it;
		LineCharInfoList::iterator free_line_it = m_linechar_list.end();
		while (line_it != m_linechar_list.end())
		{
			if (line_it->force_line)
			{
				free_line_it = line_it;
				break;
			}

			CharInfoList::iterator char_it = line_it->char_list.begin();
			for (; char_it != line_it->char_list.end(); ++char_it)
				calc_text_2.append(char_it->str);
			++line_it;
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
			++free_line_it;
		}

		line_it = m_line_cursor_it;
		++line_it;
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
			int line_skip = m_font->GetLineSkip();

			// get last line height
			LineCharInfoList::iterator last_line = m_linechar_list.end();
			--last_line;
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
		m_line_select_it = m_linechar_list.end(); --m_line_select_it;
		m_char_select_it = m_line_select_it->char_list.end();

		m_need_redraw = true;
	}
	/**
	 * insert text to tail
	 * @param text
	 * @return line_begin_it: begin line iterator
	 * @return begin_it: begin char iterator at line_begin_it
	 */
	void InsertTextUtil(const char* text, LineCharInfoList::iterator* line_begin_it = 0, CharInfoList::iterator* begin_it = 0)
	{
		// get line gap + line height
		int line_skip = m_font->GetLineSkip();

		const char* str = text;
		std::string current_char = "";
		std::string last_char = "";
		// get last line
		LineCharInfoList::iterator line_it = m_linechar_list.end();
		--line_it;
		if (line_it->acc_height == 0) line_it->acc_height = line_skip;

		// init line position, char position
		if (line_begin_it) *line_begin_it = line_it;
		if (begin_it)
		{
			*begin_it = line_it->char_list.end();
			--(*begin_it);
		}

		// start calc
		while (*str)
		{
			// get utf8 byte count
			int byte_count = CarpString::UTF8GetByteCountOfOneWord(*str);
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
					--new_line_it;
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
						--(*begin_it);
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
					--(*begin_it);
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
					--(*begin_it);
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
						--(*begin_it);
					}

					last_char = current_char;
					str += byte_count;
				}
				else
				{
					m_linechar_list.push_back(LineCharInfo());
					LineCharInfoList::iterator new_line_it = m_linechar_list.end();
					--new_line_it;
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
		m_font_path = font_path;
		m_font_size = font_size;
		// get font object
		m_font = s_alittle_font.GetFont(font_path, font_size, m_font_style);
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
	/**
	 * set text
	 * @param text
	 */
	void SetText(const char* text)
	{
		// clear text
		ClearText();
		// inset at cursor
		InsertTextImpl(text);
		// reset cursor
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
	 * @return defaule or not
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

		LineCharInfoList::iterator line_it, line_end = m_linechar_list.end();
		for (line_it = m_linechar_list.begin(); line_it != line_end; ++line_it)
		{
			CharInfoList::iterator char_it, char_end = line_it->char_list.end();
			for (char_it = line_it->char_list.begin(); char_it != char_end; ++char_it)
				m_text.append(char_it->str);
		}

		return m_text.c_str();
	}
	/**
	 * get selected text
	 * @return text
	 */
	const char* GetSelectText()
	{
		m_select_text = "";

		// check selected text or not
		if (m_char_select_it == m_line_select_it->char_list.end())
			return m_select_text.c_str();

		// from down to up
		if (m_line_select_it->pre_height > m_line_cursor_it->pre_height)
		{
			LineCharInfoList::iterator line_it = m_line_cursor_it;
			while (true)
			{
				CharInfoList::iterator char_it, char_end;

				if (line_it == m_line_cursor_it) { char_it = m_char_cursor_it; ++char_it; }
				else char_it = line_it->char_list.begin();

				if (line_it == m_line_select_it) { char_end = m_char_select_it; ++char_end; }
				else char_end = line_it->char_list.end();

				for (; char_it != char_end; ++char_it)
					m_select_text.append(char_it->str);

				if (line_it == m_line_select_it) break;
				++line_it;
			}
		}
		// from up to down
		else if (m_line_select_it->pre_height < m_line_cursor_it->pre_height)
		{
			LineCharInfoList::iterator line_it = m_line_select_it;
			while (true)
			{
				CharInfoList::iterator char_it, char_end;

				if (line_it == m_line_select_it) { char_it = m_char_select_it; ++char_it; }
				else char_it = line_it->char_list.begin();

				if (line_it == m_line_cursor_it) { char_end = m_char_cursor_it; ++char_end; }
				else char_end = line_it->char_list.end();

				for (; char_it != char_end; ++char_it)
					m_select_text.append(char_it->str);

				if (line_it == m_line_cursor_it) break;
				++line_it;
			}
		}
		else
		{
			if (m_char_cursor_it->acc_width > m_char_select_it->acc_width)
			{
				CharInfoList::iterator char_it = m_char_select_it;
				CharInfoList::iterator char_end = m_char_cursor_it;
				++char_end;
				++char_it;

				for (; char_it != char_end; ++char_it)
					m_select_text.append(char_it->str);
			}
			else if (m_char_cursor_it->acc_width < m_char_select_it->acc_width)
			{
				CharInfoList::iterator char_it = m_char_cursor_it;
				CharInfoList::iterator char_end = m_char_select_it;
				++char_end;
				++char_it;

				for (; char_it != char_end; ++char_it)
					m_select_text.append(char_it->str);
			}
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
				--line_begin_it;
				begin_it = line_begin_it->char_list.end();
				--begin_it;
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
	/**
	 * insert text
	 * @param text
	 * @return insert or not
	 */
	bool InsertText(const char* text)
	{
		if (!m_font) return false;
		if (text && text[0] != 0) m_default_text_mode = false;

		// delete select text
		DeleteSelectText();
		// insert text at cursor
		InsertTextImpl(text);
		// adjust start iterator
		AdjustStartItCloseToCursor((int)m_size.y);
		// reset cursor
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
					--line_begin_it;
					begin_it = line_begin_it->char_list.end();
					--begin_it;
				}
			}
			else
			{
				--begin_it;
				// if adjust forword is soft \n, then then delete end char at last line
				if (begin_it == line_begin_it->char_list.begin() && line_begin_it->force_line == false)
				{
					if (line_begin_it != m_linechar_list.begin())
					{
						--line_begin_it;
						begin_it = line_begin_it->char_list.end();
						--begin_it;
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
			--end_line;
			CharInfoList::iterator end_char = end_line->char_list.end();
			--end_char;
			if (m_line_cursor_it == end_line && m_char_cursor_it == end_char) return false;

			LineCharInfoList::iterator line_begin_it = m_line_cursor_it;
			CharInfoList::iterator begin_it = m_char_cursor_it;
			LineCharInfoList::iterator line_end_it = m_line_cursor_it;
			CharInfoList::iterator end_it = m_char_cursor_it;

			end_char = line_end_it->char_list.end();
			--end_char;
			// if at end char of line, then adjust next line at first char
			if (end_it == end_char)
			{
				if (line_end_it != end_line)
				{
					// set start position
					++line_end_it;
					end_it = line_end_it->char_list.begin();
					// if not a force line, then dec end_it
					if (line_end_it->force_line == false)
					{
						++end_it;
						// check param
						if (end_it == line_end_it->char_list.end())
							--end_it;
					}
				}
			}
			else
			{
				++end_it;
			}
			// delete text
			DeleteTextImpl(line_begin_it, begin_it, line_end_it, end_it);
		}

		// reset cursor
		ResetCursor();

		return true;
	}

	//=====================================================================================
private:
	/**
	 * offset cursor left or right
	 * @param left true: offset left, false: offset right
	 */
	void CursorOffsetLRImpl(bool left)
	{
		if (left)
		{
			// if cursor already at first line and first char then return
			if (m_line_cursor_it == m_linechar_list.begin()
				&& m_char_cursor_it == m_line_cursor_it->char_list.begin()) return;

			// If the cursor and the starting line same
			if (m_line_cursor_it == m_line_start_it)
			{
				// If it is in the first character, need to upgrade a walk
				if (m_char_cursor_it == m_line_cursor_it->char_list.begin())
				{
					// The cursor line minus one, starting line minus one
					--m_line_cursor_it;
					--m_line_start_it;
					// The cursor to take the last character
					m_char_cursor_it = m_line_cursor_it->char_list.end();
					--m_char_cursor_it;
					m_need_redraw = true;
				}
				// Otherwise go directly one character at a time
				else
				{
					--m_char_cursor_it;
				}
			}
			// If the cursor and the starting line not the same
			else
			{
				// If it is the first character
				if (m_char_cursor_it == m_line_cursor_it->char_list.begin())
				{
					// The cursor minus one
					--m_line_cursor_it;
					// The cursor to take the last character
					m_char_cursor_it = m_line_cursor_it->char_list.end();
					--m_char_cursor_it;
				}
				// Otherwise go directly one character at a time
				else
				{
					--m_char_cursor_it;
				}
			}

			ResetCursor();
			return;
		}

		LineCharInfoList::iterator end_line_it = m_linechar_list.end();
		--end_line_it;
		CharInfoList::iterator end_char_it = end_line_it->char_list.end();
		--end_char_it;

		// Is the last character, just returned directly
		if (m_line_cursor_it == end_line_it && m_char_cursor_it == end_char_it) return;

		// Gets the current lines of the last character
		end_char_it = m_line_cursor_it->char_list.end();
		--end_char_it;
		// If it is in the final one character at a time, down to a walk
		if (m_char_cursor_it == end_char_it)
		{
			// The cursor line plus one
			++m_line_cursor_it;
			// The cursor in the first character
			m_char_cursor_it = m_line_cursor_it->char_list.begin();
		}
		// Otherwise directly go back one character at a time
		else
		{
			++m_char_cursor_it;
		}

		// Adjust the starting position
		AdjustStartItCloseToCursor((int)m_size.y);

		ResetCursor();
	}
	/**
	 * offset cursor up or down
	 * @param up true: offset up, false: offset down
	 */
	void CursorOffsetUDImpl(bool up)
	{
		if (up)
		{
			// If is the first line, then returned directly
			if (m_line_cursor_it == m_linechar_list.begin()) return;

			// Access to offset width
			int offset_x = m_char_cursor_it->acc_width;

			// If is the starting line, then starting line minus one
			if (m_line_cursor_it == m_line_start_it)
			{
				--m_line_start_it;
				m_need_redraw = true;
			}
			// The cursor line minus one
			--m_line_cursor_it;

			// According to the offset to reposition the column location
			m_char_cursor_it = m_line_cursor_it->char_list.begin();
			CharInfoList::iterator end_char_it = m_line_cursor_it->char_list.end();
			for (; m_char_cursor_it != end_char_it; ++m_char_cursor_it)
			{
				if (m_char_cursor_it->acc_width >= offset_x) break;
			}
			if (m_char_cursor_it == end_char_it)
			{
				--end_char_it;
				m_char_cursor_it = end_char_it;
			}

			ResetCursor();
			return;
		}

		// If is the last line, then returned directly
		LineCharInfoList::iterator line_end_test_it = m_linechar_list.end();
		--line_end_test_it;
		if (m_line_cursor_it == line_end_test_it) return;
		// Access to offset width
		int offset_x = m_char_cursor_it->acc_width;
		// The cursor down one line
		++m_line_cursor_it;

		// According to the offset to reposition the column location
		m_char_cursor_it = m_line_cursor_it->char_list.begin();
		CharInfoList::iterator end_char_it = m_line_cursor_it->char_list.end();
		for (; m_char_cursor_it != end_char_it; ++m_char_cursor_it)
		{
			if (m_char_cursor_it->acc_width >= offset_x) break;
		}
		if (m_char_cursor_it == end_char_it)
		{
			--end_char_it;
			m_char_cursor_it = end_char_it;
		}

		AdjustStartItCloseToCursor((int)m_size.y);

		ResetCursor();
	}
	/**
	 * get iterator by offset x and y
	 * @param offset_x
	 * @param offset_y
	 * @return line_it_result
	 * @return char_it_result
	 */
	void GetIteratorByOffset(float offset_x, float offset_y, LineCharInfoList::iterator* line_it_result, CharInfoList::iterator* char_it_result)
	{
		LineCharInfoList::iterator line_it = m_line_start_it;
		LineCharInfoList::iterator line_end_it = m_linechar_list.end();

		// Get the total offset
		float real_offset_y = offset_y + m_line_start_it->pre_height;
		while (line_it != line_end_it)
		{
			// If the offset is greater than the current line, then the next line directly
			if (real_offset_y > line_it->acc_height)
			{
				++line_it;
				continue;
			}
			// According to take half the size to determine to a line, or the next line
			float half_line_height = (line_it->acc_height - line_it->pre_height) * 0.5f;
			if (real_offset_y - line_it->acc_height > half_line_height)
				++line_it;

			break;
		}

		// If traversal till the end, then take the last line
		if (line_it == line_end_it)
		{
			--line_end_it;
			line_it = line_end_it;
		}

		// Set the result row
		*line_it_result = line_it;

		float real_offset_x = offset_x;

		CharInfoList::iterator char_it = line_it->char_list.begin();
		CharInfoList::iterator char_end_it = line_it->char_list.end();
		while (char_it != char_end_it)
		{
			if (real_offset_x > char_it->acc_width)
			{
				++char_it;
				continue;
			}

			float half_char_width = (char_it->acc_width - char_it->pre_width) * 0.5f;
			if (real_offset_x - char_it->pre_width < half_char_width && char_it != line_it->char_list.begin())
				--char_it;

			break;
		}
		// If through until the end, then take the last character
		if (char_it == char_end_it)
		{
			--char_end_it;
			char_it = char_end_it;
		}

		*char_it_result = char_it;
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
	void CursorOffsetLR(bool left)
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
	/**
	 * offset select cursor left or right
	 * @param left true: offset left, false: offset right
	 */
	void SelectCursorOffsetLR(bool left)
	{
		// init select iterator
		if (m_char_select_it == m_line_select_it->char_list.end())
		{
			m_line_select_it = m_line_cursor_it;
			m_char_select_it = m_char_cursor_it;
		}

		CursorOffsetLRImpl(left);
	}
	/**
	 * offset cursor up or down
	 * @param up true: offset up, false: offset down
	 */
	void CursorOffsetUD(bool up)
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
	/**
	 * offset select cursor up and down
	 * @param up true: offset up, false: offset down
	 */
	void SelectCursorOffsetUD(bool up)
	{
		// init select iterator
		if (m_char_select_it == m_line_select_it->char_list.end())
		{
			m_line_select_it = m_line_cursor_it;
			m_char_select_it = m_char_cursor_it;
		}

		CursorOffsetUDImpl(up);
	}
	/**
	 * offset cursor to home
	 */
	void SetCursorToHome()
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
	/**
	 * offset cursor to end
	 */
	void SetCursorToEnd()
	{
		m_line_select_it = m_linechar_list.begin();
		m_char_select_it = m_line_select_it->char_list.end();

		m_line_cursor_it = m_linechar_list.end();
		--m_line_cursor_it;
		m_char_cursor_it = m_line_cursor_it->char_list.end();
		--m_char_cursor_it;

		AdjustStartItCloseToCursor((int)m_size.y);
		ResetCursor();
	}
	/**
	 * select all text
	 */
	void SelectAll()
	{
		m_line_select_it = m_linechar_list.begin();
		m_char_select_it = m_line_select_it->char_list.begin();

		m_line_cursor_it = m_linechar_list.end();
		--m_line_cursor_it;
		m_char_cursor_it = m_line_cursor_it->char_list.end();
		--m_char_cursor_it;

		AdjustStartItCloseToCursor((int)m_size.y);

		ResetCursor();
	}
	/**
	 * set cursor offset by x and y
	 * @param offset_x
	 * @param offset_y
	 */
	void ClickCursor(float offset_x, float offset_y)
	{
		m_char_select_it = m_line_select_it->char_list.end();

		// set cursor position
		GetIteratorByOffset(offset_x, offset_y, &m_line_cursor_it, &m_char_cursor_it);

		AdjustStartItCloseToCursor((int)m_size.y);

		ResetCursor();
	}
	/**
	 * set cursor offset by x and y
	 * @param offset_x
	 * @param offset_y
	 */
	bool ClickWordCursor(float offset_x, float offset_y)
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
					&& !CarpString::IsNumber(m_char_cursor_it->str[0])
					&& !CarpString::IsLetter(m_char_cursor_it->str[0]))
				{
					has_find = true;
					break;
				}
				if (m_char_cursor_it == m_line_cursor_it->char_list.begin()) break;
				--m_char_cursor_it;
			}
			if (has_find) break;
			if (m_line_cursor_it == m_linechar_list.begin()) break;

			--m_line_cursor_it;
			m_char_cursor_it = m_line_cursor_it->char_list.end();
			--m_char_cursor_it;
		}

		// find char to right
		CharInfoList::iterator cursor_tmp = m_char_select_it;
		LineCharInfoList::iterator line_cursor_tmp = m_line_select_it;
		while (true)
		{
			++cursor_tmp;
			if (cursor_tmp == m_line_select_it->char_list.end())
			{
				++line_cursor_tmp;
				if (line_cursor_tmp == m_linechar_list.end()) break;
				cursor_tmp = line_cursor_tmp->char_list.begin();
			}
			if (cursor_tmp->str.size() == 1
				&& cursor_tmp->str[0] != '_'
				&& !CarpString::IsNumber(cursor_tmp->str[0])
				&& !CarpString::IsLetter(cursor_tmp->str[0]))
				break;
			m_char_select_it = cursor_tmp;
			m_line_select_it = line_cursor_tmp;
		}

		if (m_line_select_it == m_linechar_list.end())
		{
			--m_line_select_it;
			m_char_select_it = m_line_select_it->char_list.end();
		}
		if (m_char_select_it == m_line_select_it->char_list.end())
			--m_char_select_it;

		if (m_line_select_it == m_line_cursor_it && m_char_select_it == m_char_cursor_it)
			m_char_select_it = m_line_select_it->char_list.end();

		AdjustStartItCloseToCursor((int)m_size.y);

		ResetCursor();

		return m_char_select_it != m_line_select_it->char_list.end();
	}
	/**
	 * cursor drag begin
	 */
	void DragCursorBegin()
	{
		m_line_select_it = m_line_cursor_it;
		m_char_select_it = m_char_cursor_it;
	}
	/**
	 * cursor draging
	 * @param offset_x
	 * @param offset_y
	 */
	void DragCursor(float offset_x, float offset_y)
	{
		// set cursor position
		GetIteratorByOffset(offset_x, offset_y, &m_line_cursor_it, &m_char_cursor_it);

		// if start line behind the cursor then rejuse to pre until the first line
		if (m_line_start_it->pre_height >= m_line_cursor_it->pre_height)
		{
			while (m_line_start_it != m_linechar_list.begin() && m_line_start_it->pre_height >= m_line_cursor_it->pre_height)
			{
				--m_line_start_it;
				m_need_redraw = true;
			}
			ResetCursor();
			return;
		}

		// adjust start iterator
		if (m_line_cursor_it->acc_height - m_line_start_it->pre_height > (int)m_size.y)
			AdjustStartItCloseToCursor((int)m_size.y);

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
	int GetCursorY() { return m_cursor.GetY(); }
	/**
	 * get cursor height
	 * @return height
	 */
	int GetCursorHeight() { return m_cursor.GetHeight(); }

public:
	void NeedDraw() { m_need_redraw = true; }
	void Render(const CarpMatrix2D& parent, bool parent_changed)
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

		if (m_select_1.GetVisible() || m_select_2.GetVisible() || m_select_3.GetVisible())
		{
			m_select_1.Render(m_global_matrix, global_changed);
			m_select_2.Render(m_global_matrix, global_changed);
			m_select_3.Render(m_global_matrix, global_changed);
		}
		else
			m_cursor.Render(m_global_matrix, global_changed);
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
		if (!m_font || m_linechar_list.size() == 0 || m_size.x <= 0 || m_size.y <= 0) return;

		// get line gap
		int line_skip = m_font->GetLineSkip();

		// create surface
		SDL_Surface* total_surface = ALittleSurface::CreateSurface((int)m_size.x, (int)m_size.y);
		if (!total_surface)
		{
			CARP_ERROR(SDL_GetError());
			return;
		}

		// According to the width of the current height, 
		// capture the real to apply colours to a drawing of that part of the string
		int remain_height = (int)m_size.y;
		LineCharInfoList::iterator line_start_it = m_line_start_it;
		while (line_start_it != m_linechar_list.end())
		{
			std::string content;
			// The traversal, add text to the content of the \t into four Spaces, filtering \r \n
			CharInfoList::iterator it, end = line_start_it->char_list.end();
			for (it = line_start_it->char_list.begin(); it != end; ++it)
			{
				if (it->str == "\t")
					content.append("    ");
				else if (it->str == "\r" || it->str == "\n")
					continue;
				else
					content.append(it->str);
			}

			// If there is a text, then perform rendering, copying the surface
			if (content.size())
			{
				SDL_Surface* surface = s_alittle_font.CreateSurface(m_font, content.c_str());
				if (!surface)
				{
					CARP_ERROR("g_DisplaySystem.CreateSurface failed!");
					SDL_FreeSurface(total_surface);
					return;
				}
				SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);

				// copy surface
				SDL_Rect src_rect;
				src_rect.x = 0;
				src_rect.w = (int)(surface->w < (int)m_size.x ? surface->w : (int)m_size.x);
				src_rect.y = 0;
				src_rect.h = (int)(surface->h < remain_height ? surface->h : remain_height);

				SDL_Rect dst_rect;
				dst_rect.x = 0;
				dst_rect.y = (int)((int)m_size.y - remain_height);
				dst_rect.w = src_rect.w;
				dst_rect.h = src_rect.h;

				SDL_BlitSurface(surface, &src_rect, total_surface, &dst_rect);
				SDL_FreeSurface(surface);
			}

			// Remaining highly removes line_skip
			remain_height -= line_skip;
			// If the residual height has < = 0 then exit the loop
			if (remain_height <= 0) break;
			++line_start_it;
		}

		m_texture = new ALittleSurfaceTexture(total_surface);
	}

private:
	bool m_need_redraw = false;

private:
	unsigned int m_cursor_width = 1;
	//////////////////////////////////////////////////////////////////////////////
		// all text
	std::string m_text;
	// select text
	std::string m_select_text;
	// all char info
	LineCharInfoList m_linechar_list;
	// font object
	CarpFont* m_font = nullptr;
	std::string m_font_path;
	unsigned int m_font_size = 0;
	// font style
	unsigned int m_font_style = CARP_FONT_STYLE_NORMAL;
	// default mode or not
	bool m_default_text_mode = true;
	// default text alpha
	unsigned char m_default_text_alpha = 255;
	//////////////////////////////////////////////////////////////////////////////
private:
	// start line iterator
	LineCharInfoList::iterator m_line_start_it;

	// cursor line iterator
	LineCharInfoList::iterator m_line_cursor_it;
	// cursor char iterator
	CharInfoList::iterator m_char_cursor_it;

	// select line iterator
	LineCharInfoList::iterator m_line_select_it;
	// select char iterator
	CharInfoList::iterator m_char_select_it;

	/////////////////////////////////////////////////////////////////////////////
private:
	ALittleQuad m_cursor;

private:
	ALittleQuad m_select_1;		// selected area 1
	ALittleQuad m_select_2;		// selected area 2
	ALittleQuad m_select_3;		// selected area 3

/////////////////////////////////////////////////////////////////////////////
private:
	void GetCharSize(const char* text, int& width, int& height)
	{
		// get font height
		height = m_font->GetFontHeight();

		// find text height
		std::map<std::string, int>::iterator it = m_width_map.find(text);
		if (it != m_width_map.end())
		{
			width = it->second;
			return;
		}

		width = m_font->CutTextWidth(text);
		// save size
		m_width_map[text] = width;
	}
	std::map<std::string, int> m_width_map;		// cache char width
};

#endif
