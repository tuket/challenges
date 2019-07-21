#include <iostream>
#include <vector>

using namespace std;

bool intersect(const vector<int>& A, const vector<int>& B)
{
    const int n = A.size();
    if(A[0] == B[0])
        return true;
    int a0 = A[0];
    int b0 = B[0];
    for(int i=0; i<n; i++)
    {
        int a1 = A[i];
        int b1 = B[i];
        if(a1 == b1)
            return true;
        if(a0 < b0 && a1 > b1)
            return true;
        if(a0 > b0 && a1 < b1)
            return true;
        a0 = a1;
        b0 = b1;
    }
    return false;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n, k;
        cin >> n >> k;
        vector<vector<int>> v(n, vector<int>(k));
        for(int i=0; i<n; i++) {
            for(int j=0; j<k; j++) {
                cin >> v[i][j];
            }
        }

        vector<vector<bool>> G(n, vector<bool>(n, true));
        for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
        {
            const bool inter = intersect(v[i], v[j]);
            G[i][j] = G[j][i] = inter;
        }

        
    }
}