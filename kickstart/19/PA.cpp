#include <iostream>
#include <string>

using namespace std;

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int A, B, N;
        cin >> A >> B >> N;
        A++;
        string o;
        while(true)
        {
            int AB = (A+B) / 2;
            cout << AB << endl;
            cin >> o;
            if(o == "CORRECT")
                break;
            else if(o == "TOO_SMALL") {
                A = AB + 1;
            }
            else {
                B = AB - 1;
            }
        }
    }
}
