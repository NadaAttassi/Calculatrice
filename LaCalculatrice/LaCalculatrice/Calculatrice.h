#pragma once

#include "Pile.h"
#include <string>
#include <stack>
#include <stdexcept>
#include <cmath>

class Calculatrice {
public:
    double evaluate(const std::string& expression);

private:
  
    void applyOperator(std::stack<double>& values, std::stack<char>& ops);
    bool isOperator(char c);
    int precedence(char op);
    bool areParenthesesBalanced(const std::string& expr);
};




