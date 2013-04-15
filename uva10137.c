#include<stdio.h>
int main(){
	int n, i ;
	double num[1000], sum, posdiff, negdiff, avg ;
	while(scanf("%d",&n) && n){
		sum = 0 ;
		for(i=0 ; i<n ; ++i){
			scanf("%lf",&num[i]) ;
			sum += num[i] ;
		}
		avg = sum / n ;  
		avg = (double)(int)(avg*100+0.5)/100 ;
		posdiff = negdiff = 0 ;
		for(i=0 ; i<n ; ++i){
			if(num[i]>avg) posdiff += (num[i]-avg) ;	
			else if(num[i]<avg) negdiff += (avg-num[i]) ; 
		}
		printf("$%.2lf\n",(posdiff<negdiff?posdiff:negdiff)) ;
	}
	return 0;
}
