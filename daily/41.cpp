#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <utility>
#include <string>

using namespace std;

int main()
{
    /*vector<pair<string, string>> P = {
        {"A", "B"}, {"A", "C"}, {"B", "C"}, {"C", "A"}
    };
    string cur = "A";*/
    vector<pair<string, string>> P = {
        {"SFO", "HKO"}, {"YYZ", "SFO"}, {"YUL", "YYZ"}, {"HKO", "ORD"}
    };
    string cur = "YUL";

    unordered_map<string, set<string>> M;
    for(const auto& p : P)
    {
        auto it = M.find(p.first);
        if(it == M.end()) {
            M[p.first] = {};
            it = M.find(p.first);
        }
        it->second.insert(p.second);
    }
    vector<string> itinerary = {};
    for(auto it = M.find(cur); ; )
    {
        itinerary.push_back(cur);
        if(it == M.end() || it->second.size() == 0) {
            break;
        }
        auto it0 = it->second.begin();
        cur = *it0;
        it->second.erase(it0);
        it = M.find(cur);
    }
    for(string airport : itinerary)
        cout << airport << endl;
}