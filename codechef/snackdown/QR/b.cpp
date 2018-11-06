#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<int> primes = {2, 3, 5, 7 , 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199};

bool R[201] = {false};

void precomp()
{
    const int np = primes.size();
    set<int> semiPrimes;
    for(int i=0; i<np; i++)
    {
        int p1 = primes[i];
        for(int j=i+1; j<np; j++)
        {
            int p2 = primes[j];
            int sp = p1 * p2;
            if(sp > 200) break;
            semiPrimes.insert(sp);
        }
    }
    vector<int> SP(semiPrimes.begin(), semiPrimes.end());
    const int nsp = SP.size();
    for(int i=0; i<nsp; i++)
    {
        int p1 = SP[i];
        for(int j=i; j<nsp; j++)
        {
            int p2 = SP[j];
            int sp2 = p1 + p2;
            if(sp2 > 200) break;
            R[sp2] = true;
        }
    }
}

int main()
{
    precomp();
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n;
        cin >> n;
        cout << (R[n] ? "YES" : "NO") << endl;
    }
}