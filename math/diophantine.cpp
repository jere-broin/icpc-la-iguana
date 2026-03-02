ii extendedEuclid (ll a, ll b){ //a * x + b * y = gcd(a,b)
	if(!b) return {1,0};
	auto p=extendedEuclid(b,a%b); ll x=p.snd, y=p.fst-(a/b)*x;
	if(a*x+b*y<0) x=-x, y=-y;
	return {x,y};
}
pair<ii,ii> diophantine(ll a,ll b,ll r) {
	//a*x+b*y=r where r is multiple of gcd(a,b);
	ll d=gcd(a,b); a/=d; b/=d; r/=d;
	auto p = extendedEuclid(a,b); p.fst*=r; p.snd*=r;
	return {p,{-b,a}}; // solutions: p+t*ans.snd
}