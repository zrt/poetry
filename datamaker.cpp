#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

// 注意换行\r
// x比较大比较好


int p[50000+5];
int inv[50000+5];
void makechain(int n,int q,int k){
	printf("%d %d %d\n",n,q,k);
	for(int i=1;i<=n;i++) p[i]=i;
	random_shuffle(p+2,p+n+1);
	for(int i=1;i<=n;i++) inv[p[i]]=i;
	for(int i=2;i<=n;i++){
		printf("%d\n",p[inv[i]-1]);
	}
	for(int i=1;i<=q;i++){
		int x=n/2 + rand()%(n-n/2)+1;
		int y=rand()%n+1;
		printf("%d %d\n",x,y);
	}
}
int fa[50000+5];
void makedata(int n,int q,int k){
	printf("%d %d %d\n",n,q,k);
	for(int i=1;i<=n;i++) p[i]=i;
	random_shuffle(p+2,p+n+1);
	for(int i=1;i<=n;i++) inv[p[i]]=i;
	for(int i=2;i<=n/2;i++){
		fa[i] = rand()%(i-1)+1;
	}
	for(int i=n/2+1;i<=n;i++){
		fa[i] = i-1;
	}
	for(int i=2;i<=n;i++){
		printf("%d\n",p[fa[inv[i]]]);
	}
	for(int i=1;i<=q;i++){
		int x=n/2 + rand()%(n-n/2)+1;
		int y=rand()%n+1;
		printf("%d %d\n",x,y);
	}
}

void makedata2(int n,int q,int k){
	printf("%d %d %d\n",n,q,k);
	assert(n==q);
	for(int i=1;i<=n;i++) p[i]=i;
	random_shuffle(p+2,p+n+1);
	for(int i=1;i<=n;i++) inv[p[i]]=i;
	for(int i=2;i<=n/2;i++){
		fa[i] = rand()%(i-1)+1;
	}
	for(int i=n/2+1;i<=n;i++){
		fa[i] = i-1;
	}
	for(int i=2;i<=n;i++){
		printf("%d\n",p[fa[inv[i]]]);
	}
	for(int i=1;i<=q;i++){
		int x=i;
		int y=rand()%n+1;
		printf("%d %d\n",x,y);
	}
}

void make(int T){
	// 1 \le n,Q \le 50000 ,  1 \le k \le 10^9$ , $1 \le x,y,fa_i \le n
	if(T<=4){
		//n,Q \le 2000
		makedata(2000,2000,int(1e8)+rand()%int(1e9-1e8)+1);
	}else if(T<=8){
		// 存在某个点的深度为$n$
		makechain(50000,50000,int(1e8)+rand()%int(1e9-1e8)+1);
	}else if(T<=10){
		// $Q=n$，且对于第i个询问，$x=i$
		makedata2(50000,50000,int(1e8)+rand()%int(1e9-1e8)+1);
	}else if(T<=12){
		// k=1
		if(T==11)
			makedata(10000,50000,1);
		else
			makedata(20000,50000,1);
	}else if(T<=14){
		// k=2
		if(T==13)
			makedata(30000,50000,2);
		else
			makedata(40000,50000,2);
	}else if(T<=16){
		// k=3
		makedata(50000,50000,3);
	}else{
		//
		if(T==17)
			makedata(10000,50000,int(1e8)+rand()%int(1e9-1e8)+1);
		else
			makedata(50000,50000,int(1e8)+rand()%int(1e9-1e8)+1);
	}
}

int main(){
	srand(time(0));
	for(int T=1;T<=20;T++){
		char s[100];
		sprintf(s,"tree%d.in",T);
		freopen(s,"w",stdout);
		// make data
		make(T);
		fclose(stdout);
		sprintf(s,"./std < tree%d.in > tree%d.out",T,T);
		system(s);
	}

	// int n,q;
	// n=q=50000;
	// int k;
	// k=1000000;

	// printf("%d %d %d\n",n,q,k);

	// for(int i=2;i<=n;i++){
	// 	printf("%d\n",rand()%(i-1)+1);
	// }

	// for(int i=1;i<=q;i++){
	// 	printf("%d %d\n",rand()%n+1, rand()%n+1);
	// }

	return 0;
}