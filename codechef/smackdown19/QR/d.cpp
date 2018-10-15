#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

bool solve(const vector<ll>& A, const vector<ll>& B)
{
    const int n = A.size();
    vector<ll> x(n);
    x[0] = B[0] - A[0];
    x[1] = B[1] - A[1] - 2 * x[0];
    if(x[1] < 0) return false;
    for(int i=2; i<n; i++)
    {
        x[i] = B[i] - A[i] - 2 * x[i-1] - 3 * x[i-2];
        if(x[i] < 0) return false;
    }
    return x[n-1] == 0 && x[n-2] == 0;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n;
        cin >> n;
        vector<ll> A(n);
        for(int i=0; i<n; i++)
            cin >> A[i];
        vector<ll> B(n);
        for(int i=0; i<n; i++)
            cin >> B[i];
        int res = solve(A, B);
        cout << (res ? "TAK" : "NIE") << endl;
    }
}