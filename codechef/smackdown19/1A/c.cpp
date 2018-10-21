#include <iostream>
#include <vector>
#include <set>

using namespace std;

const vector<int> P = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

int gcd(int a, int b) {
  while (b != 0)  {
    int t = b;
    b = a % b;
    a = t;
  }
  return a;
}

int root(const vector<int>& tree, int i)
{
    while(tree[i] != i) i = tree[i];
    return i;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n;
        cin >> n;
        vector<int> v(n);
        for(int i=0; i<n; i++)
            cin >> v[i];
            
        vector<int> tree(n);
        for(int i=0; i<n; i++) tree[i] = i;

        for(int i=0; i<n-1; i++)
        {
            for(int j=i+1; j<n; j++)
            {
                if(gcd(v[i], v[j]) == 1)
                {
                    tree[root(tree, j)] = root(tree, i);
                }
            }
        }

        int r = 0;
        bool has47 = false;
        for(int i=0; i<n; i++) {
            if(tree[i] == i) r++;
            if(v[i] == 47) has47 = true;
        }

        if(r > 1) {
            cout << 1 << endl;
            v[0] = !has47 ? 47 : 43;
        }
        else {
            cout << 0 << endl;
        }
        cout << v[0];
        for(int i=1; i<n; i++)
        {
            cout << " " << v[i];
        }
        cout << endl;
    }
}