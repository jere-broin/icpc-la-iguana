// Codeforces gym 100551A - AC
// http://codeforces.com/gym/100551/problem/A
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

struct RollbackUF {
	vector<int> e; vector<pii> st;
	RollbackUF(int n) : e(n, -1) {}
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : find(e[x]); }
	int time() { return sz(st); }
	void rollback(int t) {
		for (int i = time(); i --> t;)
			e[st[i].first] = st[i].second;
		st.resize(t);
	}
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		st.push_back({a, e[a]});
		st.push_back({b, e[b]});
		e[a] += e[b]; e[b] = a;
		return true;
	}
};
enum {ADD,DEL,QUERY};
struct Query {int type,x,y;};
struct DynCon {
	vector<Query> q;
	UnionFind dsu;
	vector<int> mt;
	map<pair<int,int>,int> last;
	DynCon(int n):dsu(n){}
	void add(int x, int y){
		if(x>y) swap(x,y);
		q.pb((Query){ADD,x,y}),mt.pb(-1);
		last[{x,y}]=q.size()-1;
	}
	void remove(int x, int y){
		if(x>y)swap(x,y);
		q.pb((Query){DEL,x,y});
		int pr=last[{x,y}];
		mt[pr]=q.size()-1;
		mt.pb(pr);
	}
	void query(){
		q.pb((Query){QUERY,-1,-1});mt.pb(-1);}
	void process(){ // answers all queries in order
		if(!q.size())return;
		fore(i,0,q.size())if(q[i].type==ADD&&mt[i]<0)mt[i]=q.size();
		go(0,q.size());
	}
	void go(int s, int e){
		if(s+1==e){
			if(q[s].type==QUERY) // answer query using DSU
				printf("%d\n",dsu.comp);
			return;
		}
		int k=dsu.snap(),m=(s+e)/2;
		for(int i=e-1;i>=m;--i)if(mt[i]>=0&&mt[i]<s)dsu.join(q[i].x,q[i].y);
		go(s,m);
		dsu.rollback(k);
		for(int i=m-1;i>=s;--i)if(mt[i]>=e)dsu.join(q[i].x,q[i].y);
		go(m,e);
		dsu.rollback(k);
	}
};

int main(){
#ifdef ONLINE_JUDGE
	freopen("connect.in","r",stdin);
	freopen("connect.out","w",stdout);
#endif
	int n,k;
	scanf("%d%d",&n,&k);
	DynCon w(n);
	while(k--){
		char s[4];
		scanf("%s",s);
		if(s[0]=='?')w.query();
		else {
			int x,y;
			scanf("%d%d",&x,&y);x--;y--;
			if(s[0]=='+')w.add(x,y);
			else w.remove(x,y);
		}
	}
	w.process();
	return 0;
}

