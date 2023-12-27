#include <iostream>
#include <vector>
#include <cmath>

template <typename T>
class PriorityQueue
{
private:
    std::vector<T> heap;

public:
    template <typename InputIt>
    PriorityQueue(InputIt first, InputIt last)
    {
        while (first != last)
        {
            heap.push(*first);
            ++first;
        }
        for (int index = heap.size() / 2 - 1; index >= 0; --index)
        {
            int child = 2 * index + 1;
            if (child + 1 < heap.size() && heap[child + 1] > heap[child])
            {
                ++child;
            }
            if (heap[child] > heap[index])
            {
                std::swap(heap[index], heap[child]);
            }
        }
    }

    PriorityQueue() = default;

    bool empty() const
    { // O(1)
        if (size() == 0)
        {
            return true;
        }
        return false;
    }

    size_t size() const
    { // O(1)
        return heap.size();
    }

    void push(const T &value)
    { // O(log(N))
        heap.push_back(value);
        int index = heap.size() - 1;
        while (index > 0 && heap[(index - 1) / 2] < value)
        {
            std::swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    void pop()
    { 
        if (empty())
        {
            return;
        }

        std::swap(heap[0], heap[size() - 1]);
        heap.pop_back();
        int index = 0;

        while (2 * index + 1 < size())
        {
            int largestChild = 2 * index + 1;

            if (largestChild + 1 < size() && heap[largestChild + 1] > heap[largestChild])
            {
                largestChild = largestChild + 1;
            }

            if (heap[largestChild] > heap[index])
            {
                std::swap(heap[index], heap[largestChild]);
                index = largestChild;
            }
            else
            {
                break;
            }
        }
    }

    const T &top() const
    { 
        if (empty())
        {
            throw std::out_of_range("PriorityQueue is empty");
        }
        return heap[0];
    }
};

struct Point
{
    int x{};
    int y{};

    double dist() const
    {
        return std::sqrt(x * x + y * y);
    }

    friend bool operator<(const Point &lhs, const Point &rhs)
    {
        if (lhs.dist() < rhs.dist())
        {
            return true;
        }
        return false;
    }
};

int main()
{
    PriorityQueue<Point> pq;
    int n, k;
    std::cin >> n;
    std::cin >> k;
    int count = k;
    while (count > 0)
    {
        int x, y;
        std::cin >> x >> y;
        Point p{x, y};
        pq.push(p);
        --count;
    }

    for (int i = k + 1; i <= n; ++i)
    {
        int x, y;
        std::cin >> x >> y;
        Point p{x, y};
        if (p < pq.top())
        {
            pq.pop();
            pq.push(p);
        }
    }

    while (!pq.empty())
    {
        std::cout << "[" << pq.top().x << ", " << pq.top().y << "] ";
        pq.pop();
    }
}