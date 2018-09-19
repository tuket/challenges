#include <iostream>
#include <vector>

using namespace std;

// i: index
// n: current cards
/*
int f_recursive(int N, int n, int i)
{
    int j = (N - n) % n;
    if(j == i) return N - n;
    else if(i < j) {
        return f(N, n-1, i+n-j-1);
    }
    else {
        return f(N, n-1, i-j-1);
    }
}
*/

int f_iterative(int N, int i)
{
    int n = N;
    for(int n=N; n>0; n--)
    {
        int j = (N - n) % n;
        if(j == i) return N - n;
        else if(i < j) {
            i = i+n-j-1;
        }
        else {
            i = i-j-1;
        }
    }
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int N, n;
        cin >> N >> n;
        vector<int> v(n);
        for(auto& i : v)
            cin >> i;
        cout << "Case #" << kk << ":";
        for(auto i : v)
            cout << " " << f_iterative(N, i-1) + 1;
        cout << endl;
    }
}
