{
if (typeof ALittle === "undefined") ALittle = {};


ALittle.String_JsonEncode = function(object) {
	return JSON.stringify(object);
}

ALittle.String_JsonDecode = function(text) {
	return JSON.parse(text);
}

}