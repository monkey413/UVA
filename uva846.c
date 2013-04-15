#include<stdio.h>
#include<math.h>
int main(){
	int Case, a, b; 
	scanf("%d",&Case) ;
	while(Case--){
		scanf("%d %d",&a,&b) ;	
		int dis = b-a ;
		if(dis<=3) printf("%d\n",dis) ;
		else{
			int n = sqrt(dis) ;
			if(n*n==dis) printf("%d\n",2*n-1) ;
			else if((dis-n*n)<=n) printf("%d\n",2*n);
			else printf("%d\n",2*n+1) ; 
		}
	}
	return 0 ;
}
