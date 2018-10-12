// g++ a_view.cpp -lsfml-graphics -lsfml-window -lsfml-system -g
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>

using namespace std;

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

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
int OX = 0, OY = 0;
float scale = 10.f;

bool drawGrid = true;
bool drawShadows = true;
bool drawWalls = true;
bool drawPath = true;

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


struct Drawer
{
    Drawer(sf::RenderWindow& window, const vector<AA>& v)
        : window(window), v(v) {}

    sf::RenderWindow& window;
    const vector<AA>& v;

    void operator()()
    {
        const int w = window.getSize().x;
        const int h = window.getSize().y;

        // draw grid
        if(drawGrid)
        {
            sf::Color color(20, 20, 20, 255);
            vector<sf::Vertex> verts;
            for(float x = 0; x < w/2; x += scale) {
                verts.emplace_back(sf::Vector2f(w/2 + x, 0), color);
                verts.emplace_back(sf::Vector2f(w/2 + x, h), color);
                verts.emplace_back(sf::Vector2f(w/2 - x, 0), color);
                verts.emplace_back(sf::Vector2f(w/2 - x, h), color);
            }
            for(float y = 0; y < h/2; y += scale) {
                verts.emplace_back(sf::Vector2f(0, h/2 + y), color);
                verts.emplace_back(sf::Vector2f(w, h/2 + y), color);
                verts.emplace_back(sf::Vector2f(0, h/2 - y), color);
                verts.emplace_back(sf::Vector2f(w, h/2 - y), color);
            }
            window.draw(verts.data(), verts.size(), sf::Lines);
        }

        // draw shadowns
        if(drawShadows)
        {
            const float WW = 0.2f;
            const int minX = TX/2 - w/(2*scale) + OX - 1;
            const int maxX = TX/2 + w/(2*scale) + OX + 1;
            const int minY = TY/2 - h/(2*scale) + OY - 1;
            const int maxY = TY/2 + h/(2*scale) + OY + 1;
            for(int x=minX; x<maxX; x++)
            for(int y=minY; y<maxY; y++)
            {
                float X = w/2 + scale * (x - TX/2 - OX);
                float Y = h/2 + scale * (y - TY/2 - OY);
                char t = 0xFF;
                if(x >= 0 && x < TX && y >= 0 && y < TY)
                    t = table[y][x];
                if((t & SHADOW_VERT) == SHADOW_VERT || (t & SHADOW_HORI) == SHADOW_HORI)
                {
                    sf::RectangleShape rect(sf::Vector2f(scale, scale));
                    rect.setPosition(sf::Vector2f(X, Y));
                    rect.setFillColor(sf::Color(40, 40, 40, 255));
                    window.draw(rect);
                }
            }
        }

        // draw walls
        if(drawWalls)
        {
            const float WW = 0.2f;
            const int minX = TX/2 - w/(2*scale) + OX - 1;
            const int maxX = TX/2 + w/(2*scale) + OX + 1;
            const int minY = TY/2 - h/(2*scale) + OY - 1;
            const int maxY = TY/2 + h/(2*scale) + OY + 1;
            for(int x=minX; x<maxX; x++)
            for(int y=minY; y<maxY; y++)
            {
                float X = w/2 + scale * (x - TX/2 - OX);
                float Y = h/2 + scale * (y - TY/2 - OY);
                char t = 0;
                if(x >= 0 && x < TX && y >= 0 && y < TY)
                    t = table[y][x];

                if(t & WALL_DOWN) {
                    sf::RectangleShape rect(sf::Vector2f(scale, WW*scale));
                    rect.setPosition(sf::Vector2f(X, Y+scale-WW*scale));
                    rect.setFillColor(sf::Color::Red);
                    window.draw(rect);
                }
                if(t & WALL_UP) {
                    sf::RectangleShape rect(sf::Vector2f(scale, WW*scale));
                    rect.setPosition(sf::Vector2f(X, Y));
                    rect.setFillColor(sf::Color::Red);
                    window.draw(rect);
                }
                if(t & WALL_LEFT) {
                    sf::RectangleShape rect(sf::Vector2f(WW*scale, scale));
                    rect.setPosition(sf::Vector2f(X+scale-WW*scale, Y));
                    rect.setFillColor(sf::Color::Red);
                    window.draw(rect);
                }
                if(t & WALL_RIGHT) {
                    sf::RectangleShape rect(sf::Vector2f(WW*scale, scale));
                    rect.setPosition(sf::Vector2f(X, Y));
                    rect.setFillColor(sf::Color::Red);
                    window.draw(rect);
                }
            }
        }

        // draw path
        if(drawPath)
        {
            State state{{0, 0}, UP};
            vector<sf::Vertex> verts = {sf::Vertex(sf::Vector2f(w/2 -scale*OX, h/2 -scale*OY), sf::Color::Blue)};
            for(const AA& a : v)
            for(int ii=0; ii<a.n; ii++)
            for(char c : a.s)
            {
                advanceState(state, c);
                verts.push_back(sf::Vertex(sf::Vector2f(
                    scale*(state.pos.x - OX) + w/2,
                    scale*(state.pos.y - OY) + h/2),
                    sf::Color::Blue));
            }
            window.draw(verts.data(), verts.size(), sf::LineStrip);
        }
    }
};

void handleInput()
{
    // move
    int inc = ceil(16.f/scale);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        OX -= inc;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        OX += inc;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        OY += inc;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        OY -= inc;
    }

    // magnify
    const float step = 1.06f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        scale /= step;
        scale = max(0.1f, scale);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        scale *= step;
        scale = min(100.f, scale);
    }

    // visibility
    static bool prevPressed_Z = false;
    static bool prevPressed_X = false;
    static bool prevPressed_C = false;
    static bool prevPressed_V = false;
    const bool nowPressed_Z = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
    const bool nowPressed_X = sf::Keyboard::isKeyPressed(sf::Keyboard::X);
    const bool nowPressed_C = sf::Keyboard::isKeyPressed(sf::Keyboard::C);
    const bool nowPressed_V = sf::Keyboard::isKeyPressed(sf::Keyboard::V);
    if(!prevPressed_Z && nowPressed_Z)
        drawGrid = !drawGrid;
    if(!prevPressed_X && nowPressed_X)
        drawShadows = !drawShadows;
    if(!prevPressed_C && nowPressed_C)
        drawWalls = !drawWalls;
    if(!prevPressed_V && nowPressed_V)
        drawPath = !drawPath;
    prevPressed_Z = nowPressed_Z;
    prevPressed_X = nowPressed_X;
    prevPressed_C = nowPressed_C;
    prevPressed_V = nowPressed_V;
}

int main()
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

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "How Big Are the Pockets?");
    auto view = window.getView();
    view.setSize(WINDOW_WIDTH, -WINDOW_HEIGHT);
    window.setView(view);

    Drawer drawer(window, v);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        handleInput();

        window.clear();
        drawer();
        window.display();
        sf::sleep(sf::seconds(0.05));
    }

    return 0;
}