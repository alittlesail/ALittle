
#ifndef _ALITTLE_NETSYSTEM_H_
#define _ALITTLE_NETSYSTEM_H_

#include "ALittle/LibClient/ThreadSystem/Task.h"

#include "ALittle/LibClient/Helper/NetHelper.h"

#include <vector>
#include <string>

#include "SendThread.h"
#include "ReceiveThread.h"

#include "ALittle/LibCommon/Protocol/Message.h"
#include "ALittle/LibCommon/Protocol/MessageReadFactory.h"
#include "ALittle/LibCommon/Protocol/MessageWriteFactory.h"

namespace ALittle
{

class ScriptSystem;

class NetSystem : public Task
{
public:
	NetSystem();
	~NetSystem();

public:
	int m_netsystem_filter_push;
	int m_netsystem_filter_handle;

public:
	static void Setup();
	static void Shutdown();
	static void RegisterToScript(ScriptSystem& script_system);

public:
	enum ConnectState
	{
		CONNECT_IDLE,			// idle
		CONNECT_ED,				// connected
		CONNECT_ING				// connecting
	};

	void Execute();
	void Abandon();
	
	int GetID() const;

public:
	/**
	 * connect 
	 * @param ip ip or domain
	 * @param port port
	 */
	void Connect(const char* ip, unsigned int port);
	/**
	 * close
	 */
	void Close();
	
	/**
	 * check is connected
	 * @return connect or not
	 */
	bool IsConnected() const { return m_state == CONNECT_ED; }

public:
	// handle message function template
	typedef void (*MessageHandle)(const Message& msg);
	/**
	 * register callback to handle message
	 * @param msg: message object
	 * @param func: callback
	 */
	void RegisterHandle(Message* msg, MessageHandle func);

public:
	/**
	 * handle connect event
	 * @param event_type
	 * @param data1 NetSystem object
	 * @param data2 TCPSocket object
	 */
	static void HandleConnectEvent(unsigned int event_type, void* data1, void* data2);
	
	/**
	 * handle message event
	 * @param data1 NetSystem object
	 * @param data2 message data
	 */
	static void HandleMessageEvent(unsigned int event_type, void* data1, void* data2);

public:
	/**
	 * send message
	 * @param message
	 */
	void Send(const Message& message);
	
	/**
	 * send message factory
	 * @param message
	 */
	void SendFactory(const MessageWriteFactory* message);
	
private:
	TCPsocket m_socket;	// TCP socket

private:	
	SendThread* m_send_thread;			// sender thread
	ReceiveThread* m_receive_thread;	// receive thread

private:
	ConnectState m_state;		// connect status
	bool m_in_cancel;			// is in cancel
	std::string m_ip;			// ip
	unsigned int m_port;		// port

private:
	typedef std::vector<MessageHandle> HandleList;
	HandleList m_handle_list;	// handle list
	
	typedef std::vector<Message*> MessageList;
	MessageList m_message_list;	// message list

	MessageReadFactory m_read_factory;	// read factory
};

} // ALittle

#endif // _ALITTLE_NETSYSTEM_H_