#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int W, H;
        cin >> H >> W;
        vector<char> t(W*H);
        for(int y=0; y<H; y++) {
            string s;
            cin >> s;
            for(int x=0; x<W; x++)
            {
                t[W*y+x] = s[x]-'0';
            }
        }
        
        vector<long long> res(W+H-2, 0);
        for(int y=0; y<H; y++)
        for(int x=0; x<W; x++)
        if(t[W*y+x] == 1)
        {
            for(int i=W*y+x+1; i<W*H; i++)
            {
                int xx = i%W;
                int yy = i/W;
                if(t[i] == 1)
                {
                    res[abs(x-xx) + abs(y-yy)-1]++;
                }
            }
        }
        cout << res[0];
        for(int i=1; i<res.size(); i++)
            cout << " " << res[i];
        cout << endl;
    }
}