
#ifndef _ALITTLE_MESSAGERECEIVER_H_
#define _ALITTLE_MESSAGERECEIVER_H_

#include <SDL.h>
#include "ALittle/LibClient/Helper/NetHelper.h"
#include "ALittle/LibCommon/Protocol/Message.h"

namespace ALittle
{

class NetSystem;

class MessageReceiver
{
public:
	MessageReceiver(NetSystem* net_system, TCPsocket socket);
	~MessageReceiver();

public:
	/** 
	 * receive bytes from socket
	 * return if failed then retuen false
	 */
	bool Run();

public:
	/** 
	 * clear
	 */
	void Clear();

private:
	/** 
	 * receive completed
	 */
	void ReadComplete();

private:
	NetSystem* m_net_system;
	TCPsocket m_socket;		// TCP socket

private:
	// if true is receiving head, otherwise receiveing body
	bool m_receive_head;

	// message head buffer
	char m_message_head[PROTOCOL_HEAD_SIZE];
	// message body buffer
	void* m_memory;

	// current message size
	MESSAGE_SIZE* m_message_size;
	// current message id
	MESSAGE_ID* m_message_id;
    // current message rpc id
    MESSAGE_RPCID* m_message_rpc_id;
};

} // ALittle

#endif // _ALITTLE_MESSAGERECEIVER_H_