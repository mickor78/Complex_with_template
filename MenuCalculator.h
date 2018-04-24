#ifndef MENUCALCULATOR_H_
#define MENUCALCULATOR_H_
#include "Calculator.h"
class MenuCalculator
{
public:
    static MenuCalculator getInstance()
    {
        static MenuCalculator menu;
        return menu;
    }
    void run();
protected:
    void show();
private:
    Calculator calc;
    MenuCalculator()=default;
    MenuCalculator(const MenuCalculator& m)=default;
};
#endif // MENU_H_
