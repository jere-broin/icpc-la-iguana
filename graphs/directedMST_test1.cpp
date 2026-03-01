// kattis fastestspeedrun - AC
//https://vjudge.net/problem/Kattis-fastestspeedrun
#include <bits/stdc++.h>
#define fore(i,a,b) for(ll i = a,jet = b;i<jet;i++)
#define snd second
#define fst first
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define mset(a,v) memset((a),(v),sizeof(a))
#define pb push_back
#define JET ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vv;


struct UnionFind {
	int n,comp;
	vector<int> uf,si,c;
	UnionFind(int n=0):n(n),comp(n),uf(n),si(n,1){ fore(i,0,n)uf[i]=i; }
	int find(int x){return x==uf[x]?x:find(uf[x]);}
	bool join(int x, int y){
		if((x=find(x))==(y=find(y)))return false;
		if(si[x]<si[y])swap(x,y);
		si[x]+=si[y];uf[y]=x;comp--;c.pb(y);
		return true;
	}
	int snap(){return c.size();}
	void rollback(int snap){
		while(c.size()>snap){
			int x=c.back();c.pop_back(); si[uf[x]]-=si[x]; uf[x]=x;comp++;
		}
	}
};

struct Edge{int a, b; ll w;};
struct Node{
    Edge key;
    Node *l, *r;
    ll delta;
    void prop(){
        key.w += delta;
        if(l) l->delta += delta;
        if(r) r-> delta += delta;
        delta = 0;
    }
    Edge top(){prop(); return key;}
};
Node *merge(Node *a, Node *b){
    if(!a || !b) return a ?: b;
    a-> prop(), b -> prop();
    if(a->key.w > b-> key.w) swap(a,b);
    swap(a-> l,(a->r = merge(b,a->r)));
    return a;
}
void pop(Node *& a){a-> prop(); a = merge(a->l,a->r);}
pair<ll,vv> dmst(int n, int r, vector<Edge>&g){
    UnionFind uf(n);
    vector<Node*> heap(n);
    for(Edge e:g) heap[e.b] = merge(heap[e.b], new Node{e});
    ll res = 0;
    vv seen(n,-1), path(n),par(n);
    seen[r] = r;
    vector<Edge> Q(n), in(n,{-1,-1}), comp;
    deque<tuple<int, int, vector<Edge>>> cycs;
    fore(s,0,n){
        int u = s, qi = 0, w;
        while(seen[u] < 0){
            if(!heap[u]) return {-1,{}};
            Edge e = heap[u] -> top();
            heap[u] -> delta -= e.w, pop(heap[u]);
            Q[qi] = e, path[qi++] = u, seen[u]  = s;
            res += e.w, u = uf.find(e.a);
            if(seen[u] == s){
                Node *cyc = 0;
                int end = qi, time = uf.snap();
                do cyc = merge(cyc, heap[w = path[--qi]]);
                while(uf.join(u,w));
                u = uf.find(u), heap[u] = cyc, seen[u] = -1;
                cycs.push_front({u,time,{&Q[qi], &Q[end]}});
            }
        }
        fore(i,0,qi)in[uf.find(Q[i].b)] = Q[i];
    }

    for(auto & [u,t,comp] : cycs){
        uf.rollback(t);
        Edge inEdge = in[u];
        for(auto &e : comp) in[uf.find(e.b)] = e;
        in[uf.find(inEdge.b)] = inEdge;
    }
    fore(i,0,n) par[i] = in[i].a;
    return {res,par};
}

int main(){
    JET
    ll n; cin>>n;
    vector<Edge> g;
    fore(i,1,n+1){
        ll x,y; cin>>x>>y;
        g.pb((Edge){x,i,y});
        fore(j,0,n+1){
            ll w; cin>>w;
            g.pb((Edge){j,i,w});
        }
    }
    cout<<dmst(n+1,0,g).fst<<"\n";
    return 0;
}