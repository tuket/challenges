#include <iostream>
#include <array>

using namespace std;
typedef array<int, 4> V4;

int W, H, A;
V4 v;

int area(const V4& v)
{
    return v[0] * v[1] - v[2] * v[3];
}

int minEstim(const V4& v, int n)
{
    V4 vv = v;
    for(int i=n; i<4; i++)
    {
        if(i<2)
            vv[i] = 0;
        else if(i == 2)
            vv[i] = v[1];
        else
            vv[i] = vv[0];
    }
    return area(vv);
}

int maxEstim(const V4& v, int n)
{
    V4 vv = v;
    for(int i=n; i<4; i++)
    {
        if(i == 0)
            vv[i] = W;
        else if(i == 1)
            vv[i] = H;
        else
            vv[i] = 0;
    }
    return area(vv);
}

void binFind(int n, int& lb, int& ub)
{
    bool increasing = n == 0 || n == 1;
    int LB = lb, UB = ub;
    int i = LB;
    int j = UB;
    while(i<j)
    {
        int ij = (i+j) / 2;
        v[n] = ij;
        int mine = minEstim(v, n+1);
        if(mine == A) {
            i = j = ij;
            break;
        }
        if(increasing) {
            
            if(mine > A)
                j = ij-1;
            else
                i = ij+1;
        }
        else {
            if(mine > A)
                i = ij+1;
            else
                j = ij-1;
        }
    }
    if(increasing)
        ub = i;
    else
        lb = i;

    i = LB; j = UB;
    while(i<j)
    {
        int ij = (i+j) / 2;
        v[n] = ij;
        int maxe = maxEstim(v, n+1);
        if(maxe == A) {
            i = j = ij;
            break;
        }
        if(increasing) {
            
            if(maxe > A)
                j = ij-1;
            else
                i = ij+1;
        }
        else {
            if(maxe > A)
                i = ij+1;
            else
                j = ij-1;
        }
    }
    if(increasing)
        lb = i;
    else
        ub = i;
}

bool binFind(int n)
{
    if(minEstim(v, n) > A || maxEstim(v, n) < A)
        return false;
    
    int i = 0, j;
    if(n == 0) {
        j = W;
    }
    else if(n == 1) {
        j = H;
    }
    else if(n == 2) {
        j = v[1];
    }
    else if(n == 3) {
        j = v[0];
    }
    else {
        return true;
    }   

    binFind(n, i, j);
    for(int ij=i; ij<=j; ij++)
    {
        v[n] = ij;
        if(binFind(n+1))
            return true;
    }
    return false;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        cin >> W >> H >> A;
        cout << "Case #" << kk << ": ";
        if(!binFind(0)) {
            cout << "IMPOSSIBLE" << endl;
        }
        else {
            cout << "0 0 " << v[0] << " " << v[2] << " " << v[3] << " " << v[1] << endl;
        }
    }
}