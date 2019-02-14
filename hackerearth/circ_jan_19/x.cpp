#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <algorithm>

using namespace std;

int N;
int canAdd, canRemove;
vector<string> G;
vector<array<float, 4>> P;
unordered_set<size_t> sols;

default_random_engine randEng;
uniform_int_distribution<int> randDist;
int randMutation()
{
    return randDist(randEng);
}

struct Pos
{
    char x, y;
    bool operator==(const Pos& o)const
    {
        return x == o.x && y == o.y;
    }
    bool isValid()const
    {
        return x >= 0 && y >= 0 && x < N && y < N;
    }
};

struct Sol;

namespace std
{
template <>
struct hash<Pos>
{
    size_t operator()(const Pos& p)const
    {
        size_t x = p.x;
        size_t y = p.y;
        return x + N * y;
    }
};
}

vector<Pos> empties;
vector<Pos> fulls;
vector<Pos> starts;
vector<Pos> endings;
int NEF;

struct Table
{
    Table() {}
    Table(int C, int N)
         : C(C)
         , N(N)
    {
        v.resize(C*N*N);
    }

    float& operator()(int c, int x, int y)
    {
        return v[x + N*(y + N*c)];
    }

    void reset()
    {
        fill(v.begin(), v.end(), 0.f);
        float prob = 1.f / starts.size();
        for(const Pos& p : starts)
        {
            operator()(0, p.x, p.y) = prob;
        }
    }

    void compC(const Sol& sol, int c);

    float eval(const Sol& sol)
    {
        reset();
        for(int c=1; c<C; c++)
            compC(sol, c);
        float res = 0;
        for(const Pos& p : endings)
            res += operator()(C-1, p.x, p.y);
        return res;
    }

    int C, N;
    vector<float> v;
};

Table MP;

struct Sol
{
    vector<Pos> toAdd;
    vector<Pos> toRemove;

    void mutate()
    {
        int mut = randMutation();
        if(mut < empties.size())
        {
            const Pos& p = empties[mut];
            auto it = find(toAdd.begin(), toAdd.end(), p);
            if(it == toAdd.end())
                if(toAdd.size() < canAdd)
                    toAdd.push_back(p);
                else
                    toAdd.pop_back();
            else
                toAdd.erase(it);
        }
        else
        {
            mut -= empties.size();
            const Pos& p = fulls[mut];
            auto it = find(toRemove.begin(), toRemove.end(), p);
            if(it == toRemove.end())
                if(toRemove.size() < canRemove)
                    toRemove.push_back(p);
                else
                    toRemove.pop_back();
            else
                toRemove.erase(it);
        }
    }

    vector<string> G;

    float evaluate()
    {
        this->G = ::G;
        for(const Pos& p : toAdd)
            this->G[p.y][p.x] = 'X';
        for(const Pos& p : toRemove)
            this->G[p.y][p.x] = '.';
        
        float val = MP.eval(*this);
        return val;
    }

    bool isValid(int x, int y)const
    {
        return //x >= 0 && y >= 0 && x <= N && y <= N &&
            G[y][x] != 'X';
    }

    bool isFinal(int x, int y)const
    {
        return G[y][x] == 'B';
    }

    vector<string> getResult()const
    {
        return this->G;
    }
};

void Table::compC(const Sol& sol, int c)
{
    float probRight = P[c-1][0];
    float probUp = P[c-1][1];
    float probLeft = P[c-1][2];
    float probDown = P[c-1][3];
    for(int y=0; y<N; y++)
    for(int x=0; x<N; x++)
    {
        float prob = operator()(c-1, x, y);
        if(prob == 0)
            continue;
        if(sol.isFinal(x, y))
        {
            operator()(c, x, y) += prob;
            continue;
        }
        // right
        if(x != N-1 && sol.isValid(x+1, y))
            operator()(c, x+1, y) += prob * probRight;
        else
            operator()(c, x, y) += prob * probRight;
        // up
        if(y != 0 && sol.isValid(x, y-1))
            operator()(c, x, y-1) += prob * probUp;
        else
            operator()(c, x, y) += prob * probUp;
        // left
        if(x != 0 && sol.isValid(x-1, y))
            operator()(c, x-1, y) += prob * probLeft;
        else
            operator()(c, x, y) += prob * probLeft;
        // down
        if(y != N-1 && sol.isValid(x, y+1))
            operator()(c, x, y+1) += prob * probDown;
        else
            operator()(c, x, y) += prob * probDown;
    }
}

namespace std
{
template <>
struct hash<Sol>
{
    size_t operator()(const Sol& o)const
    {
        std::size_t seed = 423423;
        for(const Pos& x : o.toAdd)
        {
            size_t a = hash<Pos>()(x);
            seed ^= a + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        for(const Pos& x : o.toRemove)
        {
            size_t a = hash<Pos>()(x);
            seed ^= a + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};
}

Sol bestSol;
float bestVal;

int main()
{
    cin >> N;
    cin >> canAdd >> canRemove;
    string s;
    getline(cin, s);
    G.resize(N);
    for(int i=0; i<N; i++)
    {
        getline(cin, G[i]);
    }
    array<float, 4> p;
    while(cin >> p[0])
    {
        cin >> p[1] >> p[2] >> p[3];
        P.push_back(p);
    }
    int cLim = ((60-N)*(60-N)*2000) / (50*50);
    int C = min(cLim, (int)P.size());
    int STEPS = 450000 / C;
    MP = Table(C, N);

    for(char y=0; y<N; y++)
    for(char x=0; x<N; x++)
    {
        char c = G[y][x];
        Pos p {x, y};
        if(c == '.')
            empties.push_back(p);
        else if(c == 'X')
            fulls.push_back(p);
        else if(c == 'A')
            starts.push_back(p);
        else if(c == 'B')
            endings.push_back(p);
    }
    NEF = empties.size() + fulls.size();

    randEng.seed(536553);
    randDist = uniform_int_distribution<int>(0, NEF-1);

    bestVal = bestSol.evaluate();
    sols.insert(hash<Sol>()(bestSol));
    Sol sol = bestSol;
    for(int i=0; i<STEPS; i++)
    {
        sol.mutate();
        size_t solHash = hash<Sol>()(sol);
        float val = sol.evaluate();
        if(val > bestVal)
        {
            bestSol = sol;
            bestVal = val;
        }
        sols.insert(solHash);

        /*
        cerr << i << endl;
        cerr << "toAdd: ";
        for(const Pos& p : sol.toAdd)
            cerr << "(" << (int)p.x << ", " << (int)p.y << ") ";
        cerr << endl << "toEnd: ";
        for(const Pos& p : sol.toRemove)
            cerr << "(" << (int)p.x << ", " << (int)p.y << ") ";
        cerr << endl;
        cerr << "val: " << val << "/" << bestVal << endl;*/
    }

    auto solG = bestSol.getResult();

    for(int i=0; i<N; i++)
    {
        cout << solG[i] << endl;
    }
}