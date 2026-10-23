// not necessary for crt
typedef __int128 xl;
ii diophantine(ll a, ll b, ll r) {//a*x + b*y = r
	ll x,y,g=euclid(a,b,x,y);
	assert(r%g==0);//else no solution
	if(!b)return {r/a,0};
	x=(xl)x*(r/g)%(b/g);//reduces |x|<|b/g| so (x0,y0) fits in ll
	return {x,(r-(xl)a*x)/b};//solutions: (x0,y0) + t*(-b,a)/g
}