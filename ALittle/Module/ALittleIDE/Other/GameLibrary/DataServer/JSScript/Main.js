{
if (typeof DataServer === "undefined") DataServer = {};


DataServer.g_ConfigSystem = undefined;
DataServer.g_ConnectServerYunIp = "";
DataServer.g_ConnectServerWanIp = "";
DataServer.g_ConnectServerPort = 0;
DataServer.__Module_Setup = async function(config_path, script_base_path) {
	lua.math.randomseed(lua.os.time());
	if (config_path === undefined || config_path === "") {
		config_path = "Module/ALittleIDE/Other/GameLibrary/DataServer.cfg";
	}
	DataServer.g_ConfigSystem = ALittle.CreateJsonConfig(config_path, true);
	let wan_ip = DataServer.g_ConfigSystem.GetConfig("wan_ip", "127.0.0.1");
	let yun_ip = DataServer.g_ConfigSystem.GetConfig("yun_ip", "");
	let port_offset = DataServer.g_ConfigSystem.GetConfig("port_offset", 0);
	let route_offset = DataServer.g_ConfigSystem.GetConfig("route_offset", 0);
	__CPPAPI_ServerSchedule.StartMysqlQuery(1, DataServer.g_ConfigSystem.GetString("main_conn_ip", undefined), DataServer.g_ConfigSystem.GetString("main_conn_username", undefined), DataServer.g_ConfigSystem.GetString("main_conn_password", undefined), DataServer.g_ConfigSystem.GetInt("main_conn_port", undefined), DataServer.g_ConfigSystem.GetString("main_conn_dbname", undefined));
	__CPPAPI_ServerSchedule.StartRouteSystem(2, 1 + route_offset);
	DataServer.g_ConnectServerYunIp = yun_ip;
	DataServer.g_ConnectServerWanIp = wan_ip;
	DataServer.g_ConnectServerPort = 1600 + port_offset + route_offset;
	__CPPAPI_ServerSchedule.CreateConnectServer(DataServer.g_ConnectServerYunIp, DataServer.g_ConnectServerWanIp, DataServer.g_ConnectServerPort);
	__CPPAPI_ServerSchedule.CreateConnectClient(wan_ip, 1001 + port_offset);
	await Require(script_base_path + "DataManager");
	await Require(script_base_path + "LoginManager");
	await Require(script_base_path + "LeaseManager");
	DataServer.g_LeaseManager.Setup();
}

DataServer.__Module_Shutdown = function() {
	DataServer.g_LeaseManager.Shutdown();
}

}