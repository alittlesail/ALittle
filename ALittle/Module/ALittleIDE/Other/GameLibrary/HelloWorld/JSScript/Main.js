{
if (typeof HelloWorld === "undefined") window.HelloWorld = {};
let ___lastscript = document.scripts[document.scripts.length - 1]
let ___thispath = "";
if (___lastscript !== undefined) ___thispath = ___lastscript.src.substring(0, ___lastscript.src.lastIndexOf("/") + 1);


Require(___thispath, "../../../../../Std/JSScript/ALittle");
HelloWorld.Main = function() {
	ALittle.Log("HelloWorld");
	A_Schedule.Run();
}

}