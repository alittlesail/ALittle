{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.IsEmpty = function(object) {
	if (object.__proto__.constructor === Map) {
		return object.size === 0;
	}
	if (object.__proto__.constructor === Object) {
		let has = true;
		let ___OBJECT_1 = object;
		for (let key in ___OBJECT_1) {
			let value = ___OBJECT_1[key];
			if (value === undefined) continue;
			has = false;
			break;
		}
		return has;
	}
	return false;
}

}