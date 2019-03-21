#include <list>

using namespace std;

int main()
{
    list<int> a;
    list<int> b;
    list<int>::iterator i, j;
    if(a.size() < b.size()) {
        i = a.begin();
        j = b.begin();
        for(int _=0; _<b.size()-a.size(); _++)
            j++;
    }
    for(; i != j; i++, j++);
    int res = *i;
}