/**
 * @author Michal Korzniewski
 * @version 1.0 24/04/2018
 */

#include <iostream>
#include "MenuCalculator.h"
#include "Tests.h"
void arithmeticTest();

int main()
{
    //#define _DEBUG
    #ifdef _DEBUG
        Tests::getInstance().run();
    #endif // _DEBUG
    MenuCalculator::getInstance().run();
    return 0;
}
