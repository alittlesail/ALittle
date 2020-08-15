{
if (typeof HelloWorld === "undefined") window.HelloWorld = {};


HelloWorld.Main = function() {
	ALittle.Log("HelloWorld");
	A_Schedule.Run();
}

}