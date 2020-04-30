{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(115253948, "ALittle.KeyValueInfo", {
name : "ALittle.KeyValueInfo", ns_name : "ALittle", rl_name : "KeyValueInfo", hash_code : 115253948,
name_list : ["key","value"],
type_list : ["string","string"],
option_map : {}
})

ALittle.ICsvFile = JavaScript.Class(undefined, {
	Close : function() {
	},
	ReadCell : function(row, col) {
		return "";
	},
	GetRowCount : function() {
		return 0;
	},
	GetColCount : function() {
		return 0;
	},
}, "ALittle.ICsvFile");

ALittle.ICsvFileLoader = JavaScript.Class(undefined, {
	Start : function() {
	},
	SetPath : function(file_path, only_from_asset) {
	},
	GetPath : function() {
		return undefined;
	},
	GetID : function() {
		return undefined;
	},
}, "ALittle.ICsvFileLoader");

ALittle.CsvConfig = JavaScript.Class(undefined, {
	Load : function(file_path) {
		let js_file = ALittle.NewObject(JavaScript.JCsvFile);
		JavaScript.Assert(js_file.Load(file_path), file_path + " load failed!");
		this.Init(js_file);
		ALittle.Log(file_path + " load succeed!");
	},
	Init : function(file) {
	},
}, "ALittle.CsvConfig");

if (ALittle.CsvConfig === undefined) throw new Error(" extends class:ALittle.CsvConfig is undefined");
ALittle.KeyValueConfig = JavaScript.Class(ALittle.CsvConfig, {
	Ctor : function() {
		this._data = {};
		this._csv_info = ALittle.CreateCsvInfo(this.__class.__element[0]);
	},
	Init : function(file) {
		if (file === undefined) {
			return;
		}
		let reflt = this.__class.__element[0];
		let handle_map = {};
		let ___OBJECT_1 = this._csv_info.handle;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let handle = ___OBJECT_1[index - 1];
			if (handle === undefined) break;
			handle_map[handle.var_name] = handle;
		}
		let row_count = file.GetRowCount();
		for (let row = 1; row <= row_count; row += 1) {
			let key = file.ReadCell(row, 1);
			let value = file.ReadCell(row, 2);
			if (key !== undefined && value !== undefined) {
				let handle = handle_map[key];
				if (handle !== undefined) {
					let hvalue = handle.func(value, handle);
					if (hvalue !== undefined) {
						this._data[key] = hvalue;
					} else {
						ALittle.Error("key:" + key + " load failed!");
					}
				}
			}
		}
		file.Close();
	},
	GetFieldNameList : function() {
		let rflt = ___all_struct.get(115253948);
		return rflt.name_list;
	},
	GetData : function() {
		return this._data;
	},
}, "ALittle.KeyValueConfig");

