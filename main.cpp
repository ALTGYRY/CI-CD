#include "lib.h"
#include "somelib.h"
#include <iostream>

int main (int, char **) {
    std::cout << "build " << version() << "\n";
    std::cout << "Hello, World!\n";
    std::cout << Somelib::somefunc(1,2) << "\n";
    return 0;
}
//choto choto