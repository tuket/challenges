#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <unordered_set>
#include <utility>

using namespace std;

typedef int64_t i64;

char s[100000];

int lu(char c)
{
    switch(c) {
        case 'U': return 0;
        case 'D': return 1;
        case 'L': return 2;
        case 'R': return 3;
    }
    //assert(false);
    return -1;
}

struct P { int x, y; };

bool operator==(P a, P b) { return a.x == b.x && a.y == b.y; }

namespace std
{
template <>
struct hash<P> {
    size_t operator()(const P& p)const {
        size_t r = p.x;
        r = (r << 32) | p.y;
        return r;
    }
};
}

static const int dx[4] = { 0,  0, -1, +1};
static const int dy[4] = {-1, +1,  0,  0};

int main()
{
    int nn;
    scanf("%d", &nn);
    fgets(s, 100000, stdin);
    for(int kk = 1; kk <= nn; kk++)
    {
        fgets(s, 100000, stdin);
        const int ns = strlen(s);

        int x = 0, y = 0;
        unordered_set<P> m; 
        i64 res = 0;
        auto f2 = [&](int x, int y, int n) {
            auto it = m.find({x, y});
            if(it == m.end()) {
                m.insert({x ,y});
                res += n;
            }
        };
        f2(x, y, 1);
        f2(x, y-1, 2);
        f2(x, y+1, 3);
        f2(x-1, y, 4);
        f2(x+1, y, 5);

        for(int i = 0; i < ns-2; i += 2)
        {
            if(s[i] == 'S')
                break;
            const int d = lu(s[i]);
            x += dx[d];
            y += dy[d];
            f2(x, y-1, 2);
            f2(x, y+1, 3);
            f2(x-1, y, 4);
            f2(x+1, y, 5);
        }

        printf("%ld\n", res);
    }
}