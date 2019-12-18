#include <stdio.h>
#pragma warning(disable : 4996)
int main()
{
	FILE* fp;

	if ((fp = fopen("../config files/test.txt", "r")) != NULL)
		printf("otoreno");
	else
		printf("nije otvoreno");

	return 0;
}