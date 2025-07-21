// CSES Subarray Sum Queries - AC
// https://cses.fi/problemset/task/1190/ 
#include <bits/stdc++.h>
#define fore(i,a,b) for(ll i=a,jet=b;i<jet;++i)
#define JET ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long ll;
 
struct node{
	ll sum,pre,suf,all;
	node(ll a):sum(a),pre(a),suf(a),all(a){}
	node(){}
};
node oper(node a, node b){ // a left, b right
	node p;
	p.sum=max({a.sum,b.sum,a.suf+b.pre});
	p.pre=max(a.pre,a.all+b.pre);
	p.suf=max(b.suf,a.suf+b.all);
	p.all=a.all+b.all;
	return p;
}
node NEUT=node(0);
struct STree{
	int n; vector<node>t;
	STree(int n):n(n),t(2*n+5,NEUT){}
	void init(vector<node> &a){
		fore(i,0,n)t[n+i]=a[i];
		for(ll i=n-1;i>0;i--)t[i]=oper(t[2*i],t[2*i+1]);
	}
	void upd(int p, node v){
		for(p+=n,t[p]=v;p>1;p>>=1)p^=p&1,t[p>>1]=oper(t[p],t[p^1]);
	}
	node query(int l, int r){
		node izq=NEUT,der=NEUT;
		for(l+=n,r+=n;l<r;l>>=1,r>>=1){
			if(l&1)izq=oper(izq,t[l++]);
			if(r&1)der=oper(t[--r],der);
		}
		return oper(izq,der);
	}
}; // usage: STree rmq(n);rmq.init(x);rmq.upd(i,v);rmq.query(s,e);

 
int main(){
	JET
	ll n,q; cin>>n>>q;
	vector<ll> a(n);
	vector<node> ini(n);
	fore(i,0,n)cin>>a[i],ini[i]=node(a[i]);
	STree st(n);
	st.init(ini);
	while(q--){
		ll k,v; cin>>k>>v; k--;
		st.upd(k,v);
		cout<<max(st.query(0,n).sum,0ll)<<"\n";
	}
	return 0;
}