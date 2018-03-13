#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

queue* queue_init()
{
    queue* temp = calloc (1, sizeof(*temp));
    return temp;
}

int queue_empty(queue* q)
{
    return (!q->head);
}

int queue_push(queue* q, int value)
{
    node* temp = calloc (1, sizeof(*temp));
    if (!temp)
       return Q_ERR_MEM_ALLOC;

    temp->data = value;

    if (!queue_empty(q)) {
        q->tail->next = temp;
        q->tail = temp;
    } else {
        q->head = temp;
        q->tail = temp;
    }
    
    return Q_ERR_OK;
}

pop_ret queue_pop(queue* q)
{
    pop_ret ret_struct = {};
   
    if (!queue_empty(q)) {
        node* temp = q->head;
        ret_struct.value = q->head->data;
        //printf("Pop: %d\n", ret_struct.value);
        q->head = q->head->next;
        free (temp);
    } else
        ret_struct.err_num = Q_ERR_EMPTY_QUEUE;
    
    return ret_struct;
}

int queue_print(node* node, void* ctx)
{
    printf("[%d]->", node->data);
    return 0;
}

void queue_destructor(queue* q)
{
    node* temp = q->head;
    while (temp) {
        temp = q->head->next;
        free(q->head);
        q->head = temp;
    }
    free(q);
}

elem_t for_each(queue* q, 
        elem_t (*act)(struct node* elem, void* ctx), void* ctx)
{
    node* temp = q->head;
    while (temp) {
        elem_t res = act(temp, ctx); 
        if (res)
            return res;
        temp = temp->next;
    }
    return 0;
}
