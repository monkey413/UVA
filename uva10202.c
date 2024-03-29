/*http://972169909-qq-com.iteye.com/blog/1679217*/
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
struct pairsum{
	int sum ;	
	int flag ;
}num[45]={0,0};
typedef struct pairsum pairsum ; 
int compare(const void *a, const void *b){
	return ((pairsum *)a)->sum - ((pairsum*)b)->sum;	
}
int main(){
	int n, m, i, j, k, a[10], s, find, x ;
	while(scanf("%d",&n)==1){
		m = n*(n-1)/2 ;
		for(i=0 ; i<m ; ++i){
			scanf(" %d",&num[i].sum) ;	
		}
		qsort(num,m,sizeof(num[i]),compare) ;

		for(i=2 ; i<m ; ++i){
			a[1] = (num[0].sum+num[1].sum-num[i].sum)/2 ;	
			a[2] = num[0].sum - a[1] ; 
			a[3] = num[1].sum - a[1] ;
			if(a[2]+a[3] != num[i].sum) continue ;
			
			for(j=0 ; j<45 ; ++j){
				num[j].flag = 0 ;
			}
			num[i].flag = 1 ; 	
			s = 2 ;
			find = 1 ;
			for(j=4 ; j<=n ; ++j){
				while(num[s].flag) s++ ;
				a[j] = num[s].sum - a[1] ;
				num[s].flag = 1 ;
				for(k=2 ; k<j && find ; ++k){
					for(x=s+1 ; x<m ; ++x){
						if(!num[x].flag && a[j]+a[k]==num[x].sum){
							num[x].flag = 1 ;
							break ;
						}
					}
					if(x>=m) find = 0;
				}
			}
			if(find) break ;
		}
		if(i<m){
			printf("%d",a[1]) ;
			for(i=2 ; i<=n ; ++i) printf(" %d",a[i]) ;
			puts("") ;
		}
		else puts("Impossible") ;
	}
	return 0;
}
