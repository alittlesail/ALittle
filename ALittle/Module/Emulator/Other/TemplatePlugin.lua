
-- 1. 以下定义的函数，全部由客户端模拟器来调用
-- 2. 定制相关的业务逻辑，都在模板函数中编写
-- 3. 函数中已经有范例，可以根据范例来编写自己的定制
-- 4. 尾部有模拟器提供的接口可以使用

-- proto文件被重新加载刷新时被调用
function __PLUGIN_ProtoRefresh()
end

-- 开始执行登陆流程【在协程内被调用，这个函数内可以使用带await的函数】
-- param ip[string] 目标IP
-- param port[int] 目标端口
-- param login_msg[protobuf_message] 登陆消息包
-- return error[string] 如果执行错误，那么就返回错误原因，否则返回
-- return socket[Emulator.PluginSocket] 日志登陆执行成功，返回socket对象
function __PLUGIN_StartLogin(ip, port, login_msg)
	--[[ 这个是范例
	-- 创建一个socket
	local socket = Emulator.PluginSocket()
	-- 开始连接
	local error = socket:Connect(ip, port)
	if (error ~= nil) then return error, nil end
	-- 发送登陆包
	socket:SendMessage(login_msg)
	-- 读取登陆结果包
	local error, rsp = socket:ReadStruct()
	-- 根据rsp里面的内容来判断是否成
	if rsp.ret_code ~= nil and rsp.ret_code ~= 0 then
		return "login faeild, ret_code:"..rsp.ret_code, nil
	else
		return nil, socket
	end
	--]]
	return "not implement", nil
end

-- 根据项目的消息结构来读取一个消息包【在协程内被调用，这个函数内可以使用带await的函数】
-- param socket[Emulator.PluginSocket] 消息对象
-- return error[string] 如果读取错误，那么就返回错误原因，如果正确那么就返回null
-- return protobuf_msg[protobuf_message] 如果读取正确，返回protobuf消息对象
function __SOCKET_ReadMessage(socket)
	--[[ 这个是范例
	-- 读取full_name的长度
	local error, full_name_len = socket:ReadUint16()
	if (error ~= nil) then return error, nil end
	-- 读取fulle_name
	local error, full_name = socket:ReadString(full_name_len)
	if (error ~= nil) then return error, nil end
	-- 读取protof长度
	local error, protobuf_len = socket:ReadUint16()
	if (error ~= nil) then return error, nil end
	-- 读取protobuf_msg
	return socket:ReadProtobuf(full_name, protobuf_len)
	--]]
	return "not implement", nil
end

