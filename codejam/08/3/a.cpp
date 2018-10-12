// g++ a_view.cpp -lsfml-graphics -lsfml-window -lsfml-system -g
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

enum Dir {
    UP, DOWN, LEFT, RIGHT, COUNT
};

const char SHADOW_UP = 1 << 0;
const char SHADOW_DOWN = 1 << 1;
const char SHADOW_LEFT = 1 << 2;
const char SHADOW_RIGHT = 1 << 3;
const char WALL_UP = 1 << 4;
const char WALL_DOWN = 1 << 5;
const char WALL_LEFT = 1 << 6;
const char WALL_RIGHT = 1 << 7;
const char SHADOW_VERT = SHADOW_UP | SHADOW_DOWN;
const char SHADOW_HORI = SHADOW_LEFT | SHADOW_RIGHT;


struct AA { string s; int n; };

struct State
{
    struct Pos {
        int x, y;
    } pos;
    Dir dir;
};

const int TX = 6002;
const int TY = 6002;
char table[TY][TX];
int LR;

void cleanTable()
{
    fill(&table[0][0], &table[0][0]+sizeof(table), 0);
}

typedef function<void(const State&, char)> MapFunc;

void advanceState(State& state, char action)
{
    if(action == 'F')
    {
        switch(state.dir)
        {
            case UP:
                state.pos.y++;
                break;
            case DOWN:
                state.pos.y--;
                break;
            case LEFT:
                state.pos.x--;
                break;
            case RIGHT:
                state.pos.x++;
        }
    }
    else
    {
        const int lr = action == 'L' ? 0 : 1;
        static const Dir transform[Dir::COUNT][2] = {
            {LEFT, RIGHT}, {RIGHT, LEFT}, {DOWN, UP}, {UP, DOWN}
        };
        state.dir = transform[state.dir][lr];
    }
}

void setWall(const State& state, char action)
{
    if(action != 'F')
        return;
    
    const State::Pos& pos = state.pos;
    const Dir& dir = state.dir;
    if(dir == UP)
    {
        if(LR < 0)
            table[pos.y][pos.x] |= WALL_RIGHT;
        else
            table[pos.y][pos.x-1] |= WALL_LEFT;
    }
    else if(dir == DOWN)
    {
        if(LR < 0)
            table[pos.y-1][pos.x-1] |= WALL_LEFT;
        else
            table[pos.y-1][pos.x] |= WALL_RIGHT;
    }
    else if(dir == LEFT)
    {
        if(LR < 0)
            table[pos.y][pos.x-1] |= WALL_UP;
        else
            table[pos.y-1][pos.x-1] |= WALL_DOWN;
    }
    else // RIGHT
    {
        if(LR < 0)
            table[pos.y-1][pos.x] |= WALL_DOWN;
        else
            table[pos.y][pos.x] |= WALL_UP;
    }
}

void mapActions(const vector<AA>& v, MapFunc mf)
{
    State state{{TX/2, TY/2}, UP};
    for(const AA& a : v)
    for(int ii=0; ii<a.n; ii++)
    for(char c : a.s)
    {
        mf(state, c);
        advanceState(state, c);
    }
}

void setShadow(const State& state, char action)
{
    if(action != 'F')
        return;

    if(state.dir == UP)
    {
        const int y = state.pos.y;
        if(LR < 0) {
            for(int x = state.pos.x; x < TX; x++) {
                char& t = table[y][x];
                t |= SHADOW_RIGHT;
                if(t & WALL_LEFT) break;
            }
        }
        else {
            for(int x = state.pos.x-1; x >= 0; x--) {
                char& t = table[y][x];
                t |= SHADOW_LEFT;
                if(t & WALL_RIGHT) break;
            }
        }
    }
    else if(state.dir == DOWN)
    {
        const int y = state.pos.y - 1;
        if(LR < 0) {
            for(int x = state.pos.x-1; x >= 0; x--) {
                char& t = table[y][x];
                t |= SHADOW_LEFT;
                if(t & WALL_RIGHT) break;
            }
        }
        else {
            for(int x = state.pos.x; x < TX; x++) {
                char& t = table[y][x];
                t |= SHADOW_RIGHT;
                if(t & WALL_LEFT) break;
            }
        }
    }
    else if(state.dir == LEFT)
    {
        const int x = state.pos.x - 1;
        if(LR < 0) {
            for(int y = state.pos.y; y < TY; y++) {
                char& t = table[y][x];
                t |= SHADOW_UP;
                if(t & WALL_DOWN) break;
            }
        }
        else {
            for(int y = state.pos.y - 1; y >= 0; y--) {
                char& t = table[y][x];
                t |= SHADOW_DOWN;
                if(t & WALL_UP) break;
            }
        }
    }
    else // RIGHT
    {
        const int x = state.pos.x;
        if(LR < 0) {
            for(int y = state.pos.y - 1; y >= 0; y--) {
                char& t = table[y][x];
                t |= SHADOW_DOWN;
                if(t & WALL_UP) break;
            }
        }
        else {
            for(int y = state.pos.y; y < TY; y++) {
                char& t = table[y][x];
                t |= SHADOW_UP;
                if(t & WALL_DOWN) break;
            }
        }
    }    
}

int count()
{
    int res = 0;
    for(int y = 0; y < TY; y++)
    for(int x = 0; x < TX; x++)
    {
        const char t = table[y][x];
        if((t & SHADOW_VERT) == SHADOW_VERT || (t & SHADOW_HORI) == SHADOW_HORI)
        {
            res++;
        }
    }
    return res;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        cleanTable();
        int N;
        cin >> N;
        vector<AA> v(N);
        State state{{TX/2, TY/2}, UP};
        LR = 0;
        for(int ii=0; ii<N; ii++)
        {
            cin >> v[ii].s;
            cin >> v[ii].n;
            for(int i = 0; i < v[ii].n; i++) {
                for(char c : v[ii].s) {
                    if(c == 'L') LR--;
                    else if(c == 'R') LR ++;
                }
            }
        }
        mapActions(v, setWall);
        mapActions(v, setShadow);
        cout << "Case #" << kk << ": " << count() << endl;
    }
}