#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stack>
#include <string>
#include <queue>

void autoStacker(std::stack<std::string> &ts, std::stack<double> &ds, std::stack<int> &is, std::string var);
auto autoPoppper(std::stack<std::string> &ts, std::stack<double> &ds, std::stack<int> &is);

int main(int argc, char* argv[]) {

    // setup the print out format for the precision required.
    std::cout.setf(std::ios::fixed,std::ios::floatfield);
    std::cout.precision(3);

    // open the file for reading
    std::ifstream in;
    in.open(argv[1]);

    std::cout << argv[1] << std::endl;

    // Initation
    std::string s;
    std::queue <std::string> op;
    std::stack <double> doubleStack;
    std::stack <int> intStack;
    std::stack <std::string> typeStack;


    // read the file while we have input and shove it into a queue.
    while (in >> s) {
        op.push(s);
    }

    // loop from queue
    while (!op.empty()){
        std::string frontElem = op.front();
        if (frontElem.find('.') != std::string::npos){
            autoStacker(typeStack, doubleStack, intStack, frontElem);
        } else if (std::isdigit(frontElem[0])){
            autoStacker(typeStack, doubleStack, intStack, frontElem);
        } else {
            if (frontElem.find("add")){
                auto var1 = autoPoppper(typeStack, doubleStack, intStack);
                auto var2 = autoPoppper(typeStack, doubleStack, intStack);

                auto sum = var1 + var2;
                autoStacker(typeStack, doubleStack, intStack, sum);
                std::cout << var1 << " + " << var2 << " = " << sum << "\n";
            } else if (frontElem.find("sub")){
                std::cout << "operator: " << op.front() << "\n";
            } else if (frontElem.find("div")){
                std::cout << "operator: " << op.front() << "\n";
            } else if (frontElem.find("sqrt")){
                std::cout << "operator: " << op.front() << "\n";
            } else if (frontElem.find("pop")){
                std::cout << "operator: " << op.front() << "\n";
            } else if (frontElem.find("reverse")){
                std::cout << "operator: " << op.front() << "\n";
            } else if (frontElem.find("repeat")){
                std::cout << "operator: " << op.front() << "\n";
            } else if (frontElem.find("endrepeat")){
                std::cout << "operator: " << op.front() << "\n";
            }
        }
        op.pop();
    }

    //close input file
    in.close();
}

void autoStacker(std::stack<std::string> &ts, std::stack<double> &ds, std::stack<int> &is, std::string var){
    if (var.find('.') != std::string::npos){
        double d = std::stod(var);
        ds.push(d);
        ts.push("double");
        //debugger
        std::cout << "PUSHED: double stack: " << ds.top() << "\n";
    } else if (std::isdigit(var[0])){
        int i = std::stoi(var);
        is.push(i);
        ts.push("integer");
        //debugger
        std::cout << "PUSHED: integer stack: " << is.top() << "\n";
    }
}

auto autoPoppper(std::stack<std::string> &ts, std::stack<double> &ds, std::stack<int> &is){
    auto var;
    string typeCheck = ts.top();
    if (typeCheck.find("double")){
        var = ds.top();
        ds.pop();
    } else {
        var = is.pop();
        is.pop();
    }
    ts.pop();
    return var;
}
