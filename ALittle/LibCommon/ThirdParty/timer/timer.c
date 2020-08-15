
#include "timer.h"
#include <stdio.h>

timer* timer_create()
{
    timer* ts = (timer*)malloc(sizeof(timer));
    timer_init(ts);
    return ts;
}

void timer_init(timer* ts)
{
    ts->cur_time = 0;
    ts->max_id = 0;
    ts->heap = mini_heap_create();
    ts->map = kh_init(node_info);
    ts->pool = 0;
    ts->pool_count = 0;
}

void timer_clear(timer* ts)
{
    if (ts->heap)
    {
        mini_heap_destory(ts->heap);
        ts->heap = 0;
    }
    if (ts->map)
    {
        for (khint_t k = kh_begin(ts->map); k != kh_end(ts->map); ++k)
        {
            if (kh_exist(ts->map, k))
                free(kh_value(ts->map, k));
        }
        kh_destroy(node_info, ts->map);
        ts->map = 0;
    }
    while (ts->pool != 0)
    {
        node_info* next = ts->pool->next;
        free(ts->pool);
        ts->pool = next;
    }
    ts->pool_count = 0;
}

void timer_destroy(timer* ts)
{
    timer_clear(ts);
    free(ts);
}

static node_info* timer_node_create(timer* ts)
{
    node_info* node = 0;
    if (ts->pool == 0)
    {
        node = (node_info*)malloc(sizeof(node_info));
    }
    else
    {
        --ts->pool_count;
        node = ts->pool;
        ts->pool = ts->pool->next;
    }

    memset(node, 0, sizeof(node_info));
    return node;
}

static void timer_node_release(timer* ts, node_info* node)
{
    if (ts->pool_count > 1000)
    {
        free(node);
        return;
    }

    node->next = ts->pool;
    ts->pool = node;
    ++ts->pool_count;
}

int timer_add(timer* ts, int delay_ms, int loop, int interval_ms)
{
    node_info* info = timer_node_create(ts);

    info->heap_index = -1;
    if (delay_ms < 0) delay_ms = 0;
    info->end_time = ts->cur_time + delay_ms;
    if (loop <= 0) info->loop = -1;
    else info->loop = loop;
    info->interval_ms = interval_ms;
    if (info->interval_ms <= 0) info->interval_ms = 1;

    int find_count = 1000000;
    do
    {
        // 往前加
        ++ts->max_id;
        // 如果到达最大值，那么回到1开始
        if (ts->max_id >= 0x7FFFFFFF) ts->max_id = 1;

        // 如果没有被使用，那么可以跳出
        khint_t node_it = kh_get(node_info, ts->map, ts->max_id);
        if (node_it == kh_end(ts->map))
        {
            info->id = ts->max_id;
            break;
        }

        // 继续查找
        --find_count;
    } while (find_count > 0);

    if (!mini_heap_push(ts->heap, info))
    {
        timer_node_release(ts, info);
        return 0;
    }

    int ret = 0;
    khint_t node_it = kh_put(node_info, ts->map, info->id, &ret);
    if (!ret) kh_del(node_info, ts->map, node_it);
    kh_value(ts->map, node_it) = info;
    return info->id;
}

int timer_remove(timer* ts, int id)
{
    khint_t node_it = kh_get(node_info, ts->map, id);
    if (node_it == kh_end(ts->map)) return 0;
    node_info* node = kh_value(ts->map, node_it);
    if (node != 0)
    {
        mini_heap_erase(ts->heap, node);
        timer_node_release(ts, node);
    }
    kh_del(node_info, ts->map, node_it);
    return 1;
}

void timer_update(timer* ts, int frame_ms)
{
    ts->cur_time += frame_ms;
}

int timer_poll(timer* ts)
{
    node_info* info = mini_heap_top(ts->heap);
    if (info == 0) return 0;

    if (info->end_time > ts->cur_time)
        return 0;

    mini_heap_pop(ts->heap);

    // 处理无限循环
    if (info->loop < 0)
    {
        info->end_time = info->end_time + info->interval_ms;
        mini_heap_push(ts->heap, info);
        return info->id;
    }
    // 如果还有次数，那么就扣除次数
    else if (info->loop > 1)
    {
        --info->loop;
        info->end_time = info->end_time + info->interval_ms;
        mini_heap_push(ts->heap, info);
        return info->id;
    }
    // 次数已经用完，那么就直接删除
    else
    {
        int id = info->id;
        khint_t node_it = kh_get(node_info, ts->map, id);
        if (node_it != kh_end(ts->map))
            kh_del(node_info, ts->map, node_it);
        timer_node_release(ts, info);
        return -id;
    }
}
