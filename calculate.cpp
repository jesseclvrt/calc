/*
*TODO: File header
*TODO: Testing
*TODO: Function comments
*/

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

double applyOperation(double x, double y, char op) {
    switch (op) {
        case('+') : return x + y;
        case('-') : return x - y;
        case('*') : return x * y;
        case('/') : return x / y;
        case('^') : return pow(x, y);
    }
}

//TODO: Exception handling here
void evaluateTops(std::stack<double>& values, std::stack<char>& operators) {
    double op2 = values.top();
    values.pop();
    double op1 = values.top();
    values.pop();
    char op = operators.top();
    operators.pop();
    values.push(applyOperation(op1, op2, op));
}

double parseNum(char expression[], int start, int end) {
    bool negative = false;
    if (expression[start] == '-' && expression[start + 1] == '-') {
        negative = true;
        start += 2;
    }
    double decimal = 0;
    double solution = 0;
    while (start <= end) {
        if (expression[start] == '.') {
            decimal = 1;
            start++;
            continue;
        }
        if (decimal) {
            decimal *= 10;
            solution += (expression[start] - '0') / decimal;
        } else {
            solution *= 10;
            solution += expression[start] - '0';
        }
        start++;
    }
    if (negative) {
        solution *= -1;
    }
    return solution;
}

double evaluate(char expression[]) {
    std::stack<double> values;
    std::stack<char> operators;
    for (int i = 0; i < strlen(expression); i++) {
        if (std::isspace(expression[i])) { continue; }
        else if (std::isdigit(expression[i])
                    || expression[i] == '.'
                    || (expression[i] == '-' && expression[i+1] == '-')) {
            int start = i;
            if (expression[start] == '-' && expression[start+1] == '-') {
                i += 2;
            }
            while (isdigit(expression[i+1])
                    || expression[i+1] == '.') {
                i++;
            }
            values.push(parseNum(expression, start, i));
        } else if (expression[i] == '(') {
            operators.push(expression[i]);
        } else if (expression[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                evaluateTops(values, operators);
            }
            operators.pop(); // opening brace
        } else { // expression[i] is operator
            while (!operators.empty()
                    && opOrder(operators.top()) >= opOrder(expression[i])) {
                evaluateTops(values, operators);
            }
            operators.push(expression[i]);
        }
    } // end for
    while (!operators.empty()) {
        evaluateTops(values, operators);
    }
    return values.top();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Evaluates simple infix expressions.\n"
            "Valid operations: + - * / ^ ()\n"
            "Represent negative numbers with a prepended \'--\' sign.\n"
            "Spaces and parenthesis are disallowed unless "
            "the argument is enclosed in \"quotation marks\".\n"
            "Handles multiple expressions." << std::endl;
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        std::cout << argv[i] << " = " << evaluate(argv[i]) << std::endl;
    }
    return 0;
}