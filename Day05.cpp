#include <iostream>
#include "ComplexNum.h"

void addTwoCompNums(ComplexNum n1, ComplexNum n2) {
    int realResult = n1.getReal() + n2.getReal();
    int imagResult = n1.getImag() + n2.getImag();
    ComplexNum result(realResult, imagResult);
    
    result.Display();
}

void subtractTwoCompNums(ComplexNum n1, ComplexNum n2) {
    int realResult = n1.getReal() - n2.getReal();
    int imagResult = n1.getImag() - n2.getImag();
    ComplexNum result(realResult, imagResult);

    result.Display();
}

int main()
{
    ComplexNum firstNum(3, 2);
    ComplexNum secondNum(2, 0);

    std::cout << "adding: ";
    firstNum.Display();
    std::cout << "to: ";
    secondNum.Display();
    std::cout << "Result : ";
    addTwoCompNums(firstNum, secondNum);
    std::cout << '\n';

    ComplexNum thirdNum(5, 1);
    ComplexNum forthNum(2, 6);

    std::cout << "subtracting: ";
    thirdNum.Display();
    std::cout << "from: ";
    forthNum.Display();
    std::cout << "Result : ";

    subtractTwoCompNums(thirdNum, forthNum);
}