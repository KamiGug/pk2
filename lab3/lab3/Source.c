#include "Header.h"

int main()
{
	start();

	if (_CrtDumpMemoryLeaks())
	{
		printf("\nfok");
	}
	return 0;
}