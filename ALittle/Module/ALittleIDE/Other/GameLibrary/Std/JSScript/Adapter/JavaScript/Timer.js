{
if (typeof JavaScript === "undefined") window.JavaScript = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1961635951, "JavaScript.MiniHeapNodeInfo", {
name : "JavaScript.MiniHeapNodeInfo", ns_name : "JavaScript", rl_name : "MiniHeapNodeInfo", hash_code : 1961635951,
name_list : ["heap_index","end_time"],
type_list : ["int","int"],
option_map : {}
})
ALittle.RegStruct(979480799, "JavaScript.TimerInfo", {
name : "JavaScript.TimerInfo", ns_name : "JavaScript", rl_name : "TimerInfo", hash_code : 979480799,
name_list : ["heap_index","end_time","id","loop","interval_ms"],
type_list : ["int","int","int","int","int"],
option_map : {}
})

let Math_Floor = Math.floor;
JavaScript.MiniHeap = JavaScript.Class(undefined, {
	Ctor : function() {
		this._nodes = [];
		this._size = 0;
		this._capacity = 0;
	},
	get size() {
		return this._size;
	},
	get empty() {
		return this._size === 0;
	},
	GetTop : function() {
		if (this._size === 0) {
			return undefined;
		}
		return this._nodes[0 /*因为使用了Native修饰，下标从0开始，不做减1处理*/];
	},
	Push : function(node) {
		if (this._capacity < this._size + 1) {
			this._capacity = this._capacity + (1);
			this._nodes[this._capacity /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = undefined;
		}
		this.ShiftUp(this._size, node);
		++ this._size;
		return true;
	},
	Pop : function() {
		if (this._size === 0) {
			return undefined;
		}
		let node = this._nodes[0 /*因为使用了Native修饰，下标从0开始，不做减1处理*/];
		this.ShiftDown(0, this._nodes[this._size - 1 /*因为使用了Native修饰，下标从0开始，不做减1处理*/]);
		this._size = this._size - (1);
		node.heap_index = -1;
		return node;
	},
	Adjust : function(node) {
		if (node.heap_index === -1) {
			return this.Push(node);
		}
		if (node.heap_index > 0 && this._nodes[Math_Floor((node.heap_index - 1) / 2) /*因为使用了Native修饰，下标从0开始，不做减1处理*/].end_time > node.end_time) {
			this.ShiftUpUnconditional(node.heap_index, node);
		} else {
			this.ShiftDown(node.heap_index, node);
		}
		return true;
	},
	Erase : function(node) {
		if (node.heap_index < 0) {
			return false;
		}
		let last = this._nodes[this._size - 1 /*因为使用了Native修饰，下标从0开始，不做减1处理*/];
		this._size = this._size - (1);
		if (node.heap_index > 0 && this._nodes[Math_Floor((node.heap_index - 1) / 2) /*因为使用了Native修饰，下标从0开始，不做减1处理*/].end_time > last.end_time) {
			this.ShiftUpUnconditional(node.heap_index, last);
		} else {
			this.ShiftDown(node.heap_index, last);
		}
		node.heap_index = -1;
		return true;
	},
	ShiftUp : function(index, node) {
		let parent = Math_Floor((index - 1) / 2);
		while (index > 0 && this._nodes[parent /*因为使用了Native修饰，下标从0开始，不做减1处理*/].end_time > node.end_time) {
			this._nodes[index /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = this._nodes[parent /*因为使用了Native修饰，下标从0开始，不做减1处理*/];
			this._nodes[index /*因为使用了Native修饰，下标从0开始，不做减1处理*/].heap_index = index;
			index = parent;
			parent = Math_Floor((index - 1) / 2);
		}
		this._nodes[index /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = node;
		node.heap_index = index;
	},
	ShiftUpUnconditional : function(index, node) {
		let parent = Math_Floor((index - 1) / 2);
		do {
			this._nodes[index /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = this._nodes[parent /*因为使用了Native修饰，下标从0开始，不做减1处理*/];
			this._nodes[index /*因为使用了Native修饰，下标从0开始，不做减1处理*/].heap_index = index;
			index = parent;
			parent = Math_Floor((index - 1) / 2);
		} while (index > 0 && this._nodes[parent /*因为使用了Native修饰，下标从0开始，不做减1处理*/].end_time > node.end_time);
		this._nodes[index /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = node;
		node.heap_index = index;
	},
	ShiftDown : function(index, node) {
		let min_child = 2 * (index + 1);
		while (min_child <= this._size) {
			if (min_child === this._size || this._nodes[min_child /*因为使用了Native修饰，下标从0开始，不做减1处理*/].end_time > this._nodes[min_child - 1 /*因为使用了Native修饰，下标从0开始，不做减1处理*/].end_time) {
				min_child = min_child - (1);
			}
			if (!(node.end_time > this._nodes[min_child /*因为使用了Native修饰，下标从0开始，不做减1处理*/].end_time)) {
				break;
			}
			this._nodes[index /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = this._nodes[min_child /*因为使用了Native修饰，下标从0开始，不做减1处理*/];
			this._nodes[index /*因为使用了Native修饰，下标从0开始，不做减1处理*/].heap_index = index;
			index = min_child;
			min_child = 2 * (index + 1);
		}
		this._nodes[index /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = node;
		node.heap_index = index;
	},
}, "JavaScript.MiniHeap");

if (ALittle.IHeapTimer === undefined) throw new Error(" extends class:ALittle.IHeapTimer is undefined");
JavaScript.JHeapTimer = JavaScript.Class(ALittle.IHeapTimer, {
	Ctor : function() {
		this._max_id = 0;
		this._cur_time = 0;
		this._heap = ALittle.NewObject(JavaScript.Template(JavaScript.MiniHeap, "JavaScript.MiniHeap<JavaScript.TimerInfo>", ___all_struct.get(979480799)));
		this._map = new Map();
		this._pool = [];
		this._pool_count = 0;
	},
	Create : function() {
		if (this._pool_count === 0) {
			return {};
		}
		let info = this._pool[this._pool_count - 1];
		this._pool[this._pool_count - 1] = undefined;
		this._pool_count = this._pool_count - (1);
		return info;
	},
	Release : function(info) {
		if (this._pool_count >= 1000) {
			return;
		}
		this._pool_count = this._pool_count + (1);
		this._pool[this._pool_count - 1] = info;
	},
	Add : function(delay_ms, loop, interval_ms) {
		let info = this.Create();
		info.heap_index = -1;
		if (delay_ms < 0) {
			delay_ms = 0;
		}
		info.end_time = this._cur_time + delay_ms;
		if (loop <= 0) {
			info.loop = -1;
		} else {
			info.loop = loop;
		}
		info.interval_ms = interval_ms;
		if (info.interval_ms <= 0) {
			info.interval_ms = 1;
		}
		let find_count = 1000000;
		while (find_count > 0) {
			this._max_id = this._max_id + (1);
			if (this._max_id === 0x7FFFFFFF) {
				this._max_id = 1;
			}
			if (this._map.get(this._max_id) === undefined) {
				info.id = this._max_id;
				break;
			}
			-- find_count;
		}
		if (!this._heap.Push(info)) {
			this.Release(info);
			return 0;
		}
		this._map.set(info.id, info);
		return info.id;
	},
	Remove : function(id) {
		let info = this._map.get(id);
		if (info === undefined) {
			return false;
		}
		this._heap.Erase(info);
		this.Release(info);
		this._map.delete(id);
		return true;
	},
	Update : function(frame_ms) {
		this._cur_time = this._cur_time + (frame_ms);
	},
	Poll : function() {
		let info = this._heap.GetTop();
		if (info === undefined) {
			return 0;
		}
		if (info.end_time > this._cur_time) {
			return 0;
		}
		this._heap.Pop();
		if (info.loop < 0) {
			info.end_time = info.end_time + info.interval_ms;
			this._heap.Push(info);
			return info.id;
		}
		if (info.loop > 1) {
			-- info.loop;
			info.end_time = info.end_time + info.interval_ms;
			this._heap.Push(info);
			return info.id;
		}
		this._map.delete(info.id);
		this.Release(info);
		return -info.id;
	},
}, "JavaScript.JHeapTimer");

}