require('./JSNative/libs/weapp-adapter')
require('./JSNative/libs/symbol')
require('./JSNative/Core')
require('./JSNative/native')
require('./JSNative/md5.min')
require('./JSNative/Std')
require('./JSNative/pixi.min.wx');
import {install} from './JSNative/unsafe-eval/install';
install(PIXI);
require('./JSNative/pixi-textinput');

// 游戏资源所在的域名，端口，起始路径
window.alittle_hostname = "127.0.0.1";
window.alittle_port = 80;
window.alittle_base_url = "ALittle/";
require('./JSNative/CEngine')

window.__ALITTLEAPI_SetupMainModule("Module/abcd@project_name@abcd/", "abcd@project_name@abcd")