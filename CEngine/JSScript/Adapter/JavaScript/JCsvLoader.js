{
if (typeof JavaScript === "undefined") JavaScript = {};


if (ALittle.ICsvFile === undefined) throw new Error(" extends class:ALittle.ICsvFile is undefined");
JavaScript.JCsvFile = JavaScript.Class(ALittle.ICsvFile, {
	Load : function(path, headers) {
		return false;
	},
	Close : function() {
	},
	GetPath : function() {
		return undefined;
	},
	ReadCell : function(row, col) {
		return undefined;
	},
	GetRowCount : function() {
		return 0;
	},
	GetColCount : function() {
		return 0;
	},
}, "JavaScript.JCsvFile");

if (ALittle.ICsvFileLoader === undefined) throw new Error(" extends class:ALittle.ICsvFileLoader is undefined");
JavaScript.JCsvFileLoader = JavaScript.Class(ALittle.ICsvFileLoader, {
	Start : function() {
	},
	SetPath : function(file_path, only_from_asset, headers) {
	},
	GetPath : function() {
		return undefined;
	},
	GetID : function() {
		return undefined;
	},
}, "JavaScript.JCsvFileLoader");

}