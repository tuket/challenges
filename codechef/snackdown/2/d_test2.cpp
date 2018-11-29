#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define slld(x) scanf("%lld", &x)
#define nl printf("\n")
#define plld(x) printf("%lld\n", x)
#define pllds(x) printf("%lld ", x)
#define fr(i, a, b) for(i=a; i<b; i++)
#define pb push_back
#define mp make_pair 
#define ft first
#define sd second
#define pcc pair<char,char>
#define pll pair<ll,ll>
#define vll vector<ll>
#define vpll vector< pll >
#define tr(container,it) for(it=container.begin();it!=container.end();it++)
#define clr(a) memset(a,0,sizeof(a))
#define all(v) v.begin(), v.end()
#define MAX 200008
#define mod 1000000007
ll fpow(ll x, ll y) {ll r = 1;  while(y > 0){if(y & 1) r = (r * x) % mod; y >>= 1;  x = (x * x) % mod;} return r;}
ll inv(ll n) {return fpow(n, mod-2);}
ll add(ll x, ll y) { return ( (x%mod)+(y%mod) ) % mod; }
ll sub(ll x, ll y) { return ( (x%mod)-(y%mod) + mod ) % mod; }
ll mul(ll x, ll y) { return ( (x%mod)*(y%mod) ) % mod; }
ll lcm(ll a, ll b) {return (a*b) / __gcd(a, b) ;}

bool can(ll x, ll y, ll z){
	if(x+y>z && x+z>y && y+z > x)
		return true;
	return false;
}

bool com(pll a, pll b){
	return (1LL*a.ft*b.sd >= 1LL*a.sd*b.ft); 
}

int main(){
    ll i, j, n, _max, _min, ans, t, m, k, p, q, x, y, z, dx, dy, dz;
    slld(t);
    while(t--){
    	slld(n);slld(p);slld(q);
    	ll a[n+1];
    	for(i=0; i<n; i++)
    		slld(a[i]);
    	if(n<3){
    		plld(-1LL);
    		continue;
    	}
    	set< pll > s;
    	vll v1, v2;
    	for(i=0; i<n; i++){
    		s.insert(mp(a[i]*a[i]*q, i));
    	}
    	set< pll > ::iterator it;
    	for(it = s.begin(); it != s.end(); it++){
    		v1.pb(it->ft);
    		v2.pb(it->sd);
    	}
    	pll theta = mp(2LL, 1LL);

    	for(i=0; i<n; i++){
    		for(j=i+1; j<n; j++){
    			m = (a[i]*a[i] + a[j]*a[j])*q - 2LL*a[i]*a[j]*p;
    			k = upper_bound(all(v1), m)-v1.begin();
    			k--;
    			while(k>=0 && (v2[k] == i || v2[k] == j)) k--;
    			if(k < 0) continue;
	    		x = a[i];y=a[j];z=a[v2[k]];
	    		if(!can(x, y, z))continue;
	    		//pllds(x);pllds(y);plld(z);
	    		pll tmp = mp(x*x+y*y-z*z, 2LL*x*y);
	    		//pllds(tmp.ft);plld(tmp.sd);
	    		if(com(tmp, mp(p, q)) && com(theta, tmp)){
    				theta = tmp;
	    			dx = v2[k]+1;
	    			dy = i+1;
	    			dz = j+1; 
	    			//pllds(x);pllds(y);pllds(z);
	    			//pllds(tmp.ft);plld(tmp.sd);
	    		}		
    		}
    	}
    	if(theta.ft == 2LL){
    		plld(-1LL);
    	}
    	else{
    		pllds(dx);pllds(dy);plld(dz);
    	}
    	
    }
    return 0;
}
