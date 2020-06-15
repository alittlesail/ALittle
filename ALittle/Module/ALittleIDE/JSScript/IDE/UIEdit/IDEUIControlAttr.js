{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEUIControlAttr = JavaScript.Class(ALittle.DisplayLayout, {
	SetTitle : function(title) {
		let text = "控件属性";
		if (title !== "") {
			text = "控件属性(" + title + ")";
		}
		let main_tab = this.parent;
		main_tab.SetChildText(this, text);
	},
}, "ALittleIDE.IDEUIControlAttr");

}