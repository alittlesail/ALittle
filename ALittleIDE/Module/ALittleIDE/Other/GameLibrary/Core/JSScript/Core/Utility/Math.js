{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.Math_Min = function(x, y) {
	if (x < y) {
		return x;
	}
	return y;
}

ALittle.Math_Max = function(x, y) {
	if (x < y) {
		return y;
	}
	return x;
}

ALittle.Math_Sin = function(v) {
	return Math.sin(v);
}

ALittle.Math_Tan = function(v) {
	return Math.tan(v);
}

ALittle.Math_Cos = function(v) {
	return Math.cos(v);
}

ALittle.Math_Abs = function(v) {
	return Math.abs(v);
}

ALittle.Math_Floor = function(v) {
	return Math.floor(v);
}

ALittle.Math_Ceil = function(v) {
	return Math.ceil(v);
}

ALittle.Math_Sqrt = function(v) {
	return Math.sqrt(v);
}

ALittle.Math_ToInt = function(s) {
	let value = parseInt(s);
	if (isNaN(value)) {
		return undefined;
	} else {
		return value;
	}
}

ALittle.Math_ToIntOrZero = function(s) {
	let value = ALittle.Math_ToInt(s);
	if (value === undefined) {
		return 0;
	}
	return value;
}

ALittle.Math_ToDouble = function(s) {
	let value = parseFloat(s);
	if (isNaN(value)) {
		return undefined;
	} else {
		return value;
	}
}

ALittle.Math_ToDoubleOrZero = function(s) {
	let value = ALittle.Math_ToDouble(s);
	if (value === undefined) {
		return 0;
	}
	return value;
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