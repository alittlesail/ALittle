
#ifdef HAS_MYSQL

#include "MysqlSystem.h"

#include <functional>

#include "../ServerSystem/ServerSchedule.h"
#include "Carp/carp_mysql.hpp"

namespace ALittle
{

MysqlThread::MysqlThread()
{
    m_conn = new MysqlConnection();
}

MysqlThread::~MysqlThread()
{
    delete m_conn;
}

bool MysqlThread::Init(const char* ip, const char* username, const char* password, unsigned int port, const char* db_name)
{
    if (!m_conn->Open(ip, username, password, port, db_name))
        return false;

    Start();
    return true;
}

void MysqlThread::AddTask(int query_id, MysqlStatementQuery* query, ServerSchedule* schedule)
{
    MysqlTask info;
    info.query_id = query_id;
    info.schedule = schedule;
    info.empty = false;
    info.query = query;
    Add(info);
}

void MysqlThread::AddTask(int query_id, const char* sql, ServerSchedule* schedule)
{
    MysqlTask info;
    info.query_id = query_id;
    info.schedule = schedule;
	info.empty = false;
    info.query = nullptr;
    info.sql = sql;
    Add(info);
}

void MysqlThread::AddTask(int query_id, ServerSchedule* schedule)
{
	MysqlTask info;
	info.query_id = query_id;
	info.schedule = schedule;
	info.empty = true;
	info.query = nullptr;
	Add(info);
}

void MysqlThread::Execute(MysqlTask& info)
{
    if (info.empty)
    {
        std::string reason;
        bool result = true;
		info.schedule->Execute(std::bind(&ServerSchedule::HandleMysqlEmpty, info.schedule, info.query_id, result, reason));
    }
    else if (info.query != nullptr)
    {
        std::string reason;
        info.query->SetConnection(m_conn);
        bool result = info.query->Execute(reason);
        info.schedule->Execute(std::bind(&ServerSchedule::HandleMysqlQuery, info.schedule, info.query_id, result, reason));
    }
    else
    {
        std::string reason;
        bool result = m_conn->ExecuteQuery(info.sql.c_str(), reason);
        info.schedule->Execute(std::bind(&ServerSchedule::HandleMysqlQuery, info.schedule, info.query_id, result, reason));
    }
}

MysqlSystem::MysqlSystem()
{
}

MysqlSystem::~MysqlSystem()
{
}

void MysqlSystem::Setup(int thread_count
    , const char* ip
    , const char* username
    , const char* password
    , unsigned int port
    , const char* db_name)
{
    Shutdown();

    if (thread_count <= 0)
    {
        CARP_ERROR("thread_count <= 0");
        return;
    }

    // �����������ݿ⣬���û�оʹ���һ��
    MysqlConnection conn;
    if (!conn.Open(ip, username, password, port, db_name))
    {
        if (!conn.Open(ip, username, password, port, "mysql"))
        {
            CARP_ERROR("can't not connect db_name:mysql for create db_name:" << db_name);
            return;
        }

        std::string create_sql = "CREATE DATABASE `";
        create_sql += db_name;
        create_sql += "` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;";

        std::string reason;
        if (!conn.ExecuteQuery(create_sql.c_str(), reason))
        {
            CARP_ERROR("sql(" << create_sql << ") execute failed:" << reason);
            return;
        }
    }

    for (int i = 0; i < thread_count; ++i)
    {
        auto thread = new MysqlThread();
        m_threads.push_back(thread);
        if (!thread->Init(ip, username, password, port, db_name))
        {
            Shutdown();
            return;
        }
    }
}

void MysqlSystem::Shutdown()
{
    for (size_t i = 0; i < m_threads.size(); ++i)
        delete m_threads[i];
    m_threads.clear();
}

bool MysqlSystem::AddTask(int thread_id, int query_id, MysqlStatementQuery* query, ServerSchedule* schedule)
{
    if (m_threads.empty()) return false;
    if (thread_id < 0) thread_id = 0;
    m_threads[thread_id % m_threads.size()]->AddTask(query_id, query, schedule);
    return true;
}

bool MysqlSystem::AddTask(int thread_id, int query_id, const char* sql, ServerSchedule* schedule)
{
    if (m_threads.empty()) return false;
    if (thread_id < 0) thread_id = 0;
    m_threads[thread_id % m_threads.size()]->AddTask(query_id, sql, schedule);
    return true;
}

bool MysqlSystem::AddTask(int thread_id, int query_id, ServerSchedule* schedule)
{
	if (m_threads.empty()) return false;
	if (thread_id < 0) thread_id = 0;
	m_threads[thread_id % m_threads.size()]->AddTask(query_id, schedule);
	return true;
}

} // ALittle

#endif // HAS_MYSQL