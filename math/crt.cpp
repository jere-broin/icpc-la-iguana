#define mod(a,m) (((a)%m+m)%m)
#define inv(a,m) mod(diophantine(a,m,1).fst,m)
ii sol(ll a, ll x1, ll m){ //requires dioph
  ll d=gcd(a,m);if(d<2)return{mod(x1*inv(a,m),m),m};
  return x1%d?ii({-1LL,-1LL}):sol(a/d,x1/d,m/d);
}
ii crt(vv as, vv bs, vv ms){ //returns:(sol,lcm)
    ll x1=0,m1=1;
    fore(i,0,SZ(ms)){
        auto [x2,m2]=sol(as[i],bs[i],ms[i]);
        if(m2<0||(x1-x2)%gcd(m1,m2))return{-1,-1};
        if(m1==m2)continue;; ll l=lcm(m1,m2);
        ll k=diophantine(m2,-m1,x1-x2).snd;
        x1=mod((xl)m1*k+x1,l);m1=l;
    }
    return {x1,m1};
}// as[i]*x=bs[i] (ms[i]); assumes lcm fits in ll
