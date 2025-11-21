// CCW order
// Includes collinear points (change sign of EPS in left to exclude)
// Complexity: O(nlog(n)), O(n) if the vector is alredy sorted
vector<pt> chull(vector<pt> p){
	if(SZ(p)<3) return p;
	vector<pt> r;
    sort(ALL(p)); //first x, then y. Remove if alredy sorted
	int k=0;
	fore(_,0,2){//first lower hull, then upper hull
		fore(i,0,SZ(p)){
			while(SZ(r)>1+k&&r.back().left(r[SZ(r)-2],p[i]))r.pop_back();
			r.pb(p[i]);
		}
        r.pop_back(),k=SZ(r),reverse(ALL(p));
	}
	return r;
}
