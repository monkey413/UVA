#include<iostream>
#include<string>
#include<algorithm>
using namespace std ;
class letter{
	public :
		char let ; 
		int  count ;
}num[26] ;
bool cmp(letter a, letter b){
	if(a.count == b.count) return a.let < b.let ; 
	else return b.count < a.count ;
}
int main(){
	int n ;
	string s ;
	while(cin>>n){
		getline(cin,s) ;
		for(int j=0 ; j<26 ; ++j){
			num[j].count = 0 ;
			num[j].let = 'A'+j ;
		}
		for(int j=0 ; j<n ; ++j){
			getline(cin,s) ;	
			for(int i=0 ; i<s.length() ; ++i){
				if(s[i]>='a' && s[i]<='z') num[s[i]-'a'].count++ ;
				else if(s[i]>='A' && s[i]<='Z') num[s[i]-'A'].count++ ;
			}
		}
		sort(num,num+26,cmp) ;
		for(int i=0 ; i<26 ; ++i){
			if(num[i].count) cout << num[i].let << " " << num[i].count << endl ;
		}
	}
	return 0 ;
}

