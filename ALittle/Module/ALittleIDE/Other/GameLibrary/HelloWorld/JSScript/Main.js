{
if (typeof HelloWorld === "undefined") HelloWorld = {};


HelloWorld.DownloadTest = async function() {
	let error = await ALittle.DownloadFile("marketplace.visualstudio.com", 443, "items?itemName=AProtobuf.ALittleAProtobuf", "text.txt");
	if (error !== undefined) {
		ALittle.Log(error);
	} else {
		ALittle.Log("download succeed");
	}
}

HelloWorld.Main = function() {
	ALittle.Log("HelloWorld");
	HelloWorld.DownloadTest();
	A_Schedule.Run();
}

}