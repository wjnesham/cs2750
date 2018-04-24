#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "queue.h"



int main () {
	srand(time(0));

	int customers = 0;
	//5 to 31 customers
	customers = (rand() % 10) + 5;

	timeSpent( customers );

	checkoutLanes();
		
	return 0;
}

