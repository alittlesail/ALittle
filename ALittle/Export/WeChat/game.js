require('./js/libs/weapp-adapter')
require('./js/libs/symbol')
require('./js/Core')
require('./js/native')
require('./js/md5.min')
require('./js/Std')
require('./js/pixi.min.wx');
import {install} from './js/unsafe-eval/install';
install(PIXI);
require('./js/pixi-textinput');

// 游戏资源所在的域名，端口，起始路径
window.alittle_hostname = "127.0.0.1";
window.alittle_port = 80;
window.alittle_base_url = "ALittle/";
require('./js/CEngine')

window.__ALITTLEAPI_SetupMainModule("Module/ALittleIDE/", "ALittleIDE")