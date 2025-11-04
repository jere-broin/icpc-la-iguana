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