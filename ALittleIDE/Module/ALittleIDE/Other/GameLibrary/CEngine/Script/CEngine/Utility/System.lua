-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___pairs = pairs
local ___ipairs = ipairs


function ALittle.System_CalcPortrait(src_width, src_height, flag)
	local scale = 1.0
	local platform = ALittle.System_GetPlatform()
	if platform == "iOS" or platform == "Android" then
		local screen_width = ALittle.System_GetScreenWidth()
		local screen_height = ALittle.System_GetScreenHeight()
		src_height = ALittle.Math_Floor(screen_height / screen_width * src_width)
		flag = flag | 0x00000001
	elseif platform == "Web" then
		if flag & 0x00000020 > 0 then
			src_width = ALittle.System_GetScreenWidth()
			src_height = ALittle.System_GetScreenHeight()
		else
			scale = ALittle.System_GetScreenHeight() / src_height
		end
	elseif platform == "WeChat" then
		local screen_width = ALittle.System_GetScreenWidth()
		local screen_height = ALittle.System_GetScreenHeight()
		src_height = ALittle.Math_Floor(screen_height / screen_width * src_width)
		scale = screen_width / src_width
	elseif platform == "Windows" then
		if src_height > ALittle.System_GetScreenHeight() then
			scale = 0.5
		end
	end
	return src_width, src_height, flag, scale
end

function ALittle.System_CalcLandscape(src_width, src_height, flag)
	local scale = 1.0
	local platform = ALittle.System_GetPlatform()
	if platform == "iOS" or platform == "Android" then
		local screen_width = ALittle.System_GetScreenWidth()
		local screen_height = ALittle.System_GetScreenHeight()
		src_width = ALittle.Math_Floor(screen_width / screen_height * src_height)
		flag = flag | 0x00000001
	elseif platform == "Web" then
		if flag & 0x00000020 > 0 then
			src_width = ALittle.System_GetScreenWidth()
			src_height = ALittle.System_GetScreenHeight()
		else
			scale = ALittle.System_GetScreenWidth() / src_width
		end
	elseif platform == "WeChat" then
		local screen_width = ALittle.System_GetScreenWidth()
		local screen_height = ALittle.System_GetScreenHeight()
		src_width = ALittle.Math_Floor(screen_width / screen_height * src_height)
		scale = screen_height / src_height
	elseif platform == "Windows" then
		if src_width > ALittle.System_GetScreenWidth() then
			scale = 0.5
		end
	end
	return src_width, src_height, flag, scale
end

function ALittle.System_GetPlatform()
	return __CPPAPI_System:GetPlatform()
end

function ALittle.System_SetFPS(fps)
	__CPPAPI_ScheduleSystem:SetFPS(fps)
end

function ALittle.System_GetCurMSTime()
	return __CPPAPI_System:GetCurMSTime()
end

function ALittle.System_GetDeviceID()
	return __CPPAPI_System:GetDeviceID()
end

function ALittle.System_IsPhone()
	local platform = __CPPAPI_System:GetPlatform()
	return platform ~= "Windows" and platform ~= "Emscripten"
end

function ALittle.System_InstallProgram(file_path)
	__CPPAPI_System:InstallProgram(file_path)
end

function ALittle.System_GetScreenWidth()
	return __CPPAPI_System:GetScreenWidth()
end

function ALittle.System_GetScreenHeight()
	return __CPPAPI_System:GetScreenHeight()
end

function ALittle.System_ForceExit()
	__CPPAPI_ScheduleSystem:ForceExit()
end

function ALittle.System_Exit()
	__CPPAPI_ScheduleSystem:Exit()
end

function ALittle.System_Restart()
	__CPPAPI_ScheduleSystem:Restart()
end

function ALittle.System_SetThreadCount(count)
	carp.SetThreadCount(count)
end

function ALittle.System_GetThreadCount(thread_type)
	return carp.GetThreadCount()
end

function ALittle.System_GetIMESelectList()
	return __CPPAPI_InputSystem:GetIMESelectList()
end

function ALittle.System_SetIMEPos(x, y)
	__CPPAPI_InputSystem:SetIMEPos(x, y)
end

function ALittle.System_SetIMERect(x, y, w, h)
	__CPPAPI_InputSystem:SetIMERect(x, y, w, h)
end

function ALittle.System_OpenIME()
	__CPPAPI_InputSystem:OpenIME()
end

function ALittle.System_CloseIME()
	__CPPAPI_InputSystem:CloseIME()
end

function ALittle.System_GetCursorX()
	return __CPPAPI_InputSystem:GetCursorX()
end

function ALittle.System_GetCursorY()
	return __CPPAPI_InputSystem:GetCursorY()
end

