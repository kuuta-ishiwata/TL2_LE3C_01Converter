#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	
	for (int i = 0; i < argc; i++)
	{
		
		printf(argv[i]);
		printf("\n");
	}
	
	//printf("Hellow,World!\n");
	system("pause");
	return 0;
}