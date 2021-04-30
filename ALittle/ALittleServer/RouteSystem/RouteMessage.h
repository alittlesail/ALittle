
#ifndef _ALITTLE_ROUTEMESSAGE_H_
#define _ALITTLE_ROUTEMESSAGE_H_

#include "Carp/carp_message.hpp"
#include "RouteIdDefine.h"

namespace ALittle
{

// ��������·��
CARP_MESSAGE_MACRO(QSearchRouteInfo, 200
	, std::list<ROUTE_ID>, route_path);
	
// Ӧ������·��
CARP_MESSAGE_MACRO(ASearchRouteInfo, 201
	, std::list<ROUTE_ID>, route_id_list);
	
// ��������·��
CARP_MESSAGE_MACRO(QConnectRouteInfo, 202
	, int, connect_index
	, std::vector<ROUTE_ID>, route_path);
	
// Ӧ�����ӳɹ�
CARP_MESSAGE_MACRO(AConnectRouteInfo, 203);

// ·�����ӶϿ���
CARP_MESSAGE_MACRO(ConnectRouteDisconnected, 204
	, CONNECT_KEY, connect_key);


// ע�� ConnectRouteMessageWrite �� ConnectRouteMessageRead ��ϢID ���ⶨ��һ����
// ������ͬһ����Ϣ��һ������д��һ��ͬ����

// ·�ɻ����ϵ���Ϣ�������ڶ�ȡ
CARP_MESSAGE_MACRO(ConnectRouteMessageRead, 205
    , CONNECT_KEY, connect_key
    , int, message_id
	, int, message_rpcid
    , int, message_size);

// ·�ɻ����ϵ���Ϣ��������д
CARP_MESSAGE_MACRO(ConnectRouteMessageWrite, 205
	, CONNECT_KEY, connect_key
	, int, message_id
	, int, message_rpcid
	, CarpMessagePtrWapper<CarpMessage>, message_body);

} // ALittle

#endif // _ALITTLE_ROUTEMESSAGE_H_
