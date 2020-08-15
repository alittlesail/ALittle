{
if (typeof Lua === "undefined") window.Lua = {};


if (ALittle.IHeapTimer === undefined) throw new Error(" extends class:ALittle.IHeapTimer is undefined");
Lua.LuaHeapTimer = JavaScript.Class(ALittle.IHeapTimer, {
	Ctor : function() {
		this._timer = lua.timer.create();
	},
	Add : function(delay_ms, loop, interval_ms) {
		return lua.timer.add(this._timer, delay_ms, loop, interval_ms);
	},
	Remove : function(id) {
		return lua.timer.remove(this._timer, id) !== 0;
	},
	Update : function(frame_ms) {
		lua.timer.update(this._timer, frame_ms);
	},
	Poll : function() {
		return lua.timer.poll(this._timer);
	},
}, "Lua.LuaHeapTimer");

}