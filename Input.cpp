#include "Input.h"
bool Input::isOperator(const char ch) const
{
    return (ch=='+' || ch=='-' || ch=='*' || ch=='/');
}
bool Input::isImaginary(const char ch) const
{
    return (ch==tolower(Mcomplex<>::IMAGINARY_UNIT) || ch==toupper(Mcomplex<>::IMAGINARY_UNIT));
}
std::vector<std::string> Input::split(const std::string& str,const std::vector<char>& spl) const
{
    std::vector<std::string>result;
    std::string tem="";
    bool con=true;
    for(unsigned int i=0;i<str.length();i++)
    {
        con=true;
        for(char c:spl)
        {
            if(str.at(i)==c)
            {
                con=false;
                break;
            }
        }
        if(con==true)
            tem+=str.at(i);
        else
        {
            if(tem!="")
            {
                result.push_back(tem);
                tem="";
            }
        }
    }
    if(tem!="")
        result.push_back(tem);
    return result;
}
std::string Input::parseString(std::string line, std::map<std::string,Mcomplex<> > mapOfCNumbers) const
{
    line=trim(line);
    std::string result="";
    unsigned int obr,cbr;
    obr=cbr=0;
    if(line.at(0)=='+')//+ at the beginning
    {
        line.at(0)='+';
        line='0'+line;
    }
    if(line.at(0)=='-')//- at the beginning
    {
        line.at(0)='-';
        line='0'+line;
    }
    if(line.at(0)=='*' || line.at(0)=='/' || isOperator(line.at(line.length()-1)))
        throw std::invalid_argument("Invalid input data");
    unsigned int j=0;
    while(j<line.length()-1)
    {
        if(line.at(j)=='+' && line.at(j+1)=='-')
            {
                std::string res="";
                res+=line.substr(0,j);
                res+='-';
                res+=line.substr(j+2,line.length()-1-j-1);
                line=res;
                j=0;
                continue;
            }
        if(line.at(j)=='-' && line.at(j+1)=='-')
            {
                std::string res="";
                res+=line.substr(0,j);
                res+='+';
                res+=line.substr(j+2,line.length()-1-j-1);
                line=res;
                j=0;
                continue;
            }
            j++;
    }
    for(unsigned int i=0;i<line.length();i++){
        if(line.at(i)>='a'&& line.at(i)<='z'&&line.at(i)!='j'){
            std::stringstream ss,rr;
            rr<< line.at(i);
            std::string NAZWA = rr.str();
            if(mapOfCNumbers.find(NAZWA)!=mapOfCNumbers.end()){
                std::map<std::string,Mcomplex<> >::iterator Variable= mapOfCNumbers.find(NAZWA);
                ss<<Variable->second;
                std::string napis;
                napis = '('+ss.str()+')';
                line.erase(line.begin()+i);
                line.insert(i,napis);
            }
        }
    }

    for(unsigned int i=0;i<line.length();i++)
    {


        if(line.length()==1 && line.at(0)=='.')
            throw std::invalid_argument("Invalid input data");
        if(!(
                (line.at(i)>='a'&& line.at(i)<='z')||
           (line.at(i)>='0' && line.at(i)<='9') ||
           (isImaginary(line.at(i))) ||
           (isOperator(line.at(i)) || line.at(i)=='(' || line.at(i)==')' || line.at(i)=='.')
             )
          )
            throw std::invalid_argument("Invalid input data");
        if(line.at(i)=='(')obr++;
        if(line.at(i)==')')cbr++;
		if(cbr>obr)
			throw std::invalid_argument("Ivalid input data");
		if(
           i<(line.length()-1) &&
               (
                 ((isOperator(line.at(i)) && isOperator(line.at(i+1))) || (line.at(i)=='(' && line.at(i+1)==')')) ||
                 (isOperator(line.at(i)) && ( line.at(i+1)==')')) ||
                 ((line.at(i+1)=='*' || line.at(i+1)=='/') && (line.at(i)=='('))
               )
           )
            throw std::invalid_argument("Invalid input data");
        if(
           i>0 &&
           i<(line.length()-1) &&
           (
            ((line.at(i)=='.' && (isOperator(line.at(i+1)) || line.at(i+1)=='(' || line.at(i+1)==')') && (isOperator(line.at(i-1)) || line.at(i-1)=='(' || line.at(i-1)==')'))) ||
            (line.at(i)=='.' && isImaginary(line.at(i+1)) && isImaginary(line.at(i-1))) ||
            (line.at(i)=='.' && isOperator(line.at(i+1)) && isOperator(line.at(i-1))) ||
            (line.at(i)=='.' && (isOperator(line.at(i-1)) || isImaginary(line.at(i-1))) && (isOperator(line.at(i+1)) || isImaginary(line.at(i+1))))
           )
          )
            throw std::invalid_argument("Invalid input data");
    }
    if(obr!=cbr)
        throw std::invalid_argument("Number of brackets is different");
    ///
    std::vector<char>chara={'(',')','*','/','+','-'};
    std::vector<std::string> arguments;
    arguments=split(line,chara);
    for(std::string s:arguments)
    {
        uint16_t n=0;
        for(unsigned i=0;i<s.length();i++)
            if(s.at(i)=='.')n++;
        if(n>1)
            throw std::invalid_argument("Dot error");
    }
    for(unsigned int i=0;i<line.length();i++)
    {
        if(i<line.length()-1)
        {
            if(isImaginary(line.at(i)))
            {
                if(isdigit(line.at(i+1)) || line.at(i+1)=='.' || isImaginary(line.at(i+1)))
                {
                    result+=tolower(Mcomplex<>::IMAGINARY_UNIT);
                    result+="*";
                    continue;
                }
            }
            if(line.at(i)==')' && (isdigit(line.at(i+1)) || isImaginary(line.at(i+1))))
            {
                result+=")*";
                continue;
            }
            if(line.at(i)==')' && line.at(i+1)=='(')
            {
                result+=")*(";
                i++;
                continue;
            }
        }
        if(i>0)
        {
            if(line.at(i)=='(' && (isdigit(line.at(i-1)) || isImaginary(line.at(i-1))))
            {
                result+="*(";
                continue;
            }
            if(line.at(i-1)=='(' && line.at(i)=='-')
            {
                result+="0-";
                continue;
            }
            if(line.at(i-1)=='(' && line.at(i)=='+')
            {
                continue;
            }
        }
        result+=line.at(i);
    }
    #ifdef _DEBUG
	std::cout<<result<<std::endl;
    #endif // _DEBUG
    return result;
}
std::string Input::trim(std::string data)
{
    std::string res="";
    for(unsigned int i=0;i<data.length();i++)
        if(data.at(i)!=' ' && data.at(i)!='\t' && data.at(i)!='\n' && data.at(i)!='\r')
            res+=data.at(i);
    return res;
}
