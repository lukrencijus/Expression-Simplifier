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

//FIXME
//unary negation
//multiplication and division priorities

//TODO
//OOP classes
//Private and public things
//Put functions into their classes
//Dynamic memory

using namespace std;

const string OUTPUT_FILE = "out.txt";


class CustomException {
    public:

        //Error message
        CustomException(const string& message) : errorMessage(message) {}
        const char* what() const { return errorMessage.c_str(); }

    private:
        string errorMessage;
};



class Validation {
    public:

        //Check if string is empty
        bool hasOnlySpaces(string input) 
        {
            for (char c : input) {
                if (!isspace(c)) {
                    return false;
                }
            }
            return true;
        }

        //Check if file exists
        bool fileExists (const string& name) 
        {
        struct stat buffer;   
        return (stat (name.c_str(), &buffer) == 0); 
        }

        //Check if it is a number using ASCII
        bool isDigit(char c) 
        {
            return (c >= '0' && c <= '9');
        }

        //Check if string includes numbers or operators
        bool hasOnlyNumbersOrOperations(const string& str) 
        {
            if (hasOnlySpaces(str)) return false;
            for (char c : str) {
                if (!(c == '+' || c == '-' || c == '*' || c == '/' || c == ' ' || c == '(' || c == ')' || isDigit(c))) {
                    return false;
                }
            }
            return true;
        }

};



class Simplifier {
    private:
        Validation check;

    public:

        //If digit is in a row two times or more we must x10 it because it is a multi-digit number
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

                //For the last digit in an expression
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
                    result += simplifyExpression(inside);
                }
            }
            return result;
        }

        //Reading from provided file as input and writing it to output file
        void readingAndWritingStdout(const string& line){
                if(check.hasOnlyNumbersOrOperations(line))
                {
                    cout << evaluateParentheses(line) << endl;
                }
                else if (line.empty())
                {
                    cout << endl;
                }
                else if (evaluateParentheses(line) == 0 && check.hasOnlyNumbersOrOperations(line))
                {
                    cout << evaluateParentheses(line) << endl;
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

        //Reading from provided file as command line argument and writing it to output file
        void readingAndWritingFile(const string& arg)
        {
            string line;

            ifstream inputFile;
            inputFile.open(arg);
            ofstream outputFile;
            outputFile.open(OUTPUT_FILE);
            
            cout << endl;
            cout << "Answers: " << endl;

            while (getline(inputFile, line)) 
            {
                if(check.hasOnlyNumbersOrOperations(line))
                {
                    cout << evaluateParentheses(line) << endl;
                    outputFile << evaluateParentheses(line) << endl;
                }
                else if (check.hasOnlySpaces(line))
                {
                    cout << endl;
                    outputFile << endl;
                }
                else if (evaluateParentheses(line) == 0 && check.hasOnlyNumbersOrOperations(line))
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
                cout << "All answers were also successfully saved to " << OUTPUT_FILE << endl;
                cout << endl;
            }
        }

        //Checking if files exists, can they be opened
        int areFilesGood(const string& arg) 
        {
            ifstream inputFile;
                
            if (!check.fileExists(arg))
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
            return EXIT_SUCCESS;
    }
};


int main( int argc, char *argv[] )
{
    Simplifier simp;
    Validation check;

    //If only one file is provided everything is nice
   if( argc == 2 ) 
   {
        if(simp.areFilesGood(argv[1]) != EXIT_SUCCESS) return EXIT_FAILURE;
        simp.readingAndWritingFile(argv[1]);
   }

    //If more than one file provided it is not nice
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
                if(simp.areFilesGood(expression) != EXIT_SUCCESS) return EXIT_FAILURE;
                simp.readingAndWritingFile(expression);
                break;
            }

            else
            {
                simp.readingAndWritingStdout(expression);
            }
        }
    }
    return 0;
}