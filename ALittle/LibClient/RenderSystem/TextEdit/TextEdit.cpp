
#include "TextEdit.h"

#include "ALittle/LibCommon/Helper/LogHelper.h"
#include "ALittle/LibClient/RenderSystem/DisplaySystem.h"
#include "ALittle/LibClient/RenderSystem/RenderSystem.h"
#include "ALittle/LibClient/RenderSystem/Texture/SurfaceTexture.h"
#include "ALittle/LibClient/Helper/FontHelper.h"

namespace ALittle
{

TextEdit::TextEdit()
: m_need_redraw(false)
, m_font(0)
, m_font_style(TTF_STYLE_NORMAL)
, m_cursor_width(1), m_font_size(0)
, m_default_text_mode(true), m_default_text_alpha(255)
{
	m_cursor.SetVisible(false);

	m_select_1.SetVisible(false);
	m_select_2.SetVisible(false);
	m_select_3.SetVisible(false);

	ClearText();
}

TextEdit::~TextEdit()
{
	if (m_texture)
	{
		delete m_texture;
		m_texture = 0;
	}
}

void TextEdit::SetWidth(float width)
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

void TextEdit::SetHeight(float height)
{
	height = floor(height);
	if (m_size.y == height) return;
	m_size.y = height;

	AdjustStartItCloseTOCursor((int)height);

	ResetCursor();

	m_self_matrix_dirty = true;
}

void TextEdit::SetCursorRed(float red)
{
	m_cursor.SetRed(red);
	m_select_1.SetRed(red);
	m_select_2.SetRed(red);
	m_select_3.SetRed(red);
}

void TextEdit::SetCursorGreen(float green)
{
	m_cursor.SetGreen(green);
	m_select_1.SetGreen(green);
	m_select_2.SetGreen(green);
	m_select_3.SetGreen(green);
}

void TextEdit::SetCursorBlue(float blue)
{
	m_cursor.SetBlue(blue);
	m_select_1.SetBlue(blue);
	m_select_2.SetBlue(blue);
	m_select_3.SetBlue(blue);
}

void TextEdit::SetCursorAlpha(float alpha)
{
	m_cursor.SetAlpha(alpha);
	m_select_1.SetAlpha(alpha);
	m_select_2.SetAlpha(alpha);
	m_select_3.SetAlpha(alpha);
}

void TextEdit::SetBold(bool bold)
{
	bool is_bold = (m_font_style & TTF_STYLE_BOLD) != 0;
	if (is_bold == bold) return;

	if (bold)
		m_font_style |= TTF_STYLE_BOLD;
	else
		m_font_style &= ~TTF_STYLE_BOLD;

	if (!m_font_path.empty() && m_font_size > 0)
		m_font = g_DisplaySystem.GetFont(m_font_path.c_str(), m_font_style, m_font_size);

	m_width_map.clear();

	std::string text = GetText();

	ClearText();

	InsertTextImpl(text.c_str());

	ResetCursor();
}

void TextEdit::SetUnderline(bool underline)
{
	bool is_underline = (m_font_style & TTF_STYLE_UNDERLINE) != 0;
	if (is_underline == underline) return;

	if (underline)
		m_font_style |= TTF_STYLE_UNDERLINE;
	else
		m_font_style &= ~TTF_STYLE_UNDERLINE;

	if (!m_font_path.empty() && m_font_size > 0)
		m_font = g_DisplaySystem.GetFont(m_font_path.c_str(), m_font_style, m_font_size);

	m_need_redraw = true;
}

void TextEdit::SetDeleteline(bool deleteline)
{
	bool is_deleteline = (m_font_style & TTF_STYLE_STRIKETHROUGH) != 0;
	if (is_deleteline == deleteline) return;

	if (deleteline)
		m_font_style |= TTF_STYLE_STRIKETHROUGH;
	else
		m_font_style &= ~TTF_STYLE_STRIKETHROUGH;

	if (!m_font_path.empty() && m_font_size > 0)
		m_font = g_DisplaySystem.GetFont(m_font_path.c_str(), m_font_style, m_font_size);

	m_need_redraw = true;
}

void TextEdit::SetItalic(bool italic)
{
	bool is_italic = (m_font_style & TTF_STYLE_ITALIC) != 0;
	if (is_italic == italic) return;

	if (italic)
		m_font_style |= TTF_STYLE_ITALIC;
	else
		m_font_style &= ~TTF_STYLE_ITALIC;

	if (!m_font_path.empty() && m_font_size > 0)
		m_font = g_DisplaySystem.GetFont(m_font_path.c_str(), m_font_style, m_font_size);

	m_need_redraw = true;
}

void TextEdit::ShowCursor(bool show)
{
	m_cursor.SetVisible(show);
}
///////////////////////////////////////////////////////////////////////////////////////////
void TextEdit::Render(const Matrix2D& parent, bool parent_changed)
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
			Color4 color = m_color;
			color.a = m_default_text_alpha;
			m_texture->Render(color, m_vertex_coord, m_texture_coord);
		}
		else
		{
			m_texture->Render(m_color, m_vertex_coord, m_texture_coord);
		}
	}

	if (m_select_1.GetVisible()||m_select_2.GetVisible()||m_select_3.GetVisible())
	{
		m_select_1.Render(m_global_matrix, global_changed);
		m_select_2.Render(m_global_matrix, global_changed);
		m_select_3.Render(m_global_matrix, global_changed);
	}
	else
		m_cursor.Render(m_global_matrix, global_changed);
}

void TextEdit::Draw()
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
	int line_skip = TTF_FontLineSkip(m_font);

	// create surface
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	int rmask = 0xff000000;
	int gmask = 0x00ff0000;
	int bmask = 0x0000ff00;
	int amask = 0x000000ff;
#else
	int rmask = 0x000000ff;
	int gmask = 0x0000ff00;
	int bmask = 0x00ff0000;
	int amask = 0xff000000;
#endif
	SDL_Surface* total_surface = SDL_CreateRGBSurface(0, (int)m_size.x, (int)m_size.y, 32, rmask, gmask, bmask, amask);
	if (!total_surface)
	{
		ALITTLE_ERROR(SDL_GetError());
		return;
	}

	// init color
	SDL_Color color = { 255, 255, 255, 255 };

	// According to the width of the current height, 
	// capture the real to apply colours to a drawing of that part of the string
	int remain_height = (int)m_size.y;
	LineCharInfoList::iterator line_start_it = m_line_start_it;
	while(line_start_it != m_linechar_list.end())
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
			SDL_Surface* surface = TTF_RenderUTF8_Blended(m_font, content.c_str(), color);
			if (!surface)
			{
				ALITTLE_ERROR(TTF_GetError());
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
		++ line_start_it;
	}

	m_texture = new SurfaceTexture(total_surface);
}

} // ALittle
