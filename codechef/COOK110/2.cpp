#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

void yes() { cout << "YES" << endl; }
void no() { cout << "NO" << endl; }

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if(b >= 3 && b % 2 == 1 && c >= 2 && c % 2 == 0) {
            if(a % 2 == 0)
                yes();
            else
                no();
        }
        else {
            if(c % 2 == 0) {
                if(b % 2 == 0) {
                    if(a % 2 == 0)
                        yes();
                    else
                        no();
                }
                else {
                    if(a >= 2 && a % 2 == 0)
                        yes();
                    else
                        no();
                }
            }
            else {
                if(b == 0) {
                    if(a >= 3 && a % 2 == 1)
                        yes();
                    else
                        no();
                }
                else {
                    if(a % 2 == 1)
                        yes();
                    else
                        no();
                }
            }
        }
    }
}