
#ifndef _ALITTLE_MINIHEAP_H_
#define _ALITTLE_MINIHEAP_H_

typedef struct node_info
{
    struct node_info* next;
    long long end_time;
    int id;
    int heap_index;
    int loop;
    int interval_ms;
} node_info;

typedef struct
{
    node_info** nodes;
    unsigned int size;
    unsigned int capacity;
} mini_heap;

mini_heap* mini_heap_create();
void mini_heap_destory(mini_heap* heap);

unsigned int mini_heap_size(mini_heap* heap);
node_info* mini_heap_top(mini_heap* heap);
int mini_heap_push(mini_heap* heap, node_info* node);
node_info* mini_heap_pop(mini_heap* heap);
int mini_heap_adjust(mini_heap* heap, node_info* node);
int mini_heap_erase(mini_heap* heap, node_info* node);

#endif // _ALITTLE_MINIHEAP_H_