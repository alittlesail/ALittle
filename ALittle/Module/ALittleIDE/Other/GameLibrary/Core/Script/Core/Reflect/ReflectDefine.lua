
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs

RegStruct(1847150134, "ALittle.StructInfo", {
name = "ALittle.StructInfo", ns_name = "ALittle", rl_name = "StructInfo", hash_code = 1847150134,
name_list = {"name","ns_name","rl_name","hash_code","name_list","type_list","option_map"},
type_list = {"string","string","string","int","List<string>","List<string>","Map<string,string>"},
option_map = {}
})
RegStruct(318154964, "ALittle.ClassInfo", {
name = "ALittle.ClassInfo", ns_name = "ALittle", rl_name = "ClassInfo", hash_code = 318154964,
name_list = {"__name","__super","__element","__child","__getter","__setter"},
type_list = {"string","ALittle.ClassInfo","List<ALittle.ClassInfo>","Map<string,ALittle.ClassInfo>","Map<string,Functor<(any):any>>","Map<string,Functor<(any,any)>>"},
option_map = {}
})

function NewObject(clazz, ...)
	return clazz(...)
end

