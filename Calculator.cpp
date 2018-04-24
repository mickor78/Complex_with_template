#include "Calculator.h"

std::queue<std::string> Calculator::toRPN(std::string data) {
    std::queue<std::string> result;
    std::stack<char> stac;
    std::string builder = "";
    for (unsigned int i = 0; i < data.length(); i++) {
        switch (data.at(i)) {
            case '+':
                if (builder != "") {
                    result.push(builder);
                }
                builder = "";
                if (stac.empty() || (!stac.empty() && stac.top() == '(')) {
                    stac.push('+');
                } else {
                    while (!stac.empty() && stac.top() != '(') {
                        std::string pu = "";
                        pu += stac.top();
                        result.push(pu);
                        stac.pop();
                    }
                    stac.push('+');
                }
                break;
            case '-':
                if (builder != "") {
                    result.push(builder);
                }
                builder = "";
                if (stac.empty() || (!stac.empty() && stac.top() == '(')) {
                    stac.push('-');
                } else {
                    while (!stac.empty() && stac.top() != '(') {
                        std::string pu = "";
                        pu += stac.top();
                        result.push(pu);
                        stac.pop();
                    }
                    stac.push('-');
                }
                break;
            case '*':
                if (builder != "") {
                    result.push(builder);
                }
                builder = "";
                if (stac.empty() || (!stac.empty() && (stac.top() != '*' && stac.top() != '/'))) {
                    stac.push('*');
                } else {
                    while (!stac.empty() && (stac.top() == '*' || stac.top() == '/')) {
                        std::string pu = "";
                        pu += stac.top();
                        result.push(pu);
                        stac.pop();
                    }
                    stac.push('*');
                }
                break;
            case '/':
                if (builder != "") {
                    result.push(builder);
                }
                builder = "";
                if (stac.empty() || (!stac.empty() && (stac.top() != '*' && stac.top() != '/'))) {
                    stac.push('/');
                } else {
                    while (!stac.empty() && (stac.top() == '*' || stac.top() == '/')) {
                        std::string pu = "";
                        pu += stac.top();
                        result.push(pu);
                        stac.pop();
                    }
                    stac.push('/');
                }
                break;
            case '(':
                if (builder != "") {
                    result.push(builder);
                }
                builder = "";
                stac.push('(');
                break;
            case ')':
                if (builder != "") {
                    result.push(builder);
                }
                builder = "";
                while (stac.top() != '(') {
                    std::string pu = "";
                    pu += stac.top();
                    result.push(pu);
                    stac.pop();
                }
                stac.pop();//remove last bracket (
                break;
            default:
                builder += data.at(i);
        }
    }
    if (builder != "") {
        result.push(builder);
    }
    while (!stac.empty()) {
        std::string pu = "";
        pu += stac.top();
        result.push(pu);
        stac.pop();
    }
    return result;
}

Mcomplex<> Calculator::res(std::queue<std::string> &que) {
    std::stack<Mcomplex<> > stac;
    Mcomplex<> arg1, arg2;
    while (!que.empty()) {
        if (que.front() == "+") {
            arg1 = stac.top();
            stac.pop();
            arg2 = stac.top();
            stac.pop();
            Mcomplex<> result = arg2 + arg1;
            stac.push(result);
        } else if (que.front() == "-") {
            arg1 = stac.top();
            stac.pop();
            arg2 = stac.top();
            stac.pop();
            Mcomplex<> result = arg2 - arg1;
            stac.push(result);
        } else if (que.front() == "*") {
            arg1 = stac.top();
            stac.pop();
            arg2 = stac.top();
            stac.pop();
            Mcomplex<> result = arg2 * arg1;
            stac.push(result);
        } else if (que.front() == "/") {
            try {
                arg1 = stac.top();
                stac.pop();
                arg2 = stac.top();
                stac.pop();
                Mcomplex<> result = arg2 / arg1;
                stac.push(result);
            } catch (const std::exception &e) {
                std::cout << e.what();
            }
        } else {
            Mcomplex<> num = toC(que.front());
            stac.push(num);
        }
        que.pop();
    }
    return stac.top();
}

Mcomplex<> Calculator::toC(std::string s) {
    double d;
    std::stringstream stre;
    stre << s;
    stre >> d;
    std::string im = "";
    if (s.find(Mcomplex<>::IMAGINARY_UNIT) != s.npos || s.find(toupper(Mcomplex<>::IMAGINARY_UNIT)) != s.npos) {
        im = "";
        im += static_cast<char>(tolower(Mcomplex<>::IMAGINARY_UNIT));
        if (s == im)
            return Mcomplex<>(0, 1);
        else
            return Mcomplex<>(0, d);
    } else {
        return Mcomplex<>(d);
    }
}

std::string Calculator::solve(std::string s, std::map<std::string,Mcomplex<> > &mapOfVariables) {
    s = Input::trim(s);
    if (s.length() == 0)
        throw std::invalid_argument("No data");
    unsigned int leng = s.length() - 1;

    std::string left, right;
    Mcomplex<> cright;
            try {
                left = s.substr(0, s.find('='));
                right = s.substr(s.find('=') + 1, s.length() - s.find('=') - 1);
                cright = parse(right,mapOfVariables);
                Mcomplex<> result;
                result = cright;
                mapOfVariables.insert(std::make_pair(left,cright));
                return result.value();
            }
            catch (const std::exception &e) {
                std::cout << e.what();
    }
    return "";
}
