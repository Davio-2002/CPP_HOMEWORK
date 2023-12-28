#include <iostream>
#include <set>

int main()
{
    std::string jewels;
    std::string stones;

    std::cout << "Jewels:" << std::endl;
    std::cin >> jewels;

    std::cout << "Stones:" << std::endl;
    std::cin >> stones;

    std::set<char> st;
    for (char x : jewels)
    {
        st.insert(x);
    }

    int count = 0;
    for (char x : stones)
    {
        if (st.find(x) != st.end())
        {
            ++count;
        }
    }

    std::cout << count;
}