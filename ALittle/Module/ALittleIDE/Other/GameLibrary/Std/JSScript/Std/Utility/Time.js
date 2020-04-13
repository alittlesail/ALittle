{
if (typeof ALittle === "undefined") ALittle = {};


let __VersionTime = 0;
let __VersionIndex = 0;
ALittle.NewTimeAndIndex = function() {
	let cur_time = lua.os.time();
	if (__VersionTime === cur_time) {
		__VersionIndex = __VersionIndex + 1;
	} else if (cur_time > __VersionTime) {
		__VersionTime = cur_time;
		__VersionIndex = 0;
	}
	return [__VersionTime, __VersionIndex];
}

}