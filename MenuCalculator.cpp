#include "MenuCalculator.h"
#include <iostream>
#include <stdexcept>
#include <map>

void MenuCalculator::run()
{
    show();
    std::string s,r;
    getline(std::cin,s);
    getline(std::cin,r);
    std::string results;
    std::string resultr;

    std::map<std::string, Mcomplex<> > mapOfCVariables;
    try
    {
        results=calc.solve(s,mapOfCVariables);
        std::cout<<results<<std::endl;
        resultr=calc.solve(r,mapOfCVariables);
        std::cout<<resultr<<std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout<<e.what()<<std::endl;
    }
}
void MenuCalculator::show()
{
    std::cout<<"Complex numbers calculator:"<<std::endl;
}
