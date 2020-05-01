{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.Time_GetCurTime = function() {
	return ALittle.Math_Floor(Date.now() / 1000);
}

ALittle.Time_GetCurDate = function(time) {
	{
		let date = new Date();
		if (time !== undefined) {
			date.setTime(time * 1000);
		}
		let result = date.getFullYear() + "-";
		let month = (date.getMonth() + 1);
		if (month < 10) {
			result = result + "-0" + month;
		} else {
			result = result + "-" + month;
		}
		let day = date.getDate();
		if (day < 10) {
			result = result + "-0" + day;
		} else {
			result = result + "-" + day;
		}
		let hours = date.getHours();
		if (hours < 10) {
			result = result + "-0" + hours;
		} else {
			result = result + "-" + hours;
		}
		let minutes = date.getMinutes();
		if (minutes < 10) {
			result = result + "-0" + minutes;
		} else {
			result = result + "-" + minutes;
		}
		let seconds = date.getSeconds();
		if (seconds < 10) {
			result = result + "-0" + seconds;
		} else {
			result = result + "-" + seconds;
		}
		return result;
	}
}

ALittle.Time_GetCurYMD = function(time) {
	{
		let date = new Date();
		if (time !== undefined) {
			date.setTime(time * 1000);
		}
		let result = date.getFullYear() + "-";
		let month = (date.getMonth() + 1);
		if (month < 10) {
			result = result + "-0" + month;
		} else {
			result = result + "-" + month;
		}
		let day = date.getDate();
		if (day < 10) {
			result = result + "-0" + day;
		} else {
			result = result + "-" + day;
		}
		return result;
	}
}

}