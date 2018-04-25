#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "queue.h"



int main () {
	srand(time(0));

	int customersCount = 0;
	//5 to 31 customers
	customersCount = (rand() % 10) + 5;

	timeSpent( customersCount );

	checkoutLanes(customersCount);
		
	return 0;
}

