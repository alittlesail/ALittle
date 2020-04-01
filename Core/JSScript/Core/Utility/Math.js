{
if (typeof ALittle === "undefined") ALittle = {};


ALittle.Math_Abs = function(v) {
	return Math.abs(v);
}

ALittle.Math_Floor = function(v) {
	return Math.floor(v);
}

ALittle.Math_ToInt = function(s) {
	return parseInt(s);
}

ALittle.Math_ToDouble = function(s) {
	return parseFloat(s);
}

ALittle.Math_RandomSeed = function(seed) {
}

ALittle.Math_RandomInt = function(min, max) {
	return Math.floor(Math.random() * (max - min + 1)) + min;
}

ALittle.Math_RandomDouble = function(min, max) {
	return Math.random() * (max - min) + min;
}

}