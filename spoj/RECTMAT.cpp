#include <stdio.h>
#include <stdint.h>

typedef int64_t i64;
constexpr i64 M = 1'000'000'007;

inline i64 min(i64 a, i64 b) { return a < b ? a : b; }

struct R { i64 x0, y0, x1, y1; };
i64 nr;
R rr[6];
i64 W, H, K;
i64 res;

void f()
{
    const R& pr = rr[nr-1];
    i64 sx, sy;
    if(nr > 0) {
        sx = pr.x0+1;
        sy = pr.y0;
    } else {
        sx = sy = 0;
    }
    if(nr == K) {
        /*const i64 w = pr.x1 - pr.x0;
        const i64 h = pr.y1 - pr.y0;
        res += w * h * (w+1) * (h+1) / 4;
        res %= M;*/
        res++;
        res %= M;
    }
    for(i64 y0 = sy; y0 <= H; y0++)
    for(i64 x0 = sx; x0 < W; x0++)
    {
        i64 maxXX1 = W;
        for(int i = 0; i < nr; i++) {
            const R& r = rr[i];
            if(r.x0 >= x0 && r.y1 > y0) {
                maxXX1 = min(maxXX1, r.x0);
                if(maxXX1 <= x0) {
                    x0 = r.x1;
                    goto next0;
                }
            }
        }
        nr++;
        for(i64 y1 = y0+1; y1 <= H; y1++)
        for(i64 x1 = x0+1; x1 <= maxXX1; x1++) {
            rr[nr-1] = {x0, y0, x1, y1};
            f();
        }
        nr--;
        next0: ;
    }
}

int main()
{
    while (scanf("%ld %ld %ld", &H, &W, &K) != EOF)
    {
        res = 0;
        nr = 0;
        f();
        printf("%ld\n", res);
    }
}