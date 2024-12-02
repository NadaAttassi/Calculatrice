#include "Calculatrice.h"
#include <iostream>
#include <cctype>

using namespace std;

bool Calculatrice::areParenthesesBalanced(const string& expr) {
    stack<char> parentheses;
    for (char ch : expr) {
        if (ch == '(') {
            parentheses.push(ch);
        }
        else if (ch == ')') {
            if (parentheses.empty()) {
                return false; 
            }
            parentheses.pop();
        }
    }
    return parentheses.empty();
}

double Calculatrice::evaluate(const string& expression) {
    if (!areParenthesesBalanced(expression)) {
        throw runtime_error("Erreur : parenthèses mal utilisées.");
    }

    stack<double> values;  // Pile pour les valeurs numériques
    stack<char> ops;       // Pile pour les opérateurs

    bool lastWasOperator = true; //vérifier les opérateurs consécutifs

    for (int i = 0; i < expression.size(); i++) {
        if (isspace(expression[i])) {
            continue; // Ignorer les espaces
        }

        if (isdigit(expression[i]) || expression[i] == '.') {
            string num = "";

            while (i < expression.size() && (isdigit(expression[i]) || expression[i] == '.')) {
                num += expression[i++];
            }
            values.push(stod(num));
            lastWasOperator = false;
            i--;
        }

        else if (expression[i] == '(') {
            ops.push('(');
            lastWasOperator = true;
        }

        else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                applyOperator(values, ops);
            }
            ops.pop(); // Retirer la parenthèse ouvrante '('
            lastWasOperator = false;
        }

        else if (isOperator(expression[i])) {
            if (lastWasOperator && expression[i] != '-') {
                throw runtime_error("Erreur : opérateur consécutif trouvé (ex: '++', '--', '**', '//').");
            }
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                applyOperator(values, ops);
            }
            ops.push(expression[i]);
            lastWasOperator = true;
        }

        else {
            throw runtime_error("Erreur : caractère invalide dans l'expression.");
        }
    }

    while (!ops.empty()) {
        applyOperator(values, ops);
    }

    if (values.size() != 1) {
        throw runtime_error("Erreur : expression malformée.");
    }

    return values.top();
}

void Calculatrice::applyOperator(stack<double>& values, stack<char>& ops) {
    char op = ops.top();
    ops.pop();

    double right = values.top();
    values.pop();

    double left = values.top();
    values.pop();

    double result = 0;

    switch (op) {
    case '+': result = left + right; break;
    case '-': result = left - right; break;
    case '*': result = left * right; break;
    case '/':
        if (right == 0) {
            throw runtime_error("Erreur : division par zéro.");
        }
        result = left / right;
        break;
    case '^': result = pow(left, right); break;
    case 'r': result = sqrt(right); break;
    default: throw runtime_error("Erreur : opérateur inconnu.");
    }

    values.push(result);
}

bool Calculatrice::isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 'r');
}

int Calculatrice::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^' || op == 'r') return 3;
    return 0;
}
