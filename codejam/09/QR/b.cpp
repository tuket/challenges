#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <map>

using namespace std;

struct P
{
    int x = -1, y = -1;
    bool operator<(const P& p)const
    {
        return  y < p.y ? true :
                y > p.y ? false :
                x < p.x;
    }
    bool operator==(const P& p)const { return x == p.x && y == p.y; }
    bool operator!=(const P& p)const { return x != p.x || y != p.y;}
};

struct PT
{
    P p;
    unsigned h;
    bool operator<(const PT& pt)const
    {
        return  h < pt.h ? true :
                h > pt.h ? false :
                p < pt.p;
    }
};

struct Table
{
    Table(int W, int H) : W(W), H(H) { t.resize(W*H); }
    PT& operator()(int x, int y) { return t[x+ W*y]; }
    PT& operator()(P p) { return t[p.x + W*p.y]; }
    P root(P p)
    {
        static vector<P> chain;
        chain.clear();
        P parent = operator()(p).p;
        while(parent.x != -1) {
            chain.push_back(p);
            p = parent;
            parent = operator()(p).p;
        }
        for(int i=0; i < (int)chain.size()-1; i++)
            operator()(chain[i]).p = p;
        return p;
    }
    void merge(P a, P b)
    {
        P ra = root(a);
        P rb = root(b);
        if(ra != rb)
            operator()(rb).p = ra;
    }
    int W, H;
    vector<PT> t;
};

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int H, W;
        cin >> H >> W;
        Table t(W, H);
        for(int y=0; y<H; y++)
        for(int x=0; x<W; x++)
        {
            cin >> t(x, y).h;
        }

        auto isValid = [W, H](P p)
        {
            return p.x >= 0 && p.x < W && p.y >= 0 && p.y < H;
        };

        vector<PT> vp(4);
        for(int y=0; y<H; y++)
        for(int x=0; x<W; x++)
        {
            vp.clear();
            array<P, 4> ap = {
                P{x-1, y},
                P{x+1, y},
                P{x, y-1},
                P{x, y+1}
            };
            for(P p : ap) {
                if(isValid(p))
                    vp.push_back({p, t(p).h});
            }
            if(vp.size())
            {
                sort(vp.begin(), vp.end());
                P a{x, y};
                PT pta = t(a);
                PT pb = vp[0];
                if(pb.h < pta.h) {
                    if(t.root(a) < t.root(pb.p))
                        t.merge(a, pb.p);
                    else
                        t.merge(pb.p, a);
                }
            }
        }

        map<P, char> ptoc;
        char c = 'a';
        for(int y=0; y<H; y++)
        for(int x=0; x<W; x++)
        {
            P p{x, y};
            const PT& pt = t(p);
            if(pt.p.x == -1)
            {
                ptoc[p] = c;
                c++;
            }
        }

        cout << "Case #" << kk << ":" << endl;
        for(int y=0; y<H; y++)
        {
            for(int x=0; x<W; x++)
            {
                P p = t.root({x, y});
                char c = ptoc[p];
                cout << c;
                if(x != W-1)
                    cout << " ";
            }
            cout << endl;
        }
    }
}