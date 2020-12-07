{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(124598654, "ALittle.UISystemSelectFileEvent", {
name : "ALittle.UISystemSelectFileEvent", ns_name : "ALittle", rl_name : "UISystemSelectFileEvent", hash_code : 124598654,
name_list : ["target","path"],
type_list : ["ALittle.DisplayObject","string"],
option_map : {}
})

NESEmulator.g_GConfig = undefined;
NESEmulator.GCenter = JavaScript.Class(undefined, {
	Ctor : function() {
	},
	Setup : function() {
		NESEmulator.g_GConfig = ALittle.CreateConfigSystem(NESEmulator.g_ModuleBasePath + "/User.cfg");
		ALittle.Math_RandomSeed(ALittle.Time_GetCurTime());
		ALittle.System_SetThreadCount(1);
		this._main_layer = ALittle.NewObject(ALittle.DisplayLayout, NESEmulator.g_Control);
		this._main_layer.width_type = 4;
		this._main_layer.height_type = 4;
		NESEmulator.g_LayerGroup.AddChild(this._main_layer, undefined);
		this._dialog_layer = ALittle.NewObject(ALittle.DisplayLayout, NESEmulator.g_Control);
		this._dialog_layer.width_type = 4;
		this._dialog_layer.height_type = 4;
		NESEmulator.g_LayerGroup.AddChild(this._dialog_layer, undefined);
		A_UISystem.view_resize_callback = this.HandleViewResize.bind(this);
		let main_scene = NESEmulator.g_Control.CreateControl("main_scene", this, this._main_layer);
		let group = new Map();
		this._file_menu.group = group;
		this._rom_menu.group = group;
		this._help_menu.group = group;
		this._file_menu.AddEventListener(___all_struct.get(124598654), this, this.HandleSelectFile);
		this._screen = ALittle.NewObject(ALittle.DynamicImage, NESEmulator.g_Control);
		this.UpdateScreenWH();
		this._screen.SetSurfaceSize(NESEmulator.SCREEN_WIDTH, NESEmulator.SCREEN_HEIGHT, 0);
		this._canvas.AddChild(this._screen);
		g_GNes.Setup(this._screen);
	},
	HandleViewResize : function(width, height) {
		this.UpdateScreenWH();
	},
	UpdateScreenWH : function() {
		if (this._screen === undefined) {
			return;
		}
		if (this._canvas.width > this._canvas.height) {
			this._screen.height = this._canvas.height;
			this._screen.width = this._canvas.height * NESEmulator.SCREEN_WIDTH / NESEmulator.SCREEN_HEIGHT;
		} else {
			this._screen.width = this._canvas.width;
			this._screen.height = this._canvas.width * NESEmulator.SCREEN_HEIGHT / NESEmulator.SCREEN_WIDTH;
		}
		this._screen.x = (this._canvas.width - this._screen.width) / 2;
	},
	HandleFileClick : function(event) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("退出", this.HandleExit.bind(this));
		menu.Show(this._file_menu);
	},
	HandleRomClick : function(event) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("坦克大战", this.HandleLoadRom.bind(this, "BattleCity.nes"));
		menu.AddItem("马里奥兄弟", this.HandleLoadRom.bind(this, "SuperMarioBros.nes"));
		menu.AddItem("重装机兵", this.HandleLoadRom.bind(this, "MetalMax.nes"));
		menu.Show(this._rom_menu);
	},
	HandleHelpClick : function(event) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("控制器", this.HandleShowControl.bind(this));
		menu.AddItem("关于", this.HandleShowAbout.bind(this));
		menu.Show(this._help_menu);
	},
	HandleShowControl : function() {
		g_AUITool.ShowNotice("提示", "左:A    右:D\n上:W    下:D\n选择:G    开始:H\nB键:J    A键:K");
	},
	HandleShowAbout : function() {
		g_AUITool.ShowNotice("提示", "本模拟器提供的ROM只提供学习使用，不作为商业用途");
	},
	HandleVersionUpdate : function() {
	},
	HandleSelectFile : async function(event) {
		let error = await g_GNes.LoadROMFromPath(event.path);
		if (error !== undefined) {
			g_AUITool.ShowNotice("错误", error);
		}
	},
	HandleLoadRom : async function(file_name) {
		let error = await g_GNes.LoadROMFromOther(file_name);
		if (error !== undefined) {
			g_AUITool.ShowNotice("错误", error);
		}
	},
	HandleOpenFile : function() {
		A_OtherSystem.SystemSelectFile(this._file_menu);
	},
	HandleExit : function() {
		ALittle.System_Exit();
	},
	Shutdown : function() {
		g_GNes.Shutdown();
	},
}, "NESEmulator.GCenter");

window.g_GCenter = ALittle.NewObject(NESEmulator.GCenter);
}