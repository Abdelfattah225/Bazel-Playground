// main.cpp
#include <iostream>
#include "cal.hpp"

int main() {
    Calculator calc;
    
    std::cout << "5 + 3 = " << calc.add(5, 3) << std::endl;
    std::cout << "5 - 3 = " << calc.subtract(5, 3) << std::endl;
    std::cout << "5 * 3 = " << calc.multiply(5, 3) << std::endl;
    
    return 0;
}