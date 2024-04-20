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

//PRIDETI FUNKCIJA KURI PIRMA PATIKRINA AR 
//STRINGAS NERA TIUSCIAS
//JEIGU YRA TAI TIESIOG PADARO JI TUSCIA IR ISSIUNCIA ATGAL



// string subtraction (const string& expression){
//     //gal ne const
// }

// string multiplication (const string& expression){
//     //gal ne const
// }

// string division (const string& expression){
//     for (char c : expression){
        
//     }
// }

int simplifyExpression(const string& expression) {
    int result = 0;
    int sum = 0;
    int num = 0;
    bool inNumber = false;
    char op = '+';

   for (char c : expression) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
            inNumber = true;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (inNumber) {
                if (op == '+') {
                    result += num;
                } else if (op == '-') {
                    result -= num;
                } else if (op == '*') {
                    result *= num;
                } else if (op == '/') {
                    result /= num;
                }
                num = 0;
                inNumber = false;
            }
            op = c;
        } else {
            // Ignore other characters
        }
    }

    // Add/subtract the last number if the expression doesn't end with '+' or '-' or '*'
        if (inNumber) {
            if (op == '+') {
                result += num;
            } else if (op == '-') {
                result -= num;
            } else if (op == '*') {
                result *= num;
            } else if (op == '/') {
                result /= num;
            }
        }

        return (result);
}

int evaluateParentheses(string str) {
    int result = 0;
    string temp;
    stringstream ss(str);
    while (getline(ss, temp, '(')) 
    {
        stringstream ss2(temp);
        string inside;
        while (getline(ss2, inside, ')')) 
        {
            result = simplifyExpression(inside);
        }
    }
    return result;
}

bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

bool hasOnlyNumbersOrOperations(string str) {
    if (simplifyExpression(str) == 0) return false;
    for (char c : str) {
        if (!(c == '+' || c == '-' || c == '*' || c == '/' || c == ' ' || c == '(' || c == ')' || isDigit(c))) {
            return false;
        }
    }
    return true;
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
        if(hasOnlyNumbersOrOperations(line))
        {
              cout << evaluateParentheses(line) << endl;
              cout << endl;
        }
        else if (simplifyExpression(line) == 0)
        {
            cout << endl;
            cout << endl;
        }
        else
        {
            cout << "Error: invalid expression" << endl;
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