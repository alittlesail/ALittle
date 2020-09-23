
#include "TextInput.h"

#include "ALittle/LibClient/RenderSystem/DisplaySystem.h"
#include "ALittle/LibClient/RenderSystem/RenderSystem.h"

namespace ALittle
{

void TextInput::CursorOffsetImpl(bool left)
{
	if (left)
	{
		if (m_cursor_it == m_char_list.begin()) return;

		if (m_cursor_it != m_start_it)
		{
			-- m_cursor_it;

			ResetCursor();
			return;
		}

		-- m_cursor_it;
		-- m_start_it;

		m_need_redraw = true;

		AdjustStartItAwayFromCursor((int)m_size.x / 2);

		ResetCursor();
		return;
	}

	if (m_cursor_it->str.size() == 0) return;

	++ m_cursor_it;
	AdjustStartItCloseTOCursor((int)m_size.x);

	ResetCursor();
}

TextInput::CharInfoList::iterator TextInput::GetIteratorByOffset(float offset)
{
	// Starting from the text
	float real_offset = offset + m_start_it->pre_width;

	std::list<CharInfo>::iterator cursor_it = m_start_it;
	while(cursor_it->str.size())
	{
		if (real_offset > cursor_it->acc_width)
		{
			++ cursor_it;
			continue;
		}

		float half_char_width = (cursor_it->acc_width - cursor_it->pre_width) * 0.5f;
		if (real_offset - cursor_it->pre_width > half_char_width)
			++ cursor_it;

		break;
	}

	return cursor_it;
}

} // ALittle
