// Brazillian Summer School: Piles of Trash - AC
// https://codeforces.com/group/TFrGcBYYxs/contest/585176/problem/H
#include<bits/stdc++.h>
#define fore(i,a,b) for(ll i=a,jet=b;i<jet;i++)
#define pb push_back
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long ll;
typedef vector<ll> vv;
typedef pair<ll,ll> ii;

typedef signed char tf; typedef ll tc;
const tf INFFLOW=5; const tc INFCOST=1e18;
struct MCF{
	int n; vector<tc> prio, pot;
	vector<tf> curflow;vector<int> prevedge,prevnode;
	priority_queue<pair<tc, int>, vector<pair<tc, int>>, greater<pair<tc, int>>> q;
	struct edge{int to, rev; tf f, cap; tc cost;};
	vector<vector<edge>> g;
	MCF(int n):n(n),prio(n),pot(n),curflow(n),prevedge(n),prevnode(n),g(n){}
	void add_edge(int s, int t, tf cap, tc cost) {
		g[s].pb((edge){t,(int)SZ(g[t]),0,cap,cost});
		g[t].pb((edge){s,(int)SZ(g[s])-1,0,0,-cost});
	}
	pair<tf,tc> get_flow(int s, int t) {
		tf flow=0; tc flowcost=0;
		while(1){
			q.push({0, s}); fill(ALL(prio),INFCOST); 
			prio[s]=0; curflow[s]=INFFLOW;
			while(!q.empty()) {
				auto cur=q.top(); tc d=cur.fst; int u=cur.snd; q.pop();
				if(d!=prio[u]) continue;
				for(int i=0; i<SZ(g[u]); ++i) {
					edge &e=g[u][i]; int v=e.to;
					if(e.cap<=e.f) continue;
					tc nprio=prio[u]+e.cost+pot[u]-pot[v];
					if(prio[v]>nprio) {
						prio[v]=nprio; q.push({nprio, v});
						prevnode[v]=u; prevedge[v]=i;
						curflow[v]=min(curflow[u],tf(e.cap-e.f));
					}
				}
			}
			if(prio[t]==INFCOST) break;
			fore(i,0,n) if(prio[i]!=INFCOST) pot[i]+=prio[i];
			tf df=min(curflow[t],tf(INFFLOW-flow)); flow+=df;
			for(int v=t; v!=s; v=prevnode[v]) {
				edge &e=g[prevnode[v]][prevedge[v]];
				e.f+=df; g[v][e.rev].f-=df; flowcost+=df*e.cost;
			}
		}
		return {flow,flowcost};
	}
	// If some costs can be negative, call this before maxflow:
	void set_pot(int s){ // O(nm), or O(n+m) if DAG in topo order 0..n-1
		fill(ALL(pot),INFCOST); pot[s]=0;
		int it=n,ch=1;
		while(ch--&&it--)fore(u,0,n)if(pot[u]!=INFCOST){
			for(auto &e:g[u])if(e.cap&&pot[e.to]>pot[u]+e.cost){
				pot[e.to]=pot[u]+e.cost,ch=1;
			}
		}
		assert(it>=0); // negative cycle
	}
};

int n,m;
int cv(ll i, ll j){return m*i+j;}
int in(ll i, ll j){return cv(i,j)*2;}
int out(ll i, ll j){return cv(i,j)*2+1;}

int main(){
	FIN
	cin>>n>>m;
	MCF fl(2*(n*m+5));
	fore(i,0,n)fore(j,0,m){
		ll x; cin>>x;
		ll fg=(i==0&&j==0)||(i==n-1&&j==m-1);
		if(i<n-1)fl.add_edge(out(i,j),in(i+1,j),INFFLOW,0);
		if(j<m-1)fl.add_edge(out(i,j),in(i,j+1),INFFLOW,0);
		fl.add_edge(in(i,j),out(i,j),fg?2:1,-x);
	}
	ll s=in(0,0),t=out(n-1,m-1);
	fl.set_pot(s);
	auto [flow,cost]=fl.get_flow(s,t);
	assert(flow==2);
	cout<<-cost<<"\n";
	return 0;
}