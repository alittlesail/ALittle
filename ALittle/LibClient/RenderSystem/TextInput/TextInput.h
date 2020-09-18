
#ifndef _ALITTLE_TEXTINPUT_H_
#define _ALITTLE_TEXTINPUT_H_

#include "ALittle/LibClient/RenderSystem/Image/Image.h"
#include "ALittle/LibClient/RenderSystem/Image/Quad.h"


typedef struct _carp_font_t carp_font_t;

#include <string>
#include <list>

namespace ALittle
{

class Texture;

class TextInput : public Image
{
public:
	TextInput();
	~TextInput();

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
	void SetWidth(float width);
	void SetHeight(float height);

public:
	void SetCursorRed(float red);
	void SetCursorGreen(float green);
	void SetCursorBlue(float blue);
	void SetCursorAlpha(float alpha);

public:
	void SetBold(bool bold);
	void SetUnderline(bool underline);
	void SetDeleteline(bool deleteline);
	void SetItalic(bool italic);
	
public:
	void SetPasswordMode(bool mode);

public:
	void ShowCursor(bool show);

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
	void ClearText();
	/**
	 * reset cursor
	 */
	void ResetCursor();
	/**
	 * Closer to the starting position and distance
	 * @param distance
	 */
	void AdjustStartItCloseTOCursor(int distance);
	/**
	 * wawy from Starting position and distance
	 * @param distance
	 */
	void AdjustStartItAwayFromCursor(int distance);
	/**
	 * Delete the specified range node
	 * @param begin_it
	 * @param end_it
	 */
	void DeleteTextImpl(CharInfoList::iterator begin_it, CharInfoList::iterator end_it);
	/**
	 * Insert text at the location of the cursor
	 * @param text
	 */
	void InsertTextImpl(const char* text);

//=====================================================================================
public:
	/**
	 * set font
	 * @param font_path
	 * @param font_size
	 */
	void SetFont(const char* font_path, unsigned int font_size);
	/**
	 * set text
	 * @param text
	 */
	void SetText(const char* text);
	/**
	 * set default text, it shows when textedit is empty
	 * @param mode: default or not
	 * @param text: default text
	 */
	void SetDefaultText(bool mode, const char* text);
	/*
	 * set default alpha
	 * @param alpha
	 */
	void SetDefaultTextAlpha(float alpha);
	/**
	 * get default mode or not
	 * @return defaule or not
	 */
	bool IsDefaultText();
	/**
	 * get text
	 * @return text
	 */
	const char* GetText();
	/**
	 * get selected text
	 * @return text
	 */
	const char* GetSelectText();
	/**
	 * delete selcted text
	 * @return delete or not
	 */
	bool DeleteSelectText();
	/**
	 * insert text
	 * @param text
	 * @return insert or not
	 */
	bool InsertText(const char* text);
	/**
	 * delete one char
	 * @param left true:delete left, false:delete right
	 * @return delete or not
	 */
	bool DeleteText(bool left);

//=====================================================================================
private:
	/**
	 * offset cursor left or right
	 * @param left true: offset left, false: offset right
	 */
	void CursorOffsetImpl(bool left);
	
	/**
	 * get iterator by offset x
	 * @param offset
	 * @return char info iterator
	 */
	CharInfoList::iterator GetIteratorByOffset(float offset);

	/*
	*  resize cursor width by font_size
	* @param font_size
	*/
	unsigned int GetCursorWidth(unsigned int font_size);
public:
	/**
	 * offset cursor left or right
	 * @param left true: offset left, false: offset right
	 */
	void CursorOffset(bool left);
	
	/**
	 * offset select cursor left or right
	 * @param left true: offset left, false: offset right
	 */
	void SelectCursorOffset(bool left);
	/**
	 * offset cursor to home
	 */
	void SetCursorToHome();
	/**
	 * offset cursor to end
	 */
	void SetCursorToEnd();
	/**
	 * select all text
	 */
	void SelectAll();
	/**
	 * set cursor offset by x
	 * @param offset
	 */
	void ClickCursor(float offset);
	/**
	 * set cursor offset by x
	 * @param offset
	 */
	bool ClickWordCursor(float offset);
	/**
	 * cursor drag begin
	 */
	void DragCursorBegin();
	/**
	 * cursor draging
	 * @param offset_x
	 * @param offset_y
	 */
	void DragCursor(float offset_x, float offset_y);
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
	void Render(const Matrix2D& parent, bool parent_changed);
	void UpdateVertexCoord();

private:
	void Draw();

private:
	bool m_need_redraw;

private:
	int m_real_width, m_real_height;

private:
	unsigned int m_cursor_width;
//////////////////////////////////////////////////////////////////////////////
	// all text
	std::string m_text;
	// select text
	std::string m_select_text;
	// all char info
	CharInfoList m_char_list;
	// font object
	carp_font_t* m_font;
	std::string m_font_path;
	unsigned int m_font_size;
	// font style
	unsigned int m_font_style;
	// password mode or not
	bool m_password_mode;
	// default mode or not
	bool m_default_text_mode;
	// default text alpha
	unsigned char m_default_text_alpha;
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
	Quad m_cursor;
};

} // ALittle

#endif // _ALITTLE_TEXTINPUT_H_
