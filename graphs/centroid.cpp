// tag[y]>=tag[x] for every y in x's connected subgraph (unrooted subtree)
vector<int> g[MAXN];
int tag[MAXN]; // time of discovery of centroid
int fat[MAXN]; // father in centroid decomposition
int szt[MAXN]; // size of subtree
int calcsz(int x, int f){
	szt[x]=1;
	for(auto y:g[x])if(y!=f&&tag[y]<0)szt[x]+=calcsz(y,x);
	return szt[x];
}
int ccnt=0;
void cdfs(int x, int f, int sz=-1){ // O(nlogn)
	if(sz<0)sz=calcsz(x,-1);
	for(auto y:g[x])if(tag[y]<0&&szt[y]*2>=sz){
		szt[x]=0;cdfs(y,f,sz);return;
	}
	tag[x]=ccnt++; fat[x]=f;
	for(auto y:g[x])if(tag[y]<0)cdfs(y,x);
}
void centroid(){mset(tag,-1);ccnt=0;cdfs(0,-1);}