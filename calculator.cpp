#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stack>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>

//Prototype Declaration
//operations
std::string checker(std::stack<std::string> &numbers, std::string op, std::string var1, std::string var2);
template<typename T>
T operation(T x, T y, std::string op);
void sqrt_op(std::stack<std::string> &numbers, std::string var);
void reverse_op(std::stack<std::string> &numbers, int nth);
void pop_op(std::stack<std::string> &numbers);
void repeat_op(std::queue <std::string> &op, std::stack <std::string> &numbers, int times);
void end_repeat_op(std::queue <std::string> &op, std::stack <std::string> &numbers, std::vector<std::string> &repeater, int times);

//End stage printer
void op_ptr(std::string op, auto x, auto y, auto z);
void pre_print_check(std::string op, std::string x, std::string y, std::string z);

int main(int argc, char* argv[]) {

    // setup the print out format for the precision required.
    std::cout.setf(std::ios::fixed,std::ios::floatfield);
    std::cout.precision(3);

    // open the file for reading
    std::ifstream in;
    in.open(argv[1]);

    //seg fault will occur if theres no input so 
    //I have it set to EXIT_FAILURE if no input
    if (argv[1] != NULL){
        std::cout << argv[1] << std::endl;
    } else {
        std::cout << "Please input a valid filename" << std::endl;
        return EXIT_FAILURE;
    }

    // Initialisation
    std::string s;
    std::queue <std::string> op;
    std::stack <std::string> numbers;

    // read the file while we have input and shove it into a queue.
    while (in >> s) {
        op.push(s);
    }

    // loop from queue
    while (!op.empty()){
        std::string frontElem = op.front();
        //Check if the front of the queue is a digit
        if (std::isdigit(frontElem[0]) || std::isdigit(frontElem[1])){
            numbers.push(frontElem);
            op.pop();
        } else {
            if (frontElem.find("repeat") != std::string::npos){
                int nth = std::stoi(numbers.top());
                numbers.pop();
                op.pop();
                repeat_op(op, numbers, nth);
            } else {
                if (frontElem.find("pop") != std::string::npos){
                    numbers.pop();
                } else if (frontElem.find("reverse") != std::string::npos){
                    int nth = std::stoi(numbers.top());
                    numbers.pop();
                    reverse_op(numbers, nth);
                } else if(frontElem.find("sqrt") != std::string::npos){
                    auto var = numbers.top();
                    numbers.pop();
                    sqrt_op(numbers, var);
                //All other simple op
                } else {
                    auto var1 = numbers.top();
                    numbers.pop();
                    auto var2 = numbers.top();
                    numbers.pop();
                    auto var3 = checker(numbers, frontElem, var1, var2);
                    pre_print_check(frontElem, var1, var2, var3);
                }    
                op.pop();
            }
        }
    }
    //close input file
    in.close();
    return 0;
}

//Convert the variable to the appropriate type to print out to get 3 decimal place
void pre_print_check(std::string op, std::string x, std::string y, std::string z){
    if (x.find('.') != std::string::npos && y.find('.') == std::string::npos){
        double v1 = std::stod(x);
        int v2 = std::stoi(y);
        double v3 = std::stod(z);
        op_ptr(op, v1, v2, v3);
    } else if (x.find('.') == std::string::npos && y.find('.') != std::string::npos){
        int v1 = std::stoi(x);
        double v2 = std::stod(y);
        double v3 = std::stod(z);
        op_ptr(op, v1, v2, v3);
    } else {
        op_ptr(op, x, y, z);
    }
}

//Operation printer
void op_ptr(std::string op, auto x, auto y, auto z){
    if (op.find("add") != std::string::npos){
        std::cout << x << " + " << y << " = " << z << "\n";
    } else if (op.find("sub") != std::string::npos){
        std::cout << x << " - " << y << " = " << z << "\n";
    } else if (op.find("div") != std::string::npos){
        std::cout << x << " / " << y << " = " << z << "\n";
    } else if (op.find("mult") != std::string::npos){
        std::cout << x << " * " << y << " = " << z << "\n";
    }
}

//Checks whether a variable is a int or double
std::string checker(std::stack<std::string> &numbers, std::string op, std::string var1, std::string var2){
    std::string ret;
    if ((var1.find('.') != std::string::npos) || (var2.find('.') != std::string::npos)){
        double x = std::stod(var1);
        double y = std::stod(var2);
        auto z = operation(x,y,op);
        ret = std::to_string(z);
        numbers.push(ret);
    } else {
        int x = std::stoi(var1);
        int y = std::stoi(var2);
        auto z = operation(x,y,op);
        ret = std::to_string(z);
        numbers.push(ret);
    }
    return ret;
}

//Standard Operation
template<typename T>
T operation(T x, T y, std::string op){
    auto z = x;
    if (op.find("add") != std::string::npos){
        z = x+y;
    } else if (op.find("sub") != std::string::npos){
        z = x-y;
    } else if (op.find("div") != std::string::npos){
        z = x/y;
    } else if (op.find("mult") != std::string::npos){
        z = x*y;
    } else {
        z = 0;
    }
    return z;
}

//While it didn't find the endrepeat command will continue
void repeat_op(std::queue <std::string> &op, std::stack <std::string> &numbers, int times){
    std::vector<std::string> rep;

    while (!op.empty()){
        std::string var = op.front();
        if (var.find("endrepeat") == std::string::npos){
            rep.push_back(var);
            op.pop();
        } else {
            op.pop();
            break;
        }
    }
    end_repeat_op(op, numbers, rep, times);
}

//when this function is called it iterate through the vector for the amount of times needed
//basically execute all the operation
//pushing numbers into stack while executing from vector instead
void end_repeat_op(std::queue <std::string> &op, std::stack <std::string> &numbers, std::vector<std::string> &repeater, int times){
    for (int i = 0; i < times; i++){
        //Vector iteration
        for (auto itr = repeater.begin(); itr != repeater.end(); ++itr){
            std::string it = *itr;
            if (std::isdigit(it[0]) || std::isdigit(it[1])){
                numbers.push(it);
            } else {
                if (it.find("pop") != std::string::npos){
                    numbers.pop();
                } else if (it.find("reverse") != std::string::npos){
                    int nth = std::stoi(numbers.top());
                    numbers.pop();
                    reverse_op(numbers, nth);
                } else if(it.find("sqrt") != std::string::npos){
                    auto var = numbers.top();
                    numbers.pop();
                    sqrt_op(numbers, var);
                //All other simple op
                } else {
                    auto var1 = numbers.top();
                    numbers.pop();
                    auto var2 = numbers.top();
                    numbers.pop();
                    auto var3 = checker(numbers, it, var1, var2);
                    pre_print_check(it, var1, var2, var3);
                }
            }
        }
    }
}

//Square Root Op
void sqrt_op(std::stack<std::string> &numbers, std::string var){
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
}

//Reverse op
void reverse_op(std::stack<std::string> &numbers, int nth){
    std::queue <std::string> reverse;
    for (int i = 0; i < nth; ++i){
        reverse.push(numbers.top());
        numbers.pop(); 
    }
    for (int j = 0; j < nth; ++j){
        numbers.push(reverse.front());
        reverse.pop();
    }
}
