#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int na, nb;
        cin >> na >> nb;
        vector<ll> A(na);
        vector<ll> B(nb);
        for(int i=0; i<na; i++) cin >> A[i];
        for(int i=0; i<nb; i++) cin >> B[i];
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        int i = 0, j = 0;
        for(;i < na; i++) if(A[i] != 0) break;
        for(;j < nb; j++) if(B[j] != 0) break;
        bool equal = na-i == nb-j;
        for(; i < na && equal; i++, j++) {
            if(A[i] != B[j]) equal = false;
        }
        if(equal)
            cout << "Bob" << endl;
        else
            cout << "Alice" << endl;
    }
}