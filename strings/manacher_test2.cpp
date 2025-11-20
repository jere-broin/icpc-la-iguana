//CSES - Longest Palindrome
//ACC
//https://cses.fi/paste/50f24f722ab07cf4ea5195/

#include<bits/stdc++.h>
#define fore(i,a,b) for(ll i=a,jet=b;i<jet;i++)
#define fst first
#define snd second
#define mset(a,v) memset((a),(v),sizeof(a))
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define pb push_back
#define JET ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define imp(v) for(auto pera:v) cout<<pera<<" ";;cout<<endl;
#define imp2(v) for(auto [sandia,melon]:v) cout<<sandia<<","<<melon<<" ";;cout<<endl;
#define inp(v) for(auto &uva:v) cin>>uva;
#define inp2(v) for(auto &[fresa,mora]:v) cin>>fresa>>mora;

using namespace std;

typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vv;
typedef vector<ii> vi;
typedef __int128 xl;
typedef long double ld;
typedef vector<vv> mtx;



vv manacher(string &s, bool p){ //paridad de la longitud de los palíndromos
    int n=SZ(s),l=-1,r=0;
    vv d(n);
    fore(i,0,n){
        int k=(i<r?min(d[l+r-i+!p],r-i):p);
        while(i+k<n&&k<i+p&&s[i-k-!p]==s[i+k]) k++;
        d[i]=k;
        if(i+k>r) r=i+k,l=i-k-!p;
    }
    return d;
}

int main(){
    JET
    string s; cin>>s;
    auto d1=manacher(s,1);
    auto d2=manacher(s,0);
    int l=0,r=0;
    fore(i,0,SZ(s)){
        if(r-l<(d1[i]<<1)-1) l=i-d1[i]+1,r=i+d1[i];
        if(r-l<(d2[i]<<1)) l=i-d2[i],r=i+d2[i];
    }
    fore(i,l,r) cout<<s[i];;cout<<'\n';
    return 0;
}
