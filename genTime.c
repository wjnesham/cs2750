#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct customer
{
	int arrival;
	int spent;
	int id;
};

void timeSpent (int i) {
	FILE * file;
	//open customers file
	file = fopen ("./customers", "w");
	int a, num;
	//First customer some time between 8am and 11am.
	int t = (rand() % (60*60*3) ) + (60*60*8);
	for (a=0; a<i; a++)
	{
		num = (rand() % 301) + 100;
		//10 seconds between customers max, 5 seconds average.
		t += (rand() % (10) );
		//print to customer data file.
		fprintf( file, "Customer: %d Time spent: %d Arrived at: %d Time left?\n", a+1, num, t);
		
		printf("Customer: %d Arrived at: %d \n", a+1, t);
	}
	fclose(file);
}

