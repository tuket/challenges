#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;

typedef array<int, 256> A;

A operator-(const A& a, const A& b)
{
	A res = a;
	for(int i=0; i<256; i++)
		res[i] -= b[i];
	return res;
}

int countNonZero(const A& a)
{
	int res = 0;
	for(int x : a)
		if(x != 0)
			res++;
	return res;
}

int longestWithK(const string& s, int k)
{
	const int n = s.size();
	vector<A> v(n+1);
	fill(v[0].begin(), v[0].end(), 0);
	for(int i=0; i<n; i++) {
		v[i+1] = v[i];
		char c = s[i];
		v[i+1][c]++;
	}
	int res = 0;
	for(int i=0; i<n; i++) {
		auto it = upper_bound(v.begin()+i, v.end(), k,
		[&](int k, const A& a)
		{
			return k < countNonZero(a - v[i]);
		});
		if(it != v.end()) {
			if(countNonZero(*(it-1)) == k) {
				int len = (int)(it - i - v.begin());
				res = max(res, len);
			}
		}
	}
	return res;
}

int main()
{
	string s = "abcba";
	int k = 2;
	int res = longestWithK(s, k);
	cout << res << endl;
}