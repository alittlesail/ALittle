{
if (typeof ALittle === "undefined") ALittle = {};


ALittle.CreateKeyWeakMap = function() {
	return new jkeyweakmap();
}

ALittle.CreateValueWeakMap = function() {
	return new jvalueweakmap();
}

}