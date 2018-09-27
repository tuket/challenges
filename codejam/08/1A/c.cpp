#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 2000000000;

template<int N>
int pw(int n)
{
    static vector<int> v = [=](){
        vector<int> v(MAX_N+1);
        int x = 1;
        for(int i=0; i<MAX_N+1; i++) {
            v[i] = x;
            v[i] *= N;
            v[i] %= 1000;
        }
        return v;
    }();
    return v[n];
}

int fct(int n)
{
    static vector<int> v = [=](){
        vector<int> v(MAX_N+1);
        v[0] = 1;
        int x = 1;
        for(int i=1; i<MAX_N+1; i++) {
            v[i] = v[i-1] * i;
            v[i] %= 1000;
        }
        return v;
    }();
    return v[n];
}

vector<int> coeffs(int n)
{
    vector<int> res = {1, 1};
    res.reserve(n+1);
    for(int i=0; )
}

int solve(int n)
{

}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n;
        cin >> n;
        cout << "Case #" << kk << ": " << solve(n) << endl;
    }
}