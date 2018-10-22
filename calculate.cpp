#include <iostream>

int evaluate(char expression[]) {
    
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Evaluates simple expressions.\n"
            "Valid symbols: + - * / ^ ()" << std::endl;
        return 0;
    }
    for (int i = 1; i <= argc; i++) {
        evaluate(argv[i]);
    }
    return 0;
}