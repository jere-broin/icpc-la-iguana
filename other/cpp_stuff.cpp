// Iterate all NON EMPTY submasks of m
for(int s=m;s;s=(s-1)&m) // Decreasing order
for(int s=0;s=s-m&m;) 	 // Increasing order
// Iterate all n-bit bitmasks with k ones, increasing
ll mk=(1ll<<k)-1,r,c;
while(mk<=(1ll<<n)-(1ll<<(n-k))){
	// Code here
	if(!k)break;
	c=mk&-mk,r=mk+c,mk=r|(((r^mk)>>2)/c);
}
//interactive tester
mkfifo fifo; (./solution < fifo) | (./interactor > fifo)
ifstream inpu;	inpu.open("pre", ios::in); // file input
//generator
from os import system
system("./a<in>o")
x=open("o","r").read().strip().split()
//dp optimizations
d&c: opt(i,j) <= opt(i,j+1)
knuth: opt(i,j-1) <= opt(i,j) <= opt(i+1,j)
//Pick: A=I+B/2-1  (area, inside, border)
auto rng=mt19937(time(0));
uniform_(int|real)_distribution<int>(a,b)(rng);
#pragma GCC optimize("Ofast") // may lead to precision errors
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <tr2/dynamic_bitset> // dynamic bitset<> b
using namespace tr2; // bugged shifts in GCC <= 14.2 !!
xl MOD=212345678987654321LL,P=1777771,PI=106955741089659571LL; //hash consts
gp_hash_table<ll,ll> ht; // faster hash table, same includes as extended set
ull splitmix64(ull x) { // splitmix
	x += R1; // R1, R2, R3, random constant 64-bit odd numbers
	x = (x ^ (x >> 30)) * R2;
	x = (x ^ (x >> 27)) * R3;
	return x ^ (x >> 31);
}