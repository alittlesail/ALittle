{
if (typeof JavaScript === "undefined") JavaScript = {};


if (ALittle.ICsvFile === undefined) throw new Error(" extends class:ALittle.ICsvFile is undefined");
JavaScript.JCsvFile = JavaScript.Class(ALittle.ICsvFile, {
	addRow : function(row) {
		if (this._col_count === 0) {
			++ this._row_count;
			this._data[this._row_count - 1] = row;
			this._col_count = row.length;
			return true;
		}
		if (row.length !== this._col_count) {
			ALittle.Error("row(" + ((this._row_count + 1)) + ") col: " + row.length + " != " + this._col_count);
			return false;
		}
		++ this._row_count;
		this._data[this._row_count - 1] = row;
		return true;
	},
	Load : function(path, content, headers) {
		this._file_path = path;
		let char_index = 0;
		this._data = [];
		let data_index = 1;
		let cur_char = undefined;
		let size = content.length;
		if (size === 0) {
			ALittle.Error("file is empty:" + this._file_path);
			return false;
		}
		if (cur_char === 0) {
			ALittle.Error("row(" + ((this._row_count + 1)) + ") has char is 0");
			return false;
		}
		let next_char = 0;
		size = content.charCodeAt(char_index);
		if (size === 0) {
			this._data[1 - 1] = [];
			this._data[1 - 1][1 - 1] = String.fromCharCode(cur_char);
			return true;
		}
		if (next_char === 0) {
			ALittle.Error("row(" + ((this._row_count + 1)) + ") has char is 0");
			return false;
		}
		let in_quote = false;
		let row = [];
		let row_index = 0;
		let cell = "";
		while (true) {
			if (cur_char === 44) {
				if (in_quote) {
					cell = cell + String.fromCharCode(cur_char);
					if (next_char === undefined) {
						ALittle.Error("row(" + this._row_count + ") have no close quote");
						return false;
					}
				} else {
					++ row_index;
					row[row_index - 1] = cell;
					cell = "";
					if (next_char === undefined) {
						++ row_index;
						row[row_index - 1] = "";
						if (!this.addRow(row)) {
							return false;
						}
						row_index = 0;
						row = [];
					}
				}
			} else if (cur_char === 10) {
				if (in_quote) {
					cell = cell + String.fromCharCode(cur_char);
					if (next_char === undefined) {
						ALittle.Error("row(" + this._row_count + ") have no close quote");
						return false;
					}
				} else {
					++ row_index;
					row[row_index - 1] = cell;
					cell = "";
					if (!this.addRow(row)) {
						return false;
					}
					row_index = 0;
					row = [];
				}
			} else if (cur_char === 34) {
				if (in_quote) {
					if (next_char === 34) {
						cell = cell + "\"";
						next_char = undefined;
						if (char_index < content.length) {
							next_char = content.charCodeAt(char_index);
							++ char_index;
						}
						if (next_char === undefined) {
							ALittle.Error("row(" + this._row_count + ") have no close quote");
							return false;
						}
					} else {
						in_quote = false;
						if (next_char === undefined) {
							++ row_index;
							row[row_index - 1] = cell;
							cell = "";
							if (!this.addRow(row)) {
								return false;
							}
							row_index = 0;
							row = [];
						}
					}
				} else {
					if (cell.length === 0) {
						in_quote = true;
					} else {
						cell = cell + String.fromCharCode(cur_char);
					}
					if (next_char === undefined) {
						ALittle.Error("row(" + this._row_count + ") have no close quote");
						return false;
					}
				}
			} else {
				if (in_quote) {
					cell = cell + String.fromCharCode(cur_char);
					if (next_char === undefined) {
						ALittle.Error("row(" + this._row_count + ") have no close quote");
						return false;
					}
				} else {
					if (!(cur_char === 13 && next_char === 10)) {
						cell = cell + String.fromCharCode(cur_char);
					}
					if (next_char === undefined) {
						++ row_index;
						row[row_index - 1] = cell;
						cell = "";
						if (!this.addRow(row)) {
							return false;
						}
						row_index = 0;
						row = [];
					}
				}
			}
			if (next_char === undefined) {
				break;
			}
			cur_char = next_char;
			next_char = undefined;
			if (char_index < content.length) {
				next_char = content.charCodeAt(char_index);
				++ char_index;
			}
		}
		return true;
	},
	Close : function() {
	},
	GetPath : function() {
		return this._file_path;
	},
	ReadCell : function(row, col) {
		return this._data[row - 1][col - 1];
	},
	GetRowCount : function() {
		return this._row_count;
	},
	GetColCount : function() {
		return this._col_count;
	},
}, "JavaScript.JCsvFile");

let __CSVFILE_MAXID = 0;
if (ALittle.ICsvFileLoader === undefined) throw new Error(" extends class:ALittle.ICsvFileLoader is undefined");
JavaScript.JCsvFileLoader = JavaScript.Class(ALittle.ICsvFileLoader, {
	Ctor : function() {
		++ __CSVFILE_MAXID;
		this._id = __CSVFILE_MAXID;
	},
	Start : function() {
		this.StartImpl();
	},
	StartImpl : async function() {
		let host = location.host;
		let port = ALittle.Math_ToInt(location.port);
		let [error, content] = await ALittle.HttpDownloadRequest(host, port, this._file_path);
		if (error !== undefined) {
			let func = window["__ALITTLEAPI_CsvFileLoadFailed"];
			if (func !== undefined) {
				func(this);
			}
			return;
		}
		let file = ALittle.NewObject(JavaScript.JCsvFile);
		if (!file.Load(this._file_path, content.GetContent(), this._headers)) {
			let func = window["__ALITTLEAPI_CsvFileLoadFailed"];
			if (func !== undefined) {
				func(this);
			}
			return;
		}
		let func = window["__ALITTLEAPI_CsvFileLoadSucceed"];
		if (func !== undefined) {
			func(this, file);
		}
	},
	SetPath : function(file_path, only_from_asset, headers) {
		this._file_path = file_path;
		this._headers = headers;
	},
	GetPath : function() {
		return this._file_path;
	},
	GetID : function() {
		return this._id;
	},
}, "JavaScript.JCsvFileLoader");

}