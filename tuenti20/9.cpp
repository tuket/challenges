#include <iostream>
#include <string>

using namespace std;

char hexDig(char c)
{
    if(c >= 'A')
        return c - 'A' + 10;
    return c - '0';
}

string getKey(const string& msg, const string& cyf)
{
    const int n = msg.size();
    string r(n, ' ');
    for(int i = 0; i < n; i++)
    {
        char mc = msg[i];
        char kc = 16 * hexDig(cyf[2*i]) + hexDig(cyf[2*i+1]);
        r[n-i-1] = mc ^ kc;
    }
    return r;
}

string encrypt(const string& msg, const string& key)
{
    const int n = msg.size();
    string r(2*n, ' ');
    for(int i = 0; i < n; i++)
    {
        char a = msg[i];
        char k = key[n-i-1];
        char e = a ^ k;
        sprintf(&r[2*i], "%02X", (int)e);
    }
    return r;
}

string decrypt(const string& cyf, const string& key)
{
    const int n = key.size();
    string r(n, ' ');
    for(int i = 0; i < n; i++)
    {
        char cc = 16 * hexDig(cyf[2*i]) + hexDig(cyf[2*i+1]);
        char kc = key[n-i-1];
        r[i] = cc ^ kc;
    }
    return r;
}

int main()
{
    string sample = "514;248;980;347;145;332";
    string sampleCyf = "3633363A33353B393038383C363236333635313A353336";
    string msg = "3A3A333A333137393D39313C3C3634333431353A37363D";
    cout << decrypt(msg, getKey(sample, sampleCyf)) << endl;
}