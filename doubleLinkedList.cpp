#include <iostream>
#include <algorithm>

template<typename T>
class List {
public:
    struct Node {
        T data;
        Node *next;
        Node *prev;
    };

    Node *head;
    Node *tail;
    size_t size_;

public:
    class iterator {
    public:
        Node *current;
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;

        iterator() : current(nullptr) {}
        explicit iterator(Node *node) : current(node) {}
        reference operator*() const { return current->data; }
        pointer operator->() const { return &(current->data); }
        iterator &operator++() {
            current = current->next;
            return *this;
        }
        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }
        iterator &operator--() {
            current = current->prev;
            return *this;
        }
        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }
        friend bool operator==(iterator lhs, iterator rhs) {
            return lhs.current == rhs.current;
        }
        friend bool operator!=(iterator lhs, iterator rhs) {
            return lhs.current != rhs.current;
        }
    };

    List() : head(nullptr), tail(nullptr), size_(0) {}
    List(size_t count, const T &value = T()) : head(nullptr), tail(nullptr), size_(0) {
        for (size_t i = 0; i < count; ++i) {
            push_back(value);
        }
    }
    List(const List &other) : head(nullptr), tail(nullptr), size_(0) {
        for (T &value : other) {
            push_back(value);
        }
    }
    explicit List(List &&other) : head(other.head), tail(other.tail), size_(other.size_) {
        other.head = nullptr;
        other.tail = nullptr;
        other.size_ = 0;
    }
    List(std::initializer_list<T> ilist) : head(nullptr), tail(nullptr), size_(0) {
        for (const T &value : ilist) {
            push_back(value);
        }
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    ~List() {
        clear();
    }

    List &operator=(const List &other) {
        if (this != &other) {
            List temp(other);
            std::swap(head, temp.head);
            std::swap(tail, temp.tail);
            std::swap(size_, temp.size_);
        }
        return *this;
    }
    List &operator=(List &&other) {
        if (this != &other) {
            clear();
            std::swap(head, other.head);
            std::swap(tail, other.tail);
            std::swap(size_, other.size_);
        }
        return *this;
    }
    List &operator=(std::initializer_list<T> ilist) {
        clear();
        for (const T &value : ilist) {
            push_back(value);
        }
        return *this;
    }

    T &front() { return head->data; }
    const T &front() const { return head->data; }
    T &back() { return tail->data; }
    const T &back() const { return tail->data; }

    bool empty() const { return size_ == 0; }
    std::size_t size() const { return size_; }

    iterator insert(iterator pos, const T &value) {
        Node *node = new Node{value, nullptr, nullptr};
        if (pos.current == nullptr) {
            push_back(value);
            return iterator(tail);
        }
        node->next = pos.current;
        node->prev = pos.current->prev;
        if (pos.current->prev != nullptr) {
            pos.current->prev->next = node;
        } else {
            head = node;
        }
        pos.current->prev = node;
        ++size_;
        return iterator(node);
    }
    iterator insert(iterator pos, T &&value) {
        Node *node = new Node{std::move(value), nullptr, nullptr};
        if (pos.current == nullptr) {
            push_back(std::move(value));
            return iterator(tail);
        }
        node->next = pos.current;
        node->prev = pos.current->prev;
        if (pos.current->prev != nullptr) {
            pos.current->prev->next = node;
        } else {
            head = node;
        }
        pos.current->prev = node;
        ++size_;
        return iterator(node);
    }
    iterator insert(iterator pos, std::initializer_list<T> ilist) {
        for (const T &value : ilist) {
            pos = insert(pos, value);
            ++pos;
        }
        return pos;
    }

    iterator erase(iterator pos) {
        if (pos.current == nullptr) {
            return pos;
        }
        Node *node = pos.current;
        iterator next(node->next);
        if (node->prev != nullptr) {
            node->prev->next = node->next;
        } else {
            head = node->next;
        }
        if (node->next != nullptr) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev;
        }
        delete node;
        --size_;
        return next;
    }
    iterator erase(iterator first, iterator last) {
        while (first != last) {
            first = erase(first);
        }
        return last;
    }

    void push_front(const T &value) {
        Node *node = new Node{value, head, nullptr};
        if (head != nullptr) {
            head->prev = node;
        } else {
            tail = node;
        }
        head = node;
        ++size_;
    }
    void push_front(T &&value) {
        Node *node = new Node{std::move(value), head, nullptr};
        if (head != nullptr) {
            head->prev = node;
        } else {
            tail = node;
        }
        head = node;
        ++size_;
    }
    void push_back(const T &value) {
        Node *node = new Node{value, nullptr, tail};
        if (tail != nullptr) {
            tail->next = node;
        } else {
            head = node;
        }
        tail = node;
        ++size_;
    }
    void push_back(T &&value) {
        Node *node = new Node{std::move(value), nullptr, tail};
        if (tail != nullptr) {
            tail->next = node;
        } else {
            head = node;
        }
        tail = node;
        ++size_;
    }

    void pop_front() {
        if (head == nullptr) {
            return;
        }
        Node *node = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete node;
        --size_;
    }

    void splice(iterator pos, List& other) {
        if (other.empty()) {
            return;
        }
        if (this == &other) {
            return;
        }
        Node* first = other.head;
        Node* last = other.tail;
        if (pos.current == nullptr) {
            if (tail != nullptr) {
                tail->next = first;
            } else {
                head = first;
            }
            first->prev = tail;
            tail = last;
        } else {
            Node* prevNode = pos.current->prev;
            if (prevNode != nullptr) {
                prevNode->next = first;
            } else {
                head = first;
            }
            first->prev = prevNode;
            pos.current->prev = last;
            last->next = pos.current;
        }
        size_ += other.size_;
        other.head = nullptr;
        other.tail = nullptr;
        other.size_ = 0;
    }

    void pop_back() {
        if (tail == nullptr) {
            return;
        }
        Node *node = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete node;
        --size_;
    }

    iterator begin() const { return iterator(head); }
    iterator end() const { return iterator(nullptr); }

    friend bool operator==(const List<T> &lhs, const List<T> &rhs) {
        if (lhs.size() != rhs.size()) {
            return false;
        }
        auto it1 = lhs.begin();
        auto it2 = rhs.begin();
        while (it1 != lhs.end()) {
            if (*it1 != *it2) {
                return false;
            }
            ++it1;
            ++it2;
        }
        return true;
    }

};

