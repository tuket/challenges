#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef int64_t i64;

struct Cse
{
    char c;
    int n;
    bool operator==(const Cse& o)const
    {
        return c == o.c && n == o.n;
    }
    bool operator!=(const Cse& o)const
    {
        return c != o.c || n != o.n;
    }
};

class Cs
{
public:
    Cs(){}
    Cs(const string& s)
    {
        Cse e{s[0], 1};
        for(int i=1; i<s.size(); i++)
        {
            if(s[i-1] != s[i]) {
                ee.push_back(e);
                e.c = s[i];
                e.n = 1;
            }
            else {
                e.n++;
            }
        }
        ee.push_back(e);
    }
    /*
    Cs(const Cs& o)
        : ee(o.ee)
    {}
    void operator==(const Cs& o)
    {
        ee = o.ee;
    }*/
    
    Cs(Cs&& o)
        : ee(std::move(o.ee))
    {}
    void operator=(Cs&& o)
    {
        ee = std::move(o.ee);
    }
    

    /*void operator+=(const string& s)
    {
        for(int i=0; i<s.size(); i++)
        {
            const char c = s[i];
            Cse& e = ee.back();
            if(c != e.c) {
                Cse ne{c, 1};
                ee.push_back(ne);
            }
            else {
                e.n++;
            }
        }
    }*/

    void operator+=(const Cs& o)
    {
        size_t newSize = ee.size() + o.ee.size();
        auto bIt = o.ee.begin();
        if(ee.back().c == o.ee[0].c)
        {
            ee.back().n += o.ee[0].n;
            newSize--;
            bIt++;
        }
        ee.reserve(newSize);
        ee.insert(ee.end(), bIt, o.ee.end());
    }

    void insert(int i, char c)
    {
        const int en = ee.size();
        int j = 0;
        for(int ie=0; ie<en; ie++)
        {
            Cse& e = ee[ie];
            j += e.n;
            if(j >= i)
            {
                if(e.c == c) {
                    e.n++;
                }
                else {
                    if(j == i)
                        continue;
                    int pi = i - (j-e.n);
                    if(pi == 0) {
                        ee.resize(en+1);
                        for(int pj=en-1; pj>=ie; pj--)
                            ee[pj+1] = ee[pj];
                        ee[ie] = {c, 1};
                    }
                    else if(pi == e.n) {
                        ee.resize(en+1);
                        for(int pj=en-1; pj>ie; pj--)
                            ee[pj+1] = ee[pj];
                        ee[ie+1] = {c, 1};
                    }
                    else {
                        char ec = e.c;
                        int en2 = e.n-pi;
                        ee.resize(en+2);
                        for(int pj=en-1; pj>ie; pj--)
                            ee[pj+2] = ee[pj];
                        ee[ie] = {ec, pi};
                        ee[ie+1] = {c, 1};
                        ee[ie+2] = {ec, en2};
                    }
                }
                return;
            }
        }
        ee.push_back({c, 1});
    }

    bool isPali()const
    {
    int i = 0;
    int j = ee.size()-1;
    while(i < j) {
        if(ee[i] != ee[j])
            return false;
        i++;
        j--;
    }
    return true;
}


private:
    vector<Cse> ee;
};

istream& operator>>(istream& is, Cs& cs)
{
    string s;
    is >> s;
    cs = Cs(s);
    return is;
}

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<Cs> ss(N);
    for(Cs& s : ss)
        cin >> s;

    vector<bool> pali(N);
    i64 np = 0;
    for(int i=0; i<N; i++) {
        Cs& s = ss[i];
        pali[i] = s.isPali();
        if(pali[i])
            np++;
    }

    i64 pr = 0;
    for(int kk=0; kk<Q; kk++)
    {
        int type;
        cin >> type;
        i64 a;
        if(type == 1)
        {
            i64 ap, bp, b;
            cin >> ap >> bp;
            a = (ap ^ pr) - 1;
            b = (bp ^ pr) - 1;
            ss[a] += ss[b];
            ss[b] = Cs();
            if(pali[b])
                np--;
            else
                pali[b] = false;
        }
        else
        {
            i64 ap, kp, k;
            string sc;
            cin >> ap >> kp >> sc;
            a = (ap ^ pr) - 1;
            k = (kp ^ pr) - 1;
            ss[a].insert(k, sc[0]);
        }
        bool ba = ss[a].isPali();
        if(ba != pali[a]) {
            if(ba)
                np++;
            else
                np--;
            pali[a] = ba;
        }

        cout << np << endl;
        pr = np;
    }
}