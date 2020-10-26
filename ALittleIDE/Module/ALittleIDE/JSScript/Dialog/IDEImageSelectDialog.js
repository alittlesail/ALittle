{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1821709712, "AUIPlugin.AUIFileSelectRightButtonDownEvent", {
name : "AUIPlugin.AUIFileSelectRightButtonDownEvent", ns_name : "AUIPlugin", rl_name : "AUIFileSelectRightButtonDownEvent", hash_code : 1821709712,
name_list : ["target","path","directory"],
type_list : ["ALittle.EventDispatcher","string","bool"],
option_map : {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})

if (AUIPlugin.AUIFileSelectDialog === undefined) throw new Error(" extends class:AUIPlugin.AUIFileSelectDialog is undefined");
ALittleIDE.IDEImageSelectDialog = JavaScript.Class(AUIPlugin.AUIFileSelectDialog, {
	Ctor : function(title, layer, ext_list) {
		ALittleIDE.g_IDEProject.AddEventListener(___all_struct.get(-332308624), this, this.HandleCloseProject);
		this.AddEventListener(___all_struct.get(1821709712), this, this.HandleImageSelectRButtonDown);
	},
	HandleCloseProject : function(event) {
		if (this._dialog === undefined) {
			return;
		}
		this.HideDialog();
	},
	HandleImageSelectRButtonDown : function(event) {
		let ext = ALittle.File_GetFileExtByPathAndUpper(event.path);
		if (ext !== "PNG" && ext !== "JPG") {
			let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
			menu.AddItem("删除", this.HandleImageDeleteClick.bind(this, event));
			menu.Show();
			return;
		}
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("复制九宫格代码", this.HandleImageCopyGrid9ImageCodeClick.bind(this, event));
		menu.AddItem("复制图片代码", this.HandleImageCopyImageCodeClick.bind(this, event));
		menu.AddItem("图片裁剪", this.HandleImageEditClick.bind(this, event));
		menu.AddItem("删除", this.HandleImageDeleteClick.bind(this, event));
		menu.Show();
	},
	HandleImageCopyGrid9ImageCodeClick : function(event) {
		let display_info = ALittleIDE.IDEUIUtility_GenerateGrid9ImageInfo(this.base_path + "/", event.path);
		if (display_info === undefined) {
			g_AUITool.ShowNotice("错误", "图片加载失败:" + event.path);
			return;
		}
		let copy_list = [];
		let info = {};
		info.index = 1;
		info.info = display_info;
		copy_list[1 - 1] = info;
		ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list));
	},
	HandleImageCopyImageCodeClick : function(event) {
		let width = 100;
		let height = 100;
		let surface = carp.LoadCarpSurface(this.base_path + "/" + event.path);
		if (surface !== undefined) {
			width = carp.GetCarpSurfaceWidth(surface);
			height = carp.GetCarpSurfaceHeight(surface);
			carp.FreeCarpSurface(surface);
		}
		let display_info = {};
		display_info.__class = "Image";
		display_info.texture_name = event.path;
		display_info.width_type = 1;
		display_info.width_value = width;
		display_info.height_type = 1;
		display_info.height_value = height;
		let info = {};
		info.index = 1;
		info.info = display_info;
		let copy_list = [];
		copy_list[1 - 1] = info;
		ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list));
	},
	HandleImageEditClick : function(event) {
		ALittleIDE.g_IDEEditImageDialog.ShowDialog(this.base_path + "/" + event.path, this.base_path);
	},
	HandleImageDeleteClick : async function(event) {
		let tittle = "确定要永久删除该文件吗？";
		if (event.directory) {
			tittle = "确定要永久删除该文件夹，以及子文件吗？";
		}
		let result = await g_AUITool.DeleteNotice("删除", tittle);
		if (result === "YES") {
			if (event.directory) {
				ALittle.File_DeleteDeepDir(this.base_path + "/" + event.path);
			} else {
				ALittle.File_DeleteFile(this.base_path + "/" + event.path);
			}
			this.Refresh();
		}
	},
}, "ALittleIDE.IDEImageSelectDialog");

ALittleIDE.g_IDEImageManagerDialog = ALittle.NewObject(ALittleIDE.IDEImageSelectDialog, "图片选择器", undefined, ["PNG", "JPG"]);
ALittleIDE.g_IDEImageSelectDialog = ALittle.NewObject(ALittleIDE.IDEImageSelectDialog, "图片选择器", ALittleIDE.g_DialogLayer, ["PNG", "JPG"]);
ALittleIDE.g_IDEEditImageDialog = ALittle.NewObject(AUIPlugin.AUIEditImageDialog);
}