#include <iostream>
#include <string>
#include <array>
#include <iomanip>

using namespace std;

constexpr char welc[] = "welcome to code jam";
constexpr unsigned N = sizeof(welc)-1;
array<array<int, N>, 2> a;

int main()
{
    int nn;
    cin >> nn;
    string s;
    getline(cin, s);
    for(int kk=1; kk<=nn; kk++)
    {
        getline(cin, s);
        const int n = s.size();
        a[0] = {0};
        for(int i=0; i<n; i++)
        {
            int from = i % 2;
            int to = from ^ 1;

            a[to] = a[from];
            if(s[i] == welc[0])
                a[to][0] = (a[to][0] + 1) % 10000;
            for(int j=1; j<N; j++)
            {
                if(s[i] == welc[j])
                    a[to][j] = (a[to][j] + a[from][j-1]) % 10000 ;
            }
        }
        cout << "Case #" << kk << ": " << setw(4) << setfill('0') << a[n%2][N-1] << endl;
    }
}