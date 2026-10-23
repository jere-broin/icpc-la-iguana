ll crt(ll a, ll m, ll b, ll n) {//lcm(m,n) must fit in ll
	a%=m, b%=n;//x will be in [0,lcm)
	if(n>m)swap(a,b),swap(m,n);
	ll x,y,g=euclid(m,n,x,y);
	if((a-b)%g)return -1;//no solution
	x=(b-a)%n*x%n/g*m+a;
	return x<0?x+m/g*n:x;
}