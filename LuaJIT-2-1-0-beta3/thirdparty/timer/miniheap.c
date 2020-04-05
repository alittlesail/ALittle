#include "miniheap.h"
#include <stdlib.h>

static int mini_heap_reserve(mini_heap* heap, unsigned int size)
{
    if (heap->capacity >= size) return 1;

    node_info** nodes = 0;

    unsigned int capacity = 0;
    if (heap->capacity == 0)
        capacity = 8;
    else
        capacity = heap->capacity * 2;

    if (capacity < size) capacity = size;

    if (!(nodes = (node_info**)realloc(heap->nodes, capacity * sizeof * nodes)))
        return 0;

    heap->nodes = nodes;
    heap->capacity = capacity;

    return 1;
}

// 从index开始，向上浮
// 1. 从当前节点开始与父节点进行对比
// 2. 如果父节点大于当前节点，那么就交换。否则停止
static void mini_heap_shitup(mini_heap* heap, unsigned int index, node_info* node)
{
    unsigned int parent = (index - 1) / 2;
    while (index > 0 && heap->nodes[parent]->end_time > node->end_time)
    {
        (heap->nodes[index] = heap->nodes[parent])->heap_index = index;
        index = parent;
        parent = (index - 1) / 2;
    }
    (heap->nodes[index] = node)->heap_index = index;
}

// 从index开始，向上浮
// 1. 第一次无条件上浮
// 2. 从当前节点开始与父节点进行对比
// 3. 如果父节点大于当前节点，那么就交换。否则停止
static void mini_heap_shiftup_unconditional(mini_heap* heap, unsigned int index, node_info* node)
{
    unsigned int parent = (index - 1) / 2;
    do
    {
        (heap->nodes[index] = heap->nodes[parent])->heap_index = index;
        index = parent;
        parent = (index - 1) / 2;
    } while (index > 0 && heap->nodes[parent]->end_time > node->end_time);
    (heap->nodes[index] = node)->heap_index = index;
}

static void mini_heap_shiftdown(mini_heap* heap, unsigned int index, node_info* node)
{
    // 选择右子节点
    unsigned int min_child = 2 * (index + 1);
    while (min_child <= heap->size)
    {
        // 如果这个字节点是最后一个节点，或者右节点大于左节点
        // 那么就选择左节点
        min_child -= min_child == heap->size || heap->nodes[min_child]->end_time > heap->nodes[min_child - 1]->end_time;

        // 如果当前节点小于或等于选择的节点，那么就跳出
        if (!(node->end_time > heap->nodes[min_child]->end_time)) {
            break;
        }

        (heap->nodes[index] = heap->nodes[min_child])->heap_index = index;
        index = min_child;
        min_child = 2 * (index + 1);
    }
    (heap->nodes[index] = node)->heap_index = index;
}

mini_heap* mini_heap_create()
{
	mini_heap* heap = (mini_heap*)malloc(sizeof(mini_heap));
	heap->nodes = 0;
	heap->size = 0;
	heap->capacity = 0;
    return heap;
}

void mini_heap_destory(mini_heap* heap)
{
	free(heap->nodes);
	free(heap);
}

unsigned int mini_heap_size(mini_heap* heap)
{
	return heap->size;
}

node_info* mini_heap_top(mini_heap* heap)
{
	if (heap->size == 0) return 0;
	return *heap->nodes;
}

int mini_heap_push(mini_heap* heap, node_info* node)
{
	if (!mini_heap_reserve(heap, heap->size + 1))
		return 0;

	mini_heap_shitup(heap, heap->size++, node);
	return 1;
}

node_info* mini_heap_pop(mini_heap* heap)
{
	if (heap->size == 0) return 0;

	node_info* node = *heap->nodes;
	mini_heap_shiftdown(heap, 0, heap->nodes[--heap->size]);
	node->heap_index = -1;
	return node;
}

int mini_heap_adjust(mini_heap* heap, node_info* node)
{
	if (-1 == node->heap_index)
		return mini_heap_push(heap, node);

	/* The position of e has changed; we shift it up or down
	* as needed.  We can't need to do both. */
	if (node->heap_index > 0 && heap->nodes[(node->heap_index - 1) / 2]->end_time > node->end_time)
		mini_heap_shiftup_unconditional(heap, node->heap_index, node);
	else
		mini_heap_shiftdown(heap, node->heap_index, node);

	return 1;
}

int mini_heap_erase(mini_heap* heap, node_info* node)
{
	if (node->heap_index < 0) return 0;

	node_info* last = heap->nodes[--heap->size];
	/* we replace e with the last element in the heap.  We might need to
	shift it upward if it is less than its parent, or downward if it is
	greater than one or both its children. Since the children are known
	to be less than the parent, it can't need to shift both up and
	down. */
	// 如果不是根节点，并且父节点比最后一个节点大，那么就使用无条件上浮一次，然后依次上浮
	if (node->heap_index > 0 && heap->nodes[(node->heap_index - 1) / 2]->end_time > last->end_time)
		mini_heap_shiftup_unconditional(heap, node->heap_index, last);
	else
		mini_heap_shiftdown(heap, node->heap_index, last);
	node->heap_index = -1;
	return 1;
}
