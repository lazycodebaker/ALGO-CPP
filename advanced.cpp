
#include "iostream"
#include "vector"

/*
class Dog
{
    int age;

public:
    Dog(int age) : age(age) {}

    const int* getAge() { return &this->age; }
};

class BigArray {
    std::vector<int> data = std::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int counter;

public:
    BigArray(int counter = 0) : counter(counter) {}

    BigArray(BigArray& otherBigArray) = delete;

    BigArray& operator=(const BigArray& other) {
        if (this != &other) {
            data = other.data;
            counter = other.counter;
        }
        return *this;
    }

    ~BigArray() {}
    int getItem(int index) const {
        // counter++; // since now i made the function const , it cant change the counter value

        // a fix ::
        const_cast<BigArray*>(this)->counter++;
        return data[index];
    }

    int getCounter() {
        return counter;
    }
};


int main() {

    // const int a  = 10;
    //  a = 3; // error : assignment of read-only variable

    // int const b = 20;
    // b = 30; // error :expression must be a modifiable lvalue

    // const int *c = 10; // a value of type "int" cannot be used to initialize an entity of type "const int *

    // int* c = new int(10);
    // *c = 10;
    // std::cout << *c << std::endl;

    // const int i = 9;

    // int i = 9; value will be changed un const_cast
    // const_cast<int&> (i) = 10;
    // std::cout << i << "value is 9 " << std::endl;

    /*
    Dog* dog = new Dog(10);
    const int* age = dog->getAge();

    // *age = 12; error : on const int ...

    const int* _age = dog->getAge();

    std::cout << *_age << std::endl;
    */

/*
    BigArray* bigArray = new BigArray();

    bigArray->getItem(0);
    bigArray->getItem(0);
    bigArray->getItem(0);
    bigArray->getItem(0);
    bigArray->getItem(0);
    bigArray->getItem(0);

    std::cout << "Counter value " << bigArray->getCounter() << std::endl;

    BigArray* _bigArray = new BigArray(100);

    std::cout << "Counter value " << _bigArray->getCounter() << std::endl;

    bigArray = _bigArray;

    delete bigArray;

    std::cout << "Counter value " << bigArray->getCounter() << std::endl; // 0

    BigArray* __bigArray = new BigArray(_bigArray);


    return EXIT_SUCCESS;
}
*/