//task 1
template<typename T>
void partitionLinkedList(List<T>& list, const T& x) {
    List<T> less;
    List<T> greaterOrEqual;
    List<T> single{ x };


    for (auto it = list.begin(); it != list.end();) {
        auto next = it;
        ++next;
        if ( *it != x )
        {
            if (*it < x ) {
                less.push_back(*it);
            } else {
                greaterOrEqual.push_back(*it);
            }
        }

        list.erase(it);
        it = next;
    }

    less.splice(less.end(), single);
    less.splice(single.begin(), greaterOrEqual);
    list = less;
}

void minorsToCapitals(List<char>& list)
{
    auto it = list.begin();
    auto it2 = list.begin();
    bool mut = false;
    char last_char = '\0';

    while (true) {
        if (it == list.end() && mut) {
            it = list.erase(it2, it);
            list.insert(it, static_cast<char>(last_char - ('a' - 'A')));
            break;
        }

        if (it == list.end()) {
            break;
        }

        if (*it != last_char) {
            if (mut) {
                it = list.erase(it2, it);
                list.insert(it, static_cast<char>(last_char - ('a' - 'A')));
                it2 = it;
                mut = false;
            } else {
                it2 = it;
            }
        }

        if (*it == last_char) {
            mut = true;
        }

        last_char = *it;
        ++it;
    }

}

int main()
{
    List<int> list { 6, -2, 5, 4, 0, 3 };
    partitionLinkedList(list, 4);

    for (const auto& value : list) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    List<char> chList { 'a', 'a', 'b', 'c', 'c', 'c' };
    minorsToCapitals(chList);

    for ( auto it = chList.begin(); it != chList.end(); ++it)
    {
        std::cout << *it << " ";
    }

    return 0;
}