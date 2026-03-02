//Max palindrome centered on i, p=pal-parity
vv manacher(string &s, bool p){
    int n=SZ(s), l=-1,r=0; 
    vv d(n); // substr(l,r) last max pal
    fore(i,0,n){
        int k=(i<r?min(d[l+r-i+!p],r-i):p);
        while(i+k<n&&k<i+p&&s[i-k-!p]==s[i+k]) k++;
        d[i]=k;
        if(i+k>r) r=i+k,l=i-k-!p;
    }
    return d;
}
