#include<stdio.h>
#define swap(a,b){int tmp; tmp = a ; a = b ; b = tmp ;}
int cycle(unsigned int a){
	int cycle_length = 1 ;
	while(a!=1){
		if(a&1){
			a = 3*a+1 ;
			cycle_length++ ;
		}
		a /= 2 ;
		cycle_length++ ;
	}
	return cycle_length ;
}
int main(){
	int i, j;
	unsigned int max, t ;
	while(scanf("%d %d",&i,&j)==2){
		printf("%d %d",i,j) ;
		if(i>j) swap(i,j) ;
		max = 0 ;
		for(;i<=j;i++){
			t = cycle(i) ;
			if(t>max){
				max = t ;
			}
		}
		printf(" %d\n",max);
	}
	return 0;
}
