{
if (typeof JavaScript === "undefined") window.JavaScript = {};


JavaScript.Assert = function(value, msg) {
	if (value !== undefined && value !== false) {
		return;
	}
	if (msg === undefined) {
		msg = "Assert failed";
	}
	throw new Error(msg);
}

}