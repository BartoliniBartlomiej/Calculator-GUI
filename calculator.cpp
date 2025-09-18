//
//  calculator.cpp
//  calculator
//
//  Created by Bartłomiej Kuś on 18/09/2025.
//

#include "calculator.hpp"

float Calculator::wynik()
{
    char _s;
    
    switch (_s) {
        case '+':
            return x + y;
            break;
        case '-':
            return x - y;
            break;
        case '*':
            return x * y;
            break;
        case '/':
            return x / y;
            break;
        default:
            break;
    }
}
