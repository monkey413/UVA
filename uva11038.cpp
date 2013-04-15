#include<iostream>
using namespace std ; 

long long int f(long long int num){
   if(num<0) return 0 ;
   long long int tmp, c, ten=10 ;
    tmp = num ;
    c = 1 + tmp/10;
    tmp /= 10;
    while (tmp >= 10)
    {
        c += (tmp/10) * ten;
        if (tmp%10 == 0)
            c -= (ten-1-num%ten);
        ten *= 10;
        tmp /= 10;
    }
    return c;
}

int main(){
    long long int m, n ; 
    while(cin>>m>>n && m>=0){
        cout << f(n)-f(m-1) << endl ; 
    }
    return 0 ; 
}
