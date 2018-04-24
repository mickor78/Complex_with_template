#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include "Mcomplex.h"
#include "Input.h"
#include <stack>
#include <queue>
#include <map>

class Calculator
{
public:
    Calculator()=default;
    Mcomplex<> parse(std::string s, std::map<std::string,Mcomplex<> > mapOfCNubers)
    {
        static Input in_;
        s=in_.parseString(s,mapOfCNubers);
        std::queue<std::string> q=toRPN(s);
        return res(q);
    }
    std::string solve(std::string s,std::map<std::string,Mcomplex<> >&);
    static void test();
protected:
    std::queue<std::string> toRPN(std::string data);
    Mcomplex<> res(std::queue<std::string>& que);
    Mcomplex<> toC(std::string s);
};
#endif // CALCULATOR_H_
