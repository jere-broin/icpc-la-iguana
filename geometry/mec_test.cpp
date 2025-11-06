// CF MasterCodeChef Russia - AC
// https://codeforces.com/gym/102299/problem/J

#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define fore(i,a,b) for(ll i=a,jet=b;i<jet;i++)
#define SZ(x) ((int) x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define JET ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
const ld EPS=1e-9;
struct pt {
	ld x,y;
	pt(ld x, ld y):x(x),y(y){}
	pt(){}
	ld norm2(){return *this**this;}
	ld norm(){return sqrt(norm2());}
	pt operator+(pt p){return pt(x+p.x,y+p.y);}
	pt operator-(pt p){return pt(x-p.x,y-p.y);}
	pt operator*(ld t){return pt(x*t,y*t);}
	pt operator/(ld t){return pt(x/t,y/t);}
	ld operator*(pt p){return x*p.x+y*p.y;}
	ld operator%(pt p){return x*p.y-y*p.x;}
};
pt bary(pt A, pt B, pt C, ld a, ld b, ld c) {
    return (A*a + B*b + C*c) / (a + b +c);
}
pt circumcenter(pt A, pt B, pt C) {
    // intersection of perpendicular bisectors
    ld a=(B-C).norm2(), b=(C-A).norm2(), c=(A-B).norm2();
    return bary(A, B, C, a*(b+c-a), b*(c+a-b), c*(a+b-c));
}
random_device rd;
mt19937 rng(rd());
pair<pt,ld> mec(vector<pt> ps) {
	shuffle(ALL(ps),rng);
	pt o=ps[0];
	ld r=0, EPS=1+1e-8;
	fore(i,0,SZ(ps))if((o-ps[i]).norm()>r*EPS) {
		o=ps[i],r=0;
		fore(j,0,i)if((o-ps[j]).norm()>r*EPS) {
			o=(ps[i]+ps[j])/2;
			r=(o-ps[i]).norm();
			fore(k,0,j)if((o-ps[k]).norm()>r*EPS) {
				o=circumcenter(ps[i],ps[j],ps[k]);
				r=(o-ps[i]).norm();
			}
		}
	}
	return {o,r};
}

int main(){
	JET
	ll n; cin>>n;
	vector<pt>a(n);
	fore(i,0,n)cin>>a[i].x>>a[i].y;
	auto [o,r]=mec(a);
	cout<<fixed<<setprecision(15);
	cout<<o.x<<" "<<o.y<<" "<<r*r/2<<"\n";
	return 0;
}