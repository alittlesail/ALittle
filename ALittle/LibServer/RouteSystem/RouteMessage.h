
#ifndef _ALITTLE_ROUTEMESSAGE_H_
#define _ALITTLE_ROUTEMESSAGE_H_

#include "ALittle/LibCommon/Protocol/Message.h"
#include "RouteIdDefine.h"

namespace ALittle
{

enum
{
	_QSearchRouteInfo			= 200,
	_ASearchRouteInfo			= 201,
	_QConnectRouteInfo			= 202,
	_AConnectRouteInfo			= 203,
	_ConnectRouteDisconnected	= 204,
	_ConnectRouteMessageRead	= 205,
	_ConnectRouteMessageWrite	= 205,
};

// 请求搜索路径
MESSAGE_MACRO(QSearchRouteInfo
	, std::list<ROUTE_ID>, route_path);
	
// 应答搜索路径
MESSAGE_MACRO(ASearchRouteInfo
	, std::list<ROUTE_ID>, route_id_list);
	
// 请求连接路径
MESSAGE_MACRO(QConnectRouteInfo
	, int, connect_index
	, std::vector<ROUTE_ID>, route_path);
	
// 应答连接成功
MESSAGE_MACRO(AConnectRouteInfo);

// 路径连接断开了
MESSAGE_MACRO(ConnectRouteDisconnected
	, CONNECT_KEY, connect_key);

// 路由机制上的消息包，用于读取
MESSAGE_MACRO(ConnectRouteMessageRead
    , CONNECT_KEY, connect_key
    , int, message_id
	, int, message_rpcid
    , int, message_size);

// 路由机制上的消息包，用于写
MESSAGE_MACRO(ConnectRouteMessageWrite
	, CONNECT_KEY, connect_key
	, int, message_id
	, int, message_rpcid
	, MessagePtrWaper<Message>, message_body);

} // ALittle

#endif // _ALITTLE_ROUTEMESSAGE_H_
