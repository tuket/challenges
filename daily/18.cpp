#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int main()
{
    int N;  // number of houses
    int K;  // number of colors
    vector<vector<int>> M;

    vector<int> D[2];
    vector<int>* d0 = &D[0];
    vector<int>* d1 = &D[1];
    *d0 = M[0];
    for(int i=1; i<N; i++)
    {
        fill(*d1.begin(), d1.end(), numeric_limits<int>::max());
        for(int k0=0; k0<K; k0++)
        {
            for(int k1=0; k1<K; k1++)
            if(k0 != k1)
            {
                d1[k1] = min(d1[k1], d0[k0] + M[i][k1]);
            }
        }
        swap(d0, d1);
    }
    int res = min_element(d0->begin(), d0->end());
}