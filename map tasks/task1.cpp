#include <iostream>
#include <map>
#include <string>

int main(){
std::string s;
std::cin >> s;

std::map<char,int> mp;
for(char x:s){
    ++mp[x];
}

int index = 0;
bool isunique = false;
for(char x:s){
    if(mp[x] == 1){
        isunique = true;
        break;
    }
    ++index;
}
if(isunique){
    std::cout << index << std::endl;
}
else{
    std::cout << -1 << std::endl;
}

}