#include <iostream>
#include <string>

using namespace std;

#define IMPL 0

#if IMPL == 0
bool regexMatch(const string& regex, const string& str, int i = 0, int j = 0)
{
    if(i == regex.size() || j == str.size()) {
        if(i == regex.size() && j == str.size())
            return true;
        return false;
    }
    if(regex[i] == '.')
        return regexMatch(regex, str, i+1, j+1);
    else if(regex[i] == '*')
        return regexMatch(regex, str, i, j+1) || regexMatch(regex, str, i+1, j);
    else if(regex[i] == str[j])
        return regexMatch(regex, str, i+1, j+1);
    return false;
}
#else if IMPL == 1
bool regexMatch(const string& regex, const string& str)
{
    
}
#endif

int main()
{
    cout
        << regexMatch("ray", "ray") << endl;
}