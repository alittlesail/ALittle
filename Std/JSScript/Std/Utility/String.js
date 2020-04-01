{
if (typeof ALittle === "undefined") ALittle = {};


ALittle.String_JsonEncode = function(object) {
	return JSON.stringify(object);
}

ALittle.String_JsonDecode = function(text) {
	return JSON.parse(text);
}

ALittle.String_MD5 = function(text) {
	return md5(text);
}

ALittle.String_Base64Encode = function(text) {
	return btoa(text);
}

ALittle.String_Base64Decode = function(text) {
	return atob(text);
}

}