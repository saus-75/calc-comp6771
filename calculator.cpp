#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stack>
#include <string>
#include <queue>

void ptr(std::stack<std::string> stk);

int main(int argc, char* argv[]) {

    // setup the print out format for the precision required.
    std::cout.setf(std::ios::fixed,std::ios::floatfield);
    std::cout.precision(3);

    // open the file for reading
    std::ifstream in;
    in.open(argv[1]);

    //seg fault will occur if theres no input
    if (argv[1] != NULL){
        std::cout << argv[1] << std::endl;
    } else {
        std::cout << "Please input a valid filename" << std::endl;
    }

    // Initation
    std::string s;
    std::queue <std::string> op;
    std::stack <std::string> numbers;
    std::stack <std::string> stkPtr;

 
    // read the file while we have input and shove it into a queue.
    while (in >> s) {
        op.push(s);
        stkPtr.push(s);
    }

    // loop from queue
    while (!op.empty()){
        std::string frontElem = op.front();
        if (std::isdigit(frontElem[0]) || std::isdigit(frontElem[1])){
            numbers.push(frontElem);
            // std::cout << "number: " << numbers.top() << "\n";
        } else {
            if (frontElem.find("add") != std::string::npos){
                auto var1 = numbers.top();
                numbers.pop();
                auto var2 = numbers.top();
                numbers.pop();
                if ((var1.find('.') != std::string::npos) || (var2.find('.') != std::string::npos)){
                    double x = std::stod(var1);
                    double y = std::stod(var2);
                    double z = x + y;
                    numbers.push(std::to_string(z));
                    std::cout << x << " + " << y << " = " << z << "\n";
                } else {
                    int x = std::stoi(var1);
                    int y = std::stoi(var2);
                    int z = x + y;
                    numbers.push(std::to_string(z));
                    std::cout << x << " + " << y << " = " << z << "\n";
                }
            } else if (frontElem.find("sub") != std::string::npos){
                auto var1 = numbers.top();
                numbers.pop();
                auto var2 = numbers.top();
                numbers.pop();
                if ((var1.find('.') != std::string::npos) || (var2.find('.') != std::string::npos)){
                    double x = std::stod(var1);
                    double y = std::stod(var2);
                    double z = x - y;
                    numbers.push(std::to_string(z));
                    std::cout << x << " - " << y << " = " << z << "\n";
                } else {
                    int x = std::stoi(var1);
                    int y = std::stoi(var2);
                    int z = x - y;
                    numbers.push(std::to_string(z));
                    std::cout << x << " - " << y << " = " << z << "\n";
                }
            } else if (frontElem.find("div") != std::string::npos){
                auto var1 = numbers.top();
                numbers.pop();
                auto var2 = numbers.top();
                numbers.pop();
                if ((var1.find('.') != std::string::npos) || (var2.find('.') != std::string::npos)){
                    double x = std::stod(var1);
                    double y = std::stod(var2);
                    double z = x / y;
                    numbers.push(std::to_string(z));
                    std::cout << x << " / " << y << " = " << z << "\n";
                } else {
                    int x = std::stoi(var1);
                    int y = std::stoi(var2);
                    int z = x / y;
                    numbers.push(std::to_string(z));
                    std::cout << x << " / " << y << " = " << z << "\n";
                }
            } else if (frontElem.find("mult") != std::string::npos){
                auto var1 = numbers.top();
                numbers.pop();
                auto var2 = numbers.top();
                numbers.pop();
                if ((var1.find('.') != std::string::npos) || (var2.find('.') != std::string::npos)){
                    double x = std::stod(var1);
                    double y = std::stod(var2);
                    double z = x * y;
                    numbers.push(std::to_string(z));
                    std::cout << x << " * " << y << " = " << z << "\n";
                } else {
                    int x = std::stoi(var1);
                    int y = std::stoi(var2);
                    int z = x * y;
                    numbers.push(std::to_string(z));
                    std::cout << x << " * " << y << " = " << z << "\n";
                }
            } else if (frontElem.find("sqrt") != std::string::npos){
                auto var = numbers.top();
                numbers.pop();

                if (var.find('.') != std::string::npos){
                    double x = std::stod(var);
                    double y = std::sqrt(x);
                    numbers.push(std::to_string(y));
                    std::cout << "sqrt " << x << " = " << y << "\n";
                } else {
                    int x = std::stoi(var);
                    int y = std::sqrt(x);
                    numbers.push(std::to_string(y));
                    std::cout << "sqrt " << x << " = " << y << "\n";
                }
            } else if (frontElem.find("pop") != std::string::npos){
                std::cout << numbers.top() << " Popped\n";
                numbers.pop();
            } else if (frontElem.find("reverse") != std::string::npos){
                std::queue <std::string> reverse;
                int nth = std::stoi(numbers.top());
                numbers.pop();
                std::cout << "blocks of number to reverse: " << nth << "\n";
                for (int i = 0; i < nth; ++i){
                    reverse.push(numbers.top());
                    numbers.pop(); 
                }
                for (int j = 0; j < nth; ++j)
                {
                    numbers.push(reverse.front());
                    reverse.pop();
                }
            } else if (frontElem.find("endrepeat") != std::string::npos){
                std::cout << "endrepeat operator: " << frontElem << "\n";
            } else if (frontElem.find("repeat") != std::string::npos){
                int nth = std::stoi(numbers.top());
                numbers.pop();
                std::cout << "Number of repeats: " << nth << "\n";
            }
        }
        // std::cout << "popping: " <<op.front() << "\n";
        op.pop();
    }
    ptr(numbers);
    //close input file
    in.close();
}

void checker(std::stack<std::string> &stk, string x, string y){
    
}

void ptr(std::stack<std::string> stk){
    std::cout << "--------------------\n";
    while (!stk.empty()){
        std::cout << "\t" << stk.top() << "\n";
        std::cout << "--------------------\n";
        stk.pop();
    }
}