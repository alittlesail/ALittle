{
if (typeof ALittle === "undefined") ALittle = {};


if (ALittle.IFileLoader === undefined) throw new Error(" extends class:ALittle.IFileLoader is undefined");
ALittle.JSClientFileLoader = JavaScript.Class(ALittle.IFileLoader, {
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
}, "ALittle.JSClientFileLoader");

if (ALittle.IFileSaver === undefined) throw new Error(" extends class:ALittle.IFileSaver is undefined");
ALittle.JSClientFileSaver = JavaScript.Class(ALittle.IFileSaver, {
	Save : function(file_path, content) {
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
		return true;
	},
}, "ALittle.JSClientFileSaver");

ALittle.CreateConfigSystem = function(file_path, print_error) {
	return ALittle.NewObject(JavaScript.Template(ALittle.ConfigSystem, "ALittle.ConfigSystem<ALittle.JSClientFileLoader, ALittle.JSClientFileSaver>", ALittle.JSClientFileLoader, ALittle.JSClientFileSaver), file_path, print_error);
}

}