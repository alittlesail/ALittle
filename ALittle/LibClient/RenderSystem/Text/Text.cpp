
#include "Text.h"

#include "ALittle/LibClient/RenderSystem/DisplaySystem.h"
#include "ALittle/LibClient/RenderSystem/RenderSystem.h"
#include "ALittle/LibClient/RenderSystem/Texture/SurfaceTexture.h"

#include "Carp/carp_log.hpp"
#include "Carp/carp_font.hpp"

namespace ALittle
{

std::unordered_map<CarpFont*, std::unordered_map<std::string, TextTextureInfo*>> Text::s_texture_map;

TextTextureInfo* Text::CreateTextureInfo(CarpFont* font, const std::string& text)
{
	auto& text_map = s_texture_map[font];
	auto it = text_map.find(text);
	if (it != text_map.end())
	{
		++it->second->ref_count;
		return it->second;
	}

	// create surface
	SDL_Surface* surface = g_DisplaySystem.CreateSurface(font, text.c_str());
	if (!surface)
	{
		CARP_ERROR("Font Helper create surface failed!");
		return 0;
	}

	if (surface->w <= 0 || surface->h <= 0)
	{
		CARP_ERROR("surface:(w, h)=(" << surface->w << ", " << surface->h << ")");
		return 0;
	}

	auto* info = new TextTextureInfo();
	info->font = font;
	info->ref_count = 1;
	info->text = text;
	info->texture = new SurfaceTexture(surface);
	text_map[text] = info;

	return info;
}

void Text::ReleaseTextureInfo(TextTextureInfo* info)
{
	--info->ref_count;
	if (info->ref_count > 0) return;

	auto text_it = s_texture_map.find(info->font);
	if (text_it == s_texture_map.end()) return;
	auto font_it = text_it->second.find(info->text);
	if (font_it == text_it->second.end()) return;

	delete font_it->second->texture;
	delete font_it->second;
	text_it->second.erase(font_it);
	if (text_it->second.empty()) s_texture_map.erase(text_it);
}

Text::Text()
: m_need_redraw(false)
, m_calc_real_size(false)
, m_font(0), m_font_style(CARP_FONT_STYLE_NORMAL)
, m_real_width(0), m_real_height(0)
, m_texture_info(0), m_font_size(0)
{ }

Text::~Text()
{
	if (m_texture_info)
	{
		ReleaseTextureInfo(m_texture_info);
		m_texture_info = 0;
		m_texture = 0;
		m_real_width = m_real_height = 0;
	}
}

unsigned int Text::GetRealWidth()
{
	if (m_calc_real_size == true) return m_real_width;

	if (m_text.empty()) return 0;
	if (m_font_path.empty()) return 0;
	if (m_font_size == 0) return 0;
	if (m_font == 0) m_font = g_DisplaySystem.GetFont(m_font_path.c_str(), m_font_style, m_font_size);
	if (m_font == 0) return 0;

	// calc size
	m_real_width = m_font->CutTextWidth(m_text.c_str());
	m_real_height = m_font->GetFontHeight();

	m_calc_real_size = true;

	return m_real_width;
}

unsigned int Text::GetRealHeight()
{
	if (m_calc_real_size == true) return m_real_height;

	if (m_text.empty()) return 0;
	if (m_font_path.empty()) return 0;
	if (m_font_size == 0) return 0;

	if (m_font == 0)
		m_font = g_DisplaySystem.GetFont(m_font_path.c_str(), m_font_style, m_font_size);
	if (m_font == 0) return 0;

	// calc size
	m_real_width = m_font->CutTextWidth(m_text.c_str());
	m_real_height = m_font->GetFontHeight();

	m_calc_real_size = true;
	return m_real_height;
}

void Text::AdjustSize()
{
	SetWidth((float)m_real_width);
	SetHeight((float)m_real_height);
}

void Text::Render(const Matrix2D& parent, bool parent_changed)
{
	if (m_clip) return;
	if (!m_visible) return;
	if (m_color.a <= 0) return;

	if (m_need_redraw)
	{
		Draw();
		m_need_redraw = false;
		m_calc_real_size = true;
		SetSelfMatrixDirty();
	}

	if (m_texture == 0) return;

	UpdateGlobalMatrix2D(parent, parent_changed);
	UpdateVertexCoord();
	UpdateTextureCoord();

	m_texture->Render(m_color, m_vertex_coord, m_texture_coord);
}

void Text::SetFont(const char* font_path, unsigned int font_size)
{
	if (m_font_path == font_path && m_font_size == font_size) return;
	m_font_path = font_path;
	m_font_size = font_size;
	m_font = 0;

	m_need_redraw = true;
	m_calc_real_size = false;
}

void Text::SetText(const char* text)
{
	if (!text) return;

	m_text.assign(text);

	m_need_redraw = true;
	m_calc_real_size = false;
}

void Text::Draw()
{
	// release current texture
	if (m_texture_info)
	{
		ReleaseTextureInfo(m_texture_info);
		m_texture_info = 0;
		m_texture = 0;
		m_real_width = m_real_height = 0;
	}

	if (m_text.empty()) return;
	if (m_font == 0) m_font = g_DisplaySystem.GetFont(m_font_path.c_str(), m_font_style, m_font_size);
	if (m_font == 0) return;

	m_texture_info = CreateTextureInfo(m_font, m_text);
	if (m_texture_info == 0) return;
	m_texture = m_texture_info->texture;
	m_real_width = m_texture_info->texture->GetWidth();
	m_real_height = m_texture_info->texture->GetHeight();
}

void Text::SetBold(bool bold)
{
	bool is_bold = (m_font_style & CARP_FONT_STYLE_BOLD) != 0;
	if (is_bold == bold) return;

	if (bold)
		m_font_style |= CARP_FONT_STYLE_BOLD;
	else
		m_font_style &= ~CARP_FONT_STYLE_BOLD;

	m_font = 0;
	m_need_redraw = true;
	m_calc_real_size = false;
}

void Text::SetUnderline(bool underline)
{
	bool is_underline = (m_font_style & CARP_FONT_STYLE_UNDERLINE) != 0;
	if (is_underline == underline) return;

	if (underline)
		m_font_style |= CARP_FONT_STYLE_UNDERLINE;
	else
		m_font_style &= ~CARP_FONT_STYLE_UNDERLINE;

	m_font = 0;
	m_need_redraw = true;
	m_calc_real_size = false;
}

void Text::SetDeleteline(bool deleteline)
{
	bool is_deleteline = (m_font_style & CARP_FONT_STYLE_DELETELINE) != 0;
	if (is_deleteline == deleteline) return;

	if (deleteline)
		m_font_style |= CARP_FONT_STYLE_DELETELINE;
	else
		m_font_style &= ~CARP_FONT_STYLE_DELETELINE;

	m_font = 0;
	m_need_redraw = true;
	m_calc_real_size = false;
}

void Text::SetItalic(bool italic)
{
	bool is_italic = (m_font_style & CARP_FONT_STYLE_ITALIC) != 0;
	if (is_italic == italic) return;

	if (italic)
		m_font_style |= CARP_FONT_STYLE_ITALIC;
	else
		m_font_style &= ~CARP_FONT_STYLE_ITALIC;

	m_font = 0;
	m_need_redraw = true;
	m_calc_real_size = false;
}

int Text::GetFontHeight()
{
	if (m_font == 0) m_font = g_DisplaySystem.GetFont(m_font_path.c_str(), m_font_style, m_font_size);
	if (m_font == 0) return 0;

	return m_font->GetFontHeight();
}

int Text::CutTextByWidth(float width, const char* content, int max_width)
{
	if (m_font == 0) m_font = g_DisplaySystem.GetFont(m_font_path.c_str(), m_font_style, m_font_size);
	if (m_font == 0) return 0;

	m_calc_width_list.clear();
	return m_font->CutTextByWidth(content, (int)width, max_width, &m_calc_width_list);
}

int Text::CalcTextWidth(const char* content)
{
	if (m_font == 0) m_font = g_DisplaySystem.GetFont(m_font_path.c_str(), m_font_style, m_font_size);
	if (m_font == 0) return 0;

	return m_font->CutTextWidth(content);
}

} // ALittle
