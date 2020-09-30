#ifndef ALITTLE_TEXTAREA_INCLUDED
#define ALITTLE_TEXTAREA_INCLUDED

#include "SDL.h"
#include "alittle_displayobject.hpp"
#include "alittle_font.hpp"
#include "alittle_image.hpp"
#include "alittle_texture.hpp"
#include "Carp/carp_font.hpp"

class ALittleTextArea : public ALittleImage
{
public:
	ALittleTextArea() {}
	~ALittleTextArea() { delete m_texture; }

	static void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.deriveClass<ALittleTextArea, ALittleImage>("__CPPAPITextArea")
			.addConstructor<void(*)()>()
			.addFunction("SetScaleX", &ALittleTextArea::SetScaleX)
			.addFunction("SetScaleY", &ALittleTextArea::SetScaleY)
			.addFunction("SetCenterX", &ALittleTextArea::SetCenterX)
			.addFunction("SetCenterY", &ALittleTextArea::SetCenterY)
			.addFunction("SetAngle", &ALittleTextArea::SetAngle)
			.addFunction("SetX", &ALittleTextArea::SetX)
			.addFunction("SetY", &ALittleTextArea::SetY)
			.addFunction("SetWidth", &ALittleTextArea::SetWidth)
			.addFunction("SetHeight", &ALittleTextArea::SetHeight)
			.addFunction("SetRed", &ALittleTextArea::SetRed)
			.addFunction("SetGreen", &ALittleTextArea::SetGreen)
			.addFunction("SetBlue", &ALittleTextArea::SetBlue)
			.addFunction("SetAlpha", &ALittleTextArea::SetAlpha)
			.addFunction("SetFont", &ALittleTextArea::SetFont)
			.addFunction("SetText", &ALittleTextArea::SetText)
			.addFunction("GetRealHeight", &ALittleTextArea::GetRealHeight)
			.addFunction("SetVisible", &ALittleTextArea::SetVisible)
			.addFunction("SetBold", &ALittleTextArea::SetBold)
			.addFunction("SetDeleteline", &ALittleTextArea::SetDeleteline)
			.addFunction("SetUnderline", &ALittleTextArea::SetUnderline)
			.addFunction("SetItalic", &ALittleTextArea::SetItalic)
			.addFunction("SetClip", &ALittleTextArea::SetClip)
			.addFunction("SetFlip", &ALittleTextArea::SetFlip)
			.addFunction("SetHAlign", &ALittleTextArea::SetHAlign)
			.addFunction("SetVAlign", &ALittleTextArea::SetVAlign)
			.addFunction("NeedDraw", &ALittleTextArea::NeedDraw)
			.endClass();
	}

#ifdef __EMSCRIPTEN__
	void SetX(float x) { Image::SetX(x); }
	void SetY(float y) { Image::SetY(y); }

	void SetWidth(float width) { Image::SetWidth(width); }
	void SetHeight(float height) { Image::SetHeight(height); }

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
	void SetBold(bool bold)
	{
		const bool is_bold = (m_font_style & CARP_FONT_STYLE_BOLD) != 0;
		if (is_bold == bold) return;

		if (bold)
			m_font_style |= CARP_FONT_STYLE_BOLD;
		else
			m_font_style &= ~CARP_FONT_STYLE_BOLD;

		m_font = 0;
		m_need_redraw = true;
	}
	void SetUnderline(bool underline)
	{
		const bool is_underline = (m_font_style & CARP_FONT_STYLE_UNDERLINE) != 0;
		if (is_underline == underline) return;

		if (underline)
			m_font_style |= CARP_FONT_STYLE_UNDERLINE;
		else
			m_font_style &= ~CARP_FONT_STYLE_UNDERLINE;

		m_font = 0;
		m_need_redraw = true;
	}
	void SetDeleteline(bool deleteline)
	{
		const bool is_deleteline = (m_font_style & CARP_FONT_STYLE_DELETELINE) != 0;
		if (is_deleteline == deleteline) return;

		if (deleteline)
			m_font_style |= CARP_FONT_STYLE_DELETELINE;
		else
			m_font_style &= ~CARP_FONT_STYLE_DELETELINE;

		m_font = 0;
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

		m_font = nullptr;
		m_need_redraw = true;
	}

