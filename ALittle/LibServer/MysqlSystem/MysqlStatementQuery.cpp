
#include "MysqlStatementQuery.h"

#ifdef _WIN32
#include <WinSock2.h>
#endif
#include <Mysql/mysql.h>
#include <Mysql/errmsg.h>

#include "Carp/carp_log.hpp"

namespace ALittle
{

MysqlStatementQuery::MysqlStatementQuery()
: m_conn(0), m_need_reset(false)
, m_input_index(0), m_col_index(0), m_col_count(0), m_row_count(0), m_row_index(0), m_affect_count(0)
{
}

MysqlStatementQuery::~MysqlStatementQuery()
{
	Clear();
}

void MysqlStatementQuery::SetConnection(MysqlConnection* conn)
{
	if (conn == 0) return;
	m_conn = conn;
}

void MysqlStatementQuery::SetSQL(const char* sql)
{
	Reset();
	m_sql = sql;
}

const char* MysqlStatementQuery::GetSQL() const
{
    return m_sql.c_str();
}

bool MysqlStatementQuery::Begin(std::string& reason)
{
	// must be reset after begin
	m_need_reset = true;

	// sql must not be empty
    if (m_sql.empty())
    {
        reason = "m_sql is empty";
        End();
        return false;
    }

	// connect must not be null
	if (!m_conn)
    {
        reason = "connection is null";
		End();
		return false;
	}

    // create stmt
    bool need_reconnect = false;
    MysqlConnection::MysqlStmtInfoPtr stmt_info = m_conn->GetStmt(m_sql, need_reconnect);
    if (!stmt_info)
    {
    	if (!need_reconnect)
    	{
            reason = "stmt create failed:" + m_sql;
            End();
            return false;
    	}
    	
        CARP_WARN("try reconnect mysql");
        if (!m_conn->ReOpen())
        {
            reason = "reconnect mysql failed!";
            reason += " stmt create failed:" + m_sql;
            CARP_WARN(reason);
            End();
            return false;
        }
        CARP_WARN("reconnect succeed");

        stmt_info = m_conn->GetStmt(m_sql, need_reconnect);
        if (!stmt_info)
        {
            reason = "stmt create failed:" + m_sql;
            End();
            return false;
        }
    }

	// bind param input
	if (m_bind_input.size() && mysql_stmt_bind_param(stmt_info->stmt, &m_bind_input[0]))
	{
        reason = "mysql_stmt_bind_param failed:";
        reason += mysql_stmt_error(stmt_info->stmt);
		End();
		return false;
	}

	// execute and receive succeed or not
	if (mysql_stmt_execute(stmt_info->stmt))
	{
		reason = "mysql_stmt_execute failed:";
		reason += mysql_stmt_error(stmt_info->stmt);
		
        unsigned int exe_errno = mysql_stmt_errno(stmt_info->stmt);
        if (exe_errno == CR_SERVER_GONE_ERROR || exe_errno == CR_SERVER_LOST)
        {
            CARP_WARN("try reconnect mysql");
            if (!m_conn->ReOpen())
			{
				reason = "reconnect mysql failed!";
                CARP_WARN(reason);
                End();
                return false;
			}
			CARP_WARN("reconnect succeed");

            // create stmt
            stmt_info = m_conn->GetStmt(m_sql, need_reconnect);
            if (!stmt_info)
			{
				reason = "stmt create failed:" + m_sql;
                End();
                return false;
            }

            // bind param input
            if (m_bind_input.size() && mysql_stmt_bind_param(stmt_info->stmt, &m_bind_input[0]))
            {
                reason = "mysql_stmt_bind_param failed:";
                reason += mysql_stmt_error(stmt_info->stmt);
                End();
                return false;
            }

            // execute and receive succeed or not
            if (mysql_stmt_execute(stmt_info->stmt))
            {
                reason = "mysql_stmt_execute failed:";
                reason += mysql_stmt_error(stmt_info->stmt);
                End();
                return false;
            }
        }
        else
        {
            End();
            return false;
        }
	}

	// store result
	mysql_stmt_store_result(stmt_info->stmt);

    // get result info
    m_row_index = 0;
    m_col_index = 0;
	m_row_count = (unsigned int)mysql_stmt_num_rows(stmt_info->stmt);
	m_col_count = (unsigned int)stmt_info->bind_output.size();
	m_affect_count = (unsigned int)mysql_stmt_affected_rows(stmt_info->stmt);

    // fetch data
	m_bind_outputs.resize(m_row_count);
	bool result = true;
	if (m_row_count > 0)
	{		
		int row = 0;
        while (true)
        {
            // bind for output
            if (stmt_info->bind_output.size() && mysql_stmt_bind_result(stmt_info->stmt, &(stmt_info->bind_output[0])))
            {
                reason = "mysql_stmt_bind_result failed:";
                reason += mysql_stmt_error(stmt_info->stmt);
                result = false;
				break;
            }

            // fetch next result
            int fetch_result = mysql_stmt_fetch(stmt_info->stmt);
			if (fetch_result != 0)
			{
                if (fetch_result == MYSQL_DATA_TRUNCATED)
				{
                    // 数据出现截断，那么就要重新申请内存
                    for (size_t i = 0; i < stmt_info->bind_output.size(); ++i)
                    {
                        if (stmt_info->bind_output[i].buffer_length >= stmt_info->value_length[i])
                            continue;
                        if (stmt_info->bind_output[i].buffer != nullptr)
                            free(stmt_info->bind_output[i].buffer);
                        stmt_info->bind_output[i].buffer_length = stmt_info->value_length[i];
                        stmt_info->bind_output[i].buffer = malloc(stmt_info->value_length[i]);
                    }
                    // 返回上一条数据
                    mysql_stmt_data_seek(stmt_info->stmt, row);
                    continue;
                }
                else if (fetch_result == MYSQL_NO_DATA)
				{
                    // 已经没有数据了，这里不做处理
                }
                else
				{
                    reason = "mysql_stmt_bind_result failed:";
					reason += mysql_stmt_error(stmt_info->stmt);
					result = false;
                }
                break;
			}

			// copy data
            m_bind_outputs[row].resize(stmt_info->bind_output.size());
            for (size_t i = 0; i < stmt_info->bind_output.size(); ++i)
            {
				MysqlBind& data = m_bind_outputs[row][i];
                data.buffer_type = (ALittle_enum_field_types)(stmt_info->bind_output[i].buffer_type);
				data.buffer.resize(stmt_info->value_length[i] + 1, 0);
                data.value_length = stmt_info->value_length[i];
                if (stmt_info->value_length[i] > 0)
				    memcpy(data.buffer.data(), stmt_info->bind_output[i].buffer, stmt_info->value_length[i]);
            }
			++row;
        }
	}

    mysql_stmt_free_result(stmt_info->stmt);
	return result;
}

void MysqlStatementQuery::End()
{
	m_input_index = 0;
	m_col_index = 0;
	for (size_t i = 0; i < m_bind_input.size(); ++i)
	{
		if (m_bind_input[i].buffer != nullptr)
			free(m_bind_input[i].buffer);
    }
    m_bind_input.clear();
    m_bind_outputs.clear();
}

bool MysqlStatementQuery::Execute(std::string& reason)
{
	return Begin(reason);
}

void MysqlStatementQuery::Reset()
{
	if (!m_need_reset) return;
	Clear();
}

void MysqlStatementQuery::Clear()
{
	End();
	m_need_reset = false;
}

void MysqlStatementQuery::CommonBindForInput(void* ptr, size_t size, bool is_unsigned, ALittle_enum_field_types buffer_type)
{
	// try reset
	Reset();

	MYSQL_BIND bind;
	memset(&bind, 0, sizeof(bind));

	bind.buffer = malloc(size+1);
	memcpy(bind.buffer, ptr, size);
	bind.buffer_length = (unsigned long)size;
	bind.is_unsigned = is_unsigned;
	bind.buffer_type = (enum_field_types)buffer_type;

	m_bind_input.push_back(bind);
	return;
}

unsigned int MysqlStatementQuery::GetCount() { return m_row_count; }
unsigned int MysqlStatementQuery::GetAffectCount() { return m_affect_count; }

bool MysqlStatementQuery::Next()
{
	// check row index
	if (m_row_index >= m_row_count)
	{
		End();
		return false;
	}

	// reset index
	m_col_index = 0;
	++ m_row_index;

    if (m_row_index >= m_row_count)
    {
        End();
        return false;
    }
	return true;
}

bool MysqlStatementQuery::ReadBool()
{
	if (m_col_index >= m_col_count)
	{
		CARP_ERROR("m_col_index out of range:" << m_col_index << " >= " << m_col_count);
		return false;
    }
    if (m_row_index >= m_row_count)
    {
        CARP_ERROR("m_row_index out of range:" << m_row_index << " >= " << m_row_count);
        return false;
    }

	MysqlBind& data = m_bind_outputs[m_row_index][m_col_index];

	bool result;
	if (data.value_length < sizeof(result))
	{
		CARP_ERROR("field length is too small:" << data.value_length);
		return false;
	}
	if (data.buffer_type != ALITTLE_MYSQL_TYPE_TINY)
	{
		CARP_ERROR("field type is not ALITTLE_MYSQL_TYPE_TINY, is:" << data.buffer_type);
		return false;
	}
	memcpy(&result, data.buffer.data(), sizeof(result));
	++m_col_index;
	if (m_col_index >= m_col_count) Next();
	return result;
}

char MysqlStatementQuery::ReadChar()
{
    if (m_col_index >= m_col_count)
    {
        CARP_ERROR("m_col_index out of range:" << m_col_index << " >= " << m_col_count);
        return '?';
    }
    if (m_row_index >= m_row_count)
    {
        CARP_ERROR("m_row_index out of range:" << m_row_index << " >= " << m_row_count);
        return '?';
    }

    MysqlBind& data = m_bind_outputs[m_row_index][m_col_index];

    char result;
    if (data.value_length < sizeof(result))
    {
        CARP_ERROR("field length is too small:" << data.value_length);
        return '?';
    }
	if (data.buffer_type != ALITTLE_MYSQL_TYPE_TINY)
	{
		CARP_ERROR("field type is not ALITTLE_MYSQL_TYPE_TINY, is:" << data.buffer_type);
		return '?';
	}
	memcpy(&result, data.buffer.data(), sizeof(result));
	++m_col_index;
	if (m_col_index >= m_col_count) Next();
	return result;
}

short MysqlStatementQuery::ReadShort()
{
	if (m_col_index >= m_col_count)
	{
		CARP_ERROR("out of range:" << m_col_index << " >= " << m_col_count);
		return 0;
    }
    if (m_row_index >= m_row_count)
    {
        CARP_ERROR("m_row_index out of range:" << m_row_index << " >= " << m_row_count);
        return 0;
    }

    MysqlBind& data = m_bind_outputs[m_row_index][m_col_index];

	short result;
	if (data.value_length < sizeof(result))
	{
		CARP_ERROR("field length is too small:" << data.value_length);
		return 0;
	}
	if (data.buffer_type != ALITTLE_MYSQL_TYPE_SHORT)
	{
		CARP_ERROR("field type is not ALITTLE_MYSQL_TYPE_SHORT, is:" << data.buffer_type);
		return 0;
    }
    memcpy(&result, data.buffer.data(), sizeof(result));
    ++m_col_index;
    if (m_col_index >= m_col_count) Next();
    return result;
}

int MysqlStatementQuery::ReadInt()
{
    if (m_col_index >= m_col_count)
    {
        CARP_ERROR("out of range:" << m_col_index << " >= " << m_col_count);
        return 0;
    }
    if (m_row_index >= m_row_count)
    {
        CARP_ERROR("m_row_index out of range:" << m_row_index << " >= " << m_row_count);
        return 0;
    }

    MysqlBind& data = m_bind_outputs[m_row_index][m_col_index];

    int result;
    if (data.value_length < sizeof(result))
    {
        CARP_ERROR("field length is too small:" << data.value_length);
        return 0;
    }
	if (data.buffer_type != ALITTLE_MYSQL_TYPE_LONG)
	{
		CARP_ERROR("field type is not ALITTLE_MYSQL_TYPE_LONG, is:" << data.buffer_type);
		return 0;
    }
    memcpy(&result, data.buffer.data(), sizeof(result));
    ++m_col_index;
    if (m_col_index >= m_col_count) Next();
    return result;
}

long MysqlStatementQuery::ReadLong()
{
    if (m_col_index >= m_col_count)
    {
        CARP_ERROR("out of range:" << m_col_index << " >= " << m_col_count);
        return 0;
    }
    if (m_row_index >= m_row_count)
    {
        CARP_ERROR("m_row_index out of range:" << m_row_index << " >= " << m_row_count);
        return 0;
    }

    MysqlBind& data = m_bind_outputs[m_row_index][m_col_index];

    long result;
    if (data.value_length < sizeof(result))
    {
        CARP_ERROR("field length is too small:" << data.value_length);
        return 0;
    }
	if (data.buffer_type != ALITTLE_MYSQL_TYPE_LONG)
	{
		CARP_ERROR("field type is not ALITTLE_MYSQL_TYPE_LONG, is:" << data.buffer_type);
		return 0;
    }
    memcpy(&result, data.buffer.data(), sizeof(result));
    ++m_col_index;
    if (m_col_index >= m_col_count) Next();
    return result;
}

int MysqlStatementQuery::ReadLongLong()
{
    if (m_col_index >= m_col_count)
    {
        CARP_ERROR("out of range:" << m_col_index << " >= " << m_col_count);
        return 0;
    }
    if (m_row_index >= m_row_count)
    {
        CARP_ERROR("m_row_index out of range:" << m_row_index << " >= " << m_row_count);
        return 0;
    }

    MysqlBind& data = m_bind_outputs[m_row_index][m_col_index];

    long long result;
    if (data.value_length < sizeof(result))
    {
        CARP_ERROR("field length is too small:" << data.value_length);
        return 0;
    }
	if (data.buffer_type != ALITTLE_MYSQL_TYPE_LONGLONG)
	{
		CARP_ERROR("field type is not ALITTLE_MYSQL_TYPE_LONGLONG, is:" << data.buffer_type);
		return 0;
    }
    memcpy(&result, data.buffer.data(), sizeof(result));
    ++m_col_index;
    if (m_col_index >= m_col_count) Next();
    return (int)result;
}

float MysqlStatementQuery::ReadFloat()
{
    if (m_col_index >= m_col_count)
    {
        CARP_ERROR("out of range:" << m_col_index << " >= " << m_col_count);
        return 0;
    }
    if (m_row_index >= m_row_count)
    {
        CARP_ERROR("m_row_index out of range:" << m_row_index << " >= " << m_row_count);
        return 0;
    }

    MysqlBind& data = m_bind_outputs[m_row_index][m_col_index];

    float result;
    if (data.value_length < sizeof(result))
    {
        CARP_ERROR("field length is too small:" << data.value_length);
        return 0;
    }
	if (data.buffer_type != ALITTLE_MYSQL_TYPE_FLOAT)
	{
		CARP_ERROR("field type is not ALITTLE_MYSQL_TYPE_FLOAT, is:" << data.buffer_type);
		return 0;
    }
    memcpy(&result, data.buffer.data(), sizeof(result));
    ++m_col_index;
    if (m_col_index >= m_col_count) Next();
    return result;
}

double MysqlStatementQuery::ReadDouble()
{
    if (m_col_index >= m_col_count)
    {
        CARP_ERROR("out of range:" << m_col_index << " >= " << m_col_count);
        return 0;
    }
    if (m_row_index >= m_row_count)
    {
        CARP_ERROR("m_row_index out of range:" << m_row_index << " >= " << m_row_count);
        return 0;
    }

    MysqlBind& data = m_bind_outputs[m_row_index][m_col_index];

    double result;
    if (data.value_length < sizeof(result))
    {
        CARP_ERROR("field length is too small:" << data.value_length);
        return 0;
    }
	if (data.buffer_type != ALITTLE_MYSQL_TYPE_DOUBLE)
	{
		CARP_ERROR("field type is not ALITTLE_MYSQL_TYPE_DOUBLE, is:" << data.buffer_type);
		return 0;
    }
    memcpy(&result, data.buffer.data(), sizeof(result));
    ++m_col_index;
    if (m_col_index >= m_col_count) Next();
    return result;
}

const char* MysqlStatementQuery::ReadString()
{
    if (m_col_index >= m_col_count)
    {
        CARP_ERROR("out of range:" << m_col_index << " >= " << m_col_count);
        m_temp_string.resize(0);
        return m_temp_string.c_str();
    }
    if (m_row_index >= m_row_count)
    {
        CARP_ERROR("m_row_index out of range:" << m_row_index << " >= " << m_row_count);
		m_temp_string.resize(0);
		return m_temp_string.c_str();
    }

    MysqlBind& data = m_bind_outputs[m_row_index][m_col_index];

    m_temp_string.resize(0);
    const char* result = m_temp_string.c_str();
    if (!data.buffer.empty()) result = data.buffer.data();
    ++m_col_index;
    if (m_col_index >= m_col_count)
    {
        if (m_row_index + 1 >= m_row_count)
        {
            m_temp_string = result;
            result = m_temp_string.c_str();
        }
        Next();
    }
    return result;
}

int MysqlStatementQuery::ReadType()
{
    if (m_col_index >= m_col_count)
    {
        CARP_ERROR("out of range:" << m_col_index << " >= " << m_col_count);
        return -1;
    }
    if (m_row_index >= m_row_count)
    {
        CARP_ERROR("m_row_index out of range:" << m_row_index << " >= " << m_row_count);
        return -1;
    }

    MysqlBind& data = m_bind_outputs[m_row_index][m_col_index];

	if (data.buffer_type == ALITTLE_MYSQL_TYPE_TINY) return MYSQLRT_BOOL;
	if (data.buffer_type == ALITTLE_MYSQL_TYPE_SHORT) return MYSQLRT_SHORT;
	if (data.buffer_type == ALITTLE_MYSQL_TYPE_LONG) return MYSQLRT_INT;
	if (data.buffer_type == ALITTLE_MYSQL_TYPE_LONGLONG) return MYSQLRT_LONGLONG;
	if (data.buffer_type == ALITTLE_MYSQL_TYPE_FLOAT) return MYSQLRT_FLOAT;
	if (data.buffer_type == ALITTLE_MYSQL_TYPE_DOUBLE) return MYSQLRT_DOUBLE;
	return MYSQLRT_STRING;
}

bool MysqlStatementQuery::HasNext()
{
	return m_row_index < m_row_count;
}

} // ALittle
