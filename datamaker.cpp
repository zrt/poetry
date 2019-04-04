#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;


int main(){
	srand(time(0));
	int n,q;
	n=q=50;
	int k;
	k=3;
	
	printf("%d %d %d\n",n,q,k);

	for(int i=2;i<=n;i++){
		printf("%d\n",rand()%(i-1)+1);
	}

	for(int i=1;i<=q;i++){
		printf("%d %d\n",i, rand()%n+1);
	}


	return 0;
}