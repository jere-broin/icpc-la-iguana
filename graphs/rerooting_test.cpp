// CSES Tree Distances II
// AC: https://cses.fi/paste/eaf2ec082533ba1dfa786b/
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define fore(i,a,b) for(ll i=a,jet=b;i<jet;++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define imp(v) {for(auto gdljh:v)cout<<gdljh<<" "; cout<<"\n";}
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
const ll MAXN=2e5+5;

vector<ii> g[MAXN]; // node, weight (1 if none)

// to see what these mean, look at dfs1
struct node {
	ll dp,q;
	node():dp(0),q(0){} // NEUT
	node(ll q):dp(0),q(q){}
};
node NEUT;
node leaf(ll x){
	return node(1);
}
node merge(node a, node b){
	a.q+=b.q;
	a.dp+=b.dp;
	return a;
}
node up(node x, ll w){
	x.dp+=x.q;
	return x;
}

node h[MAXN],ch[MAXN]; // hijo, complement hijo (SIN ARISTA PADRE)
node tot[MAXN]; // total
ll wf[MAXN],fa[MAXN]; // weight father, father
void dfs1(ll x){
	h[x]=leaf(x);
	for(auto [y,w]:g[x])if(y!=fa[x]){
		wf[y]=w; fa[y]=x; dfs1(y);
		h[x]=merge(h[x],up(h[y],w));
	}
}
vector<node> pre[MAXN],suf[MAXN];
void dfs2(ll x){
	fore(j,0,SZ(g[x])){
		auto [y,w]=g[x][j];
		if(y==fa[x])continue;
		ch[y]=merge(leaf(x),merge(pre[x][j],suf[x][j+1]));
		if(fa[x]!=-1)ch[y]=merge(ch[y],up(ch[x],wf[x]));
		dfs2(y);
	}
}
void reroot(ll n){
	ll rt=0; fa[rt]=-1,wf[rt]=0; dfs1(rt);
	fore(x,0,n){
		fore(ty,0,2){
			auto &p=(ty?suf[x]:pre[x]);
			p=vector<node>(SZ(g[x])+1,NEUT);
			fore(j,1,SZ(p)){
				auto [y,w]=g[x][j-1]; p[j]=p[j-1];
				if(y!=fa[x])p[j]=merge(p[j],up(h[y],w));
			}
			reverse(ALL(g[x]));
		}
		reverse(ALL(suf[x]));
	}
	dfs2(rt);
	fore(x,0,n){
		tot[x]=h[x];
		if(fa[x]!=-1)tot[x]=merge(tot[x],up(ch[x],wf[x]));
		// you may want to treat the root specially
		// if that is the case, remember to recalculate tot[rt]
	}
}

int main(){FIN;
	ll n; cin>>n;
	fore(i,0,n-1){
		ll u,v; cin>>u>>v; u--,v--;
		g[u].pb({v,1});
		g[v].pb({u,1});
	}
	reroot(n);
	fore(i,0,n)cout<<tot[i].dp<<" ";
	cout<<"\n";
	return 0;
}
