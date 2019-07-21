#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;
    int i;
    for(i=0; i<=n; i++) {
        int j;
        for(j=i; j<n; j++) {
            if(a[j] != b[j-i])
                break;
        }
        if(j == n)
            break;
    }
    cout << i << endl;
}