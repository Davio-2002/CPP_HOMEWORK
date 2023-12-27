#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>

int main(){
std::string pattern;
std::string s;
std::vector<std::string> words;//[dog,cat,dog,cat]

std::getline(std::cin,pattern);//pattern = abba
std::getline(std::cin, s);

std::istringstream iss(s);
std::string word;

while(iss >> word){
    words.push_back(word);
}

std::map<char,std::string> mp;//a:dog b:cat
int index = 0;
for(char x:pattern){
    mp.insert({x,words[index]});
    ++index;
}

bool tmp = false;
for(int i = 0;i<words.size();++i){
    if(mp.find(pattern[i])->second == words[i]){
        tmp = true;
    }
    else{
        tmp = false;
        break;
    }
}
if(tmp){
    std::cout << "True";
}
else{
    std::cout << "False";
}

}