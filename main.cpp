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

const string OUTPUT_FILE = "out.txt";

class CustomException {
    public:

        CustomException(const string& message) : errorMessage(message) {}
        const char* what() const { return errorMessage.c_str(); }

    private:
        string errorMessage;
};

class Validation {
    public:

        //Check if string is empty
        bool hasOnlySpaces(const string& input) 
        {
            for (char c : input) {
                if (!isspace(c)) 
                {
                    return false;
                }
            }
            return true;
        }

        //Check if file exists
        bool doesFileExist(const string& name) 
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
            for (char c : str) 
            {
                if (!(c == '+' || c == '-' || c == '*' || c == '/' || c == ' ' || c == '(' || c == ')' || isDigit(c))) 
                {
                    return false;
                }
            }
            return true;
        }

        //Checking if files exists, can they be opened
        int areFilesGood(const string& arg) 
        {
            ifstream inputFile;
            if (!doesFileExist(arg))
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

class Simplifier {
    private:

        Validation check;

        int* result;
        int* sum;
        int* num;
        bool* inNumber;
        char* op;

        string* line;

        string* temp;
        string* inside;

        int* results;

        //If digit is in a row two times or more we must x10 it because it is a multi-digit number
        int simplifyExpression(const string& expression) 
        {
            *result = 0;
            *num = 0;
            *inNumber = false;
            *op = '+';

            for (char c : expression) 
            {
                if (check.isDigit(c)) 
                {
                    *num = *num * 10 + (c - '0');
                    *inNumber = true;
                } 
                else if (c == '+' || c == '-' || c == '*' || c == '/') 
                {
                    if (*inNumber) 
                    {
                        if (*op == '+') 
                        {
                            *result += *num;
                        } 
                        else if (*op == '-') 
                        {
                            *result -= *num;
                        } 
                        else if (*op == '*') 
                        {
                            *result *= *num;
                        } 
                        else if (*op == '/') 
                        {
                            *result /= *num;
                        }
                        *num = 0;
                        *inNumber = false;
                    }
                    *op = c;
                }
            }

            if (*inNumber) 
            {
                if (*op == '+') 
                {
                    *result += *num;
                } 
                else if (*op == '-') 
                {
                    *result -= *num;
                } 
                else if (*op == '*') 
                {
                    *result *= *num;
                } 
                else if (*op == '/') 
                {
                    *result /= *num;
                }
            }
            return *result;
        }

    public:

        Simplifier()
        {
            result = new int;
            sum = new int;
            num = new int;
            inNumber = new bool;
            op = new char;

            line = new string;

            temp = new string;
            inside = new string;

            results = new int;
        }

        ~Simplifier() 
        {
            delete result;
            delete sum;
            delete num;
            delete inNumber;
            delete op;

            delete line;

            delete temp;
            delete inside;

            delete results;
        }

        //Find ")", write everything until it to temp
        //send it into a deeper while loop that finds "(" 
        //only then sends it to be simplified
        int evaluateParentheses(const string& str) 
        {
            *results = 0;
            stringstream ss(str);
            while (getline(ss, *temp, ')')) 
            {
                stringstream ss2(*temp);
                while (getline(ss2, *inside, '(')) 
                {
                    *results += simplifyExpression(*inside);
                }
            }
            return *results;
        }

        //Reading from command line as input and writing it to command line
        void readingAndWritingStdout(const string& line)
        {
            if(check.hasOnlyNumbersOrOperations(line))
            {
                cout << evaluateParentheses(line) << endl;
            }
            else if (check.hasOnlySpaces(line))
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

        //Reading from provided file as command line argument
        //writing it to command line and output file
        void readingAndWritingFile(const string& arg)
        {
            ifstream inputFile;
            inputFile.open(arg);
            ofstream outputFile;
            outputFile.open(OUTPUT_FILE);
            
            cout << endl;
            cout << "Answers: " << endl;

            while (getline(inputFile, *line)) 
            {
                if(check.hasOnlyNumbersOrOperations(*line))
                {
                    cout << evaluateParentheses(*line) << endl;
                    outputFile << evaluateParentheses(*line) << endl;
                }
                else if (check.hasOnlySpaces(*line))
                {
                    cout << endl;
                    outputFile << endl;
                }
                else if (evaluateParentheses(*line) == 0 && check.hasOnlyNumbersOrOperations(*line))
                {
                    cout << evaluateParentheses(*line) << endl;
                    outputFile << evaluateParentheses(*line) << endl;
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
};



int main( int argc, char *argv[] )
{
    Simplifier simp;
    Validation check;

    //If only one file is provided everything is nice
   if( argc == 2 ) 
   {
        if(check.areFilesGood(argv[1]) != EXIT_SUCCESS) return EXIT_FAILURE;
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
                if(check.areFilesGood(expression) != EXIT_SUCCESS) return EXIT_FAILURE;
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