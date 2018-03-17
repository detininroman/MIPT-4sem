#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
 
queue* queue_init()
{
    queue* temp = calloc (1, sizeof(*temp));
    if (!temp)
        ERR(calloc);
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

int queue_pop(queue* q, int* value)
{
   
    if (!queue_empty(q)) {
        node* temp = q->head;
        *value = q->head->data;
        //printf("Pop: %d\n", *value);
        q->head = q->head->next;
        free (temp);
        return Q_ERR_OK;
    } else
        return Q_ERR_EMPTY_QUEUE;
}

int queue_print(node* node, void* ctx)
{
    printf("[%d]->", node->data);
    return 0;
}

int find_number(node* node, void* ctx)
{
    int num = atoi((char*) ctx);
    if (node->data == num)
        return num;
    else 
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

int for_each(queue* q, 
        int (*act)(struct node* elem, void* ctx), void* ctx)
{
    node* temp = q->head;
    while (temp) {
        int res = act(temp, ctx); 
        if (res)
            return res;
        temp = temp->next;
    }
    return 0;
}
