#include <iostream>
#include <map>
#include <string>

int main() {
    std::string s;
    std::cin >> s;

    std::map<char, int> mp;
    for (char x : s) {
        ++mp[x];
    }

    int res = 0;
    bool oddchar = false;
    for (auto it : mp) {
        res += (it.second / 2) * 2;
        if (it.second % 2 == 1) {
            oddchar = true;
        }
    }
    if (oddchar) {
        res += 1;
    }
    std::cout << res;
}