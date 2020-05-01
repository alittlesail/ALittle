{
if (typeof JavaScript === "undefined") window.JavaScript = {};


JavaScript.CloneProperty = function(clazz, copy_ctor) {
	let new_clazz = {};
	new_clazz.__super = clazz.__super;
	new_clazz.__name = clazz.__name;
	let setter_map = {};
	let getter_map = {};
	new_clazz.__setter = setter_map;
	new_clazz.__getter = getter_map;
	let ___OBJECT_1 = clazz;
	for (let name in ___OBJECT_1) {
		// 因为for使用了Native修饰，不做undefined处理
		// let _ = ___OBJECT_1[name];
		// if (_ === undefined) continue;
		if (!copy_ctor && name === "Ctor") {
			continue;
		}
		if (name !== "__super" && name !== "__getter" && name !== "__setter") {
			let info = Object.getOwnPropertyDescriptor(clazz, name);
			if (info["set"] !== undefined || info["get"] !== undefined) {
				Object.defineProperty(new_clazz, name, info);
			}
			if (info["set"] !== undefined) {
				setter_map[name] = info["set"];
			}
			if (info["get"] !== undefined) {
				getter_map[name] = info["get"];
			}
			if (info["set"] === undefined && info["get"] === undefined) {
				new_clazz[name] = clazz[name];
			}
		}
	}
	return new_clazz;
}

JavaScript.Class = function(drived, clazz_prop, clazz_name) {
	let clazz = undefined;
	if (drived !== undefined) {
		clazz = JavaScript.CloneProperty(drived, false);
		clazz.__super = drived;
	} else {
		clazz = {};
		clazz.__setter = {};
		clazz.__getter = {};
	}
	clazz.__name = clazz_name;
	let setter_map = clazz.__setter;
	let getter_map = clazz.__getter;
	let ___OBJECT_2 = clazz_prop;
	for (let name in ___OBJECT_2) {
		// 因为for使用了Native修饰，不做undefined处理
		// let _ = ___OBJECT_2[name];
		// if (_ === undefined) continue;
		let info = Object.getOwnPropertyDescriptor(clazz_prop, name);
		if (info["get"] === undefined && info["set"] === undefined) {
			clazz[name] = clazz_prop[name];
		} else {
			if (info["get"] !== undefined && info["set"] === undefined) {
				getter_map[name] = info["get"];
				if (setter_map[name] !== undefined) {
					info["set"] = setter_map[name];
				}
				Object.defineProperty(clazz, name, info);
			} else {
				if (info["get"] === undefined && info["set"] !== undefined) {
					setter_map[name] = info["set"];
					if (getter_map[name] !== undefined) {
						info["get"] = getter_map[name];
					}
					Object.defineProperty(clazz, name, info);
				} else {
					getter_map[name] = info["get"];
					setter_map[name] = info["set"];
					Object.defineProperty(clazz, name, info);
				}
			}
		}
	}
	return clazz;
}

JavaScript.Template = function(clazz, name, ...___args) {
	let child = clazz.__child;
	if (child === undefined) {
		child = {};
		clazz.__child = child;
	}
	let template = child[name];
	if (template !== undefined) {
		return template;
	}
	template = JavaScript.CloneProperty(clazz, true);
	child[name] = template;
	template.__name = name;
	template.__element = [...___args];
	return template;
}

JavaScript.ClassCtor = function(object, clazz, ...___args) {
	let drived = clazz.__super;
	if (drived !== undefined) {
		JavaScript.ClassCtor(object, drived, ...___args);
	}
	let fctor = clazz["Ctor"];
	if (fctor !== undefined) {
		fctor.call(object, ...___args);
	}
}

JavaScript.NewObject = function(clazz, ...___args) {
	let object = Object.create(clazz);
	object["__class"] = clazz;
	JavaScript.ClassCtor(object, clazz, ...___args);
	return object;
}

}