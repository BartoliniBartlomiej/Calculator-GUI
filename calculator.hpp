#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>

class Calculator
{
public:
    float x;
    float y;
    char sign;

    Calculator(float _x, float _y, char _sign) : x(_x), y(_y), sign(_sign) {};

    float wynik()
    {
        switch (sign) {
            case '+':
                return x + y;
            case '-':
                return x - y;
            case '*':
                return x * y;
            case '/':
                if (y != 0) return x / y;
                std::cerr << "Division by zero!" << std::endl;
                return 0; // lub throw
            default:
                std::cerr << "Unknown operator!" << std::endl;
                return 0;
        }
    }
};

#endif // CALCULATOR_H
