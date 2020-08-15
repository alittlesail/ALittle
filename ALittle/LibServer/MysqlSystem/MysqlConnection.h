
#ifndef _ALITTLE_MYSQLCONNECTION_H_
#define _ALITTLE_MYSQLCONNECTION_H_

#include <string>
#include <map>
#include <memory>
#include <vector>

struct MYSQL_STMT;
struct MYSQL;
struct MYSQL_BIND;

namespace ALittle
{

class MysqlConnection
{
public:
	MysqlConnection();
	~MysqlConnection();

public:
	/**
	 * invoke before use mysql
	 */
	static void Setup();

	/**
	 * invoke before application end
	 */
	static void Shutdown();

public:
	/* connect mysql
	 * @param ip: target ip dress
	 * @param username: username
	 * @param password: password
	 * @param port: port
	 * @param db_name: database name
	 * @return succeed or not
     */
	bool Open(const char* ip
		, const char* username
		, const char* password
		, unsigned int port
		, const char* db_name);

	bool ReOpen();

	/* reconnect
	 * @param error_message: error message
	 * @return succeed or not
	 */
	bool Ping();

	// close
	void Close();

	/* current is open
	 * @return open or not
	 */
	bool IsOpen() const;

public:
	// mysql stmt info
	struct MysqlStmtInfo
	{
		MYSQL_STMT* stmt;									// stmt object
		std::vector<MYSQL_BIND> bind_output;				// output bind for read
		std::vector<unsigned long> value_length;		// output max length for read
		MysqlConnection* conn;								// come from
	};
	typedef std::shared_ptr<MysqlStmtInfo> MysqlStmtInfoPtr;

	/* get stmt object
	 * @param sql: sql string
	 * @return MysqlStmtInfo
	 */
	MysqlStmtInfoPtr GetStmt(const std::string& sql, bool& need_reconnect);
	bool ReleaseStmt(const char* sql);

	// execute simple sql
	bool ExecuteQuery(const char* sql, std::string& reason);

public:
	/* current connect database name
	 * return database name
	 */
	const std::string& GetDBName() const;

private:
	MYSQL* m_mysql;

	typedef std::map<std::string,MysqlStmtInfoPtr> StmtMap;
	StmtMap m_stmt_map;

private:
	std::string m_db_name;
	std::string m_ip;
	std::string m_username;
	std::string m_password;
	int m_port;
};

} // ALittle

#endif // _ALITTLE_MYSQLCONNECTION_H_