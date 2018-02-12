enum {
  ERR_OK,
  ERR_POP_FROM_EMPTY_QUEUE
};

typedef struct node {
  int data;
  struct node* next;
} node;

typedef struct queue {
  node* head;
  node* tail;
} queue;

queue* init           ();
int empty             (queue* q);
void push             (queue* q, int value);
int pop               (queue* q);
void dump             (queue* q);
void destructor       (queue* q);
void queueDotDump     (queue* q);
void queueNodeDotDump (node* node, FILE* file);
