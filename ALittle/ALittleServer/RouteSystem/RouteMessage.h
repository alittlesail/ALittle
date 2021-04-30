
#ifndef _ALITTLE_ROUTEMESSAGE_H_
#define _ALITTLE_ROUTEMESSAGE_H_

#include "Carp/carp_message.hpp"
#include "RouteIdDefine.h"

namespace ALittle
{

// 请求搜索路径
CARP_MESSAGE_MACRO(QSearchRouteInfo, 200
	, std::list<ROUTE_ID>, route_path);
	
// 应答搜索路径
CARP_MESSAGE_MACRO(ASearchRouteInfo, 201
	, std::list<ROUTE_ID>, route_id_list);
	
// 请求连接路径
CARP_MESSAGE_MACRO(QConnectRouteInfo, 202
	, int, connect_index
	, std::vector<ROUTE_ID>, route_path);
	
// 应答连接成功
CARP_MESSAGE_MACRO(AConnectRouteInfo, 203);

// 路径连接断开了
CARP_MESSAGE_MACRO(ConnectRouteDisconnected, 204
	, CONNECT_KEY, connect_key);


// 注意 ConnectRouteMessageWrite 和 ConnectRouteMessageRead 消息ID 故意定成一样的
// 他们是同一个消息，一个用来写，一个同来读

// 路由机制上的消息包，用于读取
CARP_MESSAGE_MACRO(ConnectRouteMessageRead, 205
    , CONNECT_KEY, connect_key
    , int, message_id
	, int, message_rpcid
    , int, message_size);

// 路由机制上的消息包，用于写
CARP_MESSAGE_MACRO(ConnectRouteMessageWrite, 205
	, CONNECT_KEY, connect_key
	, int, message_id
	, int, message_rpcid
	, CarpMessagePtrWapper<CarpMessage>, message_body);

} // ALittle

#endif // _ALITTLE_ROUTEMESSAGE_H_
