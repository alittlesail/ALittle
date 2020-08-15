{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.IDisplayObject = JavaScript.Class(undefined, {
	SetX : function(value) {
	},
	SetY : function(value) {
	},
	SetScaleX : function(value) {
	},
	SetScaleY : function(value) {
	},
	SetCenterX : function(value) {
	},
	SetCenterY : function(value) {
	},
	SetAngle : function(value) {
	},
	SetRed : function(value) {
	},
	SetGreen : function(value) {
	},
	SetBlue : function(value) {
	},
	SetAlpha : function(value) {
	},
	SetClip : function(value) {
	},
	SetWidth : function(value) {
	},
	SetHeight : function(value) {
	},
	SetVisible : function(value) {
	},
	RemoveChild : function(value) {
	},
	AddChild : function(value) {
	},
	AddChildBefore : function(value1, value2) {
	},
	RemoveAllChild : function() {
	},
	SetFont : function(path, size) {
	},
	ClearTexture : function() {
	},
	SetTexture : function(texture) {
	},
	SetTextureCoord : function(t, b, l, r) {
	},
	SetFlip : function(value) {
	},
	SetRowColCount : function(row_count, col_count) {
	},
	SetRowColIndex : function(row, col) {
	},
	NeedDraw : function() {
	},
	SetText : function(value) {
	},
	SetBold : function(value) {
	},
	SetItalic : function(value) {
	},
	SetUnderline : function(value) {
	},
	SetDeleteline : function(value) {
	},
	GetRealWidth : function() {
		return 0;
	},
	GetRealHeight : function() {
		return 0;
	},
	GetFontHeight : function() {
		return 0;
	},
	SetHAlign : function(value) {
	},
	SetVAlign : function(value) {
	},
	SetCursorAlpha : function(value) {
	},
	GetLineWidth : function(value) {
		return 0;
	},
	GetLineCount : function() {
		return 0;
	},
	GetScrollOffset : function() {
		return 0;
	},
	IsDefaultText : function() {
		return false;
	},
	SetDefaultText : function(defaultv, value) {
	},
	SetDefaultTextAlpha : function(value) {
	},
	GetCursorX : function() {
		return 0;
	},
	GetCursorY : function() {
		return 0;
	},
	GetCursorHeight : function() {
		return 0;
	},
	GetText : function() {
		return undefined;
	},
	SetCursorToEnd : function() {
	},
	SetCursorToHome : function() {
	},
	ShowCursor : function(value) {
	},
	ClickCursor : function(x, y) {
	},
	ClickWordCursor : function(x, y) {
		return false;
	},
	SelectAll : function() {
	},
	GetSelectText : function() {
		return undefined;
	},
	InsertText : function(value) {
		return false;
	},
	CursorOffsetLR : function(value) {
	},
	SelectCursorOffsetLR : function(value) {
	},
	CursorOffsetUD : function(value) {
	},
	SelectCursorOffsetUD : function(value) {
	},
	DeleteText : function(value) {
		return false;
	},
	DeleteSelectText : function() {
		return false;
	},
	DragCursorBegin : function() {
	},
	DragCursor : function(x, y) {
	},
	SetCursorRed : function(value) {
	},
	SetCursorGreen : function(value) {
	},
	SetCursorBlue : function(value) {
	},
	SetPasswordMode : function(value) {
	},
	CursorOffset : function(value) {
	},
	SelectCursorOffset : function(value) {
	},
	SetTexUV : function(index, u, v) {
	},
	SetPosXY : function(index, x, y) {
	},
	SetLeftSize : function(value) {
	},
	SetRightSize : function(value) {
	},
	SetTopSize : function(value) {
	},
	SetBottomSize : function(value) {
	},
	CutTextByWidth : function(remain_width, text, total_width) {
		return 0;
	},
	ClearCutWidthCache : function() {
	},
	GetCutWidthListCount : function() {
		return 0;
	},
	GetCutWidthByIndex : function(index) {
		return 0;
	},
	CalcTextWidth : function(value) {
		return 0;
	},
}, "ALittle.IDisplayObject");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.IDisplayObjects = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.IDisplayObjects");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.IDisplayView = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.IDisplayView");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.IImage = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.IImage");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.IQuad = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.IQuad");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.ISprite = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.ISprite");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.IText = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.IText");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.ITextArea = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.ITextArea");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.ITextEdit = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.ITextEdit");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.ITextInput = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.ITextInput");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.ITriangle = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.ITriangle");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.IGrid9Image = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.IGrid9Image");

ALittle.IDisplaySystem = JavaScript.Class(undefined, {
	AddSpecialChild : function(value) {
	},
	AddChild : function(value) {
	},
	AddChildBefore : function(value1, value2) {
	},
	RemoveChild : function(value) {
	},
	RemoveAllChild : function() {
	},
}, "ALittle.IDisplaySystem");

ALittle.ITexture = JavaScript.Class(undefined, {
	Clear : function() {
	},
	GetTexture : function() {
		return this;
	},
	GetWidth : function() {
		return 0;
	},
	GetHeight : function() {
		return 0;
	},
}, "ALittle.ITexture");

if (ALittle.ITexture === undefined) throw new Error(" extends class:ALittle.ITexture is undefined");
ALittle.IRenderTexture = JavaScript.Class(ALittle.ITexture, {
	Save : function(file_path, show, width, height, scale) {
		return false;
	},
	Draw : function(show, width, height, scale) {
		return false;
	},
}, "ALittle.IRenderTexture");

ALittle.ITextureLoader = JavaScript.Class(undefined, {
	SetPath : function(big_path, altas, big_width, big_height, crypt_mode) {
	},
	Start : function() {
	},
	GetID : function() {
		return 0;
	},
	GetPath : function() {
		return undefined;
	},
}, "ALittle.ITextureLoader");

ALittle.ITextureCutLoader = JavaScript.Class(undefined, {
	SetPath : function(path, max_width, max_height) {
	},
	Start : function() {
	},
	GetID : function() {
		return 0;
	},
	GetPath : function() {
		return undefined;
	},
	GetMaxWidth : function() {
		return 0;
	},
	GetMaxHeight : function() {
		return 0;
	},
}, "ALittle.ITextureCutLoader");

}