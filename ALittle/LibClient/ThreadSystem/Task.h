
#ifndef _ALITTLE_TASK_H_
#define _ALITTLE_TASK_H_

namespace ALittle
{

class Task
{
public:
	/**
	 * execute
	 */
	virtual void Execute() = 0;
	/**
	 * abandon
	 */
	virtual void Abandon() = 0;
	/**
	 * destruction
	 */
	virtual ~Task() { }
};

} // ALittle

#endif // _ALITTLE_TASK_H_
