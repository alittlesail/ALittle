
#ifndef _ALITTLE_MYSQLSTATEMENTQUERY_H_
#define _ALITTLE_MYSQLSTATEMENTQUERY_H_

#include <string>
#include <vector>

#include "MysqlConnection.h"

namespace ALittle
{

enum ALittle_enum_field_types {
    ALITTLE_MYSQL_TYPE_DECIMAL, ALITTLE_MYSQL_TYPE_TINY,
    ALITTLE_MYSQL_TYPE_SHORT, ALITTLE_MYSQL_TYPE_LONG,
    ALITTLE_MYSQL_TYPE_FLOAT, ALITTLE_MYSQL_TYPE_DOUBLE,
    ALITTLE_MYSQL_TYPE_NULL, ALITTLE_MYSQL_TYPE_TIMESTAMP,
    ALITTLE_MYSQL_TYPE_LONGLONG, ALITTLE_MYSQL_TYPE_INT24,
    ALITTLE_MYSQL_TYPE_DATE, ALITTLE_MYSQL_TYPE_TIME,
    ALITTLE_MYSQL_TYPE_DATETIME, ALITTLE_MYSQL_TYPE_YEAR,
    ALITTLE_MYSQL_TYPE_NEWDATE, ALITTLE_MYSQL_TYPE_VARCHAR,
    ALITTLE_MYSQL_TYPE_BIT,
    ALITTLE_MYSQL_TYPE_TIMESTAMP2,
    ALITTLE_MYSQL_TYPE_DATETIME2,
    ALITTLE_MYSQL_TYPE_TIME2,
    ALITTLE_MYSQL_TYPE_NEWDECIMAL = 246,
    ALITTLE_MYSQL_TYPE_ENUM = 247,
    ALITTLE_MYSQL_TYPE_SET = 248,
    ALITTLE_MYSQL_TYPE_TINY_BLOB = 249,
    ALITTLE_MYSQL_TYPE_MEDIUM_BLOB = 250,
    ALITTLE_MYSQL_TYPE_LONG_BLOB = 251,
    ALITTLE_MYSQL_TYPE_BLOB = 252,
    ALITTLE_MYSQL_TYPE_VAR_STRING = 253,
    ALITTLE_MYSQL_TYPE_STRING = 254,
    ALITTLE_MYSQL_TYPE_GEOMETRY = 255
};

class MysqlStatementQuery
{
public:
	MysqlStatementQuery();
	~MysqlStatementQuery();

//===================================================================
public:
	/* set sql string
	 * @param sql: set sql string
	 * notice:!!!!  if you use SUM, then please used like this CAST(IFNULL(SUM(XXXX),0) AS UNSIGNED)
	 *				and use longlong to receive the value
	 * notice:!!!!  if you use COUNT, then please use longlong to receive the value
	 */
	void SetSQL(const char* sql);
	const char* GetSQL() const;

public:
	/* set connect
	 * @param conn: connect object
	 */
	void SetConnection(MysqlConnection* conn);

//===================================================================
public:
	/* execute
	 * @return succeed or not
	 */
	bool Execute(std::string& reason);
	/* clear
	 */
	void Clear();

//===================================================================
public:
	/* common bing for input
	 * @param ptr: pointer of input param
	 * @param size: size of input param
	 * @param is_unsigned: unsigned or not
	 * @param type: input type
	 */
	void CommonBindForInput(void* ptr, size_t size, bool is_unsigned, ALittle_enum_field_types type);

public:
	void PushBool (bool param)						{ CommonBindForInput((void*)&param, sizeof(bool),				false,	ALITTLE_MYSQL_TYPE_TINY); }
	void PushChar (char param)						{ CommonBindForInput((void*)&param, sizeof(char),				false,	ALITTLE_MYSQL_TYPE_TINY); }
	void PushUChar (unsigned char param)			{ CommonBindForInput((void*)&param, sizeof(unsigned char),		true,	ALITTLE_MYSQL_TYPE_TINY); }
	void PushShort (short param)					{ CommonBindForInput((void*)&param, sizeof(short),				false,	ALITTLE_MYSQL_TYPE_SHORT); }
	void PushUShort (unsigned short param)			{ CommonBindForInput((void*)&param, sizeof(unsigned short),		true,	ALITTLE_MYSQL_TYPE_SHORT); }
	void PushInt (int param)						{ CommonBindForInput((void*)&param, sizeof(int),				false,	ALITTLE_MYSQL_TYPE_LONG); }
	void PushUInt (unsigned int param)				{ CommonBindForInput((void*)&param, sizeof(unsigned int),		true,	ALITTLE_MYSQL_TYPE_LONG); }
	void PushLong (long param)						{ CommonBindForInput((void*)&param, sizeof(long),				false,	ALITTLE_MYSQL_TYPE_LONG); }
	void PushULong (unsigned long param)			{ CommonBindForInput((void*)&param, sizeof(unsigned long),		true,	ALITTLE_MYSQL_TYPE_LONG); }
	void PushLongLong(long long param)				{ CommonBindForInput((void*)&param, sizeof(long long),			false,	ALITTLE_MYSQL_TYPE_LONGLONG); }
	void PushULongLong(unsigned long long param)	{ CommonBindForInput((void*)&param, sizeof(unsigned long long),	true,	ALITTLE_MYSQL_TYPE_LONGLONG); }
	void PushFloat(float param)						{ CommonBindForInput((void*)&param, sizeof(float),				false,	ALITTLE_MYSQL_TYPE_FLOAT); }
	void PushDouble(double param)					{ CommonBindForInput((void*)&param, sizeof(double),				false,	ALITTLE_MYSQL_TYPE_DOUBLE); }
	void PushString(const char* param)				{ CommonBindForInput((void*)param, strlen(param),				false,	ALITTLE_MYSQL_TYPE_STRING); }

//===================================================================
public:
    enum ReadTypes
    {
        MYSQLRT_BOOL = 0,
        MYSQLRT_SHORT = 1,
        MYSQLRT_INT = 2,
        MYSQLRT_LONGLONG = 3,
        MYSQLRT_FLOAT = 4,
        MYSQLRT_DOUBLE = 5,
        MYSQLRT_STRING = 6
    };

