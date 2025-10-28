// CSES Area of Rectangles - AC
// https://cses.fi/problemset/task/1741
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,jet=b;i<jet;++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define imp(v) {for(auto i:v)cout<<i<<" "; cout<<"\n";}
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vv;
// node is (min, # of occurences of min)
// update is just range addition
typedef ii tn; // segment-tree node type
typedef ll tl; // lazy type
tn NEUT={1e6,0}; // operation neutral
#define CLEAR 0 // cleared lazy node
tn oper(tn a, tn b){ // segment tree operation
	if(a.fst==b.fst){
		a.snd+=b.snd;
		return a;
	}
	return min(a,b);
}
void acum(tl &a, tl v){ // accumulate lazy
	a+=v;
}
tn calc(int s, int e, tn a, tl v){ // calculate new segment tree value of node with range [s,e), previous value a, and lazy update v
	a.fst+=v;
	return a;
}
struct STree{
	vector<tn>st; vector<tl>lazy; int n;
	STree(int n):st(4*n+5,NEUT),lazy(4*n+5,CLEAR),n(n){}
	void init(int k, int s, int e, vector<tn>&a){
		if(e-s==1)st[k]=a[s];
		else {
			int m=(s+e)/2;
			init(2*k,s,m,a); init(2*k+1,m,e,a);
			st[k]=oper(st[2*k],st[2*k+1]);
		}
	}
	void push(int k, int s, int e){
		if(lazy[k]==CLEAR)return;
		st[k]=calc(s,e,st[k],lazy[k]);
		if(e-s!=1){
			acum(lazy[2*k],lazy[k]);
			acum(lazy[2*k+1],lazy[k]);
		}
		lazy[k]=CLEAR;
	}
	void upd(int k, int s, int e, int a, int b, tl v){
		push(k,s,e);
		if(e<=a||b<=s)return;
		if(a<=s&&e<=b){
			acum(lazy[k],v);
			push(k,s,e);
			return;
		}
		int m=(s+e)/2;
		upd(2*k,s,m,a,b,v),upd(2*k+1,m,e,a,b,v);
		st[k]=oper(st[2*k],st[2*k+1]);
	}
	tn query(int k, int s, int e, int a, int b){
		if(e<=a||b<=s)return NEUT;
		push(k,s,e);
		if(a<=s&&e<=b)return st[k];
		int m=(s+e)/2;
		return oper(query(2*k,s,m,a,b),query(2*k+1,m,e,a,b));
	}
	void upd(int a, int b, tl v){upd(1,0,n,a,b,v);}
	tn query(int a, int b){return query(1,0,n,a,b);}
	void init(vector<tn>&a){init(1,0,n,a);}
};
const int MAXV=1e6;
int main(){FIN;
	int n; cin>>n;
	vector<array<int,4>>ev;
	fore(i,0,n){
		int i0,j0,i1,j1; cin>>i0>>j0>>i1>>j1;
		ev.pb({i0,j0,j1,1});
		ev.pb({i1,j0,j1,-1});
	}
	sort(ALL(ev));
	STree st(2*MAXV+5);
	vector<tn> ini(st.n,{0,1});
	st.init(ini);
	ll res=0;
	fore(i,0,SZ(ev)){
		auto [x,l,r,v]=ev[i];
		l+=MAXV,r+=MAXV; // make them non-negative
		st.upd(l,r,v);
		if(i==SZ(ev)-1)continue;
		res+=(ev[i+1][0]-x)*(st.n-st.query(0,st.n).snd); // width * count of non-zero positions
	}
	cout<<res<<"\n";
	return 0;
}