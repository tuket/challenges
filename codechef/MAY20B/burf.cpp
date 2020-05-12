#include <stdio.h>
#include <stdlib.h>

bool isSorted(int* v)
{
	for(int i = 0; i < 3; i++)
		if(v[i] > v[i+1])
			return false;
	return true;
}

int main()
{
	int v[4] = {0, 2, 1, 3};
	do{
		int i0 = rand() % 4;
		int i1 = rand() % 4;
		while(i1 == i0) {
			i1 = rand() % 4;
		}
		int i2 = rand() % 4;
		int aux = v[i0];
		v[i0] = v[i1];
		v[i1] = v[i2];
		v[i2] = aux;
		printf("%d %d %d\n", i0, i1, i2);
		printf("%d %d %d %d\n", v[0], v[1], v[2], v[3]);
	}
	while(!isSorted(v));
}