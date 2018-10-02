#include <iostream>
#include <vector>

using namespace std;

const unsigned MO = -1;

struct Solver
{
    vector<int> v, c;
    int n, o, N;

    void read()
    {
        cin >> n >> o;
        N = (n-1)/2   ;
        v.resize(n);
        c.resize(N);
        int i;
        for(i=0; i<N; i++)
        {
            cin >> v[i];
            cin >> c[i];
        }
        for(; i<n; i++) {
            cin >> v[i];
        }
    }

    bool isLeaf(int i)
    {
        return i >= N;
    }

    unsigned solve(int i, int o)
    {
        if(isLeaf(i))
        {
            if(v[i] == o) return 0;
            else return -1;
        }
        unsigned withChange, withoutChange;
        auto f = [&](int cv) -> unsigned
        {
            int vv = v[i]^cv;
            if(vv == o) { // &
                unsigned s1 = solve(2*i+1, vv);
                unsigned s2 = solve(2*i+2, vv);
                if(s1 == MO || s2 == MO) return -1;
                return s1 + s2;
            }
            else {
                return min(solve(2*i+1, 1-vv), solve(2*i+2, 1-vv));
            }
        };
        withoutChange = f(0);
        if(c[i])
        {
            withChange = f(1);
            if(withChange < withoutChange)
                return withChange + 1;
        }
        return withoutChange;
    }

    int solve()
    {
        return solve(0, o);
    }
};

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        Solver solver;
        solver.read();
        unsigned res = solver.solve();
        cout << "Case #" << kk << ": ";
        if(res == (unsigned)-1)
            cout << "IMPOSSIBLE";
        else
            cout << res;
        cout << endl;
    }
}