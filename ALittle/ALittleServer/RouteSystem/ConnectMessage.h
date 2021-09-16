
#ifndef _ALITTLE_CONNECTMESSAGE_H_
#define _ALITTLE_CONNECTMESSAGE_H_

#include "Carp/carp_message.hpp"
#include "RouteIdDefine.h"

namespace ALittle
{

// 向连接目标注册自己，告诉目标我是谁
CARP_MESSAGE_MACRO(QConnectRegister, 100
	, ROUTE_ID, route_id);

// 向请求方注册自己，告诉请求方我是谁
CARP_MESSAGE_MACRO(AConnectRegister, 101
	, ROUTE_ID, route_id, std::string, error);

// 请求点对点RPC

// QConnect2ConnectRPCRead 和 QConnect2ConnectRPCWrite 其实是同一个消息
// 一个用来读的，一个用来写的

// 这个协议用于读取
CARP_MESSAGE_MACRO(QConnect2ConnectRPCRead, 102
    , int, message_id
    , int, message_size);
// 这个协议用于发送
CARP_MESSAGE_MACRO(QConnect2ConnectRPCWrite, 102
	, int, message_id
	, CarpMessagePtrWapper<CarpMessage>, message_body);


// 应答点对点RPC

// AConnect2ConnectRPCRead 和 AConnect2ConnectRPCWrite 其实是同一个消息
// 一个用来读的，一个用来写的

// 这个协议用于读取
CARP_MESSAGE_MACRO(AConnect2ConnectRPCRead, 103
	, int, message_id
	, int, message_size);

// 这个协议用于发送
CARP_MESSAGE_MACRO(AConnect2ConnectRPCWrite, 103
	, int, message_id
	, CarpMessagePtrWapper<CarpMessage>, message_body);

} // ALittle

#endif // _ALITTLE_CONNECTMESSAGE_H_
