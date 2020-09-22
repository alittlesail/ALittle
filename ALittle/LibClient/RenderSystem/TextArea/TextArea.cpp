
#include "TextArea.h"
#include "ALittle/LibCommon/Helper/LogHelper.h"
#include "ALittle/LibCommon/Helper/StringHelper.h"
extern "C" {
#include "ALittle/LibCommon/ThirdParty/utf8/utf8.h"
}

#include "ALittle/LibClient/RenderSystem/DisplaySystem.h"
#include "ALittle/LibClient/RenderSystem/RenderSystem.h"
#include "ALittle/LibClient/RenderSystem/Texture/SurfaceTexture.h"
#include "Carp/carp_font.hpp"
#include <vector>

namespace ALittle
{

TextArea::TextArea()
: m_need_redraw(false)
, m_font(0), m_font_style(CARP_FONT_STYLE_NORMAL)
, m_halign(HALIGN_LEFT), m_valign(VALIGN_TOP)
, m_real_height(0), m_font_size(0)
{ }

TextArea::~TextArea()
{
	if (m_texture)
	{
		delete m_texture;
		m_texture = 0;
	}
}

void TextArea::Render(const Matrix2D& parent, bool parent_changed)
{
	if (m_clip) return;
	if (!m_visible) return;
	if (m_color.a <= 0) return;

	if (m_need_redraw)
	{
		Draw(true);
		m_need_redraw = false;
		SetSelfMatrixDirty();
	}

	if (m_texture == 0) return;

	UpdateGlobalMatrix2D(parent, parent_changed);
	UpdateVertexCoord();
	UpdateTextureCoord();

	m_texture->Render(m_color, m_vertex_coord, m_texture_coord);
}

void TextArea::SetFont(const char* font_path, unsigned int font_size)
{
	if (m_font_path == font_path && m_font_size == font_size) return;
	m_font_path = font_path;
	m_font_size = font_size;
	m_font = 0;
	m_need_redraw = true;
}

void TextArea::SetText(const char* text)
{
	if (!text) return;

	m_text.assign(text);
	m_need_redraw = true;
}

void TextArea::Draw(bool draw)
{
	// if texture exist, release first
	if (m_texture)
	{
		delete m_texture;
		m_texture = 0;
	}

	m_real_height = 0;

	if (m_text.empty()) return;
	if (m_font_path.empty()) return;
	if (m_font_size == 0) return;
	if (m_font == 0) m_font = g_DisplaySystem.GetFont(m_font_path.c_str(), m_font_style, m_font_size);
	if (m_font == 0) return;

	int width = (int)m_size.x;
	int height = (int)m_size.y;
	// set total size
	int total_width = width;
	int total_height = height;

	// get font height
	int font_height = m_font->GetFontHeight();
	// start layout
	const char* str = m_text.c_str();
	// remain size
	int width_offset = 0;
	int height_offset = 0;
	int gap = m_font->GetLineGap();
	std::vector<int> height_offset_array, width_offset_array;
	std::vector<std::string> string_array;
	// calc text
	std::string calc_text;
	while(true)
	{
		int byte_count = utf8_GetByteCountOfOneWord(*str);
		
		// check char
		if (byte_count == 1)
		{
			if (*str == '\0')
			{
				width_offset_array.push_back(width_offset);
				height_offset_array.push_back(height_offset);
				string_array.push_back(calc_text);
				
				break;
			}
			else if (*str == '\r')
			{
				str += byte_count;
				continue;
			}
			else if (*str == '\n')
			{
				str += byte_count;

				height_offset_array.push_back(height_offset);
				height_offset = gap + height_offset + font_height;

				width_offset_array.push_back(width_offset);
				string_array.push_back(calc_text);

				width_offset = 0;
				calc_text = "";

				continue;
			}
		}

		std::string next_calc_text = calc_text;
		if (*str == '\t' && byte_count == 1)
			next_calc_text.append("    ");
		else
			next_calc_text.append(str, byte_count);

		int text_width = m_font->CutTextWidth(next_calc_text.c_str());
		int next_width_offset = text_width;

		if (next_width_offset > total_width && calc_text.size())
		{
			height_offset_array.push_back(height_offset);
			height_offset = gap + height_offset + font_height;

			width_offset_array.push_back(width_offset);
			string_array.push_back(calc_text);

			width_offset = 0;
			calc_text = "";

			continue;
		}

		str += byte_count;
		width_offset = next_width_offset;
		calc_text = next_calc_text;
	}
	// total line
	int line_count = static_cast<int>(height_offset_array.size());
	// total height
	m_real_height = height_offset_array[line_count - 1] + font_height;

	// if not need to draw then return
	if (draw == false) return;

	// at least 1*1
	if (total_width < 1 || total_height < 1) return;
	
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
	SDL_Surface* total_surface = SDL_CreateRGBSurface(0, total_width, total_height, 32, rmask, gmask, bmask, amask);
	if (!total_surface)
	{
		ALITTLE_ERROR(SDL_GetError());
		return;
	}

	// set color
	SDL_Color color = { 255, 255, 255, 255 };

	// offset at height
	height_offset = 0;
	if (m_valign == VALIGN_CENTER)
		height_offset = (int)((total_height - m_real_height)*0.5f);
	else if (m_valign == VALIGN_BOTTOM)
		height_offset = total_height - m_real_height;
	// read line
	for (int i = 0; i < line_count; ++i)
	{
		int current_height_offset = height_offset_array[i] + height_offset;
		// check visible or not
		if (current_height_offset > total_height || current_height_offset + font_height <= 0)
			continue;
		// create text surface
		SDL_Surface* surface = g_DisplaySystem.CreateSurface(m_font, string_array[i].c_str());
		if (!surface) continue;
		SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);
		// offset at width
		width_offset = 0;
		if (m_halign == HALIGN_CENTER)
			width_offset = (int)((total_width - surface->w)*0.5f);
		else if (m_halign == HALIGN_RIGHT)
			width_offset = total_width - surface->w;
		// copy surface
		SDL_Rect src_rect;
		src_rect.x = width_offset < 0 ? -width_offset : 0;
		src_rect.w = width_offset < 0 ? total_width : surface->w;
		src_rect.y = current_height_offset < 0 ? -current_height_offset : 0;
		src_rect.h = surface->h - src_rect.y;

		SDL_Rect dst_rect;
		dst_rect.x = width_offset < 0 ? 0 : width_offset;
		dst_rect.y = current_height_offset < 0 ? 0 : current_height_offset;
		dst_rect.w = src_rect.w;
		dst_rect.h = src_rect.h;
		
		SDL_BlitSurface(surface, &src_rect, total_surface, &dst_rect);
		SDL_FreeSurface(surface);
	}
	
