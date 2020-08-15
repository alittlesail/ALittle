
#ifndef _ALITTLE_SOCKETWRAP_H_
#define _ALITTLE_SOCKETWRAP_H_

#include <asio.hpp>
#include <asio/ssl.hpp>

#include <functional>
#include <memory>

namespace ALittle
{

typedef std::shared_ptr<asio::io_service> ServicePtr;
typedef std::shared_ptr<asio::ip::tcp::resolver> ResolverPtr;

typedef std::shared_ptr<asio::ip::tcp::socket> NTVSocketPtr;
typedef std::shared_ptr<asio::ssl::stream<asio::ip::tcp::socket> > SSLSocketPtr;

typedef std::shared_ptr<asio::ip::tcp::acceptor> AcceptorPtr;

class ALittleSocket
{
public:
	ALittleSocket(bool is_ssl, asio::io_service* service, const std::string& domain)
	{
		if (is_ssl)
		{
			asio::ssl::context cxt(asio::ssl::context::sslv23);
			ssl_socket = SSLSocketPtr(new asio::ssl::stream<asio::ip::tcp::socket>(*service, cxt));
			// Set SNI Hostname (many hosts need this to handshake successfully)
			SSL_set_tlsext_host_name(ssl_socket->native_handle(), domain.c_str());
		}
		else
			ntv_socket = NTVSocketPtr(new asio::ip::tcp::socket(*service));
	}

	ALittleSocket(bool is_ssl, asio::io_service* service, asio::ssl::context* context)
	{
		if (is_ssl)
			ssl_socket = SSLSocketPtr(new asio::ssl::stream<asio::ip::tcp::socket>(*service, *context));
		else
			ntv_socket = NTVSocketPtr(new asio::ip::tcp::socket(*service));
	}

	~ALittleSocket() {}

public:
	NTVSocketPtr ntv_socket;
	SSLSocketPtr ssl_socket;
};
typedef std::shared_ptr<ALittleSocket> ALittleSocketPtr;

#define SOCKETHELPER_Connect(self, it, ec) \
do { \
	if (self->ntv_socket) \
		self->ntv_socket->connect(*it, ec); \
	else \
		asio::connect(self->ssl_socket->lowest_layer(), it, ec); \
} while (0)

#define SOCKETHELPER_IsOpen(self, result) \
do { \
	if (self->ntv_socket) \
		result = self->ntv_socket->is_open(); \
	else \
		result = self->ssl_socket->lowest_layer().is_open(); \
} while (0)

#define SOCKETHELPER_SetNoDelay(self) \
do { \
	if (self->ntv_socket) \
		self->ntv_socket->set_option(asio::ip::tcp::no_delay(true)); \
	else \
		self->ssl_socket->lowest_layer().set_option(asio::ip::tcp::no_delay(true)); \
} while (0)

#define SOCKETHELPER_AfterConnect(self) \
do { \
	if (self->ntv_socket) \
	{ \
		self->ntv_socket->lowest_layer().set_option(asio::ip::tcp::no_delay(true)); \
	} \
	else \
	{ \
		self->ssl_socket->lowest_layer().set_option(asio::ip::tcp::no_delay(true)); \
		asio::error_code ec; \
		self->ssl_socket->handshake(asio::ssl::stream<asio::ip::tcp::socket>::client, ec); \
	} \
} while (0)

#define SOCKETHELPER_AfterAsyncConnect(self) \
do { \
	if (self->ntv_socket) \
	{ \
		self->ntv_socket->lowest_layer().set_option(asio::ip::tcp::no_delay(true)); \
	} \
	else \
	{ \
		self->ssl_socket->lowest_layer().set_option(asio::ip::tcp::no_delay(true)); \
	} \
} while (0)

#define SOCKETHELPER_Close(self) \
do { \
	asio::error_code ec; \
	if (self->ntv_socket) \
		self->ntv_socket->close(ec); \
	else \
		self->ssl_socket->shutdown(ec); \
} while (0)

#define SOCKETHELPER_Write(self, content, size, ec) \
do { \
	if (self->ntv_socket) \
		asio::write(*self->ntv_socket, asio::buffer(content, size), ec); \
	else \
		asio::write(*self->ssl_socket, asio::buffer(content, size), ec); \
} while (0)

#define SOCKETHELPER_ReadSome(self, content, size, ec, result) \
do { \
	if (self->ntv_socket) \
		result = self->ntv_socket->read_some(asio::buffer(content, size), ec); \
	else \
		result = self->ssl_socket->read_some(asio::buffer(content, size), ec); \
} while (0)

#define SOCKETHELPER_AsyncConnect(self, it, callback) \
do { \
	if (self->ntv_socket) \
		self->ntv_socket->async_connect(*it, callback); \
	else \
		asio::async_connect(self->ssl_socket->lowest_layer(), it, callback); \
} while(0)

#define SOCKETHELPER_AsyncWrite(self, content, size, callback) \
do { \
	if (self->ntv_socket) \
		asio::async_write(*self->ntv_socket, asio::buffer(content, size), callback); \
	else \
		asio::async_write(*self->ssl_socket, asio::buffer(content, size), callback); \
} while(0)

#define SOCKETHELPER_AsyncReadSome(self, content, size, callback) \
do { \
	if (self->ntv_socket) \
		self->ntv_socket->async_read_some(asio::buffer(content, size), callback); \
	else \
		self->ssl_socket->async_read_some(asio::buffer(content, size), callback); \
} while(0)

#define SOCKETHELPER_AsyncAccept(self, acceptor, callback) \
do { \
	if (self->ntv_socket) \
		acceptor->async_accept(*self->ntv_socket, callback); \
	else \
		acceptor->async_accept(self->ssl_socket->lowest_layer(), callback); \
} while(0)

#define SOCKETHELPER_GetRemoteIp(self, result) \
do { \
	if (self->ntv_socket) \
		result = self->ntv_socket->remote_endpoint().address().to_string(); \
	else \
		result = self->ssl_socket->lowest_layer().remote_endpoint().address().to_string(); \
} while(0)

#define SOCKETHELPER_GetRemotePort(self, result) \
do { \
	if (self->ntv_socket) \
		result = self->ntv_socket->remote_endpoint().port(); \
	else \
		result = self->ssl_socket->lowest_layer().remote_endpoint().port(); \
} while(0)

} // ALittle

#endif // _ALITTLE_SOCKETWRAP_H_
