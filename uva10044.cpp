/*Reference 寂靜山林*/
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<map>
using namespace std ;
struct erdos_number{
	string name ;
	int number ;
};
vector<erdos_number> erdos ; 
vector<string> author ;
map<string, int> exist ; 
vector<bool> processed ;
int find_index(string &name){
	map<string, int>::iterator it = exist.find(name) ;
	if(it != exist.end()) return (*it).second ;
	return -1 ;
}
vector<string> extract_name(string &line){
	vector<string> list ;
	string::size_type begin(0) ;
	string::size_type end = line.find(".,",begin) ;
	
	while(end!=string::npos){
		list.push_back(line.substr(begin,end-begin+1)) ;
		begin = end + 3 ;
		end = line.find(".,",begin) ;
	}
	if(begin<line.length()-1) list.push_back(line.substr(begin)) ;
	return list ;
}
void set_erdos_number(string &author, int number){
	vector<string> list = extract_name(author) ;

	for(int i=0 ; i<list.size() ; ++i){
		if(find_index(list[i])<0){
			erdos_number tmp ;
			tmp.name = list[i] ; 
			tmp.number = number+1 ;
			erdos.push_back(tmp) ;
			exist.insert(make_pair<string,int>(list[i],erdos.size()-1)) ;
		}
	}
}

void cal_erdos_number(){
	int begin = 0, end = 0 ;
	erdos.clear() ;
	erdos_number tmp ;
	tmp.name = "Erdos, P.";
	tmp.number = 0;
	erdos.push_back(tmp) ;

	exist.clear() ;
	exist.insert(make_pair<string,int>("Erdos, P.",0)) ;
	processed.clear() ;
	processed.resize(author.size());
	fill(processed.begin(),processed.end(),false) ;
	while(1){
		for(int i=0 ; i<author.size() ; ++i){
			if(processed[i]) continue ;
			for(int j=begin ; j<=end ; ++j){
				if(author[i].find(erdos[j].name)!=string::npos){
					set_erdos_number(author[i],erdos[j].number) ;
					processed[i] = true ;
					break ;
				}
			}
		}

		if(end==erdos.size()-1) return ; 
		else{
			begin = end+1 ;
			end = erdos.size()-1 ;
		}
	}
}
int main(){
	string line ;	
	int scenario ; 
	int p ; 
	int n ;
	cin >> scenario ; 
	for(int i=1 ; i<=scenario ; ++i){
		cin >> p >> n; 
		cin.ignore() ;

		author.clear() ;
		for(int j=0 ; j<p ; ++j){
			getline(cin,line) ;
			author.push_back(line.substr(0,line.find_first_of(":"))) ;
		}
		cal_erdos_number() ;
		cout << "Scenario " << i << endl ;
		for(int j=0 ; j<n ; ++j){
			getline(cin,line) ;
			cout << line << " " ; 
			int pos = find_index(line) ;
			if(pos>=0) cout << erdos[pos].number << endl ;
			else cout << "infinity" << endl ;
		}
	}
	return 0 ;
}
