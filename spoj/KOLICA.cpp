#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

typedef int64_t i64;

i64 gcd(i64 a, i64 b) {
    while(b) {
        const i64 bb = b;
        b = a % b;
        a = bb;
    }
    return a;
}

struct K {
    i64 x, y;
    i64 vx, vy;
};

struct  Q {
    i64 a, b;
public:
    Q(i64 a, i64 b = 1) : a(a), b(b) { reduce(); }
    void reduce() {
        const i64 g = gcd(a, b);
        a /= g;
        b /= g;
        if(b < 0) {
            a = -a;
            b = -b;
        }
    }
    bool operator==(Q o) const { return a == o.a && b == o.b; }
    bool operator!=(Q o) const { return a != o.a || b != o.b; }
    bool operator<(Q o) const { return (a * o.b) < (o.a * b); }
    bool operator>(Q o) const { return (a * o.b) > (o.a * b); }
    Q operator+(Q o) const { Q r (a * o.b + o.a * b, b * o.b); return r; }
    Q operator*(Q o) const { Q r (a * o.a, b * o.b); return r; }
};

struct C {
    i64 a, b;
    Q t;
    Q x, y;
    bool operator<(C o) {
        return t != o.t ? t < o.t :
                x != o.x ? x < o.x :
                y < o.y;
    }
};

Q timeColli(K a, K b)
{
    const i64 t1Denom = b.vx - a.vx;
    const i64 t2Denom = b.vy - a.vy;
    if(t1Denom == 0) {
        if(a.x - b.x != 0)
            return -1;
        const Q t2(a.y - b.y, t2Denom);
        return t2;
    }
    else if(t2Denom == 0) {
        if(a.y - b.y != 0)
            return -1;
        const Q t1(a.x - b.x, t1Denom);
        return t1;
    }
    else {
        const Q t1(a.x - b.x, t1Denom);
        const Q t2(a.y - b.y, t2Denom);
        if(t1 != t2)
            return -1;
        return t1;
    }
}

int main()
{
    i64 n;
    cin >> n;
    vector<K> kk(n);
    for(i64 i = 0; i < n; i++) {
        cin >> kk[i].x >> kk[i].y;
        string s;
        cin >> s;
        switch(s[2]) {
            case 'r':
                kk[i].vx = 0;
                kk[i].vy = +1;
                break;
            case 'l':
                kk[i].vx = 0;
                kk[i].vy = -1;
                break;
            case 'j':
                kk[i].vx = -1;
                kk[i].vy = 0;
                break;
            case 's':
                kk[i].vx = +1;
                kk[i].vy = 0;
                break;
        }
    }

    vector<C> cc;
    for(i64 i = 0; i < n; i++) {
        K k = kk[i];
        for(i64 j = i+1; j < n; j++) {
            const Q t = timeColli(kk[i], kk[j]);
            if(t > 0) {
                cc.push_back({i, j, Q(k.x) + t * k.vx, Q(k.y) + t * k.vy, t});
            }
        }
    }
    sort(cc.begin(), cc.end());

    vector<bool> expl(n, false);
    for(i64 i = 0; i < cc.size(); i++) {
        set<i64> s;
        auto add = [&](i64 i) {
            if(!expl[cc[i].a])
                s.insert(cc[i].a);
            if(!expl[cc[i].b])
                s.insert(cc[i].b);
        };
        add(i);
        for(i64 j = i+1; j < cc.size(); j++) {
            if(cc[i].t != cc[j].t || cc[i].x != cc[j].x || cc[i].y != cc[j].y)
                break;
            add(j);
        }
        if(s.size() > 1) {
            for(i64 j : s)
                expl[j] = true;
        }
    }

    bool allExpl = true;
    for(i64 i = 0; i < n ; i++) allExpl &= expl[i];
    if(allExpl) {
        cout << "nema" << endl;
    }
    else {
        for(i64 i = 0; i < n ; i++)
        if(!expl[i])
            cout << i+1 << endl;
    }
}