#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <queue>
#include <stack>
#include <string>

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
    std::stack <int> intStack;
    std::stack <double> doubleStack;
    std::stack <std::string> typeStack;


    // read the file while we have input and shove it into a queue.
    while (in >> s) {
        op.push(s);
    }

    // loop from queue
    while (!op.empty()){
        std::string frontElem = op.front();
        if (frontElem.find('.') != std::string::npos){
            double d = std::stod(frontElem);
            doubleStack.push(d);
            typeStack.push("double");
            std::cout << "double stack: " << doubleStack.top() << "\n";
        } else if (std::isdigit(frontElem[0])){
            int i = std::stoi(frontElem);
            intStack.push(i);
            typeStack.push("integer");
            std::cout << "integer stack: " << intStack.top() << "\n";
        } else {
            if (frontElem.find('add')){
                auto var1;
                auto var2;

                var1 = popper(typeStack, doubleStack, intStack);
                var2 = popper(typeStack, doubleStack, intStack);
            } else if (frontElem.find('sub')){
                std::cout << "operator: " << op.front() << "\n";
            } else if (frontElem.find('div')){
                std::cout << "operator: " << op.front() << "\n";
            } else if (frontElem.find('sqrt')){
                std::cout << "operator: " << op.front() << "\n";
            } else if (frontElem.find('pop')){
                std::cout << "operator: " << op.front() << "\n";
            } else if (frontElem.find('reverse')){
                std::cout << "operator: " << op.front() << "\n";
            } else if (frontElem.find('repeat')){
                std::cout << "operator: " << op.front() << "\n";
            } else if (frontElem.find('endrepeat')){
                std::cout << "operator: " << op.front() << "\n";
            }
        }
        op.pop();
    }

    //close input file
    in.close();
}
