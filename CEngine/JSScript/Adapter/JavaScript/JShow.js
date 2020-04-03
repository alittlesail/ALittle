{
if (typeof JavaScript === "undefined") JavaScript = {};


if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
JavaScript.JDisplayObject = JavaScript.Class(ALittle.IDisplayObject, {
	Ctor : function() {
		this._scale = new PIXI.Point(1, 1);
		this._pivot = new PIXI.Point(0, 0);
		this._clip = false;
		this._visible = true;
	},
	get native() {
		return this._native;
	},
	SetX : function(value) {
		this._native.x = value;
	},
	SetY : function(value) {
		this._native.y = value;
	},
	SetScaleX : function(value) {
		this._scale.x = value;
		this._native.scale = this._scale;
	},
	SetScaleY : function(value) {
		this._scale.y = value;
		this._native.scale = this._scale;
	},
	SetCenterX : function(value) {
		this._pivot.x = value;
		this._native.pivot = this._pivot;
	},
	SetCenterY : function(value) {
		this._pivot.y = value;
		this._native.pivot = this._pivot;
	},
	SetAngle : function(value) {
		this._native.rotation = value;
	},
	SetWidth : function(value) {
		this._native.width = value;
	},
	SetHeight : function(value) {
		this._native.height = value;
	},
	SetVisible : function(value) {
		this._visible = value;
		this._native.visible = value && !this._clip;
	},
	SetClip : function(value) {
		this._clip = value;
		this._native.visible = value && this._visible;
	},
	SetAlpha : function(value) {
		this._native.alpha = value;
	},
	SetRed : function(value) {
	},
	SetGreen : function(value) {
	},
	SetBlue : function(value) {
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
	SetOutline : function(value) {
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
}, "JavaScript.JDisplayObject");

if (JavaScript.JDisplayObject === undefined) throw new Error(" extends class:JavaScript.JDisplayObject is undefined");
JavaScript.JDisplayObjects = JavaScript.Class(JavaScript.JDisplayObject, {
	Ctor : function() {
		this._native = new PIXI.Container();
	},
	RemoveChild : function(value) {
		this._native.removeChild(value._native);
	},
	AddChild : function(value) {
		this._native.addChild(value._native);
	},
	AddChildBefore : function(back, value) {
		let index = this._native.getChildAt(value._native);
		this._native.addChildAt(value._native, index - 1);
	},
	RemoveAllChild : function() {
		this._native.removeChildren(0);
	},
}, "JavaScript.JDisplayObjects");

if (ALittle.IDisplaySystem === undefined) throw new Error(" extends class:ALittle.IDisplaySystem is undefined");
JavaScript.JDisplaySystem = JavaScript.Class(ALittle.IDisplaySystem, {
	Ctor : function() {
		this._layer = new PIXI.Container();
		this._special_layer = new PIXI.Container();
	},
	AddToStage : function(stage) {
		this._layer.width = stage.width;
		this._layer.height = stage.height;
		this._special_layer.width = stage.width;
		this._special_layer.height = stage.height;
		stage.addChild(this._layer);
		stage.addChild(this._special_layer);
	},
	AddSpecialChild : function(value) {
		this._special_layer.addChild(value.native);
	},
	AddChild : function(value) {
		this._layer.addChild(value.native);
	},
	AddChildBefore : function(back, value) {
		let index = this._layer.getChildAt(value.native);
		this._layer.addChildAt(value.native, index - 1);
	},
	RemoveChild : function(value) {
		this._layer.removeChild(value.native);
	},
	RemoveAllChild : function() {
		this._layer.removeChildren(0);
		this._special_layer.removeChildren(0);
	},
}, "JavaScript.JDisplaySystem");

window.A_JDisplaySystem = ALittle.NewObject(JavaScript.JDisplaySystem);
if (JavaScript.JDisplayObject === undefined) throw new Error(" extends class:JavaScript.JDisplayObject is undefined");
JavaScript.JQuad = JavaScript.Class(JavaScript.JDisplayObject, {
	Ctor : function() {
		this._native = new PIXI.Graphics();
		this._color = 0;
		this._red = 0;
		this._green = 0;
		this._blue = 0;
		this._alpha = 1;
		this._width = 0;
		this._height = 0;
	},
	Draw : function() {
		this._native.clear();
		this._native.beginFill(this._color, this._alpha);
		this._native.drawRect(0, 0, this._width, this._height);
		this._native.endFill();
	},
	SetWidth : function(value) {
		this._width = value;
		this.Draw();
	},
	SetHeight : function(value) {
		this._height = value;
		this.Draw();
	},
	SetRed : function(value) {
		this._red = Math.floor(value * 255);
		this._color = this._red * 65536 + this._green * 256 + this._blue;
		this.Draw();
	},
	SetGreen : function(value) {
		this._green = Math.floor(value * 255);
		this._color = this._red * 65536 + this._green * 256 + this._blue;
		this.Draw();
	},
	SetBlue : function(value) {
		this._blue = Math.floor(value * 255);
		this._color = this._red * 65536 + this._green * 256 + this._blue;
		this.Draw();
	},
	SetAlpha : function(value) {
		this._alpha = value;
		this.Draw();
	},
}, "JavaScript.JQuad");

}