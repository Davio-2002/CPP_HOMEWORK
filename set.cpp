#include <iostream>
#include <cassert>

template <typename T>
class Set
{
    struct Node
    {
        T value;
        Node *left;
        Node *right;
        Node *parent;

        int height{};
        int balanceFactor{};

        explicit Node(T value_) noexcept : value(value_), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node *root{};
    size_t size_{};

    void updateHeight(Node* node) noexcept
    {
        int leftHeight = (node->left != nullptr) ? node->left->height : -1;
        int reightheight = (node->right != nullptr) ? node->right->height : -1;
        node->height = 1 + std::max(leftHeight, reightheight);
    }

    int getBalanceFactor(Node* node) noexcept
    {
        int leftHeight = (node->left != nullptr) ? node->left->height : -1;
        int reightheight = (node->right != nullptr) ? node->right->height : -1;
        return (leftHeight - reightheight);
    }

    void updateBalanceFactor(Node* node) noexcept
    {
        node->balanceFactor = getBalanceFactor(node);
    }

    void insert_recursively(Node *&current, const T &value) noexcept
    {
        if (!current)
        {
            current = new Node(value);
            ++size_;
            return;
        }

        if (value < current->value)
        {
            insert_recursively(current->left, value);
            current->left->parent = current;
        }
        else if (value >= current->value && current->value >= value)
        {
            return;
        }
        else
        {
            insert_recursively(current->right, value);
            current->right->parent = current;
        }

        updateHeight(current);
        updateBalanceFactor(current);
    }

    void inorder_traversal(Node *node) noexcept
    {
        if (node != nullptr)
        {
            inorder_traversal(node->left);
            std::cout << node->value << " ";
            inorder_traversal(node->right);
        }
    }

public:
    void insert(const T &value)
    {
        insert_recursively(root, value);
    };

    void print_inorder()
    {
        inorder_traversal(root);
        std::cout << "\n";
    };

    struct iterator
    {
    public:
        Node *current;

        using value_type = T;
        using reference = T &;
        using pointer = T *;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        explicit iterator() noexcept : iterator(nullptr) {}

        explicit iterator(Node *node) noexcept : current(node) {}

        auto findSuccessor(Node *node) -> Node *
        {
            if (node == nullptr)
                return nullptr;

            if (node->right != nullptr)
            {
                Node *successor = node->right;
                while (successor->left != nullptr)
                {
                    successor = successor->left;
                }
                return successor;
            }
            else
            {
                Node *ancestor = node->parent;
                Node *presentNode = node;

                while (ancestor != nullptr && current == ancestor->right)
                {
                    current = ancestor;
                    ancestor = ancestor->parent;
                }
                return ancestor;
            }
        }

        reference operator*() const
        {
            return current->value;
        }

        pointer operator->() const
        {
            return &(current->value);
        }

        iterator &operator++()
        {
            current = findSuccessor(current);
            return (*this);
        }

        iterator operator++(int)
        {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        friend bool operator==(iterator lhs, iterator rhs)
        {
            return lhs.current == rhs.current;
        }

        friend bool operator!=(iterator lhs, iterator rhs)
        {
            return lhs.current != rhs.current;
        }
    };

    iterator begin()
    {
        if (!root)
        {
            return iterator(nullptr);
        }

        auto current = root;
        while (current->left)
            current = current->left;

        return iterator(current);
    }

    iterator end()
    {
        return iterator(nullptr);
    }

    iterator find(const T &value)
    {
        auto current = root;
        while (current)
        {
            if (value < current->value)
            {
                current = current->left;
            }
            else if (value >= current->value && current->value >= value)
            {
                return iterator(current);
            }
            else
            {
                current = current->right;
            }
        }
        return end();
    }

    void erase(iterator pos)
    {
        auto toBeErased = pos.current;
        if (toBeErased == nullptr)
            return;

        if (toBeErased->left == nullptr && toBeErased->right == nullptr)
        {
            if (toBeErased->parent != nullptr)
            {
                if (toBeErased->parent->left == toBeErased)
                {
                    toBeErased->parent->left = nullptr;
                }
                else
                {
                    toBeErased->parent->right = nullptr;
                }
            }
            else
            {
                root = nullptr;
            }
            delete toBeErased;
            --size_;
            return;
        }

        if (toBeErased->left == nullptr || toBeErased->right == nullptr)
        {
            auto child = (toBeErased->left != nullptr) ? toBeErased->left : toBeErased->right;
            if (toBeErased->parent != nullptr)
            {
                if (toBeErased == toBeErased->parent->left)
                {
                    toBeErased->parent->left = child;
                }
                else
                {
                    toBeErased->parent->right = child;
                }
                child->parent = toBeErased->parent;
            }
            else
            {
                root = child;
                child->parent = nullptr;
            }
            delete toBeErased;
            --size_;
            return;
        }

        Node *successor = pos.findSuccessor(toBeErased);
        toBeErased->value = successor->value;
        erase(iterator(successor));

        updateHeight(toBeErased);
        updateBalanceFactor(toBeErased);
    }

    ~Set()
    {
        while (root != nullptr)
        {
            erase(iterator(root));
        }
    }
};

int main()
{
    // First task
    Set<int> st;
    st.insert(10);
    st.insert(-10);
    st.insert(20);
    st.insert(10);
    st.insert(0);
    st.print_inorder(); // Output: -10 0 10 20

    // Second task
    for (auto x : st)
    {
        std::cout << x << ' ';
    } // Output: -10 0 10 20
    std::cout << std::endl;

    auto it = st.find(10);
    std::cout << *it << std::endl; // Output: 10

    assert(st.find(-20) == st.end());

    // Third task
    Set<int> set;
    set.insert(1);
    set.insert(3);
    set.insert(5);
    set.insert(2);
    set.insert(4);

    auto sit = set.find(3);
    set.erase(sit);

    for (auto x : set)
    {
        std::cout << x << ' ';
    } // Output: 1 2 3 4 5

    assert(set.find(3) == set.end());

    return 0;
}
