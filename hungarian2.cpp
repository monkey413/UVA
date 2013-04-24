/*尚未完成*/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

#define INF (0x7FFFFFFF)

#define size1 (13)
#define size2 (13)
#define NROUNDS (13) 
#define NCATEGORIES (13) 
#define NDICES (5) 

#define verbose (1)

using namespace std ;

int Array[size1][size2];
int yahtzee[NROUNDS][NDICES];  
int scoring[NROUNDS][NCATEGORIES] ;
char Result[size1][size2];  // used as boolean
int largest = -1 ;

void initArray()
{
		int i,j;

		for (i=0;i<size1;++i)
				for (j=0;j<size2;++j)
						Array[i][j]=99999999;
}

bool cmp(int a, int b)  
{  
    return a < b;  
} 

int scoring(int dices[NDICES], int category)  
{  
    // 計一到計六。  
    int ret = 0;  
    if (category < 6)  
    {  
        for (int i = 0; i < NDICES; i++)  
            if (dices[i] == (category + 1))  
                ret += dices[i];  
    }  
    else  
    {  
        switch (category)  
        {  
                // 機會。  
            case 6:  
                for (int i = 0; i < NDICES; i++)  
                    ret += dices[i];  
                break;  
                // 三同。  
            case 7:  
                if (dices[0] == dices[2] || dices[1] == dices[3]  
                 || dices[2] == dices[4])  
                    for (int i = 0; i < NDICES; i++)  
                        ret += dices[i];  
                break;  
                // 四同。  
            case 8:  
                if (dices[0] == dices[3] || dices[1] == dices[4])  
                    for (int i = 0; i < NDICES; i++)  
                        ret += dices[i];  
                break;  
                // 五同。  
            case 9:  
                if (dices[0] == dices[4])  
                    ret = 50;  
                break;  
                // 小順。  
            case 10:  
                bool value[6];  
                memset(value, 0, sizeof(value));  
  
                for (int i = 0; i < 5; i++)  
                    value[dices[i] - 1] = true;  
  
                for (int i = 0; i < 3; i++)  
                    if (value[i] && value[i + 1] &&   
                    value[i + 2] && value[i + 3])  
                        ret = 25;  
                break;  
                // 大順。  
            case 11:  
                if (dices[1] == (dices[0] + 1) &&  
                    dices[2] == (dices[1] + 1) &&  
                    dices[3] == (dices[2] + 1) &&  
                    dices[4] == (dices[3] + 1))  
                      
                    ret = 35;  
                break;  
                // 葫蘆。  
            case 12:  
                if (dices[0] == dices[1] &&  
                    dices[2] == dices[4] ||  
                    dices[0] == dices[2] &&  
                    dices[3] == dices[4])  
                    ret = 40;  
                break;  
        }  
    }  
      
    return ret;  
}  

