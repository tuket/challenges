#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int nn;
	cin >> nn;
	for(int kk=1; kk<=nn; kk++)
	{
		int N, K;
		cin >> N >> K;
		vector<int> v(N);
		for(int i=0; i<N; i++)
			cin >> v[i];
		sort(v.begin(), v.end(), greater<int>());
		int res = K;
		int x = v[K-1];
		while(res < N && v[res] == x) res++;
		cout << res << endl;
	}
}