#ifndef HEADER_H
#define HEADER_H
 
#define test() do { printf("================== [%s]\n", __func__); } while (0)

#define ERR(func) do { fprintf(stderr, "Error: " #func "\n"); } while (0)

#define _queue_push(q, val)                  \
    do {                                     \
        if (queue_push(q, val) != Q_ERR_OK)  \
            ERR(push);                       \
    } while (0)   

#define _queue_pop(q, val)                   \
    do {                                     \
        if (queue_pop(q, val) != Q_ERR_OK)   \
            ERR(pop);                        \
    } while (0)   

enum QUEUE_ERRORS {
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

queue*   queue_init       ();
int      queue_empty      (queue* q);
int      queue_push       (queue* q, int value);
int      queue_pop        (queue* q, int* value);
int      queue_print      (node* node, void* ctx);
void     queue_destructor (queue* q);
int      for_each         (queue* q, 
         int (*act)(struct node* elem, void* ctx), void* ctx);
void     test_standard    ();
void     test_for_each    ();
void     test_empty_pop   ();
int      find_number      ();

#endif
