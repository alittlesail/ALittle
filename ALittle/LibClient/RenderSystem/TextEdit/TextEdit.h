
#ifndef _ALITTLE_TEXTEDIT_H_
#define _ALITTLE_TEXTEDIT_H_

#include "ALittle/LibClient/RenderSystem/Image/Image.h"
#include "ALittle/LibClient/RenderSystem/Image/Quad.h"

typedef struct _carp_font_t carp_font_t;

#include <string>
#include <list>
#include <map>

namespace ALittle
{

class Texture;

class TextEdit : public Image
{
public:
	TextEdit();
	~TextEdit();

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
	void ShowCursor(bool show);

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
	 * get real height of textedit
	 * @return real height
	 */
	int GetRealHeight();
	
	/**
	 * get line real width
	 * @param line index
	 * @return width
	 */
	int GetLineWidth(int line_index);
	
	/**
	 * get line count
	 * @param line index
	 * @return count
	 */
	int GetLineCount();

	/**
	 * get text offset from start line
	 * @return offset
	 */
	int GetScrollOffset();

private:
	/**
	 * clear all info
	 */
	void ClearText();

	/**
	 * reset cursor position
	 */
	void ResetCursor();

	/**
	 * adjust start iterator close to Cursor
	 * @param distance at last
	 */
	void AdjustStartItCloseTOCursor(int distance);
	/**
	 * adjust start iterator away from Cursor
	 * @param distance at most
	 */
	void AdjustStartItAwayFromCursor(int distance);
	/**
	 * delete text info
	 * @param line_begin_it: begin line iterator
	 * @param begin_it: begin char iterator at line_begin_it
	 * @param line_end_it: end line iterator
	 * @param end_it: end char iterator at line_end_it
	 */
	void DeleteTextImpl(LineCharInfoList::iterator line_begin_it, CharInfoList::iterator begin_it
						, LineCharInfoList::iterator line_end_it, CharInfoList::iterator end_it);
	/**
	 * insert text to cursor
	 * @param text
	 */
	void InsertTextImpl(const char* text);
	/**
	 * insert text to tail
	 * @param text
	 * @return line_begin_it: begin line iterator
	 * @return begin_it: begin char iterator at line_begin_it
	 */
	void InsertTextUtil(const char* text, LineCharInfoList::iterator* line_begin_it = 0, CharInfoList::iterator* begin_it = 0);

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
	void CursorOffsetLRImpl(bool left);
	/**
	 * offset cursor up or down
	 * @param up true: offset up, false: offset down
	 */
	void CursorOffsetUDImpl(bool up);
	/**
	 * get iterator by offset x and y
	 * @param offset_x
	 * @param offset_y
	 * @return line_it_result
	 * @return char_it_result
	 */
	void GetIteratorByOffset(float offset_x, float offset_y, LineCharInfoList::iterator* line_it_result, CharInfoList::iterator* char_it_result);

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
	void CursorOffsetLR(bool left);
	/**
	 * offset select cursor left or right
	 * @param left true: offset left, false: offset right
	 */
	void SelectCursorOffsetLR(bool left);
	/**
	 * offset cursor up or down
	 * @param up true: offset up, false: offset down
	 */
	void CursorOffsetUD(bool up);
	/**
	 * offset select cursor up and down
	 * @param up true: offset up, false: offset down
	 */
	void SelectCursorOffsetUD(bool up);
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
	 * set cursor offset by x and y
	 * @param offset_x
	 * @param offset_y
	 */
	void ClickCursor(float offset_x, float offset_y);
	/**
	 * set cursor offset by x and y
	 * @param offset_x
	 * @param offset_y
	 */
	bool ClickWordCursor(float offset_x, float offset_y);
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
	int GetCursorY() { return m_cursor.GetY(); }
	/**
	 * get cursor height
	 * @return height
	 */
	int GetCursorHeight() { return m_cursor.GetHeight(); }

public:
	void NeedDraw() { m_need_redraw = true; }
	void Render(const Matrix2D& parent, bool parent_changed);

private:
	void Draw();

private:
	bool m_need_redraw;

private:
	unsigned int m_cursor_width;
//////////////////////////////////////////////////////////////////////////////
	// all text
	std::string m_text;
	// select text
	std::string m_select_text;
	// all char info
	LineCharInfoList m_linechar_list;
	// font object
	carp_font_t* m_font;
	std::string m_font_path;
	unsigned int m_font_size;
	// font style
	unsigned int m_font_style;
	// default mode or not
	bool m_default_text_mode;
	// default text alpha
	unsigned char m_default_text_alpha;
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
	Quad m_cursor;

private:
	Quad m_select_1;		// selected area 1
	Quad m_select_2;		// selected area 2
	Quad m_select_3;		// selected area 3

/////////////////////////////////////////////////////////////////////////////
private:
	void GetCharSize(const char* text, int& width, int& height);
	std::map<std::string, int> m_width_map;		// cache char width
};

} // ALittle

#endif // _ALITTLE_TEXTEDIT_H_
