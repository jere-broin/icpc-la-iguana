// bash commands for interaction:

// mkfifo fifo
// (./solution < fifo) | (./grader > fifo)


// sample grader for cf 101021A (guess a number, queries: is it >=k?)
#include <bits/stdc++.h>
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long ll;

const ll MAX_QUERIES=25;

// for external input use in>>
// for external output use cerr<<

int main(){FIN;
	ifstream in; in.open("in",ios::in); // input in file "in"
	
	// tipically hidden info
	// enter it with in>>
	ll n; in>>n;
	
	cerr<<"Input:\n";
	cerr<<n<<"\n";
	ll cnt=0; // number of queries
	while(1){
		string x; cin>>x;
		if(x!="!"){
			if(++cnt > MAX_QUERIES){
				cerr<<"Too much queries\n";
				exit(0);
			}
			ll k=stoll(x);
			if(n >= k) cout<<">="<<endl; // use endl
			else cout<<"<"<<endl; // use endl
		}
		else {
			ll k; cin>>k;
			cerr<<"Answered:\n";
			cerr<<k<<"\n";
			if(n==k)cerr<<"Correct :)\n";
			else cerr<<"Incorrect\n";
			break;
		}
	}
	return 0;
}