if (ALittle.CsvConfig === undefined) throw new Error(" extends class:ALittle.CsvConfig is undefined");
ALittle.CsvTableConfig = JavaScript.Class(ALittle.CsvConfig, {
	Ctor : function() {
		let error = undefined;
		[error, this._csv_info] = (function() { try { let ___VALUE = ALittle.CreateCsvInfo.call(undefined, this.__class.__element[0]); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
		if (error !== undefined) {
			ALittle.Error(error);
		}
		this._col_map = new Map();
	},
	Init : function(file) {
		if (this._csv_file !== undefined) {
			this._csv_file.Close();
		}
		this._csv_file = file;
		if (this._csv_file === undefined) {
			return;
		}
		let rflt = this.__class.__element[0];
		let name_map = {};
		let ___OBJECT_2 = rflt.name_list;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let name = ___OBJECT_2[index - 1];
			if (name === undefined) break;
			name_map[name] = index;
		}
		for (let i = 1; i <= this._csv_file.GetColCount(); i += 1) {
			let name = this._csv_file.ReadCell(1, i);
			let index = name_map[name];
			if (index !== undefined) {
				this._col_map.set(index, i);
			}
		}
		this.onInit();
	},
	onInit : function() {
	},
	LoadCell : function(row) {
		let value = {};
		let ___OBJECT_3 = this._csv_info.handle;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let handle = ___OBJECT_3[index - 1];
			if (handle === undefined) break;
			let real = this._col_map.get(index);
			if (real === undefined) {
				value[handle.var_name] = handle.func("", handle);
			} else {
				let read = this._csv_file.ReadCell(row, real);
				if (read === undefined) {
					value[handle.var_name] = handle.func("", handle);
				} else {
					value[handle.var_name] = handle.func(read, handle);
				}
			}
		}
		return value;
	},
}, "ALittle.CsvTableConfig");

if (ALittle.CsvTableConfig === undefined) throw new Error(" extends class:ALittle.CsvTableConfig is undefined");
ALittle.SingleKeyTableConfig = JavaScript.Class(ALittle.CsvTableConfig, {
	Ctor : function() {
		this._key_map = new Map();
		this._cache_map = new Map();
	},
	onInit : function() {
		let rflt = this.__class.__element[0];
		let key_type = rflt.type_list[1 - 1];
		let key_index = this._col_map.get(1);
		let is_int = key_type === "int" || key_type === "long";
		let is_double = key_type === "double";
		let row_count = this._csv_file.GetRowCount();
		for (let row = 2; row <= row_count; row += 1) {
			let value = this._csv_file.ReadCell(row, key_index);
			if (value !== undefined) {
				if (is_int) {
					this._key_map.set(ALittle.Math_ToInt(value), row);
				} else if (is_double) {
					this._key_map.set(ALittle.Math_ToDouble(value), row);
				} else {
					this._key_map.set(value, row);
				}
			}
		}
	},
	GetData : function(key) {
		if (this._csv_file === undefined) {
			return undefined;
		}
		let value = this._cache_map.get(key);
		if (value !== undefined) {
			return value;
		}
		let row = this._key_map.get(key);
		if (row === undefined) {
			return undefined;
		}
		value = this.LoadCell(row);
		if (value === undefined) {
			return undefined;
		}
		this._cache_map.set(key, value);
		return value;
	},
}, "ALittle.SingleKeyTableConfig");

if (ALittle.CsvTableConfig === undefined) throw new Error(" extends class:ALittle.CsvTableConfig is undefined");
ALittle.DoubleKeyTableConfig = JavaScript.Class(ALittle.CsvTableConfig, {
	Ctor : function() {
		this._key_map = new Map();
		this._cache_map = new Map();
	},
	onInit : function() {
		let rflt = this.__class.__element[0];
		let first_key_type = rflt.type_list[1 - 1];
		let first_key_index = this._col_map.get(1);
		let first_is_int = first_key_type === "int" || first_key_type === "long";
		let first_is_double = first_key_type === "double";
		let second_key_type = rflt.type_list[2 - 1];
		let second_key_index = this._col_map.get(2);
		let second_is_int = second_key_type === "int" || second_key_type === "long";
		let second_is_double = second_key_type === "double";
		let row_count = this._csv_file.GetRowCount();
		for (let row = 2; row <= row_count; row += 1) {
			let tmp = undefined;
			let value = this._csv_file.ReadCell(row, first_key_index);
			if (value !== undefined) {
				if (first_is_int) {
					tmp = this._key_map.get(ALittle.Math_ToInt(value));
					if (tmp === undefined) {
						tmp = new Map();
						this._key_map.set(ALittle.Math_ToInt(value), tmp);
					}
				} else if (first_is_double) {
					tmp = this._key_map.get(ALittle.Math_ToDouble(value));
					if (tmp === undefined) {
						tmp = new Map();
						this._key_map.set(ALittle.Math_ToDouble(value), tmp);
					}
				} else {
					tmp = this._key_map.get(value);
					if (tmp === undefined) {
						tmp = new Map();
						this._key_map.set(value, tmp);
					}
				}
			}
			if (tmp === undefined) {
				continue;
			}
			value = this._csv_file.ReadCell(row, second_key_index);
			if (value !== undefined) {
				if (second_is_int) {
					tmp.set(ALittle.Math_ToInt(value), row);
				} else if (second_is_double) {
					tmp.set(ALittle.Math_ToDouble(value), row);
				} else {
					tmp.set(value, row);
				}
			}
		}
	},
	GetData : function(first_key, second_key) {
		if (this._csv_file === undefined) {
			return undefined;
		}
		let value_map = this._cache_map.get(first_key);
		if (value_map !== undefined) {
			let value = value_map.get(second_key);
			if (value !== undefined) {
				return value;
			}
		}
		let key_tmp = this._key_map.get(first_key);
		if (key_tmp === undefined) {
			return undefined;
		}
		let row = key_tmp.get(second_key);
		if (row === undefined) {
			return undefined;
		}
		let value = this.LoadCell(row);
		if (value === undefined) {
			return undefined;
		}
		let tmp = this._cache_map.get(first_key);
		if (tmp === undefined) {
			tmp = new Map();
			this._cache_map.set(first_key, tmp);
		}
		tmp.set(second_key, value);
		return value;
	},
}, "ALittle.DoubleKeyTableConfig");

}