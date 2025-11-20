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
