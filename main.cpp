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

class CustomException {
public:
    CustomException(const string& message) : errorMessage(message) {}
    const char* what() const { return errorMessage.c_str(); }

private:
    string errorMessage;
};

bool fileExists (const string& name) 
{
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}


// Function to parse and evaluate addition and subtraction
int additionAndSubtraction(const std::string& expression) {
    int result = 0;
    int num = 0;
    char op = '-';

    for (char c : expression) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        } else {
            if (op == '+') {
                result += num;
            } else if (op == '-') {
                result -= num;
            }
            num = 0;
            op = c;
        }
    }
    if (op == '+') {
        result += num;
    } else if (op == '-') {
        result -= num;
    }
    return result;
}

// Function to parse and evaluate multiplication and division
int multiplicationAndDivision(const std::string& expression) {
    int result = 0;
    int num = 0;
    char op = '*'; // Default operation is multiplication

    for (char c : expression) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        } else {
            if (op == '*') {
                result = (result == 0) ? num : result * num;
            } else if (op == '/') {
                result /= num;
            }
            num = 0;
            op = c;
        }
    }
    if (op == '*') {
        result = (result == 0) ? num : result * num;
    } else if (op == '/') {
        result /= num;
    }
    return result;
}

// Function to evaluate expressions combining addition/subtraction and multiplication/division
int evaluateExpression(const std::string& expression) {
    // Find the first occurrence of '+' or '-'
    size_t plus_minus_pos = expression.find_first_of("+-");
    if (plus_minus_pos == std::string::npos) {
        // If '+' or '-' not found, evaluate only multiplication and division
        return multiplicationAndDivision(expression);
    } else {
        // Evaluate the part before '+' or '-' recursively
        int left_result = multiplicationAndDivision(expression.substr(0, plus_minus_pos));
        // Evaluate the part after '+' or '-' recursively
        int right_result = evaluateExpression(expression.substr(plus_minus_pos + 1));

        // Perform addition or subtraction based on the operator
        if (expression[plus_minus_pos] == '+') {
            return left_result + right_result;
        } else {
            return left_result - right_result;
        }
    }
}

//Find "(", write everything until "(" to temp
//send it into a deeper while loop that finds ")" 
//only then sends it to be simplified
int evaluateParentheses(const string& str) 
{
    int result = 0;
    string temp;
    stringstream ss(str);
    while (getline(ss, temp, ')')) 
    {
        stringstream ss2(temp);
        string inside;
        while (getline(ss2, inside, '(')) 
        {
            result += evaluateExpression(inside);
        }
    }
    return result;
}

//Check if it a number using ASCII
bool isDigit(char c) 
{
    return (c >= '0' && c <= '9');
}

bool hasOnlyNumbersOrOperations(const string& str) 
{
    for (char c : str) {
        if (!(c == '+' || c == '-' || c == '*' || c == '/' || c == ' ' || c == '(' || c == ')' || isDigit(c))) {
            return false;
        }
    }
    return true;
}

int areFilesGood(const string& arg) 
{
        ifstream inputFile;
        
        if (!fileExists(arg))
        {
            try {
                throw CustomException("File does not exist");
                } catch (const CustomException& e) {
                cerr << "ERROR: " << e.what() << endl;
            }
            return EXIT_FAILURE;
        }

        inputFile.open(arg);
        if (!inputFile) 
        {
            try {
                throw CustomException("Unable to open input file");
                } catch (const CustomException& e) {
                cerr << "ERROR: " << e.what() << endl;
            }
            return EXIT_FAILURE;
        }

        ofstream outputFile;
        outputFile.open(OUTPUT_FILE);

        if (!outputFile) 
        {
            try {
                throw CustomException("Unable to open output file");
                } catch (const CustomException& e) {
                cerr << "ERROR: " << e.what() << endl;
            }
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
            else if (evaluateParentheses(line) == 0 && hasOnlyNumbersOrOperations(line))
            {
                cout << evaluateParentheses(line) << endl;
                outputFile << evaluateParentheses(line) << endl;
            }
            else
            {
                try {
                    throw CustomException("Invalid expression");
                    } catch (const CustomException& e) {
                    cerr << "ERROR: " << e.what() << endl;
                    outputFile << "ERROR: " << e.what() << endl;
                }
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
        try {
            throw CustomException("Too many arguments supplied");
            } catch (const CustomException& e) {
                cerr << "ERROR: " << e.what() << endl;
        }
        return 0;
   }

    //If user does not provide anything
   else 
   {
        cout << endl;
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        cout << "One argument was expected. But now please enter expression you would like to simplify" << endl;
        cout << "Or you can enter file name ending with [.txt] from which you would like expressions to be simplified" << endl;
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
                else if (evaluateParentheses(expression) == 0 && hasOnlyNumbersOrOperations(expression))
                {
                    cout << evaluateParentheses(expression) << endl;
                }
                else
                {
                    try {
                        throw CustomException("Invalid expression");
                        } catch (const CustomException& e) {
                            cerr << "ERROR: " << e.what() << endl;
                    }
                }
            }
        }
   }
    return 0;
}