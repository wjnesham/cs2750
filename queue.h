/*
 * queue.h
 *
 *  Created on: Apr 23, 2018
 *      Author: williamnesham
 */

void timeSpent (int i);
void grocery( int customersCount );
void bakery( int customersCount );
void loadCustomersFromFile(int customersCount);

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
queue *createLane(void);

/*
 *  * Destroy an queue.
 *   * Returns 1 on success, and otherwise 0.
 *    */
int destroyLane(queue *q);


//  * Check if queue is empty.
// Returns 1 if the queue is empty, and otherwise 0.
int isLaneEmpty(queue *q);

 //*  * Add element to queue.
 //*   * Returns 1 on success, and otherwise 0.
int enterLane(queue *q, qelem_t elem);

// *  * Remove element from queue, and return it.
qelem_t exitLane(queue *q);


