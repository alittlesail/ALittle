{
if (typeof VersionServer === "undefined") VersionServer = {};


VersionServer.g_ConfigSystem = undefined;
VersionServer.__Module_Setup = async function(config_path, script_base_path) {
	lua.math.randomseed(lua.os.time());
	if (config_path === undefined || config_path === "") {
		config_path = "Module/ALittleIDE/Other/GameLibrary/VersionServer.cfg";
	}
	VersionServer.g_ConfigSystem = ALittle.CreateJsonConfig(config_path, true);
	let wan_ip = VersionServer.g_ConfigSystem.GetConfig("wan_ip", "127.0.0.1");
	let yun_ip = VersionServer.g_ConfigSystem.GetConfig("yun_ip", "");
	let port_offset = VersionServer.g_ConfigSystem.GetConfig("port_offset", 0);
	__CPPAPI_ServerSchedule.StartRouteSystem(3, 1);
	__CPPAPI_ServerSchedule.CreateConnectClient(wan_ip, 1001 + port_offset);
	__CPPAPI_ServerSchedule.StartMysqlQuery(1, VersionServer.g_ConfigSystem.GetString("main_conn_ip", undefined), VersionServer.g_ConfigSystem.GetString("main_conn_username", undefined), VersionServer.g_ConfigSystem.GetString("main_conn_password", undefined), VersionServer.g_ConfigSystem.GetInt("main_conn_port", undefined), VersionServer.g_ConfigSystem.GetString("main_conn_dbname", undefined));
	__CPPAPI_ServerSchedule.CreateHttpServer(yun_ip, wan_ip, 1100 + port_offset, false);
	__CPPAPI_ServerSchedule.CreateClientServer(yun_ip, wan_ip, 1101 + port_offset);
	await Require(script_base_path + "VersionManager");
	await Require(script_base_path + "WebAccount/WebPermission");
	await Require(script_base_path + "WebAccount/WebAccount");
	await Require(script_base_path + "WebAccount/WebAccountManager");
	await Require(script_base_path + "WebAccount/WebOPSManager");
	await A_WebAccountManager.Setup();
	await VersionServer.g_VersionManager.Setup();
}

VersionServer.__Module_Shutdown = function() {
}

}