

#include "iostream"
#include "vector"
#include "algorithm"
#include "execution"
#include "utility"
#include "random"
#include "limits"
#include "stdexcept"
#include "thread"
#include "mutex"
#include "variant"

int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::cout << std::count_if(v.begin(), v.end(), [](int x)
                               { return x % 2 == 0; })
              << std::endl;

    auto ms = std::mismatch(v.begin(), v.end(), v.begin(), v.end());

    std::cout << *ms.first << " " << *ms.second << std::endl;

    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::vector<int>::iterator it = std::swap_ranges(vec.begin(), vec.end(), vec.begin());

    std::cout << *it << std::endl;

    auto res = std::all_of(vec.begin(), vec.end(), [](int x)
                           { return x % 2 == 0; });

    std::fill_n(vec.begin(), vec.size(), 0);

    for (auto &i : vec)
    {
        std::cout << i << std::endl;
    };

    std::fill(vec.begin(), vec.end(), 0);

    for (auto &i : vec)
    {
        std::cout << i << std::endl;
    };
}

/*
int main()
{
    std::variant<int, std::string> v ;
    v =  "this is a string";
    v = 8;

    std::cout << std::get<std::string>(v)  << std::endl;
    std::cout << std::get<int>(v) << std::endl;


}

class PtrDeleter
{
public:
    template <typename T>
    void operator()(T *ptr)
    {
        std::cout << ptr << " :: " << *ptr << " :: deleted" << std::endl;
        // delete ptr;
    }
};

int main()
{
    std::unique_ptr<int, PtrDeleter> ptr(new int(10));
    std::shared_ptr<int> ptr2(ptr.release());

    std::cout << ptr << std::endl;

    int* p = new int(10);

    // prints the value of address : 0x13a6060e0
    const char *address = reinterpret_cast<const char *>(*p);

    std::cout << "address : " << address << std::endl;

}

template <typename T>
T Sum(T arg)
{
    return arg;
}

template <typename T, typename... Args>
T Sum(T a, Args... args)
{
    return a + Sum(args...);
}

int main()
{
    std::cout << Sum<double,double>(1.2f, 2, 3,4.3f);
}

void print(const int a...)
{
    va_list args;
    va_start(args, a);

    while (true)
    {
        int arg = va_arg(args, int);
        if (arg == 0)
            break;
        std::cout << arg << std::endl;
    }
    va_end(args);
}

int main()
{
    print(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
}


template<typename T>
bool equal(const T &a, const T &b)
{
    return a == b;
}

int main()
{
    std::cout << (equal<int>(1, 2) ? "true" : "false") << std::endl;
}

int main()
{
    std::initializer_list<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> data_vector{1,2,3,4,5};
}

class Collection
{
public:
    Collection() {}
    ~Collection()
    {
        delete this;
    }

    int &operator[](std::size_t index)
    {
        return this->data[index];
    }

    const int &operator[](std::size_t index) const
    {
        return this->data[index];
    }

private:
    std::unique_ptr<int[]> data = std::make_unique<int[]>(10);
};

int main()
{
    Collection collection;
    collection[0] = 10;
    collection[6] = 16;

    // if we use int* data then at index 8 we will get garbage value = 0 but now after using unqie ptr this leak if fixed
    std::cout << collection[6] << collection[8] << std::endl;
}

std::mutex mtx;

void print_block(int n, char c) {
    // critical section
    mtx.lock();
    for (int i = 0; i < n; i++) {
        std::cout << c;
    }
    std::cout << std::endl;
    mtx.unlock();
}

int main() {
    std::thread t1(print_block, 50, '*');
    std::thread t2(print_block, 50, '$');

    t1.join();
    t2.join();

    return 0;
}



std::mutex m;

void f()
{
    std::cout << "Hello" << std::endl;
}

void bad()
{
    m.lock();
    f();
    m.unlock();
}

void good()
{
    std::lock_guard<std::mutex> lock(m);
    f();
}

int main()
{
    bad();
    good();
}



class Vector
{
public:
    int x, y, z;

    Vector()
    {
        x = 1;
        y = 2;
        z = 3;
    }

    std::ostream& operator << (std::ostream &t) const
    {
        out << this->x << " " << this->y << " " << this->z;
        return out;
    }
};

int main()
{
    Vector v;
}

class UDT
{
    public:
    UDT()
    {
        std::cout << "Constructor" << std::endl;
    }
    ~UDT()
    {
        std::cout << "Destructor" << std::endl;
    }
    void print_udt()
    {
        std::cout << "Print" << std::endl;
    }
};

struct UDT_S : UDT{
    UDT_S() {
        std::cout << "Constructor" << std::endl;
    }
    ~UDT_S() {
        std::cout << "Destructor" << std::endl;
    }
    void print() {
        std::cout << "Print" << std::endl;
    }
};

int main()
{
    std::shared_ptr<UDT> _udt = std::make_shared<UDT>();
    {
        std::weak_ptr<UDT> __udt = _udt;
        std::cout << __udt.use_count() << std::endl;
    }
    std::cout << _udt.use_count() << std::endl;

    UDT_S _udt_s = UDT_S();

    _udt_s.~UDT_S();

    _udt_s.print();

}


int main()
{
    int i = 9;

    const float i_f = static_cast<const float>(i);

    const char* const ch = "hello";

    char* m_ch = const_cast<char*>(ch);

    int *j = new int(10);

    int* p = &(*(j + 2));

    std::cout << p << std::endl;

    int &z = i;

    std::cout << z << std::endl;

    z = 10;

    std::cout << z << std::endl;


}


class Animal;
class Dog
{
    Animal* _animal;

    Dog &operator=(const Dog &other)
    {
        if (this == &other)
        {
            return *this;
        }
        delete _animal;

        _animal = new Animal(*other._animal);

        return *this;
    }
};

int main()
{
    Dog d;
    return 0;
}


class Dog
{
public:
    Dog()
    {
        std::cout << "From Dog Constructor" << std::endl;
    }
    virtual void bark()
    {
        std::cout << "Barking of dog class" << std::endl;
    }
    void pleaseBark()
    {
        this->bark();
    }
};

class Golden : public Dog
{
public:
    Golden()
    {
        std::cout << "Golden Constructor" << std::endl;
    }

    void bark()
    {
        std::cout << "Barking of Golden class" << std::endl;
    }
};

int main()
{
    Golden g;
    g.pleaseBark();
    return 0;
}

*/