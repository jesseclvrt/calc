#include <iostream>
#include <stack>
#include <cmath>
#include <cstring>

int opOrder(char op) {
    switch (op) {
        case('(') :             return 0;
        case('+') : case('-') : return 1;
        case('*') : case('/') : return 2;
        case('^') :             return 3;
    }
}

int applyOperation(int x, int y, char op) {
    switch (op) {
        case('+') : return x + y;
        case('-') : return x - y;
        case('*') : return x * y;
        case('/') : return x / y;
        case('^') : return pow(x, y);
    }
}

void evaluateTops(std::stack<int>* values, std::stack<char>* operators) {
    int op2 = values->top();
    values->pop();
    int op1 = values->top();
    values->pop();
    char op = operators->top();
    operators->pop();
    values->push(applyOperation(op1, op2, op));
}

int evaluate(char expression[]) {
    std::stack<int>* values = new std::stack<int>;
    std::stack<char>* operators = new std::stack<char>;
    for (int i = 0; i < strlen(expression); i++) {
        if (std::isspace(expression[i])) { continue; }

        else if (std::isdigit(expression[i])) {
            int num = 0;
            while (isdigit(expression[i])) {
                num *= 10;
                num += expression[i] - '0';
                i++;
            }
            values->push(num);
        }

        else if (expression[i] == '(') {
            operators->push(expression[i]);
        }

        else if (expression[i] == ')') {
            while (!operators->empty() && operators->top() != '(') {
                evaluateTops(values, operators);
            }
            operators->pop(); // opening brace
        }

        else { // expression[i] is operator
            while (!operators->empty()
                    && opOrder(operators->top()) >= opOrder(expression[i])) {
                evaluateTops(values, operators);
            }
            operators->push(expression[i]);
        }
    } // end for
    while (!operators->empty()) {
        evaluateTops(values, operators);
    }
    int solution = values->top();
    delete values;
    delete operators;
    return solution;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Evaluates simple expressions.\n"
            "Valid symbols: + - * / ^ ()" << std::endl;
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        std::cout << argv[i] << " = " << evaluate(argv[i]) << std::endl;
    }
    return 0;
}