
if (typeof JavaScript === "undefined") JavaScript = {};
if (typeof ___RETURN === "undefined") ___RETURN = [];


JavaScript.Assert = function(value, msg) {
	if (value !== undefined && value !== false) {
		return;
	}
	if (msg === undefined) {
		msg = "Assert failed";
	}
	throw new Error(msg);
}

