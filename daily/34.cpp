#include <iostream>
#include <string>
#include <vector>

using namespace std;

string pali(const string& s)
{
    string res = "";
    int i = 0;
    int j = s.size()-1;
    while(i < j) {
        if(s[i] == s[j]) {
            res += s[i];
            i++; j--;
        }
        else if(s[i] < s[j]) {
            res += s[i];
            i++;
        }
        else {
            res += s[j];
            j--;
        }
    }
    int back = res.size()-1;
    if(i == j) { 
        res += s[i];
    }
    for(int i=back; i>=0; i--)
        res += res[i];
    return res;
}

int main()
{
    vector<string> v = {
        "a",
        "ab",
        "ba",
        "abc",
        "cba"
    };
    for(const string& s : v) {
        cout << pali(s) << endl;
    }
}