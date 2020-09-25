
#include "ClientReceiver.h"
#include "ClientServer.h"

#include "ALittle/LibServer/ServerSystem/ServerSchedule.h"

#include <functional>

#include "Carp/carp_crypto.hpp"
#include "Carp/carp_string.hpp"

namespace ALittle
{

#define WEBSOCKET_HEAD_BUFFER_SIZE_MAX 1024
#define MESSAGE_BUFFER_SIZE 102400000

void ClientReceiver::NextReadWebSocketHandShake()
{
	m_socket->async_read_some(asio::buffer(m_message_head, sizeof(m_message_head))
		, std::bind(&ClientReceiver::HandleWebSocketHandShakeReceive, this->shared_from_this()
		, std::placeholders::_1, std::placeholders::_2));
}

void ClientReceiver::HandleWebSocketHandShakeReceive( const asio::error_code& ec, std::size_t actual_size )
{
	if (ec)
	{
		CARP_SYSTEM("receive failed:" << ec.value());
		ClientServerPtr server = m_server.lock();
		if (server)	server->HandleOuterDisconnected(this->shared_from_this());
		return;
	}

	// store current size
	int current_size = (int)m_websocket_handshake.size();
	// add to buffer
	m_websocket_handshake.append(m_message_head, actual_size);

	// stop receive if lager than max size
	if (m_websocket_handshake.size() > WEBSOCKET_HEAD_BUFFER_SIZE_MAX)
	{
		CARP_SYSTEM("websocket hand shake is large than " << WEBSOCKET_HEAD_BUFFER_SIZE_MAX);
		ClientServerPtr server = m_server.lock();
		if (server)	server->HandleOuterDisconnected(this->shared_from_this());
		return;
	}

	// set start point to find
	int find_start_pos = current_size - (int)strlen("\r\n\r\n");
	if (find_start_pos < 0) find_start_pos = 0;

	// find \r\n\r\n
	std::string::size_type find_pos = m_websocket_handshake.find("\r\n\r\n", find_start_pos);
	if (find_pos != std::string::npos)
	{
		// the end position of \r\n\r\n in m_http_head
		int head_size = (int)find_pos + (int)strlen("\r\n\r\n");
		// resize http size, delete other data
		m_websocket_handshake.resize(head_size);

		// get the key
		std::string::size_type pos = m_websocket_handshake.find("Sec-WebSocket-Key:");
		if (pos == std::string::npos)
		{
			CARP_SYSTEM("can't find Sec-WebSocket-Key in web socket head");
			ClientServerPtr server = m_server.lock();
			if (server)	server->HandleOuterDisconnected(this->shared_from_this());
			return;
		}

		pos += strlen("Sec-WebSocket-Key:");

		std::string::size_type end_pos = m_websocket_handshake.find("\r\n", pos);
		if (pos == std::string::npos)
		{
			CARP_SYSTEM("can't find end of Sec-WebSocket-Key in web socket head");
			ClientServerPtr server = m_server.lock();
			if (server)	server->HandleOuterDisconnected(this->shared_from_this());
			return;
		}

		// encode the key
		std::string key = m_websocket_handshake.substr(pos, end_pos - pos);
		CarpString::TrimLeft(key);
		CarpString::TrimRight(key);
		key.append("258EAFA5-E914-47DA-95CA-C5AB0DC85B11");

		unsigned int digest[5];
		CarpCrypto::Sha1(key, digest);

		char* tmp = (char*)digest;
		char new_digest[20] = { 0 };
		for(int i = 0; i < 5; ++i)
		{
			new_digest[i*4]		= tmp[i*4+3];
			new_digest[i*4+1]	= tmp[i*4+2];
			new_digest[i*4+2]	= tmp[i*4+1];
			new_digest[i*4+3]	= tmp[i*4];
		}

		key = CarpCrypto::Base64Encode(new_digest, 20);

		m_websocket_handshake = "";
		m_websocket_handshake.append("HTTP/1.1 101 Switching Protocols\r\n");
		m_websocket_handshake.append("Sec-WebSocket-Version: 13\r\n");
		m_websocket_handshake.append("Upgrade: websocket\r\n");
		m_websocket_handshake.append("Connection: Upgrade\r\n");
		m_websocket_handshake.append("Server: ALittle\r\n");
		m_websocket_handshake.append("Sec-WebSocket-Accept: ").append(key).append("\r\n\r\n");

		// send hand shake
		asio::async_write(*m_socket, asio::buffer(m_websocket_handshake.c_str(), m_websocket_handshake.size())
			, std::bind(&ClientReceiver::HandleWebSocketHandShakeSend, this->shared_from_this()
			, std::placeholders::_1, std::placeholders::_2));
		
		return;
	}

	NextReadWebSocketHandShake();
}

void ClientReceiver::HandleWebSocketHandShakeSend( const asio::error_code& ec, std::size_t actual_size )
{
	if (ec)
	{
		CARP_SYSTEM("websocket hand shake send failed!, " << ec.value());
		ClientServerPtr server = m_server.lock();
		if (server)	server->HandleOuterDisconnected(this->shared_from_this());
		return;
	}

	NextWebSocketRead1();
}

void ClientReceiver::NextWebSocketRead1()
{
	asio::async_read(*m_socket, asio::buffer(m_frame_buffer, 2)
		, std::bind(&ClientReceiver::HandleNextWebSocketRead1, this->shared_from_this()
		, std::placeholders::_1, std::placeholders::_2));
}

void ClientReceiver::HandleNextWebSocketRead1( const asio::error_code& ec, std::size_t actual_size )
{
	if (ec)
	{
		CARP_SYSTEM("receive failed!, " << ec.value());
		ClientServerPtr server = m_server.lock();
		if (server)	server->HandleOuterDisconnected(this->shared_from_this());
		return;
	}

	bool fin = (m_frame_buffer[0]  & 0x80) > 0;
	m_opcode = m_frame_buffer[0] & 0x0F;
	m_current_is_message = false;

	switch (m_opcode)
	{
	case 0: // lianxu message
	case 1: // text message
	case 2: m_current_is_message = true; break;	// binary message
	case 8:
		{
			CARP_INFO("websocket client send to server close");
			ClientServerPtr server = m_server.lock();
			if (server)	server->HandleOuterDisconnected(this->shared_from_this());
			return;
		}
	default: break;
	}

	m_has_mark = (m_frame_buffer[1]  & 0x80) > 0;
	int payload_len = m_frame_buffer[1] & 0x7F;
	if (payload_len < 0)
	{
		CARP_SYSTEM("payload len < 0");
		ClientServerPtr server = m_server.lock();
		if (server)	server->HandleOuterDisconnected(this->shared_from_this());
		return;
	}

	NextWebSocketRead2(payload_len);
}

void ClientReceiver::NextWebSocketRead2(int payload_len)
{
	if (payload_len == 126)
		asio::async_read(*m_socket, asio::buffer(m_frame_buffer, 2)
		, std::bind(&ClientReceiver::HandleNextWebSocketRead2, this->shared_from_this()
		, std::placeholders::_1, std::placeholders::_2));
	else if (payload_len == 127)
		asio::async_read(*m_socket, asio::buffer(m_frame_buffer, 8)
		, std::bind(&ClientReceiver::HandleNextWebSocketRead2, this->shared_from_this()
		, std::placeholders::_1, std::placeholders::_2));
	else
	{
		m_data_length = payload_len;
		if (m_has_mark)
			NextWebSocketReadMark();
		else
			NextWebSocketReadData();
	}
}

void ClientReceiver::HandleNextWebSocketRead2( const asio::error_code& ec, std::size_t actual_size )
{
	if (ec)
	{
		CARP_SYSTEM("receive failed!, " << ec.value());
		ClientServerPtr server = m_server.lock();
		if (server)	server->HandleOuterDisconnected(this->shared_from_this());
		return;
	}

	if (actual_size == 2)
	{
		short data_length = 0;
		unsigned char* char_data_length = (unsigned char*)&data_length;
		char_data_length[0] = m_frame_buffer[1];
		char_data_length[1] = m_frame_buffer[0];
		m_data_length = data_length;
	}
	else
	{
		m_data_length = 0;
		unsigned char* char_data_length = (unsigned char*)&m_data_length;
		char_data_length[0] = m_frame_buffer[7];
		char_data_length[1] = m_frame_buffer[6];
		char_data_length[2] = m_frame_buffer[5];
		char_data_length[3] = m_frame_buffer[4];
	}

	if (m_data_length < 0)
	{
		CARP_SYSTEM("m_data_length < 0");
		ClientServerPtr server = m_server.lock();
		if (server)	server->HandleOuterDisconnected(this->shared_from_this());
		return;
	}

	if (m_has_mark)
		NextWebSocketReadMark();
	else
		NextWebSocketReadData();
}

void ClientReceiver::NextWebSocketReadMark()
{
	asio::async_read(*m_socket, asio::buffer(m_frame_buffer, 4)
		, std::bind(&ClientReceiver::HandleNextWebSocketReadMark, this->shared_from_this()
		, std::placeholders::_1, std::placeholders::_2));
}

void ClientReceiver::HandleNextWebSocketReadMark( const asio::error_code& ec, std::size_t actual_size )
{
	if (ec)
	{
		CARP_SYSTEM("receive failed!, " << ec.value());
		ClientServerPtr server = m_server.lock();
		if (server)	server->HandleOuterDisconnected(this->shared_from_this());
		return;
	}

	memcpy(m_mark, m_frame_buffer, 4);

	NextWebSocketReadData();
}

void ClientReceiver::NextWebSocketReadData()
{
	if (m_websocket_buffer) free(m_websocket_buffer);
	m_websocket_buffer = malloc(m_data_length);

	asio::async_read(*m_socket, asio::buffer((char*)m_websocket_buffer, m_data_length)
		, std::bind(&ClientReceiver::HandleNextWebSocketReadData, this->shared_from_this()
		, std::placeholders::_1, std::placeholders::_2));
}

void ClientReceiver::HandleNextWebSocketReadData( const asio::error_code& ec, std::size_t actual_size )
{
	if (ec)
	{
		CARP_SYSTEM("receive failed!, " << ec.value());
		ClientServerPtr server = m_server.lock();
		if (server)	server->HandleOuterDisconnected(this->shared_from_this());
		return;
	}

	if (m_current_is_message == false)
	{
		// release buffer
		ReleaseWebSocketBuffer();
		// read next
		NextWebSocketRead1();
		return;
	}

	// handle mark
	char* body = (char*)m_websocket_buffer;
	if (m_has_mark)
	{
		for (unsigned int i = 0; i < actual_size; ++i)
			body[i] = (body[i] ^ m_mark[i % 4]);
	}

	HandleWebSocketReadData((int)actual_size, 0);
}

void ClientReceiver::HandleWebSocketReadData( int total_size, int offset )
{
	// check offset
	if (offset >= total_size)
	{
		ReleaseWebSocketBuffer();
		NextWebSocketRead1();
		return;
	}
	// calc remain size
	int remain_size = total_size - offset;

	char* body = (char*)m_websocket_buffer + offset;

	// check is read message head
	if (m_head_size < sizeof(m_message_head))
	{
		// calc need head size
		int need_size = sizeof(m_message_head) - m_head_size;
		int copy_size = remain_size < need_size ? remain_size : need_size;

		// copy to message head
		memcpy(m_message_head + m_head_size, body, copy_size);
		m_head_size += copy_size;
		offset += copy_size;
		body += copy_size;

		// if head size is enough
		if (m_head_size == sizeof(m_message_head))
		{
			// get message size from head buffer
			CARP_MESSAGE_SIZE message_size = *(CARP_MESSAGE_SIZE*)m_message_head;
			CARP_MESSAGE_ID message_id = *(CARP_MESSAGE_ID*)(m_message_head + sizeof(CARP_MESSAGE_SIZE));

			// check message_id is 0 and message_size is 0 then is heartbeat message
			if (message_id == 0 && message_size == 0)
			{
				ReadComplete();
				HandleWebSocketReadData(total_size, offset);
				return;
			}

			if (message_size > MESSAGE_BUFFER_SIZE)
			{
				CARP_ERROR("message_size(" << message_size << ") is large then " << MESSAGE_BUFFER_SIZE);
				ClientServerPtr server = m_server.lock();
				if (server)	server->HandleOuterDisconnected(this->shared_from_this());
				return;
			}

			// if message size is 0,then read completed
			if (message_size == 0)
			{
				ReadComplete();
				HandleWebSocketReadData(total_size, offset);
				return;
			}

			// create memory from pool
			m_memory = malloc(message_size);

			// copy remain data
			remain_size = total_size - offset;
			if (remain_size >= (int)message_size)
			{
				// copy message
				memcpy(m_memory, body, message_size);
				ReadComplete();

				offset += message_size;

				// handle next
				HandleWebSocketReadData(total_size, offset);
				return;
			}

			// copy remain
			memcpy(m_memory, body, remain_size);
			offset += remain_size;
			m_body_size = remain_size;
			// handle next
			HandleWebSocketReadData(total_size, offset);
			return;
		}

		HandleWebSocketReadData(total_size, offset);
		return;
	}

	// get message size from head buffer
	CARP_MESSAGE_SIZE message_size = *(CARP_MESSAGE_SIZE*)m_message_head;
	
	// offset body memory
	char* body_memory = (char*)m_memory;
	body_memory += m_body_size;

	// calc need size
	int need_size = (int)message_size - m_body_size;
	if (remain_size >= need_size)
	{
		// copy message
		memcpy(body_memory, body, need_size);
		ReadComplete();

		offset += need_size;

		// handle next
		HandleWebSocketReadData(total_size, offset);
		return;
	}

	// copy message
	memcpy(body_memory, body, remain_size);
	offset += remain_size;
	m_body_size += remain_size;
	// handle next
	HandleWebSocketReadData(total_size, offset);
}

void ClientReceiver::ReleaseWebSocketBuffer()
{
	if (m_websocket_buffer)
	{
		free(m_websocket_buffer);
		m_websocket_buffer = 0;
	}
}

void ClientReceiver::SendWebSocket(const CarpMessage& message)
{
	// get the size of message body and save in head
	CARP_MESSAGE_SIZE message_size = message.GetTotalSize();
	// get the id of message and save in head
	CARP_MESSAGE_ID message_id = message.GetID();
	// ªÒ»°RPCID
	CARP_MESSAGE_RPCID message_rpcid = message.GetRpcID();

	// memory size = body size + head size
	unsigned int extend_size = message_size + CARP_PROTOCOL_HEAD_SIZE;
	unsigned int memory_size = extend_size;
	void* memory = 0;
	unsigned char* body_memory = 0;

	if (extend_size < 126)
	{
		memory_size += 2;

		// create memory from pool
		memory = malloc(memory_size);
		body_memory = (unsigned char*)memory;
		// clear bit
		body_memory[0] = body_memory[1] = 0;
		// put FIN
		body_memory[0] = body_memory[0] | 0x80;
		// put opcode
		body_memory[0] = body_memory[0] | 0x02;
		// put payload
		body_memory[1] = (unsigned char)extend_size;
		body_memory += 2;
	}
	else if (extend_size <= 65535)
	{
		memory_size += 4;

		// create memory from pool
		memory = malloc(memory_size);
		body_memory = (unsigned char*)memory;
		// clear bit
		body_memory[0] = body_memory[1] = 0;
		// put FIN
		body_memory[0] = body_memory[0] | 0x80;
		// put opcode
		body_memory[0] = body_memory[0] | 0x02;
		// put payload
		body_memory[1] = 126;
		body_memory += 2;
		// put length
		unsigned short value = (unsigned short)extend_size;
		unsigned char* char_extend_size = (unsigned char*)(&value);
		body_memory[0] = char_extend_size[1];
		body_memory[1] = char_extend_size[0];
		body_memory += 2;
	}
	else
	{
		memory_size += 10;

		// create memory from pool
		memory = malloc(memory_size);
		body_memory = (unsigned char*)memory;
		// clear bit
		body_memory[0] = body_memory[1] = 0;
		// put FIN
		body_memory[0] = body_memory[0] | 0x80;
		// put opcode
		body_memory[0] = body_memory[0] | 0x02;
		// put payload
		body_memory[1] = 127;
		body_memory += 2;
		// put length
		unsigned char* char_extend_size = (unsigned char*)&extend_size;
		body_memory[0] = 0;
		body_memory[1] = 0;
		body_memory[2] = 0;
		body_memory[3] = 0;
		body_memory[4] = char_extend_size[3];
		body_memory[5] = char_extend_size[2];
		body_memory[6] = char_extend_size[1];
		body_memory[7] = char_extend_size[0];
		body_memory += 8;
	}

	// set head info
	memcpy(body_memory, &message_size, sizeof(CARP_MESSAGE_SIZE));
	body_memory += sizeof(CARP_MESSAGE_SIZE);
	memcpy(body_memory, &message_id, sizeof(CARP_MESSAGE_ID));
	body_memory += sizeof(CARP_MESSAGE_ID);
	memcpy(body_memory, &message_rpcid, sizeof(CARP_MESSAGE_RPCID));
	body_memory += sizeof(CARP_MESSAGE_RPCID);
	// transfer message to memory
	message.Serialize(body_memory);

	SendPocket(memory, memory_size);
}

} // ALittle
