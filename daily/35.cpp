#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s = "GBR";
    const int n = s.size();
    // sort R
    int back = 0;
    for(int i=0; i<n; i++) {
        if(s[i] == 'R') {
            swap(s[i], s[back]);
            back++;
        }
    }
    // sort by G
    for(int i=back; i<n; i++) {
        if(s[i] == 'G') {
            swap(s[i], s[back]);
            back++;
        }
    }
    cout << s << endl;
}