
#ifndef _ALITTLE_MYSQLTHREADSYSTEM_H_
#define _ALITTLE_MYSQLTHREADSYSTEM_H_

#include <string>
#include <map>
#include <memory>
#include <vector>
#include <list>
#include <mutex>

#include "ALittle/LibCommon/Tool/ThreadConsumer.h"
#include "MysqlConnection.h"

namespace ALittle
{

class MysqlStatementQuery;
class ServerSchedule;

struct MysqlTask
{
    int query_id;
    bool empty;                 // 如果empty为true，那么就是一个空请求
    MysqlStatementQuery* query; // 如果query为空，那么就使用sql
    std::string sql;
    ServerSchedule* schedule;
};

class MysqlThread : ThreadConsumer<MysqlTask>
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
    MysqlConnection m_conn;
};

class MysqlThreadSystem
{
public:
    MysqlThreadSystem();
    ~MysqlThreadSystem();

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

#endif // _ALITTLE_MYSQLTHREADSYSTEM_H_