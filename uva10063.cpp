#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
void DFS(int now);
char str[11], Ans[11];
int len;
int main()
{
    int judge = 0;
    while(scanf("%s", str) == 1){
        if(judge)   puts("");
        judge = 1;
        len = strlen(str);
        DFS(0);
    }
    return 0;
}
void DFS(int now){
    if(now == len){
        Ans[now] = '\0';
        puts(Ans);
        return ;
    }
    for(int i = now; i >= 1; i--)
        Ans[i] = Ans[i-1];
    for(int i = 0; i <= now; i++){
        Ans[i] = str[now];
        DFS(now+1);
        Ans[i] = Ans[i+1];
    }
}

