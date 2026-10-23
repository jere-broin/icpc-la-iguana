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

ll euclid(ll a, ll b, ll &x, ll &y) {//a*x + b*y = gcd(a,b)
	if(!b)return x=1,y=0,a;
	ll d=euclid(b,a%b,y,x);//returns gcd(a,b)
	return y-=a/b*x,d;//which can be <0 if a,b <0
}
ll crt(ll a, ll m, ll b, ll n) {//lcm(m,n) must fit in ll
	a%=m, b%=n;//x will be in [0,lcm)
	if(n>m)swap(a,b),swap(m,n);
	ll x,y,g=euclid(m,n,x,y);
	if((a-b)%g)return -1;//no solution
	x=(b-a)%n*x%n/g*m+a;
	return x<0?x+m/g*n:x;
}

int main(){
    int T; cin >> T;
    while(T--){
        ll a, m, b, n; cin >> a >> m >> b >> n;
		ll x=crt(a,m,b,n);
        if(x==-1)cout<<"no solution\n";
        else cout<<x<<" "<<lcm(m,n)<<"\n";
    }
}