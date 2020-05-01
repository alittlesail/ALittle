-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

RegStruct(-1864322361, "ALittle.LoginSessionInfo", {
name = "ALittle.LoginSessionInfo", ns_name = "ALittle", rl_name = "LoginSessionInfo", hash_code = -1864322361,
name_list = {"account_id","session","timer"},
type_list = {"int","string","int"},
option_map = {}
})
RegStruct(-1922773679, "ALittle.DATA2GS_QSaveSession", {
name = "ALittle.DATA2GS_QSaveSession", ns_name = "ALittle", rl_name = "DATA2GS_QSaveSession", hash_code = -1922773679,
name_list = {"account_id","session"},
type_list = {"int","string"},
option_map = {}
})
RegStruct(-963859571, "ALittle.GS2DATA_ASaveSession", {
name = "ALittle.GS2DATA_ASaveSession", ns_name = "ALittle", rl_name = "GS2DATA_ASaveSession", hash_code = -963859571,
name_list = {},
type_list = {},
option_map = {}
})

GameLoginManager = Lua.Class(nil, "ALittle.GameLoginManager")

function GameLoginManager:Ctor()
	___rawset(self, "_session_map", {})
end

function GameLoginManager:Setup()
end

function GameLoginManager:Shutdown()
	for account_id, info in ___pairs(self._session_map) do
		if info.timer ~= nil then
			A_LoopSystem:RemoveTimer(info.timer)
		end
	end
	self._session_map = {}
end

function GameLoginManager:ChcekSession(account_id, session)
	local info = self._session_map[account_id]
	if info == nil then
		return false
	end
	return info.session == session
end

function GameLoginManager:RemoveSession(account_id)
	local info = self._session_map[account_id]
	if info == nil then
		return
	end
	if info.timer ~= nil then
		A_LoopSystem:RemoveTimer(info.timer)
	end
	self._session_map[account_id] = nil
end

function GameLoginManager:HandleQSaveSession(msg)
	local info = self._session_map[msg.account_id]
	if info ~= nil and info.timer ~= nil then
		A_LoopSystem:RemoveTimer(info.timer)
	end
	info = {}
	info.account_id = msg.account_id
	info.session = msg.session
	info.timer = A_LoopSystem:AddTimer(30 * 1000, Lua.Bind(self.HandleSessionTimeout, self, msg.account_id))
	self._session_map[msg.account_id] = info
end

function GameLoginManager:HandleSessionTimeout(account_id)
	self._session_map[account_id] = nil
end

g_GameLoginManager = GameLoginManager()
function HandleQSaveSession(client, msg)
local ___COROUTINE = coroutine.running()
	g_GameLoginManager:HandleQSaveSession(msg)
	return {}
end

RegMsgRpcCallback(-1922773679, HandleQSaveSession, -963859571)
