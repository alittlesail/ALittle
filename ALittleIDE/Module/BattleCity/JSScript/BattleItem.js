{
if (typeof BattleCity === "undefined") window.BattleCity = {};


if (ALittle.FramePlay === undefined) throw new Error(" extends class:ALittle.FramePlay is undefined");
BattleCity.BattleItem = JavaScript.Class(ALittle.FramePlay, {
	get sprite() {
		return this._sprite;
	},
}, "BattleCity.BattleItem");

}