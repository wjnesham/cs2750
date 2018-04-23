#include <stdlib.h>

typedef void *qelem_t;

typedef struct qnode
{
        qelem_t elem;
        struct qnode *next;
        struct qnode *prev;
}qnode;
 
typedef struct
{
        qnode *back;
        qnode *front;
}queue;
 
/*
 *  * Create an queue.
 *   */
queue *q_create(void);
 
/*
 *  * Destroy an queue.
 *   * Returns 1 on success, and otherwise 0.
 *    */
int q_destroy(queue *q);
 

//  * Check if queue is empty.
// Returns 1 if the queue is empty, and otherwise 0.
int q_isempty(queue *q);
 
 //*  * Add element to queue.
 //*   * Returns 1 on success, and otherwise 0.
int q_enqueue(queue *q, qelem_t elem);
 
// *  * Remove element from queue, and return it.
qelem_t q_dequeue(queue *q);



queue *q_create()
{
        queue *q = malloc(sizeof(*q));
        if (!q)
                return NULL;
        q->back = NULL;
        q->front = NULL;
        return q;
}
 
int q_destroy(queue *q)
{
        if (!q)
                return 0;
	// ?
        while (!q_isempty(q))
                q_dequeue(q);// ??
        free(q);
        return 1;
}
 
int q_isempty(queue *q)
{
        if (!q)
                return 1;
        if (!q->front)
                return 1;
        else
                return 0;
}
 
int q_enqueue(queue *q, qelem_t elem)
{
        qnode *new = malloc(sizeof(*new));
        if (!new)
                return 0;
        if (!q || !elem)
        {
                free(new);
                return 0;
        }
        new->elem = elem;
        new->next = q->back;
        new->prev = NULL;
        if (q->back)
                q->back->prev = new;
        q->back = new;
        if (!q->front)
                q->front = new;
        return 1;
}
 
qelem_t q_dequeue(queue *q)
{
        qnode *prev;
        qelem_t *elem;
        if (q_isempty(q))
                return NULL;
        prev = q->front->prev;
        elem = q->front->elem;
        free(q->front);
        q->front = prev;
        return elem;
}
