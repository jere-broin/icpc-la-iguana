// Codeforces 166B - AC
// http://codeforces.com/problemset/problem/166/B
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

const double EPS=1e-12;

struct pt {  // for 3D add z coordinate
	double x,y;
	pt(double x, double y):x(x),y(y){}
	pt(){}
	double norm2(){return *this**this;}
	double norm(){return sqrt(norm2());}
	bool operator==(pt p){return abs(x-p.x)<EPS&&abs(y-p.y)<EPS;}
	pt operator+(pt p){return pt(x+p.x,y+p.y);}
	pt operator-(pt p){return pt(x-p.x,y-p.y);}
	pt operator*(double t){return pt(t*x,t*y);}
	pt operator/(double t){return pt(x/t,y/t);}
	double operator*(pt p){return x*p.x+y*p.y;}
//	pt operator^(pt p){ // only for 3D
//		return pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}
	double angle(pt p){ // redefine acos for values out of range
		return acos(*this*p/(norm()*p.norm()));}
	pt unit(){return *this/norm();}
	double operator%(pt p){return x*p.y-y*p.x;} // 2D from now on
	bool operator<(pt p)const{ // for convex hull
		return x<p.x-EPS||(abs(x-p.x)<EPS&&y<p.y-EPS);}
	bool left(pt p, pt q){ // is it to the left of directed line pq?
		return (q-p)%(*this-p)>EPS;}
	pt rot(pt r){return pt(*this%r,*this*r);}
	pt rot(double a){return rot(pt(sin(a),cos(a)));}
};
vector<pt> chull(vector<pt> p){// CCW order
	if(SZ(p)<3) return p;//incl collinear
	vector<pt> r; sort(ALL(p)); int k=0,pr=-1;
	fore(_,0,2){//first lower hull, then upper hull
		fore(i,0,SZ(p)){
			while(SZ(r)>1+k&&r.back().left(r[SZ(r)-2],p[i]))r.pop_back();
			while(pr>=0&&p[i]<r[pr]) pr--; 
		    if(pr<0||!(p[i]==r[pr])||!_) r.pb(p[i]); 
		}
        if(!_)r.pop_back(),k=SZ(r),pr=k-1,reverse(ALL(p));
	}
	return r;
}

int n,m;
vector<pt> p;

int main(){
	scanf("%d",&n);
	fore(i,0,n){
		int x,y;
		scanf("%d%d",&x,&y);
		p.pb(pt(x,y));
	}
	scanf("%d",&m);
	vector<pt> q;
	fore(i,0,m){
		int x,y;
		scanf("%d%d",&x,&y);
		p.pb(pt(x,y));
		q.pb(pt(x,y));
	}
	vector<pt> c=chull(p);
	set<pt> s(c.begin(),c.end());
	for(pt p:q)if(s.count(p)){puts("NO");return 0;}
	puts("YES");
	return 0;
}