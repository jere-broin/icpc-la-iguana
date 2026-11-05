// SWERC 2024 A: Titanomachy - AC
// https://qoj.ac/contest/2691/problem/15695
#include <bits/stdc++.h>
#define fore(i,a,b) for(ll i = a, jet = b;i<jet;i++)
#define fst first
#define snd second
#define pb push_back
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) ((ll)(x).size())
#define mset(a,v) memset((a),(v),sizeof(a))
#define show(a) {for(auto x:a)cout<<x<<" ";cout<<"\n";}
#define JET ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vv;
typedef ll tc;
struct Line{tc m,h;};
struct CHT { // for minimum (for maximum just change the sign of lines)
	vector<Line> c; int pos=0;
	tc in(Line a, Line b){
		tc x=b.h-a.h,y=a.m-b.m;
		return x/y+(x%y?!((x>0)^(y>0)):0);//==ceil(x/y)
	}
	void add(tc m, tc h){ // m's should be non increasing
		Line l=(Line){m,h};
		if(SZ(c)&&m==c.back().m){
			l.h=min(h,c.back().h);c.pop_back();if(pos)pos--;
		}
		while(SZ(c)>1&&in(c.back(),l)<=in(c[SZ(c)-2],c.back())){
			c.pop_back();if(pos)pos--;
		}
		c.pb(l);
	}
	inline bool fbin(tc x, int m){return in(c[m],c[m+1])>x;}
	tc eval(tc x){
		// O(log n) query:
		int s=0,e=SZ(c);
		while(e-s>1){int m=(s+e)/2;
			if(fbin(x,m-1))e=m;
			else s=m;
		}
		return c[s].m*x+c[s].h;
	}
};
CHT operator+(CHT a, CHT b){ // minkowsi sum trick, O(n+m)
	CHT r;
	int i=0,j=0,n=SZ(a.c),m=SZ(b.c);
	while(i<n&&j<m){
		Line l=a.c[i],k=b.c[j];
		r.add(l.m+k.m, l.h+k.h);
		if(i!=n-1 && (j==m-1||a.in(l,a.c[i+1])<b.in(k,b.c[j+1])))i++;
		else j++;
	}
	return r;
}
typedef array<ll,3> tri;
ll n;
vv a;
vv ans;
void cand(ll i, ll cur){ans[i]=max(ans[i],cur);}
vv acums;
vector<vector<ll>> ev;
vv part;
CHT rec(ll s, ll e, vector<tri> qs){
	ll m=(s+e)/2;
	vector<tri> recl,recr;
	vv full;
	for(auto [l,r,i]:qs){
		assert(l>=s and r<=e);
		if(l==s and r==e)full.pb(i);
		else if(r<=m)recl.pb({l,r,i});
		else if(l>=m)recr.pb({l,r,i});
		else {
			recl.pb({l,m,i}),recr.pb({m,r,i});
			ev[l].pb(i);
			ev[r].pb(i);
		}
	}
	if(e-s==1){
		assert(!SZ(recl) and !SZ(recr));
		for(auto i:full)cand(i,a[s]+acums[i]);
		CHT ret; ret.add(-1,-a[s]);
		return ret;
	}
	CHT CL,CR;
	Line cur={0,0};
	for(ll l=m-1;l>=s;l--){
		cur.m++;
		cur.h+=a[l];
		CL.add(-cur.m,-cur.h);
		for(auto i:ev[l])part[i]=-CL.eval(acums[i]);
		ev[l].clear();
	}
	cur={0,0};
	fore(r,m+1,e+1){
		cur.m++;
		cur.h+=a[r-1];
		CR.add(-cur.m,-cur.h);
		for(auto i:ev[r]){
			cand(i,part[i] -CR.eval(acums[i]));
			part[i]=0;
		}
		ev[r].clear();
	}
	auto gotl=rec(s,m,recl);
	auto gotr=rec(m,e,recr);
	CHT cross=CL+CR;
	vector<Line> all;
	for(auto &v:{gotl.c,gotr.c,cross.c})for(auto l:v)all.pb(l);
	sort(ALL(all),[&](Line a, Line b){return a.m>b.m;});
	CHT ret;
	for(auto l:all)ret.add(l.m,l.h);
	for(auto i:full)cand(i,-ret.eval(acums[i]));
	return ret;
}

int main(){
	JET
	ll q; cin>>n>>q;
	a=vv(n);
	fore(i,0,n)cin>>a[i];
	ll acum=0;
	vector<tri> qs;
	while(q--){
		string ty; cin>>ty;
		if(ty=="ASSESS"){
			ll l,r; cin>>l>>r; l--;
			acums.pb(acum);
			ans.pb(0);
			qs.pb({l,r,SZ(qs)});
		}
		else {
			ll dx; cin>>dx;
			acum+=dx;
		}
	}
	ll z=SZ(qs);
	ev.resize(n+1);
	part.resize(z);
	rec(0,n,qs);
	for(auto i:ans)cout<<i<<"\n";
	return 0;
}