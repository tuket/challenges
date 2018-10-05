#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <limits>

using namespace std;

const int MAX_INT = numeric_limits<int>::max();
const int G = 1 << 16;
int table[G][16][16];

int calc(const string& s, int n, int len, int nend, int end, int start)
{
    const int N = s.size() / n;
    int res = 0;
    for(int i=0; i<N; i++)
    {
        char a = s[i*n+end];
        char b = s[i*n+nend];
        if(a != b)
            res++;
    }
    if(len == n-2)
    {
        for(int i=0; i<N-1; i++)
        {
            char a = s[i*n+nend];
            char b = s[(i+1)*n+start];
            if(a != b)
                res++;
        }
        res++;
    }
    return res;
}

int solve(int n, const string& s)
{
    fill(&table[0][0][0], &table[0][0][0] + sizeof(table)/sizeof(int), MAX_INT);
    const int N = s.size() / N;
    set<int> ss;
    for(int i=0; i < n; i++) {
        ss.insert(1<<i);
        table[1<<i][i][i] = 0;
    }
    
    for(int len = 0; len<n-1; len++)
    {
        set<int> nss;
        for(int g : ss)
        {
            for(int nend = 0; nend < n; nend++)
            if(((1 << nend) & g) == 0)
            {
                int ng = (1 << nend) | g;
                nss.insert(ng);
                for(int end = 0; end < n; end++)
                if(((1 << end) & g) != 0) 
                {
                    for(int j=0; j<n; j++)
                    if((1 << j) & g)
                    if(j != nend)   
                    if(j != end || (j == end && len == 0))
                    {
                        int& te = table[ng][nend][j];
                        int addVal = calc(s, n, len, nend, end,  j);
                        if(table[g][end][j] != MAX_INT)
                            te = min(te, table[g][end][j] + addVal);
                    }
                }
            }
        }
        ss = nss;
    }

    int res = MAX_INT;
    for(int g : ss)
    for(int end=0; end<n; end++)
    for(int start=0; start<n; start++)
    {
        res = min(res, table[g][end][start]);
    }
    return res;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n;
        cin >> n;
        string s;
        cin >> s;
        cout << "Case #" << kk << ": " << solve(n, s) << endl;
    }
}