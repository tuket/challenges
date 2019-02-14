#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <numeric>

using namespace std;

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        array<int, 26> A{};
        string s;
        cin >> s;
        for(char c : s)
            A[c-'A']++;
        int SUM = accumulate(A.begin(), A.end(), 0);
        sort(A.begin(), A.end());
        int bestRes = numeric_limits<int>::max();
        int sum = 0;
        for(int i=0; i<26; i++)
        {
            if(SUM % (26-i) == 0)
            {
                int res = 0;
                int avg = SUM / (26-i);
                for(int j=i; j<26; j++)
                    res += abs(A[j] - avg);
                res += sum;
                res /= 2;
                bestRes = min(bestRes, res);
            }
            sum += A[i];
        }
        cout << bestRes << endl;
    }
}