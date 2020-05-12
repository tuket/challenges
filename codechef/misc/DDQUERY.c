#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int max(int a, int b) {
	return a < b ? b : a;
}

void recurse(int lvl, int targetLvl, int node, int prevNode, int n,
	const int* parent, const int* children, const int* childrenOf, int* markBoard)
{
	if(lvl == targetLvl) {
		markBoard[node] ++;
		return;
	}
	if(parent[node] != -1 && parent[node] != prevNode)
		recurse(lvl+1, targetLvl, parent[node], node, n, parent, children, childrenOf, markBoard);
	for(int i = childrenOf[node]; i < childrenOf[node+1]; i++)
		if(children[i] != prevNode)
			recurse(lvl+1, targetLvl, children[i], node, n, parent, children, childrenOf, markBoard);
}

int main()
{
	int nn;
	scanf("%d", &nn);
	for(int kk = 1; kk <= nn; kk++)
	{
		int n, Q;
		scanf("%d %d", &n, &Q);
		int* parent = malloc(sizeof(int) * n*4 + 1);
		for(int i = 0; i < n; i++)
			parent[i] = -1;
		for(int i = 0; i < n-1; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			a--; b--;
			if(a < b)
				parent[b] = max(parent[b], a);
			else
				parent[a] = max(parent[a], b);
		}

		int* children = parent + n;
		int* childrenOf = parent + 2*n;
		{
			for(int i = 0; i < n; i++)
				childrenOf[i] = 0;
			for(int i = 1; i < n; i++)
				childrenOf[parent[i]]++;
			int j = 0;
			for(int i = 0; i < n; i++) {
				const int numChildren = childrenOf[i];
				childrenOf[i] = j;
				j += numChildren;
			}
			childrenOf[n] = j;
			int* childrenInserted = parent + n*3 + 1;
			for(int i = 0; i < n; i++)
				childrenInserted[i] = 0;
			for(int i = 0; i < n; i++)
			if(parent[i] != -1) {
				children[childrenOf[parent[i]] + childrenInserted[parent[i]]] = i;
				childrenInserted[parent[i]]++;
			}
		}

		/*printf("parent: ");
		for(int i = 0; i < n; i++)
			printf("%d ", parent[i]);
		printf("\n");*/

		for(int q = 0; q < Q; q++)
		{
			int a, da, b, db;
			scanf("%d %d %d %d", &a, &da, &b, &db);
			a--; b--;
			int* markBoard = parent + n*3 + 1;
			for(int i = 0; i < n; i++)
				markBoard[i] = 0;
			recurse(0, da, a, -1, n, parent, children, childrenOf, markBoard);
			recurse(0, db, b, -1, n, parent, children, childrenOf, markBoard);
			int result = -1;
			for(int i = 0; i < n; i++) {
				if(markBoard[i] == 2) {
					result = i;
					break;
				}
			}
			printf("%d\n", result == -1 ? -1 : result+1);
		}

		free(parent);
	}
}
