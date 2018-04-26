#include <stdlib.h>
#include "queue.h"


queue *createLane()
{
        queue *q = malloc(sizeof(*q));
        if (!q)
           return NULL;
        q->back = NULL;
        q->front = NULL;
        return q;
}
 
int destroyLane(queue *q)
{
        if (!q)
        	return 0;
        while (!isLaneEmpty(q))
                exitLane(q);
        free(q);
        return 1;
}
 
int isLaneEmpty(queue *q)
{
        if (!q)
           return 1;
        if (!q->front)
           return 1;
        else
           return 0;
}
 
int enterLane(queue *q, qelem_t elem)
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

//Remove customer.
qelem_t exitLane(queue *q)
{
        qnode *prev;
        qelem_t *elem;
        if (isLaneEmpty(q))
            return NULL;
        prev = q->front->prev;
        elem = q->front->elem;
        free(q->front);
        q->front = prev;
        return elem;
}
