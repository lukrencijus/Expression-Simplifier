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
#include <cstdlib> 

using namespace std;

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

int simplifyExpression(const string& expression) 
{
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
        }
    }

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

int evaluateParentheses(string str) 
{
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

bool isDigit(char c) 
{
    return (c >= '0' && c <= '9');
}

bool hasOnlyNumbersOrOperations(string str) 
{
    if(simplifyExpression(str) == 0) return false;
    for (char c : str) {
        if (!(c == '+' || c == '-' || c == '*' || c == '/' || c == ' ' || c == '(' || c == ')' || isDigit(c))) {
            return false;
        }
    }
    return true;
}


int main( int argc, char *argv[] )
{
    // if one file is provided everything is nice
   if( argc == 2 ) 
   {
    cout << endl;
    cout << "The argument supplied is " << argv[1] << endl;
    cout << endl;
    ifstream inputFile;
    inputFile.open(argv[1]);
    if (!(inputFile.good()))
    {
        return EXIT_FAILURE;
    }

    if (!inputFile) 
    {
        cerr << "Unable to open input file";
        return 1;
    }

    ofstream outputFile;
    const string OUTPUT_FILE = "out.txt";
    outputFile.open(OUTPUT_FILE);

    if (!outputFile) 
    {
        cerr << "Unable to open output file";
        return 1;
    }

    string line;
    while (getline(inputFile, line)) 
    {
        if(hasOnlyNumbersOrOperations(line))
        {
              cout << evaluateParentheses(line) << endl;
              outputFile << evaluateParentheses(line) << endl;
        }
        else if (line.empty())
        {
            cout << endl;
            outputFile << endl;
        }
        else if (simplifyExpression(line) == 0)
        {
            cout << "0" << endl;
            outputFile << "0" << endl;
        }
        else
        {
            cout << "Error: invalid expression" << endl;
            outputFile << "Error: invalid expression" << endl;
        }
    }

    inputFile.close();
    outputFile.seekp(-1, ios_base::cur);
    outputFile.put(' ');
    outputFile.close();
   }



   else if( argc > 2 ) 
   {
        cout << "Too many arguments supplied" << endl;
        return 0;
   }
   else 
   {
        cout << endl;
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        cout << "One argument was expected. But now please enter expression you would like to simplify" << endl;
        cout << "Quit by typing \"q\" or \"exit\" and [Enter]" << endl;
        string expression;
        while(true)
        {
            getline(cin, expression);
            if(expression == "q" || expression == "exit") return 0;

            if(hasOnlyNumbersOrOperations(expression))
            {
                cout << evaluateParentheses(expression) << endl;
            }
            else if (expression.empty())
            {
                cout << endl;
            }
            else if (simplifyExpression(expression) == 0)
            {
                cout << "0" << endl;
            }
            else
            {
                cout << "Error: invalid expression" << endl;
            }

        }
   }
    return 0;
}