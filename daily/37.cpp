#include <iostream>
#include <vector>
#include <unordered_set>
#include <numeric>

using namespace std;

class Ind
{
public:
    Ind(int n, int mx)
        : mx(mx)
    {
        ind.resize(n);
        iota(ind.begin(), ind.end(), 0);
    }

    bool next()
    {
        const int n = ind.size();
        int i = n-1;
        for(; i >= 0; i--)
        {
            int j = n-i-1;
            ind[i]++;
            if(ind[i] < mx-j) {
                break;
            }
        }
        if(i == -1)
            return false;
        int x = ind[i] + 1;
        for(i++; i<n; i++, x++)
            ind[i] = x;
        return true;
    }

    int operator[](int i)const { return ind[i]; }
private:
    vector<int> ind;
    unordered_set<int> indSet;
    int mx;
};

void calcSubsetsOfLength(vector<vector<int>>& out, const vector<int>& set, int n)
{
    if(n == 0) {
        out.push_back({});
        return;
    }
    vector<int> s(n);
    Ind ind(n, set.size());
    do {
        for(int i=0; i<n; i++)
            s[i] = set[ind[i]];
        out.push_back(s);
    }
    while(ind.next());
}

vector<vector<int>> powerSet(const vector<int>& set)
{
    vector<vector<int>> ps;
    for(int n=0; n<=set.size(); n++)
        calcSubsetsOfLength(ps, set, n);
    return ps;
}

void print(const vector<vector<int>>& vv)
{
    for(const vector<int>& v : vv)
    {
        cout << "{";
        if(v.size())
        {
            cout << v[0];
            for(int i=1; i<v.size(); i++)
                cout << ", " << v[i];
        }
        cout << "}" << endl;
    }
}

int main()
{
    vector<int> set = {1, 2, 3};
    vector<vector<int>> ps = powerSet(set);
    print(ps);
}