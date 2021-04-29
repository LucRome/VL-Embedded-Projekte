// VariadicTemplateTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define PRINT_AS_WARNING(constant) char(_<constant>())

#include <iostream>

// factorial

template<int N>
struct factorial {
public:

    factorial<N - 1> minus1;

    int prod;

    constexpr factorial()
        :prod(N* minus1.prod)
    {
    }   
};

template<>
struct factorial<0> {
    int prod = 1;
};

// put N%10 for each N -> 0 into buffer
template <char N>
constexpr void fillBuffer(char* ptr) {
    *ptr = N % 10 + '0';
    *(++ptr) = ';';
    fillBuffer<N - 1>(ptr);
}

template<>
constexpr void fillBuffer<0>(char* ptr) {
    *ptr = '0';
    *(++ptr) = '\0';
}


template <char N>
struct numbuf {
    char buf[N * 2] = { 0 };
public:
    constexpr numbuf() {
        fillBuffer<N>(buf);
    }

    const char* getBuf() const {
        return buf;
    }
};


int main()
{
    constexpr factorial<10> fac;
    constexpr int f = fac.prod;

    std::cout << f << std::endl;

    constexpr numbuf<20> nb;
    printf("\nnumbuffer: %s\n", nb.getBuf());
}
