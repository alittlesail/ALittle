require('./Module/abcd@project_name@abcd/JSNative/libs/weapp-adapter')
require('./Module/abcd@project_name@abcd/JSNative/libs/symbol')
require('./Module/abcd@project_name@abcd/JSNative/runtime')
require('./Module/abcd@project_name@abcd/JSNative/Core')
require('./Module/abcd@project_name@abcd/JSNative/native')
require('./Module/abcd@project_name@abcd/JSNative/md5.min')
require('./Module/abcd@project_name@abcd/JSNative/Std')

// 适配真机上的微信小游戏
if (!window.WebGLRenderingContext)
{
	var contextOptions = {
		stencil: true,
		failIfMajorPerformanceCaveat: true,
	};
	window.WebGLRenderingContext  = canvas.getContext("webgl", contextOptions);
}

require('./Module/abcd@project_name@abcd/JSNative/pixi.min.wx');
import {install} from './Module/abcd@project_name@abcd/JSNative/unsafe-eval/install';
install(PIXI);
require('./Module/abcd@project_name@abcd/JSNative/pixi-textinput');

// 游戏资源所在的域名，端口，起始路径
window.alittle_hostname = "abcd@res_ip@abcd";
window.alittle_port = abcd@res_port@abcd;
window.alittle_base_url = "abcd@res_base_path@abcd";
require('./Module/abcd@project_name@abcd/JSNative/CEngine1')
require('./Module/abcd@project_name@abcd/JSNative/CEngine2')

window.__ALITTLEAPI_SetupMainModule("Module/abcd@project_name@abcd/", "abcd@project_name@abcd")