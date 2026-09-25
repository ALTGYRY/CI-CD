#include "lib.h"

#include <iostream>

int main (int, char **) {
    auto closure = [c = 100](int a,int b) {return c + a + b;};
    std::cout << closure(1,2) << "\n";

}
//choto choto