function ALittle.System_SetEditCursor()
	__CPPAPI_InputSystem:SetEditCursor()
end

function ALittle.System_SetNormalCursor()
	__CPPAPI_InputSystem:SetNormalCursor()
end

function ALittle.System_SetHandCursor()
	__CPPAPI_InputSystem:SetHandCursor()
end

function ALittle.System_SetHDragCursor()
	__CPPAPI_InputSystem:SetHDragCursor()
end

function ALittle.System_SetVDragCursor()
	__CPPAPI_InputSystem:SetVDragCursor()
end

function ALittle.System_SetHVDragCursor()
	__CPPAPI_InputSystem:SetHVDragCursor()
end

function ALittle.System_SetHV2DragCursor()
	__CPPAPI_InputSystem:SetHV2DragCursor()
	if not ALittle.System_IsPhone() then
	end
end

function ALittle.System_SetCrossDragCursor()
	__CPPAPI_InputSystem:SetCrossDragCursor()
	if not ALittle.System_IsPhone() then
	end
end

function ALittle.System_CreateView(title, width, height, flag, scale)
	return __CPPAPI_RenderSystem:CreateView(title, width, height, flag, scale)
end

function ALittle.System_SetViewTitle(title)
	return __CPPAPI_RenderSystem:SetViewTitle(title)
end

function ALittle.System_SetViewIcon(path)
	return __CPPAPI_RenderSystem:SetViewIcon(path)
end

function ALittle.System_SetViewSize(width, height)
	__CPPAPI_RenderSystem:SetViewSize(width, height)
end

function ALittle.System_ShowView()
	__CPPAPI_RenderSystem:ShowView()
end

function ALittle.System_HideView()
	__CPPAPI_RenderSystem:HideView()
end

function ALittle.System_GetMaxTextureWidth()
	return __CPPAPI_RenderSystem:GetMaxTextureWidth()
end

function ALittle.System_GetMaxTextureHeight()
	return __CPPAPI_RenderSystem:GetMaxTextureHeight()
end

function ALittle.System_Render()
	__CPPAPI_RenderSystem:Render()
end

function ALittle.System_GetClipboardText()
	return __CPPAPI_InputSystem:GetClipboardText()
end

function ALittle.System_SetClipboardText(content)
	__CPPAPI_InputSystem:SetClipboardText(content)
end

function ALittle.System_HasClipboardText()
	return __CPPAPI_InputSystem:HasClipboardText()
end

function ALittle.System_OpenUrlBySystemBrowser(url)
	__CPPAPI_System:OpenUrlBySystemBrowser(url)
end

function ALittle.CreateMsgSender(heartbeat, check_heartbeat, callback, rudp)
	if rudp then
		return Lua.Template(ALittle.MsgSenderTemplate, "ALittle.MsgSenderTemplate<lua.__CPPAPIUMsgInterface, carp.CarpMessageWriteFactory>", __CPPAPIUMsgInterface, carp.CarpMessageWriteFactory)(heartbeat, true, A_LuaLoopSystem, callback)
	else
		return Lua.Template(ALittle.MsgSenderTemplate, "ALittle.MsgSenderTemplate<lua.__CPPAPIMsgInterface, carp.CarpMessageWriteFactory>", __CPPAPIMsgInterface, carp.CarpMessageWriteFactory)(heartbeat, check_heartbeat, A_LuaLoopSystem, callback)
	end
end

function ALittle.CreateHttpSender(ip, port)
	return Lua.Template(ALittle.HttpSenderTemplate, "ALittle.HttpSenderTemplate<lua.__CPPAPIHttpInterface>", __CPPAPIHttpInterface)(ip, port)
end

function ALittle.HttpRequest(ip, port, method)
	local ___COROUTINE = coroutine.running()
	local sender = ALittle.CreateHttpSender(ip, port)
	if ___COROUTINE == nil then
		return "当前不是协程", nil
	end
	sender:SendRPC(___COROUTINE, method, nil)
	return coroutine.yield()
end

function ALittle.CreateHttpFileSender(ip, port, file_path, start_size, callback)
	return Lua.Template(ALittle.HttpFileSenderTemplate, "ALittle.HttpFileSenderTemplate<lua.__CPPAPIHttpFileInterface>", __CPPAPIHttpFileInterface)(ip, port, file_path, start_size, callback)
end

function ALittle.HttpDownloadRequest(ip, port, file_path, method, callback, array_buffer)
	local ___COROUTINE = coroutine.running()
	local sender = ALittle.CreateHttpFileSender(ip, port, file_path, 0, callback)
	if ___COROUTINE == nil then
		return "当前不是协程"
	end
	sender:SendDownloadRPC(___COROUTINE, method, nil, array_buffer)
	return coroutine.yield()
end

end