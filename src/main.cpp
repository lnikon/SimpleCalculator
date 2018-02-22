#include <iostream>
#include <string>

#include "evaluator.h"

int main()
{
    std::cout << "Calculate something!\n";
    
    std::string str;
    
    while(getline(std::cin, str))
    {
        Evaluator<double> e(str);
        std::cout << e.GetValue() << std::endl;
    }
    
    return 0;
}