public:
	void SetFont(const char* font_path, unsigned int font_size)
	{
		if (m_font_path == font_path && m_font_size == font_size) return;
		m_font_path = font_path;
		m_font_size = font_size;
		m_font = nullptr;
		m_need_redraw = true;
	}
	void SetText(const char* text)
	{
		if (!text) return;

		m_text.assign(text);
		m_need_redraw = true;
	}

public:
	enum HAlign
	{
		HALIGN_LEFT,
		HALIGN_CENTER,
		HALIGN_RIGHT
	};

	enum VAlign
	{
		VALIGN_TOP,
		VALIGN_CENTER,
		VALIGN_BOTTOM
	};

	void SetHAlign(int align)
	{
		if (m_halign == align) return;

		m_halign = align;
		m_need_redraw = true;
	}
	void SetVAlign(int align)
	{
		if (m_valign == align) return;

		m_valign = align;
		m_need_redraw = true;
	}

public:
	int GetRealHeight()
	{
		if (m_need_redraw) Draw(false);
		return m_real_height;
	}

public:
	void NeedDraw() { m_need_redraw = true; }
	void Render(const CarpMatrix2D& parent, bool parent_changed) override
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

		if (m_texture == nullptr) return;

		UpdateGlobalMatrix2D(parent, parent_changed);
		UpdateVertexCoord();
		UpdateTextureCoord();

		m_texture->Render(m_color, m_vertex_coord, m_texture_coord);
	}

private:
	void Draw(bool draw)
	{
		// if texture exist, release first
		if (m_texture)
		{
			delete m_texture;
			m_texture = nullptr;
		}

		m_real_height = 0;

		if (m_text.empty()) return;
		if (m_font_path.empty()) return;
		if (m_font_size == 0) return;
		if (m_font == 0) m_font = s_alittle_font.GetFont(m_font_path.c_str(), m_font_size, m_font_style);
		if (m_font == 0) return;

		int width = static_cast<int>(m_size.x);
		int height = static_cast<int>(m_size.y);
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
		while (true)
		{
			int byte_count = CarpString::UTF8GetByteCountOfOneWord(*str);

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
		auto* total_surface = CarpSurfaceBind::CreateCarpSurface(total_width, total_height);
		if (!total_surface)
		{
			CARP_ERROR(SDL_GetError());
			return;
		}

		// set color
		SDL_Color color = { 255, 255, 255, 255 };

		// offset at height
		height_offset = 0;
		if (m_valign == VALIGN_CENTER)
			height_offset = (int)((total_height - m_real_height) * 0.5f);
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
			auto* surface = s_alittle_font.CreateSurface(m_font, string_array[i].c_str());
			if (!surface) continue;
			
			// offset at width
			width_offset = 0;
			if (m_halign == HALIGN_CENTER)
				width_offset = (int)((total_width - surface->GetWidth()) * 0.5f);
			else if (m_halign == HALIGN_RIGHT)
				width_offset = total_width - surface->GetWidth();
			// copy surface
			CarpSurfaceRect src_rect;
			src_rect.x = width_offset < 0 ? -width_offset : 0;
			src_rect.w = width_offset < 0 ? total_width : surface->GetWidth();
			src_rect.y = current_height_offset < 0 ? -current_height_offset : 0;
			src_rect.h = surface->GetHeight() - src_rect.y;

			CarpSurfaceRect dst_rect;
			dst_rect.x = width_offset < 0 ? 0 : width_offset;
			dst_rect.y = current_height_offset < 0 ? 0 : current_height_offset;
			dst_rect.w = src_rect.w;
			dst_rect.h = src_rect.h;

			total_surface->CopyFrom(surface, &src_rect, dst_rect.x, dst_rect.y);
			CarpSurfaceBind::FreeCarpSurface(surface);
		}

		m_texture = new ALittleSurfaceTexture(total_surface);
	}

private:
	bool m_need_redraw = false;

private:
	int m_halign = HALIGN_LEFT;
	int m_valign = VALIGN_TOP;
	int m_real_height = 0;

private:
	std::string m_text;
	unsigned int m_font_style = CARP_FONT_STYLE_NORMAL;
	std::string m_font_path;
	unsigned int m_font_size = 0;
	CarpFont* m_font = nullptr;
};


#endif
