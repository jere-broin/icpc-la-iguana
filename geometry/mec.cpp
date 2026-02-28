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