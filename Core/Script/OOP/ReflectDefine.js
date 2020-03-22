
if (typeof ALittle === "undefined") ALittle = {};
if (typeof ___RETURN === "undefined") ___RETURN = [];

ALittle.RegStruct(1847150134, "ALittle.StructInfo", {
name : "ALittle.StructInfo", ns_name : "ALittle", rl_name : "StructInfo", hash_code : 1847150134,
name_list : ["name","ns_name","rl_name","hash_code","name_list","type_list","option_map"],
type_list : ["string","string","string","int","List<string>","List<string>","Map<string,string>"],
option_map : {}
})
ALittle.RegStruct(318154964, "ALittle.ClassInfo", {
name : "ALittle.ClassInfo", ns_name : "ALittle", rl_name : "ClassInfo", hash_code : 318154964,
name_list : ["__name","__super","__element","__child","__getter","__setter"],
type_list : ["string","ALittle.ClassInfo","List<ALittle.ClassInfo>","Map<string,ALittle.ClassInfo>","Map<string,Functor<(any):any>>","Map<string,Functor<(any,any)>>"],
option_map : {}
})

ALittle.ClassCtor = function(object, clazz, ...___args) {
	let drived = clazz.__super;
	if (drived !== undefined) {
		ALittle.ClassCtor(object, drived, ...___args);
	}
	let fctor = clazz["Ctor"];
	if (fctor !== undefined) {
		fctor.call(object, ...___args);
	}
}

ALittle.NewObject = function(clazz, ...___args) {
	let object = Object.create(clazz);
	object["__class"] = clazz;
	ALittle.ClassCtor(object, clazz, ...___args);
	return object;
}

