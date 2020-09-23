
#include "MysqlConnection.h"

#ifdef _WIN32
#include <winsock.h>
#endif
#include <Mysql/mysql.h>
#include <Mysql/errmsg.h>

#include "Carp/carp_log.hpp"

namespace ALittle
{

void MysqlConnection::Setup()
{
	if (mysql_library_init(0, NULL, NULL))
	{
		CARP_ERROR("could not initialize MySQL library");
	}
}

void MysqlConnection::Shutdown()
{
	mysql_library_end();
}

MysqlConnection::MysqlConnection()
: m_mysql(0), m_port(0)
{ }

MysqlConnection::~MysqlConnection() { Close(); }

const std::string& MysqlConnection::GetDBName() const
{
	return m_db_name;
}

bool MysqlConnection::Open(const char* ip
							, const char* username
							, const char* password
							, unsigned int port
							, const char* db_name)
{
	// check param
    if (ip == nullptr) { CARP_ERROR("ip == nullptr"); return false; }
    if (username == nullptr) { CARP_ERROR("username == nullptr"); return false; }
    if (password == nullptr) { CARP_ERROR("password == nullptr"); return false; }
    if (db_name == nullptr) { CARP_ERROR("db_name == nullptr"); return false; }

	if (m_mysql) return true;

	// create mysql object
	m_mysql = mysql_init(0);

	// check create succeed or not
	if (!m_mysql)
	{
		CARP_ERROR("mysql_init failed: out of memory");
		return false;
	}

	// allow report data truncation error
	bool bool_option = true;
	if (mysql_options(m_mysql, MYSQL_REPORT_DATA_TRUNCATION, &bool_option))
	{
		mysql_close(m_mysql); m_mysql = 0;
		CARP_ERROR("mysql_options failed: MYSQL_REPORT_DATA_TRUNCATION is unknow option");
		return false;
	}
	// use utf8
	if (mysql_options(m_mysql, MYSQL_SET_CHARSET_NAME, "utf8mb4"))
	{
		mysql_close(m_mysql); m_mysql = 0;
		CARP_ERROR("mysql_options failed: MYSQL_SET_CHARSET_NAME is unknow option");
		return false;
	}
	// can auto reconnect
	bool_option = false;
	if (mysql_options(m_mysql, MYSQL_OPT_RECONNECT, &bool_option))
	{
		mysql_close(m_mysql); m_mysql = 0;
		CARP_ERROR("mysql_options failed: MYSQL_OPT_RECONNECT is unknow option");
		return false;
	}

	// mysql temp
	MYSQL* mysql = 0;

	// start connect
	mysql = mysql_real_connect(m_mysql
								, ip
								, username
								, password
								, db_name
								, port
								, 0
								, CLIENT_MULTI_STATEMENTS | CLIENT_INTERACTIVE);

	// if connect succeed
	if (mysql)
	{
		// save current database name
		m_db_name = db_name;
		m_ip = ip;
		m_username = username;
		m_password = password;
		m_port = port;
		return true;
	}

	CARP_ERROR("mysql_real_connect failed:" << mysql_error(m_mysql));
	// connect failed
	mysql_close(m_mysql); m_mysql = 0;

	return false;
}

bool MysqlConnection::ReOpen()
{
	Close();
	return Open(m_ip.c_str(), m_username.c_str(), m_password.c_str(), m_port, m_db_name.c_str());
}

void MysqlConnection::Close()
{
	if (!m_mysql) return;

	// release all stmt
	StmtMap::iterator it, end = m_stmt_map.end();
	for (it = m_stmt_map.begin(); it != end; ++it)
	{
		for (size_t i = 0; i < it->second->bind_output.size(); ++i)
		{
			if (it->second->bind_output[i].buffer != nullptr)
				free(it->second->bind_output[i].buffer);
		}
		// free stmt
		mysql_stmt_close(it->second->stmt);
		// flag stmt to 0
		it->second->stmt = 0;
	}
	m_stmt_map.clear();

	// release mysql object
	mysql_close(m_mysql);
	m_mysql = 0;
}

bool MysqlConnection::ReleaseStmt(const char* sql)
{
	StmtMap::iterator it = m_stmt_map.find(sql);
	if (it == m_stmt_map.end())
	{
		CARP_ERROR("can't find stmt by sql:" << sql);
		return false;
	}
	for (size_t i = 0; i < it->second->bind_output.size(); ++i)
	{
		if (it->second->bind_output[i].buffer != nullptr)
			free(it->second->bind_output[i].buffer);
	}
	// free stmt
	mysql_stmt_close(it->second->stmt);
	// flag stmt to 0
	it->second->stmt = 0;

	m_stmt_map.erase(it);
	return true;
}

bool MysqlConnection::ExecuteQuery(const char* sql, std::string& reason)
{
	if (sql == nullptr)
	{
		reason = "sql == nullptr";
		return false;
	}
	if (m_mysql == nullptr)
	{
		reason = "m_mysql == nullptr";
		return false;
	}

	if (mysql_query(m_mysql, sql))
	{
		reason = mysql_error(m_mysql);
		return false;
	}

	MYSQL_RES* store_result = mysql_store_result(m_mysql);
	if (store_result) mysql_free_result(store_result);
	
	return true;
}

bool MysqlConnection::Ping()
{
	if (!m_mysql)
	{
		CARP_ERROR("m_mysql is null!");
		return false;
	}

	// check disconnect
	if (mysql_ping(m_mysql))
	{
		CARP_ERROR("mysql_ping failed: " << mysql_error(m_mysql));
		return false;
	}

	return true;
}

MysqlConnection::MysqlStmtInfoPtr MysqlConnection::GetStmt(const std::string& sql, bool& need_reconnect)
{
	need_reconnect = false;
	if (!m_mysql)
	{
		CARP_ERROR("m_mysql is null!");
		return MysqlStmtInfoPtr();
	}
	
	// find stmt
	auto it = m_stmt_map.find(sql);
	if (it != m_stmt_map.end()) return it->second;

	// mysql stmt info
	MysqlStmtInfoPtr info = MysqlStmtInfoPtr(new MysqlStmtInfo);
	info->conn = this;
	
	// create stmt
	info->stmt = mysql_stmt_init(m_mysql);
	if (!info->stmt)
	{
		CARP_ERROR("mysql_stmt_init failed: out of memory!");
		return MysqlStmtInfoPtr();
	}

	// check succeed or not
	if (mysql_stmt_prepare(info->stmt, sql.c_str(), (unsigned long)sql.size()))
	{
		auto error = mysql_stmt_errno(info->stmt);
		need_reconnect = error == CR_SERVER_GONE_ERROR || error == CR_SERVER_LOST;
		CARP_ERROR("mysql_stmt_prepare failed: code:" << mysql_stmt_errno(info->stmt) << ", reason:" << mysql_stmt_error(info->stmt));
		mysql_stmt_close(info->stmt);
		return MysqlStmtInfoPtr();
	}

	// get param meta
	MYSQL_RES* field_meta_result = mysql_stmt_result_metadata(info->stmt);
	if (field_meta_result != nullptr)
	{
		// get field count
		unsigned int field_count = mysql_num_fields(field_meta_result);
		if (field_count > 0)
		{
			// init bind input
			info->bind_output.resize(field_count);
			info->value_length.resize(field_count, 0);
			memset(&info->bind_output[0], 0, sizeof(MYSQL_BIND) * field_count);

			// get param field
			MYSQL_FIELD* field_list = mysql_fetch_field(field_meta_result);
			if (field_list == nullptr)
			{
				CARP_ERROR("mysql_fetch_field failed: " << mysql_stmt_error(info->stmt));
				mysql_free_result(field_meta_result);
				mysql_stmt_close(info->stmt);
				return MysqlStmtInfoPtr();
			}

			// set bind input info
			for (unsigned int i = 0; i < field_count; ++i)
			{
				MYSQL_BIND& bind = info->bind_output[i];
				bind.buffer_type = field_list[i].type;
				bind.is_unsigned = (field_list[i].flags & UNSIGNED_FLAG) > 0;
				auto buffer_length = field_list[i].length;
				// 首先，对于数值类型的变量，mysql_stmt_fetch会无视buffer_length参数，强行写入
				// 所以这里的内存长度，必须大于或等于8个字节
				// 这里定1024，是因为减少字符串阶段通知
				if (buffer_length <= 0 || buffer_length >= 1024) buffer_length = 1024;
				bind.buffer = malloc(buffer_length);
				bind.buffer_length = buffer_length;
				bind.length = &info->value_length[i];
			}
		}
		mysql_free_result(field_meta_result);
	}

	// save and return
	m_stmt_map[sql] = info;
	return info;
}

bool MysqlConnection::IsOpen() const
{
	return m_mysql != 0;
}

} // ALittle
