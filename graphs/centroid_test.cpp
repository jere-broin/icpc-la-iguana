#include <bits/stdc++.h>
#define fore(i,a,b) for(ll i=a, jet=b; i<jet; i++)
#define fst first
#define snd second
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) ((ll)x.size())
#define pb push_back
#define mset(a,v) memset((a),(v),sizeof(a))
#define ET ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vv;
const ll MAXN=1e5+5;

// tag[y]>=tag[x] for every y in x's connected subgraph (unrooted subtree)
vector<int> g[MAXN];
int tag[MAXN]; // time of discovery of centroid
int fat[MAXN]; // father in centroid decomposition
int szt[MAXN]; // size of subtree
int calcsz(int x, int f){
	szt[x]=1;
	for(auto y:g[x])if(y!=f&&tag[y]<0)szt[x]+=calcsz(y,x);
	return szt[x];
}
int ccnt=0;
void cdfs(int x, int f, int sz=-1){ // O(nlogn)
	if(sz<0)sz=calcsz(x,-1);
	for(auto y:g[x])if(tag[y]<0&&szt[y]*2>=sz){
		szt[x]=0;cdfs(y,f,sz);return;
	}
	tag[x]=ccnt++; fat[x]=f;
	for(auto y:g[x])if(tag[y]<0)cdfs(y,x);
}
void centroid(){mset(tag,-1);ccnt=0;cdfs(0,-1);}

vv dis[MAXN]; // distance from x to j'th centroid ancestor
void dfs(ll rt, ll x, ll fa, ll d){
	dis[x].pb(d);
	for(auto y:g[x])if(y!=fa&&tag[y]>=tag[rt])dfs(rt,y,x,d+1);
}
int main(){
	ET;
	ll n; cin>>n;
	fore(i,0,n-1){
		ll u,v; cin>>u>>v; u--,v--;
		g[u].pb(v);
		g[v].pb(u);
	}
	centroid();
	vv ord(n);
	fore(i,0,n)ord[tag[i]]=i;
	reverse(ALL(ord));
	for(auto x:ord)dfs(x,x,-1,0);
	
	vector<ii> best(n,{n+5,n+5});
	vv ans(n);
	for(ll x=n-1;x>=0;x--){
		ii res={n+5,n+5};
		for(ll y=x,j=0;y!=-1;y=fat[y],j++){
			auto [d,v]=best[y];
			res=min(res,{d+dis[x][j],v});
		}
		ans[x]=res.snd;
		if(ans[x]==n+5)ans[x]=x;
		for(ll y=x,j=0;y!=-1;y=fat[y],j++){
			best[y]=min(best[y],{dis[x][j],x});
		}
	}
	for(auto i:ans){
		cout<<i+1<<" ";
	}
	cout<<"\n";
}