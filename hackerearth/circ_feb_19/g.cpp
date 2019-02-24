#include <iostream>
#include <vector>

using namespace std;

inline int pow2(int n) { return n*n; }

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n;
        cin >> n;
        if(n % 2 == 1 && n < 7) {
            cout << -1 << endl;
            continue;
        }

        vector<vector<int>> g(n, vector<int>(n, 0));
        int num;
        int i = 1;
        auto q = [&g, &i](int x, int y)
        {
            g[y][x] = i;
            g[y][x+1] = i;
            g[y+1][x+1] = i;
            i++;
        };
        auto v = [&g, &i](int x, int y)
        {
            g[y][x] = i;
            g[y][x+1] = i;
            g[y+1][x] = i;
            i++;
            g[y+1][x+1] = i;
            g[y+2][x] = i;
            g[y+2][x+1] = i;
            i++;
        };
        auto h = [&g, &i](int x, int y)
        {
            g[y][x] = i;
            g[y][x+1] = i;
            g[y+1][x] = i;
            i++;
            g[y][x+2] = i;
            g[y+1][x+1] = i;
            g[y+1][x+2] = i;
            i++;
        };
        if(n % 2 == 0)
        {
            num = (n*n) / 4;
            for(int y=0; y<n; y+=2)
            for(int x=0; x<n; x+=2)
            {
                q(x, y);
            }
        }
        else
        {
            num = pow2((n+1)/2);
            for(int y=0; y<n-7; y+=2) {
                for(int x=0; x<n-3; x+=2)
                    q(x, y);
            }   
            for(int y=n-7; y<n-3; y+=2) {
                for(int x=2; x<n-3; x+=2)
                    q(x, y);
            }
            v(0, n-7);
            h(0, n-4);
            h(0, n-2); 
            for(int x=3; x<n; x+=2)
                v(x, n-3);
            for(int y=0; y<n-3; y+=2)
                h(n-3, y);
        }
        
        cout << num << endl;
        for(int y=0; y<n; y++) {
            for(int x=0; x<n-1; x++)
                cout << g[y][x] << " ";
            cout << g[y][n-1] << endl;
        }
    }   
}