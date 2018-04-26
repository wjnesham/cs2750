#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "queue.h"



int main () {
	srand(time(0));

	int customersCount = 0;
	//5 to 30 customers
	customersCount = (rand() % 26) + 5;

	//report
	printf("Grocery queue simulation.\n");
	printf("0 customers served.\n");
	printf("%d customers remaining.\n", customersCount);

	timeSpent( customersCount );

	loadCustomersFromFile(customersCount);

	grocery(customersCount );

	printf("\n\nBakery queue simulation.\n");
	printf("0 customers served.\n");
	printf("%d customers remaining.\n", customersCount);
	bakery( customersCount);

	return 0;
}

