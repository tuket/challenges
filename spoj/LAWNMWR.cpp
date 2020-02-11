#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

static constexpr int bufSize = 4*1024*1024;
char buf[bufSize];

typedef long long ll;

struct FP {
    static constexpr int DM = 10'000'000;
    FP(int a = 0, int b = 0) : x(DM*a + b) {}
    ll x;
    FP operator+(FP o) const {
        FP res;
        res.x = x + o.x;
        return res;
    }
    FP operator-(FP o) const {
        FP res;
        res.x = x - o.x;
        return res;
    }
    FP operator/(ll o) const {
        FP res;
        res.x = x / o;
        return res;
    }
    bool operator<(FP o) const { return x < o.x; }
    bool operator>(FP o) const { return x > o.x; }
    bool operator<=(FP o) const { return x <= o.x; }
    bool operator>=(FP o) const { return x >= o.x; }
    bool operator==(FP o) const { return x == o.x; }
    bool operator!=(FP o) const { return x != o.x; }
};

struct R {
    FP a, b;
};

bool isNum(char c) {
    return c >= '0' && c <= '9';
}

int parseInt(const char* (&p))
{
    int r = 0;
    while(!isNum(*p)) p++;
    while(isNum(*p)) {
        r *= 10;
        r += *p - '0';
        p++;
    }
    return r;
}

FP parseFp(const char* (&p))
{
    FP r {0, 0};
    r.x = FP::DM * parseInt(p);
    p++;
    //p++;
    r.x += parseInt(p);
    return r;
}

void subs(R& o1, R& o2, R x1, R x2)
{
    o1 = {
        x1.a,
        min(x1.b, x2.a - FP(0, 1))
    };
    o2 = {
        max(x1.a, x2.b + FP(0, 1)),
        x1.b
    };
}

void cut(vector<R>& f, FP x, FP w)
{
    vector<R> res;
    R x2 = {x - w/2, x + w/2};
    for(R x1 : f) {
        R o1, o2;
        subs(o1, o2, x1, x2);
        if(o1.a <= o1.b)
            res.push_back(o1);
        if(o2.a <= o2.b)
            res.push_back(o2);
    }
    swap(res, f);
}

int main()
{
    while(true)
    {
        char* pw = buf;
        const char* p = buf;
        fgets(pw, bufSize, stdin);
        pw += strlen(pw);
        *(pw++) = ' ';

        int nx, ny;
        FP w;
        nx = parseInt(p);
        ny = parseInt(p);
        w = parseFp(p);
        //fprintf(stderr, "--- %d %d %lld\n", nx, ny, w.x);
        if(nx == 0 && ny == 0 && w == 0)
            break;

        fgets(pw, bufSize, stdin);
        pw += strlen(pw);
        *(pw++) = ' ';
        fgets(pw, bufSize, stdin);
        
        vector<R> chuX = {R{0, 75}};
        for(int i = 0; i < nx; i++) {
            const FP x = parseFp(p);
            //fprintf(stderr, "chuX: %lld\n", x.x);
            cut(chuX, x, w);
            if(chuX.empty())
                break;
        }
        vector<R> chuY = {R{0, 100}};
        for(int i = 0; i < ny; i++) {
            const FP y = parseFp(p);
            //fprintf(stderr, "chuY: %lld\n", y.x);
            cut(chuY, y, w);
            if(chuY.empty())
                break;
        }

        if(chuX.empty() && chuY.empty())
            printf("YES\n");
        else
            printf("NO\n");
    }
}