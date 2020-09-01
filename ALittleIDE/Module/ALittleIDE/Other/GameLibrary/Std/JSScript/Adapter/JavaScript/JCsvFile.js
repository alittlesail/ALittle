{
if (typeof JavaScript === "undefined") window.JavaScript = {};


if (ALittle.ICsvFile === undefined) throw new Error(" extends class:ALittle.ICsvFile is undefined");
JavaScript.JCsvFile = JavaScript.Class(ALittle.ICsvFile, {
	Ctor : function() {
		this._row_count = 0;
		this._col_count = 0;
		this._file_path = "";
	},
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
	Load : function(path) {
		let [content] = JavaScript.File_LoadFile(path);
		if (content === undefined) {
			ALittle.Error("file load failed:" + path);
			return false;
		}
		this._file_path = path;
		this._data = [];
		let data_index = 1;
		let char_index = 0;
		if (char_index >= content.length) {
			ALittle.Error("file is empty:" + this._file_path);
			return false;
		}
		let cur_char = content.charCodeAt(char_index);
		++ char_index;
		if (char_index >= content.length) {
			this._data[1 - 1] = [];
			this._data[1 - 1][1 - 1] = String.fromCharCode(cur_char);
			return true;
		}
		let next_char = content.charCodeAt(char_index);
		let in_quote = false;
		let row = [];
		let row_index = 0;
		let cell = "";
		while (true) {
			if (cur_char === 44) {
				if (in_quote) {
					cell = cell + ",";
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
					cell = cell + "\n";
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
						if (char_index + 1 < content.length) {
							++ char_index;
							next_char = content.charCodeAt(char_index);
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
						cell = cell + "\"";
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
			if (char_index + 1 < content.length) {
				++ char_index;
				next_char = content.charCodeAt(char_index);
			}
		}
		return true;
	},
	Close : function() {
		this._data = undefined;
		this._row_count = 0;
		this._col_count = 0;
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

}