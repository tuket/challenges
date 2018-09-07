#include <iostream>
#include <vector>
#include <array>
#include <limits>
#include <unordered_set>

using namespace std;

int index(int x, int y) {
    return 3*y + x;
}

long long& a(long long* m, int x, int y)
{
    return m[index(x, y)];
}

vector<vector<int>> groups = {};

void initGroups()
{
    groups.push_back({index(0, 0), index(2, 1), index(1, 2)});
    groups.push_back({index(1, 0), index(0, 1), index(2, 2)});
    groups.push_back({index(2, 0), index(0, 1), index(1, 2)});
    groups.push_back({index(1, 0), index(2, 1), index(0, 2)});

    for(int y=0; y < 3; y++)
    {
        vector<int> v;
        for(int x=0; x<3; x++)
            v.push_back(index(x, y));
        groups.push_back(v);
    }
    for(int y=0; y < 3; y++)
    {
        vector<int> v;
        for(int x=0; x<3; x++)
            v.push_back(index(y, x));
        groups.push_back(v);
    }

    groups.push_back({index(0, 0), index(1, 1), index(2, 2)});
    groups.push_back({index(2, 0), index(1, 1), index(0, 2)});
}

int main()
{
    initGroups();

    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        long long n, A, B, C, D, x, y, M;
        cin >> n >> A >> B >> C >> D >> x >> y >> M;
        array<long long, 9> m = {0};
        a(m.data(), x%3, y%3)++;
        for(int i=0; i<n-1; i++) {
            x = (A*x + B) % M;
            y = (C*y + D) % M;
            a(m.data(), x%3, y%3)++;
        }
        long long res = 0;
        for(const auto& g : groups)
        {
            long long n = 1;
            for(int i : g) n *= m[i];
            res += n;
        }
        for(int i=0; i<9; i++) {
            if(m[i] > 2) res += ((m[i]) * (m[i]-1) * (m[i]-2)) / 6L;
        }
        cout << "Case #" << kk << ": " << res << endl;
    }
}