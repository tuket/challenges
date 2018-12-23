#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <fstream>

using namespace std;

const int N = 9;
int H[1 << N];

array<vector<bool>, 11> happy;
array<vector<bool>, 11> notHappy;

int next(int b, int n)
{
    int res = 0;
    while(n / b)
    {
        int x = n % b;
        res += x * x;
        n /= b;
    }
    res += n * n;
    return res;
}

int main()
{
    vector<int> toDo(1 << N);
    for(int i=0; i< (1<<N); i++)
    {
        H[i] = -1;
        toDo[i] = i;
    }
    
    for(int i=2; toDo.size(); i++)
    {
        int mask = 0;
        for(int j=0; j<N; j++)
        {
            int b = 2+j;
            set<int> seen = {i};
            if(i < happy[b].size() && happy[b][i])
            {
                mask |= (1 << j);
                continue;
            }
            int x = next(b, i);
            while(
                x != 1 && seen.count(x) == 0 &&
                (x >= notHappy[b].size() || notHappy[b][x] == false) &&
                (x >= happy[b].size() || happy[b][x] == false))
            {
                seen.insert(x);
                x = next(b, x);
            }
            if(x == 1 || (x < happy[b].size() && happy[b][x]))
            {
                mask |= (1 << j);
                happy[b].resize(i+1);
                happy[b][i] = true;
            }
            else
            {
                notHappy[b].resize(i+1);
                notHappy[b][i] = true;
            }
        }
        for(int j=0; j<toDo.size(); )
        {
            int bb = toDo[j];
            if((bb | mask) == mask)
            {
                H[bb] = i;
                toDo[j] = toDo.back();
                toDo.pop_back();
            }
            else
                j++;
        }
    }

    ofstream fs("a.cpp");

    fs <<
R"(#include <iostream>
#include <sstream>

using namespace std;

const int N = 9;
const int R[1 << N] = {)";

    for(int i=0; i < (1 << N); i++)
        fs << H[i] << ", ";
    fs << "};" << endl;

    fs <<
R"(
int main()
{
    int nn;
    cin >> nn;
    string s;
    getline(cin, s);
    for(int kk=1; kk<=nn; kk++)
    {
        getline(cin, s);
        stringstream ss(s);
        int mask = 0;
        int b;
        while(ss >> b)
        {
            mask |= (1 << (b-2));
        }
        cout << "Case #" << kk << ": " << R[mask] << endl;
    }
}
)";

}