#include <cstdio>
#include <cstdlib>

int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
	{
		printf("Hellow,World!\n");
		printf(argv[i]);
		printf("\n");
	}
	system("\n");
	return 0;
}