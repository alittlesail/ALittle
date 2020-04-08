{
if (typeof ALittle === "undefined") ALittle = {};


ALittle.ISchedule = JavaScript.Class(undefined, {
	Run : function() {
	},
}, "ALittle.ISchedule");

let GetSchedule = function() {
	return A_JSchedule;
}

window.A_Schedule = GetSchedule();
}