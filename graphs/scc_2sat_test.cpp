/*
This test is over the problem https://cses.fi/problemset/task/1684
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
const int MAXN = 2e5+100;
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
    mset(vis,0);
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

int main(){
    JET
    ll m,vars;
    cin>>m>>vars;
    n = 2*vars;
    fore(i,0,m){
        char c, c1;
        ll x, y;
        cin>>c>>x>>c1>>y;
        x--,y--;
        if(c == '-') x = neg(x);
        if(c1 == '-') y = neg(y);
        addor(x,y);
    }
    if(!satis()){
        cout<<"IMPOSSIBLE\n";
        return 0;
    }
    fore(i,0,vars) cout<<(truth[i] == 0 ? '-':'+')<<" ";
    cout<<"\n";
    return 0;
}