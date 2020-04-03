{
if (typeof ALittle === "undefined") ALittle = {};


ALittle.Time_GetCurTime = function() {
	return ALittle.Math_Floor(Date.now() / 1000);
}

}