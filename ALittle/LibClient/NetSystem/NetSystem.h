
#ifndef _ALITTLE_NETSYSTEM_H_
#define _ALITTLE_NETSYSTEM_H_

#include <vector>
#include <string>

#include "Carp/carp_connect_client.hpp"
#include "Carp/carp_message.hpp"

namespace ALittle
{

class ScriptSystem;

class NetSystem
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

private:
	void HandleConnectFailed();
	void HandleConnectSucceed();
	void HandleDisconnected();
	void HandleMessage(void* message, int size);

public:
	/**
	 * send message
	 * @param message
	 */
	void Send(const CarpMessage& message);
	
	/**
	 * send message factory
	 * @param message
	 */
	void SendFactory(const CarpMessageWriteFactory* message);
	
private:
	ConnectState m_state;		// connect status
	std::string m_ip;			// ip
	unsigned int m_port;		// port

private:
	CarpMessageReadFactory m_read_factory;	// read factory
	CarpConnectClientPtr m_client;
};

} // ALittle

#endif // _ALITTLE_NETSYSTEM_H_