#ifndef ALITTLE_NET_INCLUDED
#define ALITTLE_NET_INCLUDED (1)

#include <unordered_set>

#include "Carp/carp_http_client.hpp"
#include "Carp/carp_connect_client.hpp"
#include "Carp/carp_rudp_client.hpp"
#include "Carp/carp_schedule.hpp"
#include "Carp/carp_log.hpp"
#include "Carp/carp_task_consumer.hpp"

#include "alittle_script.hpp"

extern int s_alittle_net_id_creator;
extern std::unordered_set<int> s_alittle_net_id_set;

class ALittleHttpClient
{
public:
	ALittleHttpClient()
	{
		++s_alittle_net_id_creator;
		m_id = s_alittle_net_id_creator;
	}
	~ALittleHttpClient()
	{
		if (m_client) m_client->Stop();
	}

public:
	void SetURL(const char* url, const char* content)
	{
		if (m_client) { CARP_ERROR("socket already exist!"); return; }

		if (url) m_url = url;
		if (content) m_content = content;

		m_client = std::make_shared<CarpHttpClientText>();
	}

	void Start()
	{
		if (m_client)
		{
			int id = m_id;
			m_client->SendRequest(m_url, m_content.empty(), "application/json", m_content.c_str(), m_content.size()
				, [this, id](bool result, const std::string& body, const std::string& head, const std::string& error)
				{
					m_head = head;
					m_response = body;
					if (result)
						s_carp_event_consumer.PushEvent([id]() { s_alittle_script.Invoke("__ALITTLEAPI_HttpClientSucceed", id); });
					else
						s_carp_event_consumer.PushEvent([id, error]() { s_alittle_script.Invoke("__ALITTLEAPI_HttpClientFailed", id, error.c_str()); });
				}
			, nullptr, &s_carp_schedule.GetIOService(), "", 0, "");
		}
	}

	/**
	 * stop http
	 */
	void Stop() const
	{
		if (m_client) m_client->Stop();
	}

	const char* GetHead() const
	{
		return m_head.c_str();
	}

	const char* GetResponse() const
	{
		return m_response.c_str();
	}

	void GetContent(const char*& content, int& size) const
	{
		size = static_cast<int>(m_response.size());
		if (size <= 0)
		{
			content = 0;
			size = 0;
			return;
		}
		content = m_response.c_str();
	}

	const char* GetURL() const { return m_url.c_str(); }

	int GetID() const { return m_id; }

private:
	int m_id;
	std::string m_url;			// url
	std::string m_content;		// if content is empty, then GET. otherwise POST
	std::string m_response;		// response
	std::string m_head;

private:
	CarpHttpClientTextPtr m_client;
};

class ALittleHttpFile
{
public:
	ALittleHttpFile()
	{
		++s_alittle_net_id_creator;
		m_id = s_alittle_net_id_creator;
	}
	~ALittleHttpFile()
	{
		if (m_upload_client) m_upload_client->Stop();
		if (m_download_client) m_download_client->Stop();
	}

public:
	void SetURL(const char* url, const char* file_path, bool download, int start_size, bool array_buffer)
	{
		if (m_upload_client || m_download_client)
		{
			CARP_ERROR("socket already exist!");
			return;
		}

		m_url = url;
		m_file_path = file_path;
		m_download = download;
		m_start_size = start_size;

		if (download)
			m_download_client = std::make_shared<CarpHttpClientText>();
		else
			m_upload_client = std::make_shared<CarpHttpClientPost>();
	}

	int GetID() const { return m_id; }

public:
	void Start()
	{
		int id = m_id;
		if (m_download_client)
		{
			m_download_client->SendRequest(m_url, true, "", nullptr, 0
				, [this, id](bool result, const std::string& head, const std::string& body, const std::string& error)
				{
					if (result)
						s_carp_event_consumer.PushEvent([id]() { s_alittle_script.Invoke("__ALITTLEAPI_HttpFileSucceed", id); });
					else
						s_carp_event_consumer.PushEvent([id, error]() { s_alittle_script.Invoke("__ALITTLEAPI_HttpFileFailed", id, error.c_str()); });
				}
				, [this, id](int total_size, int cur_size)
				{
					m_total_size = total_size;
					m_cur_size = cur_size;
					s_carp_event_consumer.PushEvent([id, total_size, cur_size]() { s_alittle_script.Invoke("__ALITTLEAPI_HttpFileProcess", id, cur_size, total_size); });
				}, &s_carp_schedule.GetIOService(), m_file_path, m_start_size, "");
		}
		else if (m_upload_client)
		{
			m_upload_client->SendRequest(m_url
				, std::map<std::string, std::string>()
				, CarpFile::GetFileNameByPath(m_file_path), m_file_path, m_start_size
				, [this, id](bool result, const std::string& head, const std::string& body, const std::string& error)
				{
					if (result)
						s_carp_event_consumer.PushEvent([id]() { s_alittle_script.Invoke("__ALITTLEAPI_HttpFileSucceed", id); });
					else
						s_carp_event_consumer.PushEvent([id, error]() { s_alittle_script.Invoke("__ALITTLEAPI_HttpFileFailed", id, error.c_str()); });
				}
				, [this, id](int total_size, int cur_size)
				{
					m_total_size = total_size;
					m_cur_size = cur_size;
					s_carp_event_consumer.PushEvent([id, total_size, cur_size]() { s_alittle_script.Invoke("__ALITTLEAPI_HttpFileProcess", id, cur_size, total_size); });
				}, &s_carp_schedule.GetIOService(), "");
		}
	}

