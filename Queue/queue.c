#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

#define NDEBUG

queue* queue_init()
{
    queue* temp = calloc (1, sizeof (*temp));
    temp->head = NULL;
    temp->tail = NULL;
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
    temp->next = NULL;

    if (!queue_empty(q)) {
        q->tail->next = temp;
        q->tail = temp;
    }
    else
        q->head = q->tail = temp;
    
    return Q_ERR_OK;
}

pop_ret queue_pop(queue* q)
{
    pop_ret ret_struct = {};
   
    if (!queue_empty(q)) {
        node* temp = q->head;
        ret_struct.value = q->head->data;
        printf ("Pop: %d\n", ret_struct.value);
        q->head = q->head->next;
        free (temp);
    } else {
        printf ("You cannot pop from empty queue!\n");
        ret_struct.err_num = Q_ERR_EMPTY_QUEUE;
    }
    return ret_struct;
}

void queue_dump(queue* q)
{
    node* temp = q->head;
    while (temp) {
        printf ("[%d] ", temp->data);
        temp = temp->next;
    }
    printf ("\n");
}

void queue_destructor(queue* q)
{
    node* temp = q->head;
    while(temp) {
        temp = q->head->next;
        free(q->head);
        q->head = temp;
    }
    free(q);
}

int queue_dot_dump(queue* q)
{
    if (queue_empty(q))
        return Q_ERR_EMPTY_QUEUE;

    FILE* file_ptr = fopen("./Dot/queue_dump.gv", "w");

    fprintf(file_ptr, "digraph graf {\n"
                    "rankdir=\"LR\";");
    queue_node_dot_dump(q->head, file_ptr);
    fprintf(file_ptr, "}");

    fclose(file_ptr);

    system("dot ./Dot/queue_dump.gv -Tpng -o ./Dot/queue_dump.png");
    system("xdot ./Dot/queue_dump.gv");

    return Q_ERR_OK;
}

void queue_node_dot_dump (node* node, FILE* file)
{
    fprintf(file, "Node_%p [label=\"", node);

#ifndef NDEBUG
    if(!node->next)
        fprintf(file, "[TAIL]\n");

    fprintf(file, "Node: [%p]\\l"
                  "Next: [%p]\\l"
                  "Data: %d\\l \"]\n", 
                   node, node->next, node->data);
#else
    fprintf (file, "%d\\l \"]\n", node->data);
#endif

    if (node->next) {
        fprintf(file, "Node_%p->Node_%p\n", node->next, node);
        queue_node_dot_dump(node->next, file);
    }
}

int main()
{
    test_standard();
    test_debug();
    test_empty_dump();
    test_empty_pop();
    return 0;
}
