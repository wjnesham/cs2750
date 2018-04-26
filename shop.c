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

	//report
	printf("0 customers served.\n");
	printf("%d customers remaining.\n", customersCount);

	timeSpent( customersCount );

	checkoutLanes(customersCount);
		

	printf("Bakery queue simulation.\n");
	printf("0 customers served.");
	printf("%d customers remaining.\n", customersCount);
	bakery( customersCount);

	return 0;
}

