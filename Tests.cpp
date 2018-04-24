#include "Tests.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <complex>
Tests Tests::getInstance()
{
	static Tests t{};
	return t;	
}
void Tests::run()
{
	this->complexT();
	this->calculatorT();
}
void Tests::complexT()
{
    const double EPSILON=0.00001;
    std::complex<double> s1,s2,sres;
    Mcomplex<> m1,m2,mres;
    srand(time(0));
    for(int i=0;i<1e6;i++)
    {
        double re,im;//<1;101)
        re=(rand()/(RAND_MAX)+1.0)*100+1;
        im=(rand()/(RAND_MAX)+1.0)*100+1;
        s1.real(re);s1.imag(im);
        m1=Mcomplex<>(re,im);
        re=(rand()/(RAND_MAX+1.0))*100+1;
        im=(rand()/(RAND_MAX+1.0))*100+1;
        s2.real(re);s2.imag(im);
        m2=Mcomplex<>(re,im);
        sres=s1+s2;
        mres=m1+m2;
        if(fabs(mres.getReal()-sres.real())>=EPSILON || fabs(mres.getImaginary()!=sres.imag())>=EPSILON)
        {
            std::cout<<"+ test failed"<<std::endl;
            return;
        }
        sres=s1-s2;
        mres=m1-m2;
        if(fabs(mres.getReal()-sres.real())>=EPSILON || fabs(mres.getImaginary()!=sres.imag())>=EPSILON)
        {
            std::cout<<"- test failed"<<std::endl;
            return;
        }
        sres=s1*s2;
        mres=m1*m2;
        if(fabs(mres.getReal()-sres.real())>=EPSILON || fabs(mres.getImaginary()!=sres.imag())>=EPSILON)
        {
            std::cout<<"* test failed"<<std::endl;
            return;
        }
        sres=s1/s2;
        try
        {
            mres=m1/m2;
        }catch(const std::exception& e)
        {
            std::cout<<"ERROR: "<<e.what();
            exit(1);
        }
        if(fabs(mres.getReal()-sres.real())>=EPSILON || fabs(mres.getImaginary()!=sres.imag())>=EPSILON)
        {
            std::cout<<"/ test failed"<<std::endl;
            return;
        }
    }
    std::cout<<"Passed"<<std::endl;
}
void Tests::calculatorT()
{
    std::vector<std::string> test={"0","2","2+j","2+2j","2-2j",
                                    "-j","-3j","j","3j","jj",
                                    "(2)(3)","(1+j)(1+j)","12j2","12.23j-12/4+j/3","1>2",
                                    "2<4","2j+3>=5","1.25+j=","2+2*2=6","7*7>=49",
                                    "3*6j<=-.1+18j","(13)(23456)",
                                    };
    Calculator calc;
    try
    {
        std::map<std::string,Mcomplex<> > mapOfCVariables;
        for(std::string s:test)
        {
            std::string result;
            result=calc.solve(s,mapOfCVariables);
            std::cout<<s<<" -> "<<result<<std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cout<<e.what();
    }
}
