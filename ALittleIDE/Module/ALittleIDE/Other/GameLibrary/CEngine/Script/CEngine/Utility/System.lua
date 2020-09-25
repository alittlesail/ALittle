-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function ALittle.System_CalcPortrait(src_width, src_height, flag)
	local scale = 1.0
	local platform = ALittle.System_GetPlatform()
	if platform == "iOS" or platform == "Android" then
		local screen_width = ALittle.System_GetScreenWidth()
		local screen_height = ALittle.System_GetScreenHeight()
		src_height = ALittle.Math_Floor(screen_height / screen_width * src_width)
		flag = ALittle.BitOr(flag, ALittle.UIEnumTypes.VIEW_FULLSCREEN)
	elseif platform == "Web" then
		if ALittle.BitAnd(flag, ALittle.UIEnumTypes.VIEW_RESIZABLE) > 0 then
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
		flag = ALittle.BitOr(flag, ALittle.UIEnumTypes.VIEW_FULLSCREEN)
	elseif platform == "Web" then
		if ALittle.BitAnd(flag, ALittle.UIEnumTypes.VIEW_RESIZABLE) > 0 then
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
	return __CPPAPI_GetPlatform()
end

function ALittle.System_GetDeviceID()
	return __CPPAPI_GetDeviceID()
end

function ALittle.System_IsPhone()
	local platform = __CPPAPI_GetPlatform()
	return platform ~= "Windows" and platform ~= "Emscripten"
end

function ALittle.System_InstallProgram(file_path)
	__CPPAPI_InstallProgram(file_path)
end

function ALittle.System_StartProgram(package_name)
	__CPPAPI_StartProgram(package_name)
end

function ALittle.System_BackProgram()
	__CPPAPI_BackProgram()
end

function ALittle.System_GetScreenWidth()
	return __CPPAPI_GetScreenWidth()
end

function ALittle.System_GetScreenHeight()
	return __CPPAPI_GetScreenHeight()
end

function ALittle.System_GetStatusBarHeight()
	return __CPPAPI_GetStatusBarHeight()
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

function ALittle.System_SetFPS(fps)
	__CPPAPI_ScheduleSystem:SetFPS(fps)
end

function ALittle.System_SetAppPauseInterval(interval)
	__CPPAPI_ScheduleSystem:SetAppPauseInterval(interval)
end

function ALittle.System_GetAppPauseInterval()
	return __CPPAPI_ScheduleSystem:GetAppPauseInterval()
end

function ALittle.System_SetThreadCount(count)
	carp.SetThreadCount(count)
end

function ALittle.System_GetThreadCount(thread_type)
	return carp.GetThreadCount()
end

function ALittle.System_GetIMESelectList()
	return __CPPAPI_GetIMESelectList()
end

function ALittle.System_SetIMEPos(x, y)
	__CPPAPI_SetIMSPos(x, y)
end

function ALittle.System_SetIMERect(x, y, w, h)
	__CPPAPI_SetIMSRect(x, y, w, h)
end

function ALittle.System_OpenIME()
	__CPPAPI_OpenIME()
end

function ALittle.System_CloseIME()
	__CPPAPI_CloseIME()
end

function ALittle.System_GetCursorX()
	return __CPPAPI_GetCursorX()
end

function ALittle.System_GetCursorY()
	return __CPPAPI_GetCursorY()
end

function ALittle.System_SetEditCursor()
	__CPPAPI_SetEditCursor()
end

function ALittle.System_SetNormalCursor()
	__CPPAPI_SetNormalCursor()
end

function ALittle.System_SetHandCursor()
	__CPPAPI_SetHandCursor()
end

function ALittle.System_SetHDragCursor()
	__CPPAPI_SetHDragCursor()
end

function ALittle.System_SetVDragCursor()
	__CPPAPI_SetVDragCursor()
end

function ALittle.System_SetHVDragCursor()
	__CPPAPI_SetHVDragCursor()
end

function ALittle.System_SetHV2DragCursor()
	__CPPAPI_SetHV2DragCursor()
end

function ALittle.System_SetCrossDragCursor()
	__CPPAPI_SetCrossDragCursor()
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

function ALittle.System_SetViewShape(path)
	return __CPPAPI_RenderSystem:SetViewShape(path)
end

function ALittle.System_SetViewSize(width, height)
	__CPPAPI_RenderSystem:SetViewSize(width, height)
end

function ALittle.System_SetMaxViewSize()
	__CPPAPI_RenderSystem:SetMaxViewSize()
end

function ALittle.System_SetMinViewSize()
	__CPPAPI_RenderSystem:SetMinViewSize()