	void Stop() const
	{
		if (m_upload_client) m_upload_client->Stop();
		if (m_download_client) m_download_client->Stop();
	}

public:
	const char* GetPath() const { return m_file_path.c_str(); }
	unsigned int GetTotalSize() const { return m_total_size; }
	unsigned int GetCurSize() const { return m_cur_size; }

private:
	int m_id = 0;
	std::string m_url;				// uel
	std::string m_file_path;		// file path
	unsigned int m_total_size = 0;		// total file size
	unsigned int m_cur_size = 0;	// current size
	int m_start_size = 0;				// start size
	bool m_download = false;				// download or upload

private:
	CarpHttpClientPostPtr m_upload_client;
	CarpHttpClientTextPtr m_download_client;
};

class ALittleMsgClient
{
public:
	ALittleMsgClient()
	{
		++s_alittle_net_id_creator;
		m_id = s_alittle_net_id_creator;
		s_alittle_net_id_set.insert(m_id);
	}
	virtual ~ALittleMsgClient()
	{
		s_alittle_net_id_set.erase(m_id);
		Close();
	}

public:
	enum ConnectState
	{
		CONNECT_IDLE,			// idle
		CONNECT_ED,				// connected
		CONNECT_ING				// connecting
	};

	int GetID() const { return m_id; }

public:
	/**
	 * connect
	 * @param ip ip or domain
	 * @param port port
	 */
	virtual void Connect(const char* ip, unsigned int port)
	{
		// if current is connected then close first
		if (m_state == CONNECT_ED) Close();

		// if connecting then return
		if (m_state == CONNECT_ING)
		{
			CARP_WARN("net system already connecting:" << m_ip << ":" << m_port);
			return;
		}

		if (ip) m_ip = ip;
		m_port = port;

#ifdef __EMSCRIPTEN__
		s_alittle_script.Invoke("__ALITTLEAPI_ConnectFailed", this);
#else
		// flag to connecting
		m_state = CONNECT_ING;

		if (m_rudp)
		{
			m_rudp_client = std::make_shared<CarpRudpClient>();
			m_rudp_client->Connect(m_ip, m_port, &s_carp_schedule.GetIOService()
				, std::bind(&ALittleMsgClient::HandleConnectFailed, this)
				, std::bind(&ALittleMsgClient::HandleConnectSucceed, this)
				, std::bind(&ALittleMsgClient::HandleDisconnected, this)
				, std::bind(&ALittleMsgClient::HandleMessage, this, std::placeholders::_1, std::placeholders::_2));
		}
		else
		{
			m_connect_client = std::make_shared<CarpConnectClient>();
			m_connect_client->Connect(m_ip, m_port, &s_carp_schedule.GetIOService()
				, std::bind(&ALittleMsgClient::HandleConnectFailed, this)
				, std::bind(&ALittleMsgClient::HandleConnectSucceed, this)
				, std::bind(&ALittleMsgClient::HandleDisconnected, this)
				, std::bind(&ALittleMsgClient::HandleMessage, this, std::placeholders::_1, std::placeholders::_2));
		}
#endif
	}

	virtual void Close()
	{
		if (m_state == CONNECT_IDLE) return;
		if (m_connect_client)
			m_connect_client->Close();
		if (m_rudp_client)
			m_rudp_client->Close();

		// flag to idle
		m_state = CONNECT_IDLE;

		m_port = 0;
		m_ip = "";
	}

	virtual bool IsConnected() const { return m_state == CONNECT_ED; }

private:
	void HandleConnectFailed()
	{
		int id = m_id;
		s_carp_event_consumer.PushEvent([this, id]()
		{
			// 检查是否被析构了
			if (s_alittle_net_id_set.find(id) == s_alittle_net_id_set.end()) return;
			// set connected
			m_state = CONNECT_IDLE;
			m_port = 0;
			m_ip = "";
			m_connect_client = CarpConnectClientPtr();
			m_rudp_client = CarpRudpClientPtr();
			// notify script system
			s_alittle_script.Invoke("__ALITTLEAPI_ConnectFailed", id);
		});
	}

	void HandleConnectSucceed()
	{
		int id = m_id;
		s_carp_event_consumer.PushEvent([this, id]()
		{
			// 检查是否被析构了
			if (s_alittle_net_id_set.find(id) == s_alittle_net_id_set.end()) return;
			// set connected
			m_state = CONNECT_ED;
			// notify script system
			s_alittle_script.Invoke("__ALITTLEAPI_ConnectSucceed", id);
		});
	}
	
