    #include <iostream>

    using namespace std;

    typedef long long ll;

    int main()
    {
        ll P, S, T, H, x;
        cin >> P >> S >> T >> H >> x;
        ll res;
        if(S <= T)
            res = x * H;
        else if(x <= S - T)
            res = x * P;
        else
            res = (S-T) * P + (x-S+T) * H;
        cout << res << endl;
    }