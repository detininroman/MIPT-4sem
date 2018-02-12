#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include "header.h"

#define NDEBUG

queue* init()
{
  queue* temp = calloc (1, sizeof (queue));
  temp->head = NULL;
  temp->tail = NULL;
  return temp;
}

int empty(queue* q)
{
  return (!q->head);
}

void push(queue* q, int value)
{
  node* temp = calloc (1, sizeof(node));
  temp->data = value;
  temp->next = NULL;

  if (!empty(q))
  {
    q->tail->next = temp;
    q->tail = temp;
  }
  else
    q->head = q->tail = temp;
}

int pop(queue* q)
{
  int val = 0;
  if (!empty(q))
  {
    node* temp = q->head;
    val = q->head->data;
    printf ("Pop: %d\n", val);
    q->head = q->head->next;
    free (temp);
  }
  else
  {
    printf ("You cannot pop from empty queue!\n");
    errno = ERR_POP_FROM_EMPTY_QUEUE;
  }
  return val;
}

void dump(queue* q)
{
  node* temp = q->head;
  while (temp)
  {
    printf ("%d ", temp->data);
    temp = temp->next;
  }
  printf ("\n");
}

void destructor(queue* q)
{
  node* temp = q->head;
    while(temp != NULL)
    {
      temp = q->head->next;
      free(q->head);
      q->head = temp;
    }
  free(q);
}

void queueDotDump(queue* q)
{
  FILE* file_ptr = fopen("./Dot/queue_dump.gv", "w");

  fprintf(file_ptr, "digraph graf {\n"
                    "rankdir=\"LR\";");
  queueNodeDotDump(q->head, file_ptr);
  fprintf(file_ptr, "}");

  fclose (file_ptr);

  system ("dot ./Dot/queue_dump.gv -Tpng -o ./Dot/queue_dump.png");
  system ("xdot ./Dot/queue_dump.gv");
}

void queueNodeDotDump (node* node, FILE* file)
{
  fprintf(file, "Node_%p [label=\"", node);

#ifndef NDEBUG
  if(!node->next)
    fprintf(file, "[TAIL]\n");

  fprintf(file, "Node: [%p]\\l"
                "Next: [%p]\\l"
                "Data: %d\\l \"]\n", node, node->next, node->data);
#else
  fprintf (file, "%d\\l \"]\n", node->data);
#endif

  if (node->next)
  {
    fprintf(file, "Node_%p->Node_%p\n", node->next, node);
    queueNodeDotDump(node->next, file);
  }
}

int main()
{
  queue* q1 = init();

  push (q1, 10);

  queueDotDump(q1);

  if (pop(q1) == 0 && errno == ERR_POP_FROM_EMPTY_QUEUE)

  dump(q1);
  destructor(q1);

  return 0;
}
