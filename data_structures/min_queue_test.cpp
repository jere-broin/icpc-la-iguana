// CSES Maximum Subarray Sum II - AC
// https://cses.fi/paste/ab88b7430b5b298f6ed195/
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define fore(i,a,b) for(ll i=a,ggdem=b;i<ggdem;++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define imp(v) for(auto messi:v)cout<<messi<<" "; cout<<"\n"
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
const ll INF=1e15;
 
struct MinQ{
	deque<ii>q; ll dif=0;
	MinQ(){}
	void push(ll x){
		ll cnt=1;
		x-=dif;
		while(SZ(q)&&x<=q.back().fst)cnt+=q.back().snd,q.pop_back();
		q.pb({x,cnt});
	}
	void pop(){
		if(!SZ(q))return;
		if(q.front().snd>1)q.front().snd--;
		else q.pop_front();
	}
	ll query(){
		if(!SZ(q))return INF;
		return q.front().fst+dif;
	}
	void add(ll x){
		dif+=x;
	}
};
 
int main(){FIN;
	ll n,l,r; cin>>n>>l>>r;
	ll a[n];
	fore(i,0,n)cin>>a[i],a[i]=-a[i];
	vector<ll>sp(n+1);
	fore(i,1,n+1)sp[i]=sp[i-1]+a[i-1];
	MinQ q;
	ll res=INF;
	fore(i,0,n){
		if(i-r>=0)q.pop();
		if(i-l+1>=0)q.push(sp[i]-sp[i-l+1]);
		q.add(a[i]);
		res=min(res,q.query());
	}
	cout<<-res<<"\n";
	return 0;
}
 