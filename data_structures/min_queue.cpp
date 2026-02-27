struct MinQ{ // O(1) amortized
	deque<ii>q; ll dif=0;
	MinQ(){}
	void push(ll x){
		ll cnt=1;
		x-=dif;
		while(SZ(q)&&x<=q.back().fst)cnt+=q.back().snd,q.pop_back();
		q.pb({x,cnt});
	}
	void pop(){
		if(!SZ(q))return;
		if(q.front().snd>1)q.front().snd--;
		else q.pop_front();
	}
	ll query(){
		if(!SZ(q))return INF; // querying empty queue
		return q.front().fst+dif;
	}
	void add(ll x){dif+=x;}
};