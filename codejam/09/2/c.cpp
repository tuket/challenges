#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int n, k;
vector<int> stockCharts;

vector<int> charComps;
vector<int> prevs;
vector<bool> visited;

int compareCharts(int a, int b)
{
    const int A = stockCharts[a*k];
    const int B = stockCharts[b*k];
    if(A < B)
    {
        for(int i=1; i<k; i++) {
            const int A = stockCharts[i + a*k];
            const int B = stockCharts[i + b*k];
            if(A < B == false)
                return 0;
        }
        return -1;
    }
    else if(A > B)
    {
        for(int i=1; i<k; i++) {
            const int A = stockCharts[i + a*k];
            const int B = stockCharts[i + b*k];
            if(A > B == false)
                return 0;
        }
        return +1;
    }
    else {
        return 0;
    }
}

bool dfs(int a)
{
    if(a < 0)
        return true;
    if(visited[a])
        return false;

    visited[a] = true;

    for(int b = 0; b < n; b++)
    if(charComps[a + b*n] == +1)
    if(dfs(prevs[b]))
    {
        prevs[b] = a;
        return true;
    }
    return false;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        
        cin >> n >> k;
        stockCharts = vector<int>(n*k);
        for(int i=0; i<n*k; i++)
            cin >> stockCharts[i];

        charComps = vector<int>(n*n);
        for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
        {
            const int c = compareCharts(i, j);
            charComps[j + i*n] = c;
            charComps[i + j*n] = -c;
        }

        int result = 0;
        prevs = vector<int>(n, -1);
        for(int i=0; i<n; i++)
        {
            visited = vector<bool> (n, false);
            if(!dfs(i))
                result++;
        }

        cout << "Case #" << kk << ": " << result << endl;
    }
}