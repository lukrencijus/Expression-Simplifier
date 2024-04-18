//This program reads expressions from provided text file
//If no file is provided, user can enter input directly
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main() {
    const string OUTPUT_FILE = "out.txt";

    ifstream inputFile;
    ofstream outputFile;    //Is this the correct way of reading and writing, read about it in notion

    inputFile.open("in.txt");   //but it should be provided from cmd

    if (!inputFile) {
        cerr << "Unable to open file";
        return 1; // Maybe different error
    }

    string line;
    while (getline(inputFile, line)) {
        cout << line << endl;
    }



    outputFile.open(OUTPUT_FILE);

    if (!outputFile) {
        cerr << "Unable to open file";
        return 1; // Maybe different error
    }

    outputFile << "25" << endl;

    // cout << endl;
    // cout << "Use case is:    ./main.cpp <filename.txt>" << endl;
    // cout << "If no file name is detected, you will need to enter expression manually" << endl;
    // cout << "Quit by typing <q> or <exit>" << endl;
    // cout << endl;
    // cout << "Please enter the expresion" << endl;
    //while(true)

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