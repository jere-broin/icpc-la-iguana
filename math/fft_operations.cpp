//Works with NTT. For FFT, just replace addmod,submod,mulmod,inv
poly add(poly &a, poly &b){
	int n=SZ(a),m=SZ(b);
	poly ans(max(n,m));
	fore(i,0,max(n,m)) ans[i]=addmod(i<SZ(a)?a[i]:0, i<SZ(b)?b[i]:0);
	while(SZ(ans)>1&&!ans.back())ans.pop_back();
	return ans;
}
poly derivate(poly &p){//derivative of p
	poly ans(max(1, SZ(p)-1));
	fore(i,1,SZ(p)) ans[i-1]=mulmod(p[i],i);
	return ans;
}
poly integrate(poly &p){
	poly ans(SZ(p)+1);//integral of p
	fore(i,0,SZ(p)) ans[i+1]=mulmod(p[i], inv(i+1));
	return ans;
}
poly takemod(poly &p, int n){
	poly res=p;//p % (x^n)
	res.resize(min(SZ(res),n));
	while(SZ(res)>1&&res.back()==0) res.pop_back();
	return res;
}
poly invert(poly &p, int d){
	assert(p[0]);//first d terms of 1/p
	poly res={inv(p[0])};
	int sz=1;
	while(sz<d){
		sz*=2;
		poly pre(p.begin(), p.begin()+min(SZ(p),sz));
		poly cur=multiply(res,pre);
		fore(i,0,SZ(cur)) cur[i]=submod(0,cur[i]);
		cur[0]=addmod(cur[0],2);
		res=multiply(res,cur);
		res=takemod(res,sz);
	}
	res.resize(d);
	return res;
}//O(n*log(n))
poly log(poly &p, int d){
	assert(p[0]==1);//first d terms of log(p)
	poly cur=takemod(p,d);
	poly a=invert(cur,d), b=derivate(cur);
	auto res=multiply(a,b);
	res=takemod(res,d-1);
	res=integrate(res);
	return res;
}//O(n*log(n))
poly exp(poly &p, int d){
	assert(!p[0]);
	poly res={1};
	int sz=1;//first d terms of exp(p)
	while(sz<d){
		sz*=2; poly lg=log(res, sz), cur(sz);
		fore(i,0,sz) cur[i]=submod(i<SZ(p)?p[i]:0, i<SZ(lg)?lg[i]:0);
		cur[0]=addmod(cur[0],1);
		res=multiply(res,cur);
		res=takemod(res, sz);
	}
	res.resize(d);
	return res;
}//O(n*log(n))
pair<poly,poly> divslow(poly &a, poly &b){
	poly q,r=a;
	while(SZ(r)>=SZ(b)){
		q.pb(mulmod(r.back(),inv(b.back())));
		if(q.back()) fore(i,0,SZ(b)){
			r[SZ(r)-i-1]=submod(r[SZ(r)-i-1],mulmod(q.back(),b[SZ(b)-i-1]));
		}
		r.pop_back();
	}
	reverse(ALL(q)); return {q,r};
}
pair<poly,poly> divide(poly &a, poly &b){
	int m=SZ(a),n=SZ(b),MAGIC=750;
	if(m<n) return {{0},a};
	if(min(m-n,n)<MAGIC)return divslow(a,b);
	poly ap=a; reverse(ALL(ap));
	poly bp=b; reverse(ALL(bp));
	bp=invert(bp,m-n+1);
	poly q=multiply(ap,bp);
	q.resize(SZ(q)+m-n-SZ(q)+1,0);
	reverse(ALL(q));
	poly bq=multiply(b,q);
	fore(i,0,SZ(bq)) bq[i]=submod(0,bq[i]);
	poly r=add(a,bq); return {q,r};//quot,rem
}//O(n*log(n))
vector<poly> tree;
void filltree(vector<tf> &x){
	int k=SZ(x); tree.resize(2*k);
	fore(i,k,2*k) tree[i]={submod(0,x[i-k]),1};
	for(int i=k-1;i;i--) tree[i]=multiply(tree[2*i],tree[2*i+1]);
}
vector<tf> evaluate(poly &a, vector<tf> &x){
	filltree(x); int k=SZ(x); vector<poly> ans(2*k);
	ans[1]=divide(a,tree[1]).snd;
	fore(i,2,2*k) ans[i]=divide(ans[i>>1],tree[i]).snd;
	vector<tf> r; fore(i,0,k) r.pb(ans[i+k][0]); return r;
}//O(n*log^2(n))
poly derivate(poly &p){
	poly ans(SZ(p)-1);
	fore(i,1,SZ(p)) ans[i-1]=mulmod(p[i],i);
	return ans;
}
poly interpolate(vector<tf> &x, vector<tf> &y){
	filltree(x);poly p=derivate(tree[1]);int k=SZ(y);
	vector<tf>d=evaluate(p,x);vector<poly>intree(2*k);
	fore(i,k,2*k) intree[i]={mulmod(y[i-k],inv(d[i-k]))};
	for(int i=k-1;i;i--){
		poly p1=multiply(tree[2*i],intree[2*i+1]);
		poly p2=multiply(tree[2*i+1],intree[2*i]);
		intree[i]=addpoly(p1,p2);
	}
	return intree[1];
}//O(n*log^2(n))