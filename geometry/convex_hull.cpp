vector<pt> chull(vector<pt> p){// CCW order
	if(SZ(p)<3) return p;//incl collinear
	vector<pt> r; sort(ALL(p)); int k=0;
	fore(_,0,2){//first lower hull, then upper hull
		fore(i,0,SZ(p)){
			while(SZ(r)>1+k&&r.back().left(r[SZ(r)-2],p[i]))r.pop_back();
			r.pb(p[i]);
		}
        r.pop_back(),k=SZ(r),reverse(ALL(p));
	}
	return r;
}