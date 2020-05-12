#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
	return a < b ? b : a;
}

int testCandidate(int lvlA, int lvlB, const int* startOfLevel, int numLevels)
{
	if(lvlA != lvlB || lvlA < 0 || lvlA >= numLevels)
		return -1;
	return startOfLevel[lvlA];
}

int main()
{
	int nn;
	scanf("%d", &nn);
	for(int kk = 1; kk <= nn; kk++)
	{
		int n;
		scanf("%d", &n);
		int* parent = malloc(sizeof(int) * n * 5);
		for(int i = 0; i < n; i++)
			parent[i] = -1;
		for(int i = 0; i < n; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			if(a < b)
				parent[b] = max(parent[b], a);
			else
				parent[a] = max(parent[a], b);
		}

		int* level = parent + n;
		for(int i = 0; i < n; i++) {
			int l = 0;
			int x = i;
			while(parent[i] != -1) {
				x = parent[x];
				l++;
			}
			level[i] = l;
		}

		int* nodesSortedByLevel = parent + 2*n;
		int numLevels = 0;
		int* startOfLevel = parent + 3*n;
		{
			for(int i = 0; i < n; i++)
				startOfLevel[i] = 0;
			for(int i = 0; i < n; i++) {
				startOfLevel[level[i]]++;
				numLevels = max(numLevels, level[i]);
			numLevels++;

			int lvlStart = 0;
			for(int i = 0; i < numLevels; i++) {
				int newLvlStart = lvlStart + startOfLevel[i];
				startOfLevel[i] = lvlStart;
				lvlStart = newLvlStart;
			}
			startOfLevel[numLevels] = lvlStart;

			int* numInsertedInLevel = parent + 4*n;
			for(int i = 0; i < numLevels; i++)
				numInsertedInLevel[i] = 0;

			for(int i = 0; i < n; i++)
			{
				const int lvl = level[i];
				nodesSortedByLevel[startOfLevel[lvl] + numInsertedInLevel[lvl]] = i;
				numInsertedInLevel[lvl]++;
			}
		}

		int Q;
		scanf("%d", &Q);
		for(int q = 0; q < Q; q++)
		{
			int a, da, b, db;
			scanf("%d %d %d %d", a, da, b, db);
			const int aLvl0 = level[a] - da;
			const int aLvl1 = level[a] + da;
			const int bLvl0 = level[b] - db;
			const int bLvl1 = level[b] + db;
			int indSol = testCandidate(aLvl0, bLvl0);
			if(sol)

		free(parent);
	}
}
