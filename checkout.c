#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

// functions to generate report.
//
struct customerQueue {
	int pos;
        char * customer;
	char * time_spent
	char * time_arrived
};

char * clearAndCopy(char *dest, char* src, int cpySize) {
	//printf("enter clearAndCopy \n");
	memset(dest, 0, MAX_BUFFER_SIZE);
	strncpy(dest, src, cpySize
	//printf("exit clearAndCopy \n");
	return dest;
}

//Simulation with 10 lines.
void checkoutLanes() {
	int i = 0;

	FILE * file = fopen("customers.txt", "r");
	if (file==NULL) {
		printf("no such file.");
	return;
	}

	int c = 0;
	char dat[MAX_BUFFER_SIZE];
	struct customerQueue lane[MAX_CUSTOMER_SIZE+1];
	char temp[MAX_BUFFER_SIZE];

	//initialize struct array
	for( i=0; i < MAX_CUSTOMER_SIZE; i++) {
		lane[i].customer = (char *) malloc(MAX_BUFFER_SIZE);
		lane[i].time_spent = (char *) malloc(MAX_BUFFER_SIZE);
		lane[i].time_arrived = (char *) malloc(MAX_BUFFER_SIZE);
		lane[i].pos = 0;
	}

	while (!feof(file)) {

		memset(dat, 0, sizeof(dat));
		//clear out any left over text
		fgets(dat, sizeof(dat), file);

		if(dat[1] == 0) continue;
		//skip any extra cr/lf at end of line
		if(c >= MAX_CUSTOMER_SIZE) break;
		//file is bigger than array, avoid writing past array size

		if(DEBUG == 1) {
			printf("Customer %s\n", clearAndCopy(temp, dat+CUSTOMER_NUMBER_POS, CUSTOMER_NUMBER_WIDTH));
			printf("Time spent %s\n", clearAndCopy(temp, dat+CUSTOMER_TIME_SPENT_POS, CUSTOMER_TIME_SPENT_WIDTH));
			printf("Time arrived %s\n", clearAndCopy(temp, dat+CUSTOMER_TIME_ARRIVED_POS, CUSTOMER_TIME_ARRIVED_WIDTH));
		}

		lane[c].pos = c+1;
		clearAndCopy(lane[c].customer, dat+CUSTOMER_NUMBER_POS, CUSTOMER_NUMBER_WIDTH);
		clearAndCopy(lane[c].time_spent, dat+CUSTOMER_TIME_SPENT_POS, CUSTOMER_TIME_SPENT_WIDTH);
		clearAndCopy(lane[c].time_arrived, dat+CUSTOMER_TIME_ARRIVED_POS, CUSTOMER_TIME_ARRIVED_WIDTH);
		c++;

	}
	fclose(file);

	for( i=0; i<MAX_CUSTOMER_SIZE; i++) {
		//node not set with customer
		if(lane[i].pos == 0) continue; 
			printf("customer: %s time spent: %s arrived at: %s\n", lane[i].customer, lane[i].time_spent, lane[i].time_arrived);
	}
}

//Simulation with only one line
void bakery() {

}



