#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

struct P{
    int a, b;
};

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n, ne;
        cin >> n >> ne;
        
        vector<int> bb(n);
        for(int& x : bb)
            cin >> x;
        
        vector<P> pp;
        for(int ie=0; ie<ne; ie++)
        {
            int a, b;
            string s;
            cin >> a >> s >> b;
            a--; b--;
            if(s[0] == '>')
                swap(a, b);
            pp.push_back({a, b});
        }

        map<int, set<int>> m;
        for(const P& p : pp) {
            if(m.count(p.a) == 0)
                m[p.a] = set<int>();
            m[p.a].insert(p.b);
        }

        set<int> lows;
        for(const P& p : pp)
            lows.insert(p.a);

        bool isValid = true;
        {
            set<int> seen, cur;
            vector<int> q;
            for(int x : lows) {
                q.push_back(x);
            }
            while(!q.empty() && isValid)
            {
                int a = q.back();
                q.pop_back();
                if(a < 0) {
                    cur.erase(-a-1);
                    continue;
                }
                else {
                    cur.insert(a);
                    q.push_back(-a-1);
                }
                for(int b : m[a]) {
                    if(cur.count(b)) {
                        isValid = false;
                        break;
                    }
                    if(seen.count(b) == 0) {
                        q.push_back(b);
                        seen.insert(b);
                    }
                }
            }
        }

        if(!isValid) {
            cout << "NO" << endl;
            continue;
        }

        for(const P& p : pp)
            lows.erase(p.b);        

        vector<set<int>> dToI;
        map<int, int> iToD;
        queue<P> q;
        for(int x : lows)
            q.push({x, 0});
        while(!q.empty())
        {
            P xd = q.front();
            q.pop();
            if(iToD.count(xd.a))
                dToI[iToD[xd.a]].erase(xd.a);
            if(xd.b >= dToI.size())
                dToI.resize(xd.b+1);
            dToI[xd.b].insert(xd.a);
            iToD[xd.a] = xd.b;
            for(int b : m[xd.a])
                q.push({b, xd.b+1});
        }

        vector<int> A(n, 0);
        for(int d=0; d<dToI.size(); d++) {
            for(int j : dToI[d])
                A[j] = d+1;
        }

        for(int i=0; i<n; i++)
        {
            if(i == n-1)
                A[i] = bb[i] + 1;
            else if(A[i] == 0)
                A[i] = bb[i];
            else
            {
                int md = 0;
                int minSeen = n;
                for(; i<n; i++)
                {
                    if(A[i] != 0)
                        minSeen = min(minSeen, A[i]);

                    if(i == n-1)
                        A[i] = bb[i]+1;
                    else if(A[i] == 0)
                        A[i] = bb[i];
                    else if(A[i]+md < bb[i]) {
                        md = max(md, bb[i]-A[i]);
                        A[i] = bb[i];
                    }
                    else {
                        md = max(md, bb[i]-A[i]);
                        A[i] = bb[i]+1;
                        for(i++; i<n; i++)
                        {
                            if(A[i] > minSeen)
                                A[i] += md;
                            else if(A[i] == 0)
                                A[i] = 1;
                        }
                    }
                }
            }
        }

        cout << "YES" << endl;
        for(int i=0; i<n; i++)
            cout << A[i] << " ";
        cout << endl;
    }
}