#include "ComplexNum.h"
#include <iostream>

ComplexNum::ComplexNum(int real, int imag) {
	this->realNum = real;
	this->Imaginary = imag;
}

int ComplexNum::getReal() {
	return realNum;
}
int ComplexNum::getImag() {
	return Imaginary;
}

void ComplexNum::Display() {
	std::cout << realNum;
	if (Imaginary >= 0) {
		std::cout << " + " << Imaginary << "i";
	}
	else {
		std::cout << " - " << -Imaginary << "i";
	}
	std::cout << '\n';
}