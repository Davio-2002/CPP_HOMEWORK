#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

int main(){

std::string s;
std::cin >> s;//tree

std::map<char,int> mp;//e:2 r:1 t:1

for(char x:s){
    ++mp[x];
}

std::vector<std::pair<char,int>> vec;//(e,2) (r,1) (t,1)

for(auto it:mp){
    vec.push_back(std::make_pair(it.first, it.second));
}

std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
});

for(auto it:vec){
    std::cout << std::string(it.second,it.first);
}
}