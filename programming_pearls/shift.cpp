#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>

using namespace std;

template <typename T>
void vecSwap(vector<T>& v, int i1, int  i2, int n) {
    for(int i=0; i < n; i++) {
        swap(v[i1+i], v[i2+i]);
    }
}

// 1: revese and reverse
template <typename T>
void rotateShift1(vector<T>& v, int n)
{
    int vn = v.size();
    while(n < 0) n += vn;
    while(n >= vn) n -= vn;
    reverse(v.begin(), v.end());
    reverse(v.begin(), v.begin() + n);
    reverse(v.begin() + n, v.end());
}

// 2: recursive left-right swap
template <typename T>
void rotateShift2(vector<T>& v, int n, int i, int j)
{
    if(i >= j) return;
    int vn = j - i + 1;
    while(n > vn / 2) n -= vn;
    while(n <= -vn / 2) n += vn;
    if(n == 0) return;
    else if(n < 0) {
        vecSwap(v, i, j+n+1, -n);
        rotateShift2(v, n, i, j+n);
    }
    else {
        vecSwap(v, i, j-n+1, +n);
        rotateShift2(v, n, i+n, j);
    }
}

template <typename T>
void rotateShift2(vector<T>& v, int n)
{
    rotateShift2(v, n, 0, v.size()-1);
}

// 3: same as 2 but made iterative
template <typename T>
void rotateShift3(vector<T>& v, int n, int i, int j)
{
    while(i < j){
        int vn = j - i + 1;
        while(n > vn / 2) n -= vn;
        while(n <= -vn / 2) n += vn;
        if(n == 0) return;
        else if(n < 0) {
            vecSwap(v, i, j+n+1, -n);
            j = j + n;
        }
        else {
            vecSwap(v, i, j-n+1, +n);
            i = i + n;
        }
    }
}

template <typename T>
void rotateShift3(vector<T>& v, int n)
{
    rotateShift3(v, n, 0, v.size()-1);
}

void print(const vector<int>& v)
{
    for(int x : v)
        cout << x << endl;
}

class Timer {
    chrono::steady_clock::time_point t1, t2;
public:
    void start() {
        t1 = chrono::steady_clock::now();
    }
    void stop() {
        t2 = chrono::steady_clock::now();
    }
    chrono::milliseconds elapsed()const {
        using namespace chrono;
        return duration_cast<milliseconds>(t2 - t1);
    }
};

void test();
void benchmark();

int main()
{
    test();
    benchmark();
}

void test()
{
    const unsigned N = 10;
    vector<int> v1(N);
    iota(v1.begin(), v1.end(), 0);
    vector<int> v2(N);
    iota(v2.begin(), v2.end(), 0);
    vector<int> v3(N);
    iota(v3.begin(), v3.end(), 0);
    bool ok = true;
    for(int i = 0; i < N/2; i++)
    {
        rotateShift1(v1, i);
        rotateShift2(v2, i);
        rotateShift3(v3, i);
        if(v1 != v2 || v1 != v3) {
            ok = false;
            break;
        }
    }
    cout << "test: " << (ok ? "ok!" : "failed!") << endl;
}

void benchmark()
{
    vector<int> v(40000);
    iota(v.begin(), v.end(), 0);

    Timer timer;

    timer.start();
    for(int i = 0; i < v.size()/2; i++) {
        rotateShift1(v, 1);
    }
    timer.stop();
    cout << "rotateShift1: " << timer.elapsed().count() << endl;

    timer.start();
    for(int i = 0; i < v.size()/2; i++) {
        rotateShift2(v, 1);
    }
    timer.stop();
    cout << "rotateShift2: " << timer.elapsed().count() << endl;

    timer.start();
    for(int i = 0; i < v.size()/2; i++) {
        rotateShift3(v, 1);
    }
    timer.stop();
    cout << "rotateShift2: " << timer.elapsed().count() << endl;
}

/*
    OUTPUT:
    test: ok!
    rotateShift1: 16111
    rotateShift2: 17551
    rotateShift2: 13054
*/