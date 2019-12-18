#include <stdio.h>
int main()
{

	FILE* fp;

	if ((fp = fopen("test.txt", "r")) != NULL)
		printf("otoreno");
	else
		printf("nije otvoreno");

	return 0;
}