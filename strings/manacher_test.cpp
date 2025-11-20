// SPOJ PLD - AC
// http://www.spoj.com/problems/PLD/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
typedef vector<int> vv;

#define MAXN (1<<20)

//Máximo palíndromo de paridad p centrado en i
//Complejidad: O(n)

// s = a a b b a a c a a b b a a
// d = 0 1 0 3 0 1 0 0 1 0 3 0 1 , p=0
// d = 1 1 1 1 1 1 7 1 1 1 1 1 1 , p=1
vv manacher(string &s, bool p){ // p == paridad de la longitud de los palíndromos
    int n=SZ(s),l=-1,r=0;  // último palíndromo maximal en (l,r)
    vv d(n);
    fore(i,0,n){
        int k=(i<r?min(d[l+r-i+!p],r-i):p);
        while(i+k<n&&k<i+p&&s[i-k-!p]==s[i+k]) k++;
        d[i]=k;
        if(i+k>r) r=i+k,l=i-k-!p;
    }
    return d;
}

char _s[MAXN];

int main(){
	int k;
	scanf("%d%s",&k,_s);
	string s(_s);
	auto d1=manacher(s,1);
    auto d2=manacher(s,0);
	int r=0;
	fore(i,0,s.size()){
		if(k%2==1&&2*d1[i]-1>=k)r++;
		if(k%2==0&&2*d2[i]>=k)r++;
	}
	printf("%d\n",r);
	return 0;
}
