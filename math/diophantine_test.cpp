//https://codeforces.com/problemset/problem/1244/C
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;

ll euclid(ll a, ll b, ll &x, ll &y) {//a*x + b*y = gcd(a,b)
	if(!b)return x=1,y=0,a;
	ll d=euclid(b,a%b,y,x);//returns gcd(a,b)
	return y-=a/b*x,d;//which can be <0 if a,b <0
}

typedef __int128 xl;
ii diophantine(ll a, ll b, ll r) {//a*x + b*y = r
	ll x,y,g=euclid(a,b,x,y);
	assert(r%g==0);//else no solution
	if(!b)return {r/a,0};
	x=(xl)x*(r/g)%(b/g);//reduces |x|<|b/g| so (x0,y0) fits in ll
	return {x,(r-(xl)a*x)/b};//solutions: (x0,y0) + t*(-b,a)/g
}

int main(){
    ll n,p,w,d; cin>>n>>p>>w>>d;
    ll g=gcd(w,d);
    if(p%g){
		cout<<"-1\n";
		return 0;
	}
    auto [y,x]=diophantine(d,w,p);// |y| < w/g
    if(y<0)y+=w/g,x-=d/g;// shift by t = +1 so y >= 0 is minimal
    if(x<0||x+y>n)cout<< "-1\n";
    else cout<<x<<" "<<y<<" "<<n-x-y<<"\n";
}