{


__ALITTLEAPI_CEngine_Init = async function(base_path, callback) {
	{
		await Require(base_path + "Adapter/JavaScript/JHttpInterface");
		await Require(base_path + "Adapter/JavaScript/JMessageFactory");
		await Require(base_path + "Adapter/JavaScript/JMsgInterface");
		await Require(base_path + "Adapter/JavaScript/JSystem");
	}
	await Require(base_path + "CEngine/Utility/String");
	await Require(base_path + "CEngine/Utility/System");
	await Require(base_path + "CEngine/Utility/AudioSystem");
	await Require(base_path + "CEngine/LoopSystem/LoopAnimation");
	await Require(base_path + "CEngine/LoopSystem/LoopAttribute");
	await Require(base_path + "CEngine/LoopSystem/LoopLinear");
	await Require(base_path + "CEngine/LoopSystem/LoopRit");
	ALittle.System_CreateView("test", 800, 600, 0, 0);
	if (callback !== undefined) {
		callback();
	}
}

}