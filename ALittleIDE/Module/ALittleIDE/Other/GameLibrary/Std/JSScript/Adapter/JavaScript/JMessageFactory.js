{
if (typeof JavaScript === "undefined") window.JavaScript = {};


if (ALittle.IMessageWriteFactory === undefined) throw new Error(" extends class:ALittle.IMessageWriteFactory is undefined");
JavaScript.JMessageWriteFactory = JavaScript.Class(ALittle.IMessageWriteFactory, {
	Ctor : function(init_size) {
		this._size = 0;
		this._id = 0;
		this._rpc_id = 0;
		if (init_size === undefined || init_size <= 0) {
			init_size = 1024;
		}
		let data = new ArrayBuffer(init_size);
		this._memory = new DataView(data);
	},
	ResizeMemory : function(add_size) {
		if (this._memory.byteLength >= this._size + add_size) {
			return;
		}
		let new_data = new ArrayBuffer(this._memory.byteLength * 2);
		let new_memory = new DataView(new_data);
		for (let i = 0; i < this._memory.byteLength; i += 1) {
			new_memory.setUint8(i, this._memory.getUint8(i));
		}
		this._memory = new_memory;
	},
	SetID : function(id) {
		this._id = id;
	},
	SetRpcID : function(id) {
		this._rpc_id = id;
	},
	ResetOffset : function() {
		this._size = 0;
	},
	GetOffset : function() {
		return this._size;
	},
	SetInt : function(offset, value) {
		this._memory.setInt32(offset, value, true);
	},
	WriteBool : function(value) {
		this.ResizeMemory(1);
		if (value) {
			this._memory.setUint8(this._size, 1);
		} else {
			this._memory.setUint8(this._size, 0);
		}
		this._size = this._size + (1);
		return 1;
	},
	WriteInt : function(value) {
		this.ResizeMemory(4);
		this._memory.setInt32(this._size, value, true);
		this._size = this._size + (4);
		return 4;
	},
	WriteLong : function(value) {
		throw new Error("not suppert long");
	},
	WriteString : function(value) {
		this.ResizeMemory(value.length * 4 + 5);
		let old_size = this._size;
		this._size = this._size + (4);
		let new_data = StringToUTF8Array(value);
		let new_memory = new DataView(new_data.buffer);
		for (let i = 0; i < new_memory.byteLength; i += 1) {
			this._memory.setUint8(this._size, new_memory.getUint8(i));
			++ this._size;
		}
		let str_len = this._size - 4 - old_size;
		this._memory.setUint32(old_size, str_len + 1, true);
		this._memory.setUint8(this._size, 0);
		this._size = this._size + (1);
		return str_len + 4 + 1;
	},
	WriteDouble : function(value) {
		this.ResizeMemory(8);
		this._memory.setFloat64(this._size, value, true);
		this._size = this._size + (8);
		return 8;
	},
	GetArrayBuffer : function(head) {
		if (head) {
			let new_data = new ArrayBuffer(this._size + 12);
			let new_view = new DataView(new_data);
			new_view.setInt32(0, this._size, true);
			new_view.setInt32(4, this._id, true);
			new_view.setInt32(8, this._rpc_id, true);
			for (let i = 0; i < this._size; i += 1) {
				new_view.setUint8(12 + i, this._memory.getUint8(i));
			}
			return new_data;
		} else {
			let new_data = new ArrayBuffer(this._size);
			let new_view = new DataView(new_data);
			for (let i = 0; i < this._size; i += 1) {
				new_view.setUint8(i, this._memory.getUint8(i));
			}
			return new_data;
		}
	},
	WriteToStdFile : function(file_path) {
		let buffer = this.GetArrayBuffer(false);
		return JavaScript.File_SaveFile(file_path, undefined, buffer);
	},
}, "JavaScript.JMessageWriteFactory");

if (ALittle.IMessageReadFactory === undefined) throw new Error(" extends class:ALittle.IMessageReadFactory is undefined");
JavaScript.JMessageReadFactory = JavaScript.Class(ALittle.IMessageReadFactory, {
	Ctor : function(data, offset, head) {
		this._memory = data;
		this._offset = offset;
		this._total_size = data.byteLength;
		this._read_size = 0;
		if (head) {
			this._data_size = this.ReadInt();
			this._id = this.ReadInt();
			this._rpc_id = this.ReadInt();
		} else {
			this._data_size = data.byteLength;
			this._id = 0;
			this._rpc_id = 0;
		}
		this._last_read_size = 0;
	},
	GetID : function() {
		return this._id;
	},
	GetRpcID : function() {
		return this._rpc_id;
	},
	GetDataSize : function() {
		return this._data_size;
	},
	ReadBool : function() {
		if (this._read_size >= this._total_size || this._read_size < 0) {
			this._last_read_size = -1;
			ALittle.Error("id: " + this._id + " already read completed:" + this._total_size + ", " + this._read_size);
			return false;
		}
		let value = this._memory.getUint8(this._read_size);
		this._read_size = this._read_size + (1);
		this._last_read_size = 1;
		return value !== 0;
	},
	ReadInt : function() {
		if (this._read_size >= this._total_size || this._read_size < 0) {
			this._last_read_size = -1;
			ALittle.Error("id: " + this._id + " already read completed:" + this._total_size + ", " + this._read_size);
			return 0;
		}
		let value = this._memory.getInt32(this._read_size, true);
		this._read_size = this._read_size + (4);
		this._last_read_size = 4;
		return value;
	},
	ReadLong : function() {
		ALittle.Error("id: " + this._id + " not support long");
		return 0;
	},
	ReadString : function() {
		if (this._read_size >= this._total_size || this._read_size < 0) {
			this._last_read_size = -1;
			ALittle.Log("id:" + this._id + " already read completed:" + this._total_size + ", " + this._read_size);
			return "";
		}
		let len = this._memory.getInt32(this._read_size, true);
		if (len <= 0) {
			this._last_read_size = -1;
			ALittle.Error("id:" + this._id + " string len: " + len + " is error:" + this._total_size + ", " + this._read_size);
			return "";
		}
		this._read_size = this._read_size + (4);
		let value = "";
		if (len > 1) {
			value = UTF8ArrayToString(new Uint8Array(this._memory.buffer, this._offset + this._read_size, len - 1));
		}
		this._read_size = this._read_size + (len);
		this._last_read_size = len + 4;
		return value;
	},
	ReadDouble : function() {
		if (this._read_size >= this._total_size || this._read_size < 0) {
			this._last_read_size = -1;
			ALittle.Error("id: " + this._id + " already read completed:" + this._total_size + ", " + this._read_size);
			return 0;
		}
		let value = this._memory.getFloat64(this._read_size, true);
		this._read_size = this._read_size + (8);
		this._last_read_size = 8;
		return value;
	},
	GetReadSize : function() {
		return this._last_read_size;
	},
}, "JavaScript.JMessageReadFactory");

}