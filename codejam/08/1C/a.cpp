#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int P, K, L;
        cin >> P >> K >> L;
        vector<int> v(L);
        for(int i=0; i<L; i++)
            cin >> v[i];
        sort(v.begin(), v.end(), greater<>());

        ll res = 0;
        int p = 1, k = 0;
        for(int i=0; i<L; i++)
        {
            res += p * v[i];
            k++;
            if(k == K) {
                k = 0;
                p++;
            }
        }
        cout << "Case #" << kk << ": " << res << endl;
    }
}