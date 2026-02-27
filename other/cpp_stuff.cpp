ifstream inpu;	inpu.open("pre", ios::in); // file input
// double inf
const double DINF=numeric_limits<double>::infinity();
// Iterate over NON EMPTY subsets of bitmask
for(int s=m;s;s=(s-1)&m) // Decreasing order
for (int s=0;s=s-m&m;) 	 // Increasing order
// Generate all n-bit bitmasks with k ones, increasing
ll mk=(1ll<<k)-1,r,c;
while(mk<=(1ll<<n)-(1ll<<(n-k))){
	// Code here
	if(!k)break;
	c=mk&-mk,r=mk+c,mk=r|(((r^mk)>>2)/c);
}
#include <tr2/dynamic_bitset> // dynamic bitset
using namespace tr2;
dynamic_bitset<> b; // bugged shifts in GCC <= 14.2 !!
gp_hash_table<ll,ll> ht; // faster hash table, same includes as extended set
ull splitmix64(ull x) { // splitmix
	x += R1; // R1, R2, R3, random constant 64-bit odd numbers
	x = (x ^ (x >> 30)) * R2;
	x = (x ^ (x >> 27)) * R3;
	return x ^ (x >> 31);
}