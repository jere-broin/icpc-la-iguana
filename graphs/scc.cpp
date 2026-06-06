// Finds strongly connencted components , ord is a valid toposort of the component graph
vv g[MAXN], gt[MAXN], ord;  //gt: transposed graph. ord: order for scc  
ll vis[MAXN], cmp[MAXN], truth[MAXN], qcmp = 0, n; //cmp[x]:scc of x.truth[x]:bool value for 2sat  
void dfsk(ll x, ll t){
	vis[x] = 1; if(t) cmp[x] = qcmp;
    for(auto y:t ? gt[x]:g[x])if(!vis[y]) dfsk(y,t);
    if(!t) ord.pb(x);
}
void scc(){
	qcmp=0; ord.clear(); mset(vis,0);
    fore(i,0,n) if(!vis[i]) dfsk(i,0);
    reverse(ALL(ord)); mset(vis,0);
    for(auto x:ord)if(!vis[x]) dfsk(x,1),qcmp++;
}
// 2SAT, first define n = 2 * vars
ll neg(ll x){return n-x-1;}
void add_or(ll x, ll y){   
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