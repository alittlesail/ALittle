{
if (typeof ALittle === "undefined") ALittle = {};


ALittle.String_JsonEncode = function(object) {
	return JSON.stringify(object);
}

ALittle.String_JsonDecode = function(text) {
	return JSON.parse(text);
}

ALittle.String_MD5 = function(text) {
	if (window["utf8"] === undefined) {
		ALittle.Error("请在html添加script标签 <script src=\"ALittle/Module/ALittleIDE/Other/GameLibrary/JSNative/md5.min.js\"></script>");
		return undefined;
	}
	return md5(text);
}

ALittle.String_Base64Encode = function(text) {
	return btoa(text);
}

ALittle.String_Base64Decode = function(text) {
	return atob(text);
}

ALittle.String_GetWordCount = function(text) {
	return text.length;
}

ALittle.String_GetByteCount = function(text, word_count) {
	if (text.length < word_count) {
		return text.length;
	} else {
		return word_count;
	}
}

}