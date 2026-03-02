// MAXN must be power of 2 !!
// MOD-1 needs to be a multiple of MAXN !!
CD cp1[MAXN+9],cp2[MAXN+9]; int R[MAXN+9];
void dft(CD* a, int n, bool inv){
	fore(i,0,n)if(R[i]<i)swap(a[R[i]],a[i]);
	for(int m=2;m<=n;m*=2){
		double z=2*pi/m*(inv?-1:1); CD wi=CD(cos(z),sin(z));
		for(int j=0;j<n;j+=m){
			CD w(1);
			for(int k=j,k2=j+m/2;k2<j+m;k++,k2++){
				CD u=a[k];CD v=a[k2]*w;a[k]=u+v;a[k2]=u-v;w=w*wi;
			}
		}
	}
	if(inv)fore(i,0,n)a[i]/=n;
}
poly multiply(poly& p1, poly& p2){
	int n=p1.size()+p2.size()+1,m=1,cnt=0;
	while(m<=n)m+=m,cnt++;
	fore(i,0,m){R[i]=0;fore(j,0,cnt)R[i]=(R[i]<<1)|((i>>j)&1);}
	fore(i,0,m)cp1[i]=0,cp2[i]=0;
	fore(i,0,p1.size())cp1[i]=p1[i];
	fore(i,0,p2.size())cp2[i]=p2[i];
	dft(cp1,m,false);dft(cp2,m,false);
	fore(i,0,m)cp1[i]=cp1[i]*cp2[i];
	dft(cp1,m,true); poly res; n-=2;
	fore(i,0,n)res.pb((tf)floor(cp1[i].real()+0.5));
	return res;
}
