#include <iostream>

using namespace std;

int main()
{
    string s;
    cin >> s;
    int prev1 = 1;
    int prev2 = 0;
    for(int i=s.size()-1; i>=0; i--)
    {
        //res++;
        int x0 = s[i] - '0';
        int x1 = s[i+1] - '0';
        if(x0 == 1 || (x0 == 2 && x1 <= 6)) {
            int prev0 = prev1 + prev2;
            prev2 = prev1;
            prev1 = prev0;
        }
        else {
            prev2 = prev1;
        }
    }
    cout << prev1 << endl;
}