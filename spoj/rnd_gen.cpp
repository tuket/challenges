#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <set>

using namespace std;

int main()
{
	srand(time(0));
	//int nn = 1 + rand() % 10;
	int nn = 10;
	for(int kk = 0; kk < nn; kk++)
	{
		//int n = 1 + rand() % 5;
		int n = 4;
		printf("%d\n", n);
		set<int> used;
		for(int i = 0; i < 2*n; i++)
		{
			int x, y;
			do {
				x = rand() % 10;
				y = rand() % 10;
			} while(used.count(x + n*y));
			used.insert(x + n*y);
			printf("%d %d\n", x, y);
		}
	}
	printf("0\n");
}