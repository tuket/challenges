#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main()
{
	int nn;
	cin >> nn;
	for(int kk=1; kk<=nn; kk++)
	{
		int n;
		cin >> n;
		vector<ll> a(n), b(n);
		for(int i=0; i<n; i++)
			cin >> a[i];
		for(int i=0; i<n; i++)
			cin >> b[i];
		sort(a.begin(), a.end());
		sort(b.begin(), b.end(), greater<int>());
		ll res = 0;
		for(int i=0; i<n; i++)
			res += a[i] * b[i];
		cout << "Case #" << kk << ": " << res << endl;
	}
}
