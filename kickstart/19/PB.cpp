#include <iostream>

using namespace std;

inline int toNum(char c)
{
    return c - '0';
}

int calc(const string& s)
{
    int n = s.size();
    n = (n+1) / 2;
    int sum = 0;
    for(int i=0; i<n; i++)
        sum += toNum(s[i]);
    int best = sum;
    for(int i=n; i<s.size(); i++) {
        sum -= s[i-n];
        sum += s[i];
        best = max(best, sum);
    }
    return best;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n;
        cin >> n;
        string s;
        cin >> s;
        cout << "Case #" << kk << ": " << calc(s) << endl;
    }
}