{
if (typeof ALittle === "undefined") ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(115253948, "ALittle.KeyValueInfo", {
name : "ALittle.KeyValueInfo", ns_name : "ALittle", rl_name : "KeyValueInfo", hash_code : 115253948,
name_list : ["key","value"],
type_list : ["string","string"],
option_map : {}
})

ALittle.CsvConfig = JavaScript.Class(undefined, {
	Load : function(file_path) {
		let name_list = this.GetFieldNameList();
		let js_loader = ALittle.NewObject(JavaScript.JCsvFile);
		JavaScript.Assert(js_loader.Load(file_path, ALittle.String_Join(name_list, ",")), file_path + " load failed!");
		this.Init(js_loader);
		ALittle.Log(file_path + " load succeed!");
	},
	GetFieldNameList : function() {
		return undefined;
	},
	Init : function(loader) {
	},
}, "ALittle.CsvConfig");

if (ALittle.CsvConfig === undefined) throw new Error(" extends class:ALittle.CsvConfig is undefined");
ALittle.CsvTableConfig = JavaScript.Class(ALittle.CsvConfig, {
	Ctor : function() {
		let error = undefined;
		[error, this._csv_info] = (function() { try { let ___VALUE = ALittle.CreateCsvInfo.call(undefined, this.__class.__element[0]); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } })();
		if (error !== undefined) {
			ALittle.Error(error);
		}
	},
	Init : function(loader) {
		this._csv_file = loader;
	},
	GetFieldInfo : function(field) {
		let rflt = this.__class.__element[0];
		let field_index = 0;
		let is_number = false;
		let ___OBJECT_1 = rflt.name_list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let name = ___OBJECT_1[index - 1];
			if (name === undefined) break;
			if (name === field) {
				field_index = index;
				let var_type = rflt.type_list[index - 1];
				is_number = var_type === "int" || var_type === "double" || var_type === "long";
				break;
			}
		}
		return [field_index, is_number];
	},
	GetFieldNameList : function() {
		let rflt = this.__class.__element[0];
		return rflt.name_list;
	},
	ReadCell : function(lua_row, lua_col) {
		return this._csv_file.ReadCell(lua_row, lua_col);
	},
	LoadCell : function(row) {
		let value = {};
		let ___OBJECT_2 = this._csv_info.handle;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let handle = ___OBJECT_2[index - 1];
			if (handle === undefined) break;
			value[handle.var_name] = handle.func(this._csv_file.ReadCell(row, index), handle);
		}
		return value;
	},
}, "ALittle.CsvTableConfig");

if (ALittle.CsvConfig === undefined) throw new Error(" extends class:ALittle.CsvConfig is undefined");
ALittle.KeyValueConfig = JavaScript.Class(ALittle.CsvConfig, {
	Ctor : function() {
		this._data = {};
		this._csv_info = ALittle.CreateCsvInfo(this.__class.__element[0]);
	},
	Init : function(loader) {
		if (loader === undefined) {
			return;
		}
		let reflt = this.__class.__element[0];
		let handle_map = {};
		let ___OBJECT_3 = this._csv_info.handle;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let handle = ___OBJECT_3[index - 1];
			if (handle === undefined) break;
			handle_map[handle.var_name] = handle;
		}
		let row_count = loader.GetRowCount();
		for (let row = 1; row <= row_count; row += 1) {
			let key = loader.ReadCell(row, 1);
			let value = loader.ReadCell(row, 2);
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
		loader.Close();
	},
	GetFieldNameList : function() {
		let rflt = ___all_struct.get(115253948);
		return rflt.name_list;
	},
	GetData : function() {
		return this._data;
	},
}, "ALittle.KeyValueConfig");

