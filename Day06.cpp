#include <iostream>
#include "ComplexNum.h"


int main()
{
	ComplexNum firstNum(3, 2);
	ComplexNum secondNum(2, 0);
	ComplexNum thirdNum(2, 0);

	std::cout << "first number: ";
	firstNum.Display();
	std::cout << "second number: ";
	secondNum.Display();
	std::cout << "third number: ";
	thirdNum.Display();

	ComplexNum additionResult;

	additionResult = firstNum + secondNum;
	std::cout << "Result of adding first and second: ";
	additionResult.Display();
	std::cout << '\n';

	ComplexNum subResult;

	subResult = firstNum - secondNum;
	std::cout << "Result of subtracting first from second: ";
	subResult.Display();
	std::cout << '\n';

	std::cout << "result of comparing first and second with == : ";
	firstNum == secondNum ? std::cout << "true\n" : std::cout << "false\n";
	std::cout << "result of comparing first and second with != : ";
	firstNum != secondNum ? std::cout << "true\n" : std::cout << "false\n";

	std::cout << '\n';
	float complxSqr = firstNum;
	std::cout << "casting first number: " << complxSqr << '\n';

}