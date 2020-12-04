{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.ConditionExpr = function(value, a, b) {
	if (value) {
		return a;
	}
	return b;
}

NESEmulator.CopyArrayElements = function(src, srcPos, dest, destPos, length) {
	for (let i = 0; i < length; i += 1) {
		dest.set(destPos + i, src.get(srcPos + i));
	}
}

}