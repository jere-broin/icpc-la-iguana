/*
This test is over the problem https://codeforces.com/problemset/problem/1239/D
*/

#include<bits/stdc++.h>
#define fore(i,a,b) for(ll i=a,jet=b;i<jet;i++)
#define fst first
#define snd second
#define mset(a,v) memset((a),(v),sizeof(a))
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define JET ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
 
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vv;
 
// Finds strongly connencted components , ord is a valid toposort of the component graph
ll n;
const int MAXN = 1e6+100;
vv g[MAXN], gt[MAXN], ord;  //gt: transposed graph. ord: order for scc  
ll vis[MAXN], cmp[MAXN], truth[MAXN]; //cmp[x]: scc of node x. truth[x]: boolean value for 2sat  
ll qcmp = 0;


void dfs(ll x, ll t){
    if(t) cmp[x] = qcmp;
    vis[x] = 1;
    for(auto y: t ? gt[x] : g[x])if(!vis[y]) dfs(y,t);
    if(!t) ord.pb(x);
}
void scc(){
    fore(i,0,n) if(!vis[i]) dfs(i,0);
    reverse(ALL(ord));
    fore(i,0,n) vis[i] = 0;
    for(auto x:ord)if(!vis[x]){
        dfs(x,1);  
        qcmp++;
    }
}

// 2SAT, first define n = 2 * vars
ll neg(ll x){return n-x-1;}
void addor(ll x,ll y){   
    g[neg(x)].pb(y); g[neg(y)].pb(x);
    gt[x].pb(neg(y)); gt[y].pb(neg(x));
}
bool satis(){
    scc();
    fore(i,0,n){
        if(cmp[i] == cmp[neg(i)]) return false;
        truth[i] = cmp[i] > cmp[neg(i)];
    }
    return true;
}


void limpiar(){
	fore(i,0,n){
        g[i].clear();
        vis[i] = 0; 
        gt[i].clear();
        cmp[i] = 0;
    }
    qcmp = 0;
    ord.clear();
}
 
int main(){
	JET
	ll t; cin>>t;
	while(t--){
		ll m; cin>>n>>m;
		fore(i,0,m){
			ll x,y; cin>>x>>y;
			x--,y--;
			g[x].pb(y);
            gt[y].pb(x);
		}
		scc();
		if (qcmp == 1){
			cout<<"No\n";
			limpiar();
			continue;
		}
		vv outd(qcmp,0);
		fore(i,0,n){
			ll act = cmp[i];
			for(auto x:g[i]) if(cmp[x]!=act) outd[act]++;
		}
		ll buena = -1;
		// cout<<"cantidad de componentes conexas: "<<qcmp<<endl;
		fore(i,0,qcmp){
			if(outd[i] == 0){
				buena = i;
				break;
			}
		}
		assert(buena>=0);
		vv ar,ab;
		fore(i,0,n){
			if(cmp[i] == buena) ar.pb(i);
			else ab.pb(i);
		}
		cout<<"Yes\n";
		cout<<SZ(ar)<<" "<<SZ(ab)<<"\n";
		for(auto x:ar) cout<<x+1<<" ";
		cout<<"\n";
		for(auto x:ab) cout<<x+1<<" ";
		cout<<"\n";
		limpiar();
	}
	return 0;
}