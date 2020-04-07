{
if (typeof JavaScript === "undefined") JavaScript = {};


JavaScript.JNetBuffer = JavaScript.Class(undefined, {
	Ctor : function(init_size) {
		this._msize = 0;
		this._dstart = 0;
		this._dsize = 0;
		let data = new ArrayBuffer(init_size);
		this._memory = new DataView(data);
	},
	Add : function(array_buffer) {
		let data_view = new DataView(array_buffer);
		this.Resize(data_view.byteLength);
		for (let i = 0; i < data_view.byteLength; i += 1) {
			this._memory.setUint8(this._dstart + this._dsize, data_view.getUint8(i));
			++ this._dsize;
		}
	},
	Read : function() {
		if (this._dsize < 12) {
			return undefined;
		}
		if (this._dsize >= 4) {
			this._msize = this._memory.getInt32(this._dstart, true);
		}
		if (this._dsize - 12 >= this._msize) {
			let data = new DataView(this._memory.buffer, this._dstart, this._msize + 12);
			this._dstart = this._dstart + (this._msize + 12);
			this._dsize = this._dsize - (this._msize + 12);
			return data;
		}
		return undefined;
	},
	Optimizes : function() {
		if (this._dstart < 100) {
			return;
		}
		let start = this._dstart;
		let end = this._dstart + this._dsize;
		for (let i = start; i < end; i += 1) {
			this._memory.setUint8(i - this._dsize, this._memory.getUint8(i));
		}
		this._dstart = 0;
	},
	Resize : function(add_size) {
		let need_size = this._dstart + this._dsize + add_size;
		if (need_size <= this._memory.byteLength) {
			return;
		}
		let new_data = undefined;
		if (this._memory.byteLength * 2 < need_size) {
			new_data = new ArrayBuffer(need_size);
		} else {
			new_data = new ArrayBuffer(this._memory.byteLength * 2);
		}
		let new_memory = new DataView(new_data);
		for (let i = 0; i < this._memory.byteLength; i += 1) {
			new_memory.setUint8(i, this._memory.getUint8(i));
		}
		this._memory = new_memory;
	},
}, "JavaScript.JNetBuffer");

JavaScript.JConnectStatus = {
	NET_IDLE : 0,
	NET_CONNECTING : 1,
	NET_CONNECTED : 2,
}

if (ALittle.IMsgCommonNative === undefined) throw new Error(" extends class:ALittle.IMsgCommonNative is undefined");
JavaScript.JMsgInterface = JavaScript.Class(ALittle.IMsgCommonNative, {
	Ctor : function() {
		this._net_status = JavaScript.JConnectStatus.NET_IDLE;
		this._ip = "";
		this._port = 0;
		this._net_buffer = ALittle.NewObject(JavaScript.JNetBuffer, 2048);
	},
	SetID : function(id) {
	},
	GetID : function() {
		return 0;
	},
	Connect : function(ip, port) {
		if (this._net_status === JavaScript.JConnectStatus.NET_CONNECTED) {
			this.Close();
		}
		if (this._net_status === JavaScript.JConnectStatus.NET_CONNECTING) {
			ALittle.Warn("net system already connecting:" + this._ip + ":" + this._port);
			return;
		}
		let url = "ws://" + ip + ":" + port;
		this._net_status = JavaScript.JConnectStatus.NET_CONNECTING;
		this._net_system = new WebSocket(url);
		this._net_system.binaryType = "arraybuffer";
		this._net_system.onmessage = this.HandleNetSystemMessage.bind(this);
		this._net_system.onopen = this.HandleNetSystemOpen.bind(this);
		this._net_system.onclose = this.HandleNetSystemClose.bind(this);
		this._net_system.onerror = this.HandleNetSystemError.bind(this);
	},
	IsConnected : function() {
		return false;
	},
	SendFactory : function(factory) {
	},
	Close : function() {
		if (this._net_status === JavaScript.JConnectStatus.NET_IDLE) {
			return;
		}
		this._net_system.close();
		this._net_system = undefined;
		this._net_status = JavaScript.JConnectStatus.NET_IDLE;
	},
	HandleNetSystemOpen : function(event) {
		if (this._net_status !== JavaScript.JConnectStatus.NET_CONNECTING) {
			return;
		}
		this._net_status = JavaScript.JConnectStatus.NET_CONNECTED;
		if (this._conn_succeed !== undefined) {
			this._conn_succeed(this);
		}
	},
	HandleNetSystemClose : function(event) {
		if (this._net_status !== JavaScript.JConnectStatus.NET_CONNECTED) {
			return;
		}
		this._net_status = JavaScript.JConnectStatus.NET_IDLE;
		this._net_system = undefined;
		if (this._disconnected !== undefined) {
			this._disconnected(this);
		}
	},
	HandleNetSystemError : function(event) {
		if (this._net_status !== JavaScript.JConnectStatus.NET_CONNECTING) {
			return;
		}
		this._net_status = JavaScript.JConnectStatus.NET_IDLE;
		this._net_system = undefined;
		if (this._conn_failed !== undefined) {
			this._conn_failed(this);
		}
	},
	HandleNetSystemMessage : function(event) {
		if (event.data === undefined) {
			return;
		}
		this._net_buffer.Add(event.data);
		while (true) {
			let data = this._net_buffer.Read();
			if (data === undefined) {
				break;
			}
			let factory = ALittle.NewObject(JavaScript.JMessageReadFactory, data);
			let size = factory.ReadInt();
			let id = factory.ReadInt();
			let rpc_id = factory.ReadInt();
			factory.SetID(id);
			factory.SetRpcID(rpc_id);
			if (this._message !== undefined) {
				this._message(id, rpc_id, factory, this);
			}
		}
		this._net_buffer.Optimizes();
	},
}, "JavaScript.JMsgInterface");

}