// assumes sorted v (in dfs order)
// virtual (directed) tree is t
void agr(ll x, ll y){if(y!=-1)t[x].pb(y);}
ll virtu(vv v){ // O(|v|) * O(lca)
	stack<ll>s; s.push(v[0]); ll ult=-1,p;
	auto vacia=[&](bool fg){
		while(SZ(s)&&(fg||lca(s.top(),p)!=s.top())){
			agr(s.top(),ult);
			ult=s.top(); s.pop();
		}
	};
	vv vi; // virtual nodes and possibly normal
	fore(i,1,SZ(v)){
		ll x=v[i];p=lca(s.top(),x); vi.pb(p); vacia(0);
		if(s.empty()||p!=s.top())s.push(p);
		agr(p,ult); ult=-1; if(p!=x)s.push(x);
	}
	vacia(1); ll rt=ult; // root of t
	// do stuff, then reset t with both v and vi
}
