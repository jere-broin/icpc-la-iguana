//https://open.kattis.com/problems/generalchineseremainder
#include <bits/stdc++.h>
#define fore(i,a,b) for(ll i=a,jet=b; i<jet; i++)
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vv;
typedef __int128 xl;

ii extendedEuclid (ll a, ll b){ //a * x + b * y = gcd(a,b)
	if(!b) return {1,0};
	auto p=extendedEuclid(b,a%b); ll x=p.snd, y=p.fst-(a/b)*x;
	if(a*x+b*y<0) x=-x, y=-y;
	return {x,y};
}
ii diophantine(ll a,ll b,ll r) {
	//a*x+b*y=r where r is multiple of gcd(a,b);
	ll d=gcd(a,b); a/=d; b/=d; r/=d;
	auto p = extendedEuclid(a,b); p.fst*=r; p.snd*=r;
	return p; // solutions: p+t*(-b,a)/d
}
#define mod(a,m) (((a)%m+m)%m)
#define inv(a,m) mod(diophantine(a,m,1).fst,m)
ii sol(ll a, ll x1, ll m){ //requires dioph
  ll d=gcd(a,m);if(d<2)return{mod(x1*inv(a,m),m),m};
  return x1%d?ii({-1LL,-1LL}):sol(a/d,x1/d,m/d);
}
ii crt(vv as, vv bs, vv ms){ //returns:(sol,lcm)
    ll x1=0,m1=1;
    fore(i,0,SZ(ms)){
        auto [x2,m2]=sol(as[i],bs[i],ms[i]);
        if(m2<0||(x1-x2)%gcd(m1,m2))return{-1,-1};
        if(m1==m2)continue;; ll l=lcm(m1,m2);
        ll k=diophantine(m2,-m1,x1-x2).snd;
        x1=mod((xl)m1*k+x1,l);m1=l;
    }
    return {x1,m1};
}// as[i]*x=bs[i] (ms[i]); assumes lcm fits in ll

int main(){
    int T; cin >> T;
    while(T--){
        int a, n, b, m; cin >> a >> n >> b >> m;
        vv as={1,1}, bs={a,b}, ms={n,m};
        auto ans = crt(as,bs,ms);
        if(ans.fst==-1&&ans.snd==-1)cout<<"no solution\n";
        else cout<<ans.fst<<" " <<ans.snd << "\n";
    }
}