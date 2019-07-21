#include <bits/stdc++.h>

using namespace std;

typedef int64_t i64;
typedef uint64_t u64;

template <typename T>
string toString(const vector<T>& v, string sep = " ")
{
    if(v.size() == 0)
        return "";
    stringstream ss;
    for(size_t i=0; i<v.size()-1; i++)
    {
        ss << v[i] << sep;
    }
    ss << v.back() << endl;
    return ss.str();
}
// -------------------------------------------------------------------------

struct Person {
    unsigned x, y;
    char dir;
};

struct Zone {
    unsigned x0, y0;
    unsigned x1, y1;
    unsigned count = 0;
};

bool operator<(Zone a, Zone b)
{
    return
        a.count > b.count ? true:
        a.count < b.count ? false:
        a.x0 < b.x0 ? true:
        a.x0 > b.x0 ? false:
        a.y0 < b.y0;
}

unsigned Q;

void addPerson(vector<Zone>& zones, Person person)
{
    unsigned x = person.x;
    unsigned y = person.y;
    static vector<Zone> newZones;
    newZones.clear();
    for(Zone zone : zones)
    {
        if(person.dir == 'N') {
            if(zone.y0 > y && zone.y1 > y) {
                zone.count++;
                newZones.push_back(zone);
            }
            else if(zone.y0 <= y && zone.y1 > y) {
                Zone newZone;
                newZone.x0 = zone.x0;
                newZone.x1 = zone.x1;
                newZone.y0 = zone.y0;
                newZone.y1 = y+1;
                newZone.count = zone.count;
                zone.y0 = y+1;
                zone.count++;
                newZones.push_back(zone);
                newZones.push_back(newZone);
            }
            else {
                newZones.push_back(zone);
            }
        }
        else if(person.dir == 'S') {
            if(zone.y0 < y && zone.y1 < y) {
                zone.count++;
                newZones.push_back(zone);
            }
            else if(zone.y0 < y && zone.y1 >= y) {
                Zone newZone;
                newZone.x0 = zone.x0;
                newZone.x1 = zone.x1;
                newZone.y1 = zone.y1;
                newZone.y0 = y-1;
                newZone.count = zone.count;
                zone.y1 = y-1;
                zone.count++;
                newZones.push_back(zone);
                newZones.push_back(newZone);
            }
            else {
                newZones.push_back(zone);
            }
        }
        else if(person.dir == 'E') {
            if(zone.x0 > x && zone.x1 > x) {
                zone.count++;
                newZones.push_back(zone);
            }
            else if(zone.x0 <= x && zone.x1 > x) {
                Zone newZone;
                newZone.y0 = zone.y0;
                newZone.y1 = zone.y1;
                newZone.x0 = zone.x0;
                newZone.x1 = x+1;
                newZone.count = zone.count;
                zone.x0 = x+1;
                zone.count++;
                newZones.push_back(zone);
                newZones.push_back(newZone);
            }
            else {
                newZones.push_back(zone);
            }
        }
        else { // W
            if(zone.x0 < x && zone.x1 < x) {
                zone.count++;
                newZones.push_back(zone);
            }
            else if(zone.x0 < x && zone.x1 >= x) {
                Zone newZone;
                newZone.y0 = zone.y0;
                newZone.y1 = zone.y1;
                newZone.x1 = zone.x1;
                newZone.x0 = x-1;
                newZone.count = zone.count;
                zone.x1 = x-1;
                zone.count++;
                newZones.push_back(zone);
                newZones.push_back(newZone);
            }
            else {
                newZones.push_back(zone);
            }
        }
    }
    swap(zones, newZones);
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        unsigned np;
        cin >> np >> Q;
        vector<Person> people(np);
        for(Person& p : people) {
            cin >> p.x >> p.y >> p.dir;
        }
        Zone allZone;
        allZone.x0 = allZone.y0 = 0;
        allZone.x1 = allZone.y1 = Q;
        vector<Zone> zones;
        zones.push_back(allZone);
        for(Person p : people)
            addPerson(zones, p);
        Zone zone = *min_element(zones.begin(), zones.end());
        cout << "Case #" << kk << ": "
            << zone.x0 << " " << zone.y0 << endl;
    }

}