-- 根据项目的消息结构来发送一个消息包。当UI界面选中某个消息并发送时，会调用这个函数
-- param socket[Emulator.PluginSocket] socket对象
-- param full_name[string] protobuf消息全称
-- param protobuf_msg[protobuf_message] protobuf消息对象
-- return error[string] 如果发送失败，就返回失败原因，否则返回null
function __SOCKET_WriteMessage(socket, full_name, protobuf_msg)
	--[[ 这个是范例
	-- 发送full_name的长度
	socket:WriteUint16(#full_name)
	-- 发送消息的全称
	socket:WriteBinary(full_name, #full_name)
	-- 获取消息大小
	local protobuf_size = protobuf.message_getbytesize(protobuf_msg)
	-- 发送消息包大小
	socket:WriteUint16(protobuf_size)
	-- 发送消息包
	return socket:WriteProtobuf(protobuf_msg)
	--]]
	return "not implement"
end

-- 当服务器向客户端发送消息时，客户端收到了消息就会调用这个函数
-- param socket[Emulator.PluginSocket] socket对象
-- param protobuf_msg[protobuf_message] protobuf的消息对象
function __SOCKET_HandleMessage(socket, protobuf_msg)
	--[[ 这个是范例
	-- 获取描述信息
	local descriptor = protobuf.message_getdescriptor(protobuf_msg)
	-- 获取消息名称
	local full_name = protobuf.messagedescriptor_fullname(descriptor)
	-- 如果是心跳请求包，那么就发送一个应答包
	if full_name == "Package.MSG_KEEP_LIVE_REQ" then
		socket:SendStruct("Package.MSG_KEEP_LIVE_RSP", {})
		return
	end
	--]]
end

--[[ 框架提供的接口
接口文档说明
类：表示对象是某种类型
单例：全局某种类型的唯一对象
fun：成员函数，调用时请使用lua的语法糖':'
static：静态函数，可以直接调用
await：表示必须在协程函数中调用

类   LuaSocketSchedule
单例  A_LuaSocketSchedule
成员函数
    // 根据枚举的全称获取枚举描述对象
    public fun GetEnumDescriptor(string full_name) : protobuf_enum_descriptor
    // 根据消息的全称获取枚举描述对象
    public fun GetMessageDescriptor(string full_name) : protobuf_descriptor

类       Emulator.PluginSocket
创建一个实例：local socket = Emulator.PluginSocket()
成员函数
	// 连接服务器
	// return error[string] 如果连接失败，那么表示错误信息，否则为null
	public await fun Connect() : string
	// 关闭连接
	public fun Close()
	// 读取一个消息包，并且把消息转为lua的table
	// return error[string] 如果读取失败，那么表示错误信息，否则为null
	// return table[any] 如果读取成功表示返回的table
	public await fun ReadStruct() : string, any
	// 读取一个基本变量类型
	// return error[string] 如果读取失败，那么表示错误信息，否则为null
	// return value 如果读取成功表示返回的数
	public await fun ReadUint8() : string, int
	public await fun ReadInt8() : string, int
	public await fun ReadUint16() : string, int
	public await fun ReadInt16() : string, int
	public await fun ReadUint32() : string, int
	public await fun ReadInt32() : string, int
	public await fun ReadUint64() : string, int
	public await fun ReadInt64() : string, int
	public await fun ReadFloat() : string, double
	public await fun ReadDouble() : string, int
	public await fun ReadString() : string, string
	// 读取二进制数据
	// param len[int] 表示要指定读取的数据字节数量
	// return error[string] 如果读取失败，那么表示错误信息，否则为null
	// param buffer[any] 如果读取成功，那么buffer就是存放在数据的缓冲区
	public await fun ReadBinary(int len) : string, any
	// 读取一个protobuf消息对象
	// param full_name[string] 表示protobuf的消息全称
	// param len[int] 表示要指定读取的数据字节数量
	// param protobuf_msg[protobuf_message] 表示protobuf的消息对象
	public await fun ReadProtobuf(string full_name, int len) : string, protobuf_msg

	// 发送一个基本变量类型
	public fun WriteUint8(int value)
	public fun WriteInt8(int value)
	public fun WriteUint16(int value)
	public fun WriteInt16(int value)
	public fun WriteUint32(int value)
	public fun WriteInt32(int value)
	public fun WriteUint64(int value)
	public fun WriteInt64(int value)
	public fun WriteFloat(double value)
	public fun WriteDouble(double value)
	public fun WriteString(string value)
    // 发送一个二进制缓冲区
	public fun WriteBinary(memory buffer, int size)


	// 发送一个逻辑消息包，内部会触发__SOCKET_WriteMessage来组包
    // return error[string] 如果发送失败，那么返回失败原因，否则返回null
    public fun SendMessage(protobuf_message msg) : string
	// 发送一个lua的table，内部会把table转为full_name对应的消息包发送出去
    // param full_name[string] 表示要发送的protobuf消息全称
    // param table[any] 消息内容
    // return error[string] 如果发送失败，那么返回失败原因，否则返回null
    public fun SendStruct(string full_name, any table) : string

memory 模块下的函数
public static create(int size) : memory {}
public static free(memory m) {}

json 模块下的函数
public static encode(any table) : string {}
public static decode(string value) : any {}

protobuf 模块下的函数

public static filedescriptor_messagetypecount(protobuf_file_descriptor descriptor) : int {}
public static filedescriptor_messagetype(protobuf_file_descriptor descriptor, int index) : protobuf_descriptor {}
public static filedescriptor_enumtypecount(protobuf_file_descriptor descriptor) : int {}
public static filedescriptor_enumtype(protobuf_file_descriptor descriptor, int index) : protobuf_enum_descriptor {}

public static messagedescriptor_name(protobuf_descriptor descriptor) : string {}
public static messagedescriptor_fullname(protobuf_descriptor descriptor) : string {}
public static messagedescriptor_fieldcount(protobuf_descriptor descriptor) : int {}
public static messagedescriptor_field(protobuf_descriptor descriptor, int index) : protobuf_field_descriptor {}
public static messagedescriptor_findfieldbyname(protobuf_descriptor descriptor, string name) : protobuf_field_descriptor {}
public static messagedescriptor_findfieldbynumber(protobuf_descriptor descriptor, int number) : protobuf_field_descriptor {}

public static enumdescriptor_name(protobuf_enum_descriptor descriptor) : string {}
public static enumdescriptor_fullname(protobuf_enum_descriptor descriptor) : string {}
public static enumdescriptor_valuecount(protobuf_enum_descriptor descriptor) : int {}
public static enumdescriptor_value(protobuf_enum_descriptor descriptor, int index) : protobuf_enum_value_descriptor {}
public static enumdescriptor_findvaluebyname(protobuf_enum_descriptor descriptor, string name) : protobuf_enum_value_descriptor {}
public static enumdescriptor_findvaluebynumber(protobuf_enum_descriptor descriptor, int number) : protobuf_enum_value_descriptor {}
    
public static enumvaluedescriptor_name(protobuf_enum_value_descriptor descriptor) : string {}
public static enumvaluedescriptor_number(protobuf_enum_value_descriptor descriptor) : int {}

public static fielddescriptor_cpptype(protobuf_field_descriptor descriptor) : int {}
public static fielddescriptor_name(protobuf_field_descriptor descriptor) : string {}
public static fielddescriptor_cpptypename(protobuf_field_descriptor descriptor) : string {}
public static fielddescriptor_ismap(protobuf_field_descriptor descriptor) : bool {}
public static fielddescriptor_isrepeated(protobuf_field_descriptor descriptor) : bool {}
public static fielddescriptor_messagetype(protobuf_field_descriptor descriptor) : protobuf_descriptor {}
public static fielddescriptor_enumtype(protobuf_field_descriptor descriptor) : protobuf_enum_descriptor {}

public static createfactory() : protobuf_factory {}
public static createmessage(protobuf_factory factory, protobuf_descriptor descriptor) : protobuf_message {}
public static clonemessage(protobuf_message msg) : protobuf_message {}

public static message_getdescriptor(protobuf_message msg) : protobuf_descriptor {}
public static message_getreflection(protobuf_message msg) : protobuf_reflection {}
public static message_getbytesize(protobuf_message msg) : int {}
public static message_serializetoarray(protobuf_message msg, any buffer, int size) : bool {}
public static message_parsefromarray(protobuf_message msg, any buffer, int size) : bool {}
public static message_jsonencode(protobuf_message msg) : string {}
public static message_jsondecode(protobuf_message msg, string json) : string {}

public static reflection_clearfield(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor) {}

public static reflection_getmessage(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor) : protobuf_message {}
public static reflection_getbool(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor) : bool {}
public static reflection_getint32(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor) : int {}
public static reflection_getuint32(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor) : int {}
public static reflection_getint64(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor) : long {}
public static reflection_getuint64(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor) : long {}
public static reflection_getdouble(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor) : double {}
public static reflection_getfloat(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor) : double {}
public static reflection_getenumvalue(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor) : int {}
public static reflection_getstring(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor) : string {}
    
public static reflection_setmessage(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, protobuf_message value) {}
public static reflection_setbool(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, bool value) {}
public static reflection_setint32(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int value) {}
public static reflection_setuint32(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int value) {}
public static reflection_setint64(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, long value) {}
public static reflection_setuint64(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, long value) {}
public static reflection_setdouble(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, double value) {}
public static reflection_setfloat(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, double value) {}
public static reflection_setenumvalue(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int value) {}
public static reflection_setstring(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, string value) {}
    
public static reflection_getrepeatedmessagecount(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor) : int {}
public static reflection_getrepeatedboolcount(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor) : int {}
public static reflection_getrepeatedint32count(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor) : int {}
public static reflection_getrepeateduint32count(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor) : int {}
public static reflection_getrepeatedint64count(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor) : int {}
public static reflection_getrepeateduint64count(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor) : int {}
public static reflection_getrepeateddoublecount(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor) : int {}
public static reflection_getrepeatedfloatcount(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor) : int {}
public static reflection_getrepeatedstringcount(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor) : int {}

public static reflection_getrepeatedmessage(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index) : protobuf_message {}
public static reflection_getrepeatedbool(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index) : bool {}
public static reflection_getrepeatedint32(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index) : int {}
public static reflection_getrepeateduint32(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index) : int {}
public static reflection_getrepeatedint64(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index) : long {}
public static reflection_getrepeateduint64(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index) : long {}
public static reflection_getrepeateddouble(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index) : double {}
public static reflection_getrepeatedfloat(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index) : double {}
public static reflection_getrepeatedstring(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index) : string {}
    
public static reflection_setrepeatedbool(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index, bool value) {}
public static reflection_setrepeatedint32(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index, int value) {}
public static reflection_setrepeateduint32(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index, int value) {}
public static reflection_setrepeatedint64(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index, long value) {}
public static reflection_setrepeateduint64(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index, long value) {}
public static reflection_setrepeateddouble(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index, double value) {}
public static reflection_setrepeatedfloat(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index, double value) {}
public static reflection_setrepeatedstring(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index, string value) {}
    
public static reflection_insertrepeatedmessage(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index) : protobuf_message {}
public static reflection_insertrepeatedbool(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index, bool value) {}
public static reflection_insertrepeatedint32(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index, int value) {}
public static reflection_insertrepeateduint32(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index, int value) {}
public static reflection_insertrepeatedint64(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index, long value) {}
public static reflection_insertrepeateduint64(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index, long value) {}
public static reflection_insertrepeateddouble(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index, double value) {}
public static reflection_insertrepeatedfloat(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index, double value) {}
public static reflection_insertrepeatedstring(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index, string value) {}
    
public static reflection_removerepeatedmessage(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index) {}
public static reflection_removerepeatedbool(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index) {}
public static reflection_removerepeatedint32(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index) {}
public static reflection_removerepeateduint32(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index) {}
public static reflection_removerepeatedint64(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index) {}
public static reflection_removerepeateduint64(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index) {}
public static reflection_removerepeateddouble(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index) {}
public static reflection_removerepeatedfloat(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index) {}
public static reflection_removerepeatedstring(protobuf_reflection reflection, protobuf_message message, protobuf_field_descriptor descriptor, int index) {}
--]]