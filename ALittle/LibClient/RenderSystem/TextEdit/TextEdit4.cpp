
#include "TextEdit.h"

#include "ALittle/LibCommon/Helper/LogHelper.h"
#include "ALittle/LibClient/RenderSystem/DisplaySystem.h"
#include "ALittle/LibClient/RenderSystem/RenderSystem.h"

namespace ALittle
{

void TextEdit::CursorOffsetLRImpl(bool left)
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
				-- m_line_cursor_it;
				-- m_line_start_it;
				// The cursor to take the last character
				m_char_cursor_it = m_line_cursor_it->char_list.end();
				-- m_char_cursor_it;
				m_need_redraw = true;
			}
			// Otherwise go directly one character at a time
			else
			{
				-- m_char_cursor_it;
			}
		}
		// If the cursor and the starting line not the same
		else
		{
			// If it is the first character
			if (m_char_cursor_it == m_line_cursor_it->char_list.begin())
			{
				// The cursor minus one
				-- m_line_cursor_it;
				// The cursor to take the last character
				m_char_cursor_it = m_line_cursor_it->char_list.end();
				-- m_char_cursor_it;
			}
			// Otherwise go directly one character at a time
			else
			{
				-- m_char_cursor_it;
			}
		}

		ResetCursor();
		return;
	}

	LineCharInfoList::iterator end_line_it = m_linechar_list.end();
	-- end_line_it;
	CharInfoList::iterator end_char_it = end_line_it->char_list.end();
	-- end_char_it;

	// Is the last character, just returned directly
	if (m_line_cursor_it == end_line_it && m_char_cursor_it == end_char_it) return;

	// Gets the current lines of the last character
	end_char_it = m_line_cursor_it->char_list.end();
	-- end_char_it;
	// If it is in the final one character at a time, down to a walk
	if (m_char_cursor_it == end_char_it)
	{
		// The cursor line plus one
		++ m_line_cursor_it;
		// The cursor in the first character
		m_char_cursor_it = m_line_cursor_it->char_list.begin();
	}
	// Otherwise directly go back one character at a time
	else
	{
		++ m_char_cursor_it;
	}

	// Adjust the starting position
	RejustStartItCloseTOCursor((int)m_size.y);

	ResetCursor();
}

void TextEdit::CursorOffsetUDImpl(bool up)
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
			-- m_line_start_it;
			m_need_redraw = true;
		}
		// The cursor line minus one
		-- m_line_cursor_it;
		
		// According to the offset to reposition the column location
		m_char_cursor_it = m_line_cursor_it->char_list.begin();
		CharInfoList::iterator end_char_it = m_line_cursor_it->char_list.end();
		for (; m_char_cursor_it != end_char_it; ++ m_char_cursor_it)
		{
			if (m_char_cursor_it->acc_width >= offset_x) break;
		}
		if (m_char_cursor_it == end_char_it)
		{
			-- end_char_it;
			m_char_cursor_it = end_char_it;
		}

		ResetCursor();
		return;
	}

	// If is the last line, then returned directly
	LineCharInfoList::iterator line_end_test_it = m_linechar_list.end();
	-- line_end_test_it;
	if (m_line_cursor_it == line_end_test_it) return;
	// Access to offset width
	int offset_x = m_char_cursor_it->acc_width;
	// The cursor down one line
	++ m_line_cursor_it;

	// According to the offset to reposition the column location
	m_char_cursor_it = m_line_cursor_it->char_list.begin();
	CharInfoList::iterator end_char_it = m_line_cursor_it->char_list.end();
	for (; m_char_cursor_it != end_char_it; ++ m_char_cursor_it)
	{
		if (m_char_cursor_it->acc_width >= offset_x) break;
	}
	if (m_char_cursor_it == end_char_it)
	{
		-- end_char_it;
		m_char_cursor_it = end_char_it;
	}

	RejustStartItCloseTOCursor((int)m_size.y);

	ResetCursor();
}

void TextEdit::GetIteratorByOffset(float offset_x, float offset_y, LineCharInfoList::iterator* line_it_result, CharInfoList::iterator* char_it_result)
{
	LineCharInfoList::iterator line_it = m_line_start_it;
	LineCharInfoList::iterator line_end_it = m_linechar_list.end();

	// Get the total offset
	float real_offset_y = offset_y + m_line_start_it->pre_height;
	while(line_it != line_end_it)
	{
		// If the offset is greater than the current line, then the next line directly
		if (real_offset_y > line_it->acc_height)
		{
			++ line_it;
			continue;
		}
		// According to take half the size to determine to a line, or the next line
		float half_line_height = (line_it->acc_height - line_it->pre_height) * 0.5f;
		if (real_offset_y - line_it->acc_height > half_line_height)
			++ line_it;

		break;
	}

	// If traversal till the end, then take the last line
	if (line_it == line_end_it)
	{
		-- line_end_it;
		line_it = line_end_it;
	}

	// Set the result row
	*line_it_result = line_it;

	float real_offset_x = offset_x;

	CharInfoList::iterator char_it = line_it->char_list.begin();
	CharInfoList::iterator char_end_it = line_it->char_list.end();
	while(char_it != char_end_it)
	{
		if (real_offset_x > char_it->acc_width)
		{
			++ char_it;
			continue;
		}

		float half_char_width = (char_it->acc_width - char_it->pre_width) * 0.5f;
		if (real_offset_x - char_it->pre_width < half_char_width && char_it != line_it->char_list.begin())
			-- char_it;

		break;
	}
	// If through until the end, then take the last character
	if (char_it == char_end_it)
	{
		-- char_end_it;
		char_it = char_end_it;
	}

	*char_it_result = char_it;
}

} // ALittle
