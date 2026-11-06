// AC
// http://codeforces.com/group/3qadGzUdR4/contest/101707/problem/H
#include <bits/stdc++.h>
#ifdef DEMETRIO
#define deb(...) fprintf(stderr,__VA_ARGS__)
#define deb1(x) cerr << #x << " = " << x << endl
#else
#define deb(...) 0
#define deb1(x) 0
#endif
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;

#define double ll
#define EPS 0

struct pt {  // for 3D add z coordinate
	double x,y;
	pt(double x, double y):x(x),y(y){}
	pt(){}
	double norm2(){return *this**this;}
	double norm(){return sqrt(norm2());}
	bool operator==(pt p){return abs(x-p.x)<EPS&&abs(y-p.y)<EPS;}
	pt operator+(pt p){return pt(x+p.x,y+p.y);}
	pt operator-(pt p){return pt(x-p.x,y-p.y);}
	pt operator*(double t){return pt(x*t,y*t);}
	pt operator/(double t){return pt(x/t,y/t);}
	double operator*(pt p){return x*p.x+y*p.y;}
//	pt operator^(pt p){ // only for 3D
//		return pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}
	double angle(pt p){ // redefine acos for values out of range
		return acos(*this*p/(norm()*p.norm()));}
	pt unit(){return *this/norm();}
	double operator%(pt p){return x*p.y-y*p.x;}
	// 2D from now on
	bool operator<(pt p)const{ // for convex hull
		return x<p.x||x==p.x&&y<p.y;}
	bool left(pt p, pt q){ // is it to the left of directed line pq?
		return (q-p)%(*this-p)>=0;}
	pt rot(pt r){return pt(*this%r,*this*r);}
	pt rot(double a){return rot(pt(sin(a),cos(a)));}
};
pt ccw90(1,0);
pt cw90(-1,0);

// CCW order
// Includes collinear points (change sign of EPS in left to exclude)
vector<pt> chull(vector<pt> p){
	vector<pt> r;
	sort(p.begin(),p.end()); // first x, then y
	fore(i,0,p.size()){ // lower hull
		while(r.size()>=2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back();
	int k=r.size();
	for(int i=p.size()-1;i>=0;--i){ // upper hull
		while(r.size()>=k+2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back();
	return r;
}

int sgn(double x){return x<-EPS?-1:x>EPS;}
struct pol {
    int n;vector<pt> p;
    pol(){}
    pol(vector<pt> _p){p=_p;n=p.size();}
    pt farthest(pt v){ // O(log(n)) only CONVEX
        auto cmp=[&](int i,int j){return v*(p[j]-p[i])>EPS;};
        if(n<10){
            int k=0;fore(i,1,n)if(cmp(k,i))k=i;
            return p[k];
        }
        auto dir=[&](int i){return cmp(i,i+1);};
        int s=0,e=n; p.pb(p[0]);
        while(e-s>1){
            int m=(s+e)/2;
            bool su=dir(s),mu=dir(m);
            if(su!=mu) su?e=m:s=m;
            else if(su) cmp(s,m)?s=m:e=m;
            else cmp(m,s)?s=m:e=m;
        }
        pt ans=p[dir(s)?s+1:s]; p.pop_back();
        return ans;
    }
};

ll a[100005],b[100005],c[100005];
int m,n;
vector<pt> v;pol p;

bool doit(ll a, ll b, ll c){
	pt v(a,b);
	return p.farthest(v)*v+c>=0&&p.farthest(pt(0,0)-v)*v+c<=0;
}

int main(){
	scanf("%d%d",&m,&n);
	fore(i,0,m)scanf("%lld%lld%lld",a+i,b+i,c+i);
	fore(i,0,n){
		ll x,y;
		scanf("%lld%lld",&x,&y);
		v.pb(pt(x,y));
	}
	auto q=chull(v);
	if(q.empty())q=v;
	p=pol(q);
	vector<int> r;
	fore(i,0,m)if(doit(a[i],b[i],c[i]))r.pb(i);
	printf("%d\n",SZ(r));
	fore(i,0,SZ(r)){
		if(i)putchar(' ');
		printf("%d",r[i]+1);
	}
	puts("");
	return 0;
}
