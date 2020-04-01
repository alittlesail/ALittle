{
if (typeof JavaScript === "undefined") JavaScript = {};


if (ALittle.ICsvFile === undefined) throw new Error(" extends class:ALittle.ICsvFile is undefined");
JavaScript.JCsvLoader = JavaScript.Class(ALittle.ICsvFile, {
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
}, "JavaScript.JCsvLoader");

}