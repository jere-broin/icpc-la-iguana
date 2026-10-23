ll euclid(ll a, ll b, ll &x, ll &y) {//a*x + b*y = gcd(a,b)
	if(!b)return x=1,y=0,a;
	ll d=euclid(b,a%b,y,x);//returns gcd(a,b)
	return y-=a/b*x,d;//which can be <0 if a,b <0
}