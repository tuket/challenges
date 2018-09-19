#include <iostream>
#include <vector>

using namespace std;

// solves the problem for all indices

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "(";
    if(v.size() > 0)
        os << v[0];
    for(int i=1; i<v.size(); i++) os << " " << v[i];
    os << ")";
    return os;
}

void deck(int n)
{
    vector<int> v(1);
    v[0] = n-1;
    for(int i=n-2; i>=0; i--)
    {
        int l = n - i;
        int j = i % l;
        vector<int> newV(l);
        for(int jj=0; jj<j; jj++)
        {
            newV[jj] = v[l-j-1+jj];
        }
        newV[j] = i;
        for(int jj=j+1; jj<l; jj++)
        {
            newV[jj] = v[jj-j-1];
        }
        v = newV;
    }
    cout << v << endl;
}

int main()
{
    int N = 20;
    for(int n=1; n <= N; n++)
    {
        deck(n);
    }
}