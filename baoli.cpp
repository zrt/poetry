#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 50000 +5;
const int mod = 998244353;
int H[MAXN], P[MAXN], X[MAXN], tot;
int dep[MAXN], fa[MAXN];
inline void add(int x,int y){
	P[++tot]=y;X[tot]=H[x];H[x]=tot;
}
int n,q,k;
void dfs(int x){
	dep[x] = dep[fa[x]] +1;
	for(int i=H[x];i;i=X[i]){
		dfs(P[i]);
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	while(dep[x]>dep[y]) x=fa[x];
	while(x!=y){
		x = fa[x];
		y = fa[y];
	}
	return x;
}
int ask(int x,int y){
	int t = dep[lca(x,y)];
	int ret = 1;
	for(int i=0;i<k;i++){
		ret = ret*1LL*t%mod;
	}
	return ret;
}
int main(){
	scanf("%d%d%d",&n,&q,&k);
	for(int i=2,x;i<=n;i++){
		scanf("%d",&x);
		add(x,i);
		fa[i]=x;
	}
	dfs(1); // 1 号点为根
	while(q--){
		int x,y;
		scanf("%d%d",&x,&y);
		int ans = 0;
		for(int i=1;i<=x;i++){
			ans += ask(i,y);
			ans %= mod;
		}
		printf("%d\n",ans);
	}


	return 0;
}