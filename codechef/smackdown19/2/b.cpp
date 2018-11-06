#include <iostream>

using namespace std;

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        long long res = 0;
        int H, W, X, Y;
        cin >> H >> W >> Y >> X;
        X--; Y--;
        for(int y=0; y<H; y++)
        for(int x=0; x<W; x++)
        if(x != X || y != Y)
        {
            res += W*H -W -H - min(x, y) - min(W-x-1, y) - min(W-x-1, H-y-1) - min(x, H-y-1);
            if(x == X)
            {
                if(Y < y)
                    res += Y;
                else
                    res += H-Y-1;
                res++;
            }
            if(y == Y)
            {
                if(X < x) 
                    res += X;
                else
                    res += W-X-1;
                res++;
            }
            if(X-x == Y-y)
            {
                if(X < x)
                    res += min(X, Y);
                else
                    res += min(W-X-1, H-Y-1);
                res++;
            }
            if(X-x == -Y+y)
            {
                if(X < x)
                    res += min(X, H-Y-1);
                else
                    res += min(W-X-1, Y);
                res++;
            }
        }
        cout << res << endl;
    }
}