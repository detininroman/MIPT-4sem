#ifndef HEADER_H
#define HEADER_H
 
typedef int elem_t;

#define test() printf("================== [%s]\n", __func__);

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
    elem_t data;
    struct node* next;
} node;

typedef struct queue {
    node* head;
    node* tail;
} queue;

typedef struct pop_ret {
    int err_num;
    elem_t value;
} pop_ret;

queue*  queue_init       ();
int     queue_empty      (queue* q);
int     queue_push       (queue* q, int value);
pop_ret queue_pop        (queue* q);
int     queue_print      (node* node, void* ctx);
void    queue_destructor (queue* q);
elem_t  for_each         (queue* q, 
        int (*act)(struct node* elem, void* ctx), void* ctx);
void    test_standard    ();
void    test_for_each    ();
void    test_empty_pop   ();
int     find_number      ();

#endif
