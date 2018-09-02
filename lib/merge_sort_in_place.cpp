#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& os, const vector<int>& v) {
    os << "{";
    for(int i=0; i<v.size()-1; i++)
        os << v[i] << ", ";
    os << v.back() << "}";
}

void shiftVectorRight(vector<int>& a, int n)
{
    const int N = a.size();
    for(int i = n-1; i >= 0; i--)
    {
        int j = N - n + i;
        a[j] = a[i];
    }
}

void sortedMergeInPlace(vector<int>& a, const vector<int>& b)
{
    const int an = a.size();
    const int bn = b.size();
    const int n = an + bn;
    a.resize(an + bn);
    shiftVectorRight(a, an);
    int i = 0, j = 0;
    while(i < an && i < bn)
    {
        if(a[i + bn] < b[j]) {
            a[i+j] = a[i+bn];
            i++;
        }
        else {
            a[i+j] = b[j];
            j++;
        }
    }
    while(i < an) {
        a[i+j] = a[i+bn];
        i++;
    }
    while(j < bn) {
        a[i+j] = b[j];
        j++;
    }
}

int main()
{
    std::vector<int> a = {1, 3, 5, 7};
    std::vector<int> b = {2, 4, 6};
    sortedMergeInPlace(a, b);
    cout << a << endl;
}