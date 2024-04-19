//This program reads expressions from provided text file
//If no file is provided, user can enter input directly
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <iomanip>
#include <sstream>

using namespace std;

bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

string simplifyExpression(const string& expression) {

    cout << "I got: " << expression << endl;

    if (expression.empty()) 
    {
        cout << "The line is empty." << endl;
    } 

    stringstream ss(expression);
    string token;
    vector<int> numbers;
    int sum = 0;

    while (getline(ss, token, '+')) {
        stringstream num_ss(token);
        char c;
        bool all_digits = true;
        while (num_ss >> c) {
            if (!isDigit(c)) {
                all_digits = false;
                cout << "Error found" << endl;
                break;
            }
        }
        if (all_digits) {
            int num;
            num_ss.clear();
            num_ss.seekg(0);
            if (num_ss >> num) {
                sum += num;
            }
        }
    }

    return to_string(sum);
}

int main() {
    const string OUTPUT_FILE = "out.txt";

    ifstream inputFile;
    ofstream outputFile;    //Is this the correct way of reading and writing, read about it in notion

    inputFile.open("in.txt");   //but it should be provided from cmd

    if (!inputFile) {
        cerr << "Unable to open file";
        return 1; // Maybe different error
    }

    outputFile.open(OUTPUT_FILE);

    if (!outputFile) {
        cerr << "Unable to open file";
        return 1; // Maybe different error
    }

    string line;
    while (getline(inputFile, line)) {
        //cout << "Answer is " << calculating(line) << endl;
        cout << simplifyExpression(line) << endl;
        //outputFile << simplifyExpression(line) << endl;
        cout << endl;
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