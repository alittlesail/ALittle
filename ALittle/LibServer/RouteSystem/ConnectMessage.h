
#ifndef _ALITTLE_CONNECTMESSAGE_H_
#define _ALITTLE_CONNECTMESSAGE_H_

#include "ALittle/LibCommon/Protocol/Message.h"
#include "RouteIdDefine.h"

namespace ALittle
{

enum
{
	_QConnectRegister			= 100,
	_AConnectRegister			= 101,
	_QConnect2ConnectRPCRead	= 102,
	_QConnect2ConnectRPCWrite	= 102,
	_AConnect2ConnectRPCRead	= 103,
	_AConnect2ConnectRPCWrite	= 103,
};

// 向连接目标注册自己，告诉目标我是谁
MESSAGE_MACRO(QConnectRegister
	, ROUTE_ID, route_id);

// 向请求方注册自己，告诉请求方我是谁
MESSAGE_MACRO(AConnectRegister
	, ROUTE_ID, route_id);

// 请求点对点RPC

// 这个协议用于读取
MESSAGE_MACRO(QConnect2ConnectRPCRead
    , int, message_id
    , int, message_size);
// 这个协议用于发送
MESSAGE_MACRO(QConnect2ConnectRPCWrite
	, int, message_id
	, MessagePtrWaper<Message>, message_body);


// 应答点对点RPC

// 这个协议用于读取
MESSAGE_MACRO(AConnect2ConnectRPCRead
	, int, message_id
	, int, message_size);

// 这个协议用于发送
MESSAGE_MACRO(AConnect2ConnectRPCWrite
	, int, message_id
	, MessagePtrWaper<Message>, message_body);

} // ALittle

#endif // _ALITTLE_CONNECTMESSAGE_H_
