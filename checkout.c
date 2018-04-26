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

struct customer custArray[MAX_CUSTOMER_SIZE+1];

// prototype
void processGroceryCustomers(int recordCount);
void processCustomersInLanes(queue * customerQueue[]);
void processBakeryLane (queue * customerQueue );

char * clearAndCopy(char *dest, char* src, int cpySize) {
	//printf("enter clearAndCopy \n");
	memset(dest, 0, MAX_BUFFER_SIZE);
	strncpy(dest, src, cpySize);
	//printf("exit clearAndCopy \n");
	return dest;
}

//Simulation with 10 lines.
void loadCustomersFromFile(int customersCount) {
	int i = 0;
	FILE * file = fopen("./customers", "r");
	if (file==NULL) {
		printf("no such file.");
	}

	int c = 0;
	char dat[MAX_BUFFER_SIZE];

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


	return;
}


void processGroceryCustomers(int customersCount ) {

	int i;
	queue * customerQueue[LANES];
	// create 10 lanes
	for (i=0; i<LANES; i++) {
		customerQueue[i] = createLane();
	}
	i=0;
	int c = 0;
	for (c=0; c < customersCount; c++) {
		printf("Customer %s entered line %d at %d.\n", custArray[c].customer, i+1, atoi(custArray[c].time_arrived)+5);
		enterLane(customerQueue[i], &custArray[c]);
		i++;
		if(i == LANES) i=0;
	}

	processCustomersInLanes(customerQueue);
}

void processCustomersInLanes(queue * customerQueue[]) {
	struct customer* cust;
	int i;
	int total = 0;
	int c = 0;
	for (i=0; i<LANES; i++) {
		while( isLaneEmpty(customerQueue[i]) == 0) {
			cust = (struct customer*)exitLane(customerQueue[i]);
			//printf("Customer %s left line %d at %d.\n", cust->customer, i, custArray[i].time_arrived+custArray[i].time_spent);
	//		if( c == 0) total = atoi(cust->time_arrived);
			total += atoi(cust->time_spent);
	//		total += 5;
			c++;
		}
	}
	c++;

	printf("Total time spent by customers in line: %d.\n", total);
	printf("Average time spent by customers in line: %d.\n", total/c);
}

void grocery( int customersCount ) {
	processGroceryCustomers (customersCount );
}

void processBakeryLane (queue * customerQueue) {
	struct customer* cust;
	int i = 0;
	int total = 0;
	while( isLaneEmpty(customerQueue) == 0) {
		cust = (struct customer*)exitLane(customerQueue);
	//	printf("Customer %s left clerk %d at %d. \n", cust->customer, c+1, custArray[i].time_arrived+custArray[i].time_spent);
	//	if( i == 0) total = atoi(cust->time_arrived);
		total += atoi(cust->time_spent);
		total += 5;
		i++;
	}
	i++;
//	if (i == 0) i = 1;

	//avg time spent by customers
	printf("Total time spent by customers at bakery: %d.\n", total);
	printf("Average time spent by customers at bakery: %d.\n", total/i);
}

//Simulation with only one line
void bakery( int customersCount ) {
	int i = 0;
	queue * customerQueue;

	customerQueue = createLane();

	for ( i=0; i<customersCount; i++){
		printf("Customer %s entered bakery at %s.\n", custArray[i].customer, custArray[i].time_arrived);
		enterLane(customerQueue, &custArray[i]);
	}

	processBakeryLane (customerQueue);
	return;
}

