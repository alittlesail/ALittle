
#ifndef _ALITTLE_CONNECTMESSAGE_H_
#define _ALITTLE_CONNECTMESSAGE_H_

#include "Carp/carp_message.hpp"
#include "RouteIdDefine.h"

namespace ALittle
{

// ������Ŀ��ע���Լ�������Ŀ������˭
CARP_MESSAGE_MACRO(QConnectRegister, 100
	, ROUTE_ID, route_id);

// ������ע���Լ���������������˭
CARP_MESSAGE_MACRO(AConnectRegister, 101
	, ROUTE_ID, route_id, std::string, error);

// �����Ե�RPC

// QConnect2ConnectRPCRead �� QConnect2ConnectRPCWrite ��ʵ��ͬһ����Ϣ
// һ���������ģ�һ������д��

// ���Э�����ڶ�ȡ
CARP_MESSAGE_MACRO(QConnect2ConnectRPCRead, 102
    , int, message_id
    , int, message_size);
// ���Э�����ڷ���
CARP_MESSAGE_MACRO(QConnect2ConnectRPCWrite, 102
	, int, message_id
	, CarpMessagePtrWapper<CarpMessage>, message_body);


// Ӧ���Ե�RPC

// AConnect2ConnectRPCRead �� AConnect2ConnectRPCWrite ��ʵ��ͬһ����Ϣ
// һ���������ģ�һ������д��

// ���Э�����ڶ�ȡ
CARP_MESSAGE_MACRO(AConnect2ConnectRPCRead, 103
	, int, message_id
	, int, message_size);

// ���Э�����ڷ���
CARP_MESSAGE_MACRO(AConnect2ConnectRPCWrite, 103
	, int, message_id
	, CarpMessagePtrWapper<CarpMessage>, message_body);

} // ALittle

#endif // _ALITTLE_CONNECTMESSAGE_H_
