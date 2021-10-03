#include <iostream>
#include "net.hpp"

int main()
{
    net n;

    n.Get("https://www.google.com");

    std::cout<<n.GetData()<<std::endl;

    return 0;
}