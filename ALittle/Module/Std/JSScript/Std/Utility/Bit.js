{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.BitAnd = function(x, y) {
	return bit.band(x, y);
}

ALittle.BitOr = function(x, y) {
	return bit.bor(x, y);
}

}