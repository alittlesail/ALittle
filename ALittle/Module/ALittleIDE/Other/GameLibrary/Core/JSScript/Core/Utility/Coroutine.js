{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(-930447138, "ALittle.Thread", {
name : "ALittle.Thread", ns_name : "ALittle", rl_name : "Thread", hash_code : -930447138,
name_list : [],
type_list : [],
option_map : {}
})

ALittle.Coroutine = JavaScript.Class(undefined, {
	Resume : function(thread, ...___args) {
		let value = [...___args];
		if (value.length === 0) {
			thread();
		} else if (value.length === 1) {
			thread(value[1 - 1]);
		} else {
			thread(value);
		}
		return [true];
	},
}, "ALittle.Coroutine");

}