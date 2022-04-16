#include<bits/stdc++.h>

using namespace std;
//Dictionary for Production Rules
map<string,vector<string> > production;

//Recursive Function for deriving the non-terminal symbol
string rec;
vector<string> look;
vector<string> f_p;
string recurs(string s){
	for(int i=0;i<production[s].size();i++){
		if(production[s][i][0] >= 'A' and production[s][i][0] <= 'Z'){
			if((production[s][i][0] + production[s][i][1]) == (production[s][i][0] + '\'')){
				string r; r.push_back(production[s][i][0]); r.push_back(production[s][i][1]);
				(recurs(r));
			}else{
				string r; r.push_back(production[s][i][0]);
				(recurs(r));
			}
		}else{
			rec.push_back(production[s][i][0]);
		}
	}
	return rec;
}
map<string, string> firsts;
string first(string s){
	string ans = "";
	for(int i=0;i<production[s].size();i++){
		if(production[s][i][0] >= 'A' and production[s][i][0] <= 'Z'){
			if((production[s][i][0] + production[s][i][1]) == (production[s][i][0] + '\'')){
				string r; r.push_back(production[s][i][0]); r.push_back(production[s][i][1]);
				ans += (recurs(r));
			}else{
				string r; r.push_back(production[s][i][0]);
				ans += (recurs(r));
			}
		}else ans.push_back(production[s][i][0]);
	}
	firsts[s] = ans;
	cout<<"First("<<s<<")-> {";
	for(int i=0;i<ans.length();++i){
		cout<<ans[i];
		if(i!=ans.length()-1) cout<<",";
	}
	cout<<"}"<<endl;
	rec = "";
}

map<string,string > follows;

void follow(string s){
	for(map<string,vector<string> >::iterator it = production.begin();it!=production.end();it++){
		for(int i=0;i<it->second.size();i++){
			for(int j=0;j<it->second[i].length();j++){
				if(s.length()>1 and it->second[i][j]==s[0] and j!=it->second[i].length()-1 and it->second[i][j+1] == '\''){
					j++;
					if(j==it->second[i].length()-1) follows[s] += follows[it->first];
					else if(it->second[i][j+1] <='Z' and it->second[i][j+1]>='A'){
                        string temp; temp.push_back(it->second[i][j+1]);
                        if(it->second[i][j+2] == '\'') temp.push_back(it->second[i][j+2]);
                        follows[s] += firsts[temp];
                        follows[s] += follows[it->first];
					}else if(it->second[i][j+1] != NULL and it->second[i][j+1] != '\'') follows[s].push_back(it->second[i][j+1]);
				}
				else if(s.length()==1 and s[0] == it->second[i][j]){
                    if(j==it->second[i].length()-1) follows[s] += follows[it->first];
					else if(it->second[i][j+1] <='Z' and it->second[i][j+1]>='A'){
                        string temp; temp.push_back(it->second[i][j+1]);
                        if(it->second[i][j+2] == '\'') temp.push_back(it->second[i][j+2]);
                        follows[s] += firsts[temp];
                        follows[s] += follows[it->first];
					}else if(it->second[i][j+1] != NULL and it->second[i][j+1] != '\'') follows[s].push_back(it->second[i][j+1]);
				}
			}
		}
	}
}

//Generates Dictionary of Production Rules from user input
void generateProd(string &s){
	string non = "",term="";
	int i;
	for(i=0;i<s.length();++i){
		if(s[i]!='-'){
			non.push_back(s[i]);
		}else break;
	}
	i+=2;
	for(i=i;i<s.length();++i){
		if(s[i]=='|'){
			production[non].push_back(term);
			term="";
		}else term.push_back(s[i]);
	}
	production[non].push_back(term);
	look.push_back(non);

}

//Checks if the Production rule is non-left recursive/non-left factoring
bool isValid(){
	bool ret = true;
	string prev = "";
	for(map<string,vector<string> >::iterator it = production.begin();it!=production.end();it++){
		for(int i=0;i<it->second.size();++i){
			if(it->first[0] == it->second[i][0]){
				cout<<"Invalid Production-Left Recursion Occured : "<<it->first<<
				"->"<<it->second[i]<<endl;
				ret = false;
			}
			if(i>0 and it->second[i][0] == prev[0]){
				cout<<"Invalid Production-Left Factoring Occured : "<<it->first<<
				"->"<<prev<<"|"<<it->second[i]<<endl;
				ret = false;
			}
			prev = it->second[i];
		}
	}
	return ret;
}

void print(){
	cout<<"\n\nProduction Rules: "<<endl;
	for(map<string,vector<string> >::iterator it = production.begin();it!=production.end();it++){
		cout<<it->first<<"->";
		for(int i=0;i<it->second.size();i++){
			cout<<it->second[i];
			if(i!=it->second.size()-1) cout<<"|";
		}
		cout<<endl;
	}
	cout<<"\n\n"<<endl;
}

int main(int argc, char** argv) {
	cout<<"Enter Production Rule(Type 'end' at last to break):"<<endl;
	string s;
	while(cin>>s and s!="end"){
		generateProd(s);
	}
	print();

	if(!isValid()) return 0;

	for(map<string,vector<string> >::iterator it = production.begin();it!=production.end();it++){
		first(it->first);
	}
	//cout<<"Firsts: "<<endl;
	for(map<string,string >::iterator it = firsts.begin();it!=firsts.end();it++){
		//cout<<it->first<<"->"<<it->second<<endl;
	}
	//cout<<"Look"<<endl;
	for(int i=0;i<look.size();++i){
		//cout<<look[i]<<endl;
	}
	follows[look[0]]+="#";
	for(int i=0;i<look.size();++i){
		follow(look[i]);
	}
	map<string,set<char> > f;
	cout<<"\n\n\n"<<endl;
	for(map<string,string >::iterator it = follows.begin();it!=follows.end();it++){
		for(int i=0;i<it->second.length();i++){
            f[it->first].insert(it->second[i]);
		}
	}
	for(map<string,set<char> >::iterator it = f.begin();it!=f.end();it++){
        cout<<"Follow("<<it->first<<")->{";
        for(set<char>::iterator st = it->second.begin();st!=it->second.end();st++){
            if(st != it->second.begin()) cout<<",";
            cout<<*st;
        }
        cout<<"}"<<endl;
	}
	return 0;
}
