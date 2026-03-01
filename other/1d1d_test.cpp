// The 3rd Universal Cup. Stage 15: Chengdu. F: Double 11
// AC https://contest.ucup.ac/submission/886772

#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define fore(i,a,b) for(ll i=a,jet=b;i<jet;++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define imp(v) {for(auto i:v)cout<<i<<" "; cout<<"\n";}
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> ii;
typedef pair<ld,ll> par;
typedef vector<ll> vv;
// COMPILA CON -Wconversion
const ll MAXN=2e5+5;

const ld EPS=1e-15;
ll n;
ll a[MAXN],sp[MAXN];

par dp[MAXN];
ld lam;
par cost(ll l, ll r){
	ld now=sqrtl((r-l)*(sp[r]-sp[l]));
	par ret={now+dp[r].fst+lam,dp[r].snd+1};
	return ret;
}

par aliens(ld _lam){
	lam=_lam;
	deque<ii>dq; dq.pb({n-1,n});
	for(ll j=n-1;j>=0;j--){ // info hasta (j
		auto opt=dq.back().snd;
		assert(dq.back().fst==j);
		dp[j]=cost(j,opt);
		if(!j)break;
		dq.pop_back();
		if(!SZ(dq)||dq.back().fst<j-1)dq.pb({j-1,opt});
		ll s=0;
		while(SZ(dq)){
			auto [i,opt]=dq.front();
			if(cost(i,j)<cost(i,opt))s=i,dq.pop_front();
			else break;
		}
		if(!SZ(dq)){assert(s==j-1);dq.pb({s,j});continue;}
		ll l=s,r=dq.front().fst-1;
		while(l<=r){
			ll m=(l+r)/2;
			if(cost(m,j)<cost(m,dq.front().snd))l=m+1;
			else r=m-1;
		}
		if(r>=0)dq.push_front({r,j});
	}
	return dp[0];
}
const ll INF=MAXN*MAXN*1e5; // max sum*cant
ll REP=85;

int main(){FIN;
	ll k; cin>>n>>k;
	fore(i,0,n)cin>>a[i];
	sort(a,a+n);
	fore(i,1,n+1)sp[i]=sp[i-1]+a[i-1];
	ld l=0,r=INF;
	while(REP--){
		ld m=(l+r)/2;
		if(aliens(m).snd<=k)r=m;
		else l=m;
	}
	ld lam=r;
	auto [res,cnt]=aliens(lam);
	res-=lam*k;
	assert(cnt<=k);
	cout<<fixed<<setprecision(15)<<res<<"\n";
	return 0;
}

