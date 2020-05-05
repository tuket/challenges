#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

int main()
{
	int nn;
	cin >> nn;
	for(int kk = 1; kk <= nn; kk++)
	{
		int n;
		cin >> n;
		vector<bool> lost(n, false);
		for(int i = 0; i < n; i++)
		{
			int a, b, p;
			cin >> a >> b >> p;
			if(p == 1)
				lost[b-1] = true;
			else
				lost[a-1] = true;
		}
		for(int i = 0; i < n; i++) {
			if(!lost[i]) {
				cout << "Case #" << kk << ": " << i+1 << endl;
				break;
			}
		}
	}
}