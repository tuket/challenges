#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void debugPrint(const vector<T>& v)
{
    for(const T& x : v)
        cerr << x << " ";
    cerr << endl;
}

int minMissingPositive(vector<int>& a)
{
    const int n = a.size();
    for(int i=0; i<n; )
    {
        int ai = a[i];
        if(ai > 0 && ai <= n && ai != i+1)
            swap(a[i], a[ai-1]);
        else
            i++;
    }
    for(int i=0; i<n; i++)
    {
        if(a[i] != i+1)
            return i+1;
    }
    return n+1;
}

int main()
{
    //vector<int> a = {3, 4, -1, 1};
    vector<int> a = {1, 2, 0};
    debugPrint(a);
    cout << minMissingPositive(a) << endl;
}