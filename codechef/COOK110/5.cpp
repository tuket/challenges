#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <math.h>

using namespace std;

typedef int64_t i64;

int main()
{
    i64 nn;
    cin >> nn;
    for(i64 kk=1; kk<=nn; kk++)
    {
        i64 N, M;
        cin >> N >> M;
        vector<i64> P(N);
        vector<i64> L(M), R(M);
        for(i64 i=0; i<N; i++)
            cin >> P[i];
        for(i64 i=0; i<M; i++)
            cin >> L[i] >> R[i];

        i64 best = 0;
        for(i64 skip=0; skip<M; skip++)
        {
            set<i64> notStolen(P.begin(), P.end());
            for(i64 t=0; t<M; t++)
            if(t != skip)
            {
                auto it = lower_bound(notStolen.begin(), notStolen.end(), R[t]);
                if(it != notStolen.end() && *it == R[t]) {
                    notStolen.erase(it);
                }
                else if(it != notStolen.begin()) {
                    it--;
                    if(*it >= L[t])
                        notStolen.erase(it);
                }
            }
            const i64 r = accumulate(notStolen.begin(), notStolen.end(), (i64)0);
            best = max(best, r);
        }
        cout << best << endl;
    }
}