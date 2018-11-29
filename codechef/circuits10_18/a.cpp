#include <iostream>

using namespace std;

int gcd(int a, int b){
	while(b){
		int bb = b;
		b = a % b;
		a = bb;
	}
	return a;
}

int solve(const int N, int a, int b)
{
    const int g = gcd(a, b);
    a /= g;
    b /= g;
    const int d = a + b;
    int res = ((N+1) * (N+2)) / 2;
    if(d<=N) {
        const int xd = N - d;
        res -= ((xd+1)*(xd+2)) / 2;
    }
    return res;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int N, a, b;
        cin >> N >> a >> b;
        int sol = solve(N, a, b);
        cout << sol << endl;
    }
}