#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <unordered_map>

using namespace std;

typedef array<int, 2> P;

P operator+(P a, P b)
{
    return {a[0] + b[0], a[1] + b[1]};
}

namespace std
{
template<>
struct hash<P>
{
    size_t operator()(P p)const
    {
        return (p[0] << 16) || p[1];
    }
};
}

static const array<P, 4> DIRS = {
    P{-1, 0}, {+1, 0}, {0, -1}, {0, +1}
};

struct Sol
{
    int val;
    P p;
    string str;

    bool operator<(const Sol& o)
    {
        return str < o.str;
    }
};

bool isWithinBounds(int W, P p)
{
    return p[0] >= 0 && p[1] >= 0 && p[0] < W && p[1] < W;
}

class Solver
{
    int W;
    const vector<string> g;
    unordered_map<int,
        unordered_map<P, string>
    > valToPToStr;

public:
    Solver(int W, vector<string>&& g)
        : W(W), g(move(g)) {}

    bool insert(int val, P p, string str)
    {
        auto it1 = valToPToStr.find(val);
        if(it1 == valToPToStr.end())
        {
            valToPToStr[val] = unordered_map<P, string>();
            it1 = valToPToStr.find(val);
        }
        auto it2 = it1->second.find(p);
        if(it2 == it1->second.end())
        {
            it1->second[p] = str;
            return true;
        }
        else
        {
            if(str < it2->second) {
                it2->second = str;
                return true;
            }
            return false;
        }
    }

    string solve(int q)
    {
        valToPToStr.clear();
        vector<Sol> layer1, layer2;
        for(int y=0; y<W; y++)
        for(int x=0; x<W; x++)
        {
            const char c = g[y][x];
            if(isdigit(c))
            {
                int val = c-'0';
                string str = string(1, c);
                if(val == q)
                    return str;
                layer1.push_back({val, {x, y}, str});
                insert(val, {x, y}, str);
            }
        }

        bool opTime = true;
        while(true)
        {
            layer2.clear();
            for(const Sol& sol : layer1)
            {
                for(P dir : DIRS)
                {
                    P newPos = sol.p+dir;
                    if(isWithinBounds(W, newPos))
                    {
                        const char c = g[newPos[1]][newPos[0]];
                        int newVal = sol.val;
                        if(!opTime)
                        {
                            if(sol.str.back() == '+')
                                newVal += c-'0';
                            else
                                newVal -= c-'0';
                        }
                        Sol newSol{newVal, newPos, sol.str + c};
                        if(opTime) {
                            layer2.push_back(newSol);
                        }
                        else {
                            if(insert(newSol.val, newSol.p, newSol.str))
                                layer2.push_back(newSol);
                        }
                    }
                }
            }

            if(!opTime)
            {
                int i;
                string foundSol = "";
                for(i=0; i<layer2.size(); i++)
                {
                    const Sol& sol = layer2[i];
                    if(sol.val == q) {
                        foundSol = sol.str;
                        break;
                    }
                }
                for(i++; i<layer2.size(); i++)
                {
                    const Sol& sol = layer2[i];
                    if(sol.val == q)
                    {
                        foundSol = min(foundSol, sol.str);
                    }
                }
                if(foundSol.size() != 0)
                    return foundSol;
            }

            swap(layer1, layer2);
            opTime = !opTime;
        }
    }
};

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int W, nq;
        cin >> W >> nq;
        vector<string> g(W);
        for(auto& s : g)
            cin >> s;
        vector<int> Q(nq);
        for(int& q : Q)
            cin >> q;
        
        cout << "Case #" << kk << ":" << endl;
        Solver solver(W, move(g));
        for(int q : Q)
        {
            string sol = solver.solve(q);
            cout << sol << endl;
        }
    }
}