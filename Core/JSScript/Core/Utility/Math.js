{
if (typeof ALittle === "undefined") ALittle = {};


ALittle.Math_Abs = function(v) {
	return Math.abs(v);
}

ALittle.Math_Floor = function(v) {
	return Math.floor(v);
}

ALittle.Math_ToInt = function(s) {
	let value = parseInt(s);
	if (isNaN(value)) {
		return undefined;
	} else {
		return value;
	}
}

ALittle.Math_ToDouble = function(s) {
	let value = parseFloat(s);
	if (isNaN(value)) {
		return undefined;
	} else {
		return value;
	}
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