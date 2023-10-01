#include <iostream>
#include <climits>


template <typename T>
class Vector {
private:
    T* data;
    std::size_t capacity{};
    std::size_t size{};

public:
    Vector( ) : capacity{0}, size{0}, data{nullptr} {}

    Vector( std::size_t size_ ) : capacity{ size_ * 2 }, size{ size_ }
    {
        data = new T[ capacity ];
    }

    Vector(const std::initializer_list<T>& listOfElements) : capacity(listOfElements.size() * 2), size(listOfElements.size()) {
        data = new T[ capacity ];
        std::size_t i = 0;
        for (const T& element : listOfElements) {
            data[i++] = element;
        }
    }

    Vector( std::size_t size_, const T& init_element ) : capacity( size_ * 2 ), size( size_)
    {
        data = new T[ capacity ];
        for( std::size_t i = 0; i < size; ++i)
        {
            data[i] = init_element;
        }
    }

    Vector( const Vector<T>& other )
    {
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];

        for( std::size_t i = 0; i < this->size; ++i ) {
            data[i] = other.data[i];
        }
    }

    Vector( Vector<T>&& other ) noexcept
    {
        capacity = other.capacity;
        size = other.size;
        data = other.data;
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    Vector<T>& operator=( const Vector<T>& other )
    {
        if( this!= &other ) {
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];

            for( std::size_t i = 0; i < this->size; ++i ) {
                data[i] = other.data[i];
            }
        }

        return *this;
    }

    Vector<T>& operator=( Vector<T>&& other ) noexcept
    {
        if( this!= &other ) {
            capacity = other.capacity;
            size = other.size;
            data = other.data;
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    std::size_t getCapacity() const
    {
        return capacity;
    }

    std::size_t getSize() const
    {
        return size;
    }

    bool empty() const
    {
        if (this->size == 0) return true;
        return false;
    }

    const T &operator[](std::size_t index) const
    {
        return data[index];
    }

    T &operator[](std::size_t index)
    {
        return data[index];
    }

    const T& at( std::size_t  index) const
    {
        if (index >= this->size)
        {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    T& at( std::size_t  index)
    {
        if (index >= this->size)
        {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    void push_back(const T& element) {
        if (size == capacity) {
            capacity *= 2;
            T* temp = new T[capacity];
            for (std::size_t i = 0; i < size; ++i) {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
        }
        data[size++] = element;
    }

    void push_back(const T&& element) {
        if (size == capacity) {
            capacity *= 2;
            T* temp = new T[capacity];
            for (std::size_t i = 0; i < size; ++i) {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
        }
        data[size++] = std::move(element);
    }


    void pop_back() {
        if (size > 0) {
            --size;
        }
    }

    void clear() {
        size = 0;
    }

    ~Vector() {
        delete[] data;
    }
};

auto productNumsElements( const Vector< int >& nums )
{
    const std::size_t n = nums.getSize();
    Vector< int > result(n, 1);

    std::size_t leftProduct = 1;
    std::size_t rightProduct = 1;

    for( std::size_t i = 0; i < n; ++i )
    {
        result.at(i) *= leftProduct;
        leftProduct *= nums.at(i);
    }

    for (int i = n - 1; i >= 0; i--) {
        result[i] *= rightProduct;
        rightProduct *= nums[i];
    }

    return result;
}

auto findLuckyNumbers( const Vector<Vector< int >> matrix )
{
    Vector<int> result;

    std::size_t n = matrix.getSize();
    std::size_t m = matrix.at(0).getSize();

    Vector<int> rowMinimumElements(n, INT_MAX);
    Vector<int> colMaximumElements(m, INT_MIN);

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < m; ++j) {
            rowMinimumElements[i] = std::min(rowMinimumElements[i], matrix.at(i).at(j));
            colMaximumElements[j] = std::max(colMaximumElements[j], matrix.at(i).at(j));
        }
    }

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < m; ++j) {
            if (rowMinimumElements[i] == matrix.at(i).at(j) && colMaximumElements[j] == matrix.at(i).at(j)) {
                result.push_back(matrix.at(i).at(j));
            }
        }
    }

    return result;
}

int main()
{
    //First task
    Vector<int> v{};
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    auto newV = productNumsElements(v);

    for (int i = 0; i < newV.getSize(); ++i) {
        std::cout << newV[i] << " ";
    }

    std::cout << "\n";

    //Second task
    const Vector< Vector< int > > matrix {
                                    { 15, 7, 8 },
                                    { 9, 11, 13 },
                                    { 15, 16, 17 }
    };

    auto newV_2 = findLuckyNumbers( matrix );

    for(std::size_t i = 0; i < newV_2.getSize(); ++i)
    {
       std::cout << newV_2.at(i) << " ";
    }

    return 0;
}
