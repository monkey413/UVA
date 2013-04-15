#include<stdio.h>
#include<memory.h>
#define NINF 0x80000000 
int main(){
	int m, n, i, j, field=0 ;
	int map[150][150] ;
	while(scanf("%d %d",&m,&n) == 2){
		if(!m && !n) break ;
		if(field) puts("") ;
		memset(map,0,sizeof(map)) ;
		getchar() ;
		for(i=1 ; i<=m ; ++i){
			for(j=1 ; j<=n ; ++j){
				if(getchar()=='*'){
					map[i][j] = NINF ;
					map[i-1][j-1]++ ;
					map[i-1][j]++ ;
					map[i-1][j+1]++ ;
					map[i][j-1]++ ;
					map[i][j+1]++ ; 
					map[i+1][j-1]++ ;
					map[i+1][j]++ ;
					map[i+1][j+1]++ ;
				}
			}
			getchar() ;
		}
		printf("Field #%d:\n",++field) ;
		for(i=1 ; i<=m ; ++i){
			for(j=1 ; j<=n ; ++j){
				if(map[i][j]<0) printf("*") ;
				else printf("%d",map[i][j]) ;
			}
			puts("") ;
		}
	}
	return 0;
}
