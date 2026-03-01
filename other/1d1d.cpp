// dp[i] = min_{j=i+1}^{n} f(i,j) + dp[j]
// monge inequality must hold for f
ll dp[MAXN];
ll cost(ll l, ll r){} // f(l,r) + dp[r]
ll opt1d1d(){
	deque<ii>dq; dq.pb({n-1,n});
	for(ll j=n-1;j>=0;j--){ // info hasta (j
		auto opt=dq.back().snd; assert(dq.back().fst==j);
		dp[j]=cost(j,opt); if(!j)break; dq.pop_back();
		if(!SZ(dq)||dq.back().fst<j-1)dq.pb({j-1,opt});
		ll s=0;
		while(SZ(dq)){
			auto [i,opt]=dq.front();
			if(cost(i,j)<cost(i,opt))s=i,dq.pop_front();
			else break;
		}
		if(!SZ(dq)){assert(s==j-1);dq.pb({s,j});continue;}
		ll l=s,r=dq.front().fst-1;
		while(l<=r){
			ll m=(l+r)/2;
			if(cost(m,j)<cost(m,dq.front().snd))l=m+1;
			else r=m-1;
		}
		if(r>=0)dq.push_front({r,j});
	}
	return dp[0];
}