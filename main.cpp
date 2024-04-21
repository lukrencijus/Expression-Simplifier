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
#include <sys/stat.h>
#include <unistd.h>


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
const string OUTPUT_FILE = "out.txt";

bool fileExists (const string& name) 
{
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

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

        //For the last number
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

int areFilesGood(string arg) 
{
        ifstream inputFile;
        
        if (!fileExists(arg))
        {
            cerr << "File does not exist " << arg << endl;
            return EXIT_FAILURE;
        }

        inputFile.open(arg);
        if (!inputFile) 
        {
            cerr << "Unable to open input file";
            return EXIT_FAILURE;
        }

        ofstream outputFile;
        outputFile.open(OUTPUT_FILE);

        if (!outputFile) 
        {
            cerr << "Unable to open output file";
            return EXIT_FAILURE;
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
            else if (evaluateParentheses(line) == 0)
            {
                cout << evaluateParentheses(line) << endl;
                outputFile << evaluateParentheses(line) << endl;
            }
            else
            {
                cerr << "Error: invalid expression" << endl;
                outputFile << "Error: invalid expression" << endl;
            }
        }

        inputFile.close();
        outputFile.seekp(-1, ios_base::cur);
        outputFile.put(' ');
        outputFile.close();
        if (!outputFile.is_open())
        {
            cout << endl;
            cout << "All answers were also successfully saved to " << OUTPUT_FILE << endl;
            cout << endl;
        }
    return EXIT_SUCCESS;
}

int main( int argc, char *argv[] )
{
    //If one file is provided everything is nice
   if( argc == 2 ) 
   {
        if(areFilesGood(argv[1]) != EXIT_SUCCESS) return EXIT_FAILURE;
   }

    //If more than one file names provided it is not nice
   else if( argc > 2 ) 
   {
        cerr << "Too many arguments supplied" << endl;
        return 0;
   }

    //If user does not provide anything
   else 
   {
        cout << endl;
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        cout << "One argument was expected. But now please enter expression you would like to simplify" << endl;
        cout << "Or you can also enter file name ending with [.txt] from which you would like expressions to be simplified" << endl;
        cout << "Quit by typing \"q\" or \"exit\" and [Enter]" << endl;
        string expression;
        while(true)
        {
            getline(cin, expression);
            if(expression == "q" || expression == "exit") return 0;

            if (expression.length() >= 4 && expression.substr(expression.length() - 4) == ".txt")
            {
                if(areFilesGood(expression) != EXIT_SUCCESS) return EXIT_FAILURE;
                break;
            }

            else
            {
                if(hasOnlyNumbersOrOperations(expression))
                {
                    cout << evaluateParentheses(expression) << endl;
                }
                else if (expression.empty())
                {
                    cout << endl;
                }
                else if (evaluateParentheses(expression) == 0)
                {
                    cout << evaluateParentheses(expression) << endl;
                }
                else
                {
                    cerr << "Error: invalid expression" << endl;
                }
            }
        }
   }
    return 0;
}