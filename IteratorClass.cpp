#include "iostream"

template <class T>
class Ring
{
public:
    class iterator;
    Ring(size_t size) : m_pos(0), m_size(size), m_values(NULL)
    {
        m_values = new T[size];
    };

    ~Ring()
    {
        delete[] m_values;
    };

    int size()
    {
        return m_size;
    };

    iterator begin()
    {
        return iterator(0, *this);
    };

    iterator end()
    {
        return iterator(m_size, *this);
    };

    void add(T value)
    {
        m_values[m_pos++] = value;

        if (m_pos == m_size)
        {
            m_pos = 0;
        };
    };

    T &get(int pos)
    {
        return m_values[pos];
    };

private:
    int m_pos, m_size;
    T *m_values;
};

template <class T>
class Ring<T>::iterator
{
private:
    int m_pos;
    Ring<T> &m_ring;

public:
    iterator(int pos, Ring &a_ring) : m_pos(pos), m_ring(a_ring){};

    iterator &operator++(int)
    {
        m_pos++;
        return *this;
    };

    T &operator*()
    {
        return m_ring.get(m_pos);
    };

    bool operator!=(const iterator &other) const
    {
        return m_pos != other.m_pos;
    };
};

int main()
{
    Ring<int> r(5);

    r.add(1);
    r.add(2);
    r.add(3);
    r.add(4);
    r.add(5);

    for (Ring<int>::iterator it = r.begin(); it != r.end(); it++)
    {
        std::cout << *it << std::endl;
    };

    return EXIT_SUCCESS;
}