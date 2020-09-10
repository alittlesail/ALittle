
#ifndef _ALITTLE_MEMORYPOOL_H_
#define _ALITTLE_MEMORYPOOL_H_

#include <math.h>
#include <list>
#include <vector>

#include "concurrentqueue.h"

namespace ALittle
{

class MemoryPool
{
public:
	/**
	 * construction
	 * @param size: unit size
	 */
	MemoryPool(size_t size)
		: m_unit(size), m_total(0)
	{
	}

	/*
	 * destruction
	 */
	~MemoryPool()
	{
		Clear();
	}

public:
	/**
	 * clear
	 */
	void Clear()
	{
		void* value = 0;
		while (m_list.try_dequeue(value))
			free(value);
	}

	/**
	 * create
	 * @return memory
	 */
	void* Create()
	{
		void* value = 0;
		if (m_list.try_dequeue(value))
			return value;
		m_total += m_unit;
		return malloc(m_unit);
	}

	/**
	 * release
	 * @param memory: memory
	 */
	void Release(void* memory)
	{
		if (!memory) return;
		m_list.enqueue(memory);
	}

	/*
	 * get unit size
	 */
	size_t GetUnitSize() const { return m_unit; }
	size_t GetTotalSize() const { return m_total; }

private:
	// LockFree::Stack<void*> m_list;	// list
	moodycamel::ConcurrentQueue<void*> m_list; // list
	size_t m_unit;						// unit
	size_t m_total;					// total
};

class MemoryPoolGroup
{
#define MEMORY_MAX_SIZE 16		// max unit size (1 << MEMORY_MAX_SIZE)

public:
	static MemoryPoolGroup& Instance()
	{
		static MemoryPoolGroup instance;
		return instance;
	}

private:
	MemoryPoolGroup()
		: m_total_size(0)
		, m_used_size(0)
	{
		// create memory pool
		m_pool_list.reserve(MEMORY_MAX_SIZE);
		for (size_t i = 0; i < MEMORY_MAX_SIZE; ++i)
			m_pool_list.push_back(new MemoryPool(1ull << i));
	}

	~MemoryPoolGroup()
	{
		// release all memory
		size_t size = m_pool_list.size();
		for (size_t i = 0; i < size; ++i)
			delete m_pool_list[i];
		m_pool_list.clear();
	}

public:
	/**
	 * create memory
	 * @param request_size: size
	 * @return memory
	 */
	void* Create(size_t request_size)
	{
		// extend size = request size + sizeof(void*)
		size_t request_size_extend = request_size + sizeof(void*);
		// calc index
		double mi = log((double)request_size_extend) / log((double)2);
		size_t index = (size_t)ceil(mi);

		char* memory = 0;
		// check index
		if (index < m_pool_list.size())
		{
			size_t pre_total_size = m_pool_list[index]->GetTotalSize();
			// create memory
			memory = (char*)m_pool_list[index]->Create();
			size_t next_total_size = m_pool_list[index]->GetTotalSize();
			// copy pool address
			memcpy(memory, (void*)&m_pool_list[index], sizeof(void*));

			m_total_size += next_total_size - pre_total_size;
			m_used_size += m_pool_list[index]->GetUnitSize();
		}
		else
		{
			// malloc
			memory = (char*)malloc(request_size_extend);
			// head set zero
			memset(memory, 0, sizeof(void*));
		}

		// offset memory
		memory += sizeof(void*);

		return memory;
	}

	/**
	 * release memory
	 * @param memory: memory
	 */
	void Release(void* memory)
	{
		if (!memory) return;

		// offset to head
		char* head_memory = (char*)memory - sizeof(void*);

		// get pool
		MemoryPool* pool = 0;
		memcpy((void*)&pool, head_memory, sizeof(void*));
		
		// if pool exist
		if (pool)
		{
			pool->Release(head_memory);
			m_used_size -= pool->GetUnitSize();
		}
		else free(head_memory);
	}

	/**
	 * clear all memroy
	 */
	void Clear()
	{
		size_t size = m_pool_list.size();
		for (size_t i = 0; i < size; ++i)
			m_pool_list[i]->Clear();
	}

	size_t GetTotalSize() const { return m_total_size; }
	size_t GetUsedSize() const { return m_used_size; }

private:
	typedef std::vector<MemoryPool*> MemoryPoolList;
	MemoryPoolList m_pool_list;		// pool list

private:
	size_t m_total_size;		// total memory malloc
	size_t m_used_size;		// used memory
};

} // ALittle

#define g_MemoryPoolGroup ALittle::MemoryPoolGroup::Instance()

#endif // _ALITTLE_LOCKFREE_MEMORYPOOL_H_