	m_texture = new SurfaceTexture(total_surface);
}

void TextArea::SetBold(bool bold)
{
	bool is_bold = (m_font_style & CARP_FONT_STYLE_BOLD) != 0;
	if (is_bold == bold) return;

	if (bold)
		m_font_style |= CARP_FONT_STYLE_BOLD;
	else
		m_font_style &= ~CARP_FONT_STYLE_BOLD;

	m_font = 0;
	m_need_redraw = true;
}

void TextArea::SetUnderline(bool underline)
{
	bool is_underline = (m_font_style & CARP_FONT_STYLE_UNDERLINE) != 0;
	if (is_underline == underline) return;

	if (underline)
		m_font_style |= CARP_FONT_STYLE_UNDERLINE;
	else
		m_font_style &= ~CARP_FONT_STYLE_UNDERLINE;

	m_font = 0;
	m_need_redraw = true;
}

void TextArea::SetDeleteline(bool deleteline)
{
	bool is_deleteline = (m_font_style & CARP_FONT_STYLE_DELETELINE) != 0;
	if (is_deleteline == deleteline) return;

	if (deleteline)
		m_font_style |= CARP_FONT_STYLE_DELETELINE;
	else
		m_font_style &= ~CARP_FONT_STYLE_DELETELINE;

	m_font = 0;
	m_need_redraw = true;
}

void TextArea::SetItalic(bool italic)
{
	bool is_italic = (m_font_style & CARP_FONT_STYLE_ITALIC) != 0;
	if (is_italic == italic) return;

	if (italic)
		m_font_style |= CARP_FONT_STYLE_ITALIC;
	else
		m_font_style &= ~CARP_FONT_STYLE_ITALIC;

	m_font = 0;
	m_need_redraw = true;
}

void TextArea::SetHAlign(int align)
{
	if (m_halign == align) return;

	m_halign = align;
	m_need_redraw = true;
}

void TextArea::SetVAlign(int align)
{
	if (m_valign == align) return;

	m_valign = align;
	m_need_redraw = true;
}

int TextArea::GetRealHeight()
{
	if (m_need_redraw) Draw(false);
	return m_real_height;
}

} // ALittle
