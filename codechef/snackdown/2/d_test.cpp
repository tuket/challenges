#include <bits/stdc++.h>
 
using namespace std;
 
const int MaxN = (int)1e5 + 10;
const int MOD = (int)1e9 + 7;
const int INF = (int)1e9;

int n, p, q;
int a[MaxN];

bool compare(pair <long long, long long> a, pair <long long, long long> b) {
	return 1LL * a.first * b.second >= 1LL * a.second * b.first;
}

bool can(int x, int y, int z) {
	return a[x] + a[y] > a[z] && a[y] + a[z] > a[x] && a[x] + a[z] > a[y];
}

int main() {
//	freopen("input.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t --> 0) {
		scanf("%d%d%d", &n, &p, &q);
		set < pair < int, int > > s;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			s.insert(make_pair(a[i] * a[i], i));
		}
		if (n < 3) {
			cout << "-1\n";
			continue;
		}
		pair <long long, long long> f = make_pair(-2, 1);
		int dx = -1, dy = -1, dz = -1;
		for (int z = 1; z <= n; ++z) {
			for (int x = 1; x <= n; ++x) {
				for (int y = 1; y <= n; ++y) {
					if (x == y || x == z || z == y || !can(x, y, z)) {
						continue;
					}
					pair <long long, long long> theta = make_pair(a[x] * a[x] + a[z] * a[z] - a[y] * a[y], 2 * a[x] * a[z]);
					if (compare(theta, make_pair(p, q))) {
						if (compare(theta, f)) {
							f = theta;
							dx = x;
							dy = y;
							dz = z;
						}
					}
				}
			}
		}
		if (f.first == -2) {
			cout << "-1\n";
		} else {
			cout << dx << " " << dy << " " << dz << "\n";
		}
	}
	return 0;
}

