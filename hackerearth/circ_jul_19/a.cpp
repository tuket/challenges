#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print(const vector<int>& v, char sep = '\n')
{
    for(int x : v)
        cout << x << sep;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        string s;
        cin >> s;
        const int n = s.size();
        vector<int> v1(n);
        int x = 0;
        for(int i=0; i<n; i++)
        {
            if(s[i] == '(')
                x++;
            v1[i] = x;
        }

        int best = 0;
        x = 0;
        for(int i=n-1; i >= 0; i--)
        {
            if(s[i] == ')')
                x++;
            best = max(best, min(v1[i], x));
        }

        //print(v);

        cout << 2*best << endl;
    }
}