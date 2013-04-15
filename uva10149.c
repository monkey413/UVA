#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#define POW(c) (1<<(c))  
#define MASK(c) (((unsigned long)-1) / (POW(POW(c)) + 1))  
#define ROUND(n, c) (((n) & MASK(c)) + ((n) >> POW(c) & MASK(c)))  
int compare(const void *a, const void *b){
	return (*(int*)a-*(int*)b) ;	
}
int bits(int n)  
{  
	n = ROUND(n, 0);  
	n = ROUND(n, 1);  
	n = ROUND(n, 2);  
	n = ROUND(n, 3);  
	n = ROUND(n, 4);  
	return n;  
}  
int SC(int dp[5], int category){
	int point = 0, i, j;
	int value[6] ;
	if(category<6){
		for(i=0 ; i<5 ; ++i) if(dp[i] == category+1) point+=dp[i];
	}
	else{
		switch(category){
			case 6: 
				for(i=0 ; i<5 ; ++i) point+=dp[i] ;
				break ;
			case 7: 
				if(dp[0]==dp[2]||dp[1]==dp[3]||dp[2]==dp[4])
					for(i=0 ; i<5 ; ++i) point+=dp[i] ;
				break ;
			case 8:
				if(dp[0]==dp[3]||dp[1]==dp[4])
					for(i=0 ; i<5 ; ++i) point+=dp[i] ;
				break ;
			case 9:
				if(dp[0]==dp[4]) point = 50 ;
				break ;
			case 10:
				memset(value,0,sizeof(value));
				for(i=0 ; i<5 ; ++i){
					value[dp[i]-1] = 1 ;
				}
				for(i=0 ; i<3 ; ++i){
					if(value[i]&&value[i+1]&&value[i+2]&&value[i+3])
						point = 25 ;
				}
				break ;
			case 11:
				if(dp[1]==dp[0]+1 && dp[2]==dp[1]+1 && dp[3]==dp[2]+1 && dp[4]==dp[3]+1)
					point = 35 ; 
				break ;
			case 12: 
				if(dp[0]==dp[1] && dp[2]==dp[4] || dp[0] ==dp[2] && dp[3] == dp[4])
					point = 40 ;
				break ;
		}
	}
	return point ;
}
void DP(int dp[13][5]){
	int score[13][13], sum[1<<13][64], memo[1<<13][64][2] ;
	int i, j ;
	for(i=0 ; i<13 ; ++i){
		for(j=0 ; j<13 ; ++j){
			score[i][j] = SC(dp[i], j) ;
		}
	}
	memset(sum,-1,sizeof(sum)) ;
	sum[0][0] = 0 ;
	int b, s, t, d, a, m, c, u ; 
	for(m=0 ; m<8192 ; ++m){
		for(c=0 ; c<13 ; ++c){
			if(!(m&(1<<c))){
				b = bits(m) ;
				s = score[b][c];
				t = m | (1<<c) ;
				a =  (c<6)?s:0 ;
				for(u=0 ; u<64 ; ++u){
					if(sum[m][u]>-1){
						d = ((u+a)<63?(u+a):63) ;
						if(sum[t][d]<sum[m][u]+s){
							memo[t][d][0] = c ;
							memo[t][d][1] = u ;
							sum[t][d] = sum[m][u] + s ;
						}
					}
				}
			}
		}
	}
	int max = 0, bonus=0, upper, total ; 
	for(u=0 ; u<63 ; ++u){
		if(sum[8191][u]>max){
			max = sum[8192][u] ;
			upper = u;
		}
	}
	total = max ;
	if(sum[8191][63]>-1){
		bonus = 35  ;
		total = sum[8192][63]+bonus ;
	}

	if(max<total){
		max = total ;
		upper = 63 ;
	}

	int last = 8191 ;
	int category[13];
	for(i=12 ; i>=0 ; --i){
		category[i] = memo[last][upper][0] ; 
		upper = memo[last][upper][1] ;
		last ^= (1<<category[i]) ;
	}

	for(i=0 ; i<13 ; ++i){
		for(j=0 ; j<13 ; ++j){
			if(category[j]==i){
				printf("%d ",score[j][i]) ;
			}
		}
	}
	printf("%d %d\n",bonus,max) ;
}
int main(){
	int dp[13][5], i, j, k;
	char buf[15];
	while(fgets(buf,sizeof(buf),stdin)!=NULL){
		for(i=0 ; i<13 ; ++i){
			if(i) fgets(buf,sizeof(buf),stdin) ;
			for(j=0 ; j<5 ; ++j){
				dp[i][j] = buf[j*2]-'0' ;
			}
			qsort(dp[i],5,sizeof(int),compare) ;
		}
		DP(dp) ;		
	}
	return 0 ;
}
