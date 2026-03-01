int find(int k, int s, int e, int a, int b, ll v){
	// example: first position > v in [a,b), b if none
	if(e<=a||b<=s) return b;
	// push(k,s,e); // if it's lazy
	int m = (s+e)/2;
	bool good=st[k]>v; // someone is good in this subtree 
	if(!good&&(a<=s&&e<=b))return b;
	if(e-s==1)return s;
	int res=find(2*k,s,m,a,b,v);
	if(res==b)res=find(2*k+1,m,e,a,b,v);
	return res;
}
int find(int a, int b, ll v){return find(1,0,n,a,b,v);}