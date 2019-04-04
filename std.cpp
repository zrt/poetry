#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>

// by zrt
// zhangruotian@foxmail.com

using namespace std;

typedef long long LL;

const int MAXN = 50000+5;
const LL mod = 998244353;

int n,Q,k;
int H[MAXN], X[MAXN], P[MAXN], tot;
int fa[MAXN], dep[MAXN], dfn[MAXN], invdfn[MAXN], siz[MAXN], son[MAXN], top[MAXN];

inline void add(int x,int y){
	P[++tot]=y;X[tot]=H[x];H[x]=tot;
}

struct Query{
	int x,y,id;
}query[MAXN];

int ans[MAXN];


bool cmp_by_x(Query a, Query b){
	return a.x<b.x;
}

void dfs1(int x){
	dep[x] = dep[fa[x]] + 1;
	siz[x] = 1;
	for(int i=H[x];i;i=X[i]){
		dfs1(P[i]);
		siz[x] += siz[P[i]];
		if(siz[P[i]]>siz[son[x]]){
			son[x] = P[i];
		}
	}
}

int tim;

void dfs2(int x){
	dfn[x] = ++tim;
	if(!top[x]) top[x]=x;
	if(son[x]) top[son[x]] = top[x], dfs2(son[x]);
	for(int i=H[x];i;i=X[i]){
		if(P[i] == son[x]) continue;
		dfs2(P[i]);
	}
}

LL pow(LL a,LL b,LL p){
	LL ret = 1%p;
	while(b){
		if(b&1) ret = ret*a%p;
		b>>=1;
		a=a*a%p;
	}
	return ret;
}

const int MAXN4 = MAXN*4;
struct SEGMENT_TREE{
	LL sum[MAXN4], cnt[MAXN4], pre[MAXN4]; // sum维护的和, cnt下方的标记, pre这一段本身的和
	void updsum(int o){
		sum[o] = (sum[o<<1] + sum[o<<1|1])%mod;
	}
	void bd(int o,int l,int r){
		if(l==r){
			pre[o] = (pow(dep[invdfn[l]],k,mod) - pow(dep[invdfn[l]]-1,k,mod) + mod)%mod;
			cnt[o] = sum[o] = 0;
		}else{
			int mid=(l+r)/2;
			bd(o<<1,l,mid);
			bd(o<<1|1,mid+1,r);
			pre[o] = (pre[o<<1]+pre[o<<1|1])%mod;
			// updsum(o);
		}
	}
	void build(){
		bd(1,1,n);
	}
	void down(int o){
		if(cnt[o]>0){
			sum[o<<1] = (sum[o<<1]+(pre[o<<1]*cnt[o])%mod)%mod;
			cnt[o<<1] += cnt[o];
			sum[o<<1|1] = (sum[o<<1|1]+(pre[o<<1|1]*cnt[o])%mod)%mod;
			cnt[o<<1|1] += cnt[o];
			cnt[o]=0;
		}
	}
	void add(int o,int l,int r,int L,int R){
		if(l == L && r == R){
			sum[o] = (sum[o]+pre[o]) % mod;
			cnt[o] ++;
		}else{
			int mid=(l+r)/2;
			down(o);
			if(R<=mid) add(o<<1,l,mid,L,R);
			else if(L>mid) add(o<<1|1,mid+1,r,L,R);
			else add(o<<1,l,mid,L,mid), add(o<<1|1,mid+1,r,mid+1,R);
			updsum(o);
		}
	}
	void add(int l,int r){
		assert(l<=r);
		add(1,1,n,l,r);
	}
	LL ask(int o,int l,int r,int L,int R){
		if(l==L && r == R){
			return sum[o];
		}else{
			int mid=(l+r)/2;
			down(o);
			if(R<=mid) return ask(o<<1,l,mid,L,R);
			else if(L>mid) return ask(o<<1|1,mid+1,r,L,R);
			else return (ask(o<<1,l,mid,L,mid) + ask(o<<1|1,mid+1,r,mid+1,R))%mod;
		}
	}
	LL ask(int l,int r){
		assert(l<=r);
		return ask(1,1,n,l,r);
	}
}tree;

void prepare(){
	dfs1(1);
	dfs2(1);
	assert(tim == n);
	for(int i=1;i<=n;i++) invdfn[dfn[i]] = i;
	tree.build();
}

void add_point(int x){
	while(x){
		tree.add(dfn[top[x]], dfn[x]);
		x=fa[top[x]];
	}
}

LL ask(int x){
	LL ret = 0;
	while(x){
		ret = (ret + tree.ask(dfn[top[x]], dfn[x]))%mod;
		x=fa[top[x]];
	}
	return ret;
}

int main(){
	// input
	scanf("%d%d%d",&n,&Q,&k);
	assert(n+5 <= MAXN );
	assert(Q+5 <= MAXN );

	for(int i=2,x;i<=n;i++){
		scanf("%d",&x);
		add(x,i);
		fa[i]=x;
	}
	for(int i=1;i<=Q;i++){
		scanf("%d%d",&query[i].x,&query[i].y);
		query[i].id = i;
	}

	// prepare
	prepare();

	// solve
	sort(query+1,query+Q+1,cmp_by_x);
	int p = 1;
	for(int i=1;i<=n;i++){
		add_point(i);
		while(p <= Q && query[p].x == i){
			ans[query[p].id] = ask(query[p].y);
			p++;
		}
	}
	assert(p==Q+1);

	// output
	for(int i=1;i<=Q;i++){
		printf("%d\n",ans[i]);
	}

	return 0;
}