	/* get total count
	 * @return total count
	 */
	unsigned int GetCount();

	/* get affect count
	 * @return affect count
	 */
	unsigned int GetAffectCount();
	
	/* has next
	 * @return succeed or not
	 */
	bool HasNext();

	/* get next record
	 * @return succeed or not
	 */
	bool Next();

//===================================================================
	bool ReadBool();

	char ReadChar();

	short ReadShort();

	int ReadInt();

	long ReadLong();

	int ReadLongLong();

	float ReadFloat();

	double ReadDouble();

	const char* ReadString();

	int ReadType();

//===================================================================
private:
	/* start execute sql
	 * @return succeed or not
	 */
	bool Begin(std::string& reason);
	/* clear
	 */
	void End();

private:
	void Reset();

private:
	MysqlConnection* m_conn;		// connect object
	
private:
	std::string m_sql;				// SQL string
	int m_input_index;
	unsigned int m_col_index;
	unsigned int m_row_index;
	unsigned int m_row_count;
	unsigned int m_col_count;
	unsigned int m_affect_count;
	std::string m_temp_string;

    std::vector<MYSQL_BIND> m_bind_input;

	struct MysqlBind
	{
		ALittle_enum_field_types buffer_type;	/* buffer type */
		unsigned long value_length = 0;
		std::vector<char> buffer;
	};
	std::vector<std::vector<MysqlBind>> m_bind_outputs;

private:
	bool m_need_reset;				// need reset or not
};

} // ALittle

#endif // _ALITTLE_MYSQLSTATEMENTQUERY_H_
