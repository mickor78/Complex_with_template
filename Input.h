#ifndef INPUT_H_
#define INPUT_H_
#include "Mcomplex.h"
#include <vector>
#include <stdexcept>
#include <string>
#include <map>
#include <sstream>

class Input
{
public:
    Input()=default;
    std::string parseString(std::string line,std::map<std::string,Mcomplex<> >) const;
    static std::string trim(std::string data);
protected:
    bool isOperator(const char ch) const;
    bool isImaginary(const char ch) const;
    std::vector<std::string> split(const std::string& str,const std::vector<char>& spl) const;
};
#endif // INPUT_H_
