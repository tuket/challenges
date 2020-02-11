#include <stdio.h>
#include <stdint.h>

typedef int64_t i64;

i64 gcd(i64 a, i64 b) {
    while(b) {
        const i64 bb = b;
        b = a % b;
        a = bb;
    }
    return a;
}

struct Q {
    i64 a, b;
    Q(i64 a, i64 b = 1) : a(a), b(b) {}
    Q operator+(Q o)const {
        Q r = {
            r.a = a * o.b + o.a * b,
            r.b = b * o.b
        };
        r.reduce();
        return r;
    }
    Q inv()const {
        Q r {b, a};
        r.reduce();
        return r;
    }
    void reduce() {
        const i64 g = gcd(a, b);
        a /= g;
        b /= g;
    }
};

bool isNum(char c) { return c >= '0' && c <= '9'; }

constexpr int bufSize = 10 * 1024 * 1024;
char s[bufSize];
i64 nn[10 * 1024];

int main()
{
    int w, h;
    scanf("%d %d", &h, &w);
    fgets(s, bufSize, stdin);
    while(w != 0)
    {
        const int n = (h+1)/2;
        for(int y = 0; y < n; y++) {
            fgets(s, bufSize, stdin);
            if(2*y+1 != h)
                 fgets(s, bufSize, stdin);
            int i = 0;
            while(s[i] == '.') i++;
            nn[y] = 0;
            do {
                nn[y] = 10 * nn[y] + s[i] - '0';
                i++;
            } while(isNum(s[i]));
        }
        Q r = nn[n-1];
        for(int y = n-2; y >= 0; y--) {
            r = r.inv();
            r = r + nn[y];
        }
        printf("%ld %ld\n", r.a, r.b);
        scanf("%d %d", &h, &w);
        fgets(s, bufSize, stdin);
    }
}