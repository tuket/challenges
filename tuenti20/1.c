#include <stdio.h>

int main()
{
	int nc;
	scanf("%d", &nc);
	for(int kk = 1; kk <= nc; kk++)
	{
		char c[2];
		scanf(" %c %c", c, c+1);
		char r;
		if(c[0] == c[1])
			r = '-';
		else {
			if(c[0] == 'R' && c[1] == 'P' ||
			   c[1] == 'R' && c[0] == 'P')
			   r = 'P';
			if(c[0] == 'S' && c[1] == 'P' ||
			   c[1] == 'S' && c[0] == 'P')
			   r = 'S';
			if(c[0] == 'S' && c[1] == 'R' ||
			   c[1] == 'S' && c[0] == 'R')
			   r = 'R';
	   }
	   printf("Case #%d: %c\n", kk, r);
	}
}