#include <iostream>
#include <memory>

template <class T>
class Ring
{
public:
    class iterator;
    Ring(size_t size) : m_pos(0), m_size(size), m_values(std::make_unique<T[]>(size)) {}

    int size() const noexcept { return m_size; }

    iterator begin() const noexcept { return iterator(0, *this); }

    iterator end() const noexcept { return iterator(m_size, *this); }

    void add(T value) noexcept
    {
        m_values[m_pos++] = std::move(value);
        if (m_pos == m_size)
            m_pos = 0;
    }

    const T &get(int pos) const noexcept { return m_values[pos]; }

private:
    int m_pos, m_size;
    std::unique_ptr<T[]> m_values;
};

template <class T>
class Ring<T>::iterator
{
private:
    int m_pos;
    const Ring<T> &m_ring;

public:
    iterator(int pos, const Ring<T> &a_ring) noexcept : m_pos(pos), m_ring(a_ring) {}

    iterator &operator++() noexcept
    {
        ++m_pos;
        return *this;
    }

    iterator operator++(int) noexcept
    {
        iterator temp = *this;
        ++(*this);
        return temp;
    }

    const T &operator*() const noexcept { return m_ring.get(m_pos); }

    bool operator!=(const iterator &other) const noexcept { return m_pos != other.m_pos; }
};

int main()
{
    constexpr size_t RingSize = 5;
    Ring<int> r(RingSize);

    r.add(1);
    r.add(2);
    r.add(3);
    r.add(4);
    r.add(5);

    // Using range-based for loop for iteration
    for (const auto &element : r)
    {
        std::cout << element << std::endl;
    };

    return EXIT_SUCCESS;
}