	void HandleDisconnected()
	{
		int id = m_id;
		s_carp_event_consumer.PushEvent([this, id]()
		{
			// 检查是否被析构了
			if (s_alittle_net_id_set.find(id) == s_alittle_net_id_set.end()) return;
			m_state = CONNECT_IDLE;
			m_port = 0;
			m_ip = "";
			m_connect_client = CarpConnectClientPtr();
			m_rudp_client = CarpRudpClientPtr();
			// notify script system
			s_alittle_script.Invoke("__ALITTLEAPI_Disconnected", id);
		});
	}
	
	void HandleMessage(void* message, int size)
	{
		int id = m_id;
		s_carp_event_consumer.PushEvent([this, id, message]()
		{
			// 检查是否被析构了
			if (s_alittle_net_id_set.find(id) != s_alittle_net_id_set.end())
			{
				m_read_factory.DeserializeFromTotalMessage(message);
				s_alittle_script.Invoke("__ALITTLEAPI_Message", id, m_read_factory.GetID(), m_read_factory.GetRpcID(), &m_read_factory);
			}
			
			// release memory
			free(message);
		});
	}

public:
	/**
	 * send message
	 * @param message
	 */
	virtual void Send(const CarpMessage& message) const
	{
		if (!m_connect_client && !m_rudp_client) return;

		int size = 0;
		void* memory = message.CreateMemoryForSend(&size);
		if (m_connect_client)
			m_connect_client->SendPocket(memory, size);
		else if (m_rudp_client)
			m_rudp_client->SendPocket(memory, size);
	}

	/**
	 * send message factory
	 * @param message
	 */
	virtual void SendFactory(const CarpMessageWriteFactory* message) const
	{
		if (!m_connect_client && !m_rudp_client) return;

		int size = 0;
		void* memory = message->CreateMemoryForSend(&size);
		if (m_connect_client)
			m_connect_client->SendPocket(memory, size);
		else if (m_rudp_client)
			m_rudp_client->SendPocket(memory, size);
	}

private:
	ConnectState m_state = CONNECT_IDLE;		// connect status
	std::string m_ip;			// ip
	unsigned int m_port = 0;		// port
	int m_id = 0;

private:
	CarpMessageReadFactory m_read_factory;	// read factory
	CarpConnectClientPtr m_connect_client;
	CarpRudpClientPtr m_rudp_client;

protected:
	bool m_rudp = false;
};

class ALittleUMsgClient : public ALittleMsgClient
{
public:
	ALittleUMsgClient() { m_rudp = true; }
};

class ALittleNet
{
public:
	static void Bind(lua_State* l_state)
	{

		luabridge::getGlobalNamespace(l_state)
			.beginClass<ALittleMsgClient>("__CPPAPIMsgInterface")
			.addConstructor<void(*)()>()
			.addFunction("GetID", &ALittleMsgClient::GetID)
			.addFunction("Connect", &ALittleMsgClient::Connect)
			.addFunction("Close", &ALittleMsgClient::Close)
			.addFunction("IsConnected", &ALittleMsgClient::IsConnected)
			.addFunction("SendFactory", &ALittleMsgClient::SendFactory)
			.endClass();

		luabridge::getGlobalNamespace(l_state)
			.deriveClass<ALittleUMsgClient, ALittleMsgClient>("__CPPAPIUMsgInterface")
			.addConstructor<void(*)()>()
			.endClass();

		luabridge::getGlobalNamespace(l_state)
			.beginClass<ALittleHttpClient>("__CPPAPIHttpInterface")
			.addConstructor<void(*)()>()
			.addFunction("GetID", &ALittleHttpClient::GetID)
			.addFunction("SetURL", &ALittleHttpClient::SetURL)
			.addFunction("Start", &ALittleHttpClient::Start)
			.addFunction("Stop", &ALittleHttpClient::Stop)
			.addFunction("GetResponse", &ALittleHttpClient::GetResponse)
			.addFunction("GetHead", &ALittleHttpClient::GetHead)
			.addFunction("GetURL", &ALittleHttpClient::GetURL)
			.endClass();

		luabridge::getGlobalNamespace(l_state)
			.beginClass<ALittleHttpFile>("__CPPAPIHttpFileInterface")
			.addConstructor<void(*)()>()
			.addFunction("SetURL", &ALittleHttpFile::SetURL)
			.addFunction("GetID", &ALittleHttpFile::GetID)
			.addFunction("Start", &ALittleHttpFile::Start)
			.addFunction("Stop", &ALittleHttpFile::Stop)
			.addFunction("GetPath", &ALittleHttpFile::GetPath)
			.addFunction("GetTotalSize", &ALittleHttpFile::GetTotalSize)
			.addFunction("GetCurSize", &ALittleHttpFile::GetCurSize)
			.endClass();
	}
};

#endif

#ifdef ALITTLE_NET_IMPL
#ifndef ALITTLE_NET_IMPL_INCLUDE
#define ALITTLE_NET_IMPL_INCLUDE
int s_alittle_net_id_creator = 0;
std::unordered_set<int> s_alittle_net_id_set;
#endif
#endif