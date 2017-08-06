#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

int main(int argc, char* argv[]) {

    // setup the print out format for the precision required.
    std::cout.setf(std::ios::fixed,std::ios::floatfield);
    std::cout.precision(3);

    // open the file for reading
    std::ifstream in;
    in.open(argv[1]);

    std::cout << argv[1] << std::endl;

    // string to be read into
    std::string s;
    // std::stack<double> number;

    // read the file while we have input.
    double x = 234.090;
    if (x == std::floor(x)){
        std::cout << "int" << "\n";
        int v = x;
        std::cout << v << "\n";
    } else {
        std::cout << x << "\n";
    }
    while (in >> s) {
        if (s.find('.') != std::string::npos){
            double d = std::stod(s);
            std::cout << d << "\n";
            // std::number.push(s);
        } else {
            std::cout << s << "\n";
        }
    }
    in.close();
}