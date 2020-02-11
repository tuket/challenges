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

struct Person {
    int dayHappy = -1;
    int friendsReward = 0;
};

int N, M, K;
vector<Person> people;
unordered_map<int, vector<int>> F;

void addFriendship(int a, int b)
{
    auto it = F.find(a);
    if(it == F.end()) {
        F[a] = vector<int>{b};
    }
    else {
        it->second.push_back(b);
    }
}

int numHappy = 0;
void addReward(int p, int x, int day)
{
    auto it = F.find(p);
    if(it == F.end())
        return;
    for(int f : it->second) {
        people[f].friendsReward += x;
        if(people[f].dayHappy == -1 && people[f].friendsReward >= K) {
            people[f].dayHappy = day;
            numHappy++;
        }
    }
}

int main()
{
    cin >> N >> M >> K;

    people.resize(N);

    for(int i=0; i<M; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        addFriendship(a, b);
        addFriendship(b, a);
    }

    int Q;
    cin >> Q;
    for(int q = 0; q < Q && numHappy < N; q++) {
        int p, x;
        cin >> p >> x;
        p--;
        addReward(p, x, q+1);
    }

    for(Person p : people) {
        cout << p.dayHappy << " ";
    }
    cout << endl;
}