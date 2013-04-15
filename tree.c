#include<stdio.h>
#include<stdlib.h>
#define INF 0x7fffffff
#define NINF 0x80000000
typedef struct{
	int num ;
	int degree ;
	int remove ;
}point;
int main(){
	int n, i, k ;
	char buf[1000000] ;
	point *d, minp, maxp ;
	scanf("%d",&n);
	while(n--){
		scanf("%d",&k) ;
		d = (point*) malloc(sizeof(point)*k) ;	
		for(i=0 ; i<k ; ++i){
			d[i].num = i+1 ;	
			scanf("%d",&d[i].degree) ;
			d[i].remove = 0 ;
		}
		while(1){
			/*find min and max*/
			minp.degree = INF ;
			maxp.degree = NINF ;
			for(i=0 ; i<k ; ++i){
				if(d[i].degree && d[i].degree < minp.degree){
					minp = d[i] ;	
				}
				if(d[i].degree >= maxp.degree){
					maxp = d[i] ;
				}
			}
			if(maxp.degree==0) break;
			printf("%d %d\n",minp.num,maxp.num) ;
			d[minp.num-1].degree-- ;
			d[maxp.num-1].degree-- ;
		}
		puts("") ;
		free(d) ;
	}
	return 0;
}
