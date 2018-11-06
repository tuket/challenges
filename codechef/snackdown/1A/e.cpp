#include <iostream>
#include <vector>
#include <limits>

using namespace std;

bool isInf(const vector<int>& v)
{
    const int n = v.size();
    bool inf = true;
    int i;
    for(i=0; i<n; i++)
    {
        if(v[i] != -1)
            break;
    }
    for(int j=i+1; j<n; j++)
    {
        if(v[j] != -1) {
            if(v[i] + (j-i) != v[j])
                return false;
        }
    }
    return true;
}

int solve(const vector<int>& v)
{
    const int n = v.size();
    int minK = 1;
    int maxK = numeric_limits<int>::max();
    for(int x : v) minK = max(minK, x);
    vector<int> B;
    for(int i=0; i<n; i++) if(v[i] != -1) B.push_back(i);
    for(int k=0; k<B.size()-1; k++)
    {
        const int i = B[k];
        const int j = B[k+1];
        const int ij = j - i;
        const int a = v[i];
        const int b = v[j];
        const int c = b - a;
        if(a < b)
        {
            if(ij < c) return -1;
            if(ij == c);
            else if(ij < 2*c) return -1;
            else
                maxK = min(maxK, max(b+1, a+ij-c));
        }
        else if(a > b)
        {
            if(b > ij) return -1;
            maxK = min(maxK, ij-c);
        }
        else // a == b
        {
            if(ij == 1 && (a != 0 || b != 0)) return -1;
            maxK = min(maxK, ij-c);
        }
    }
    for(int k=maxK; k >= minK; k--)
    {
        int o = (v[B[0]] - B[0]) % k;
        bool ok = true;
        for(int i=0; i<n; i++)
        {
            if(v[i] != -1)
            {
                if(v[i] != (o+i)%k) {
                    ok = false;
                    break;
                }
            }
        }
        if(ok) return k;
    }
    return -1;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n;
        cin >> n;
        vector<int> v(n);
        for(int i=0; i<n; i++) {
            cin >> v[i];
            if(v[i] != -1)
                v[i]--;
        }
        if(isInf(v)) {
            cout << "inf" << endl;
        }
        else {
            int res = solve(v);
            if(res == -1)
                cout << "impossible" << endl;
            else
                cout << res << endl;
        }
    }
}