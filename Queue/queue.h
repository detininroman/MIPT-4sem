#ifndef HEADER_H
#define HEADER_H
 
#define test()  printf("================== [%s]\n", __func__);

#define ERR(func) fprintf(stderr, "Error: " #func "\n");

#define _queue_push(q, val) {              \
    if (queue_push(q, val) != Q_ERR_OK)    \
        ERR(push);                         \
}

#define _queue_pop(q) {                    \
    if (queue_pop(q).err_num != Q_ERR_OK)  \
        ERR(pop);                          \
}

#define _queue_dot_dump(q) {               \
    if (queue_dot_dump(q) != Q_ERR_OK)     \
        ERR(dot_dump);                     \
}

enum QUEUE_ERRORS{
    Q_ERR_OK = 0,
    Q_ERR_MEM_ALLOC,
    Q_ERR_EMPTY_QUEUE
};

typedef struct node {
    int data;
    struct node* next;
} node;

typedef struct queue {
    node* head;
    node* tail;
} queue;

typedef struct pop_ret {
    int err_num;
    int value;
} pop_ret;

queue*  queue_init          ();
int     queue_empty         (queue* q);
int     queue_push          (queue* q, int value);
pop_ret queue_pop           (queue* q);
void    queue_print         (node* node);
void    queue_destructor    (queue* q);
int     queue_dot_dump      (queue* q);
void    queue_node_dot_dump (node* node, FILE* file);
void    for_each            (node* node, void (*func) (struct node* node));

void    test_standard       ();
void    test_empty_dump     ();
void    test_empty_pop      ();

#endif