if (ALittle.CsvTableConfig === undefined) throw new Error(" extends class:ALittle.CsvTableConfig is undefined");
ALittle.SingleKeyTableConfig = JavaScript.Class(ALittle.CsvTableConfig, {
	Ctor : function() {
		this._key_map = new Map();
		this._cache_map = new Map();
	},
	get key_map() {
		return this._key_map;
	},
	Init : function(loader) {
		if (this._csv_file !== undefined) {
			this._csv_file.Close();
		}
		this._csv_file = loader;
		if (this._csv_file === undefined) {
			return;
		}
		let rflt = this.__class.__element[0];
		let key_type = rflt.type_list[1 - 1];
		let is_number = key_type === "int" || key_type === "double" || key_type === "long";
		let row_count = this._csv_file.GetRowCount();
		for (let row = 1; row <= row_count; row += 1) {
			let value = this._csv_file.ReadCell(row, 1);
			if (value !== undefined) {
				if (is_number) {
					this._key_map.set(lua.tonumber(value), row);
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
	CreateIndex : function(field) {
		if (this._csv_file === undefined) {
			return undefined;
		}
		let [col_index, is_number] = this.GetFieldInfo(field);
		if (col_index === 0) {
			return undefined;
		}
		return ALittle.NewObject(JavaScript.Template(ALittle.SingleKeyTableIndexConfig, "ALittle.SingleKeyTableIndexConfig<" + INDEX.__name + ", " + this.__class.__element[1].__name + ", " + this.__class.__element[2].name + ">", INDEX, this.__class.__element[1], this.__class.__element[2]), this, col_index, is_number);
	},
}, "ALittle.SingleKeyTableConfig");

ALittle.SingleKeyTableIndexConfig = JavaScript.Class(undefined, {
	Ctor : function(parent, col_index, is_number) {
		this._parent = parent;
		this._value_map = new Map();
		for (let [key, row] of this._parent.key_map) {
			if (row === undefined) continue;
			let value = undefined;
			if (is_number) {
				value = lua.tonumber(this._parent.ReadCell(row, col_index));
			} else {
				value = this._parent.ReadCell(row, col_index);
			}
			let key_set = this._value_map.get(value);
			if (key_set === undefined) {
				key_set = new Map();
				this._value_map.set(value, key_set);
			}
			key_set.set(key, true);
		}
	},
	GetKeySet : function(index) {
		return this._value_map.get(index);
	},
	GetOne : function(index) {
		let keys = this._value_map.get(index);
		if (keys === undefined) {
			return undefined;
		}
		for (let [k, _] of keys) {
			if (_ === undefined) continue;
			return this._parent.GetData(k);
		}
	},
	GetList : function(index) {
		let list = [];
		let keys = this._value_map.get(index);
		if (keys === undefined) {
			return list;
		}
		let count = 0;
		for (let [k, _] of keys) {
			if (_ === undefined) continue;
			++ count;
			list[count - 1] = this._parent.GetData(k);
		}
		return list;
	},
}, "ALittle.SingleKeyTableIndexConfig");

if (ALittle.CsvTableConfig === undefined) throw new Error(" extends class:ALittle.CsvTableConfig is undefined");
ALittle.DoubleKeyTableConfig = JavaScript.Class(ALittle.CsvTableConfig, {
	Ctor : function() {
		this._key_map = new Map();
		this._cache_map = new Map();
	},
	Init : function(loader) {
		if (this._csv_file !== undefined) {
			this._csv_file.Close();
		}
		this._csv_file = loader;
		if (this._csv_file === undefined) {
			return;
		}
		let rflt = this.__class.__element[0];
		let first_key_type = rflt.type_list[1 - 1];
		let first_is_number = first_key_type === "int" || first_key_type === "double" || first_key_type === "long";
		let second_key_type = rflt.type_list[2 - 1];
		let second_is_number = second_key_type === "int" || second_key_type === "double" || second_key_type === "long";
		let row_count = this._csv_file.GetRowCount();
		for (let row = 1; row <= row_count; row += 1) {
			let tmp = undefined;
			let value = this._csv_file.ReadCell(row, 1);
			if (value !== undefined) {
				if (first_is_number) {
					tmp = this._key_map.get(lua.tonumber(value));
					if (tmp === undefined) {
						tmp = new Map();
						this._key_map.set(lua.tonumber(value), tmp);
					}
				} else {
					tmp = this._key_map.get(value);
					if (tmp === undefined) {
						tmp = new Map();
						this._key_map.set(value, tmp);
					}
				}
			}
			value = this._csv_file.ReadCell(row, 2);
			if (value !== undefined) {
				if (second_is_number) {
					tmp.set(lua.tonumber(value), row);
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