#include <iostream>
#include <queue>

int main()
{
    int n;
    std::cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; ++i)
    {
        std::cin >> arr[i];
    }
    std::priority_queue<int> q;
    for (int i = 0; i < n; ++i)
    {
        q.push(arr[i]);
    }

    int k;
    std::cin >> k;
    while (k > 0)
    {
        int x = q.top();
        x -= q.top() / 2;
        q.pop();
        q.push(x);
        --k;
    }

    int sum = 0;
    while (!q.empty())
    {
        sum += q.top();
        q.pop();
    }

    std::cout << sum;
}