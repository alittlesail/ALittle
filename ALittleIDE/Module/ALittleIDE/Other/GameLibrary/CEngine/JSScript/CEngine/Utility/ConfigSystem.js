{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.IFileLoader === undefined) throw new Error(" extends class:ALittle.IFileLoader is undefined");
ALittle.JClientFileLoader = JavaScript.Class(ALittle.IFileLoader, {
	Load : function(file_path) {
		let content = undefined;
		let json = undefined;
		if (document.cookie !== undefined && document.cookie !== "") {
			let error = undefined;
			[error, json] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, document.cookie); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
			if (error !== undefined) {
				json = undefined;
			}
		}
		if (json === undefined) {
			return undefined;
		}
		return json[file_path];
	},
}, "ALittle.JClientFileLoader");

if (ALittle.IFileSaver === undefined) throw new Error(" extends class:ALittle.IFileSaver is undefined");
ALittle.JClientFileSaver = JavaScript.Class(ALittle.IFileSaver, {
	Save : function(file_path, content) {
		if (window.wx !== undefined) {
			return false;
		}
		let json = undefined;
		if (document.cookie !== undefined && document.cookie !== "") {
			let error = undefined;
			[error, json] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, document.cookie); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
			if (error !== undefined) {
				json = undefined;
			}
		}
		if (json === undefined) {
			json = {};
		}
		json[file_path] = content;
		document.cookie = ALittle.String_JsonEncode(json);
		return true;
	},
}, "ALittle.JClientFileSaver");

ALittle.CreateConfigSystem = function(file_path, print_error) {
	return ALittle.NewObject(JavaScript.Template(ALittle.JsonConfig, "ALittle.JsonConfig<ALittle.JClientFileLoader, ALittle.JClientFileSaver>", ALittle.JClientFileLoader, ALittle.JClientFileSaver), file_path, print_error);
}

}