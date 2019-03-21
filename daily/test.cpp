#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

typedef uint64_t u64;

constexpr u64 MOD = 1000000007ULL;

u64 encode(u64 N, u64 M, u64 p)
{
    return (((N << 30ULL) | M) << 1ULL) | p;
}

void decode(u64 x, u64& N, u64& M, u64& p)
{
    p = x & 1ULL;
    x >>= 1ULL;
    M = x & ((1ULL << 30ULL)-1ULL);
    x >>= 30ULL;
    N = x;
}

u64 fact(u64 n)
{
    constexpr u64 NF = 200003;
    static vector<u64> D = [NF]() {
        vector<u64> D(NF);
        D[0] = 1;
        for(u64 i=1; i<NF; i++)
        {
            D[i] = (D[i-1] * i) % MOD;
        }
        return D;
    }();
    return D[n];
}

struct Solver
{
    u64 N, M;
    u64 res;
    unordered_map<u64, u64> D;
    void solve();
    u64 recur(u64 N, u64 M, u64 p = 0);
};

void Solver::solve()
{
    cin >> N >> M;
    D.clear();
    res = recur(2*(N-M), 2*M);
}

u64 Solver::recur(u64 N, u64 M, u64 p)
{
    
    vector<u64> s;
    s.push_back(encode(N, M, p));
    while(s.size())
    {
        u64 N, M, p;
        decode(s.back(), N, M, p);
        u64 hash = s.back();
        if(M == 0 && p == 0) {
            D[hash] = fact(N);
        }
        auto it = D.find(hash);
        if(it != D.end()) {
            s.pop_back();
            continue;
        }
        u64 hash1 = encode(N-1, M, 0);
        u64 hash2 = encode(N+1, M-2, 1);
        auto it1 = D.find(hash1);
        auto it2 = D.find(hash2);
        u64 Np = N-p;
        if((Np == 0 || it1 != D.end()) &&
           (M == 0 || it2 != D.end()))
        {
            u64 res = 0;
            if(Np)
                res += Np * it1->second;
            if(M)
                res += M * it2->second;
            res = res % MOD;
            D[hash] = res;
            s.pop_back();
        }
        else {
            if(Np != 0 && it1 == D.end()) {
                s.push_back(hash1);
                //cerr << "+" << N-1 << " " << M << " " << 0 << endl;
            }
            if(M != 0 && it == D.end()) {
                s.push_back(hash2);
                //cerr << "+" << N+1 << " " << M-2 << " " << 1 << endl;
            }
            continue;
        }
    }
    u64 hash = encode(N, M, p);
    u64 res = D[hash];
    return res;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        Solver solver;
        solver.solve();
        cout << "Case #" << kk << ": " << solver.res << endl;
    }
}