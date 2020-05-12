#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void print(const vector<int>& v) {
	for(int x : v)
		cout << x << " ";
	cout << endl;
}

int main()
{
	int nn;
	cin >> nn;
	for(int kk = 1; kk <= nn; kk++)
	{
		int N, Q;
		cin >> N >> Q;
		string s;
		cin >> s;
		vector<int> v(26, 0);
		for(char c : s)
			v[c-'a']++;
		for(int q = 0; q < Q; q++)
		{
			int C;
			cin >> C;
			int res = 0;
			for(int i = 0; i < 26; i++)
				res += max(0, v[i] - C);
			cout << res << endl;
		}
	}
}
