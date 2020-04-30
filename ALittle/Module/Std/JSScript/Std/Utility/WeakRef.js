{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.CreateKeyWeakMap = function() {
	return new jkeyweakmap();
}

ALittle.CreateValueWeakMap = function() {
	return new jvalueweakmap();
}

}