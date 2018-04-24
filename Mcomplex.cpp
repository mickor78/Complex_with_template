#include "Mcomplex.h"
#include <exception>
#include <stdexcept>
#include <cmath>
#include <sstream>
template <class T>
const Mcomplex<T>& Mcomplex<T>::operator+=(const Mcomplex<T>& rw)
{
    this->re_+=rw.re_;
    this->im_+=rw.im_;
    return *this;
};
template <class T>

const Mcomplex<T>& Mcomplex<T>::operator-=(const Mcomplex<T>& rw)
{
    this->re_-=rw.re_;
    this->im_-=rw.im_;
    return *this;
};
template <class T>

const Mcomplex<T>& Mcomplex<T>::operator*=(const Mcomplex<T>& rw)
{
    double r=this->re_*rw.re_-this->im_*rw.im_,i=this->re_*rw.im_+this->im_*rw.re_;
    this->re_=r;
    this->im_=i;
    return *this;
};
template <class T>

const Mcomplex<T>& Mcomplex<T>::operator/=(const Mcomplex<T>& rw)
{
    if(rw.re_==0.0 && rw.im_==0.0)
        throw std::invalid_argument("Divide by 0\n");
    double r=(this->re_*rw.re_+this->im_*rw.im_)/(rw.re_*rw.re_+rw.im_*rw.im_),i=(this->im_*rw.re_-this->re_*rw.im_)/(rw.re_*rw.re_+rw.im_*rw.im_);
    this->re_=r;
    this->im_=i;
    return *this;
};
template <class T>

Mcomplex<T> Mcomplex<T>::operator+(const Mcomplex<T>& rw) const
{
    Mcomplex<T> r(this->re_+rw.re_,this->im_+rw.im_);
    return r;
}
template <class T>

Mcomplex<T> Mcomplex<T>::operator-(const Mcomplex<T>& rw) const
{
    Mcomplex<T> r(this->re_-rw.re_,this->im_-rw.im_);
    return r;
}
template <class T>

Mcomplex<T> Mcomplex<T>::operator*(const Mcomplex<T>& rw) const
{
    Mcomplex<T> r(this->re_*rw.re_-this->im_*rw.im_,this->re_*rw.im_+this->im_*rw.re_);
    return r;
}
template <class T>

Mcomplex<T> Mcomplex<T>::operator/(const Mcomplex<T>& rw) const
{
    if(rw.re_==0.0 && rw.im_==0.0)
        throw std::invalid_argument("Divide by 0\n");
    Mcomplex<T> r((this->re_*rw.re_+this->im_*rw.im_)/(rw.re_*rw.re_+rw.im_*rw.im_),(this->im_*rw.re_-this->re_*rw.im_)/(rw.re_*rw.re_+rw.im_*rw.im_));
    return r;
}
template <class T>

bool Mcomplex<T>::operator==(const Mcomplex<T>& a) const
{
    return (this->re_==a.re_ && this->im_==a.im_);
}
template <class T>

bool Mcomplex<T>::operator!=(const Mcomplex<T>& a) const
{
	return (this->re_!=a.re_ || this->im_!=a.im_);
}
template <class T>

bool Mcomplex<T>::operator<=(const Mcomplex<T>& a) const
{
    return (*this==a || *this<a);
}
template <class T>

bool Mcomplex<T>::operator>=(const Mcomplex<T>& a) const
{
    return (*this==a || *this>a);
}
template <class T>

bool Mcomplex<T>::operator<(const Mcomplex<T>& a) const
{
    return (this->re_<a.re_)||(this->re_==a.re_ && this->im_<a.im_);
}
template <class T>

bool Mcomplex<T>::operator>(const Mcomplex<T>& a) const
{
    return (this->re_>a.re_)||(this->re_==a.re_ && this->im_>a.im_);
}

template <class T>
double Mcomplex<T>::abs() const
{
    return sqrt(re_*re_+im_*im_);
}

template <class T>

double Mcomplex<T>::argument() const
{
    return atan2(this->im_,this->re_);
}

template <class T>

double Mcomplex<T>::getReal() const
{
    return re_;
}
template <class T>

double Mcomplex<T>::getImaginary() const
{
    return im_;
}
template <class T>

std::string Mcomplex<T>::value() const
{
	if(this->re_==0.0 && this->im_==0.0)
        return "0";
    std::stringstream strea;
    std::string retu="";
    if(this->re_!=0.0 && this->im_==0.0)
    {
        strea.str("");
        strea<<re_;
        retu+=strea.str();
        return retu;
    }
    if(this->re_==0.0 && this->im_!=0.0)
    {
        if(this->im_==1.0)
        {
            retu+=tolower(IMAGINARY_UNIT);
            return retu;
        }else if(this->im_==-1.0)
        {
            retu="-";
            retu+=tolower(IMAGINARY_UNIT);
            return retu;
        }
        else
        {
            strea.str("");
            strea<<this->im_;
            retu=strea.str();
            retu+=tolower(IMAGINARY_UNIT);
            return retu;
        }
    }
    if(this->re_!=0.0 && this->im_!=0.0)
    {
        strea<<this->re_;
        retu=strea.str();
        if(this->im_==1.0)
        {
            retu+="+";
            retu+=tolower(IMAGINARY_UNIT);
            return retu;
        }else if(this->im_==-1.0)
        {
            retu+="-";
            retu+=tolower(IMAGINARY_UNIT);
            return retu;
        }
        else
        {
            strea.str("");
            strea<<im_;
            retu+=(this->im_>0.0?"+":"")+strea.str();
            retu+=tolower(IMAGINARY_UNIT);
            return retu;
        }
    }
    return "";
}
template <class T>

std::ostream& operator<<(std::ostream& out, const Mcomplex<T>& z)
{
    return out<<z.value();
}