end

function ALittle.System_SetRestoreViewSize()
	__CPPAPI_RenderSystem:SetRestoreViewSize()
end

function ALittle.System_RaiseView()
	__CPPAPI_RenderSystem:RaiseView()
end

function ALittle.System_ShowView()
	__CPPAPI_RenderSystem:ShowView()
end

function ALittle.System_HideView()
	__CPPAPI_RenderSystem:HideView()
end

function ALittle.System_GetViewX()
	return __CPPAPI_RenderSystem:GetViewX()
end

function ALittle.System_GetViewY()
	return __CPPAPI_RenderSystem:GetViewY()
end

function ALittle.System_SetViewPosition(x, y)
	__CPPAPI_RenderSystem:SetViewPosition(x, y)
end

function ALittle.System_GetMaxTextureWidth()
	return __CPPAPI_RenderSystem:GetMaxTextureWidth()
end

function ALittle.System_GetMaxTextureHeight()
	return __CPPAPI_RenderSystem:GetMaxTextureHeight()
end

function ALittle.System_Render()
	return __CPPAPI_RenderSystem:Render()
end

function ALittle.System_GetClipboardText()
	return __CPPAPI_GetClipboardText()
end

function ALittle.System_SetClipboardText(content)
	__CPPAPI_SetClipboardText(content)
end

function ALittle.System_HasClipboardText()
	return __CPPAPI_HasClipboardText()
end

function ALittle.System_GetClipboardImage()
	return __CPPAPI_GetClipboardImage()
end

function ALittle.System_SetClipboardImage(surface)
	__CPPAPI_SetClipboardImage(surface)
end

function ALittle.System_HasClipboardImage()
	return __CPPAPI_HasClipboardImage()
end

ALittle.SystemOrientationType = {
	SDL_ORIENTATION_UNKNOWN = 0,
	SDL_ORIENTATION_LANDSCAPE = 1,
	SDL_ORIENTATION_LANDSCAPE_FLIPPED = 2,
	SDL_ORIENTATION_PORTRAIT = 3,
	SDL_ORIENTATION_PORTRAIT_FLIPPED = 4,
}

function ALittle.System_GetDisplayOrientation()
	return __CPPAPI_GetDisplayOrientation()
end

function ALittle.System_EnableScreenSaver()
	__CPPAPI_EnableScreenSaver()
end

function ALittle.System_DisableScreenSaver()
	__CPPAPI_DisableScreenSaver()
end

function ALittle.System_OpenUrlBySystemBrowser(url)
	__CPPAPI_OpenUrlBySystemBrowser(url)
end

function ALittle.System_Alert(msg)
	__CPPAPI_Alert(msg)
end

function ALittle.System_LoadSurface(path)
	return __CPPAPI_LoadSurface(path)
end

function ALittle.System_CreateSurface(width, height)
	return __CPPAPI_CreateSurface(width, height)
end

function ALittle.System_SaveSurface(surface, path)
	return __CPPAPI_SaveSurface(surface, path)
end

function ALittle.System_FreeSurface(surface)
	__CPPAPI_FreeSurface(surface)
end

function ALittle.System_GetSurfaceWidth(surface)
	return __CPPAPI_GetSurfaceWidth(surface)
end

function ALittle.System_GetSurfaceHeight(surface)
	return __CPPAPI_GetSurfaceHeight(surface)
end

function ALittle.System_CutBlitSurface(new_surface, surface, to, from)
	return __CPPAPI_CutBlitSurface(new_surface, surface, to, from)
end

function ALittle.System_SetSurfacePixel(surface, x, y, color)
	return __CPPAPI_SetSurfacePixel(surface, x, y, color)
end

function ALittle.System_GetSurfacePixel(surface, x, y)
	return __CPPAPI_GetSurfacePixel(surface, x, y)
end

function ALittle.System_GetPixelAlpha(color)
	return __CPPAPI_GetPixelAlpha(color)
end

function ALittle.System_SetPixelAlpha(color, alpha)
	return __CPPAPI_SetPixelAlpha(color, alpha)
end

function ALittle.System_GetSurfaceGrid9(surface, type)
	return __CPPAPI_GetSurfaceGrid9(surface, type)
end

function ALittle.CreateMsgSender(heartbeat, check_heartbeat, callback)
	return Lua.Template(ALittle.MsgSenderTemplate, "ALittle.MsgSenderTemplate<lua.__CPPAPIMsgInterface, carp.CarpMessageWriteFactory>", __CPPAPIMsgInterface, carp.CarpMessageWriteFactory)(heartbeat, check_heartbeat, A_LuaLoopSystem, callback)
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