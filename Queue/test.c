#include <stdio.h>
#include "queue.h"

void test_standard()
{
    queue* q = queue_init();
    
    for (int i = 0; i < 4; i++)
        _queue_push(q, 10 + i);
  
    _queue_dot_dump(q);

    queue_dump(q);
    
    for (int j = 0; j < 3; j++)
        _queue_pop(q);
   
    _queue_dot_dump(q);

    queue_destructor(q);
}

void test_debug()
{
#undef NDEBUG
    test_standard();
#define NDEBUG
}

void test_empty_dump()
{
    queue* q = queue_init();
    _queue_push(q, 100);
    _queue_dot_dump(q);
    _queue_pop(q);
    _queue_dot_dump(q);
    queue_destructor(q);
}

void test_empty_pop()
{
    queue* q = queue_init();
    _queue_pop(q);
    queue_destructor(q);
}
