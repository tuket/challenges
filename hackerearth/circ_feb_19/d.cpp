#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

array<int, 95> PP = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499};

typedef array<u8, 95> Pdec;

struct PKS2SE
{
    u64 total;
    unordered_set<u64> s;
};

struct PKS2E
{
    u64 total;
    unordered_map<u64, PKS2SE> se;
};

namespace std
{
template<>
struct hash<Pdec>
{
    size_t operator()(const Pdec& vec) const
    {
        size_t seed = vec.size();
        for(size_t i : vec) {
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};
}

struct PK {
    int p, k;
};

void primeDecomp(vector<PK>& res, int n)
{
    res.clear();
    for(int i=0; i<PP.size(); i++)
    {
        int p = PP[i];
        int k = 0;
        while(n % p == 0) {
            k++;
            n /= p;
        }
        if(k) {
            res.push_back({i, k});
        }
    }
}

void mult(vector<PK>& v, const vector<PK>& v1, const vector<PK>& v2)
{
    v.clear();
    int i = 0, j = 0;
    while(i < v1.size() && j < v2.size())
    {
        if(v1[i].p == v2[j].p) {
            v.push_back({v1[i].p, v1[i].k + v2[j].k});
            i++;
            j++;
        }
        else if(v1[i].p < v2[j].p) {
            v.push_back(v1[i]);
            i++;
        }
        else {
            v.push_back(v2[j]);
            j++;
        }
    }
    for(; i < v1.size(); i++)
        v.push_back(v1[i]);
    for(; j < v2.size(); j++)
        v.push_back(v2[j]);
}

void mult(Pdec& s, const Pdec& s1, const Pdec& s2)
{
    for(int i=0; i<95; i++)
        s[i] = (s1[i] + s2[i]) % 3;
}

Pdec toString(const vector<PK>& pks)
{
    Pdec s{};
    for(const PK& pk : pks) {
        s[pk.p] = pk.k % 3;
    }
    return s;
}

Pdec calcComplement(const Pdec& s)
{
    static constexpr char t[] = {0, 2, 1};
    Pdec res{};
    for(int i=0; i<95; i++) {
        res[i] = t[s[i]];
    }
    return res;
}

int main()
{
    int N;
    cin >> N;
    unordered_map<Pdec, vector<u64>> pks;
    for(u64 i=0; i<N; i++)
    {
        int nf;
        cin >> nf;
        vector<PK> pk;
        vector<PK> fpk1, fpk2;
        for(int i=0; i<nf; i++)
        {
            int f;
            cin >> f;
            swap(pk, fpk1);
            primeDecomp(fpk2, f);
            mult(pk, fpk1, fpk2);
        }
        Pdec s = toString(pk);
        auto it = pks.find(s);
        if(it == pks.end()) {
            pks[s] = {};
            it = pks.find(s);
        }
        it->second.push_back(i);
    }

    unordered_map<Pdec, PKS2E> pks2;
    Pdec s{};
    for(auto it1 = pks.begin(); it1 != pks.end(); ++it1)
    for(auto it2 = pks.begin(); it2 != pks.end(); ++it2)
    {
        mult(s, it1->first, it2->first);
        auto it = pks2.find(s);
        if(it == pks2.end()) {
            pks2[s] = {};
            it = pks2.find(s);
        }
        for(u64 c1 : it1->second)
        for(auto itC2 = it2->second.rbegin(); itC2 != it2->second.rend(); ++itC2)
        {
            u64 c2 = *itC2;
            //if(c1 < c2)
            {
                u64 c = (c1 << 32) | c2;
                it->second.total++;
                auto ite1 = it->second.se.find(c1);
                if(ite1 == it->second.se.end()) {
                    it->second.se[c1] = PKS2SE();
                    ite1 = it->second.se.find(c1);
                }
                ite1->second.total++;
                ite1->second.s.insert(c2);
            }
        }
    }

    uint64_t res = 0;
    for(auto it = pks2.begin(); it != pks2.end(); ++it)
    {
        Pdec cs = calcComplement(it->first);
        auto it2 = pks2.find(cs);
        if(it2 != pks2.end()) {
            PKS2E& e1 = it->second;
            PKS2E& e2 = it2->second;
            u64 total1 = it->second.total;
            for(auto& pse : e1.se)
            {
                PKS2SE& se = pse.second;
                u64 total2 = se.total;
                
            }
        }
    }
    cout << res << endl;
}