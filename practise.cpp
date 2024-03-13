
#include "iostream"
#include "vector"
#include "algorithm"
#include "execution"
#include "utility"
#include "random"
#include "limits"
#include "stdexcept"

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
    void print()
    {
        std::cout << "Print" << std::endl;
    }
};

int main()
{
    std::shared_ptr<UDT> _udt = std::make_shared<UDT>(); 
    {
        std::shared_ptr<UDT> __udt = _udt;
        std::cout << __udt.use_count() << std::endl;
    } 
    std::cout << _udt.use_count() << std::endl;
}

/*
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