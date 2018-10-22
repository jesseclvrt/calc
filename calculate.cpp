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

int evaluate(char expression[]) {
    std::stack<int> values;
    std::stack<char> operators;
    for (int i = 0; i < strlen(expression); i++) {
        if (std::isspace(expression[i])) { continue; }

        else if (std::isdigit(expression[i])) {
            int value = 0;
            while (isdigit(expression[i])) {
                value *= 10;
                value += expression[i] - '0';
                i++;
            }
            values.push(value);
        }

        else if (expression[i] == '(') {
            operators.push(expression[i]);
        }

        else if (expression[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                int op2 = values.top();
                values.pop();
                int op1 = values.top();
                values.pop();
                char op = operators.top();
                operators.pop();
                values.push(applyOperation(op1, op2, op));
            }
            operators.pop();
        }

        else { // expression[i] is operator
            while (!operators.empty()
                    && opOrder(operators.top()) >= opOrder(expression[i])) {
                int op2 = values.top();
                values.pop();
                int op1 = values.top();
                values.pop();
                char op = operators.top();
                operators.pop();
                values.push(applyOperation(op1, op2, op));
            }
            operators.push(expression[i]);
        }
    } // end for
    while (!operators.empty()) {
        int op2 = values.top();
        values.pop();
        int op1 = values.top();
        values.pop();
        char op = operators.top();
        operators.pop();
        values.push(applyOperation(op1, op2, op));
    }
    return values.top();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Evaluates simple expressions.\n"
            "Valid symbols: + - * / ^ ()" << std::endl;
        return 0;
    }
    for (int i = 1; i <= argc; i++) {
        std::cout << argv[i] << " = " << evaluate(argv[i]);
    }
    return 0;
}