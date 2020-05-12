#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;

struct Perm { int i0, i1, i2; };

vector<vector<int>> calcCycles(const vector<int>& v, int N)
{
    vector<vector<int>> cycles;
    set<int> seen;
    for(int i = 0; i < N; i++)
    if(seen.count(i) == 0 && v[i] != i)
    {
        vector<int> cycle = {i};
        for(int ind = v[i]; ind != i; ind = v[ind]) {
            cycle.push_back(ind);
        }
        for(int ind : cycle)
            seen.insert(ind);
        cycles.push_back(move(cycle));
    }
    return cycles;
}

void applyPerm(vector<int>& v, const Perm& p)
{
    const int aux = v[p.i0];
    v[p.i0] = v[p.i2];
    v[p.i2] = v[p.i1];
    v[p.i1] = aux;
}

void applyPerms(vector<int>& v, const vector<Perm>& perms)
{
    for(auto& p : perms)
        applyPerm(v, p);
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk = 1; kk <= nn; kk++)
    {
        int N, K;
        cin >> N >> K;
        vector<int> v(N);
        for(int i = 0; i < N; i++) {
            cin >> v[i];
            v[i]--;
        }

        vector<Perm> res;
        vector<vector<int>> cycles = calcCycles(v, N);
        /*for(auto& cycle : cycles) {
            printf("{");
            for(int x : cycle)
                printf("%d, ", x);
            printf("}\n");
        }*/
        // do odd cycles
        for(const auto& cycle : cycles)
        if(cycle.size() % 2 == 1) {
            for(int i = 1; i < cycle.size(); i += 2) {
                res.push_back({cycle[0], cycle[i], cycle[i+1]});
            }
        }
        // do even cycles
        vector<int> carry;
        for(const auto& cycle : cycles)
        if(cycle.size() % 2 == 0) {
            for(int i = 1; i < cycle.size()-1; i += 2) {
                res.push_back({cycle[0], cycle[i], cycle[i+1]});
            }
            if(carry.size()) {
                res.push_back({carry[0], cycle[0], cycle.back()});
                res.push_back({carry[0], cycle[0], carry[1]});
                carry.clear();
            }
            else {
                carry = {cycle[0], cycle.back()};
            }
        }

        /*applyPerms(v, res);
        printf("* ");
        for(int x : v)
            printf("%d ", x);
        printf("\n");*/

        if(carry.size()) {
            printf("-1\n");
        }
        else {
            printf("%d\n", int(res.size()));
            for(Perm p : res)
                printf("%d %d %d\n", p.i0+1, p.i1+1, p.i2+1);
        }
    }
}