void hungarian()
{
		int i,j;
		int False=0,True=1;

		unsigned int m=size1,n=size2;
		int k;
		int l;
		int s;
		int col_mate[size1]={0};
		int row_mate[size2]={0};
		int parent_row[size2]={0};
		int unchosen_row[size1]={0};
		int t;
		int q;
		int row_dec[size1]={0};
		int col_inc[size2]={0};
		int slack[size2]={0};
		int slack_row[size2]={0};
		int unmatched;
		int cost=0;

		for (i=0;i<size1;++i)
				for (j=0;j<size2;++j)
						Result[i][j]=False;

		// Begin subtract column minima in order to start with lots of zeroes 12
		printf("Using heuristic\n");
		for (l=0;l<n;l++)
		{
				s=Array[0][l];
				for (k=1;k<n;k++)
						if (Array[k][l]<s)
								s=Array[k][l];
				cost+=s;
				if (s!=0)
						for (k=0;k<n;k++)
								Array[k][l]-=s;
		}
		// End subtract column minima in order to start with lots of zeroes 12

		// Begin initial state 16
		t=0;
		for (l=0;l<n;l++)
		{
				row_mate[l]= -1;
				parent_row[l]= -1;
				col_inc[l]=0;
				slack[l]=INF;
		}
		for (k=0;k<m;k++)
		{
				s=Array[k][0];
				for (l=1;l<n;l++)
						if (Array[k][l]<s)
								s=Array[k][l];
				row_dec[k]=s;
				for (l=0;l<n;l++)
						if (s==Array[k][l] && row_mate[l]<0)
						{
								col_mate[k]=l;
								row_mate[l]=k;
								if (verbose)
										printf("matching col %d==row %d\n",l,k);
								goto row_done;
						}
				col_mate[k]= -1;
				if (verbose)
						printf("node %d: unmatched row %d\n",t,k);
				unchosen_row[t++]=k;
row_done:
				;
		}
		// End initial state 16

		// Begin Hungarian algorithm 18
		if (t==0)
				goto done;
		unmatched=t;
		while (1)
		{
				if (verbose)
						printf("Matched %d rows.\n",m-t);
				q=0;
				while (1)
				{
						while (q<t)
						{
								// Begin explore node q of the forest 19
								{
										k=unchosen_row[q];
										s=row_dec[k];
										for (l=0;l<n;l++)
												if (slack[l])
												{
														int del;
														del=Array[k][l]-s+col_inc[l];
														if (del<slack[l])
														{
																if (del==0)
																{
																		if (row_mate[l]<0)
																				goto breakthru;
																		slack[l]=0;
																		parent_row[l]=k;
																		if (verbose)
																				printf("node %d: row %d==col %d--row %d\n",
																								t,row_mate[l],l,k);
																		unchosen_row[t++]=row_mate[l];
																}
																else
																{
																		slack[l]=del;
																		slack_row[l]=k;
																}
														}
												}
								}
								// End explore node q of the forest 19
								q++;
						}

						// Begin introduce a new zero into the matrix 21
						s=INF;
						for (l=0;l<n;l++)
								if (slack[l] && slack[l]<s)
										s=slack[l];
						for (q=0;q<t;q++)
								row_dec[unchosen_row[q]]+=s;
						for (l=0;l<n;l++)
								if (slack[l])
								{
										slack[l]-=s;
										if (slack[l]==0)
										{
												// Begin look at a new zero 22
												k=slack_row[l];
												if (verbose)
														printf(
																		"Decreasing uncovered elements by %d produces zero at [%d,%d]\n",
																		s,k,l);
												if (row_mate[l]<0)
												{
														for (j=l+1;j<n;j++)
																if (slack[j]==0)
																		col_inc[j]+=s;
														goto breakthru;
												}
												else
												{
														parent_row[l]=k;
														if (verbose)
																printf("node %d: row %d==col %d--row %d\n",t,row_mate[l],l,k);
														unchosen_row[t++]=row_mate[l];
												}
												// End look at a new zero 22
										}
								}
								else
										col_inc[l]+=s;
						// End introduce a new zero into the matrix 21
				}
breakthru:
				// Begin update the matching 20
				if (verbose)
						printf("Breakthrough at node %d of %d!\n",q,t);
				while (1)
				{
						j=col_mate[k];
						col_mate[k]=l;
						row_mate[l]=k;
						if (verbose)
								printf("rematching col %d==row %d\n",l,k);
						if (j<0)
								break;
						k=parent_row[j];
						l=j;
				}
				// End update the matching 20
				if (--unmatched==0)
						goto done;
				// Begin get ready for another stage 17
				t=0;
				for (l=0;l<n;l++)
				{
						parent_row[l]= -1;
						slack[l]=INF;
				}
				for (k=0;k<m;k++)
						if (col_mate[k]<0)
						{
								if (verbose)
										printf("node %d: unmatched row %d\n",t,k);
								unchosen_row[t++]=k;
						}
				// End get ready for another stage 17
		}
done:

		// Begin doublecheck the solution 23
		for (k=0;k<m;k++)
				for (l=0;l<n;l++)
						if (Array[k][l]<row_dec[k]-col_inc[l])
								exit(0);
		for (k=0;k<m;k++)
		{
				l=col_mate[k];
				if (l<0 || Array[k][l]!=row_dec[k]-col_inc[l])
						exit(0);
		}
		k=0;
		for (l=0;l<n;l++)
				if (col_inc[l])
						k++;
		if (k>m)
				exit(0);
		// End doublecheck the solution 23
		// End Hungarian algorithm 18

		for (i=0;i<m;++i)
		{
				Result[i][col_mate[i]]=True;
				/*TRACE("%d - %d\n", i, col_mate[i]);*/
		}
		for (k=0;k<m;++k)
		{
				for (l=0;l<n;++l)
				{
						/*TRACE("%d ",Array[k][l]-row_dec[k]+col_inc[l]);*/
						Array[k][l]=Array[k][l]-row_dec[k]+col_inc[l];
				}
				/*TRACE("\n");*/
		}
		for (i=0;i<m;i++)
				cost+=row_dec[i];
		for (i=0;i<n;i++)
				cost-=col_inc[i];
		printf("Cost is %d\n",13*largest-cost);
}

void print(){
	int i, j ;
	for(i=0 ; i<size1 ; ++i){
		for(j=0 ; j<size2 ; ++j){
			printf("%-3d",Array[i][j]) ;
		}
		puts("") ;
	}
}

int main()
{
		int y,x,i;
		//initArray();
		string line ; 
		int count = 0 ;
		while (getline(cin, line))  
		{  
				istringstream iss(line);  
				for (int i = 0; i < NDICES; i++)  
						iss >> yahtzee[count % NROUNDS][i];  

				sort(yahtzee[count % NROUNDS], yahtzee[count % NROUNDS] + NDICES, cmp);  

				if (++count % NROUNDS == 0){
						for (int i = 0; i < NROUNDS; i++){  
								for (int j = 0; j < NCATEGORIES; j++){  
										Array[i][j] = scoring(yahtzee[i], j); 
								}
						}
						print() ;
						largest = -1 ; 
						for (y=0;y<size1;++y){
								for (x=0;x<size2;++x){
										//scanf("%d",&Array[y][x]) ;
										if(Array[y][x]>largest) largest = Array[y][x] ; 
								}
						}
						
						printf("largest:%d\n",largest) ;

						for (y=0;y<size1;++y){
								for (x=0;x<size2;++x){
										Array[y][x] = largest-Array[y][x] ;
								}
						}
						hungarian();

						for (y=0;y<size1;++y)
								for (x=0;x<size2;++x)
										if (Result[y][x])
												printf("%d and %d are connected in the assignment\n",y,x);
				}
		}  
		return 0 ;
}

