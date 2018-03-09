#include <stdio.h>
#include "queue.h"

int main()
{
    test_standard();
    test_empty_dump();
    test_empty_pop();
    return 0;
}

void test_standard()
{
    test();

    queue* q = queue_init();
    
    for (int i = 0; i < 24; i++)
        _queue_push(q, 10 + i);
  
    for_each(q->head, &queue_print);
    printf("\n");
    
    for (int j = 0; j < 22; j++)
        _queue_pop(q);
    
    _queue_dot_dump(q);
    queue_destructor(q);
    
    test();
}

void test_empty_dump()
{
    test();

    queue* q = queue_init();
    _queue_dot_dump(q);
    queue_destructor(q);

    test();
}

void test_empty_pop()
{
    test();

    queue* q = queue_init();
    _queue_pop(q);
    queue_destructor(q);
    
    test();
}
