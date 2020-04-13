{
if (typeof ALittle === "undefined") ALittle = {};

ALittle.RegStruct(1358089220, "ALittle.MysqlExecuteInfo", {
name : "ALittle.MysqlExecuteInfo", ns_name : "ALittle", rl_name : "MysqlExecuteInfo", hash_code : 1358089220,
name_list : ["thread","query"],
type_list : ["ALittle.Thread","ALittle.MysqlStatementQuery"],
option_map : {}
})
ALittle.RegStruct(-930447138, "ALittle.Thread", {
name : "ALittle.Thread", ns_name : "ALittle", rl_name : "Thread", hash_code : -930447138,
name_list : [],
type_list : [],
option_map : {}
})

ALittle.MysqlStatementQuery = JavaScript.Class(undefined, {
	Ctor : function() {
		this._query = ALittle.NewObject(lua.__CPPAPIMysqlStatementQuery);
	},
	set sql(value) {
		if (value === undefined) {
			value = "";
		}
		this._query.SetSQL(value);
	},
	get sql() {
		return this._query.GetSQL();
	},
	get count() {
		return this._query.GetCount();
	},
	get affect_count() {
		return this._query.GetAffectCount();
	},
	Execute : function(thread_id) {
		return new Promise((async function(___COROUTINE, ___) {
			___COROUTINE(await A_MysqlSystem.ExecuteStatement(this, thread_id)); return;
			___COROUTINE();
		}).bind(this));
	},
	get String() {
		return this._query.ReadString();
	},
	set String(value) {
		if (value === undefined) {
			this._query.PushString("");
		} else {
			this._query.PushString(value);
		}
	},
	get Int() {
		return this._query.ReadInt();
	},
	set Int(value) {
		if (value === undefined) {
			this._query.PushInt(0);
		} else {
			this._query.PushInt(value);
		}
	},
	get Long() {
		return this._query.ReadI64();
	},
	set Long(value) {
		if (value === undefined) {
			this._query.PushI64(0);
		} else {
			this._query.PushI64(value);
		}
	},
	get Double() {
		return this._query.ReadDouble();
	},
	set Double(value) {
		if (value === undefined) {
			this._query.PushDouble(0);
		} else {
			this._query.PushDouble(value);
		}
	},
	get value() {
		let type_int = this._query.ReadType();
		if (type_int === -1) {
			return undefined;
		}
		if (type_int === 0) {
			return this._query.ReadBool();
		}
		if (type_int === 1) {
			return this._query.ReadShort();
		}
		if (type_int === 2) {
			return this._query.ReadInt();
		}
		if (type_int === 3) {
			return this._query.ReadI64();
		}
		if (type_int === 4) {
			return this._query.ReadFloat();
		}
		if (type_int === 5) {
			return this._query.ReadDouble();
		}
		if (type_int === 6) {
			return this._query.ReadString();
		}
		return undefined;
	},
	set value(v) {
		let type_str = lua.type(v);
		if (type_str === "number") {
			if (lua.math.floor(v) < v) {
				this._query.PushDouble(v);
			} else {
				this._query.PushInt(v);
			}
		} else if (type_str === "string") {
			this._query.PushString(v);
		} else if (type_str === "boolean") {
			if (v === false) {
				this._query.PushInt(0);
			} else {
				this._query.PushInt(1);
			}
		} else if (type_str === "table") {
			this._query.PushString(lua.ajson.encode(v));
		} else {
			this._query.PushString(lua.tostring(v));
		}
	},
	SelectPageBegin : function(field, condition, table_name, key, asc) {
		let asc_str = " DESC";
		if (!asc) {
			asc_str = " ASC";
		}
		let sql = undefined;
		let cross = ALittle.String_Find(table_name, ",");
		if (cross !== undefined) {
			let field_list = ALittle.String_Split(table_name, ",");
			let as_name_list = [];
			let field_name_list = [];
			let ___OBJECT_1 = field_list;
			for (let k = 1; k <= ___OBJECT_1.length; ++k) {
				let v = ___OBJECT_1[k - 1];
				if (v === undefined) break;
				let as_name = "tt" + k;
				ALittle.List_Push(as_name_list, as_name);
				ALittle.List_Push(field_name_list, v + " as " + as_name);
			}
			field = ALittle.String_Join(field_name_list, ",");
			let as_field = ALittle.String_Join(as_name_list, ",");
			if (condition === undefined) {
				condition = "";
			}
			if (key !== undefined) {
				key = "ORDER BY " + key + asc_str;
			} else {
				key = "";
			}
			sql = "SELECT " + as_field + " FROM ( SELECT @rownum:=@rownum+1 AS RowNumber, " + field + " FROM " + table_name + ", (SELECT @rownum:=0) __rownumb " + condition + " " + key + " ) AS temp WHERE temp.RowNumber BETWEEN ? AND ?";
		} else {
			if (condition === undefined) {
				condition = "";
			}
			if (key !== undefined) {
				key = "ORDER BY " + key + asc_str;
			} else {
				key = "";
			}
			sql = "SELECT " + field + " FROM (  SELECT @rownum:=@rownum+1 AS RowNumber, " + field + " FROM " + table_name + ", (SELECT @rownum:=0) __rownumb " + condition + " " + key + " ) AS temp WHERE temp.RowNumber BETWEEN ? AND ?";
		}
		this._query.SetSQL(sql);
	},
	SelectPageEnd : function(page_size, page_index) {
		let start_index = (page_index - 1) * page_size + 1;
		if (start_index < 1) {
			start_index = 1;
		}
		let end_index = page_index * page_size;
		this.Int = start_index;
		this.Int = end_index;
	},
	HasNext : function() {
		return this._query.HasNext();
	},
}, "ALittle.MysqlStatementQuery");

let __TypeMap = {};
__TypeMap["bool"] = 1;
__TypeMap["int"] = 2;
__TypeMap["long"] = 3;
__TypeMap["double"] = 4;
__TypeMap["string"] = 5;
ALittle.MysqlSystem = JavaScript.Class(undefined, {
	Ctor : function() {
		this._id_creator = ALittle.NewObject(ALittle.SafeIDCreator);
		this._info_map = new Map();
		this._execute_empty_map = new Map();
	},
	HandleMysqlQueryTask : function(id, reason) {
		let info = this._info_map.get(id);
		if (info === undefined) {
			return;
		}
		this._id_creator.ReleaseID(id);
		this._info_map.delete(id);
		let [result, error] = lua.coroutine.resume(info.thread, reason);
		if (result !== true) {
			ALittle.Error(error);
		}
	},
	HandleMysqlEmptyTask : function(id, reason) {
		let thread = this._execute_empty_map.get(id);
		if (thread === undefined) {
			return;
		}
		this._id_creator.ReleaseID(id);
		this._execute_empty_map.delete(id);
		let [result, error] = lua.coroutine.resume(thread, reason);
		if (result !== true) {
			ALittle.Error(error);
		}
	},
	ExecuteStatement : function(query, thread_id) {
		return new Promise((function(___COROUTINE, ___) {
			if (___COROUTINE === undefined) {
				___COROUTINE("当前不是协程"); return;
			}
			if (thread_id === undefined) {
				thread_id = 0;
			}
			let id = this._id_creator.CreateID();
			if (!__CPPAPI_ServerSchedule.AddMysqlStatement(thread_id, id, query._query)) {
				this._id_creator.ReleaseID(id);
				___COROUTINE("任务添加失败"); return;
			}
			let info = {};
			info.thread = ___COROUTINE;
			info.query = query;
			this._info_map.set(id, info);
			return;
			___COROUTINE();
		}).bind(this));
	},
	ExecuteNormal : function(sql, thread_id) {
		return new Promise((function(___COROUTINE, ___) {
			if (___COROUTINE === undefined) {
				___COROUTINE("当前不是协程"); return;
			}
			if (thread_id === undefined) {
				thread_id = 0;
			}
			let id = this._id_creator.CreateID();
			if (!__CPPAPI_ServerSchedule.AddMysqlNormal(thread_id, id, sql)) {
				this._id_creator.ReleaseID(id);
				___COROUTINE("任务添加失败"); return;
			}
			let info = {};
			info.thread = ___COROUTINE;
			this._info_map.set(id, info);
			return;
			___COROUTINE();
		}).bind(this));
	},
	ExecuteEmpty : function(thread_id) {
		return new Promise((function(___COROUTINE, ___) {
			if (___COROUTINE === undefined) {
				___COROUTINE("当前不是协程"); return;
			}
			if (thread_id === undefined) {
				thread_id = 0;
			}
			let id = this._id_creator.CreateID();
			if (!__CPPAPI_ServerSchedule.AddMysqlEmpty(thread_id, id)) {
				this._id_creator.ReleaseID(id);
				___COROUTINE("任务添加失败"); return;
			}
			this._execute_empty_map.set(id, ___COROUTINE);
			return;
			___COROUTINE();
		}).bind(this));
	},
	SelectCountByReflect : function(info, key, value, thread_id) {
		return new Promise((async function(___COROUTINE, ___) {
			if (value === undefined) {
				___COROUTINE(["value == null", 0]); return;
			}
			let sql = "SELECT COUNT(*) FROM `";
			sql = sql + info.rl_name;
			sql = sql + "` WHERE `";
			sql = sql + key;
			sql = sql + "`=?";
			let query = ALittle.NewObject(ALittle.MysqlStatementQuery);
			query.sql = sql;
			query.value = value;
			let error = await this.ExecuteStatement(query, thread_id);
			if (error !== undefined) {
				___COROUTINE([error, 0]); return;
			}
			___COROUTINE([undefined, query.Long]); return;
			___COROUTINE();
		}).bind(this));
	},
	SelectCount : function(T, key, value, thread_id) {
		return new Promise((async function(___COROUTINE, ___) {
			___COROUTINE([await this.SelectCountByReflect(T, key, value, thread_id)]); return;
			___COROUTINE();
		}).bind(this));
	},
	SelectOneFromByKeyByReflect : function(info, key, value, thread_id) {
		return new Promise((async function(___COROUTINE, ___) {
			if (value === undefined) {
				___COROUTINE(["value == null", undefined]); return;
			}
			let sql = "SELECT ";
			let field_list = [];
			let ___OBJECT_2 = info.name_list;
			for (let i = 1; i <= ___OBJECT_2.length; ++i) {
				let name = ___OBJECT_2[i - 1];
				if (name === undefined) break;
				ALittle.List_Push(field_list, "`" + name + "`");
			}
			sql = sql + ALittle.String_Join(field_list, ",");
			sql = sql + " FROM `";
			sql = sql + info.rl_name;
			sql = sql + "` WHERE `";
			sql = sql + key;
			sql = sql + "`=?";
			let query = ALittle.NewObject(ALittle.MysqlStatementQuery);
			query.sql = sql;
			query.value = value;
			let error = await this.ExecuteStatement(query, thread_id);
			if (error !== undefined) {
				___COROUTINE([error, undefined]); return;
			}
			if (query.count === 0) {
				___COROUTINE([undefined, undefined]); return;
			}
			let map = {};
			let ___OBJECT_3 = info.name_list;
			for (let i = 1; i <= ___OBJECT_3.length; ++i) {
				let name = ___OBJECT_3[i - 1];
				if (name === undefined) break;
				let type = __TypeMap[info.type_list[i - 1]];
				if (type === 1) {
					map[name] = query.Int !== 0;
				} else if (type === 2) {
					map[name] = query.Int;
				} else if (type === 3) {
					map[name] = query.Long;
				} else if (type === 4) {
					map[name] = query.Double;
				} else if (type === 5) {
					map[name] = query.String;
				} else {
					let value = query.String;
					if (value === "") {
						map[name] = new Map();
					} else {
						let content = undefined;
						[error, content] = (function() { try { let ___VALUE = lua.ajson.decode.call(undefined, value); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
						if (error !== undefined) {
							___COROUTINE([error, undefined]); return;
						} else {
							map[name] = content;
						}
					}
				}
			}
			___COROUTINE([undefined, map]); return;
			___COROUTINE();
		}).bind(this));
	},
	SelectOneFromByKey : function(T, key, value, thread_id) {
		return new Promise((async function(___COROUTINE, ___) {
			___COROUTINE([await this.SelectOneFromByKeyByReflect(T, key, value, thread_id)]); return;
			___COROUTINE();
		}).bind(this));
	},
	SelectListFromByMapByReflect : function(info, value_map, thread_id) {
		return new Promise((async function(___COROUTINE, ___) {
			let sql = "SELECT ";
			let field_list = [];
			let ___OBJECT_4 = info.name_list;
			for (let i = 1; i <= ___OBJECT_4.length; ++i) {
				let name = ___OBJECT_4[i - 1];
				if (name === undefined) break;
				ALittle.List_Push(field_list, "`" + name + "`");
			}
			sql = sql + ALittle.String_Join(field_list, ",");
			sql = sql + " FROM `";
			sql = sql + info.rl_name;
			sql = sql + "`";
			let value_list = [];
			if (value_map !== undefined) {
				let condition = "";
				let where_list = [];
				let index = 1;
				let ___OBJECT_5 = value_map;
				for (let key in ___OBJECT_5) {
					let value = ___OBJECT_5[key];
					if (value === undefined) continue;
					where_list[index - 1] = "`" + key + "`=?";
					value_list[index - 1] = value;
				}
				condition = ALittle.String_Join(where_list, " AND ");
				if (condition !== "") {
					condition = " WHERE " + condition;
				}
				sql = sql + condition;
			}
			let query = ALittle.NewObject(ALittle.MysqlStatementQuery);
			query.sql = sql;
			let ___OBJECT_6 = value_list;
			for (let index = 1; index <= ___OBJECT_6.length; ++index) {
				let value = ___OBJECT_6[index - 1];
				if (value === undefined) break;
				query.value = value;
			}
			let error = await this.ExecuteStatement(query, thread_id);
			if (error !== undefined) {
				___COROUTINE([error, undefined]); return;
			}
			if (query.count === 0) {
				___COROUTINE([undefined, []]); return;
			}
			let list = [];
			for (let row = 1; row <= query.count; row += 1) {
				let map = {};
				let ___OBJECT_7 = info.name_list;
				for (let i = 1; i <= ___OBJECT_7.length; ++i) {
					let name = ___OBJECT_7[i - 1];
					if (name === undefined) break;
					let type = __TypeMap[info.type_list[i - 1]];
					if (type === 1) {
						map[name] = query.Int !== 0;
					} else if (type === 2) {
						map[name] = query.Int;
					} else if (type === 3) {
						map[name] = query.Long;
					} else if (type === 4) {
						map[name] = query.Double;
					} else if (type === 5) {
						map[name] = query.String;
					} else {
						let value = query.String;
						if (value === "") {
							map[name] = new Map();
						} else {
							let content = undefined;
							[error, content] = (function() { try { let ___VALUE = lua.ajson.decode.call(undefined, value); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
							if (error !== undefined) {
								___COROUTINE([error, undefined]); return;
							} else {
								map[name] = content;
							}
						}
					}
				}
				list[row - 1] = map;
			}
			___COROUTINE([undefined, list]); return;
			___COROUTINE();
		}).bind(this));
	},
	SelectListFromByMap : function(T, value_map, thread_id) {
		return new Promise((async function(___COROUTINE, ___) {
			___COROUTINE([await this.SelectListFromByMapByReflect(T, value_map, thread_id)]); return;
			___COROUTINE();
		}).bind(this));
	},
	InsertIntoByReflect : function(info, map, table_name, thread_id) {
		return new Promise((async function(___COROUTINE, ___) {
			let sql = "INSERT INTO `";
			if (table_name === undefined) {
				sql = sql + info.rl_name;
			} else {
				sql = sql + table_name;
			}
			sql = sql + "` (";
			let field_list = [];
			let ___OBJECT_8 = info.name_list;
			for (let i = 1; i <= ___OBJECT_8.length; ++i) {
				let name = ___OBJECT_8[i - 1];
				if (name === undefined) break;
				ALittle.List_Push(field_list, "`" + name + "`");
			}
			sql = sql + ALittle.String_Join(field_list, ",");
			sql = sql + ") VALUES (";
			let value_list = [];
			let ___OBJECT_9 = info.name_list;
			for (let i = 1; i <= ___OBJECT_9.length; ++i) {
				let name = ___OBJECT_9[i - 1];
				if (name === undefined) break;
				ALittle.List_Push(value_list, "?");
			}
			sql = sql + ALittle.String_Join(value_list, ",");
			sql = sql + ")";
			let query = ALittle.NewObject(ALittle.MysqlStatementQuery);
			query.sql = sql;
			let ___OBJECT_10 = info.name_list;
			for (let i = 1; i <= ___OBJECT_10.length; ++i) {
				let name = ___OBJECT_10[i - 1];
				if (name === undefined) break;
				let type = __TypeMap[info.type_list[i - 1]];
				let value = map[name];
				if (type === 1) {
					if (value !== true) {
						query.Int = 0;
					} else {
						query.Int = 1;
					}
				} else if (type === 2) {
					if (value !== undefined) {
						query.Int = lua.tonumber(value);
					} else {
						query.Int = 0;
					}
				} else if (type === 3) {
					if (value !== undefined) {
						query.Long = lua.tonumber(value);
					} else {
						query.Long = 0;
					}
				} else if (type === 4) {
					if (value !== undefined) {
						query.Double = lua.tonumber(value);
					} else {
						query.Double = 0;
					}
				} else if (type === 5) {
					if (value !== undefined) {
						query.String = lua.tostring(value);
					} else {
						query.String = "";
					}
				} else {
					if (value !== undefined) {
						query.String = lua.ajson.encode(value);
					} else {
						query.String = "";
					}
				}
			}
			___COROUTINE(await this.ExecuteStatement(query, thread_id)); return;
			___COROUTINE();
		}).bind(this));
	},
	InsertInto : function(T, value, table_name, thread_id) {
		return new Promise((async function(___COROUTINE, ___) {
			___COROUTINE(await this.InsertIntoByReflect(T, value, table_name, thread_id)); return;
			___COROUTINE();
		}).bind(this));
	},
	UpdateOneByReflect : function(info, map, key, key_value, thread_id) {
		return new Promise((async function(___COROUTINE, ___) {
			if (key_value === undefined) {
				___COROUTINE("key_value == null"); return;
			}
			let sql = "UPDATE `";
			sql = sql + info.rl_name;
			sql = sql + "` SET ";
			let set_list = [];
			let ___OBJECT_11 = info.name_list;
			for (let i = 1; i <= ___OBJECT_11.length; ++i) {
				let name = ___OBJECT_11[i - 1];
				if (name === undefined) break;
				if (key !== name) {
					ALittle.List_Push(set_list, "`" + name + "`=?");
				}
			}
			sql = sql + ALittle.String_Join(set_list, ",");
			sql = sql + " WHERE `";
			sql = sql + key;
			sql = sql + "`=?";
			let query = ALittle.NewObject(ALittle.MysqlStatementQuery);
			query.sql = sql;
			let ___OBJECT_12 = info.name_list;
			for (let i = 1; i <= ___OBJECT_12.length; ++i) {
				let name = ___OBJECT_12[i - 1];
				if (name === undefined) break;
				if (key !== name) {
					let type = __TypeMap[info.type_list[i - 1]];
					let value = map[name];
					if (type === 1) {
						if (value !== true) {
							query.Int = 0;
						} else {
							query.Int = 1;
						}
					} else if (type === 2) {
						if (value !== undefined) {
							query.Int = lua.tonumber(value);
						} else {
							query.Int = 0;
						}
					} else if (type === 3) {
						if (value !== undefined) {
							query.Long = lua.tonumber(value);
						} else {
							query.Long = 0;
						}
					} else if (type === 4) {
						if (value !== undefined) {
							query.Double = lua.tonumber(value);
						} else {
							query.Double = 0;
						}
					} else if (type === 5) {
						if (value !== undefined) {
							query.String = lua.tostring(value);
						} else {
							query.String = "";
						}
					} else {
						if (value !== undefined) {
							query.String = lua.ajson.encode(value);
						} else {
							query.String = "";
						}
					}
				}
			}
			query.value = key_value;
			___COROUTINE(await this.ExecuteStatement(query, thread_id)); return;
			___COROUTINE();
		}).bind(this));
	},
	UpdateOne : function(T, value, key, key_value, thread_id) {
		return new Promise((async function(___COROUTINE, ___) {
			___COROUTINE(await this.UpdateOneByReflect(T, value, key, key_value, thread_id)); return;
			___COROUTINE();
		}).bind(this));
	},
	UpdateSetByReflect : function(info, field, field_value, key, key_value, thread_id) {
		return new Promise((async function(___COROUTINE, ___) {
			if (field_value === undefined) {
				___COROUTINE("field_value == null"); return;
			}
			if (key_value === undefined) {
				___COROUTINE("key_value == null"); return;
			}
			let sql = "UPDATE `";
			sql = sql + info.rl_name;
			sql = sql + "` SET `";
			sql = sql + field;
			sql = sql + "`=?";
			sql = sql + " WHERE `";
			sql = sql + key;
			sql = sql + "`=?";
			let query = ALittle.NewObject(ALittle.MysqlStatementQuery);
			query.sql = sql;
			query.value = field_value;
			query.value = key_value;
			___COROUTINE(await this.ExecuteStatement(query, thread_id)); return;
			___COROUTINE();
		}).bind(this));
	},
	UpdateSet : function(T, field, field_value, key, key_value, thread_id) {
		return new Promise((async function(___COROUTINE, ___) {
			___COROUTINE(await this.UpdateSetByReflect(T, field, field_value, key, key_value, thread_id)); return;
			___COROUTINE();
		}).bind(this));
	},
	DeleteFromByMapByReflect : function(info, value_map, thread_id) {
		return new Promise((async function(___COROUTINE, ___) {
			let sql = "DELETE FROM `";
			sql = sql + info.rl_name;
			sql = sql + "`";
			let condition = "";
			let value_list = [];
			if (value_map !== undefined) {
				let where_list = [];
				let index = 1;
				let ___OBJECT_13 = value_map;
				for (let key in ___OBJECT_13) {
					let value = ___OBJECT_13[key];
					if (value === undefined) continue;
					where_list[index - 1] = "`" + key + "`=?";
					value_list[index - 1] = value;
				}
				condition = ALittle.String_Join(where_list, " AND ");
				if (condition !== "") {
					condition = " WHERE " + condition;
				}
			}
			sql = sql + condition;
			let query = ALittle.NewObject(ALittle.MysqlStatementQuery);
			query.sql = sql;
			let ___OBJECT_14 = value_list;
			for (let index = 1; index <= ___OBJECT_14.length; ++index) {
				let value = ___OBJECT_14[index - 1];
				if (value === undefined) break;
				query.value = value;
			}
			___COROUTINE(await this.ExecuteStatement(query, thread_id)); return;
			___COROUTINE();
		}).bind(this));
	},
	DeleteFromByMap : function(T, value_map, thread_id) {
		return new Promise((async function(___COROUTINE, ___) {
			___COROUTINE(await this.DeleteFromByMapByReflect(T, value_map, thread_id)); return;
			___COROUTINE();
		}).bind(this));
	},
	DeleteFromByKeyByReflect : function(info, key, value, thread_id) {
		return new Promise((async function(___COROUTINE, ___) {
			let sql = "DELETE FROM `";
			sql = sql + info.rl_name;
			sql = sql + "` WHERE `";
			sql = sql + key;
			sql = sql + "`=?";
			let query = ALittle.NewObject(ALittle.MysqlStatementQuery);
			query.sql = sql;
			query.value = value;
			___COROUTINE(await this.ExecuteStatement(query, thread_id)); return;
			___COROUTINE();
		}).bind(this));
	},
	DeleteFromByKey : function(T, key, value, thread_id) {
		return new Promise((async function(___COROUTINE, ___) {
			___COROUTINE(await this.DeleteFromByKeyByReflect(T, key, value, thread_id)); return;
			___COROUTINE();
		}).bind(this));
	},
	CreateIfNotExitByReflect : function(info, table_name, thread_id) {
		return new Promise((async function(___COROUTINE, ___) {
			let name_map = {};
			let ___OBJECT_15 = info.name_list;
			for (let index = 1; index <= ___OBJECT_15.length; ++index) {
				let name = ___OBJECT_15[index - 1];
				if (name === undefined) break;
				name_map[name] = true;
			}
			let primary = info.option_map["primary"];
			if (primary !== undefined && name_map[primary] === undefined) {
				primary = ALittle.String_Trim(primary);
				if (name_map[primary] === undefined) {
					___COROUTINE("指定的主键" + primary + "不是字段"); return;
				}
			}
			let unique_map = {};
			let unique = info.option_map["unique"];
			if (unique !== undefined) {
				let list = ALittle.String_Split(unique, ",");
				let ___OBJECT_16 = list;
				for (let index = 1; index <= ___OBJECT_16.length; ++index) {
					let value = ___OBJECT_16[index - 1];
					if (value === undefined) break;
					value = ALittle.String_Trim(value);
					unique_map[value] = true;
					if (name_map[value] === undefined) {
						___COROUTINE("指定的唯一索引" + value + "不是字段"); return;
					}
				}
			}
			let index_map = {};
			let index = info.option_map["index"];
			if (index !== undefined) {
				let list = ALittle.String_Split(index, ",");
				let ___OBJECT_17 = list;
				for (let i = 1; i <= ___OBJECT_17.length; ++i) {
					let value = ___OBJECT_17[i - 1];
					if (value === undefined) break;
					value = ALittle.String_Trim(value);
					index_map[value] = true;
					if (name_map[value] === undefined) {
						___COROUTINE("指定的索引" + value + "不是字段"); return;
					}
				}
			}
			let sql = "CREATE TABLE IF NOT EXISTS `";
			if (table_name === undefined) {
				sql = sql + info.rl_name;
			} else {
				sql = sql + table_name;
			}
			sql = sql + "` (";
			let sql_list = [];
			let ___OBJECT_18 = info.name_list;
			for (let i = 1; i <= ___OBJECT_18.length; ++i) {
				let name = ___OBJECT_18[i - 1];
				if (name === undefined) break;
				let type = __TypeMap[info.type_list[i - 1]];
				if (type === 1) {
					ALittle.List_Push(sql_list, "`" + name + "` tinyint(4) NOT NULL DEFAULT 0");
				} else if (type === 2) {
					ALittle.List_Push(sql_list, "`" + name + "` int(11) NOT NULL DEFAULT 0");
				} else if (type === 3) {
					ALittle.List_Push(sql_list, "`" + name + "` bigint(20) NOT NULL DEFAULT 0");
				} else if (type === 4) {
					ALittle.List_Push(sql_list, "`" + name + "` double NOT NULL DEFAULT 0");
				} else if (type === 5) {
					ALittle.List_Push(sql_list, "`" + name + "` varchar(250) NOT NULL DEFAULT ''");
				} else {
					ALittle.List_Push(sql_list, "`" + name + "` text");
				}
			}
			sql = sql + ALittle.String_Join(sql_list, ",");
			if (primary !== undefined) {
				sql = sql + ", PRIMARY KEY (`" + primary + "`)";
			}
			let ___OBJECT_19 = unique_map;
			for (let name in ___OBJECT_19) {
				let _ = ___OBJECT_19[name];
				if (_ === undefined) continue;
				sql = sql + ", UNIQUE KEY `" + name + "` (`" + name + "`)";
			}
			let ___OBJECT_20 = index_map;
			for (let name in ___OBJECT_20) {
				let _ = ___OBJECT_20[name];
				if (_ === undefined) continue;
				sql = sql + ", KEY `" + name + "` (`" + name + "`)";
			}
			sql = sql + ") DEFAULT CHARSET=utf8mb4";
			___COROUTINE(await this.ExecuteNormal(sql, thread_id)); return;
			___COROUTINE();
		}).bind(this));
	},
	CreateIfNotExit : function(T, table_name, thread_id) {
		return new Promise((async function(___COROUTINE, ___) {
			___COROUTINE(await this.CreateIfNotExitByReflect(T, table_name, thread_id)); return;
			___COROUTINE();
		}).bind(this));
	},
}, "ALittle.MysqlSystem");

window.A_MysqlSystem = ALittle.NewObject(ALittle.MysqlSystem);
}