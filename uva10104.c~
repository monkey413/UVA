#include<stdio.h>
int main(){
	int A, B, a1, b1, a2, b2, times, side, tmp  ;
	while(scanf("%d %d",&A,&B)==2){
		/* 輾轉相除法 */ 
		a1=1, b1=0, a2=0, b2=1, side=0 ;
		while(B!=0){
			times = A/B ; 	
			if(!side){
				a1 -= a2*times ;
				b1 -= b2*times ;
				side = 1 ;
			}
			else{
				a2 -= a1*times ;
				b2 -= b1*times ;
				side = 0 ;
			}
			tmp = A ;
			A = B ;
			B = tmp%B ;
		}
		if(!side){
			printf("%d %d %d\n",a1,b1,A) ;
		}
		else{
			printf("%d %d %d\n",a2,b2,A) ;
		}
	}
	return 0 ;
}
