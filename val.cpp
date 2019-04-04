#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>

using namespace std;

const int MAXN = 100 +5;
int  fa[MAXN];

int n,q;
int tag[MAXN];

int mark(int x){
	if(fa[x]){
		int t = mark(fa[x]);
		t++;
		tag[x] += t*t*t-(t-1)*(t-1)*(t-1);
		return t;
	}else{
		tag[x] += 1;
		return 1;
	}
}

int ask(int x){
	int ret = 0;
	while(x){
		ret += tag[x];
		x = fa[x];
	}
	return ret;
}

int main(){
	scanf("%d%d",&n,&q);
	for(int i=2,x;i<=n;i++){
		scanf("%d",&x);
		fa[i]=x;
	}
	int cnt = 0;
	while(q--){
		cnt ++;
		mark(cnt);

		int x,y;
		scanf("%d%d",&x,&y);
		assert(cnt == x);
		
		printf("%d\n",ask(y));
	}

	return 0;
}