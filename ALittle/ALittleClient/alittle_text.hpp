#ifndef ALITTLE_TEXT_INCLUDED
#define ALITTLE_TEXT_INCLUDED (1)

#include "alittle_displayobject.hpp"
#include "alittle_texture.hpp"
#include "alittle_font.hpp"
#include "alittle_image.hpp"

struct TextTextureInfo
{
	ALittleTexture* texture = nullptr;
	CarpFont* font = nullptr;
	int ref_count = 0;
	std::string text;
};

extern TextTextureInfo* CreateTextureInfo(CarpFont* font, const std::string& text);
extern void ReleaseTextureInfo(TextTextureInfo* info);
extern std::unordered_map<CarpFont*, std::unordered_map<std::string, TextTextureInfo*>> s_text_texture_map;

class ALittleText : public ALittleImage
{
public:
	ALittleText() {}
	~ALittleText()
	{
		if (m_texture_info)
		{
			ReleaseTextureInfo(m_texture_info);
			m_texture_info = nullptr;
			m_texture = nullptr;
			m_real_width = m_real_height = 0;
		}
	}

	static void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.deriveClass<ALittleText, ALittleImage>("__CPPAPIText")
			.addConstructor<void(*)()>()
			.addFunction("SetScaleX", &ALittleText::SetScaleX)
			.addFunction("SetScaleY", &ALittleText::SetScaleY)
			.addFunction("SetCenterX", &ALittleText::SetCenterX)
			.addFunction("SetCenterY", &ALittleText::SetCenterY)
			.addFunction("SetAngle", &ALittleText::SetAngle)
			.addFunction("SetX", &ALittleText::SetX)
			.addFunction("SetY", &ALittleText::SetY)
			.addFunction("SetZ", &ALittleText::SetZ)
			.addFunction("SetWidth", &ALittleText::SetWidth)
			.addFunction("SetHeight", &ALittleText::SetHeight)
			.addFunction("SetRed", &ALittleText::SetRed)
			.addFunction("SetGreen", &ALittleText::SetGreen)
			.addFunction("SetBlue", &ALittleText::SetBlue)
			.addFunction("SetAlpha", &ALittleText::SetAlpha)
			.addFunction("SetFont", &ALittleText::SetFont)
			.addFunction("SetText", &ALittleText::SetText)
			.addFunction("GetRealWidth", &ALittleText::GetRealWidth)
			.addFunction("GetRealHeight", &ALittleText::GetRealHeight)
			.addFunction("AdjustSize", &ALittleText::AdjustSize)
			.addFunction("SetVisible", &ALittleText::SetVisible)
			.addFunction("SetBold", &ALittleText::SetBold)
			.addFunction("SetDeleteline", &ALittleText::SetDeleteline)
			.addFunction("SetUnderline", &ALittleText::SetUnderline)
			.addFunction("SetItalic", &ALittleText::SetItalic)
			.addFunction("SetClip", &ALittleText::SetClip)
			.addFunction("GetFontHeight", &ALittleText::GetFontHeight)
			.addFunction("CutTextByWidth", &ALittleText::CutTextByWidth)
			.addFunction("CalcTextWidth", &ALittleText::CalcTextWidth)
			.addFunction("NeedDraw", &ALittleText::NeedDraw)
			.addFunction("GetCutWidthListCount", &ALittleText::GetCutWidthListCount)
			.addFunction("GetCutWidthByIndex", &ALittleText::GetCutWidthByIndex)
			.addFunction("ClearCutWidthCache", &ALittleText::ClearCutWidthCache)
			.endClass();

	}

	void SetX(float x) override { ALittleImage::SetX(x); }
	void SetY(float y) override { ALittleImage::SetY(y); }
	void SetZ(float z) override { ALittleImage::SetZ(z); }

	void SetWidth(float width) override { ALittleImage::SetWidth(width); }
	void SetHeight(float height) override { ALittleImage::SetHeight(height); }

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

public:
	unsigned int GetRealWidth()
	{
		if (m_calc_real_size == true) return m_real_width;

		if (m_text.empty()) return 0;
		if (m_font_path.empty()) return 0;
		if (m_font_size == 0) return 0;
		if (m_font == nullptr) m_font = s_alittle_font.GetFont(m_font_path.c_str(), m_font_size, m_font_style);
		if (m_font == nullptr) return 0;

		// calc size
		m_real_width = m_font->CutTextWidth(m_text.c_str(), false);
		m_real_height = m_font->GetFontHeight();

		m_calc_real_size = true;

		return m_real_width;
	}
	unsigned int GetRealHeight()
	{
		if (m_calc_real_size == true) return m_real_height;

		if (m_text.empty()) return 0;
		if (m_font_path.empty()) return 0;
		if (m_font_size == 0) return 0;

		if (m_font == nullptr)
			m_font = s_alittle_font.GetFont(m_font_path.c_str(), m_font_size, m_font_style);
		if (m_font == nullptr) return 0;

		// calc size
		m_real_width = m_font->CutTextWidth(m_text.c_str(), false);
		m_real_height = m_font->GetFontHeight();

		m_calc_real_size = true;
		return m_real_height;
	}
	void AdjustSize()
	{
		SetWidth(static_cast<float>(m_real_width));
		SetHeight(static_cast<float>(m_real_height));
	}

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
		m_calc_real_size = false;
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
		m_calc_real_size = false;
	}
	void SetDeleteline(bool deleteline)
	{
		const bool is_deleteline = (m_font_style & CARP_FONT_STYLE_DELETELINE) != 0;
		if (is_deleteline == deleteline) return;

		if (deleteline)
			m_font_style |= CARP_FONT_STYLE_DELETELINE;
		else
			m_font_style &= ~CARP_FONT_STYLE_DELETELINE;

		m_font = nullptr;
		m_need_redraw = true;
		m_calc_real_size = false;
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
		m_calc_real_size = false;
	}

