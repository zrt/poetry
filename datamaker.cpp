#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

// 注意换行\r
// x比较大比较好

int main(){
	srand(time(0));
	int n,q;
	n=q=50000;
	int k;
	k=1000000;

	printf("%d %d %d\n",n,q,k);

	for(int i=2;i<=n;i++){
		printf("%d\n",rand()%(i-1)+1);
	}

	for(int i=1;i<=q;i++){
		printf("%d %d\n",rand()%n+1, rand()%n+1);
	}


	return 0;
}