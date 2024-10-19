Lukas Šerelis, April 24, 2024
lukas.serelis@mif.stud.vu.lt

Vilnius University Faculty of Mathematics and Informatics
Object-Oriented Programming course
Lecturer: Irmantas Radavicius

Visual Studio Code 1.88.1   macOS 14.4   arm64
Compiler: g++ 12 (GNU C++ Compiler)

THE EXPRESSION SIMPLIFIER
Program simplifies mathematical expressions containing parentheses, operators, and numbers.
It reads input from the command line or a file, simplifies each expression, and prints the result to the console and an output file.

THE EXPRESSION SIMPLIFIER
General info:
- given the expression eg. "8+9 * 15-(-7/3 +7 * 8)/2+ 3 * 7" (spaces should not change anything, but newlines should) you should output "137" (without quotes, those are just used to separate the value from the rest of the text)
- in particular, the expression simplifier should understand 4 arithmetic operations on integers, brackets for priorities, as well as unary negation; it is recommended to do it using bottom-up approach
Requirements for the program:
- input is provided a data file which contains lines of text (possibly some empty or invalid ones) with each expression to simplify per line
- the name for the input file is to be submitted as a command line argument for main (google argc/argv); if there are no parameters, program musk ask for an input from user; if the file does not exist, program must end and return EXIT_FAILURE)
- output: all results are to be sent to stdout as well as a file "out.txt" (the name is defined as a constant on top of the file where main() is), has as many lines as the input file; for each valid expression write a single number (obtained as a result after simplifying); for each empty line write an empty line; for each invalid expression output a string with a (custom) error message
- the program should be based on classes as well as OOP principles
every variable (!) and field has to be (artificially) stored in dynamic memory (i.e. created with "new" and then released with "delete") - this is purely for learning purposes, so that you have to write a destructor, learn RAII as well as proper copy methods (google deep copy)
- if the expression is invalid - class should throw a custom (you have to create a class to represent errors, again, for learning purposes) exception, which is to be caught and processed accordingly
- it is recommended for each class to have .h and .cpp file, and put main in a separate .cpp file; you can have as many files as you wish, including sample data files - you will be asked to upload an archive with everything inside
- you are allowed to use STL (vectors and other classes and/or functions from standard library) - no need to reinvent the bike!

Summary: simplify the expression, input and output is in files, throw exceptions in case of errors, use dynamic memory, provide deep copying, and split your program among multiple files
