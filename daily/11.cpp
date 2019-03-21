#include <iostream>
#include <string>

using namespace std;

int main()
{
	string s;
	cin >> s;
	int i = 0;
	int j = s.size();
	string res;
	while(i <= j)
	{
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
	cerr << res << endl;
	for(i = res.size()-2; i>=0; i--) {
		res += res[i];
	}
	cout << res << endl;
}
