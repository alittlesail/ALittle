
#include "TextInput.h"

#include "ALittle/LibClient/RenderSystem/Texture/SurfaceTexture.h"
#include "ALittle/LibClient/RenderSystem/DisplaySystem.h"
#include "ALittle/LibClient/RenderSystem/RenderSystem.h"
#include "ALittle/LibClient/Helper/FontHelper.h"

#include "ALittle/LibCommon/Helper/LogHelper.h"

namespace ALittle
{

TextInput::TextInput()
: m_need_redraw(false)
, m_font(0)
, m_real_width(0), m_real_height(0)
, m_font_style(TTF_STYLE_NORMAL)
, m_cursor_width(1), m_font_size(0)
, m_password_mode(false), m_default_text_mode(true), m_default_text_alpha(255)
{
	m_cursor.SetVisible(false);

	ClearText();
}

TextInput::~TextInput()
{
	if (m_texture)
	{
		delete m_texture;
		m_texture = 0;
		m_real_width = m_real_height = 0;
	}
}

void TextInput::SetWidth(float width)
{
	width = floor(width);
	if (m_size.x == width) return;

	if (width > m_real_width || width < m_real_width)
		m_need_redraw = true;

	m_size.x = (float)width;

	m_self_matrix_dirty = true;
}

void TextInput::SetHeight(float height)
{
	height = floor(height);
	m_size.y = height;

	m_cursor.SetHeight(height);

	m_self_matrix_dirty = true;
}

void TextInput::SetCursorRed(float red)
{
	m_cursor.SetRed(red);
}

void TextInput::SetCursorGreen(float green)
{
	m_cursor.SetGreen(green);
}

void TextInput::SetCursorBlue(float blue)
{
	m_cursor.SetBlue(blue);
}

void TextInput::SetCursorAlpha(float alpha)
{
	m_cursor.SetAlpha(alpha);
}

void TextInput::SetBold(bool bold)
{
	bool is_bold = (m_font_style & TTF_STYLE_BOLD) != 0;
	if (is_bold == bold) return;

	if (bold)
		m_font_style |= TTF_STYLE_BOLD;
	else
		m_font_style &= ~TTF_STYLE_BOLD;

	if (!m_font_path.empty() && m_font_size > 0)
		m_font = g_DisplaySystem.GetFont(m_font_path.c_str(), m_font_style, m_font_size);

	std::string text = GetText();

	ClearText();

	InsertTextImpl(text.c_str());

	ResetCursor();
}

void TextInput::SetUnderline(bool underline)
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

void TextInput::SetDeleteline(bool deleteline)
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

void TextInput::SetItalic(bool italic)
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

void TextInput::ShowCursor(bool show)
{
	m_cursor.SetVisible(show);
}
///////////////////////////////////////////////////////////////////////////////////////////
void TextInput::Render(const Matrix2D& parent, bool parent_changed)
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

	m_cursor.Render(m_global_matrix, global_changed);
}

void TextInput::UpdateVertexCoord()
{
	if (!m_vertex_dirty) return;
	m_vertex_dirty = false;

	Vector2D coord[4];
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

void TextInput::Draw()
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
	while(char_it != m_char_list.end())
	{
		if ((int)m_size.x < char_it->acc_width - m_start_it->pre_width) break;
		if (!m_default_text_mode && m_password_mode && char_it->str.size())
			content.append("*");
		else
			content.append(char_it->str);
		++ char_it;
	}
	
	// init color
	SDL_Color color = { 255, 255, 255, 255 };
	// render text to surface
	if (content.size() == 0) return;
	SDL_Surface* surface = TTF_RenderUTF8_Blended(m_font, content.c_str(), color);
	if (!surface)
	{
		ALITTLE_ERROR(TTF_GetError());
		return;
	}

	// save size
	m_real_width = surface->w;
	m_real_height = surface->h;

	m_texture = new SurfaceTexture(surface);
	m_vertex_dirty = true;
}

void TextInput::SetPasswordMode(bool mode)
{
	if (m_password_mode == mode) return;

	m_password_mode = mode;

	std::string text = GetText();

	ClearText();

	InsertTextImpl(text.c_str());

	ResetCursor();
}

} // ALittle
