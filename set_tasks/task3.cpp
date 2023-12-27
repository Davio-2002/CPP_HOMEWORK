#include <iostream>
#include <set>

int main()
{

    std::string s;
    std::cin >> s;

    int right = 0;
    int left = 0;
    int maxLen = 0;
    int lenofsubstring = 0;
    std::set<char> st;

    while (right < s.size())
    {
        if (lenofsubstring > maxLen)
        {
            maxLen = lenofsubstring;
        }
        if (st.find(s[right]) != st.end())
        {
            st.erase(s[left]);
            ++left;
            lenofsubstring = 0;
        }
        else
        {
            st.insert(s[right]);
            ++right;
            ++lenofsubstring;
        }
    }
    if (lenofsubstring > maxLen)
    {
        maxLen = lenofsubstring;
    }
    std::cout << maxLen << std::endl;
}