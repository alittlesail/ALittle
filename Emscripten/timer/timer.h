
#ifndef _ALITTLE_TIMER_H_
#define _ALITTLE_TIMER_H_

#include "miniheap.h"
#include "klib/khash.h"

KHASH_MAP_INIT_INT(node_info, node_info*)

typedef struct
{
    long long cur_time;
    int max_id;
    mini_heap* heap;
    node_info* pool;
    int pool_count;
    khash_t(node_info)* map;
} timer;


timer* timer_create();
void timer_destroy(timer* ts);

// 添加定时器
int timer_add(timer* ts, int delay_ms, int loop, int interval_ms);
// 移除定时器
int timer_remove(timer* ts, int id);
// 更新时间
void timer_update(timer* ts, int frame_ms);
// 取出超时的定时器ID
// 如果返回0，说明没有超时的定时器
// 如果返回正数，说明定时器超时，并且等待下次循环
// 如果返回负数，说明定时器超时，并且定时器已被删除
int timer_poll(timer* ts);

#endif // _ALITTLE_TIMER_H_
