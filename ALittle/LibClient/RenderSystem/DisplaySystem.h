
#ifndef _ALITTLE_DISPLAYSYSTEM_H_
#define _ALITTLE_DISPLAYSYSTEM_H_
#include "ALittle/LibClient/Tool/LocalFile.h"

class CarpFont;

#include <string>
#include <map>

#include "DisplayObject/DisplayObject.h"
#include "DisplayObject/DisplayObjects.h"

namespace ALittle
{

class Texture;
class ScriptSystem;

class DisplaySystem
{
public:
	static DisplaySystem& Instance();

public:
	void Setup();
	void Shutdown();
	void RegisterToScript(ScriptSystem& script_system);

public:
	void Render();

public:
	/**
	 * add child
	 * @param object
	 */
	void AddChild(DisplayObject* object);
	
	/**
	 * add child
	 * @param front_object
	 * @param target_object
	 */
	void AddChildAfter(DisplayObject* front_object, DisplayObject* target_object);
	
	/**
	 * add child
	 * @param back_object
	 * @param target_object
	 */
	void AddChildBefore(DisplayObject* back_object, DisplayObject* target_object);
	
	/**
	 * add special child
	 * @param object
	 */
	void AddSpecialChild(DisplayObject* object);
	
	/**
	 * add special child
	 * @param front_object
	 * @param target_object
	 */
	void AddSpecialChildAfter(DisplayObject* front_object, DisplayObject* target_object);
		
	/**
	 * add special child
	 * @param back_object
	 * @param target_object
	 */
	void AddSpecialChildBefore(DisplayObject* back_object, DisplayObject* target_object);

	/**
	 * remove a child
	 * @param object
	 */
	void RemoveChild(DisplayObject* object);
	
	/**
	 * remove all childs
	 */
	void RemoveAllChild();

private:
	DisplayObjects m_layer_list;				// mormal layer list
	DisplayObjects m_special_layer_list;		// special layer, render at last forever

public:
	/**
	* get quad texture
	*/
	Texture* GetQuadTexture();

private:
	Texture* m_quad_texture;

public:
	/**
	 * get font object
	 * @param font_path
	 * @param font_style
	 * @param font_size
	 * @return font object
	 */
	CarpFont* GetFont(const char* font_path, unsigned int font_style, unsigned int font_size);

	SDL_Surface* CreateSurface(CarpFont* font, const char* content);
	
private:
	CarpFont* LoadFont(const std::string& file, unsigned int font_size, unsigned int font_style);

	/**
	 * release fonts
	 */
	void ClearFont();

private:
	// font size map font object
	typedef std::map<unsigned int, CarpFont*> TTF_FontSizeMap;
	// font style map font object
	typedef std::map<unsigned int, TTF_FontSizeMap> TTF_FontStyleMap;
	// font path map TTF_FontMap
	typedef std::map<std::string, TTF_FontStyleMap> TTF_FontMap;
	TTF_FontMap m_font_map;
	std::map<std::string, LocalFile*> m_font_file_map;

private:
	DisplaySystem();
	~DisplaySystem();
};

} // ALittle

#define g_DisplaySystem ALittle::DisplaySystem::Instance()

#endif // _ALITTLE_DISPLAYSYSTEM_H_
