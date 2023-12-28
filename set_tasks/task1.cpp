#include <iostream>
#include <set>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> v[i];
    }
    std::set<int> st;
    for (int i : v)
    {
        st.insert(i);
    }
    std::cout << st.size();
}