public:
	void SetFont(const char* font_path, unsigned int font_size)
	{
		if (m_font_path == font_path && m_font_size == font_size) return;
		m_font_path = font_path;
		m_font_size = font_size;
		m_font = nullptr;

		m_need_redraw = true;
		m_calc_real_size = false;
	}
	void SetText(const char* text)
	{
		if (!text) return;

		m_text.assign(text);

		m_need_redraw = true;
		m_calc_real_size = false;
	}
	int GetFontHeight()
	{
		if (m_font == nullptr) m_font = s_alittle_font.GetFont(m_font_path.c_str(), m_font_size, m_font_style);
		if (m_font == nullptr) return 0;

		return m_font->GetFontHeight();
	}
	int CutTextByWidth(float width, const char* content, int max_width)
	{
		if (m_font == nullptr) m_font = s_alittle_font.GetFont(m_font_path.c_str(), m_font_size, m_font_style);
		if (m_font == nullptr) return 0;

		m_calc_width_list.clear();
		return m_font->CutTextByWidth(content, static_cast<int>(width), max_width, false, &m_calc_width_list);
	}
	int GetCutWidthListCount() const { return static_cast<int>(m_calc_width_list.size()); }
	int GetCutWidthByIndex(int index) const { return m_calc_width_list[index]; }
	void ClearCutWidthCache() { m_calc_width_list.clear(); }
	int CalcTextWidth(const char* content)
	{
		if (m_font == nullptr) m_font = s_alittle_font.GetFont(m_font_path.c_str(), m_font_size, m_font_style);
		if (m_font == nullptr) return 0;

		return m_font->CutTextWidth(content, false);
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
			Draw();
			m_need_redraw = false;
			m_calc_real_size = true;
			SetSelfMatrixDirty();
		}

		if (m_texture == nullptr) return;

		UpdateGlobalMatrix2D(parent, parent_changed);
		UpdateVertexCoord();
		UpdateTextureCoord();

		m_texture->Render(m_color, m_vertex_coord, m_texture_coord);
	}

private:
	void Draw()
	{
		// release current texture
		if (m_texture_info)
		{
			ReleaseTextureInfo(m_texture_info);
			m_texture_info = nullptr;
			m_texture = nullptr;
			m_real_width = m_real_height = 0;
		}

		if (m_text.empty()) return;
		if (m_font == nullptr) m_font = s_alittle_font.GetFont(m_font_path.c_str(), m_font_size, m_font_style);
		if (m_font == nullptr) return;

		m_texture_info = CreateTextureInfo(m_font, m_text);
		if (m_texture_info == nullptr) return;
		m_texture = m_texture_info->texture;
		m_real_width = m_texture_info->texture->GetWidth();
		m_real_height = m_texture_info->texture->GetHeight();
	}

private:
	bool m_need_redraw = false;
	TextTextureInfo* m_texture_info = nullptr;

private:
	bool	m_calc_real_size = false;
	unsigned int m_real_width = 0, m_real_height = 0;

private:
	std::string m_text;
	unsigned int m_font_style = CARP_FONT_STYLE_NORMAL;
	std::string m_font_path;
	unsigned int m_font_size = 0;
	CarpFont* m_font = nullptr;

private:
	std::vector<int> m_calc_width_list;

private:
};
#endif

#ifdef ALITTLE_TEXT_IMPL
#ifndef ALITTLE_TEXT_IMPL_INCLUDE
#define ALITTLE_TEXT_IMPL_INCLUDE

std::unordered_map<CarpFont*, std::unordered_map<std::string, TextTextureInfo*>> s_text_texture_map;

TextTextureInfo* CreateTextureInfo(CarpFont* font, const std::string& text)
{
	auto& text_map = s_text_texture_map[font];
	auto it = text_map.find(text);
	if (it != text_map.end())
	{
		++it->second->ref_count;
		return it->second;
	}

	// create surface
	auto* surface = s_alittle_font.CreateSurface(font, text.c_str());
	if (!surface)
	{
		CARP_ERROR("Font Helper create surface failed!");
		return 0;
	}

	if (surface->GetWidth() <= 0 || surface->GetHeight() <= 0)
	{
		CARP_ERROR("surface:(w, h)=(" << surface->GetWidth() << ", " << surface->GetHeight() << ")");
		return 0;
	}

	auto* info = new TextTextureInfo();
	info->font = font;
	info->ref_count = 1;
	info->text = text;
	info->texture = new ALittleSurfaceTexture(surface, ALittleTextureRenderMode::ATRM_NEAREST);
	text_map[text] = info;

	return info;
}

void ReleaseTextureInfo(TextTextureInfo* info)
{
	--info->ref_count;
	if (info->ref_count > 0) return;

	auto text_it = s_text_texture_map.find(info->font);
	if (text_it == s_text_texture_map.end()) return;
	auto font_it = text_it->second.find(info->text);
	if (font_it == text_it->second.end()) return;

	delete font_it->second->texture;
	delete font_it->second;
	text_it->second.erase(font_it);
	if (text_it->second.empty()) s_text_texture_map.erase(text_it);
}

#endif
#endif