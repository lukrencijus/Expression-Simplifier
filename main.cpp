#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <cctype>
#include <iomanip>
#include <sstream>

using namespace std;

//ToDo
//brackets for priorities
//unary negation

// Function to perform addition
int addition(int a, int b) {
    return a + b;
}

// Function to perform subtraction
int subtraction(int a, int b) {
    return a - b;
}

// Function to perform multiplication
int multiplication(int a, int b) {
    return a * b;
}

// Function to perform division
int division(int a, int b) {
    if (b != 0) {
        return a / b;
    } else {
        cout << "Error: Division by zero!" << endl;
        return 0; // You may handle this error differently based on your needs
    }
}

// Function to simplify an expression
int simplifyExpression(const string& expression) {
    int result = 0;
    int num = 0;
    bool inNumber = false;
    char op = '+';

    for (size_t i = 0; i < expression.size(); ++i) {
        char c = expression[i];
        char cc = (i < expression.size() - 1) ? expression[i + 1] : '\0'; // Next character

        if (isdigit(c)) {
            num = num * 10 + (c - '0');
            inNumber = true;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (inNumber) {
                switch (op) {
                    case '+':
                        result = addition(result, num);
                        break;
                    case '-':
                        result = subtraction(result, num);
                        break;
                    case '*':
                        result = multiplication(result, num);
                        break;
                    case '/':
                        result = division(result, num);
                        break;
                }
                num = 0;
                inNumber = false;
            }
            op = c;
        } else if (c == '-' && cc == '-') {
            if (inNumber) {
                result = addition(result, num);
                num = 0;
                inNumber = false;
            }
        }
        // Ignore other characters
    }

    // Add/subtract/multiply/divide the last number if the expression doesn't end with an operator
    if (inNumber) {
        switch (op) {
            case '+':
                result = addition(result, num);
                break;
            case '-':
                result = subtraction(result, num);
                break;
            case '*':
                result = multiplication(result, num);
                break;
            case '/':
                result = division(result, num);
                break;
        }
    }

    return result;
}


int main() {
    const string OUTPUT_FILE = "out.txt";

    ifstream inputFile;
    ofstream outputFile;    //Is this the correct way of reading and writing, read about it in notion

    inputFile.open("in.txt");   //but it should be provided from cmd

    if (!inputFile) 
    {
        cerr << "Unable to open file";
        return 1; // Maybe different error
    }

    outputFile.open(OUTPUT_FILE);

    if (!outputFile) 
    {
        cerr << "Unable to open file";
        return 1; // Maybe different error
    }

    string line;
    while (getline(inputFile, line)) 
    {
        if (simplifyExpression(line) == 0)
        {
            cout << endl;
        }
        else
        {
            cout << simplifyExpression(line) << endl;
            cout << endl;
        }

    }



    // cout << endl;
    // cout << "Use case is:    ./main.cpp <filename.txt>" << endl;
    // cout << "If no file name is detected, you will need to enter expression manually" << endl;
    // cout << "Quit by typing \"q\" or \"exit\" and [Enter]" << endl;
    // cout << endl;
    // cout << "Please enter the expresion" << endl;
    //while(true)
    //if(input == "quit") break;

    //if file does not exist:
    //return EXIT_FAILURE


    //if user enters nothing:

    // cout << "No file name entered" << endl;
    // cout << "Please enter an expression" << endl;
    //cin >> string;


    inputFile.close();
    outputFile.close();
    return 0;
}