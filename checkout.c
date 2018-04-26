/**William Nesham**/

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "queue.h"


#ifndef NULL
#define NULL ((void *) 0)
#endif

#define MAX_BUFFER_SIZE 100
#define MAX_CUSTOMER_SIZE MAX_BUFFER_SIZE
#define DEBUG 0
#define CUSTOMER_NUMBER_POS 10
#define CUSTOMER_TIME_SPENT_POS 24
#define CUSTOMER_TIME_ARRIVED_POS 40
#define CUSTOMER_NUMBER_WIDTH 2
#define CUSTOMER_TIME_SPENT_WIDTH 3
#define CUSTOMER_TIME_ARRIVED_WIDTH 5
#define LANES 10

// functions to generate report.
//
struct customer {
	int pos;
    char * customer;
	char * time_spent;
	char * time_arrived;
};

// prototype
void printLane( struct customer [], int recordCount );

char * clearAndCopy(char *dest, char* src, int cpySize) {
	//printf("enter clearAndCopy \n");
	memset(dest, 0, MAX_BUFFER_SIZE);
	strncpy(dest, src, cpySize);
	//printf("exit clearAndCopy \n");
	return dest;
}

//Simulation with 10 lines.
void checkoutLanes(int customersCount) {
	int i = 0;
	FILE * file = fopen("./customers", "r");
	if (file==NULL) {
		printf("no such file.");
	}

	int c = 0;
	char dat[MAX_BUFFER_SIZE];
	struct customer custArray[MAX_CUSTOMER_SIZE+1];
	char temp[MAX_BUFFER_SIZE];

	//initialize struct array
	for( i=0; i < customersCount; i++) {
		custArray[i].customer = (char *) malloc(MAX_BUFFER_SIZE);
		custArray[i].time_spent = (char *) malloc(MAX_BUFFER_SIZE);
		custArray[i].time_arrived = (char *) malloc(MAX_BUFFER_SIZE);
		custArray[i].pos = 0;
	}

	int offset = 0; // for when customer and/or line change width.
	while (!feof(file)) {

		if(c < 9)
			offset = 0;
		if(c == 9)
			offset = 1;

		memset(dat, 0, sizeof(dat));
		//clear out any left over text
		fgets(dat, sizeof(dat), file);

		if(dat[1] == 0) continue;
		//skip any extra cr/lf at end of line
		if(c >= MAX_CUSTOMER_SIZE) break;



		//offset reads

		custArray[c].pos = c+1;
		clearAndCopy(custArray[c].customer, dat+CUSTOMER_NUMBER_POS, CUSTOMER_NUMBER_WIDTH);
		clearAndCopy(custArray[c].time_spent, dat+CUSTOMER_TIME_SPENT_POS+offset, CUSTOMER_TIME_SPENT_WIDTH);
		clearAndCopy(custArray[c].time_arrived, dat+CUSTOMER_TIME_ARRIVED_POS+offset, CUSTOMER_TIME_ARRIVED_WIDTH);
		c++;

	}
	fclose(file);
	

	//simulate lanes 
	printLane( custArray, customersCount);

	return;
}

void processQueues(queue * customerQueue[]);
void printLane( struct customer allCusts[], int customersCount ) {

	int i;
	queue * customerQueue[LANES];
	// create 10 lanes
	for (i=0; i<LANES; i++) {
		customerQueue[i] = createLane();
	}
	i=0;
	for (int c=0; c < customersCount; c++) {
		printf("Customer %s entered line %d at %s.\n", allCusts[c].customer, i, allCusts[c].time_arrived);
		q_enqueue(customerQueue[i], &allCusts[c]);
		i++;
		if(i == LANES) i=0;
	}

	processQueues(customerQueue);
}

void processQueues(queue * customerQueue[]) {
	struct customer* cust;
	int i;
	for (i=0; i<LANES; i++) {
		while( q_isempty(customerQueue[i]) == 0) {
			cust = (struct customer*)dequeue_cust(customerQueue[i]);
			printf("Customer %s left line.\n", cust->customer);
		}

	}

}

//Simulation with only one line
void bakery( int customersCount ) {
	int i = 0;
		FILE * file = fopen("./customers", "r");
		if (file==NULL) {
			printf("no such file.");
		}

		int c = 0;
			char dat[MAX_BUFFER_SIZE];
			struct customer custArray[MAX_CUSTOMER_SIZE+1];
			char temp[MAX_BUFFER_SIZE];

			//initialize struct array
			for( i=0; i < customersCount; i++) {
				custArray[i].customer = (char *) malloc(MAX_BUFFER_SIZE);
				custArray[i].time_spent = (char *) malloc(MAX_BUFFER_SIZE);
				custArray[i].time_arrived = (char *) malloc(MAX_BUFFER_SIZE);
				custArray[i].pos = 0;
			}

			int offset = 0; // for when customer and/or line change width.
			while (!feof(file)) {

				if(c < 9)
					offset = 0;
				if(c == 9)
					offset = 1;

				memset(dat, 0, sizeof(dat));
				//clear out any left over text
				fgets(dat, sizeof(dat), file);

				if(dat[1] == 0) continue;
				//skip any extra cr/lf at end of line
				if(c >= MAX_CUSTOMER_SIZE) break;



				//offset reads

				custArray[c].pos = c+1;
				clearAndCopy(custArray[c].customer, dat+CUSTOMER_NUMBER_POS, CUSTOMER_NUMBER_WIDTH);
				clearAndCopy(custArray[c].time_spent, dat+CUSTOMER_TIME_SPENT_POS+offset, CUSTOMER_TIME_SPENT_WIDTH);
				clearAndCopy(custArray[c].time_arrived, dat+CUSTOMER_TIME_ARRIVED_POS+offset, CUSTOMER_TIME_ARRIVED_WIDTH);
				c++;

			}
			fclose(file);

	//print stuff

	return;
}

