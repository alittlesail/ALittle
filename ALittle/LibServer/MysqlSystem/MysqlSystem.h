
#ifndef _ALITTLE_MYSQLSYSTEM_H_
#define _ALITTLE_MYSQLSYSTEM_H_

#include <string>
#include <vector>

#include "Carp/carp_thread_consumer.hpp"

class MysqlConnection;
class MysqlStatementQuery;

namespace ALittle
{

class ServerSchedule;

struct MysqlTask
{
    int query_id = 0;
    bool empty = false;                 // 如果empty为true，那么就是一个空请求
    MysqlStatementQuery* query = nullptr; // 如果query为空，那么就使用sql
    std::string sql;
    ServerSchedule* schedule = nullptr;
};

class MysqlThread : CarpThreadConsumer<MysqlTask>
{
public:
    MysqlThread();
    ~MysqlThread();

public:
    bool Init(const char* ip
        , const char* username
        , const char* password
        , unsigned int port
        , const char* db_name);

    void AddTask(int query_id, MysqlStatementQuery* query, ServerSchedule* schedule);
    void AddTask(int query_id, const char* sql, ServerSchedule* schedule);
	void AddTask(int query_id, ServerSchedule* schedule);

protected:
    // 执行日志
    virtual void Flush(MysqlTask& info) override;

private:
    MysqlConnection* m_conn;
};

class MysqlSystem
{
public:
    MysqlSystem();
    ~MysqlSystem();

public:
    void Setup(int thread_count
        , const char* ip
        , const char* username
        , const char* password
        , unsigned int port
        , const char* db_name);

    void Shutdown();

    bool AddTask(int thread_id, int query_id, MysqlStatementQuery* query, ServerSchedule* schedule);
    bool AddTask(int thread_id, int query_id, const char* sql, ServerSchedule* schedule);
	bool AddTask(int thread_id, int query_id, ServerSchedule* schedule);

private:
    std::vector<MysqlThread*> m_threads;
};

} // ALittle

#endif // _ALITTLE_MYSQLSYSTEM_H_