#include "general.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


int main()
{

int *test,i;
test = calloc(5,sizeof(int));
test =realloc(test,10);
for(i=0;i<10;i++)
	printf("%d\n",test[i]);
return 0;
}
