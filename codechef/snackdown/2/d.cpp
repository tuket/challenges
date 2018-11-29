#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int gcd(int a, int b)
{
    if( a<0 ) a = -a;
    if( b<0 ) b = -b;
    while( b!=0 ){
        a %= b;
        if( a==0 ) return b;
        b %= a;
    }
    return a;
}

template <typename T, typename Compare>
void getSortPermutation(
    std::vector<unsigned>& out,
    const std::vector<T>& v,
    Compare compare = std::less<T>())
{
    out.resize(v.size());
    std::iota(out.begin(), out.end(), 0);
    
    std::sort(out.begin(), out.end(),
        [&](unsigned i, unsigned j){ return compare(v[i], v[j]); });
}

bool cmpEqual(int p, int q, int P, int Q)
{
    p *= Q;
    P *= q;
    return p == P;
}

bool cmpLower(int p, int q, int P, int Q)
{
    p *= Q;
    P *= q;
    return p < P;
}

bool cmpGreater(int p, int q, int P, int Q)
{
    p *= Q;
    P *= q;
    return p > P;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int N, P, Q;
        cin >> N >> P >> Q;
        vector<int> A(N);
        for(int& a : A) cin >> a;

        vector<unsigned> SI;
        getSortPermutation(SI, A, less<int>());
        sort(A.begin(), A.end());
        int pBest = 1000;
        int qBest = 1;
        int I, J, K;
        for(int i=0; i<N-1; i++)
        for(int j=i+1; j<N; j++)
        {
            int p, q;
            int a, b, c;
            a = A[i];
            b = A[j];
            int k1 = 0;
            int k2 = N-3;
            while(k1 + 1 < k2)
            {
                int kk = (k1+k2) / 2;
                int kkk = kk;
                if(kkk >= min(i, j)) {
                    kkk++;
                    if(kkk >= max(i, j))
                        kkk++;
                }
                c = A[kkk];
                p = a*a + b*b - c*c;
                q = 2*a*b;
                if(a + b >= c) {
                    k1 = kk + 1;
                }
                else if(p >= q) {
                    k1 = kk + 1;
                }
                else if(p <= -q) {
                    k2 = kk - 1;
                }
                else if(!cmpLower(p, q, P, Q)){
                    if(cmpEqual(p, q, P, Q))
                        k1 = k2 = kk;
                    else
                        k1 = kk;
                }
                else {
                    k2 = kk - 1;
                }
            }
            if(k1 >= min(i, j)) {
                k1++;
                if(k1 >= max(i, j))
                    k1++;
            }
            if(k2 >= min(i, j)) {
                k2++;
                if(k2 >= max(i, j))
                    k2++;
            }
            c = A[k2];
            p = a*a + b*b - c*c;
            q = 2*a*b;
            if(p <= -q || p >= q || cmpLower(p, q, P, Q)) {
                c = A[k1];
                p = a*a + b*b - c*c;
                q = 2*a*b;
                if(p <= 0 || p > q)
                    continue;
            }
            else k1 = k2;

            if(!cmpLower(p, q, P, Q))
            if(cmpLower(p, q, pBest, qBest))
            {
                pBest = p;
                qBest = q;
                I = SI[i];
                J = SI[j];
                K = SI[k1];
            }
        }
        if(pBest > qBest)
            cout << -1 << endl;
        else
            cout << I+1 << " " << J+1 << " " << K+1;
    }
}