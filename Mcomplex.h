#ifndef MCOMPLEX_H_
#define MCOMPLEX_H_
#include <iostream>
#include <sstream>
template<class T = double>
class Mcomplex
{
public:
    static const char IMAGINARY_UNIT='j';
    Mcomplex():re_(0),im_(0){}
    Mcomplex(const Mcomplex<T>& r)=default;
    Mcomplex(double r):re_(r),im_(0){}
    Mcomplex(double r,double i):re_(r),im_(i){}
    const Mcomplex<T>& operator+=(const Mcomplex<T>& rw);
    const Mcomplex<T>& operator-=(const Mcomplex<T>& rw);
    const Mcomplex<T>& operator*=(const Mcomplex<T>& rw);
    const Mcomplex<T>& operator/=(const Mcomplex<T>& rw);
    Mcomplex<T> operator+(const Mcomplex<T>& rw) const;
    Mcomplex<T> operator-(const Mcomplex<T>& rw) const;
    Mcomplex<T> operator*(const Mcomplex<T>& rw) const;
    Mcomplex<T> operator/(const Mcomplex<T>& rw) const;
    bool operator==(const Mcomplex<T>& a) const;
    bool operator!=(const Mcomplex<T>& a) const;
    bool operator<=(const Mcomplex<T>& a) const;
    bool operator>=(const Mcomplex<T>& a) const;
    bool operator<(const Mcomplex<T>& a) const;
    bool operator>(const Mcomplex<T>& a) const;
    double getReal() const;
    double getImaginary() const;
    std::string value() const;
    double argument()const;
    double abs() const;
    static void test();
    friend std::ostream& operator<<(std::ostream& out, const Mcomplex<T>& z);
protected:
private:
    double re_,im_;
};
#endif // MCOMPLEX_H_
